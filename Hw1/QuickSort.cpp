/******************************************************************************
設pivot分兩半的那個
*******************************************************************************/
#include <iostream>    // 輸入輸出流操作(cout/cin)
#include <vector>      // 容器類別模板
#include <cstdlib>     // 亂數生成函式(rand/srand)
#include <ctime>       // 時間相關函式(time)
#include <chrono>      // 高精度時間測量
#include <fstream>     // 檔案流操作

using namespace std;

void generateRandomNumbers(vector<int>& arr, int n) {
    srand(time(0));    //用時間當亂數種子
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % 50000 + 1);    //用arr[i]=rand() % 50000 + 1的話要先給n個空間才能這樣搞 常用的但這裡會比較麻煩
    }
}

int partition(vector<int>& arr, int low, int high, bool reverse) {    //arr去引用 不用拷貝全部 讚
    int pivotIndex = low + rand() % (high - low + 1);    //先隨機選pviot 避免worst case happen(用三數中位數也行)
    swap(arr[pivotIndex], arr[low]);    //pivot放到最前面
    int pivot = arr[low];
    int i = low + 1;

    for (int j = low + 1; j <= high; ++j) {  
        if ((!reverse && arr[j] < pivot) || (reverse && arr[j] > pivot)) {  
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[low], arr[i - 1]);    //把pivot放回正確位置
    return i - 1;
}

void quickSort(vector<int>& arr, int low, int high, bool reverse) {
    if (low < high) {
        int pi = partition(arr, low, high, reverse);    //find pivot position
        quickSort(arr, low, pi - 1, reverse);    //pivot左邊做遞迴
        quickSort(arr, pi + 1, high, reverse);    //pivot右邊做遞迴
    }
}

int main() {
    int n;
    char order;
    cout << "請輸入要產生的隨機數字數量: ";
    cin >> n;
    cout << "請輸入排序順序 (a 表示遞增, d 表示遞減): ";
    cin >> order;
    bool reverse = (order == 'd');    //d=true遞減 a=false遞增

    vector<int> arr;
    generateRandomNumbers(arr, n);    //上去產生n個random num

    cout << "\n生成的數組前10個元素（共" << n << "個）: ";
    for (int i = 0; i < 10 && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    auto start = chrono::high_resolution_clock::now();    //clock()回傳的是CPU時間 如果同時在用其他東西會不準 但quicksort本身就用CPU算所以沒差多少
    quickSort(arr, 0, arr.size() - 1, reverse);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << duration.count() << " 秒" << endl;

    if(n<=1000){
        ofstream outfile("quick_sorted.txt");
        if (outfile.is_open()) {
            for (int num : arr) {
                outfile << num << "\n";
            }
            outfile.close();
            cout << "已儲存排序結果至 quick_sorted.txt" << endl;
        } 
        else {
            cerr << "無法開啟輸出檔案！" << endl;    //cerr可以馬上報錯 專門輸出錯誤訊息的 cout就只是輸出 可能有緩衝
        }
    }
    
    if (n <= 100) {
        cout << "排序後前10個元素: ";
        for (int i = 0; i < 10 && i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}

