#include <iostream>
#include "game.hpp"

int main()
{
    try
    {
        Game game{};
        game.run();
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what() << '\n';
    }
}