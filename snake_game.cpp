#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };//multiple options for user to input
enum Difficulty { EASY, MEDIUM, HARD };// enum=enumerator options for user to select

class SnakeGame {
private:
    bool gameOver;// for checking if game over or not
    const int width;//grid 
    const int height;//grid
    int x, y, foodX, foodY, score;//related to snake position,food positon,score
    int speed;//speed
    Direction dir;// enum direction
//stored in form of (x,y)
    vector<pair<int, int>> snake;//for printing snake
    vector<pair<int, int>> obstacles;//for printing obstacles
    Difficulty currentDifficulty;//enum difficulty

public:
    SnakeGame(int w, int h, int spd) : width(w), height(h), gameOver(false), score(0), speed(spd), dir(STOP) {
        resetGame();
    }// constructor for user input of this form

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

    void generateObstacles() {
        obstacles.clear();//clearing grid from garbage values
        int numObstacles = (width * height) / 200;//no. of objects
        for (int i = 0; i < numObstacles; i++) {
            // random generation of objects
            int ox = rand() % width;
            int oy = rand() % height;
            if ((ox != x || oy != y) && !(ox == foodX && oy == foodY)) {
                obstacles.push_back({ox, oy});
            }
        }
    }
    void resetGame() {
        gameOver = false;
        score = 0;
        dir = RIGHT;// intial direction
        x = width / 2;
        y = height / 2;
        snake.clear();// for clearing the grid to avoid garbage values
        snake.push_back({x, y});// body of snake
        snake.push_back({x-1, y});// body of snake
        foodX = rand() % width;//random spawn of food 
        foodY = rand() % height;
        generateObstacles();
    }
    void draw() {
        vector<string> buffer(height + 2, string(width + 2, ' '));// used + 2 becs we want extra space initialize with " "
 
        for (int i = 0; i < width + 2; i++) {
            buffer[0][i] = '#';
            buffer[height + 1][i] = '#';
        }

        for (int i = 1; i <= height; i++) {
            buffer[i][0] = '#';
            buffer[i][width + 1] = '#';
        }

        for (auto part : snake) {
            // of form column-row
            buffer[part.second + 1][part.first + 1] = '*';// buffer includes wall so we do +1
        }

        buffer[y + 1][x + 1] = '*';// include snake head
        buffer[foodY + 1][foodX + 1] = 'F';

        for (auto obs : obstacles) {
            buffer[obs.second + 1][obs.first + 1] = 'O'; // O represents obstacle
        }
        // used for smoothness and avoiding flickering
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD cursorPosition;
        cursorPosition.X = 0;
        cursorPosition.Y = 0;
        SetConsoleCursorPosition(hConsole, cursorPosition);
        // for implementing buffer
        for (const auto& line : buffer) {
            cout << line << endl;
        }
        cout << "Score: " << score << endl;
    }
    void input() {
        if (_kbhit()) {// used for keyboard input of console
            Direction olddir = dir;
            switch (_getch()) {// with getch() we don't require to press enter key after every input
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
        snake.insert(snake.begin(), {x, y});// inserting new head for continuous movement and tail is poped in else condition
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

        if (x < 0 || x >= width || y < 0 || y >= height) // when snake touches the wall then game over
            gameOver = true;

        for (int i = 1; i < snake.size(); i++) {
            // check if head is collided with body 
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
    srand(static_cast<unsigned>(time(0)));// with this srand diff sequence are produced
    int gridWidth = 30;
    int gridHeight = 25;
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



