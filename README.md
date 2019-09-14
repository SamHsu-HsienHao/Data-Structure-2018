# Practice

#include <stdio.h>
#include <vector> //dynamic array
#include <list>
#include <unordered_map> //hash table
#include <map> //generalized sorted array
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <iostream>

    
int f(int x){
    return x;
}

struct node {
    int data;
    struct node* pNext; //pNext 存下一個 node 的記憶體位置
};

typedef struct node N;

struct list {
    N* head; //list 裡第一個 Node 的 address
    N* tail; //list 裡最後一個 Node 的 address
    int length;
};

typedef struct list L;

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

L* CopyLinkList(L* t, L* l){
    t -> head = l -> head;
    t -> tail = l -> tail;
    t -> length = l -> length;
    
    return t;
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

int IthData(L* l, int i) {
    if(i==1){
        return l -> head ->data;
    }
    
    else{
        L* t = CreateEmptyList();
        int j = 1;
        while(j<i){
        CopyLinkList(t, l);
        RemoveFront(t);
            j++;
        }
        return t -> head -> data;
    }
}





int main() {
    std::list<int> L1;
    for (int i = 0; i < 10; i++) {
        L1.push_back(i);
    }
    for (std::list<int>::iterator it = L1.begin(); it != L1.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
    getchar();
    
    std::list<int> L2;
    for (int i = 0; i < 10; i++) {
        L2.push_back(9-i);
    }
    for (std::list<int>::iterator it = L2.begin(); it != L2.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
    getchar();
    
    
    
    
    std::unordered_map<int, int> M; //M maps a student ID to a score
    M[100000] = 98;
    M[100002] = 99;
    M[100005] = 100;
    for (int id = 100000; id <= 100005; id++) {
        if (M.find(id) != M.end()) {
            printf("%d:%d\n", id, M[id]);
        } else {
            printf("%d: no such student\n", id);
        } }
    getchar();
    
    
    
    
    
    std::unordered_map<int, int> M2; //M maps a student ID to a score
    M2[100000] = 98;
    M2[100002] = 99;
    M2[100005] = 100;
    for (std::unordered_map<int, int>::iterator it = M2.begin(); it != M2.end(); it++) {
        printf("%d: %d\n", *it, M2[it -> first]);
    }
    getchar();
    
    
    
    
    
    std::vector<int> V;
    V.push_back(2);
    V.push_back(4);
    V.push_back(2);
    V.push_back(6);
    V.push_back(2);
    V.push_back(5);
    V.push_back(2);
    V.push_back(9);
    std::replace (V.begin(), V.end(), 2, 2000);
    for (int i = 0; i < V.size(); i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    getchar();
    
    
    
    int p = 5;
    f(p);
    printf("p = %d\n", p);
    getchar();
    
    
    
    L* l = CreateEmptyList();
    for (int i = 1; i <= 10; i++) {
        AddDataEnd(l, i);
    }
    printf("the first data in the list is %d\n", IthData(l, 1));
    printf("the second data in the list is %d\n", IthData(l, 2));
    printf("the fifth data in the list is %d\n", IthData(l, 5));
    getchar();
    return 0;
}
