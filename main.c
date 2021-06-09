#include <stdlib.h>
#include <stdio.h>

struct node{
    int data;
    struct node* pNext; //pNext存下一個node的記憶體位置
}; // 設定一種變數型態 ex: int, double, ...

typedef struct node N;
// N n; n.data = 1; n.pNext = 10;
// struct node n; n.data = 1; n.pNext = 10;
// ------------ <-4
// | node = 1 |
// --------
// |pNext = 10|
// ------------
// ------------ <-10
// | node = ? |
// --------
// |pNext = ? |
// ------------

struct list{
    N* head; //list裡第一個node的address
    N* tail; //list裡最後一個node的address
    int length;
};

typedef struct list L;

L* CreateEmptyList(); //初始化，因為假設直接將前4個byte當head，後4個當tail，再後4個當length，若非0則有可能出錯
N* AddDataFront(L* l, int data); // intput 不能是L l，因為需要修改list的內容。N* 用來回傳data的node的addr
N* AddDataEnd(L* l, int data);
N* InsertDataFront(L* l, int data, N* n); //把data插在n前面
N* InsertDataBack(L* l, int data, N* n);
void RemoveNode(L* l, N* n);
void RemoveList(L* l);
void Printlist(L* l);



L* CreateEmptyList(){
    L* l = malloc(sizeof(L));
    if(l == NULL){
        return NULL;
    }
    //head = NULL
    //tail = NULL
    //length = 0
    
    l -> head = NULL; //(*l).head = NULL;
    l -> tail = NULL; //(*l).tail = NULL;
    l -> length = 0; //(*l).length = 0;

    return l;
}

void PrintList(L* l){
    if (l -> length == 0){
        printf("Empty List\n");
        return;
    }
    
    printf("data in head: %d, data in tail: %d, length: %d\n", l->head->data, l->tail->data, l->length);
    
    printf("%d", l -> head -> data);
    for(N* n = l->head->pNext;
        //n = list的第二個node的位置 (head的下一個Node的位置)
        n != NULL;
        //如果n是NULL，跳出for loop (所以不會印" -> %d")
        n = n->pNext
        // 印完" -> %d"後，找到下一個node的位置
        ){
        printf(" -> %d", n->data); // n->data: n存的data
    }
    printf("\n");
}

/*
 1.Update new node
 2.Update old nodes
 3.Update list
 */

N* AddDataFront(L* l, int data){
    if(l == NULL){
        printf("list does not exit\n");
        return NULL;
    }
    // 0.create a new node
    N* n = malloc(sizeof(N));
    if(n == NULL){
        return NULL;
    }
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = l -> head;
    
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
    N* n = malloc(sizeof(N));
    if(n == NULL){
        return NULL;
    }
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = NULL;
    
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
//永遠都要確定有沒有 "NULL->"，有的話會當掉


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

N* InsertDataBack(L* l, int data, N* v){
    if(IsInL(l, v) == 0){
        return NULL;
    }
    if(l == NULL){
        printf("list does not exit\n");
        return NULL;
    }
    
    // 0.create a new node
    N* n = malloc(sizeof(N));
    if(n == NULL){
        return NULL;
    }
    
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = v -> pNext;
    
    // 2.Update old nodes
    v -> pNext = n;
    
    // 3.Update list
    if(l -> tail == v){
        l -> tail = n;
    }
    l -> length++;
    
    return n;
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


N* InsertDataFront(L* l, int data, N* v){
    if(l == NULL){
        printf("list does not exit\n");
        return NULL;
    }
    int isInL;
    N* prev = PreviousNode(l, v, &isInL);
    if(isInL == 0){
        return NULL;
    }
    
    // 0.create a new node
    N* n = malloc(sizeof(N));
    if(n == NULL){
        return NULL;
    }
    
    // 1.Update the new nodes
    n -> data = data;
    n -> pNext = v;
    
    // 2.Update old nodes
    if(prev != NULL){
        prev -> pNext = n;
    }
    //if prev == NULL, then v == l->head, 則不須update任何原有的node
    
    // 3.Update list
    if(v == l -> head){
        l -> head = n;
    }
    l -> length++;
    
    return n;
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





int main(){
    L* l = CreateEmptyList();
    if(l == NULL){
        printf("CreateEmptyList failed\n");
        return 0;
    }
    
    PrintList(l);
    N* n = AddDataEnd(l, 1000);
    InsertDataBack(l, 100, n);
    InsertDataBack(l, 200, l->head);
    InsertDataBack(l, 300, l->tail);
    PrintList(l);
    getchar();
    
    RemoveList(l);
    PrintList(l);
    getchar();
    
    RemoveNode(l, l -> head);
    PrintList(l);
    RemoveNode(l, l -> head);
    PrintList(l);
    RemoveNode(l, l -> head);
    PrintList(l);
    RemoveNode(l, l -> head);
    PrintList(l);
    RemoveNode(l, l -> head);
    PrintList(l);
    getchar();

    N* n1 = AddDataEnd(l, 1000);
    InsertDataFront(l, 100, n1);
    InsertDataFront(l, 200, l->head);
    InsertDataFront(l, 300, l->tail);
    PrintList(l);
    getchar();
    
    for(int i = 0; i < 10; i++){
        AddDataFront(l, i);
        if(l == NULL){
            printf("AddDataFront failed\n");
            return 0;
        }
        PrintList(l);
    }
    
    for(int i = 0; i < 10; i++){
        N* n = AddDataEnd(l, i);
        if(n == NULL){
            printf("AddDataEnd failed\n");
            return 0;
        }
        PrintList(l);
    }
    getchar();
    
    return 0;
}
