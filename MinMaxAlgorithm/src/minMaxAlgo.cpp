#include <iostream>
#include <vector>

#define O 1
#define X -1

using namespace std;

int get(vector<vector<int>> &board, int x, int y){
    return board.at(y).at(x);
}

void set(vector<vector<int>> &board, int x, int y, int val){
    board.at(y).at(x) = val;
}

void printBoard(vector<vector<int>> &board){
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board.at(1).size(); j++){
            if(get(board, j, i) == -1){
                cout << "X" ;
            }
            if(get(board, j, i) == 1){
                cout << "O" ;
            }
            if(get(board, j, i) == 0){
                cout << "_" ;
            }
            
        }
        cout << "" << endl;
    }
}


int checkWin(vector<vector<int>> board){
    // 1 for O win | -1 for X win | 0 for draw | 2 for unfinished
    
    int sum;

    // check Column
    for(int i = 0; i < board.size(); i++){
        sum = get(board, 0, i) + get(board, 1, i) + get(board, 2, i);
        if(sum == 3){
            return 1;
        }
        if(sum == -3){
            return -1;
        }
    }

    // check Row
    for(int i = 0; i < board.size(); i++){
        sum = get(board, i, 0) + get(board, i, 1) + get(board, i, 2);
        if(sum == 3){
            return 1;
        }
        if(sum == -3){
            return -1;
        }
    }

    // check Diag1
    sum = get(board, 0, 0) + get(board, 1, 1) + get(board, 2, 2);
    if(sum == 3){
        return 1;
    }
    if(sum == -3){
        return -1;
    }
    
    sum = get(board, 2, 0) + get(board, 1, 1) + get(board, 0, 2);
    if(sum == 3){
        return 1;
    }
    if(sum == -3){
        return -1;
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(get(board, i, j) == 0){
                return 2;
            }
        }
    }
    
    return 0;
}

int optimise(vector<vector<int>> board, int currentMove, vector<int> &bestCoords){
    if(checkWin(board) == currentMove){
        return -10;
    }
    if(checkWin(board) == 0){
        return 0;
    }
    if(checkWin(board) == -1*currentMove){
        return 10;
    }
    
    vector<vector<vector<int>>> possiblePositions; 
    vector<vector<int>> coords;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(get(board, i, j) == 0){
                vector<vector<int>> newBoard(3, vector<int>(3, 0));
                newBoard = board;
                set(newBoard, i, j, currentMove);
                possiblePositions.push_back(newBoard);
                vector<int> currentCoords;
                currentCoords.push_back(i);
                currentCoords.push_back(j);
                coords.push_back(currentCoords);
            }
        }
    }
    
    int bestRating = -100;
    vector<int> blankCoords;

    for(int i = 0; i < possiblePositions.size(); i++){
        int current = optimise(possiblePositions.at(i), currentMove*(-1), blankCoords);
        if(current >= bestRating){
            bestRating = current;
            bestCoords = coords.at(i);
        }
        
    }

    return -1*bestRating;
    
}

int main(){
    vector<vector<int>> board(3, vector<int>(3, 0));

    vector<int> best;

    int move = -1;

    while(checkWin(board) == 2){
        
        cout << -1* optimise(board, move, best) << endl;

        set(board, best.at(0), best.at(1), move);

        move*=-1;

        printBoard(board);
        cout << "" << endl;
    }

    cout << checkWin(board) << endl;
}
