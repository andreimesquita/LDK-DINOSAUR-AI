static const uint32 WINDOW_WIDTH = 1200;
static const uint32 WINDOW_HEIGHT = 300;
static const float ASPECT_RATIO = 1.0f;

namespace view
{
	const uint32 SPRITESHEET_DINOSAUR_WIDTH = 32;
	const uint32 SPRITESHEET_DINOSAUR_HEIGHT = 32;
	const uint32 SCREEN_DINOSAUR_WIDTH = 32;
	const uint32 SCREEN_DINOSAUR_HEIGHT = 48;
	
	void updateProjMatrix(uint32 width, uint32 height)
	{
		_gameState->projMatrix.orthographic(0, width, 0, height, -10, 10);
	};
	
	void initialize()
	{
		Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
		renderer::context_initialize(255, clearColor, 0);
		_gameState->material = loadMaterial("./assets/spritesheet.mat");
		updateProjMatrix(WINDOW_WIDTH, WINDOW_HEIGHT);
		renderer::spriteBatch_initialize(8);
		
		//initialize dinossaur
		renderer::makeSprite(&_gameState->dinosaur,
							 _gameState->material,
							 0, 0,
							 SPRITESHEET_DINOSAUR_WIDTH, SPRITESHEET_DINOSAUR_HEIGHT);
	};
	
	void draw()
	{
		renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
		renderer::beginFrame(_gameState->projMatrix);
		renderer::spriteBatch_begin();
		
		renderer::spriteBatch_draw(&(_gameState->dinosaur),
								   0, 0,
								   SCREEN_DINOSAUR_WIDTH, SCREEN_DINOSAUR_HEIGHT);

		renderer::spriteBatch_end();
		renderer::endFrame();
	};
};
