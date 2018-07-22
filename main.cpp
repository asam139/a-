#include "AConfig.h"
#include <window.h>
#include <sprite.h>
#include <game.h>

#include <iostream>
int main (int argc, char *argv[]) {
    fprintf(stdout,"Version %d.%d\n", A_VERSION_MAJOR, A_VERSION_MINOR);

    Window::instance().init(GAME_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);

    Game game;
    game.init();
    game.start();
    game.shutdown();

    Window::instance().shutdown();

    return 0;
}