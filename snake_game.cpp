#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Difficulty { EASY, MEDIUM, HARD };

class SnakeGame {
private:
    bool gameOver;
    const int width;
    const int height;
    int x, y, foodX, foodY, score;
    int speed;
    Direction dir;
    vector<pair<int, int>> snake;
    vector<pair<int, int>> obstacles;
    Difficulty currentDifficulty;

public:
    SnakeGame(int w, int h, int spd) : width(w), height(h), gameOver(false), score(0), speed(spd), dir(STOP) {
        resetGame();
    }

    void setDifficulty(Difficulty difficulty) {
        currentDifficulty = difficulty;
        switch (currentDifficulty) {
            case EASY:
                speed = 170; // Slow speed for easy mode
                break;
            case MEDIUM:
                speed = 130; // Default speed for medium
                break;
            case HARD:
                speed = 100; // Fast speed for hard mode
                break;
        }
    }

    void resetGame() {
        gameOver = false;
        score = 0;
        dir = RIGHT;
        x = width / 2;
        y = height / 2;
        snake.clear();
        snake.push_back({x, y});
        snake.push_back({x-1, y});
        

        foodX = rand() % width;
        foodY = rand() % height;
        generateObstacles();
    }

    void generateObstacles() {
        obstacles.clear();
        int numObstacles = (width * height) / 200; 
        for (int i = 0; i < numObstacles; i++) {
            int ox = rand() % width;
            int oy = rand() % height;
            if ((ox != x || oy != y) && !(ox == foodX && oy == foodY)) {
                obstacles.push_back({ox, oy});
            }
        }
    }

    void draw() {
        vector<string> buffer(height + 2, string(width + 2, ' '));

        for (int i = 0; i < width + 2; i++) {
            buffer[0][i] = '#';
            buffer[height + 1][i] = '#';
        }

        for (int i = 1; i <= height; i++) {
            buffer[i][0] = '#';
            buffer[i][width + 1] = '#';
        }

        for (auto part : snake) {
            buffer[part.second + 1][part.first + 1] = '*';
        }

        buffer[y + 1][x + 1] = '*';
        buffer[foodY + 1][foodX + 1] = 'F';

        for (auto obs : obstacles) {
            buffer[obs.second + 1][obs.first + 1] = 'O'; // O represents obstacle
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(hConsole, cursorPosition);

        for (const auto& line : buffer) {
            cout << line << endl;
        }

        cout << "Score: " << score << endl;
    }

    void input() {
        if (_kbhit()) {
            Direction olddir = dir;
            switch (_getch()) {
                case 'a': dir = LEFT; break;
                case 'd': dir = RIGHT; break;
                case 'w': dir = UP; break;
                case 's': dir = DOWN; break;
                case 'x': gameOver = true; break;
            }

            if (olddir == UP && dir == DOWN) dir = olddir;
            else if (olddir == DOWN && dir == UP) dir = olddir;
            else if (olddir == LEFT && dir == RIGHT) dir = olddir;
            else if (olddir == RIGHT && dir == LEFT) dir = olddir;
        }
    }

    void logic() {
        snake.insert(snake.begin(), {x, y});
        if (x == foodX && y == foodY) {
            score += 10;
            foodX = rand() % width;
            foodY = rand() % height;
        } else {
            snake.pop_back();
        }

        switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
        }

        if (x < 0 || x >= width || y < 0 || y >= height)
            gameOver = true;

        for (int i = 1; i < snake.size(); i++) {
            if (snake[i].first == x && snake[i].second == y) {
                gameOver = true;
                break;
            }
        }

        // Check for obstacle collision
        for (auto obs : obstacles) {
            if (obs.first == x && obs.second == y) {
                gameOver = true;
                break;
            }
        }
    }

    void playBeepSound() {
        Beep(750, 500); // Frequency of 750 Hz for 500 ms (sound when game over)
    }

    void run() {
        int maxx = 0;
        while (true) {
            while (!gameOver) {
                draw();
                input();
                logic();
                Sleep(speed);
            }

            maxx = max(maxx, score);
            cout << "Game Over!" << endl;
            cout << "Your score: " << score << endl;
            cout << "Maximum Score: " << maxx << endl;
            playBeepSound();  // Play beep sound on game over
            char choice;
            cout << "Press 'R' to restart or any other key to exit: ";
            cin >> choice;
            if (choice == 'R' || choice == 'r') {
                resetGame();
            } else {
                break;
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    int gridWidth = 30;
    int gridHeight = 20;
    int gameSpeed = 110;

    SnakeGame game(gridWidth, gridHeight, gameSpeed);

    // Set the difficulty level (Easy, Medium, Hard)
    Difficulty chosenDifficulty;
    int difficultyChoice;
    cout << "Select Difficulty (1: Easy, 2: Medium, 3: Hard): ";
    cin >> difficultyChoice;

    switch (difficultyChoice) {
        case 1: chosenDifficulty = EASY; break;
        case 2: chosenDifficulty = MEDIUM; break;
        case 3: chosenDifficulty = HARD; break;
        default: chosenDifficulty = MEDIUM; break;
    }
    game.setDifficulty(chosenDifficulty);

    game.run();
    return 0;
}



