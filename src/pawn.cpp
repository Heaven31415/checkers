#include "pawn.hpp"
#include "board.hpp"

Pawn::Pawn(Board* board, const sf::Vector2i& position, Color color)
: mBoard{board}
, mSprite{Resources::getTexture(color == Color::Light ? "LightPawn" : "DarkPawn")}
, mPosition{position}
, mColor{color}
, mIsKing{true}
, mIsSelected{false}
{
    move(mPosition);
}

void Pawn::select(bool value)
{
    std::string textureName = "";

    if (mColor == Color::Light) textureName += "Light";
    else textureName += "Dark";

    if (mIsKing) textureName += "King";
    else textureName += "Pawn";

    if (value) textureName += "Selected";

    mSprite.setTexture(Resources::getTexture(textureName));
    mIsSelected = value;
}

void Pawn::move(const sf::Vector2i& dest)
{
    mPosition = dest;
    mSprite.setPosition(64.f * (dest.x + 5), 64.f * (dest.y + 1));

    if (!mIsKing && (mColor == Color::Light && dest.y == 7 || mColor == Color::Dark && dest.y == 0))
    {
        mIsKing = true;

        if (mColor == Color::Light)
            mSprite.setTexture(Resources::getTexture("LightKing"));
        else
            mSprite.setTexture(Resources::getTexture("DarkKing"));
    }
}

bool Pawn::canMove(const sf::Vector2i& destination) const
{
    if (!validatePosition(destination)) return false;

    if (destination == mPosition) return false;

    if (mIsKing)
    {
        if (abs(destination.x - mPosition.x) != abs(destination.y - mPosition.y)) return false;

        int dx = (destination.x > mPosition.x) ? 1 : -1;
        int dy = (destination.y > mPosition.y) ? 1 : -1;

        bool foundSomebody = false;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            if (mBoard->getPawn(actualX, actualY))
            {
                foundSomebody = true;
                break;
            }

            actualX += dx; 
            actualY += dy;
        }

        return !foundSomebody && !mBoard->getPawn(destination);
    }
    else
    {
        if (mColor == Color::Light)
        {
            if ((destination.x == mPosition.x - 1 || destination.x == mPosition.x + 1) && (destination.y == mPosition.y + 1))
                return mBoard->getPawn(destination) == nullptr;
        }
        else
        {
            if ((destination.x == mPosition.x - 1 || destination.x == mPosition.x + 1) && (destination.y == mPosition.y - 1))
                return mBoard->getPawn(destination) == nullptr;
        }
    }

    return false;
}

// for int i = -1; i <= 1; i += 2
//   for int j = -1; j <= 1; j += 2
//     ...

bool Pawn::canMove() const
{
    if (mIsKing)
    {
        int x = mPosition.x + 1;
        int y = mPosition.y + 1;

        while (validatePosition(x, y))
        {
            if (canMove({ x, y })) return true;
            x++;
            y++;
        }

        x = mPosition.x - 1;
        y = mPosition.y + 1;

        while (validatePosition(x, y))
        {
            if (canMove({ x, y })) return true;
            x--;
            y++;
        }

        x = mPosition.x + 1;
        y = mPosition.y - 1;

        while (validatePosition(x, y))
        {
            if (canMove({ x, y })) return true;
            x++;
            y--;
        }

        x = mPosition.x - 1;
        y = mPosition.y - 1;

        while (validatePosition(x, y))
        {
            if (canMove({ x, y })) return true;
            x--;
            y--;
        }
    }
    else
    {
        if (mColor == Color::Light)
            return canMove({ mPosition.x - 1, mPosition.y + 1 }) || canMove({ mPosition.x + 1, mPosition.y + 1 });
        else
            return canMove({ mPosition.x - 1, mPosition.y - 1 }) || canMove({ mPosition.x + 1, mPosition.y - 1 });
    }

    return false;
}

bool Pawn::canFight(const sf::Vector2i& destination) const
{
    if (!validatePosition(destination)) return false;

    if (destination == mPosition) return false;

    if (mBoard->getPawn(destination) != nullptr) return false;

    if (mIsKing)
    {
        if (abs(destination.x - mPosition.x) != abs(destination.y - mPosition.y)) return false;

        int dx = (destination.x > mPosition.x) ? 1 : -1;
        int dy = (destination.y > mPosition.y) ? 1 : -1;

        int foundEnemies = 0;
        int foundAllies = 0;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            auto* pawn = mBoard->getPawn({ actualX, actualY });
            if (pawn)
            {
                if (pawn->getColor() == mColor)
                    foundAllies++;
                else
                    foundEnemies++;
            }

            actualX += dx;
            actualY += dy;
        }

        return foundAllies == 0 && foundEnemies == 1 && !mBoard->getPawn(destination);
    }

    Pawn* pawn = nullptr;

    if (destination.x == mPosition.x + 2 && destination.y == mPosition.y + 2)
        pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
    else if (destination.x == mPosition.x - 2 && destination.y == mPosition.y + 2)
        pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
    else if (destination.x == mPosition.x + 2 && destination.y == mPosition.y - 2)
        pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
    else if (destination.x == mPosition.x - 2 && destination.y == mPosition.y - 2)
        pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

    return pawn && pawn->getColor() != mColor;
}

bool Pawn::canFight() const
{
    if (mIsKing)
    {
        int x = mPosition.x + 1;
        int y = mPosition.y + 1;

        while (validatePosition(x, y))
        {
            if (canFight({ x, y })) return true;
            x++;
            y++;
        }

        x = mPosition.x - 1;
        y = mPosition.y + 1;

        while (validatePosition(x, y))
        {
            if (canFight({ x, y })) return true;
            x--;
            y++;
        }

        x = mPosition.x + 1;
        y = mPosition.y - 1;

        while (validatePosition(x, y))
        {
            if (canFight({ x, y })) return true;
            x++;
            y--;
        }

        x = mPosition.x - 1;
        y = mPosition.y - 1;

        while (validatePosition(x, y))
        {
            if (canFight({ x, y })) return true;
            x--;
            y--;
        }

        return false;
    }
    else
    {
        return canFight(sf::Vector2i{ mPosition.x + 2, mPosition.y + 2 })
            || canFight(sf::Vector2i{ mPosition.x - 2, mPosition.y + 2 })
            || canFight(sf::Vector2i{ mPosition.x + 2, mPosition.y - 2 })
            || canFight(sf::Vector2i{ mPosition.x - 2, mPosition.y - 2 });
    }
}

const sf::Vector2i& Pawn::getPosition() const
{
    return mPosition;
}

Color Pawn::getColor() const
{
    return mColor;
}

bool Pawn::isKing() const
{
    return mIsKing;
}

bool Pawn::isSelected() const
{
    return mIsSelected;
}

void Pawn::fight(const sf::Vector2i& destination)
{
    if (!validatePosition(destination)) return;

    if (destination == mPosition) return;

    if (mBoard->getPawn(destination) != nullptr) return;

    if (mIsKing)
    {
        int dx = (destination.x > mPosition.x) ? 1 : -1;
        int dy = (destination.y > mPosition.y) ? 1 : -1;

        int actualX = mPosition.x + dx;
        int actualY = mPosition.y + dy;

        while (actualX != destination.x && actualY != destination.y)
        {
            auto* pawn = mBoard->getPawn({ actualX, actualY });
            if (pawn && pawn->getColor() != mColor)
            {
                move(destination);
                mBoard->killPawn(pawn->getPosition());
                break;
            }

            actualX += dx;
            actualY += dy;
        }
    }
    else
    {
        Pawn* pawn = nullptr;

        if (destination.x == mPosition.x + 2 && destination.y == mPosition.y + 2)
            pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y + 1 });
        else if (destination.x == mPosition.x - 2 && destination.y == mPosition.y + 2)
            pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y + 1 });
        else if (destination.x == mPosition.x + 2 && destination.y == mPosition.y - 2)
            pawn = mBoard->getPawn({ mPosition.x + 1, mPosition.y - 1 });
        else if (destination.x == mPosition.x - 2 && destination.y == mPosition.y - 2)
            pawn = mBoard->getPawn({ mPosition.x - 1, mPosition.y - 1 });

        if (pawn && pawn->getColor() != mColor)
        {
            move(destination);
            mBoard->killPawn(pawn->getPosition());
        }
    }
}

void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}