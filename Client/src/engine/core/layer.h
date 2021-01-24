#pragma once

#include <vector>

#include "../renderer/framebuffer.h"

namespace engine {
	class Layer {
	private:
		//FrameBuffer frame;

	public:
		virtual ~Layer() {};

		virtual void on_connect() = 0;
		virtual void on_disconnect() = 0;

		virtual void update() = 0;
	};

	class LayerManager {
	private:
		std::vector<Layer*> layers;

	public:
		LayerManager();
		~LayerManager();

		void update();

		void insert(Layer* layer);
		void insert_overlay(Layer* layer);

		void pop(Layer* layer);
	};
}