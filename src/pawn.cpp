#include "board.hpp"
#include "pawn.hpp"
#include "state_stack.hpp"

Pawn::Pawn(Board* board, const sf::Vector2i& position, Color color)
: mData{board, position, color, false}
, mSprite{ Resources::get().texture(color == Color::Light ? "LightPawn" : "DarkPawn") }
, mIsSelected{ false }
{
    move(position);
}

void Pawn::select(bool value)
{
    std::string textureName = "";

    if (mData.color == Color::Light) textureName += "Light";
    else textureName += "Dark";

    if (mData.isKing) textureName += "King";
    else textureName += "Pawn";

    mSprite.setTexture(Resources::get().texture(textureName));
    mIsSelected = value;
}

void Pawn::move(const sf::Vector2i& destination, bool duringFight)
{
    mData.move(destination, duringFight);

    mSprite.setPosition(float(TileSize) * (mData.position.x + OffsetX), float(TileSize) * (mData.position.y + OffsetY));

    if(mData.isKing)
        mSprite.setTexture(Resources::get().texture(mData.color == Color::Light ? "LightKing" : "DarkKing"));
}

bool Pawn::canMove(const sf::Vector2i& destination) const
{
    return mData.canMove(destination);
}

bool Pawn::canMove() const
{
    return mData.canMove();
}

std::vector<sf::Vector2i> Pawn::getMovePositions() const
{
    return mData.getMovePositions();
}

void Pawn::fight(const sf::Vector2i& destination)
{
    mData.fight(destination);

    mSprite.setPosition(float(TileSize) * (mData.position.x + OffsetX), float(TileSize) * (mData.position.y + OffsetY));

    if (mData.isKing)
        mSprite.setTexture(Resources::get().texture(mData.color == Color::Light ? "LightKing" : "DarkKing"));
}

bool Pawn::canFight(const sf::Vector2i& destination) const
{
    return mData.canFight(destination);
}

bool Pawn::canFight() const
{
    return mData.canFight();
}

std::vector<sf::Vector2i> Pawn::getFightPositions() const
{
    return mData.getFightPositions();
}

Pawn::Data Pawn::getData() const
{
    return mData;
}

const sf::Vector2i& Pawn::getPosition() const
{
    return mData.position;
}

Color Pawn::getColor() const
{
    return mData.color;
}

bool Pawn::isKing() const
{
    return mData.isKing;
}

bool Pawn::isSelected() const
{
    return mIsSelected;
}

void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mIsSelected)
    {
        sf::Shader* shader = Resources::get().shader("Selection");
        shader->setUniform("time", StateStack::get().globalTimer().asSeconds());
        states.shader = shader;
    }
    target.draw(mSprite, states);
}

void Pawn::Data::move(const sf::Vector2i& destination, bool duringFight)
{
    if (!isValidPosition(destination)) return;

    if (destination == position) return;

    if (board->getPawn(destination) != nullptr) return;

    position = destination;
    
    if (!isKing && (color == Color::Light && destination.y == BoardHeight - 1 || color == Color::Dark && destination.y == 0))
    {
        if (duringFight && canFight()) return;
        isKing = true;
    }
}

bool Pawn::Data::canMove(const sf::Vector2i& destination) const
{
    if (!isValidPosition(destination)) return false;

    if (destination == position) return false;

    if (isKing)
    {
        // check whether we are moving across some diagonal
        if (abs(destination.x - position.x) != abs(destination.y - position.y)) return false;

        int dx = (destination.x > position.x) ? 1 : -1;
        int dy = (destination.y > position.y) ? 1 : -1;

        bool foundSomebody = false;

        int actualX = position.x + dx;
        int actualY = position.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            if (board->getPawn(actualX, actualY))
            {
                foundSomebody = true;
                break;
            }

            actualX += dx;
            actualY += dy;
        }

        return !foundSomebody && !board->getPawn(destination);
    }
    else
    {
        int offset = (color == Color::Light ? 1 : -1);
        if ((destination.x == position.x - 1 || destination.x == position.x + 1) && (destination.y == position.y + offset))
            return board->getPawn(destination) == nullptr;
    }

    return false;
}

bool Pawn::Data::canMove() const
{
    if (isKing)
    {
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                int x = position.x + i;
                int y = position.y + j;

                while (isValidPosition(x, y))
                {
                    if (canMove({ x, y })) return true;
                    x += i;
                    y += j;
                }
            }
        }
    }
    else
    {
        int offset = (color == Color::Light ? 1 : -1);
        return canMove({ position.x - 1, position.y + offset }) || canMove({ position.x + 1, position.y + offset });
    }

    return false;
}

std::vector<sf::Vector2i> Pawn::Data::getMovePositions() const
{
    std::vector<sf::Vector2i> movePositions{};

    if (isKing)
    {
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                int x = position.x + i;
                int y = position.y + j;

                while (isValidPosition(x, y))
                {
                    if (canMove({ x, y })) movePositions.push_back({ x, y });
                    x += i;
                    y += j;
                }
            }
        }
    }
    else
    {
        int offset = (color == Color::Light ? 1 : -1);

        if (canMove({ position.x - 1, position.y + offset }))
            movePositions.push_back({ position.x - 1, position.y + offset });

        if (canMove({ position.x + 1, position.y + offset }))
            movePositions.push_back({ position.x + 1, position.y + offset });
    }

    return movePositions;
}

void Pawn::Data::fight(const sf::Vector2i& destination)
{
    if (!isValidPosition(destination)) return;

    if (destination == position) return;

    if (board->getPawn(destination) != nullptr) return;

    if (isKing)
    {
        int dx = (destination.x > position.x) ? 1 : -1;
        int dy = (destination.y > position.y) ? 1 : -1;

        int actualX = position.x + dx;
        int actualY = position.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            auto* pawn = board->getPawn({ actualX, actualY });
            if (pawn && pawn->getColor() != color)
            {
                board->killPawn(pawn->getPosition());
                move(destination, true);
                break;
            }

            actualX += dx;
            actualY += dy;
        }
    }
    else
    {
        Pawn* pawn = nullptr;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (destination.x == position.x + 2 * i && destination.y == position.y + 2 * j)
                {
                    pawn = board->getPawn(position.x + i, position.y + j);
                    break;
                }
            }
        }

        if (pawn && pawn->getColor() != color)
        {
            board->killPawn(pawn->getPosition());
            move(destination);
        }
    }
}

bool Pawn::Data::canFight(const sf::Vector2i& destination) const
{
    if (!isValidPosition(destination)) return false;

    if (destination == position) return false;

    if (board->getPawn(destination) != nullptr) return false;

    if (isKing)
    {
        // check whether we are moving across some diagonal
        if (abs(destination.x - position.x) != abs(destination.y - position.y)) return false;

        int dx = (destination.x > position.x) ? 1 : -1;
        int dy = (destination.y > position.y) ? 1 : -1;

        int foundEnemies = 0;
        int foundAllies = 0;

        int actualX = position.x + dx;
        int actualY = position.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            auto* pawn = board->getPawn(actualX, actualY);
            if (pawn)
            {
                if (pawn->getColor() == color)
                    foundAllies++;
                else
                    foundEnemies++;
            }

            actualX += dx;
            actualY += dy;
        }

        return foundAllies == 0 && foundEnemies == 1 && !board->getPawn(destination);
    }

    Pawn* pawn = nullptr;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (destination.x == position.x + 2 * i && destination.y == position.y + 2 * j)
            {
                pawn = board->getPawn(position.x + i, position.y + j);
                break;
            }
        }
    }

    return pawn && pawn->getColor() != color;
}

bool Pawn::Data::canFight() const
{
    if (isKing)
    {
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                int x = position.x + i;
                int y = position.y + j;

                while (isValidPosition(x, y))
                {
                    if (canFight({ x, y })) return true;
                    x += i;
                    y += j;
                }
            }
        }

        return false;
    }

    return canFight({ position.x + 2, position.y + 2 })
        || canFight({ position.x - 2, position.y + 2 })
        || canFight({ position.x + 2, position.y - 2 })
        || canFight({ position.x - 2, position.y - 2 });
}

std::vector<sf::Vector2i> Pawn::Data::getFightPositions() const
{
    std::vector<sf::Vector2i> fightPositions{};

    if (isKing)
    {
        for (int i = -1; i <= 1; i += 2)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                int x = position.x + i;
                int y = position.y + j;

                while (isValidPosition(x, y))
                {
                    if (canFight({ x, y })) fightPositions.push_back({ x, y });
                    x += i;
                    y += j;
                }
            }
        }
    }
    else
    {
        for (int i = -2; i <= 2; i += 4)
        {
            for (int j = -2; j <= 2; j += 4)
            {
                if (canFight({ position.x + i, position.y + j }))
                    fightPositions.push_back({ position.x + i, position.y + j });
            }
        }
    }

    return fightPositions;
}