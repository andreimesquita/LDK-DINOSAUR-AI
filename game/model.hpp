#ifndef MODEL_H
#define MODEL_H

namespace model
{
    const float SPAWN_CACTUS_X_POSITION = 1200.0f;
    const float GROUND_Y_POSITION = 100.0f;
    const float OFF_SCREEN_OFFSET = -10.0f;
    const int MAX_SCENERY_LEVEL = 8;

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
    private:
        float _sceneryLevelDeltaSum;
        uint32 _sceneryLevel;

    public:
        float speedBySceneryLevel[MAX_SCENERY_LEVEL];
        Cactus cactus;
        Dinosaur dinosaur;
        float jumpDeltaSum;
        bool isJumping;

        //input data
        bool isJumpPressed;

        void initialize()
        {
            _sceneryLevel = 0;
            _sceneryLevelDeltaSum = 0.0f;
            jumpDeltaSum = 0.0f;

            const float firstScenerySpeed = 300.0f;
            const float lastScenerySpeed = 850.0f;

            for(int i = 0; i < MAX_SCENERY_LEVEL; i++)
            {
                float increment = (lastScenerySpeed - firstScenerySpeed);
                float percentage = (i / MAX_SCENERY_LEVEL);

                speedBySceneryLevel[i] = firstScenerySpeed + increment * percentage;
            }
        }

        float getScenerySpeed()
        {
            return speedBySceneryLevel[_sceneryLevel];
        }

        void setSceneryLevel(uint32 newSceneryLevel)
        {
            _sceneryLevel = newSceneryLevel;
        }

        void tryChangeSceneryLevel(float deltaTime)
        {
            if(_sceneryLevel == MAX_SCENERY_LEVEL)
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
        dinosaur.transform.position = Vec2{30.0f,GROUND_Y_POSITION};
        dinosaur.transform.size = Vec2{32.0f,42.0f};

        //initialize cactus
        gameState->cactus = Cactus();
        gameState->cactus.transform.size = Vec2{30.0f,15.0f};
        respawnCactus(gameState->cactus);
    };

    void readInput()
    {
        gameState->isJumpPressed = input::getKey(input::LDK_KEY_UP);
        if (!gameState->isJumping && gameState->isJumpPressed)
        {
            gameState->isJumping = true;
            gameState->jumpDeltaSum = 0.0f;
        }
    };

    void processDinosaur(Dinosaur& dinosaur, float deltaTime)
    {
        if (gameState->isJumping)
        {
            gameState->jumpDeltaSum += deltaTime;
            if (gameState->isJumpPressed)
            {
                //TODO(andrei) apply impulse force over time
                dinosaur.transform.position.y += 160.0f * deltaTime;
            }
        }

        const float gravityForce = -100.0f;
        dinosaur.transform.position.y += gravityForce * deltaTime;

        dinosaur.transform.position.y = MAX(dinosaur.transform.position.y, GROUND_Y_POSITION);
        if (dinosaur.transform.position.y == GROUND_Y_POSITION)
        {
            gameState->isJumping = false;
            LogInfo("Jump stopped at %f", gameState->jumpDeltaSum);
            gameState->jumpDeltaSum = 0.0f;
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

    void readDebugInput()
    {
        if (input::isKeyDown(input::LDK_KEY_0)) gameState->setSceneryLevel(0);
        if (input::isKeyDown(input::LDK_KEY_1)) gameState->setSceneryLevel(1);
        if (input::isKeyDown(input::LDK_KEY_2)) gameState->setSceneryLevel(2);
        if (input::isKeyDown(input::LDK_KEY_3)) gameState->setSceneryLevel(3);
        if (input::isKeyDown(input::LDK_KEY_4)) gameState->setSceneryLevel(4);
        if (input::isKeyDown(input::LDK_KEY_5)) gameState->setSceneryLevel(5);
        if (input::isKeyDown(input::LDK_KEY_6)) gameState->setSceneryLevel(6);
        if (input::isKeyDown(input::LDK_KEY_7)) gameState->setSceneryLevel(7);
    };

    void update(float deltaTime)
    {
        readDebugInput();
        gameState->tryChangeSceneryLevel(deltaTime);
        readInput();
        processDinosaur(gameState->dinosaur, deltaTime);
        processCactus(deltaTime);
    };
};
#endif
