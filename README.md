# Checkers

Nature-themed checkers implemented in cpp using [SFML](https://github.com/SFML/SFML) library with artificial intelligence that is using [minimax](https://en.wikipedia.org/wiki/Minimax) algorithm to mimic thinking.

## Title
![Title](/misc/Title.png)

## Game
![Game](/misc/Game.png)

## Requirements

To build this on Windows, you will need:
- [Premake5](https://premake.github.io/) or newer.
- [SFML 2.5.1](https://github.com/SFML/SFML) or newer.
- [Visual Studio 2017](https://visualstudio.microsoft.com/) or newer.

Building on other platforms is currently not supported, however it will most likely change in the future.

## Building

1. Download Premake5 from this [website](https://premake.github.io/download.html#v5) and place it somewhere where you will be able to use it from the command line.

2. Install SFML library on your system. [Official tutorials](https://www.sfml-dev.org/tutorials/2.5/) are a big help if you haven't done that before. After installing SFML you should have a folder somewhere on your disk which contains an include, lib and bin subdirectories. Save path to this directory, you will need it later.

3. Go to the directory where you have downloaded Checkers. Find and open a file named `premake5.lua` using any text editor. Modify the first line of this file so the variable `SFML_INSTALL_DIR` points to the directory where you have installed SFML library. If for example, your SFML is located at `"C:/SFML"` then the first line of this file should look like this: `SFML_INSTALL_DIR = "C:/SFML"`. Remember to use forward slashes!

4. Open your command line in the directory with Checkers and run the following command: `premake5 vs2017`. This will generate a solution file which you will have to use to compile the project.
5. Open file `checkers.sln` using Visual Studio and compile Checkers project just like any other cpp program.

## Credits

Making this game wouldn't be possible without the help of many amazing people and websites
that allow game developers to find and use fantastic high-quality free resources.

**Websites that I used:**

* [OpenGameArt](https://opengameart.org/)
* [Freesound](https://freesound.org/)

**Resources that I used:**

* Graphics
  * [RPG GUI Construction Kit v1.0](https://opengameart.org/content/rpg-gui-construction-kit-v10) by [Lamoot](https://opengameart.org/users/lamoot) licensed: CC-BY 3.0.
  * [Seamless Grass Texture II](https://opengameart.org/content/seamless-grass-texture-ii) by [athile](https://opengameart.org/users/athile) licensed: CC0 1.0 Universal.
  * [Chess Pieces and Board Squares](https://opengameart.org/content/chess-pieces-and-board-squares) by [JohnPablok](https://opengameart.org/users/johnpablok) licensed: CC-BY-SA 3.0.
  * [Chess Pieces](https://opengameart.org/content/chess-pieces-3) by [8BitGoggles](https://opengameart.org/users/8bitgoggles) licensed: CC-BY-SA 3.0.
  * [Chess Board Icon](http://www.iconarchive.com/show/chess-icons-by-aha-soft/chess-board-icon.html) by [Aha-Soft](http://www.aha-soft.com/) licensed: [license](http://www.iconarchive.com/icons/aha-soft/chess/license.txt).
* Sounds
  * [User Interface Sound Pack](https://freesound.org/people/PaulMorek/packs/18538/) by [PaulMorek](https://freesound.org/people/PaulMorek/) licensed: CC0 1.0 Universal.
  * [Game Over](https://opengameart.org/content/game-over-0) by [zuvizu](https://opengameart.org/users/zuvizu) licensed: CC0 1.0 Universal.
  * [We Did It](https://freesound.org/people/eardeer/sounds/423692/) by [eardeer](https://freesound.org/people/eardeer/) licensed: CC-BY-NC 3.0.
* Music
  * [Woods](https://opengameart.org/content/woods) by [Axton Crolley](https://opengameart.org/users/axtoncrolley) licensed: CC-BY 3.0.
  * [Forest](https://opengameart.org/content/forest) by [syncopika](https://opengameart.org/users/syncopika) licensed: CC-BY 3.0.
  * [Woodland Fantasy](https://opengameart.org/content/woodland-fantasy) by [Matthew Pablo](https://opengameart.org/users/matthew-pablo) licensed: CC-BY 3.0.
  * [Decision](https://opengameart.org/content/decision) by [Alexandr Zhelanov](https://opengameart.org/users/alexandr-zhelanov) licensed: CC-BY 3.0.
  * [Journey to the East Rocks](https://opengameart.org/content/journey-to-the-east-rocks) by [Alexandr Zhelanov](https://opengameart.org/users/alexandr-zhelanov) licensed: CC-BY 3.0.
  * [Nature Theme Sketch](https://opengameart.org/content/nature-theme-sketch) by [remaxim](https://opengameart.org/users/remaxim) licensed: CC-BY-SA 3.0.