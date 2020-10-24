#pragma once

#include "window.h"
#include "blockgame.h"

class Layer {
	friend class LayerManager;

public:
	Layer() {}
	virtual ~Layer() = 0;

	virtual void on_connect() = 0;
	virtual void on_disconnect() = 0;

	virtual void tick(Window& window) = 0;
};

class LayerManager {
private:
	std::vector<Layer*> layers;

public:
	LayerManager();
	~LayerManager();

	void tick(Window& window);

	void insert(Layer* layer);
	void insert_overlay(Layer* layer);

	void pop(Layer* layer);
};