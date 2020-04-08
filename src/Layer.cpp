#include "Layer.h"
#include "LayerStack.h"

Layer::Layer(LayerStack &stack) :
    stack(stack), window(stack.window), visible(true)
{
}