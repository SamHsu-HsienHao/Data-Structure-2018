#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "myconio_mac.hpp"
#include <math.h>
#include <iostream>
#include <unordered_map> //hash table
#include <map> //generalized sorted array
#include <algorithm>
#define SIZE 4

void CopyBoard(int dst[4][4], int src[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

//return 1 if the contents of b1 and b2 are the same
//return 0 otherwise
int AreEqual(int b1[4][4], int b2[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b1[i][j] != b2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void PrintBoard(int board[4][4]) {
    for (int y = 0; y < 17; y++) {
        if (y % 4 == 0) {
            printf("*****************************\n");
        }
        else if (y % 4 == 1 || y % 4 == 3) {
            printf("*      *      *      *      *\n");
        }
        else {
            int i = y / 4;
            for (int j = 0; j < 4; j++) {
                printf("*");
                
                if (board[i][j] == 0) {
                    printf("      ");
                }
                else if (board[i][j] < 10) {
                    printf("   %d  ", board[i][j]);
                }
                else if (board[i][j] < 100) {
                    printf("  %d  ", board[i][j]);
                }
                else if (board[i][j] < 1000) {
                    printf("  %d ", board[i][j]);
                }
                else {
                    printf(" %d ", board[i][j]);
                }
            }
            printf("*\n");
        }
    }
    
    return;
}

//print the old board, the action, and the new board
void PrintGame(int oldBoard[4][4], int newBoard[4][4], char a) {
    PrintBoard(oldBoard);
    if (a == 'w') {
        printf("\n\nUp\n\n");
    }
    else if (a == 's') {
        printf("\n\nDown\n\n");
    }
    else if (a == 'd') {
        printf("\n\nRight\n\n");
    }
    else if (a == 'a') {
        printf("\n\nLeft\n\n");
    }
    PrintBoard(newBoard);
}

//return the number of 0s in the board
int GetNEmptyPos(int b[4][4]) {
    int count = 0;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] == 0) {
                count++;
            }
        }
    }
    
    return count;
}

int GenNewNumber() {
    int a;
    srand(time(NULL));
    a = rand() % 10;
    if(a == 1){
        return 4;
    }
    else{
        return 2;
    }
}

void InitBoard(int board[4][4]) {
    int initCol1, initRow1, initCol2, initRow2;
    initCol1 = rand() % 4;
    initRow1 = rand() % 4;
    
    initCol2 = rand() % 4;
    initRow2 = rand() % 4;
    
    while (initCol1 == initCol2 && initRow1 == initRow2) {
        initCol2 = rand() % 4;
        initRow2 = rand() % 4;
    }
    
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    
    board[initCol1][initRow1] = GenNewNumber();
    board[initCol2][initRow2] = GenNewNumber();
    
    return;
}


int UpdateIthColumn(int board[4][4], char a) {
    if(a=='w'){
        int  i,j,flag=-1;
        for (i=0;i<SIZE;i++){
            for (j=0;j<SIZE;j++){
                int  cell=board[i][j];
                if (cell!=0){
                    int  k=i+1;
                    while (k<SIZE){
                        int  nextcell=board[k][j];
                        if (nextcell!=0){
                            if (cell==nextcell){
                                flag=0;
                                board[i][j]+=board[k][j];
                                board[k][j]=0;
                            }
                            k=SIZE;
                            break ;
                        }
                        k++;
                    }
                }
            }
        }
        for (i=0;i<SIZE-1;i++){
            for (j=0;j<SIZE;j++){
                int  cell=board[i][j];
                if (cell==0){
                    int  k=i+1;
                    while (k<SIZE){
                        int  nextcell=board[k][j];
                        if (nextcell!=0){
                            flag=0;
                            board[i][j]=nextcell;
                            board[k][j]=0;
                            k=SIZE;
                        }
                        k++;
                    }
                }
            }
        }
        if (flag == -1)
            return  -1;
        else
            return  0;
    }
    if(a=='s'){
        int  i,j,flag=-1;
        for (i=SIZE-1;i>=0;i--){
            for (j=0;j<SIZE;j++){
                int  cell=board[i][j];
                if (cell!=0){
                    int  k=i-1;
                    while (k>=0){
                        int  nextcell=board[k][j];
                        if (nextcell!=0){
                            if (board[i][j]==board[k][j]){
                                flag=0;
                                board[i][j]+=board[k][j];
                                board[k][j]=0;
                            }
                            k=0;
                            break ;
                        }
                        k--;
                    }
                }
            }
        }
        for (i=SIZE-1;i>0;i--){
            for (j=0;j<SIZE;j++){
                int  cell=board[i][j];
                if (cell==0){
                    int  k=i-1;
                    while (k>=0){
                        int  nextcell=board[k][j];
                        if (nextcell!=0){
                            flag=0;
                            board[i][j]=nextcell;
                            board[k][j]=0;
                            k=0;
                        }
                        k--;
                    }
                }
            }
        }
        
        if (flag == -1)
            return  -1;
        else
            return  0;
    }
    else
        return 0;
}

int UpdateIthRow(int board[4][4], char a) {
    if(a=='a'){
        int  i,j,flag=-1;
        for (i=0;i<SIZE;i++){
            for (j=0;j<SIZE;j++){
                int  cell=board[i][j]; //cell表示當前元素
                if (cell!=0){
                    int  k=j+1;
                    while (k<SIZE){
                        int  nextcell=board[i][k];
                        if (nextcell!=0){
                            if (cell==nextcell){
                                flag=0; //相鄰兩個元素相同，就說明能移動，所以改變flag的值
                                board[i][j]+=board[i][k];
                                board[i][k]=0;
                            }
                            k=SIZE;
                            break ;
                        }
                        k++;
                    }
                }
            }
        }
        for (i=0;i<SIZE;i++){
            for (j=0;j<SIZE-1;j++){
                int  cell=board[i][j];
                if (cell==0){
                    int  k=j+1;
                    while (k<SIZE){
                        int  nextcell=board[i][k];
                        if (nextcell!=0){
                            flag=0;
                            board[i][j]=nextcell;
                            board[i][k]=0;
                            k=SIZE;
                        }
                        k++;
                    }
                }
            }
        }
        if (flag == -1)
            return  -1;
        else
            return  0;
    }
    if(a=='d'){
        int  i,j,flag=-1;
        for (i=0;i<SIZE;i++){
            for (j=SIZE-1;j>=0;j--){
                int  cell=board[i][j];
                if (cell!=0){
                    int  k=j-1;
                    while (k>=0){
                        int  nextcell=board[i][k];
                        if (nextcell!=0){
                            if (cell==nextcell){
                                flag=0;
                                board[i][j]+=board[i][k];
                                board[i][k]=0;
                            }
                            k=-1;
                            break ;
                        }
                        k--;
                    }
                }
            }
        }
        for (i=0;i<SIZE;i++){
            for (j=SIZE-1;j>0;j--){
                int  cell=board[i][j];
                if (cell==0){
                    int  k=j-1;
                    while (k>=0){
                        int  nextcell=board[i][k];
                        if (nextcell!=0){
                            flag=0; //當前元素為0，說明能移動，改變flag的值
                            board[i][j]=nextcell;
                            board[i][k]=0;
                            k=-1;
                        }
                        k--;
                    }
                }
            }
        }
        if (flag == -1)
            return  -1;
        else
            return  0;
    }
    else
        return 0;
}

int UpdateBoard(int board[4][4], char a) {
    if (a == 'w' || a == 's') {
        UpdateIthColumn(board, a);
        return UpdateIthColumn(board, a);
    }
    else{
        UpdateIthRow(board, a);
        return UpdateIthRow(board, a);
    }
    return 0;
}

int IsGameOver(int board[4][4]) {//initially, simply return 0 so that the game always continues
    
    //return 1 if the game is over
    //return 0 otherwise
    int  copy_board[SIZE][SIZE],i,j;
    /*為了避免直接把board[][]傳進move函數判斷的時候改變board，所以把board複製給
     另一個數組,然後判斷，這樣就不會改變board數組了
     */
    for (i=0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            copy_board[i][j]=board[i][j];
        }
    }
    if (UpdateIthColumn(copy_board,'w') == -1 && UpdateIthColumn(copy_board,'s') == -1 && UpdateIthRow(copy_board,'a') == -1 && UpdateIthRow(copy_board,'d') == -1) //如果四個移動函數都返回-1即不能移動GameOver
        return  1;
    else
        return  0;
}


//add a new number (by calling GenNewNumber()) to an empty slot
void AddNewNumber(int board[4][4]) {
    int nEmptyPos = GetNEmptyPos(board);
    
    int r = 1 + rand() % nEmptyPos; // generate a random number between 1 and nEmptyPos
    //add a new number to the rth empty slot
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                r--;
                if (r == 0) {
                    board[i][j] = GenNewNumber();
                    break;
                }
            }
        }
    }
}

int FastLog2(int i){
    int n = log2(i);
    return n;
}

int FastLog22(int a) {
    if (a == 0) {
        return 0;
    }
    
    int count = 0;
    while (a != 1) {
        a = a >> 1;
        count++;
    }
    return count;
}

unsigned long long Digest(int board[4][4]) {
    unsigned long long h = 0;
    
    unsigned long long basis = 1;
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            int temp = FastLog2(board[i][j]);
            h += temp*basis;
            basis *= 16;
        }
    }
    
    return h;
}

int CalScore(int b[4][4]) {
    int score = 0;
    std::unordered_map<unsigned long long, int> H;
    int x =0;

    if(H.find(Digest(b)) != H.end()){
        std::unordered_map<unsigned long long, int>::iterator p = H.find(Digest(b));
        score = H[p -> first];
        return score;
    }
    else{
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if (b[i][j] == 0){
                    x++;
                }
            }
        }
        return x;
    }
}

char AIGenNextMove(int b[4][4]) {
    char move = 'w'; //move = 'w', 's', 'a', or 'd'
    /*Your code goes here*/
    char movearr[4] = { 'w', 's', 'a', 'd' };
    char bestMove;
    int highestScore = -1;
    
    for (int i = 0; i < 4; i++) {
        int tempBoard[4][4];
        CopyBoard(tempBoard, b);
        
        
        UpdateBoard(tempBoard, movearr[i]);
        if (AreEqual(tempBoard, b)) {
            continue;
        }
        int score = CalScore(tempBoard);
        if (score >= highestScore) {
            highestScore = score;
            bestMove = movearr[i];
        }
    }
    
    return bestMove;
}




int main() {
    int board[4][4];
    int oldBoard[4][4];
    srand(time(NULL));
    InitBoard(board);
    PrintBoard(board);
    
    for (;;) {
        char c;
        
        /**********************set _2048AI = 0 to play 2048****************************/
        /********************set _2048AI = 1 to launch 2048 AI*************************/
        int _2048AI = 1;
        CopyBoard(oldBoard, board);

        
        if (!_2048AI) {
            c = getch();
            if (c != 'w' && c != 's' && c != 'a' && c != 'd') {
                printf("\n\n please press w, s, a, or d\n");
                continue;
            }
        }
        else {
            c = AIGenNextMove(oldBoard);
        }
        
        UpdateBoard(board, c);
        
        if (!AreEqual(board, oldBoard)) {
            AddNewNumber(board);
            system("cls");
            PrintGame(oldBoard, board, c);
        }
        
        if (IsGameOver(board)) {
            printf("\n\n Game Over!!\n\n");
            getchar();
        }
    }
    
    return 0;
}

