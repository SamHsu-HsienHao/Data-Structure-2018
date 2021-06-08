#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <> for grtting user input, _getchar for Mac user, go to https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
//google keyword: clear terminal C Mac

#define SIZEX 10
#define SIZEY 100


void PrintArr(int arr[], int n);

void BubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {     //i=0 找到最大的，i=1找到第二大的...
        for (j = 0; j < n - 1 - i; j++) { //當i=1，j<n-2，當j=n-3是倒數第三個，會跟n-2倒數第二個交換，n-1最後一個不需要換
            if (arr[j] > arr[j + 1]) {     //交換
                temp = arr[j];     //   temp 是一個變數
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                //就是下面的Swap
            }
            /*
            PrintArr(arr, n);
            getchar();
             */
        }
    }
}

int FindMaxPos(int arr[], int n){
    int max = arr[0];
    int maxPos = 0;
    
    for(int i=0; i<n; i++){
        if(arr[i] > max){
            max = arr[i];
            maxPos = i;
        }
    }
    return maxPos;
}
void Swap(int arr[], int post1, int post2){
    int temp = arr[post1];
    arr[post1] = arr[post2];
    arr[post2] = temp;
}
void MySort(int arr[],int n){
    for(int i=0; i<n; i++){
        int maxPos = FindMaxPos(arr, n-i); //find the positon of the max number between arr[0] and arr[n-i-1]
        Swap(arr, maxPos, n-i-1); //swap arr[maxPos] and arr[n-i-1]
    }
}

void InsertionSort(int arr[], int n) {
    int i, j;
    int temp;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        for (j=i-1; j>=0 && arr[j]>temp; j--) {
            arr[j + 1] = arr[j];
            //printf("     ");PrintArr(arr, SIZE);
            //getchar();
        }
        arr[j + 1] = temp;
        //PrintArr(arr, SIZE);
        //getchar();
    }
}

void PrintArr(int arr[], int n){
    for(int i = 0; i <n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}



int main(){
    int arr[SIZEX];
    srand(time(NULL));
    for(int i=0; i<SIZEX; i++){
        arr[i] = rand() % 100;
    }
    PrintArr(arr, SIZEX);
    getchar();
    InsertionSort(arr, SIZEX);
    PrintArr(arr, SIZEX);
    getchar();
    BubbleSort(arr, SIZEX);
    PrintArr(arr, SIZEX);
    MySort(arr, SIZEX);
    PrintArr(arr, SIZEX);
    getchar();
    
    int arr1[SIZEY], arr2[SIZEY], arr3[SIZEY];
    srand(time(NULL));
    for(int i=0; i<SIZEY; i++){
        arr1[i] = rand() % 100;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    clock_t start1 = clock();
    BubbleSort(arr1, SIZEY);
    clock_t end1 = clock();
    printf("BubbleSort: %f sec\n", (float)(end1-start1)/(CLOCKS_PER_SEC));
    
    clock_t start2 = clock();
    MySort(arr2, SIZEY);
    clock_t end2 = clock();
    printf("MySort: %f sec\n", (float)(end2-start2)/(CLOCKS_PER_SEC));
    
    clock_t start3 = clock();
    InsertionSort(arr3, SIZEY);
    clock_t end3 = clock();
    printf("InsertionSort: %f sec\n", (float)(end3-start3)/(CLOCKS_PER_SEC));
    
/*
    printf("please press any key\n");
    char c = _getch();
    printf("you just press %c\n", c);
 */
    
    getchar();
}
