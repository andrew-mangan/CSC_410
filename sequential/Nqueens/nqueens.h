#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool isSafe(int board[], int row, int col) {
    for (int i = 0; i < col; i++) {
        if (board[i] == row || abs(board[i] - row) == abs(i - col)) {
            return false;
        }
    }
    return true;
}

void solveNQueensUtil(int board[], int col, int n) {
    // Base case

for (int r = 0; r < n; r++) 
    {
        for (int c = 0; c < n; c++)
            if(isSafe(board,r,c)==true)
                {
                    board[c] = r+1;
                    //printf("%d", board[c]);
                }
        printf("\n");
    }
    

    // Recursive case
        // write your code here
}