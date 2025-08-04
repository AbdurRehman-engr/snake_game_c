#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "game.h"

Player currentPlayer, topPlayer;
Direction currentDirection;
int gameOverFlag, snakeX, snakeY, foodX, foodY;
int tailX[100], tailY[100], tailLength, gameSpeed;

void moveCursor(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideConsoleCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(console, &info);
}

void generateFood() {
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}
void initializeGame() {
    gameOverFlag = 0;
    currentDirection = STOP;
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    generateFood();
    currentPlayer.score = 0;
    tailLength = 0;
}

void drawGame() {
    moveCursor(0, 0);
    for (int i = 0; i < WIDTH + 2; i++) printf("##");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) printf("##");

            if (i == snakeY && j == snakeX)
                printf("O ");
            else if (i == foodY && j == foodX)
                printf("F ");
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o ");
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) printf("  ");
            }

            if (j == WIDTH - 1) printf("##");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("##");
    printf("\n");

    printf("Score: %d\tHigh Score: %d  name : %s\n", currentPlayer.score, topPlayer.score, topPlayer.name);
}

void handleInput() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'w': case 'W':
             if (currentDirection != DOWN)
              currentDirection = UP;
              break;
            case 's': case 'S':
             if (currentDirection != UP) 
             currentDirection = DOWN;
              break;
            case 'a': case 'A': 
            if (currentDirection != RIGHT) 
            currentDirection = LEFT;
             break;
            case 'd': case 'D':
             if (currentDirection != LEFT)
              currentDirection = RIGHT;
               break;
            case 'e': case 'E':
             gameOverFlag = 1;
              break;
        }
    }
}

void updateLogic() {
    int prevX = tailX[0], prevY = tailY[0];
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    for (int i = 1; i < tailLength; i++) {
        int tempX = tailX[i], tempY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (currentDirection) {
        case LEFT:  snakeX--; break;
        case RIGHT: snakeX++; break;
        case UP:    snakeY--; break;
        case DOWN:  snakeY++; break;
        default: break;
    }

    if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT)
        gameOverFlag = 1;

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            gameOverFlag = 1;
        }
    }

    if (snakeX == foodX && snakeY == foodY) {
        currentPlayer.score += 10;
        generateFood();
        tailLength++;
    }
}

void chooseDifficulty() {
    int level;
    do {
        system("cls");
        printf("Select Difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoice: ");
        scanf("%d", &level);
    } while (level < 1 || level > 3);

    gameSpeed = (level == 1) ? 150 : (level == 2) ? 100 : 30;
}

int askToPlayAgain() {
    int choice;
    printf("Press 1 to playagain\nAnyother key to exit ");
    scanf("%d", &choice);
    return (choice == 1);
}

void loadHighScoreFromFile() {
    FILE *file = fopen("highscore.txt", "r");
    if (file) {
        fscanf(file, "%s %d", topPlayer.name, &topPlayer.score);
        fclose(file);
    } else {
        strcpy(topPlayer.name, "---");
        topPlayer.score = 0;
    }
}

void saveHighScoreToFile() {
    if (currentPlayer.score > topPlayer.score) {
        FILE *file = fopen("highscore.txt", "w");
        if (file) {
            fprintf(file, "%s %d\n", currentPlayer.name, currentPlayer.score);
            fclose(file);
        }
    }
}

void displayHighScore() {
    printf("\n High Score: %s - %d\n", topPlayer.name, topPlayer.score);
}

void saveResultToAllPlayersFile() {
    FILE *file = fopen("results.txt", "a"); // open in append mode
    if (file) {
        fprintf(file, "%s %d\n", currentPlayer.name, currentPlayer.score);
        fclose(file);
    }
}
