#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
/*
 InitBoard(b){
 //b[i][j]
 //ramdomly choose 2 empty slots
 int x1,y2,x2,y2
 //(x1,y1)&(x2,y2)
 x1 = rand()%4
 
 while(x1==x2&y1==y2){
 x1 = rand()%4
 x2 = rand()%4
 y1 = rand()%4
 y2 = rand()%4
 }
 
 if(rand%10 ==0){
 b[x1][y1]
 }
 else{
 b[x1][y1]
 }
 }
 
 UpdateCol(){
 //maintain readPos & writePos
 }
 Update(b,c){
 if(c == 'w'){
 updateCol(b,0,c);
 updateCol(b,1,c);
 updateCol(b,2,c);
 updateCol(b,3,c);
 }
 
 int main(){
 int b[4][4];
 Initboard(b);
 printboard(b); (HW1)
 read user input without enter (hint getch())
 char c = getch();
 if(c == 'w'){
 printf("Up");
 UpdateBoard(b,c);
 }
 else if(c=='s')
 PrintBoard(b);
 }
 */


char _getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
}

int main(){
    printf("please press any key\n");
    char c = _getch();
    printf("you just press %c\n", c);
    return 0;
}

