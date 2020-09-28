#include "client.h"

Client::Client(std::string ip, uint16 port) : NetClient(ip, port), log("client") {
    if (!initialised()) {
        log.println("An error occurred while initializing client");

        WorkerThread::stop_running();
    }
}

Client::~Client() {
    
}

bool Client::initialised() {
	return NetClient::initialised() and log.initialised();
}

bool Client::is_running() {
	return running;
}

void Client::on_tick() {
    NetClient::poll_netevent();
}

void Client::disconnect() {

}

void Client::packet_recive(Packet packet) {

}

void Client::connect(uint8 connect_attempts, uint16 connect_timeout) {
    bool connected = false;

    for (uint8 i = 0; i < connect_attempts; i++) {
        log.println("Attempting to connect");
        NetClient::attempt_connect(connect_timeout);

        if (NetClient::is_connected()) {
            return;
        }
    }

    if (!connected) {
        log.println("Could not connect to server");

        WorkerThread::stop_running();
    }

    //Packet packet("A");
    //NetClient::packet_send(packet);
}