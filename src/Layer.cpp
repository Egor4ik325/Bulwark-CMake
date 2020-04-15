#include "Layer.h"
#include "LayerStack.h"

Layer::Layer(LayerStack &stack) :
    stack(stack), visible(true)
{
}