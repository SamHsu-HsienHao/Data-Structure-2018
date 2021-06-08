#include <stdio.h> //for printf and getchar
#define ARRSIZE 85
#include <time.h>
#include <stdlib.h>

void PrintArr(int arr[], int n);
void InsertionSort(int arr[], int n);

/*
 Input:
 1. Two sorted arrays, arr1 and arr2
 2. The sizes of arr1 and arr2 are arr1Size and arr2Size, respectively
 Goal: Merge arr1 and arr2 in asending order and store the result to int result[]
 Key Idea:
 1. Create three variables, readPos1, readPos2, writePos.
 readPos1 is the current reading position of arr1
 readPos2 is the current reading position of arr2
 writePos is the current writing position of result
 * Use a for loop to decide the value to result[writePos], writePos = 0...n-1
 2. compare arr1[readPos1] and arr2[readPos2]
 3. Say arr1[readPos1] <= arr2[readPos2], store arr1[readPos1] in result[writePos]
 4. update readPos1 and writePos (readPos1++, writePos++)
 5. If readPos1 == arrSize1, simply copy the remaining elements in arr2 to result
 */
void Merge(int arr1[], int arr2[], int arr1Size, int arr2Size, int result[]){
    int writePos = 0, readPos1 = 0, readPos2 = 0;
    
    for(writePos = 0; writePos < arr1Size+arr2Size; writePos++){ //key idea
        if(arr1[readPos1]<=arr2[readPos2]){ //Key idea 2
            result[writePos] = arr1[readPos1]; //Key idea 3
            readPos1++; //key idea 4
            if(readPos1 == arr1Size){
                /* another choice
                 for (writePos++;writePos < arr1Size+arr2Size; writePos++)
                 */
                writePos++;
                for (;writePos < arr1Size+arr2Size; writePos++){ //(初始值，只做一次;看這裡有沒有成立;執行完執行這個)
                    result[writePos] = arr2[readPos2];
                    readPos2++;
                }
            }
        }
        else{
            result[writePos] = arr2[readPos2]; //key idea 3
            readPos2++; //key idea 4
            if(readPos2 == arr2Size){
                /* another choice
                 for (writePos++;writePos < arr1Size+arr2Size; writePos++)
                 */
                writePos++;
                for (;writePos < arr1Size+arr2Size; writePos++){ //(初始值，只做一次;看這裡有沒有成立;執行完執行這個)
                    result[writePos] = arr1[readPos1];
                    readPos1++;
                }
            }
        }
        
    }
}
    
void TestMerge(){
        int arr1[] = {2,4,6,8,10};
        int arr2[] = {1,3,5,7,9};
        int result[10];
        Merge(arr1, arr2, 5, 5, result);
        PrintArr(result, 10);
    }

void TestDivideArray(){
    int arr[] = {10,20,30,40,50,60,70,80};
    PrintArr(arr, 3); // should print 10 20 30. arr stores the adress of 10
    PrintArr(arr+2, 4); //arr+2 store the adress of 30
}

/*
 key idea:
 1.Divide arr[0...n-1] into arr[0...n/2-1] and arr[n/2...n-1]
 2. Apply merge sort on arr[0...n/2-1] and arr[n/2...n-1]
 3. Merge arr[0...n/2-1] and arr[n/2...n-1]
 */
// This implement is wrong as the function never ends, causing stack overflow

void MergeSortWrongVersion(int arr[], int n){
    MergeSortWrongVersion(arr, n/2); // key idea 1 & 2
    MergeSortWrongVersion(arr+n/2, n-n/2); // key idea 1 & 2
    
    int result[ARRSIZE]; //int result[n] is not valid in most C complilers
                         //assume n <= ARRSIZE
    Merge(arr, arr+n/2, n/2, n-n/2, result); //key idea 3
    
    for(int i = 0; i < n; i++){
        arr[i] = result[i];
    }
}

void TestWrongMergeSort(){
    int arr[] = {1,2};
    
    MergeSortWrongVersion(arr, 2);
}

void MergeSort(int arr[], int n){
    if(n <= 1){ /*instead of n==1, n<=1 is safer and more terminating conditions
                 for example, what if the arry originally has size 2 and then becomes size 0
                 */
        return;
    }
    
    MergeSort(arr, n/2); // key ideas 1 and 2
    MergeSort(arr+n/2, n-n/2); // key ideas 1 and 2
    
    static int result[ARRSIZE]; //int result[n] is not valid in most C complilers
                         //assume n <= ARRSIZE
                         //if a variable is static, this variable is created when a process starts, this variable will be reused in the future
    Merge(arr, arr+n/2, n/2, n-n/2, result); //key idea 3
    
    for(int i = 0; i < n; i++){
        arr[i] = result[i];
    }
}

void TestMergeSort(){
    int arr[] = {5,4,3,2,1};
    MergeSort(arr,5);
    PrintArr(arr,5);
}

void CompareSorting(){
    int arr1[ARRSIZE];
    int arr2[ARRSIZE];
    
    srand(time(NULL)); //use the current time as the starting point in the random table
    for(int i = 0; i < ARRSIZE; i++){
        arr1[i] = rand()%100; //generate a random integer from 0 to 99
        arr2[i] = arr1[i];
    }
    
    clock_t start1, end1, start2, end2;
    start1 = clock();  // current clock time
    InsertionSort(arr1, ARRSIZE);
    end1 = clock();
    
    printf("Insertion sort: %f sec\n", (double) (end1-start1)/ CLOCKS_PER_SEC);
    
    start2 = clock();
    MergeSort(arr2, ARRSIZE);
    end2 = clock();
    
    printf("Merge sort: %f sec\n", (double) (end2-start2)/ CLOCKS_PER_SEC);
}

void MergeSortPlus(int arr[], int n){
    if(n <= 8){
        InsertionSort(arr, n); // insertion sort is better than merge sort when n is small
        return;
    }
    
    MergeSort(arr, n/2); // key ideas 1 and 2
    MergeSort(arr+n/2, n-n/2); // key ideas 1 and 2
    
    static int result[ARRSIZE]; //int result[n] is not valid in most C complilers
    //assume n <= ARRSIZE
    //if a variable is static, this variable is created when the process
    //starts, this variable will be reused in the future
    Merge(arr, arr+n/2, n/2, n-n/2, result); //key idea 3
    
    for(int i = 0; i < n; i++){
        arr[i] = result[i];
    }
}

void CompareSorting2(){
    int arr1[ARRSIZE];
    int arr2[ARRSIZE];
    
    srand(time(NULL)); // use the current time as the starting point in the random table
    for(int i = 0; i < ARRSIZE; i++){
        arr1[i] = rand()%100; // generate a random integer from 0 to 99
        arr2[i] = arr1[i];
    }
    
    clock_t start1, end1, start2, end2;
    start1 = clock();  // current clock time
    MergeSortPlus(arr1, ARRSIZE);
    end1 = clock();
    
    printf("Merge sort plus: %f sec\n", (double) (end1-start1)/ CLOCKS_PER_SEC);
    //CLOCKS_PER_SEC number of clocks per second
    
    start2 = clock();
    MergeSort(arr2, ARRSIZE);
    end2 = clock();
    
    printf("Merge sort: %f sec\n", (double) (end2-start2)/ CLOCKS_PER_SEC);
}

int main() {
    CompareSorting2();
    getchar();
    CompareSorting();
    getchar();
    TestMergeSort();
    getchar();
    TestDivideArray();
    getchar();
    TestMerge();
    getchar();
    return 0;
}

// 之前寫過的

void InsertionSort(int arr[], int n) {
        int i, j;
        int temp;
        for (i = 1; i < n; i++) {
            temp = arr[i];
            for (j = i - 1; j >= 0 && arr[j]>temp; j--) {
                arr[j + 1] = arr[j];
                //printf("    ");PrintArr(arr, n);
                //getchar();
            }
            arr[j + 1] = temp;
            //PrintArr(arr, n);
            //getchar();
        }
    }
    
    
    
    
void PrintArr(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
}
