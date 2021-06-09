#include "list.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>

struct stackpp {
    L* l;
    L* temp;
    
    int Push(int data);
    /*
     struct stackpp s;
     s.Push(10);
     */
    int Pop(int* addrHasData);
    int Max();
    
    
    stackpp(); //產生stackpp時會"自動"被呼叫
    ~stackpp(); //stackpp"生命結束"時會"自動"被呼叫
};
typedef struct stackpp Spp;


Spp::stackpp() {//constructor
    l = NULL;
    temp = NULL;
    printf("start\n");
}

Spp::~stackpp() {//destructor
    if (l != NULL) {
        RemoveList(l);
    }
    if (temp != NULL) {
        RemoveList(temp);
    }
    printf("finish\n");
}

int Spp::Push(int data) {
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

int Spp::Pop(int* addrHasData) {
    int data = l->head->data;
    RemoveNode(l, l->head);
    RemoveNode(temp, temp->head);
    return data;
}
int Spp::Max() {
    return temp->head->data;
}


int f() {
    Spp s; //自動呼叫Spp::stackpp
    return 1; //自動呼叫Spp::~stackpp()
}


int main() {
    std::vector<int> second (4,100);
    
    for(int i = 0; i < second.size(); i++){
        printf("%d ", second[i]);
    }
    
    getchar();
    
    
    
    
    
    std::list<double> myList;
    for(double i = 0; i <= 1; i += 0.2){
        myList.push_back(i);
    }
    
    myList.pop_back();
    
    for (std::list<double>::iterator it=myList.begin(); it != myList.end(); ++it)
        printf("%f ", *it);
    
    getchar();
    
    
    
    
    
    Spp s;
    s.Push(2);
    printf("max = %d\n", s.Max());
    s.Push(4);
    printf("max = %d\n", s.Max());
    s.Push(6);
    printf("max = %d\n", s.Max());
    s.Push(8);
    printf("max = %d\n", s.Max());
    s.Push(3);
    printf("max = %d\n", s.Max());
    
    getchar();
    
    int hasData;
    s.Pop(&hasData);
    printf("max = %d\n", s.Max());
    
    s.Pop(&hasData);
    printf("max = %d\n", s.Max());
    
    s.Pop(&hasData);
    printf("max = %d\n", s.Max());
    
    s.Pop(&hasData);
    printf("max = %d\n", s.Max());
    
    getchar();
}
