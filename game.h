#define WIDTH 40
#define HEIGHT 20

typedef struct {
    char name[50];
    int score;
} Player;

typedef enum { 
    STOP = 0, LEFT, RIGHT, UP, DOWN 
} Direction;

void initializeGame();
void drawGame();
void handleInput();
void updateLogic();
void generateFood();
void hideConsoleCursor();
void moveCursor(int x, int y);
void chooseDifficulty();
int askToPlayAgain();
void loadHighScoreFromFile();
void saveHighScoreToFile();
void saveResultToAllPlayersFile();
void displayHighScore();

extern Player currentPlayer, topPlayer;
extern Direction currentDirection;
extern int gameOverFlag, snakeX, snakeY, foodX, foodY;
extern int tailX[100], tailY[100], tailLength, gameSpeed;

