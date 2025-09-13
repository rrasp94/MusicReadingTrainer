#include "Game.h"
#include <windows.h>


int main() {

    MusicReadingTrainer::Game game;

  
    MusicReadingTrainer::g_game = &game;
    SetConsoleCtrlHandler(MusicReadingTrainer::ConsoleHandler, TRUE);

    game.run();

    return 0;
}

