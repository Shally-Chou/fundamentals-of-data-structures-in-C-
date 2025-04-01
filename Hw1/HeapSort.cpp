#include <iostream>    // 輸入輸出流操作(cout/cin)
#include <vector>      // 容器類別模板
#include <cstdlib>     // 亂數生成函式(rand/srand)
#include <ctime>       // 時間相關函式(time)
#include <chrono>      // 高精度時間測量
#include <fstream>     // 檔案流操作

using namespace std;

/**
 * 生成隨機數組
 * @param arr 目標vector容器(傳參考修改)
 * @param n   需要生成的數字數量
 */
void generateRandomNumbers(vector<int>& arr, int n) {
    srand(time(0));  // 用當前時間初始化亂數種子
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % 50000 + 1); // 生成1-50000的亂數
    }
}

/**
 * 堆排序堆化函式
 */
void heapify(vector<int>& arr, int n, int i, bool reverse) {
    int target = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (!reverse) { // 最大堆
        if (left < n && arr[left] > arr[target]) target = left;
        if (right < n && arr[right] > arr[target]) target = right;
    } else { // 最小堆
        if (left < n && arr[left] < arr[target]) target = left;
        if (right < n && arr[right] < arr[target]) target = right;
    }

    if (target != i) {
        swap(arr[i], arr[target]);
        heapify(arr, n, target, reverse);
    }
}

// 堆排序主體
void heapSort(vector<int>& arr, bool reverse) {
    int n = arr.size();

    for (int i = n/2 - 1; i >= 0; --i)
        heapify(arr, n, i, reverse);

    for (int i = n-1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, reverse);
    }
}

int main() {
    int n;
    char order;
    cout << "請輸入要產生的隨機數字數量: ";
    cin >> n;
    cout << "請輸入排序順序 (a 表示遞增, d 表示遞減): ";
    cin >> order;
    bool reverse = (order == 'd');

    vector<int> arr;
    generateRandomNumbers(arr, n);

    cout << "\n生成的數組前10個元素（共" << n << "個）: ";
    for (int i = 0; i < 10 && i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    auto start = chrono::high_resolution_clock::now();
    heapSort(arr, reverse);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << duration.count() << " 秒" << endl;

    // 寫入輸出檔案
    ofstream outfile("heap_sorted.txt");
    if (outfile.is_open()) {
        for (int num : arr) {
            outfile << num << "\n";  // 每個數字佔一行
        }
        outfile.close();
        cout << "已儲存排序結果至 heap_sorted.txt" << endl;
    } else {
        cerr << "無法開啟輸出檔案！" << endl;
    }

    // 只有當數量小於或等於100時才在終端機中打印排序後的數字
    if (n <= 100) {
        cout << "排序後前10個元素: ";
        for (int i = 0; i < 10 && i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "排序後所有元素:\n";
        for (int num : arr) {
            cout << num << "\n";  // 每個數字佔一行
        }
    }

    return 0;
}
