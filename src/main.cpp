#include <iostream>
#include "state_manager.hpp"

int main()
{
    try
    {
        StateManager manager{};
        manager.run();
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
    }
}