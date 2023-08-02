#include "pch.h"
#include "Game.h"
#include "Common/StepTimer.h"


void Game::pushState(GameState* state)
{
    states.push_back(state);

}

void Game::popState()
{
    states.back();
    delete states.back();
    states.pop_back();
}

GameState* Game::CurrentState()
{
    return nullptr;
}

void Game::gameLoop()
{


    GameTimer elapsed = restart();
    float dt = elapsed.asSeconds();

    //exception handling
    if (CurrentState() == nullptr)
        continue;

    //get user input for current game state
    CurrentState()->handleInput();

    //update anything neccessary
    CurrentState()->update(dt);

    //draw anything in the current game state
    CurrentState()->draw(dt);

}

