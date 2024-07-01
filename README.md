# SP2-A3-Catan
Course - Systems Programming - Assignment 2 - Catan

# Catan Game Simulation

This C++ program simulates a simplified version of the popular board game Catan. It allows three players to interact with a game board, manage resources, trade with each other, and compete to achieve victory points.

## Features

- **Player Management**: Each player has a set of resources (WOOD, BRICK, WHEAT, WOOL, ORE), victory points, and can perform actions such as buying settlements and roads.
  
- **Game Board**: Tracks the state of the game board, including tiles, settlements, roads (and the position of the robber).

- **Development Cards**: Players can acquire and use development cards such as VICTORYPOINT, KNIGHT, ROADBUILDING, MONOPOLY, and YEAROFPLENTY to gain advantages.

- **Turn Management**: Implements a game loop where players roll dice, perform actions based on dice rolls, and handle special scenarios like rolling a 7 (sevenScenario function).

## Components

### Board Class (`Board`)
Manages the game state and operations related to the game board.

### Hexagon Class (`Hexagon`)
Represents a hexagonal tile on the game board.
  
### Edge Class (`Edge`)
Represents an edge on the game board.
  
### Vertex Class (`Vertex`)
Represents a vertex on the game board.

### Card Class (`Card`)
The `Card` class represents a card in the game.

### Piece Class (`Piece`)
The `Piece` class is an abstract class that represents a piece on the board. It has two subclasses: `Road` and `Settlement`.

#### Road Class (`Road`)
The `Road` class represents a road on the board.

#### Settlement Class (`Settlement`)
The `Settlement` class represents a settlement on the board.

### Player Class (`Player`)
Represents each player in the game, managing resources, actions, and development cards.

## Usage

1. **Compile**: Compile the program using the provided Makefile.
   ```bash
   make catan
2. **Run**: Run the program with three player names as command-line arguments.
   ```bash
   ./Catan player1_name player2_name player3_name
3. **Game Loop**: Follow the prompts to play the game, including rolling dice, managing resources, and making decisions.
4. **Winning**: The game ends when a player reaches 10 victory points. The player with the most victory points wins.



