#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct stack{
    L* l;
};

typedef struct stack S;

int Push(S* s, int data);
int Pop(S* s, int* addrHasData);
S* CreateEmptyStack();
void RemoveStack(S* s);
void PrintStack(S* S);
int Top(S* s, int* addrHasData);
int IsEmpty(S* s);
int IsLegal(char* str);

S* CreateEmptyStack(){
    S* s = malloc(sizeof(S));
    if (s == NULL) {
        return NULL;
    }
    
    L* list = CreateEmptyList();
    if (list == NULL) {
        free(s);
        return NULL;
    }
    
    s->l = list; //q的linked list(l) 設成list
    return s;
}

void RemoveStack(S* s) {
    RemoveList(s->l);
    free(s);//一定要最後執行
}

void PrintStack(S* s) {
    PrintList(s->l);
}

int Push(S* s, int data){
    if (AddDataFront(s->l, data) == NULL) {
        //如果呼叫AddDataEnd把data放在tail，pop就要把tail刪掉，需要O(n)時間
        return 0;
    }
    //AddDataFront(s->l, data)在上面的if判斷是已經被執行過了，所以不需要再執行一次
    return 1;
}

int Pop(S* s, int* addrHasData){
    if (s->l->length == 0) {
        *addrHasData = 0; //把0存在記憶體位置為addrHasData的地方
        return 0;
    }
    
    *addrHasData = 1;
    int data = s->l->head->data;
    RemoveNode(s->l, s->l->head);
    
    
    return data;
}

int Top(S* s, int* addrHasData){
    if (s->l->length == 0) {
        *addrHasData = 0; //把0存在記憶體位置為addrHasData的地方
        return 0;
    }
    
    *addrHasData = 1;
    return s->l->head->data;
}

int IsEmpty(S* s){
    if(s->l->length == 0){
        return 1;
    }
    
    return 0;
}


int IsLegal(char* str){
    S* s = CreateEmptyStack();
    int hasData = 0;
    int result = 1;
    
    for(int i = 0; i < strlen(str); i++){
        char c = str[i];
        
        if(c == '(' || c == '[' || c == '{'){
            Push(s, (int) c);
        } else if(c == ')'){
            if(Top(s, &hasData) != (int)'('){
                result = -1;
                break;
            } else{
                Pop(s, &hasData);
            }
        } else if(c == ']'){
            if(Top(s, &hasData) != (int)'['){
                result = -1;
                break;
            } else{
                Pop(s, &hasData);
            }
        } else if(c == '}'){
            if(Top(s, &hasData) != (int)'{'){
                result = -1;
                break;
            } else{
                Pop(s, &hasData);
            }
        }
    }
    
    if(result == -1){
        RemoveStack(s);
        return -1;
    }
    if(!IsEmpty){
        RemoveStack(s);
        return -1;
    }
    
    RemoveStack(s);
    return 1;
}
