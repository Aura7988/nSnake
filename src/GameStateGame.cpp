#include "GameStateGame.hpp"
#include "Input.hpp"
#include "Ncurses.hpp"

GameStateGame::GameStateGame():
    player(NULL),
    board(NULL)
{ }
GameStateGame::~GameStateGame()
{ }
void GameStateGame::load(int stack)
{
    UNUSED(stack);
    this->player = new Sprite("[]", 2, 1, Color::pair("red", "black"));
    this->board = new Board(10, 10);
    this->board->at(2, 2)->set(Tile::FOOD);
    this->board->at(1, 2)->set(Tile::FOOD);
    this->board->at(3, 2)->set(Tile::FOOD);
    this->board->at(1, 2)->clear();
}
int GameStateGame::unload()
{
// Time to delete!
// This macro deletes a thing only if it's non-NULL,
// making sure it won't double-delete things.
#define safe_delete(x) \
{                      \
    if (x)             \
    {                  \
        delete (x);    \
        x = NULL;      \
    }                  \
}

    safe_delete(this->player);
    safe_delete(this->board);
    return 0;
}
GameState::StateCode GameStateGame::update(float dt)
{
    UNUSED(dt);

    Input* input = Input::getInstance();
    input->update();

    if (input->isKeyDown('q'))
        return GameState::QUIT;

    return GameState::CONTINUE;
}
void GameStateGame::render()
{
    Ncurses::setStyle(Color::pair("yellow", "black"));
    Ncurses::print("This is where the game would be.", 30, 2);
    Ncurses::print("Just wait a while, things are being.", 30, 3);
    Ncurses::print("actively developed.", 30, 4);

    Ncurses::setStyle(Color::pair("magenta", "black"));
    Ncurses::print("Press <q> to quit.", 30, 6);

    this->player->render(20, 20);
    this->board->render(0, 0);
}
