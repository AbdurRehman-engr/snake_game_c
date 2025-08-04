#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "game.h"

int main() {
    srand(time(NULL));
    hideConsoleCursor();

    printf("Welcome to Snake Game \n");
    printf("Enter your name to start: ");
    scanf("%s", currentPlayer.name);

    loadHighScoreFromFile();

    while (1) {
        chooseDifficulty();
        initializeGame();

        while (!gameOverFlag) {
            drawGame();
            handleInput();
            updateLogic();
            Sleep(gameSpeed);
        }

        moveCursor(0, HEIGHT + 4);
        printf("Game Over! Final Score: %d\n", currentPlayer.score);
        saveHighScoreToFile();
        saveResultToAllPlayersFile();
        loadHighScoreFromFile();
        displayHighScore();

        if (!askToPlayAgain())
            break;
    }

    printf("\nThanks for playing!\n");
    return 0;
}
