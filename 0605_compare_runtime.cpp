#include <stdio.h>
#include <vector> //dynamic array
#include <list>
#include <unordered_map> //hash table
#include <map> //generalized sorted array
#include <algorithm>
#include <stdlib.h>

/*HW4
 1. (40%) 比較新增一筆資料平均所需時間 (總共新增10萬筆隨機資料)
 list, vector, map, unordered_map
 O(1), amortized O(1), O(log n), amortized O(1)
 2. (40%) (新增10萬筆隨機資料後)比較搜尋一筆資料平均所需時間 (總共搜尋10萬筆隨機資料)
 list, vector, map, unordered_map
 O(n), O(n), O(log n), O(1)
 3. (20%) 從<algorithm>中任選5個function，解釋該function作用，並給例子。
 */

unsigned long long Digest(int board[4][4]);

int main() {
    std::unordered_map<unsigned long long /*64 bits*/, int> H2;
    
    /*int board[4][4] = { { 2048, 512, 32, 16 },{ 0, 0, 16, 32 },{ 1024, 256, 16, 4 },{ 1024, 1024, 16, 32 } };
     printf("%llu\n", Digest(board));
     getchar();*/
    std::list<int> L; //L是一個容器，存int
    std::vector<int> V;
    /*generalized sorted array*/std::map<char /*key type*/, int /*value type*/> M;
    /*hash table*/std::unordered_map<unsigned long long /*key type*/, int /*value type*/> H;
    
    for (int i = 0; i < 10; i++) {
        L.push_back(i);
    }
    std::list<int>::iterator p = std::find(L.begin(), L.end(), 11);
    //從L的起點(L.begin())開始找，一直找到終點(L.end())，找11存不存在
    //把11的位置存在p裡
    
    if (p == L.end()) {
        printf("not found\n");
    }
    else {
        printf("found\n");
    }
    
    
    p = std::find(L.begin(), L.end(), 9);
    if (p == L.end()) {
        printf("not found\n");
    }
    else {
        printf("found\n");
    }
    
    
    
    for (int i = 0; i < 10; i++) {
        V.push_back(i);
    }
    std::vector<int>::iterator p2 = std::find(V.begin(), V.end(), 11);
    if (p2 == V.end()) {
        printf("not found\n");
    }
    else {
        printf("found\n");
    }
    
    
    p2 = std::find(V.begin(), V.end(), 9);
    if (p == L.end()) {
        printf("not found\n");
    }
    else {
        printf("found\n");
    }
    
    
    M['a'] = 10; //store key-value pair('a', 10) to M
    M['b'] = 11; //store key-value pair('b', 11) to M
    
    if (M.find('a') != M.end()) {
        printf("found\n");
    }
    else {
        printf("not found\n");
    }
    
    if (M.find('c') != M.end()) {
        printf("found\n");
    }
    else {
        printf("not found\n");
    }
    
    for (int i = 0; i < 10; i++) {
        H[i] = i * 20;
    }
    if (H.find(11) != H.end()) {
        printf("found\n");
    }
    else {
        printf("not found\n");
    }
    
    if (H.find(9) != H.end()) {
        printf("found\n");
    }
    else {
        printf("not found\n");
    }
    
    getchar();
}

int FastLog2(int a) {
    if (a == 0) {
        return 0;
    }
    
    int count = 0;
    while (a != 1) {
        a = a >> 1; // a的二進位表示往右shift 1 bit => a = a/2
        count++;
    }
    return count;
}

unsigned long long Digest(int board[4][4]) {
    unsigned long long h = 0;
    
    unsigned long long basis = 1;
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            int temp = FastLog2(board[i][j]);
            h += temp*basis;
            basis *= 16;
        }
    }
    
    return h;
}
