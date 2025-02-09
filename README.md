
# SNAKE AND THE SURVIVAL HUNT
## DESCRIPTION
This is a simple Snake game implemented in C++. The game features different difficulty levels, obstacles, and a score tracking system. The snake moves around the grid, eating food to grow, and avoiding obstacles and itself to stay alive. The game ends when the snake collides with a wall, an obstacle, or itself.
## FEATURES 
Difficulty Levels: Choose between Easy, Medium, and Hard.

Obstacles: Randomly generated obstacles make the game more challenging.

Beep Sound: A beep sound is played when the game is over.

Score Tracking: The game keeps track of the current and highest score.

Smooth Gameplay: Uses Sleep() for smooth movement and _kbhit() for responsive controls.
## CONTROLS 
W - Move Up

S - Move Down

A - Move Left

D - Move Right

X - Quit the game
## How To Run
1.Compile the game using a C++ compiler that supports Windows-specific headers like windows.h.
2.Run the compiled executable.
3.Select the difficulty level (1 for Easy, 2 for Medium, 3 for Hard).
4.Use the controls to navigate the snake.
5.Eat food ('F') to increase your score and avoid obstacles ('O').
6.The game ends if you hit the walls, an obstacle, or yourself.
7.Press 'R' to restart or any other key to exit.
## Compilation Instructions (Windows) 
Use a compiler like MinGW (g++) or Microsoft Visual Studio to compile the code.
##Using g++ (MinGW)
```bash 
g++ -o snake_game snake_game.cpp -std=c++11
 ./snake_game
 ```
## Requirements
Windows OS (for windows.h and Beep function support)
C++ Compiler (MinGW g++, MSVC, or equivalent)
## Future Enhancements
Add more game modes (e.g., timed mode, survival mode).
Implement a graphical interface using SDL or SFML.
Add sound effects for eating food.
Implement a pause and resume feature.
## Author
This Snake game was developed as a fun project to practice C++ programming and game logic.
Enjoy the game!



