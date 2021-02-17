#include "scene.h"

ServerScene::ServerScene(Server* server) : server(server), scene(server) {
	EVENT_SUBSCRIBE(PacketSendEvent, on_packet_send);
}

ServerScene::~ServerScene() {

}

void ServerScene::on_tick() {

}

bool ServerScene::on_packet_send(const PacketSendEvent* e) {
	server->THREAD_EVENT_POST(PacketSendEvent, *e);

	return false;
}