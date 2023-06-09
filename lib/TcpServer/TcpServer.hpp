#pragma once

#include <String.h>
#include <AsyncTCP.h>
#include "LoggerFactory.hpp"
#include "AbstractTcpCommandProcessor.hpp"

class TcpServer {
private:
    AbstractTcpCommandProcessor& _tcpCommandProcessor;
    LoggerFactory& _logger;
    AsyncServer* _server = NULL;
    AsyncClient* _client = NULL;

    void onClientConnect(AsyncClient* newClient) {
        if (_client) {
            newClient->write("Only one connection is allowed at a time\r\n");
            newClient->close();
            return;
        }

        _client = newClient;
        _logger.logInfo("TCP Client has been connected");

        newClient->onDisconnect([this](void* data, AsyncClient* c) {
            _logger.logInfo("TCP Client has been disconnected");
            _client = NULL;
        });

        newClient->onData([this](void*, AsyncClient* c, void* data, size_t len) {
            String command = String((char*)data).substring(0, len - 2); // trim \r\n
            String reply = _tcpCommandProcessor.getReply(command);
            c->write(reply.c_str());
        }, NULL);
    }

public:
    TcpServer(AbstractTcpCommandProcessor& tcpCommandProcessor, LoggerFactory& logger)
        : _tcpCommandProcessor(tcpCommandProcessor), _logger(logger) {}

    void bebin(uint16_t port) {
        _server = new AsyncServer(port);
        
        _server->onClient([](void* arg, AsyncClient* newClient) {
            TcpServer* server = reinterpret_cast<TcpServer*>(arg);
            server->onClientConnect(newClient);
        }, this);
        
        _server->begin();
        _logger.logInfo("TCP Server has been started");
    }

    bool sendMessageToClient(String message) {
        if (!_client)
            return false;

        _client->write(message.c_str());
        return true;
    }

    void end() {
        _server->end();
        _logger.logInfo("TCP Server has been ended");
    }

    void stopClient() {
        if (!_client)
            return;
        
        _client->stop();
        _client = NULL;
        _logger.logInfo("TCP Client has been stopped");
    }
};