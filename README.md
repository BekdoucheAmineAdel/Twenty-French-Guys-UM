# Twenty-French-Guys-UM
Twenty French Guys is a C/C++ replica of the original Twenty game by Stephen French. Developed as part of the Informatique Industrielle course at the University of Montpellier (2023), this project was a hands-on exercise in low-level programming, logic design, and game mechanics. 
## Table of Contents
- About the Game
- Features
- Getting Started
- How to Play
- Project Structure
- Technical Details
- Contributors
- License
## About the Game
The original "Twenty" is a tile-matching, number-combining puzzle game. Players must merge tiles with the same number, incrementing their value, and ultimately aim to create a tile with the number twenty. The game is easy to pick up but becomes challenging as the board fills up and higher numbers are harder to achieve.
- Official website: twenty.frenchguys.net
- Game variations: Zen, Bubbles, Flip-Flop, Panic, and more.
## Features
- Faithful logic adaptation of the original "Twenty" game
- Written in C++ (88.2%) and C (11.8%)
- Modular codebase for clarity and educational value
- Designed for single-player mode (extendable)
## Getting Started
1. Clone the repository
```
git clone https://github.com/BekdoucheAmineAdel/Twenty-French-Guys-UM.git
cd Twenty-French-Guys-UM
```
2. Build the project
Compile manually (example for main.cpp):
```
g++ -o twenty main.cpp
```
3. Run the executable
```
./bin/Release/
```
## How to Play
The game board consists of numbered tiles.
Combine tiles of the same value to create a higher value tile.
Your objective: create a tile with the number twenty.
The board fills up quickly; plan your moves and merges carefully!
When the board is full and no more moves are possible, the game ends.
For details on the original game and its variations, visit twenty.frenchguys.net.
## Project Structure
Below is a partial file/folder structure (see the repository on GitHub for the complete list):
```
.
├── Icon.ico						# Game icon
├── README.md
├── Twenties a game of numbers.cbp
├── Twenties a game of numbers.depend
├── Twenties a game of numbers.layout
├── audio_controller/                   # Audio control source files
├── background.wav						          # Game sound
├── bin/                                # Compiled binaries
├── fusion.wav							            # Adding squares sound
├── game_settings.cpp
├── game_settings.h
├── grid_src_files/                     # Grid/game logic source files
├── hs.txt								              # Highest score is stored in this file
├── icon.rc
├── level_manager_src_files/            # Level management logic
├── loaders_src_files/                  # File/data loading logic
├── main.cpp
├── obj/                                # Object files
├── square_src_files/                   # Tile/square mechanics
├── squares.bmp							            # Games graphics
├── user_interactions_src_files/        # UI/user input logic
```
## Technical Details
- Languages: C++, C
- Platform: Windows
- Dependencies: FreeGlut, portaudio, sndfile
- Development context: University of Montpellier, Informatique Industrielle course (2023)
## Contributors
Bekdouche Amine
## License
This project is intended for educational use as part of university coursework.
If you wish to use or extend this project, please credit the original author and the University of Montpellier.
