#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("%d\n", IsLegal("({})[]{[()]}"));
    printf("%d\n", IsLegal("({[})[]{[()]]}"));
    getchar();
    
    S* s = CreateEmptyStack();
    
    for (int i = 0; i < 10; i++) {
        Push(s, i);
        PrintStack(s);
    }
    
    for (int i = 0; i < 10; i++) {
        int hasData;
        int data = Pop(s, &hasData);
        printf("data = %d\n", data);
        PrintStack(s);
    }
    getchar();
    
    Q* q = CreateEmptyQueue();
    
    for(int i = 0; i < 10; i++){
        Enqueue(q, i);
        PrintQueue(q);
    }
    
    for(int i = 0; i < 10; i++){
        int hasData;
        int data = Dequeue(q, &hasData);
        printf("data = %d\n", data);
        PrintQueue(q);
    }
    return 0;
}
