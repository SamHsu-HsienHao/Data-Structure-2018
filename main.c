#include<stdio.h>

void Cap1(char str[]){
    for(int i = 0; str[i] != '\0'; i++){
        // check if str[i] is a lower case char
        if(str[i]>= 'a'/*97*/ && str[i]<='z'/*122*/){ // && = 而且
            //convert str[i] to the upper case
            str[i] -= 32;
        }
    }
}

void Cap2(char str[]){
    char CAPLETTER[26];
    for(int i = 0; i< 26; i++){
        CAPLETTER[i] = i +'A';
    }
    for(int i = 0; str[i] != '\0'; i++){
        // check if str[i] is a lower case char
        if(str[i]>= 'a'/*97*/ && str[i]<='z'/*122*/){ // && = 而且
            //convert str[i] to the upper case
            str[i] = CAPLETTER [str[i] - 'a'];
        }
     }
}

int main(){

    
    char ch = 't';
    char str[] = "Hello World"; //""最後面會加一個\0 會多佔一個空間
    char str2[1] = {'t'};
    
    printf("%s\n", str);
    printf("%s\n", str2);
    getchar();
    
    char str3[] = "Hello World!!! 2018";
    printf("before: %s\n", str3);
    Cap2(str3);
    printf("after: %s\n", str3);
    getchar();
    
    return 0;
}

/*
int main() {
 
 printf("1\n");
 int i, num, len = 0;
 
 printf("2\n");
 
 while(scanf("%d",&num) != EOF){ //scanf 把user的input 存在num裡面
 
 printf("num = %d\n", num);
 
 for(i=2; i<num; i++){
 while(num % i == 0){ //餘數為0，代表i為num的因數
 num/=i; //num = num/i
 len++;
 printf("i = %d, num = %d\n", i, num);
 }
 
 printf("    num = %d\n", num);
 
 if(len!=0){
 if(num==1){ //num為i因數的len倍
 printf("%d^%d\n",i,len);
 }
 else if(len==1){
 printf("%d * ",i);
 }
 else{
 printf("%d^%d * ",i,len);
 }
 len=0;
 }
 }
 if(num==1){
 //num 不是質數
 }
 else{
 printf("%d\n",i); // num 是質數
 }
 }
 
 printf("4\n");
 getchar();
}
*/
