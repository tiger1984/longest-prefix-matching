#ifndef ROUTE_LOOKUP_H
#define ROUTE_LOOKUP_H

#include "RouteCommon.h"
#include "RouteTrie.h"


typedef struct RouteDb {
    RTrieNode *root;
    void (*rtIpMatchCallback)(const char *ip, const char *route,  const char *nh);
    int numRoutes;
} RouteDb;

bool initializeRouteDb(RouteDb **routeDb,
                    void (*routeIpMatchCallback)(const char *ip, const char *route,  const char *nh));
bool uninitializeRouteDb(RouteDb **routeDb);

bool routeAdd(RouteDb *routeDb, const char *route, const char *nextHop);
bool routeDelete(RouteDb *routeDb, const char *route);

bool registerIpAddress(RouteDb *routeDb, const char *ip);
bool unregisterIpAddress(RouteDb *routeDb, const char *ip);

void printIpCallBack(const char *ip, const char *route,  const char *nh);
void printRoute(RouteDb *routeDb, const char *route);


void printRtCallBack(const char *route,  const char *nh) ;
void printAllRoutes(RouteDb *routeDb);

void printRouteForIp(RouteDb *routeDb, const char *ip);

#endif // ROUTE_LOOKUP_H