#include <iostream>
#include "state_stack.hpp"

int main()
{
    try
    {
        StateStack::push(State::Type::Game);
        StateStack::run();
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
    }
}