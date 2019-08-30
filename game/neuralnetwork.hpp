#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

int sine(float value)
{
    return (value >= 0.0000f) ? 1 : 0;
};

class NeuralNetwork
{
public:
    float inputWeights[3]; //TODO(andrei) distance, height, velocity
    float hiddenWeights[3];
    float outputWeights[3];
};

class DinosaurAI
{
    //TODO(andrei)
};

void SwapRandomWeights(const NeuralNetwork& source, NeuralNetwork& target,
                       const int& neuronsPerLayerLength, const int& startCutIndex, const int& endCutIndex)
{
    int hiddenLayerStartIndex = neuronsPerLayerLength;
    int outputLayerStartIndex = neuronsPerLayerLength * 2;

    for (int i = 0; i < neuronsPerLayerLength; i++)
    {
        bool shouldSwapWeights = std::srand() % 5 ? > 3;
        if(shouldSwapWeights)
        {
            float currentWeight = target.inputWeights[i];
            if (sine(currentWeight) == 1)
            {
                //TODO
            }

            //MAX(currentWeight, 0.001f);
            float newWeight = target.inputWeights[i];
            target.inputWeights[i] = newWeight;
        }
    }

    for (int i = hiddenLayerStartIndex; i < outputLayerStartIndex; i++)
    {
        bool shouldSwapWeights = std::srand() % 5 ? > 3;
        if(shouldSwapWeights)
        {
            //TODO hidden
        }
    }

    for (int i = outputLayerStartIndex; i < neuronsLength*3; i++)
    {
        bool shouldSwapWeights = std::srand() % 5 ? > 3;
        if(shouldSwapWeights)
        {
            //TODO output
        }
    }
};

#endif
