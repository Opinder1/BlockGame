#include "layer.h"

LayerManager::LayerManager() {

}

LayerManager::~LayerManager() {
	for (auto layer : layers) {
		delete layer;
	}
}

void LayerManager::tick(Window& window) {
	for (auto layer : layers) {
		layer->tick(window);
	}
}

void LayerManager::insert(Layer* layer) {
	layers.push_back(layer);
	layer->on_connect();
}

void LayerManager::insert_overlay(Layer* layer) {
	layers.emplace(layers.begin(), layer);
	layer->on_connect();
}

void LayerManager::pop(Layer* layer) {
	auto it = std::find(layers.begin(), layers.end(), layer);
	if (it != layers.end()) {
		layers.erase(it);
	}
	layer->on_disconnect();
}