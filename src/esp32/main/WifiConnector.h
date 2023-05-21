#ifndef WIFICONNECTOR_H
#define WIFICONNECTOR_H

class WifiConnector
{
public:
    static bool IsConnected();
    static void EnsureConnection();
    static void Connect();
};

#endif
