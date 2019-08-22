static const uint32 CACTUS_LENGTH = 8;

namespace model
{
    const float SPAWN_CACTUS_X_POSITION = 1200;
    const float GROUND_Y_POSITION = 100.0f;
    const float OFF_SCREEN_OFFSET = -10.0f;

    struct Transform
    {
        Vec2 position;
        Vec2 size;
    };

    struct Dinosaur
    {
        Transform transform;
    };

    struct Cactus
    {
        Transform transform;

        Cactus() {}
    };

    static struct GameState
    {
        Cactus cactusArray[CACTUS_LENGTH];
        Dinosaur dinosaur;
        float scenerySpeed = 30.0f;
    } *gameState;

    void respawn(Transform & transform)
    {
        transform.position.x = SPAWN_CACTUS_X_POSITION;
        transform.position.y = GROUND_Y_POSITION;
    }

    void initialize()
    {
        //initialize dinosaur
        Dinosaur & dinosaur = gameState->dinosaur;
        dinosaur.transform.position = Vec2{30.0f,GROUND_Y_POSITION};
        dinosaur.transform.size = Vec2{32.0f,42.0f};

        //initialize cactus
        for(int i = 0; i < CACTUS_LENGTH; i++)
        {
            Cactus & cactus = gameState->cactusArray[i];
            cactus = Cactus();
            cactus.transform.size = Vec2{30.0f,15.0f};
            respawn(cactus.transform);
        }
    };

    void update(float& deltaTime)
    {
        Cactus & cactus = gameState->cactusArray[0];
        cactus.transform.position.x -= (deltaTime * gameState->scenerySpeed);

        bool mustRespawn = (cactus.transform.position.x + cactus.transform.size.x) <= OFF_SCREEN_OFFSET;
        if (mustRespawn)
        {
            respawn(cactus.transform);
        }
    };
};
