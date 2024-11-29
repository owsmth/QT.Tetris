#include "tetris.h"
#include "startscreen.h"
#include "gameoverscreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    StartScreen startScreen;
    Tetris tetrisGame;
    GameOverScreen gameOverScreen;

    // Transition from Start Screen to Tetris game
    QObject::connect(&startScreen, &StartScreen::startGame, [&]() {
        startScreen.hide();
        tetrisGame.show();
    });

    // Transition from Tetris game to Game Over screen
    QObject::connect(&tetrisGame, &Tetris::gameOver, [&]() {
        tetrisGame.hide();
        gameOverScreen.show();
    });

    // Restart game from Game Over screen
    QObject::connect(&gameOverScreen, &GameOverScreen::restartGame, [&]() {
        gameOverScreen.hide();
        tetrisGame.resetGame();  // Add this function in Tetris to reset game state
        tetrisGame.show();
    });

    startScreen.show();
    return app.exec();
}
