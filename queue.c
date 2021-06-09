#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct queue{
    L* l;
};

typedef struct queue Q;

int Dequeue(Q* q, int* hasData); //回傳q的第一個data，並刪除q的第一個data
N* Enqueue(Q* q, int data); //把data放到q的尾端，並回傳新產生的Node位置，若成功，回傳1，反之回傳0
Q* CreateEmptyQueue();
void RemoveQueue(Q* q);
void PrintQueue(Q* q);

Q* CreateEmptyQueue(){
    Q* q = malloc(sizeof(Q));
    if(q == NULL){
        return NULL;
    }
    L* l = CreateEmptyList();
    if(l == NULL){
        free(q);
        return NULL;
    }
    q -> l = l; //q的linked list(l) 設成list
    return q;
}

int Dequeue(Q* q, int* hasData){
    if(q -> l -> length == 0){
        *hasData = 0;
        return 0;
    }
    
    *hasData = 1;
    int data = q -> l -> head -> data;
    RemoveNode(q -> l, q -> l -> head);
    return data;
}

/*
 int hasData;
 int data = Dequeue(q, &hasData);
 
 if(hasData){
 print("first data is %d\n", data);
 }
 else{
 printf("Queue is empty\n");
 }
 */

N* Enqueue(Q* q, int data){
    if(AddDataEnd(q -> l, data) == NULL){
        return 0;
    }
    //AddDataEnd(q->l, data)在上面的if判斷是已經被執行過了，所以不需要再執行一次
    return 1;
}

void RemoveQueue(Q* q){
    RemoveList(q -> l);
    free(q); //一定要最後執行
}

void PrintQueue(Q* q){
    PrintList(q -> l);
}
