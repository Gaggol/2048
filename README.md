# 2048 Game

This is a console-based implementation of the popular 2048 game written in C++. The game uses standard input for user interaction and displays the game board and score using wide character output. It is compatible with both Windows and Linux platforms.

## Table of Contents
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
- [How to Play](#how-to-play)

## Features
- Classic 2048 gameplay
- Simple, text-based user interface
- Handles input for moving tiles (W, A, S, D)
- Automatically adds a new tile after each valid move
- Detects game over condition
- Cross-platform support (Windows and Linux)

## Setup

### Prerequisites
- C++ compiler (e.g., g++ on Linux, MSVC on Windows)
- A terminal that supports UTF-8 encoding

### Compilation
To compile the program on different platforms, follow the instructions below:

#### Windows
```sh
g++ -o 2048_game 2048.cpp
```
#### Linux
```sh
g++ -o 2048_game 2048.cpp
```
## Running the Game
After compilation, run the game using:

```sh
./2048_game
```

## Usage
Once the game starts, you will see the initial game board with two tiles. Use the following keys to move the tiles:

- `W` - Move tiles up
- `A` - Move tiles left
- `S` - Move tiles down
- `D` - Move tiles right

The goal is to combine tiles with the same number to create larger numbers and ultimately create a tile with the number 2048.

## How to Play
Use the input keys (W, A, S, D) to move the tiles in the desired direction.
When two tiles with the same number collide, they merge into one tile with the sum of their values.
After each move, a new tile with a value of 2 or 4 will randomly appear on the board.
The game ends when there are no more possible moves, and the board is filled.