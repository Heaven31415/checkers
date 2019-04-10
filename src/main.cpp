#include <iostream>
#include "state_stack.hpp"

int main()
{
    try
    {
        StateStack::get().push(State::Type::Title);
        StateStack::get().run();
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
    }
}