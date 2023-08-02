#pragma once


#include "pch.h"

class GameState;

class Game
{
public:
    //constructor and deconstructor
    Game();
    ~Game();

    //functions for changing game state
    void pushState(GameState* state);
    void popState();

    //function to get the current State (note this function must be a pointer)
    GameState* CurrentState();

    //game loop function
    void gameLoop();


private:
    std::vector<GameState*> states;


};



