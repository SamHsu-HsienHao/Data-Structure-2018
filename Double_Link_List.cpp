#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

/*
 Doubly Linked List
 使用 cpp 實作 doubly linked list。
 需support:
 O(1) time AddDataFront:把資料加到 list 最前面
 O(1) time AddDataEnd:把資料加到 list 最後面
 O(1) time RemoveFront: 把 list 最前面的資料刪除
 O(1) time RemoveEnd:把 list 最後面的資料刪除
 
 Queue with Q.Max();
 使用 cpp 實作 queue 資料結構，
 其中 EnQueue 的 amortized time complexity 為 O(1)，DeQueue 的 time complexity 為 O(1)，Q.Max()在 O(1)時間內回傳 Q 中最大的數字。
 Hint:使用 Doubly Linked List。
 */

struct node{
    int data;
    struct node* pNext;
    struct node* pPre;
};
typedef struct node N;

struct list{
    N* head;
    N* tail;
    int length;
};
typedef struct list L;

L* CreateEmptyList();
N* AddDataFront(L* l, int data);
N* AddDataEnd(L* l, int data);
void RemoveFront(L* l);
void RemoveEnd(L* l);
void PrintList(L* l);

L* CreateEmptyList(){
    L* l = new(L);
    if(l == NULL){
        return NULL;
    }
    
    l -> head = NULL;
    l -> tail = NULL;
    l -> length = 0;
    
    return l;
}

N* AddDataFront(L* l, int data){
    if(l == NULL){
        printf("list does not exit\n");
        return NULL;
    }
    // 0.create a new node
    N* n = new(N);
    if(n == NULL){
        return NULL;
    }
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = l -> head;
    n -> pPre = NULL;
    
    // 3.Update list
    l -> head = n;
    if(l -> length == 0){
        l -> tail = n;
    }
    l -> length++;
    
    return n;
}

N* AddDataEnd(L* l, int data){
    if(l == NULL){
        printf("list does not exit\n");
        return NULL;
    }
    
    // 0.create a new node
    N* n = new(N);
    if(n == NULL){
        return NULL;
    }
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = NULL;
    n -> pPre = l -> tail;
    
    // 2.Update old nodes
    if (l->tail != NULL) {
        l->tail->pNext = n;
    }
    
    // 3.Update list
    if(l -> length == 0){
        l -> head = n;
    }
    l -> tail = n;
    l -> length++;
    
    return n;
}

void RemoveFront(L* l){
    if(l == NULL){
        printf("list does not exit\n");
        return;
    }
    
    N* n = l -> head;
    l -> head = l -> head -> pNext;
    l -> length--;
    
    free(n);
    
    return ;
}

void RemoveEnd(L* l){
    if(l == NULL){
        printf("list does not exit\n");
        return;
    }
    
    
    l -> tail = l -> tail -> pPre;
    free(l->tail->pNext);
    l->tail->pNext=NULL;
    l -> length--;
    
    
    return ;
}

void PrintList(L* l){
    if (l -> length == 0){
        printf("Empty List\n");
        return;
    }
    
    printf("data in head: %d, data in tail: %d, length: %d\n", l->head->data, l->tail->data, l->length);
    
    printf("%d", l -> head -> data);
    for(N* n = l->head->pNext;n != NULL;n = n->pNext){
        printf(" <-> %d", n->data);
    }
    printf("\n");
}



int IsInL(L* l, N* v){
    //return 1 if v is in L
    //return 0 if v is not in L
    
    for(N* n = l -> head; n != NULL; n = n -> pNext){
        if (n == v){
            return 1;
        }
    }
    return 0;
}

N* PreviousNode(L* l, N* v, int* isInL){
    //if v is in l, then *isInL = 1
    //otherwise, *isInL = 0
    
    if(IsInL(l, v) == 0){
        *isInL = 0;
        return NULL;
    }
    
    *isInL = 1;
    if(v == l->head){
        return NULL;
    }
    
    for(N* n = l->head; n != NULL; n = n->pNext){
        if(n -> pNext == v){
            return n;
        }
    }
    return NULL;
}

void RemoveNode(L* l, N* n){
    if(l == NULL){
        printf("list does not exit\n");
        free(n);
        return;
    }
    
    int isInL;
    N* prev = PreviousNode(l, n, &isInL);
    if(isInL == 0){
        free(n);
        return;
    }
    
    // 2.Update old nodes
    if(prev != NULL){
        prev -> pNext = n -> pNext;
    }
    //if prev == NULL, then v == l->head, 則不須update任何原有的node
    
    // 3.Update list
    if(n == l -> head){
        l -> head = n ->pNext;
    }
    if(n == l -> tail){
        l -> tail = prev;
    }
    l -> length--;
    
    // 1.Update the new nodes
    free(n);
    
    return ;
}

void RemoveList(L* l){
    //for loop call RemoveNode
    
    for(N* n = l->tail; n != NULL; n = l ->tail){
        RemoveNode(l, n);
    }
    free(l);
    return;
}



struct Queuepp {
    L* l;
    L* temp;
    
    int EnQueue(int data);
    /*
     struct Queuepp s;
     s.EnQueue(10);
     */
    int DeQueue(int* addrHasData);
    int Max();

    Queuepp(); //產生stackpp時會"自動"被呼叫
    ~Queuepp(); //stackpp"生命結束"時會"自動"被呼叫
};
typedef struct Queuepp Qpp;


Qpp::Queuepp() {//constructor
    l = NULL;
    temp = NULL;
    printf("start\n");
}

Qpp::~Queuepp() {//destructor
    if (l != NULL) {
        RemoveList(l);
    }
    if (temp != NULL) {
        RemoveList(temp);
    }
    printf("finish\n");
}

int Qpp::EnQueue(int data) {
    if (l == NULL) {
        l = CreateEmptyList();
    }
    if (temp == NULL) {
        temp = CreateEmptyList();
    }
    
    AddDataFront(l, data);
    if (temp->head == NULL) {
        AddDataFront(temp, data);
    }
    else {
        //如果目前max (temp第一筆data) > data
        //push 目前max到 temp
        //否則 push data到temp
        int oldMax = temp->head->data;
        if (oldMax > data) {
            AddDataFront(temp, oldMax);
        }
        else {
            AddDataFront(temp, data);
        }
    }
    
    return 1;
}

int Qpp::DeQueue(int* addrHasData) {
    int data = l->head->data;
    RemoveNode(l, l->head);
    RemoveNode(temp, temp->head);
    return data;
}
int Qpp::Max() {
    return temp->head->data;
}


int f() {
    Qpp s; //自動呼叫Spp::stackpp
    return 1; //自動呼叫Spp::~stackpp()
}





int main() {
    L*l = CreateEmptyList();
    PrintList(l);
    getchar();
    
    AddDataFront(l, 99);
    PrintList(l);
    getchar();
    
    AddDataEnd(l, 88);
    PrintList(l);
    getchar();
    
    AddDataFront(l, 77);
    PrintList(l);
    getchar();
    
    AddDataEnd(l, 66);
    PrintList(l);
    getchar();
    
    RemoveFront(l);
    PrintList(l);
    getchar();
    
    RemoveEnd(l);
    PrintList(l);
    getchar();
    
    RemoveFront(l);
    PrintList(l);
    getchar();
    
    RemoveEnd(l);
    PrintList(l);
    getchar();
    
    
    Qpp q;
    q.EnQueue(2);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.EnQueue(444);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.EnQueue(33);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.EnQueue(88888);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.EnQueue(5555);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.EnQueue(999999);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    
    getchar();
    
    int hasData;
    q.DeQueue(&hasData);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.DeQueue(&hasData);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.DeQueue(&hasData);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.DeQueue(&hasData);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    q.DeQueue(&hasData);
    PrintList(q.l);
    printf("max = %d\n", q.Max());
    
    getchar();
    
    return 0;
}
