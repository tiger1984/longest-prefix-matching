#include "RouteCommon.h"
#include "RouteLookup.h"


RouteDb *db = NULL;

void routeIpMatchCallbackFn(const char *ip, const char *route,  const char *nh){
    printf("Route IP match Callback IP: %s, Route: %s, Next Hop: %s\n", ip, route, nh);
    return;


}

void TC1() {
    printf("=========================\n");

    printf("TC1: Route Add Ip Add\n");

    printf("TC1: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);
    // Test case logic here
    printf("TC1: Add Route 10.0.0.0/8 \n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");
    printf("TC1: Add Route 10.1.0.0/16 \n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");
    printf("TC1: Add Route 10.1.1.0/24 \n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC1: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC1: Uninitialize Route DB");
    uninitializeRouteDb(&db);
    printf("TC1 ended\n\n\n");
    printf("=========================\n");
}


void TC2() {
    printf("=========================\n");
    printf("TC2: IP Add Route Add\n");
    printf("TC2: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC2: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC2: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC2: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC2: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC2: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);

    printf("TC2 ended\n\n\n");
    printf("=========================\n");
}

void TC3() {
    printf("=========================\n");
    printf("TC3: Route Delete\n");
    printf("TC3: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC3: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC3: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC3: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC3: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC3: Delete Route 10.1.0.0/16\n");
    routeDelete(db, "10.1.0.0/16");

    printf("TC3: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC3 ended\n\n\n");
    printf("=========================\n");
}

void TC4() {
    printf("=========================\n");
    printf("TC4: Route Delete Route Add \n");
    printf("TC4: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC4: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC4: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC4: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC4: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC4: Delete Route 10.1.0.0/16\n");
    routeDelete(db, "10.1.0.0/16");

    printf("TC4: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC4: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC4 ended\n\n\n");
    printf("=========================\n");
}
void TC5() {
    printf("=========================\n");
    printf("TC5: Route IP Match Callback - Overlapping Routes\n");
    printf("TC5: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC5: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC5: Add Route 10.0.0.0/16\n");
    routeAdd(db, "10.0.0.0/16", "111.16.5.16");

    printf("TC5: Add Route 10.0.0.0/24\n");
    routeAdd(db, "10.0.0.0/24", "111.24.5.24");

    printf("TC5: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC5: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC5 ended\n\n\n");
    printf("=========================\n");
}

void TC6() {
    printf("=========================\n");
    printf("TC6: Route IP Match Callback - No Matching Route\n");
    printf("TC6: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC6: Add Route 192.168.0.0/16\n");
    routeAdd(db, "192.168.0.0/16", "192.168.1.1");

    printf("TC6: Add Route 172.16.0.0/12\n");
    routeAdd(db, "172.16.0.0/12", "172.16.1.1");

    printf("TC6: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC6: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC6 ended\n\n\n");
    printf("=========================\n");
}

void TC7() {
    printf("=========================\n");
    printf("TC7: Route IP Match Callback - Multiple Deletes\n");
    printf("TC7: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC7: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC7: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC7: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC7: Delete Route 10.1.1.0/24\n");
    routeDelete(db, "10.1.1.0/24");

    printf("TC7: Delete Route 10.1.0.0/16\n");
    routeDelete(db, "10.1.0.0/16");

    printf("TC7: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC7: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC7 ended\n\n\n");
    printf("=========================\n");
}

void TC8() {
    printf("=========================\n");
    printf("TC8: Route IP Match Callback - Repeated Adds\n");
    printf("TC8: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC8: Add Route 10.0.0.0/8 (First Add)\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC8: Add Route 10.0.0.0/8 (Second Add)\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC8: Add Route 10.0.0.0/8 (Third Add)\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC8: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC8: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);

    printf("TC8 ended\n\n\n");
    printf("=========================\n");
}

void TC9() {
    printf("=========================\n");
    printf("TC9: Route Add and Immediate Delete\n");
    printf("TC9: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC9: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC9: Delete Route 10.0.0.0/8\n");
    routeDelete(db, "10.0.0.0/8");

    printf("TC9: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC9: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC9 ended\n\n\n");
    printf("=========================\n");
}

void TC10() {
    printf("=========================\n");
    printf("TC10: Register IP Without Routes\n");
    printf("TC10: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC10: Register IP Address 192.168.1.1\n");
    registerIpAddress(db, "192.168.1.1");

    printf("TC10: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC10 ended\n\n\n");
    printf("=========================\n");
}

void TC11() {
    printf("=========================\n");
    printf("TC11: Add Routes with Different Prefix Lengths\n");
    printf("TC11: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC11: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC11: Add Route 10.0.0.0/12\n");
    routeAdd(db, "10.0.0.0/12", "111.12.5.12");

    printf("TC11: Add Route 10.0.0.0/24\n");
    routeAdd(db, "10.0.0.0/24", "111.24.5.24");

    printf("TC11: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC11: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC11 ended\n\n\n");
    printf("=========================\n");
}

void TC12() {
    printf("=========================\n");
    printf("TC12: Add and Delete Multiple Routes\n");
    printf("TC12: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC12: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC12: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC12: Delete Route 10.0.0.0/8\n");
    routeDelete(db, "10.0.0.0/8");

    printf("TC12: Delete Route 10.1.0.0/16\n");
    routeDelete(db, "10.1.0.0/16");

    printf("TC12: Register IP Address 10.1.5.9\n");
    registerIpAddress(db, "10.1.5.9");

    printf("TC12: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC12 ended\n\n\n");
    printf("=========================\n");
}

void TC13() {
    printf("=========================\n");
    printf("TC13: Add Routes and Delete Routes with Different Prefix Lengths\n");
    printf("TC13: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC13: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC13: Add Route 10.0.0.0/12\n");
    routeAdd(db, "10.0.0.0/12", "111.12.5.12");

    printf("TC13: Add Route 10.0.0.0/24\n");
    routeAdd(db, "10.0.0.0/24", "111.24.5.24");

    printf("TC13: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC13: Delete Route 10.0.0.0/12\n");
    routeDelete(db, "10.0.0.0/12");

    printf("TC13: Delete Route 10.0.0.0/24\n");
    routeDelete(db, "10.0.0.0/24");

    printf("TC13: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC13 ended\n\n\n");
    printf("=========================\n");
}

void TC14() {
    printf("=========================\n");
    printf("TC14: Unregister IP Address\n");
    printf("TC14: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC14: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC14: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC14: Unregister IP Address 10.0.0.1\n");
    unregisterIpAddress(db, "10.0.0.1");

    printf("TC14: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC14 ended\n\n\n");
    printf("=========================\n");
}

void TC15() {
    printf("=========================\n");
    printf("TC15: Unregister Non-Existent IP Address\n");
    printf("TC15: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC15: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC15: Unregister IP Address 10.0.0.1 (Not Registered)\n");
    unregisterIpAddress(db, "10.0.0.1");

    printf("TC15: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC15 ended\n\n\n");
    printf("=========================\n");
}

void TC16() {
    printf("=========================\n");
    printf("TC16: Register and Unregister Multiple IP Addresses\n");
    printf("TC16: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC16: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC16: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC16: Register IP Address 10.0.0.2\n");
    registerIpAddress(db, "10.0.0.2");

    printf("TC16: Unregister IP Address 10.0.0.1\n");
    unregisterIpAddress(db, "10.0.0.1");

    printf("TC16: Unregister IP Address 10.0.0.2\n");
    unregisterIpAddress(db, "10.0.0.2");

    printf("TC16: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC16 ended\n\n\n");
    printf("=========================\n");
}

void TC17() {
    printf("=========================\n");
    printf("TC17: Print Route Table\n");
    printf("TC17: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC17: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC17: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC17: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("\n\n\n");
    printf("TC17: Print Route Table\n");
    printAllRoutes(db);

    printf("TC17: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC17 ended\n\n\n");
    printf("=========================\n");
}

void TC18() {
    printf("=========================\n");
    printf("TC18: Add Many IPs That Are Matching\n");
    printf("TC18: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC18: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC18: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC18: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC18: Register Multiple IP Addresses\n");
    printf("TC18: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC18: Register IP Address 10.1.0.1\n");
    registerIpAddress(db, "10.1.0.1");

    printf("TC18: Register IP Address 10.1.1.1\n");
    registerIpAddress(db, "10.1.1.1");

    printf("TC18: Register IP Address 10.1.1.2\n");
    registerIpAddress(db, "10.1.1.2");

    printf("TC18: Register IP Address 10.1.1.3\n");
    registerIpAddress(db, "10.1.1.3");
    printf("TC18: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC18 ended\n\n\n");
    printf("=========================\n");
}

void TC19() {
    printf("=========================\n");
    printf("TC19: Add Many IPs That Are Matching and Verify\n");
    printf("TC19: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC19: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC19: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC19: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC19: Register Multiple IP Addresses\n");
    printf("TC19: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC19: Register IP Address 10.1.0.1\n");
    registerIpAddress(db, "10.1.0.1");

    printf("TC19: Register IP Address 10.1.1.1\n");
    registerIpAddress(db, "10.1.1.1");

    printf("TC19: Register IP Address 10.1.1.2\n");
    registerIpAddress(db, "10.1.1.2");

    printf("TC19: Register IP Address 10.1.1.3\n");
    registerIpAddress(db, "10.1.1.3");

    printf("\n\n");
    printf("TC19: Print Route Table for 10.0.0.0/8\n");
    printRoute(db, "10.0.0.0/8");

    printf("\n\n");
    printf("TC19: Print Route Table for 10.1.0.0/16\n");
    printRoute(db, "10.1.0.0/16");

    printf("\n\n");
    printf("TC19: Print Route Table for 10.1.1.0/24\n");
    printRoute(db, "10.1.1.0/24");
    printf("\n\n");
    printf("TC19: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC19 ended\n\n\n");
    printf("=========================\n");
}

void TC20() {
    printf("=========================\n");
    printf("TC20: Add Many IPs That Are Matching and Verify\n");
    printf("TC20: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC20: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC20: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC20: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC20: Register Multiple IP Addresses\n");
    printf("TC20: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC20: Register IP Address 10.1.0.1\n");
    registerIpAddress(db, "10.1.0.1");

    printf("TC20: Register IP Address 10.1.1.1\n");
    registerIpAddress(db, "10.1.1.1");

    printf("TC20: Register IP Address 10.1.1.2\n");
    registerIpAddress(db, "10.1.1.2");

    printf("TC20: Register IP Address 10.1.1.3\n");
    registerIpAddress(db, "10.1.1.3");

    printf("\n\n");
    printf("TC20: Print All Routes \n");
    printAllRoutes(db);
    printf("\n\n");
    printf("TC20: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC20 ended\n\n\n");
    printf("=========================\n");
}

void TC21() {
    printf("=========================\n");
    printf("TC21: Add Many IPs That Are Matching and Verify Routes\n");
    printf("TC21: Initialize Route DB\n");
    initializeRouteDb(&db, routeIpMatchCallbackFn);

    printf("TC21: Add Route 10.0.0.0/8\n");
    routeAdd(db, "10.0.0.0/8", "111.8.5.8");

    printf("TC21: Add Route 10.1.0.0/16\n");
    routeAdd(db, "10.1.0.0/16", "111.16.5.16");

    printf("TC21: Add Route 10.1.1.0/24\n");
    routeAdd(db, "10.1.1.0/24", "111.24.5.24");

    printf("TC21: Register Multiple IP Addresses\n");
    printf("TC21: Register IP Address 10.0.0.1\n");
    registerIpAddress(db, "10.0.0.1");

    printf("TC21: Register IP Address 10.1.0.1\n");
    registerIpAddress(db, "10.1.0.1");

    printf("TC21: Register IP Address 10.1.1.1\n");
    registerIpAddress(db, "10.1.1.1");

    printf("TC21: Register IP Address 10.1.1.2\n");
    registerIpAddress(db, "10.1.1.2");

    printf("TC21: Register IP Address 10.1.1.3\n");
    registerIpAddress(db, "10.1.1.3");

    printf("TC21: Register IP Address 11.1.1.3\n");
    registerIpAddress(db, "11.1.1.3");

    printf("\n\n");
    printf("TC21: Print Route for 10.0.0.1\n");
    printRouteForIp(db, "10.0.0.1");

    printf("TC21: Print Route for 10.1.0.1\n");
    printRouteForIp(db, "10.1.0.1");

    printf("TC21: Print Route for 10.1.1.1\n");
    printRouteForIp(db, "10.1.1.1");

    printf("TC21: Print Route for 10.1.1.2\n");
    printRouteForIp(db, "10.1.1.2");

    printf("TC21: Print Route for 10.1.1.3\n");
    printRouteForIp(db, "10.1.1.3");

    printf("TC21: Print Route for 11.1.1.3\n");
    printRouteForIp(db, "11.1.1.3");

    printf("\n\n");
    printf("TC21: Uninitialize Route DB\n");
    uninitializeRouteDb(&db);
    printf("TC21 ended\n\n\n");
    printf("=========================\n");
}


void RUN_ALL_TEST() {
    printf("Running all test cases...\n\n\n");
    TC1();
    TC2();
    TC3();
    TC4();
    TC5();
    TC6();
    TC7();
    TC8();
    TC9();
    TC10();
    TC11();
    TC12();
    TC13();
    TC14();
    TC15();
    TC16();
    TC17();
    TC18();
    TC19();
    TC20();
    TC21();

    printf("All test cases completed.\n");
}
int main() {
 
    RUN_ALL_TEST();

    return 0;
}