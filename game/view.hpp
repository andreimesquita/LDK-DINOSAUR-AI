static const uint32 WINDOW_WIDTH = 1200;
static const uint32 WINDOW_HEIGHT = 300;
static const float ASPECT_RATIO = 1.0f;

namespace view
{
    const uint32 SPRITESHEET_DINOSAUR_X_COORD = 0;
    const uint32 SPRITESHEET_DINOSAUR_Y_COORD = 0;
	const uint32 SPRITESHEET_DINOSAUR_WIDTH = 32;
	const uint32 SPRITESHEET_DINOSAUR_HEIGHT = 32;

    const uint32 SPRITESHEET_CACTUS_X_COORD = 33;
    const uint32 SPRITESHEET_CACTUS_Y_COORD = 0;
    const uint32 SPRITESHEET_CACTUS_WIDTH = 4;
    const uint32 SPRITESHEET_CACTUS_HEIGHT = 4;

    HMaterial material;
    renderer::Sprite dinosaurSprite;
    renderer::Sprite genericCactusSprite;
    Mat4 projMatrix;
	
	void updateProjMatrix(uint32 width, uint32 height)
	{
		projMatrix.orthographic(0, width, 0, height, -10, 10);
	};
	
	void initialize()
	{
		Vec4 clearColor = Vec4{0.0f, 0.0f, 0.0f, 0.0f};
		renderer::context_initialize(255, clearColor, 0);
		material = loadMaterial("./assets/spritesheet.mat");
		updateProjMatrix(WINDOW_WIDTH, WINDOW_HEIGHT);
		renderer::spriteBatch_initialize(512);
		
		//initialize dinosaur
		renderer::makeSprite(&dinosaurSprite, material,
		                     SPRITESHEET_DINOSAUR_X_COORD, SPRITESHEET_DINOSAUR_Y_COORD,
							 SPRITESHEET_DINOSAUR_WIDTH, SPRITESHEET_DINOSAUR_HEIGHT);

		//TODO(andrei) initialize cactus with different sizes
        renderer::makeSprite(&genericCactusSprite, material,
                             SPRITESHEET_CACTUS_X_COORD, SPRITESHEET_CACTUS_Y_COORD,
                             SPRITESHEET_CACTUS_WIDTH, SPRITESHEET_CACTUS_HEIGHT);
	};

	void dispose()
    {
        renderer::material_destroy(material);
        renderer::context_finalize();
    };

	void drawCactus()
    {
        for(int i = 0; i < CACTUS_LENGTH; i++)
        {
            model::Cactus & cactus = model::gameState->cactusArray[i];
            renderer::spriteBatch_draw(&genericCactusSprite,
                                       cactus.transform.position.x, cactus.transform.position.y,
                                       cactus.transform.size.x, cactus.transform.size.y);
        }
    };

	void drawDinosaur()
    {
        model::Dinosaur & dinosaur = model::gameState->dinosaur;
        renderer::spriteBatch_draw(&dinosaurSprite,
                                   dinosaur.transform.position.x, dinosaur.transform.position.y,
                                   dinosaur.transform.size.x, dinosaur.transform.size.y);
    };

	void draw()
	{
		renderer::clearBuffers(renderer::Context::COLOR_BUFFER | renderer::Context::DEPTH_BUFFER);
		renderer::beginFrame(projMatrix);
		renderer::spriteBatch_begin();
        drawCactus();
        drawDinosaur();
		renderer::spriteBatch_end();
		renderer::endFrame();
	};
};
