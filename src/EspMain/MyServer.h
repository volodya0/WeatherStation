#ifndef MYSERVER_H
#define MYSERVER_H

#include <WebServer.h>

class MyServer
{
public:
    static void InitEndpoints();
    static void CheckAndHandleRequests();

private:
    static WebServer server;
    static void handleRoot();
    static void handleGetCurrentData();
    static void handleGetAllRecords();
};

#endif // SERVER_H
