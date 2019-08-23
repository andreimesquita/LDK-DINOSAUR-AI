#include <ldk/ldk.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace ldk;

#include "model.hpp"
#include "view.hpp"
#include "neuralnetwork.hpp"

const char WINDOW_TITLE[] = "LDK Dinosaur AI";

LDKGameSettings gameInit()
{
	LDKGameSettings settings;
	settings.displayWidth = WINDOW_WIDTH;
	settings.displayHeight = WINDOW_HEIGHT;
	settings.aspect = ASPECT_RATIO;
	settings.fullScreen = false;
	settings.name = WINDOW_TITLE;
	settings.preallocMemorySize = sizeof(model::GameState);
	return settings;
};

void gameStart(void* memory)
{
    model::gameState = (model::GameState*)memory;
    model::initialize();
	view::initialize();
	unsigned int seed = (unsigned int)std::time(0);
	std::srand(seed);
};

void gameUpdate(float deltaTime)
{
    //TODO(andrei) propagate neural network
	model::update(deltaTime);
	view::draw();
    //TODO(andrei) check if all individuals are dead
    //TODO(andrei)     IF SO, find best individual and changes some weights
};

void gameViewResized(uint32 width, uint32 height)
{
	Rect viewport = {0.0f, 0.0f, (float)width, (float)height};
	renderer::setViewPort(viewport);
	view::updateProjMatrix(width, height);
};

void gameStop()
{
    view::dispose();
};
