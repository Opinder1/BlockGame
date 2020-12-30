#include "layer.h"

namespace engine {
	LayerManager::LayerManager() {

	}

	LayerManager::~LayerManager() {
		for (auto layer : layers) {
			layer->on_disconnect();
			delete layer;
		}
	}

	void LayerManager::update() {
		for (auto layer : layers) {
			layer->update();
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
}