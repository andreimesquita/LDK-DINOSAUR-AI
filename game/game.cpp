#include <ldk/ldk.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

using namespace ldk;

#include "model.hpp"
#include "view.hpp"

const char WINDOW_TITLE[] = "LDK Dinosaur AI";

LDKGameSettings gameInit()
{
	LDKGameSettings settings;
	settings.displayWidth = WINDOW_WIDTH;
	settings.displayHeight = WINDOW_HEIGHT;
	settings.aspect = ASPECT_RATIO;
	settings.fullScreen = false;
	settings.name = WINDOW_TITLE;
	settings.preallocMemorySize = sizeof(GameState);
	return settings;
};

void gameStart(void* memory)
{
	_gameState = (GameState*)memory;
	view::initialize();
	unsigned int seed = (unsigned int)std::time(0);
	std::srand(seed);
};

void gameUpdate(float deltaTime)
{
	//TODO(andrei)
	view::draw();
};

void gameViewResized(uint32 width, uint32 height)
{
	Rect viewport = {0.0f, 0.0f, (float)width, (float)height};
	renderer::setViewPort(viewport);
	view::updateProjMatrix(width, height);
};

void gameStop()
{
	renderer::material_destroy(_gameState->material);
	renderer::context_finalize();
};