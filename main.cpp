#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;


/*
    ToDO:
    Implement bitboard for game representation.
    Implement alpha beta pruning in minimax.
    Make scoring function

    transposition table - Zobrist hashing
    Quiescence Search





 */

class Board{

public:
    vector<int> board_vector;
    // default constructor, standard board set-up
    Board(){
        board_vector = {0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4};
    }

    // copy constructor,
    Board(const Board& boardToBeCopied){
        for(int i = 0; i < 14; i++){
            board_vector.push_back(boardToBeCopied.board_vector[i]);
        }
    }


    void stealMove(int cellNum){
        //player1, left side, points go to bottom
        if(cellNum < 7){
            // adds the opposing bucket to counting bucket
            board_vector[7] += board_vector[14 - cellNum];
            //adds the one rock that got the steal
            board_vector[7] += 1;
            // sets opposing bucket to zero
            board_vector[14 - cellNum] = 0;
        }
        //player 2, right side, points go to top
        if(cellNum > 7){
            // adds the opposing bucket to counting bucket
            board_vector[0] += board_vector[14 - cellNum];
            //adds the one rock that got the steal
            board_vector[0] += 1;
            // sets opposing bucket to zero
            board_vector[14 - cellNum]  = 0;
        }
    }

    bool makeMove(bool isLeftTurn, int cellNum){
        int runningCount = board_vector[cellNum];
        int currentCell = ((cellNum + 1) % 14);
        board_vector[cellNum] = 0;
        if(isLeftTurn){
            while(runningCount > 1){
                if(currentCell == 13){
                    currentCell = 1;
                    board_vector[1] += 1;
                }else{
                    board_vector[currentCell] += 1;
                    currentCell++;
                }
                runningCount--;
            }
            // there is now one moving rock left, check if it lands in an empty spot on my side, or 7,
            //ends in counting bucket, return true;
            if(currentCell == 7){
                board_vector[7] += 1;
                return true;
            }
            // last rock falls on side, into empty cell, should steal opposing bucket.
            if(board_vector[currentCell] == 0 && currentCell < 7){
                stealMove(currentCell);
                return false;
            }

            // with the last rock, there is no steal or extra move, make it just regular.
            board_vector[currentCell] += 1;
            return false;

        }else{
            // RIGHT PLAYER'S TURN (CELL NUMS 8 - 13)

            while(runningCount > 1){
                if(currentCell == 13){
                    currentCell = 0;
                    board_vector[13] += 1;
                }else{
                    board_vector[currentCell] += 1;
                    currentCell++;
                }
                runningCount--;
            }
            // there is now one moving rock left, check if it lands in an empty spot on my side, or 7,
            //ends in counting bucket, return true;
            if(currentCell == 0){
                board_vector[0] += 1;
                return true;
            }
            // last rock falls on side, into empty cell, should steal opposing bucket.
            if(board_vector[currentCell] == 0 && currentCell > 7){
                stealMove(currentCell);
                return false;
            }

            // with the last rock, there is no steal or extra move, make it just regular.
            board_vector[currentCell] += 1;
            return false;

        }
    }

    void print(){
        cout << endl;
        cout << "    " << board_vector[0] << endl;
        cout << "1| " << board_vector[1] << " | " << board_vector[13] << " |13" << endl;
        cout << "2| " << board_vector[2] << " | " << board_vector[12] << " |12" << endl;
        cout << "3| " << board_vector[3] << " | " << board_vector[11] << " |11" << endl;
        cout << "4| " << board_vector[4] << " | " << board_vector[10] << " |10" << endl;
        cout << "5| " << board_vector[5] << " | " << board_vector[9] << " |9" << endl;
        cout << "6| " << board_vector[6] << " | " << board_vector[8] << " |8" << endl;
        cout << "    " << board_vector[7] << endl;

    }

    int evaluate(){
        return board_vector[7] - board_vector[0];
    }

    bool isGameOver(){
        return (board_vector[1] == 0 && board_vector[2] == 0 && board_vector[3] == 0 && board_vector[4] == 0 && board_vector[5] == 0 && board_vector[6] == 0) || (board_vector[8] == 0 && board_vector[9] == 0 && board_vector[10] == 0 && board_vector[11] == 0 && board_vector[12] == 0 && board_vector[13] == 0);
    }

    void gameOverCleanup(){
        //left side is empty, give right spots to top bucket
        if(board_vector[1] == 0 && board_vector[2] == 0 && board_vector[3] == 0 && board_vector[4] == 0 && board_vector[5] == 0 && board_vector[6] == 0){
            for(int i = 8; i < 13; i++){
                board_vector[0] += board_vector[i];
                board_vector[i] = 0;
            }
        }else{
            if((board_vector[8] == 0 && board_vector[9] == 0 && board_vector[10] == 0 && board_vector[11] == 0 && board_vector[12] == 0 && board_vector[13] == 0)){
                //right side is empty, give seeds to bottom bucket
                for(int i = 1; i < 7; i++){
                    board_vector[7] += board_vector[i];
                    board_vector[i] = 0;
                }
            }
        }

    }
};


int minimax(bool isMax, Board board, int depth){
    if(depth == 0){
        return board.evaluate();
    }
    if(board.isGameOver()){
        board.gameOverCleanup();
        return board.evaluate();
    }


    if(isMax){
        int maximum = -100000;
        int temp;
        for(int i = 1; i < 7; i++){
            if(board.board_vector[i] != 0){
                Board tempBoard(board);
                if(tempBoard.makeMove(true, i)){
                    temp = minimax(true, tempBoard, depth);
                }else{
                    temp = minimax(false, tempBoard, depth - 1);
                }
                maximum = max(temp, maximum);
            }
        }
        return maximum;
    }
    if(!isMax){
        int minimum = 1000000;
        int tempo;
        for(int i = 8; i < 14; i++){
            if(board.board_vector[i] != 0){
                Board tempBoard(board);
                if(tempBoard.makeMove(false, i)){
                    tempo = minimax(false, tempBoard, depth);
                }else{
                    tempo = minimax(true, tempBoard, depth-1);
                }
            }
            minimum = min(tempo, minimum);
        }

        return minimum;
    }
}

int findBestMove(Board b, bool isLeftSide){
    //because minimax just returns the score, we need to find which move
    //leads to the best (min/max) minimax return.
    int bestMoveIndex;
    int maxfound = -9999999;
    int minfound =  9999999;
    int temporaryScore;
    if(isLeftSide){
        //left side is making first move
        //this side is searching for the maximum value from minimax
        for(int i = 1; i < 7; i++){
            if(b.board_vector[i] != 0){
                Board temp(b);
                if(temp.makeMove(true, i)){
                    temporaryScore = minimax(true, temp, 6);
                }else{
                    temporaryScore = minimax(false, temp, 5);
                }
                if(temporaryScore > maxfound){
                    maxfound = temporaryScore;
                    bestMoveIndex = i;
                }
            }
        }
        cout << "For left player, max score found was : " << maxfound << " by move " << bestMoveIndex << endl;
        return bestMoveIndex;
    }else{
        //right side is making first move
        //this side is minimizing
        for(int i = 8; i < 14; i++){
            if(b.board_vector[i] != 0){
                Board temp(b);
                if(temp.makeMove(false, i)){
                    temporaryScore = minimax(false, temp, 6);
                }else{
                    temporaryScore = minimax(true, temp, 5);
                }
                if(temporaryScore < minfound){
                    minfound = temporaryScore;
                    bestMoveIndex = i;
                }
            }

        }
        cout << "For right player, min score found was : " << minfound << " by move " << bestMoveIndex << endl;
        return bestMoveIndex;
    }

}


int main() {
    Board gameboard;

    int userInput;
    bool leftTurn = true;
    int botBestMove;
    while(!(gameboard.isGameOver())){
        gameboard.print();
        if(leftTurn){
            userInput = -1;
            while (userInput < 1 ||userInput > 6){
                cout << "It is left player turn. What pit should move their seeds?" << endl;
                cin >> userInput;
                if (userInput < 1 || userInput > 6){
                    cout << "Invalid input. Please enter a pit number 1 - 6" << endl;
                }
            }
        }else{
            botBestMove = findBestMove(gameboard, false);
            userInput = botBestMove;
        }

        if(!(gameboard.makeMove(leftTurn, userInput))){
            leftTurn = !leftTurn;
        };
    }
    gameboard.gameOverCleanup();
    gameboard.print();
    cout << "Game over!";
    return 0;
}
