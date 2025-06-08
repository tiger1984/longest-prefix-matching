#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RouteLookup.h"


void printIpCallBack(const char *ip, const char *route,  const char *nh) {
    printf("IP: %s, Route: %s, Next Hop: %s\n", ip, route, nh);
    return;
}

void printRtCallBack(const char *route,  const char *nh) {
    printf("Route: %s, Next Hop: %s\n", route, nh);
    return;

}


// Initialize the RouteDb
bool initializeRouteDb(RouteDb **routeDb, 
                            void (*routeIpMatchCallback)(const char *ip, const char *route,  const char *nh)) {
    if (routeDb == NULL) {
        return false;
    }
    *routeDb = (RouteDb *)malloc(sizeof(RouteDb));
    if (*routeDb == NULL) {
        return false;
    }
    rtrieInit(&((*routeDb)->root));

    (*routeDb)->rtIpMatchCallback = routeIpMatchCallback;
    (*routeDb)->numRoutes = 0;

    return true;
}

bool uninitializeRouteDb(RouteDb **routeDb) {
    if (routeDb == NULL || *routeDb == NULL) {
        return  false;
    }

    // Free the Trie
    rtrieUnInit(&((*routeDb)->root));

    // Free the RouteDb structure
    free(*routeDb);
    *routeDb = NULL;
    printf("RouteDb uninitialized successfully\n");

    return true;
}

bool routeAdd(RouteDb *routeDb, const char *route, const char *nextHop) {

    if (routeDb == NULL || route == NULL || nextHop == NULL) {
        return false;
    }

    // Insert the route into the Trie
    if (!rtrieInsertRoute(routeDb->root, route, nextHop)) {
        printf("Failed to add route: %s\n", route);
        return false;
    }

    // Increment the route count
    routeDb->numRoutes++;
    //printf("Route added successfully: %s NextHop: %s\n", route, nextHop);
    // Function to search for a route in the Trie
    // bool rtrieSearchRoute(RTrieNode *root, const char *route,
    //     void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh));
    // Search for the route in the Trie
    if (!rtrieSearchRoute(routeDb->root, route, routeDb->rtIpMatchCallback)) {
        printf("Failed to find route: %s\n", route);
        return false;
    }    
    return true;

}

bool routeDelete(RouteDb *routeDb, const char *route) {
    if (routeDb == NULL || route == NULL) {
        return false;
    }

    // Delete the route from the Trie
    if (!rtrieDeleteRoute(routeDb->root, route, routeDb->rtIpMatchCallback)) {
        printf("Failed to delete route: %s\n", route);
        return false;
    }

    // Decrement the route count
    if (routeDb->numRoutes > 0) {
        routeDb->numRoutes--;
    }
    //printf("Route deleted successfully: %s\n", route);
    return true;
}



// New functions to register and unregister IP addresses
bool registerIpAddress(RouteDb *routeDb, const char *ip) {
    if (routeDb == NULL || ip == NULL) {
        return false;
    }
 
    // Register the IP address in the Trie
    if (!rtrieInsertIp(routeDb->root, ip)) {
        printf("Failed to register IP address: %s\n", ip);
        return false;
    }

    printf("Successfully registered IP address: %s\n", ip);

    // bool rtrieSearchIp(RTrieNode *root, const char *ip,
    //     void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh));
    // Search for the IP address in the Trie
    if (!rtrieSearchIp(routeDb->root, ip, routeDb->rtIpMatchCallback)) {
        printf("Failed to match Ip: %s to exiting Route\n", ip);
        return false;
    }    
    return true; 
}

bool unregisterIpAddress(RouteDb *routeDb, const char *ip) {
    if (routeDb == NULL || ip == NULL) {
        return false;
    }
    if (false == rtrieDeleteIp(routeDb->root, ip)) {
        printf("Failed to unregister IP address: %s\n", ip);
    } else {
        printf("Successfully unregistered IP address: %s\n", ip);
    }
    return true;
}

void printRoute(RouteDb *routeDb, const char *route) {
    if (routeDb == NULL || route == NULL) {
        printf("Invalid input to printRoute\n");
        return;
    }

    printf("Route: %s\n", route);
    // Search for the route in the Trie
    if (!rtrieSearchRoute(routeDb->root, route, printIpCallBack)) {
        printf("Route not found: %s\n", route);
    }
}


void printAllRoutes(RouteDb *routeDb) {
    if (routeDb == NULL) {
        printf("Invalid RouteDb\n");
        return;
    }

    // Print all routes in the Trie
    rtriePrintRoutes(routeDb->root, printRtCallBack);

}

void printRouteForIp(RouteDb *routeDb, const char *ip) {

    if (!rtrieSearchIp(routeDb->root, ip, printIpCallBack)) {
        printf("Failed to match Ip: %s to exiting Route\n", ip);
        return ;
    } 
}
