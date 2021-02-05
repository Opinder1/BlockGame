#pragma once

#include <blockgame.h>

#include "engine/engine.h"

class Application : public engine::Application {
private:
	ocode::LogFile log;
	ocode::Config config;

	/*
	engine::MSTextureBuffer texture;
	engine::MSSprite sprite;
	engine::FrameBufferM frame;

	engine::TextureBuffer texture;
	engine::Sprite sprite;
	engine::FrameBufferT frame;
	*/

	void update();

public:
	Application();
	~Application();
};

extern Application* application;