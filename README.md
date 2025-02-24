# Mancala AI with Minimax Algorithm

This is a C++ implementation of the classic board game Mancala, featuring an AI opponent that uses the Minimax algorithm with alpha-beta pruning to determine its moves. The game is played in the terminal, and the AI is designed to provide a challenging experience for the player.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [How to Play](#how-to-play)
- [Implementation Details](#implementation-details)
- [Future Improvements](#future-improvements)
- [Getting Started](#getting-started)

## Overview
Mancala is a strategic board game where players take turns moving seeds from one pit to another, with the goal of capturing as many seeds as possible in their scoring pit. This implementation allows a human player to compete against an AI opponent that uses the Minimax algorithm to make optimal moves.

## Features
- **Human vs AI Gameplay**: Play against an AI opponent that uses the Minimax algorithm.
- **Minimax Algorithm**: The AI uses the Minimax algorithm with alpha-beta pruning to determine the best move.
- **Simple Terminal Interface**: The game is played in the terminal with a simple text-based interface.
- **Game Rules Enforcement**: The game enforces Mancala rules, including capturing seeds and ending the game when appropriate.

## How to Play
1. **Starting the Game**: Run the program in a C++ environment.
2. **Player Moves**: When it's your turn, enter the number of the pit you want to move seeds from (1-6 for the left player).
3. **AI Moves**: The AI will automatically make its move when it's its turn.
4. **Winning the Game**: The game ends when one player has no more seeds in their pits. The player with the most seeds in their scoring pit wins.

## Implementation Details
- **Board Representation**: The game board is represented as a vector of integers, where each index corresponds to a pit or scoring pit.
- **Minimax Algorithm**: The AI uses the Minimax algorithm to evaluate possible moves and choose the one that maximizes its score while minimizing the player's score.
- **Alpha-Beta Pruning**: To optimize the Minimax algorithm, alpha-beta pruning is used to reduce the number of nodes evaluated.
- **Game Logic**: The game logic includes functions for making moves, capturing seeds, and checking for game-over conditions.

## Future Improvements
- **Bitboard Representation**: Implement a bitboard for more efficient game state representation.
- **Quiescence Search**: Add quiescence search to improve the AI's decision-making in volatile positions.
- **Transposition Table**: Implement a transposition table using Zobrist hashing to cache and reuse previously computed game states.
- **Improved Evaluation Function**: Enhance the scoring function to better evaluate board positions.

## Getting Started
1. Clone the repository:
   ```bash
   git clone https://github.com/AlexGundrum/Mancala-Engine
   ```
2. Compile C++ Code using C++ compiler (g++ for example):
   ```bash
    g++ -o mancala main.cpp
   ```
3. Run the executable:
   ```bash
   ./mancala
   ```
