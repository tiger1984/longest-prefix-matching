#ifndef ROUTE_TRIE_H
#define ROUTE_TRIE_H
#include "RouteCommon.h"


typedef struct RTrieNode {
    struct RTrieNode *children[2];  // 0 and 1 for bits
    char *nextHop;  
    bool is_route;                 // Marks if node represents a route prefix
    bool is_ip;                    // Marks if node represents a full IP
} RTrieNode;

bool rtrieInit(RTrieNode **root);
bool rtrieUnInit(RTrieNode **root);

bool rtrieNodeCreate(RTrieNode **node);
bool rtrieNodeDestroy(RTrieNode **node);

bool rtrieFreeFullTrie(RTrieNode **root);

// Function to insert a route or IP into the Trie
bool rtrieInsertRoute(RTrieNode *root, const char *route, const char *nextHop);

// Function to delete a route or IP from the Trie
bool rtrieDeleteRoute(RTrieNode *root, const char *route,
    void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh));

bool rtrieInsertIp(RTrieNode *root, const char *ip);

bool rtrieDeleteIp(RTrieNode *root, const char *ip);


// Function to search for a  IP in the Trie
bool rtrieSearchIp(RTrieNode *root, const char *ip,
    void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh));

    // Function to search for a route in the Trie
bool rtrieSearchRoute(RTrieNode *root, const char *route,
    void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh));

bool rtrieTraverseAllIps(RTrieNode *root, const char *route, const char *nh,
        char *binaryPrefix, int prefixLength,
        void (*rtIpMatchCallback)(const char *ip, const char *route, const char *nh)) ;


void rtrieDfs(RTrieNode *node, int depth, char *route,void (*rt)(const char *route, const char *nh));


void rtriePrintRoutes(RTrieNode *root,
        void (*rt)( const char *route,  const char *nh));


#endif // ROUTE_TRIE_H