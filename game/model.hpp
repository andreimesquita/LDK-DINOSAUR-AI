#ifndef MODEL_H
#define MODEL_H

namespace model
{
    const float SPAWN_CACTUS_X_POSITION = 1200.0f;
    const float GROUND_Y_POSITION = 0.0f;
    const float OFF_SCREEN_OFFSET = -10.0f;
    const uint32 MAX_SCENERY_LEVEL = 8;

    struct Transform
    {
        Vec2 position;
        Vec2 size;
    };

    bool hasCollided(Transform& aTransform, Transform& bTransform)
    {
        //AABB check
        return aTransform.position.x < (bTransform.position.x + bTransform.size.x)
               && (aTransform.position.x + aTransform.size.x) > bTransform.position.x
               && aTransform.position.y < (bTransform.position.y + bTransform.size.y)
               && (aTransform.position.y + aTransform.size.y) > bTransform.position.y;
    }

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
    private:
        float _sceneryLevelDeltaSum;
        uint32 _sceneryLevel;

    public:
        float speedBySceneryLevel[MAX_SCENERY_LEVEL];
        Cactus cactus;
        Dinosaur dinosaur;
        bool isJumping;
        float jumpImpulseForce;
        float gravityForce;

        void initialize()
        {
            const float firstScenerySpeed = 550.0f;
            const float lastScenerySpeed = 1500.0f;

            for(int i = 0; i < MAX_SCENERY_LEVEL; i++)
            {
                float increment = (lastScenerySpeed - firstScenerySpeed);
                float percentage = (i / (float) MAX_SCENERY_LEVEL);
                speedBySceneryLevel[i] = firstScenerySpeed + increment * percentage;
            }

            reset();
        }

        void reset()
        {
            _sceneryLevel = 0;
            _sceneryLevelDeltaSum = 0.0f;
            jumpImpulseForce = 0.0f;
            gravityForce = 0.0f;
        }

        void applyJumpImpulseForce()
        {
            jumpImpulseForce = 1500.0f;
            gravityForce = jumpImpulseForce * -3.2f;
        }

        float getScenerySpeed()
        {
            return speedBySceneryLevel[_sceneryLevel];
        }

        void tryChangeSceneryLevel(float deltaTime)
        {
            if(_sceneryLevel == (MAX_SCENERY_LEVEL - 1))
            {
                return;
            }
            _sceneryLevelDeltaSum += deltaTime;
            const float maxSceneryDeltaSeconds = 30.0f;
            if (_sceneryLevelDeltaSum >= maxSceneryDeltaSeconds)
            {
                _sceneryLevelDeltaSum -= maxSceneryDeltaSeconds;
                _sceneryLevel += 1;
            }
        }
    } *gameState;

    void respawnCactus(Cactus & cactus)
    {
        cactus.transform.position = Vec2{SPAWN_CACTUS_X_POSITION,GROUND_Y_POSITION};
    }

    void initialize()
    {
        gameState->initialize();

        //initialize dinosaur
        Dinosaur & dinosaur = gameState->dinosaur;
        dinosaur.transform.position = Vec2{60.0f,GROUND_Y_POSITION};
        dinosaur.transform.size = Vec2{32.0f,42.0f};

        //initialize cactus
        gameState->cactus = Cactus();
        gameState->cactus.transform.size = Vec2{30.0f,15.0f};
        respawnCactus(gameState->cactus);
    };

    void resetGame()
    {
        respawnCactus(gameState->cactus);
        gameState->dinosaur.transform.position.y = GROUND_Y_POSITION;
    };

    void readInput()
    {
        bool isJumpPressed = input::isKeyDown(input::LDK_KEY_UP) || input::isKeyDown(input::LDK_KEY_W);
        if (!gameState->isJumping && isJumpPressed)
        {
            gameState->isJumping = true;
            gameState->applyJumpImpulseForce();
        }

        bool isJumpReleased = input::isKeyUp(input::LDK_KEY_UP) || input::isKeyUp(input::LDK_KEY_W);
        if (isJumpReleased && gameState->jumpImpulseForce > 0.0f)
        {
            gameState->jumpImpulseForce *= 0.6f;
        }
    };

    void processDinosaur(Dinosaur& dinosaur, float deltaTime)
    {
        if (gameState->isJumping)
        {
            dinosaur.transform.position.y += gameState->jumpImpulseForce * deltaTime;
            gameState-> jumpImpulseForce += gameState->gravityForce * deltaTime;

            bool isGrounded = dinosaur.transform.position.y <= GROUND_Y_POSITION;
            if (isGrounded)
            {
                dinosaur.transform.position.y = GROUND_Y_POSITION;
                gameState-> jumpImpulseForce = 0.0f;
                gameState->isJumping = false;
            }
        }
    };

    void processCactus(float deltaTime)
    {
        //TODO(andrei) create a cactus pool and handle its spawn logic based on {MIN,MAX} distance
        Transform & cactusTransform = gameState->cactus.transform;
        float movementStep = (gameState->getScenerySpeed() * deltaTime);
        cactusTransform.position.x -= movementStep;

        if ((cactusTransform.position.x + cactusTransform.size.x) <= OFF_SCREEN_OFFSET)
        {
            respawnCactus(gameState->cactus);
        }
    };

    void update(float deltaTime)
    {
        if (hasCollided(gameState->dinosaur.transform, gameState->cactus.transform))
        {
            resetGame();
        }

        gameState->tryChangeSceneryLevel(deltaTime);
        readInput();
        processDinosaur(gameState->dinosaur, deltaTime);
        processCactus(deltaTime);
    };
};
#endif
