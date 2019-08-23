#ifndef MODEL_H
#define MODEL_H

namespace model
{
    const float SPAWN_CACTUS_X_POSITION = 1200.0f;
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
        Cactus cactus;
        Dinosaur dinosaur;
        float scenerySpeed;
        //input data
        bool isJumping;
        float jumpDeltaSum;
    } *gameState;

    void respawnCactus(Cactus & cactus)
    {
        cactus.transform.position = Vec2{SPAWN_CACTUS_X_POSITION,GROUND_Y_POSITION};
    }

    void initialize()
    {
        //initialize dinosaur
        Dinosaur & dinosaur = gameState->dinosaur;
        dinosaur.transform.position = Vec2{30.0f,GROUND_Y_POSITION};
        dinosaur.transform.size = Vec2{32.0f,42.0f};

        //initialize cactus
        gameState->cactus = Cactus();
        gameState->cactus.transform.size = Vec2{30.0f,15.0f};
        respawnCactus(gameState->cactus);

        gameState->scenerySpeed = 300.0f;
        gameState->isJumping = false;
    };

    void readInput()
    {
        if (!gameState->isJumping && input::isKeyDown(input::LDK_KEY_UP))
        {
            gameState->isJumping = true;
        }
    };

    void processDinosaur(Dinosaur& dinosaur, float deltaTime)
    {
        if (gameState->isJumping)
        {
            jumpDeltaSum += deltaTime;
            //TODO(andrei) predict current position
        }

        dinosaur.transform.position.y = MAX(dinosaur.transform.position.y, );
        if (dinosaur.transform.position.y == GROUND_Y_POSITION)
        {
            gameState->isJumping = false;
        }
    };

    void update(float deltaTime)
    {
        readInput();
        processDinosaur(gameState->dinosaur, deltaTime);

        Transform & cactusTransform = gameState->cactus.transform;
        float movementStep = (deltaTime * gameState->scenerySpeed);
        cactusTransform.position.x -= movementStep;

        if ((cactusTransform.position.x + cactusTransform.size.x) <= OFF_SCREEN_OFFSET)
        {
            respawn(cactusTransform);
        }
    };
};
#endif
