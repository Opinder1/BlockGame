#include "scene.h"

ServerScene::ServerScene(Server& server) : server(server) {
	EVENT_SUBSCRIBE(PacketSendEvent, on_packet_send);
}

ServerScene::~ServerScene() {

}

void ServerScene::on_tick() {

}

bool ServerScene::on_packet_send(const PacketSendEvent* e) {
	server.post_thread_event(EVENT_COPY(PacketSendEvent, e));

	return false;
}