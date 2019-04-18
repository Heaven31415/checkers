#include "ai.hpp"

void ai::Pawn::move(const sf::Vector2i& destination, bool duringFight)
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

bool ai::Pawn::canMove(const sf::Vector2i& destination) const
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

bool ai::Pawn::canMove() const
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

std::vector<sf::Vector2i> ai::Pawn::getMovePositions() const
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

void ai::Pawn::fight(const sf::Vector2i& destination)
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
            if (pawn && pawn->color != color)
            {
                board->killPawn(pawn->position);
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

        if (pawn && pawn->color != color)
        {
            board->killPawn(pawn->position);
            move(destination);
        }
    }
}

bool ai::Pawn::canFight(const sf::Vector2i& destination) const
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
                if (pawn->color == color)
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

    return pawn && pawn->color != color;
}

bool ai::Pawn::canFight() const
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

std::vector<sf::Vector2i> ai::Pawn::getFightPositions() const
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

ai::Pawn* ai::Board::getPawn(int x, int y)
{
    if (x < 0 || x >= BoardWidth) return nullptr;

    if (y < 0 || y >= BoardHeight) return nullptr;

    for (auto& pawn : pawns)
        if (pawn.position == sf::Vector2i{ x, y }) return &pawn;

    return nullptr;
}

ai::Pawn* ai::Board::getPawn(const sf::Vector2i& position)
{
    return getPawn(position.x, position.y);
}

std::vector<ai::Pawn*> ai::Board::getPawns(Color color)
{
    std::vector<Pawn*> output;

    for (auto& pawn : pawns)
        if (pawn.color == color) output.push_back(&pawn);

    return output;
}

void ai::Board::killPawn(const sf::Vector2i& position)
{
    pawns.erase(
        std::remove_if(
            pawns.begin(),
            pawns.end(),
            [&position](const ai::Pawn& pawn) { return pawn.position == position; }
        ),
        pawns.end()
    );
}

bool ai::Board::isFightPossible(Color color) const
{
    for (const auto& pawn : pawns)
        if (pawn.color == color && pawn.canFight())
            return true;

    return false;
}

bool ai::Board::isMovePossible(Color color) const
{
    for (const auto& pawn : pawns)
        if (pawn.color == color && pawn.canMove())
            return true;

    return false;
}

int ai::Board::pawnCount(Color color) const
{
    int count = 0;

    for (const auto& pawn : pawns)
        if (pawn.color == color)
            count++;

    return count;
}

ai::Move ai::getNextMove(ai::Board* board, Color color, int depth)
{
    ai::buildDecisionTree(board, color, depth);

    bool canFight = false;

    for (const auto& child : board->children)
    {
        if (child->move->type == ai::Move::Type::Fight)
        {
            canFight = true;
            break;
        }
    }

    if (canFight)
    {
        board->children.erase(
            std::remove_if(
                board->children.begin(),
                board->children.end(),
                [](const std::unique_ptr<ai::Board>& board) { return board->move->type != ai::Move::Type::Fight; }
            ),
            board->children.end()
        );
    }

    auto result = ai::minimax(board, color, depth);

    auto* node = result.first;

    while (node->parent != board)
    {
        node = node->parent;
    }

    ai::Move move{};

    move.type = node->move->type;
    move.start = node->move->start;
    move.end = node->move->end;

    return move;
}

std::pair<ai::Board*, int> ai::minimax(ai::Board* board, Color color, int depth)
{
    if (depth == 0 || (!board->isFightPossible(color) && !board->isMovePossible(color)) || board->pawnCount(color) == 0)
        return { board, computeHeuristic(board) };

    if (color == Color::Light)
    {
        std::pair<ai::Board*, int> currentPair = { nullptr, std::numeric_limits<int>::min() };

        for (const auto& child : board->children)
        {
            auto pair = ai::minimax(child.get(), color == Color::Light ? Color::Dark : Color::Light, depth - 1);

            if (pair.second > currentPair.second) currentPair = pair;
        }

        return currentPair;
    }
    else
    {
        std::pair<ai::Board*, int> currentPair = { nullptr, std::numeric_limits<int>::max() };

        for (const auto& child : board->children)
        {
            auto pair = ai::minimax(child.get(), color == Color::Light ? Color::Dark : Color::Light, depth - 1);

            if (pair.second < currentPair.second) currentPair = pair;
        }

        return currentPair;
    }
}

void ai::buildDecisionTree(ai::Board* board, Color color, int depth)
{
    if (depth == 0) return;

    for (size_t i = 0; i < board->pawns.size(); i++)
    {
        if (board->pawns[i].color != color) continue;

        auto fightPositions = board->pawns[i].getFightPositions();

        for (const auto& fightPosition : fightPositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->parent = board;

            child->move = std::make_unique<ai::Move>();
            child->move->type = Move::Type::Fight;
            child->move->start = board->pawns[i].position;
            child->move->end = fightPosition;

            for (auto p : board->pawns)
            {
                p.board = child.get();
                child->pawns.push_back(p);
            }
            child->pawns[i].fight(fightPosition);

            /*
                TODO: This snippet doesn't handle situations in which after a first
                fight, you can fight again and choose between more than one fight.
            */
            auto position = fightPosition;

            while (auto* p = child->getPawn(position))
            {
                if (!p->canFight()) break;
                else
                {
                    position = p->getFightPositions()[0];
                    p->fight(position);
                }
            }

            board->children.push_back(std::move(child));
        }

        if (!fightPositions.empty()) continue;

        auto movePositions = board->pawns[i].getMovePositions();

        for (const auto& movePosition : movePositions)
        {
            auto child = std::make_unique<ai::Board>();
            child->parent = board;

            child->move = std::make_unique<ai::Move>();
            child->move->type = Move::Type::Move;
            child->move->start = board->pawns[i].position;
            child->move->end = movePosition;
            
            for (const auto& p : board->pawns) child->pawns.push_back(p);
            for (auto& p : child->pawns) p.board = child.get();
            child->pawns[i].move(movePosition);

            board->children.push_back(std::move(child));
        }
    }

    for (const auto& child : board->children)
        ai::buildDecisionTree(child.get(), color == Color::Light ? Color::Dark : Color::Light, depth - 1);
}

int ai::computeHeuristic(ai::Board* board)
{
    auto lightPawns = board->getPawns(Color::Light);
    auto darkPawns = board->getPawns(Color::Dark);

    int heuristic = 0;

    for (const auto& pawn : lightPawns)
    {
        if (pawn->isKing) heuristic += 2;
        else heuristic += 1;
    }

    for (const auto& pawn : darkPawns)
    {
        if (pawn->isKing) heuristic -= 2;
        else heuristic -= 1;
    }

    return heuristic;
}
