APIs

1. bool initializeRouteDb(RouteDb **routeDb,
void (*routeIpMatchCallback)(const char *ip, const char *route, const char *nh));

This function allocates and initializes a RouteDb structure. It also sets the callback function that will be invoked when an IP address matches a route.

2. bool uninitializeRouteDb(RouteDb **routeDb);

This function frees the memory allocated for the RouteDb structure and it  associated Trie.

3. bool routeAdd(RouteDb *routeDb, const char *route, const char *nextHop);

Adds a route to the routing database

4. bool routeDelete(RouteDb *routeDb, const char *route);

Deletes a route from the routing database.

5.  bool registerIpAddress(RouteDb *routeDb, const char *ip);

Registers an IP address in the routing database

6. bool unregisterIpAddress(RouteDb *routeDb, const char *ip);

Unregisters an IP address from the routing database

8. void printRoute(RouteDb *routeDb, const char *route);

Prints all IPs that are registered and matches the route

9. void printAllRoutes(RouteDb *routeDb);

Prints all routes in the routing database.

10. void printRouteForIp(RouteDb *routeDb, const char *ip);

Prints the route that matches the input IP.



Files

1. RouteLookupMain.c

Contains the main function and UT functions. Invokes


2. RouteLookup.c

Contains all APIs mentioned above


3. RouteTrie.c

Route DB uses trie in this file to store routes and IPs, and also matching IP to routes.


4. RouteCommon.c

Common utilities are in this file.


Data Structure and Algorithms used.
1. Trie is used to store both routes and IPs. Routes and IPs are stored in bit string format.
2. DFS is used for 
      a. insert and delete routes and IPs. 
      b. match IP to longest prefix match routes .
      c. print the table


Compiler
gcc was used in macbook to run tests.
