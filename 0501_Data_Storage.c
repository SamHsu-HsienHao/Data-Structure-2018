#include <stdio.h>
void ChangeInputTo10_FAIL(int i);
void ChangeInputTo10(void* addr);
void ChangeInputTo10_V2(int* addr);
void ChangeInputTo10_V3(int addr);
void PrintArray(int arr[], int n);
void PrintArrayV2(int* addr, int n);
void PrintArrayV3(int* addr, int n);
void TestPassingArray();
void TestBadMemoryAccess();
void TestReturnArray();
int* Return12345_FAIL();
int* Return12345_V1();
int* Return1ton(int n);
void TestFreeMem();

void TestChangeInput() {
    int i = 6;
    ChangeInputTo10_FAIL(i);
    printf("%d\n", i);
    /*印出6
     ChangeInputTo10(i): copy i的值，
     之後再把copy的值傳給ChangeInputTo10
     */
    
    i = 6;
    ChangeInputTo10(&i); //input為i的記憶體位置。&variable: variable在記憶體的位置
    printf("%d\n", i);//目標：印出10
    i = 6;
    ChangeInputTo10_V2(&i); //input為i的記憶體位置。&variable: variable在記憶體的位置
    printf("%d\n", i);//目標：印出10
    i = 6;
    ChangeInputTo10_V3(&i); //input為i的記憶體位置。&variable: variable在記憶體的位置
    printf("%d\n", i);//目標：印出10
    
    
    return;
}

void ChangeInputTo10_FAIL(int i/*產生一個新的，只屬於ChangeInputTo10的變數i*/) {
    i = 10;
}

void ChangeInputTo10(void* addr/*Input 變數儲存某個變數的記憶體位置*/) {
    //記憶體中addr位置 儲存的值改為10
    //*addr = 10; //*addr: 存在記憶體位置addr的值
    //上面的code是錯的，因為電腦不知道addr存的變數型態
    
    * (int*)addr = 10;// (int*) addr: addr存的是一個int
}

void ChangeInputTo10_V2(int* addr/*Input 變數儲存某個int變數的記憶體位置*/) {
    //記憶體中addr位置 儲存的值改為10
    
    *addr = 10; //在input的地方已經告訴電腦addr存的是int的位置
}

void ChangeInputTo10_V3(int addr/*Input 變數儲存某個int變數的記憶體位置*/) {
    //記憶體中addr位置 儲存的值改為10
    
    *(int*)addr = 10; //在input的地方已經告訴電腦addr存的是int的位置
}

void PrintArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void PrintArrayV2(int* addr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", addr[i]); // addr[i] == *(addr+i) *(addr+4*i) is wrong
    }
    printf("\n");
}

void PrintArrayV3(int* addr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(addr + i));
    }
    printf("\n");
}

void TestPassingArray() {
    int arr[] = { 1,2,3,4,5 };
    PrintArray(arr, 5);
    PrintArray(/*addr of the first element of arr*/ &arr[0], 5);
    PrintArrayV2(arr, 5);
    PrintArrayV3(arr, 5);
    //arr == &arr[0]
}


void TestBadMemoryAccess() {
    int arr[] = { 1,2,3,4,5 };
    
    //    printf("%d\n", *(arr + 10));
    //存取array外面的element
    //(arr只有5個elements，但是我們想access第11個element)
}

void TestReturnArray() {
    PrintArray(Return12345_FAIL(), 5);
    PrintArray(Return12345_V1(), 5);
    
    int* arr = Return1ton(50000000);
    if (arr != NULL) {
        PrintArray(arr, 50000000);
    }
    //should print out 1 2 3 4 5
}

int* Return12345_FAIL() {
    int arr[] = { 1,2,3,4,5 };
    return arr; //&arr[0]
    //失敗，因為當Return12345_FAIL結束後，arr的空間會被釋放
}

int* Return12345_V1() {
    static int arr[] = { 1,2,3,4,5 };
    //static的變數不會因為function結束而被釋放
    return arr; //&arr[0]
}

int* Return1ton(int n) {
    int* arr = malloc(n * sizeof(int)); //sizeof(int): int所佔的byte數 = 4
    if (arr == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr; //&arr[0]
}

void TestFreeMem(){
    printf("before malloc\n");
    getchar();
    
    int* arr = malloc(sizeof(int)*50000000);
    if(arr == NULL){
        printf("malloc failed\n");
    }
    
    printf("after malloc\n");
    getchar();
    
    free(arr);
    printf("after free\n");
    getchar();
}

int main(void) {
    //TestChangeInput();
    //TestPassingArray();
    //TestBadMemoryAccess();
    //TestReturnArray();
    TestFreeMem();
    getchar();
    return 0;
}
