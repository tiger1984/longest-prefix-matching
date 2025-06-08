#include "RouteTrie.h"
#include <arpa/inet.h>

bool rtrieInit(RTrieNode **root) {
    return rtrieNodeCreate(root);
}

bool rtrieUnInit(RTrieNode **root) {
    // Free complete tree

    return rtrieFreeFullTrie(root);
}

bool rtrieFreeFullTrie(RTrieNode **root) {
    if (root == NULL || *root == NULL) {
        return false;
    }

    RTrieNode *node = *root;

    // Recursively free child nodes
    for (int i = 0; i < 2; i++) {
        rtrieFreeFullTrie(&node->children[i]);
    }

    // Free the current node
    free(node);
    *root = NULL;

    return true;

}
bool rtrieNodeCreate(RTrieNode **node) {
    if (node == NULL) {
        return false;
    }

    *node = (RTrieNode *)malloc(sizeof(RTrieNode));
    if (*node == NULL) {
        return false;
    }

    (*node)->is_route = false;
    (*node)->is_ip = false;
    (*node)->children[0] = NULL;
    (*node)->children[1] = NULL;

    return true;
}

bool rtrieNodeDestroy(RTrieNode **node) {
    if (node == NULL || *node == NULL) {
        return false;
    }

    free(*node);
    *node = NULL;

    return true;
}

bool rtrieInsertRoute(RTrieNode *root, const char *route, const char *nextHop) {
    if (!root || !route || !nextHop) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryRoute[IPV4_BITS + 1];
    char ip[16];
    int prefixLength;

    // Parse the route into IP and prefix length
    if (sscanf(route, "%15[^/]/%d", ip, &prefixLength) != 2) {
        printf("Invalid route format\n");
        return false;
    }
    // void ipv4ToBinary(const char *ip, int prefixLength, char *binary) 
    // Convert the IP and prefix length to binary representation
    if (!ipv4ToBinary(ip, prefixLength, binaryRoute)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;

    // Traverse the trie and create nodes as needed
    for (int i = 0; i < prefixLength; i++) {
        int bit = binaryRoute[i] - '0';
        if (curr->children[bit] == NULL) {
            if (!rtrieNodeCreate(&curr->children[bit])) {
                printf("Failed to create trie node\n");
                return false;
            }
        }
        curr = curr->children[bit];
    }
    // Check if the route already exists
    if (curr->is_route) {
        printf("Route already exists: %s\n", route);
        return false;
    }
    // Mark the node as a route and store the next hop
    curr->is_route = true;
    int nextHopLen = strlen(nextHop) + 1;
    // printf("Length of nextHop: %u\n", nextHopLen);
    curr->nextHop = (char *)malloc(nextHopLen);
    if (curr->nextHop == NULL) {
        printf("Memory allocation failed for nextHop\n");
        return false;
    }
    strcpy(curr->nextHop, nextHop);
    //strncpy(curr->nextHop, nextHop, sizeof(curr->nextHop) - 1);
    curr->nextHop[nextHopLen] = '\0';
    // printf("Route Add Next hop for the route: %s\n", curr->nextHop);
    // printf("Next hop stored: %s\n", nextHop);
    printf("Route added successfully: %s, Next Hop: %s\n", route, nextHop);
    return true;
}

bool rtrieDeleteRoute(RTrieNode *root, const char *route,
    void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh)) {
    if (!root || !route) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryRoute[IPV4_BITS + 1];
    char ip[16];
    int prefixLength;

    // Parse the route into IP and prefix length
    if (sscanf(route, "%15[^/]/%d", ip, &prefixLength) != 2) {
        printf("Invalid route format\n");
        return false;
    }

    // Convert the IP and prefix length to binary representation
    if (!ipv4ToBinary(ip, prefixLength, binaryRoute)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;
    RTrieNode *stack[IPV4_BITS];
    int stack_index = 0;
    RTrieNode *routeUpdateNode = NULL;

    int lastRouteIndex = 0;
    char *lastNextHop = NULL;
    

    // Traverse the trie and store the path
    for (int i = 0; i < prefixLength; i++) {
        int bit = binaryRoute[i] - '0';
        if (curr->children[bit] == NULL) {
            printf("Route not found in trie\n");
            return false;
        }
        stack[stack_index++] = curr;
        curr = curr->children[bit];

        if ((i != prefixLength - 1) && (curr->is_route)) {
            lastRouteIndex = i;
            lastNextHop = curr->nextHop;
        }
    }


    if (!curr->is_route) {
        printf("Route not registered\n");
        return false;
    }

    // Unmark the node as a route and free the nextHop
    curr->is_route = false;
    if (curr->nextHop) {
        free(curr->nextHop);
        curr->nextHop = NULL;
    }

    routeUpdateNode = curr;
    // Generate the route from start to lastRouteIndex
    char newRoute[IPV4_BITS + 1] = {0};
    for (int i = 0; i <= lastRouteIndex; i++) {
        newRoute[i] = binaryRoute[i];
    }
    newRoute[lastRouteIndex + 1] = '\0';
    char newRouteStr[32];
    binaryToIpv4String(newRoute, newRouteStr);

    // Add the network address to newRouteStr
    snprintf(newRouteStr + strlen(newRouteStr),
            sizeof(newRouteStr) - strlen(newRouteStr), "/%d",
            lastRouteIndex + 1);
    // Cleanup unused nodes
    for (int i = stack_index - 1; i >= 0; i--) {
        RTrieNode *parent = stack[i];
        if (!curr->is_ip && !curr->is_route && curr->children[0] == NULL 
                            && curr->children[1] == NULL) {
            if (routeUpdateNode == curr) {
                routeUpdateNode = NULL;
            }
            rtrieNodeDestroy(&curr);
            int bit = binaryRoute[i] - '0';
            parent->children[bit] = NULL;
            curr = parent;
        } else {
            break;
        }
    }
    printf("Route deleted successfully: %s\n", route);

    if (routeUpdateNode) {
        rtrieTraverseAllIps(routeUpdateNode, newRouteStr, lastNextHop,
            binaryRoute, prefixLength , rtIpMatchCallback);
    }
    return true;
}

bool rtrieInsertIp(RTrieNode *root, const char *ip) {
    if (!root || !ip) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryIp[IPV4_BITS + 1];

    // Convert the IP to binary representation
    if (!ipv4ToBinary(ip, IPV4_BITS, binaryIp)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;

    // Traverse the trie and create nodes as needed
    for (int i = 0; i < IPV4_BITS; i++) {
        int bit = binaryIp[i] - '0';
        if (curr->children[bit] == NULL) {
            if (!rtrieNodeCreate(&curr->children[bit])) {
                printf("Failed to create trie node\n");
                return false;
            }
        }
        curr = curr->children[bit];
    }

    // Mark the node as an IP
    if (curr->is_ip) {
        printf("IP address is already registered\n");
        return false;
    }

    curr->is_ip = true;
    return true;
}

bool rtrieDeleteIp(RTrieNode *root, const char *ip) {
    if (!root || !ip) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryIp[IPV4_BITS + 1];

    // Convert the IP to binary representation
    if (!ipv4ToBinary(ip, IPV4_BITS, binaryIp)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;
    RTrieNode *stack[IPV4_BITS];
    int stack_index = 0;

    // Traverse the trie and store the path
    for (int i = 0; i < IPV4_BITS; i++) {
        int bit = binaryIp[i] - '0';
        if (curr->children[bit] == NULL) {
            printf("IP address not found in trie\n");
            return false;
        }
        stack[stack_index++] = curr;
        curr = curr->children[bit];
    }

    if (!curr->is_ip) {
        printf("IP address not registered\n");
        return false;
    }

    // Unmark the node as an IP
    curr->is_ip = false;

    // Cleanup unused nodes
    for (int i = stack_index - 1; i >= 0; i--) {
        RTrieNode *parent = stack[i];
        if (!curr->is_ip && !curr->is_route && curr->children[0] == NULL && curr->children[1] == NULL) {
            rtrieNodeDestroy(&curr);
            int bit = binaryIp[i] - '0';
            parent->children[bit] = NULL;
            curr = parent;
        } else {
            break;
        }
    }

    return true;
}

bool rtrieSearchIp(RTrieNode *root, const char *ip,
void (*rtIpMatchCallback)(const char *ip, const char *route, const char *nh)) {

    if (!root || !ip || !rtIpMatchCallback) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryIp[IPV4_BITS + 1];
 
    // Convert the IP to binary representation
    if (!ipv4ToBinary(ip, IPV4_BITS, binaryIp)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;
    char matchedRoute[IPV4_BITS + 1] = {0};
    const char *matchedNextHop = NULL;
    int matchedLength = 0;

    // Traverse the trie to find the longest matching prefix
    for (int i = 0; i < IPV4_BITS; i++) {
        int bit = binaryIp[i] - '0';
        if (curr->children[bit] == NULL) {
            break;
        }
        curr = curr->children[bit];
        matchedRoute[i] = binaryIp[i];

        if (curr->is_route) {
            matchedRoute[i + 1] = '\0';
            matchedNextHop = curr->nextHop;
            //printf("Matched next hop: %s\n", matchedNextHop);
            matchedLength = i + 1;
        }
    }

    if (matchedLength > 0 && matchedNextHop) {
        char routeStr[32];
        for (int i = matchedLength; i < IPV4_BITS; i++) {
            matchedRoute[i] = '0';
        }
        matchedRoute[IPV4_BITS] = '\0';
        // Convert the binary route to string format
        binaryToIpv4String(matchedRoute, routeStr);
        snprintf(routeStr + strlen(routeStr), sizeof(routeStr) - strlen(routeStr), "/%d", matchedLength);
      
        rtIpMatchCallback(ip, routeStr, matchedNextHop);
        return true;
    }

    printf("No matching route found for IP: %s\n", ip);
    return false;
}

bool rtrieSearchRoute(RTrieNode *root, const char *route,
    void (*rtIpMatchCallback)(const char *ip, const char *route, const char *nh)) {

    if (!root || !route || !rtIpMatchCallback) {
        printf("Invalid input parameters\n");
        return false;
    }

    char binaryRoute[IPV4_BITS + 1];
    char ip[16];
    int prefixLength;

    // Parse the route into IP and prefix length
    if (sscanf(route, "%15[^/]/%d", ip, &prefixLength) != 2) {
        printf("Invalid route format\n");
        return false;
    }

    // Convert the IP and prefix length to binary representation
    if (!ipv4ToBinary(ip, prefixLength, binaryRoute)) {
        printf("Failed to convert IP to binary\n");
        return false;
    }

    RTrieNode *curr = root;

    // Traverse the trie to find the route
    for (int i = 0; i < prefixLength; i++) {
        int bit = binaryRoute[i] - '0';
        if (curr->children[bit] == NULL) {
            printf("Route not found in trie\n");
            return false;
        }
        curr = curr->children[bit];
    }

    if (curr->is_route && curr->nextHop) {
        
        rtrieTraverseAllIps(curr, route, curr->nextHop, binaryRoute, prefixLength, 
                                    rtIpMatchCallback);
        return true;
    }

    return true;
}

bool rtrieTraverseAllIps(RTrieNode *root, const char *route, const char *nh,
    char *binaryPrefix, int prefixLength,
    void (*rtIpMatchCallback)(const char *ip, const char *route, const char *nh)) {

    if (!root || !route || !binaryPrefix || !rtIpMatchCallback) {
        printf("Invalid input parameters\n");
        return false;
    }

    char ipStr[16];

    // If the current node is an IP, call the callback
    if (root->is_ip) {
        binaryToIpv4String(binaryPrefix, ipStr);
        rtIpMatchCallback(ipStr, route, nh);
        return true;
    }

    // Traverse the child nodes
    for (int i = 0; i < 2; i++) {
        if (root->children[i] && !root->children[i]->is_route) {
            binaryPrefix[prefixLength] = '0' + i;
            binaryPrefix[prefixLength + 1] = '\0';

            rtrieTraverseAllIps(root->children[i], route, nh, binaryPrefix, prefixLength + 1, 
                                        rtIpMatchCallback);

            binaryPrefix[prefixLength] = '\0'; // Backtrack
        }
    }

    return true;
}

// Helper function for DFS traversal
void rtrieDfs(RTrieNode *node, int depth, char *route,void (*rt)(const char *route, const char *nh)) {
    if (!node || !rt) {
        return;
    }

    if (depth >= IPV4_BITS) {
        return;
    }

    // If the current node is a route, call the callback
    if (node->is_route && node->nextHop) {
        char routeStr[32];
        binaryToIpv4String(route, routeStr);
        snprintf(routeStr + strlen(routeStr), sizeof(routeStr) - strlen(routeStr), "/%d", depth);
        rt(routeStr, node->nextHop);
    }

    // Traverse child nodes
    for (int i = 0; i < 2; i++) {
        if (node->children[i]) {
            route[depth] = '0' + i;
            route[depth + 1] = '\0';
            rtrieDfs(node->children[i], depth + 1, route, rt);
            route[depth] = '\0'; // Backtrack
        }
    }
}

void rtriePrintRoutes(RTrieNode *root,
    void (*rt)( const char *route,  const char *nh)) {

    if (!root || !rt) {
        return;
    }

    char route[IPV4_BITS + 1] = {0};

    // Start DFS from the root
    rtrieDfs(root, 0, route, rt);
 
}

