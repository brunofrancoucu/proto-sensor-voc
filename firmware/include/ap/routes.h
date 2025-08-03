#ifndef ROUTES_H
#define ROUTES_H

#include <Arduino.h>
#include <WebServer.h>

// Function prototypes (server not global)
void handleRoot(WebServer &server);
void handleData(WebServer &server);
void handleConnect(WebServer &server);

#endif