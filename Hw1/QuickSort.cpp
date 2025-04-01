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
 * 快速排序分割函式
 */
int partition(vector<int>& arr, int low, int high, bool reverse) {
    int pivotIndex = low + rand() % (high - low + 1); // 隨機選擇基準點
    swap(arr[pivotIndex], arr[high]);  // 將基準點移到最後
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if ((!reverse && arr[j] <= pivot) || (reverse && arr[j] >= pivot)) {
            i++;
            swap(arr[i], arr[j]);  // 交換符合條件的元素
        }
    }
    swap(arr[i + 1], arr[high]);  // 將基準點放到正確位置
    return i + 1;
}

// 快速排序遞迴主體
void quickSort(vector<int>& arr, int low, int high, bool reverse) {
    if (low < high) {
        int pi = partition(arr, low, high, reverse);
        quickSort(arr, low, pi - 1, reverse);
        quickSort(arr, pi + 1, high, reverse);
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
    quickSort(arr, 0, arr.size() - 1, reverse);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << duration.count() << " 秒" << endl;

    // 寫入輸出檔案
    ofstream outfile("quick_sorted.txt");
    if (outfile.is_open()) {
        for (int num : arr) {
            outfile << num << "\n";  // 每個數字佔一行
        }
        outfile.close();
        cout << "已儲存排序結果至 quick_sorted.txt" << endl;
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
