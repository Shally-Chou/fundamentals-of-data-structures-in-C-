/******************************************************************************
先搞成heap tree, max or min看輸遞增還遞減 之後把top跟最後那個換位置 原top值就能排了 一直重複直到排完
*******************************************************************************/
#include <iostream>   
#include <vector>    
#include <cstdlib>   
#include <ctime>    
#include <chrono>   
#include <fstream> 
#include <iomanip>

using namespace std;

void generateRandomNumbers(vector<int>& arr, int n) {
    srand(time(0)); 
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % 50000 + 1);
    }
}

void heapify(vector<int>& arr, int n, int i, bool reverse) {
    int target = i;    //target就top 父節點
    int left = (2 * i) + 1;    //complete binary tree的左右點算法
    int right = (2 * i) + 2;

    if (!reverse) {    //max heap tree
        if (left < n && arr[left] > arr[target]) target = left;    //left超過堆的大小代表已經排完
        if (right < n && arr[right] > arr[target]) target = right;
    } 
    else {    //min heap tree
        if (left < n && arr[left] < arr[target]) target = left;
        if (right < n && arr[right] < arr[target]) target = right;
    }

    if (target != i) {    //i不是max/min時重排heap tree
        swap(arr[i], arr[target]);    //max/min為target 把target放到最上面的父節點i
        heapify(arr, n, target, reverse);    //重排heap tree
    }
}

void justify(vector<int>& arr, bool reverse) {
    int n = arr.size();
    for (int i = n/2 - 1; i >= 0; --i) {    //i是代表有子節點的node的數目=父節點的數目
        heapify(arr, n, i, reverse);
    }
}

void heapSort(vector<int>& arr, bool reverse) {
    int n = arr.size();

    justify(arr, reverse);

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
    cout << "請輸入排序順序 (a 表遞增, d 表遞減): ";
    cin >> order;
    bool reverse = (order == 'd');

    vector<int> arr;
    generateRandomNumbers(arr, n);

    auto start = chrono::high_resolution_clock::now();
    heapSort(arr, reverse);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << fixed << setprecision(8) << duration.count() << endl;

    if(n <= 1000){
        ofstream outfile("heap_sorted.txt");
        if (outfile.is_open()) {
            for (int num : arr) {
                outfile << num << "\n"; 
            }
            outfile.close();
            cout << "已儲存排序結果至 heap_sorted.txt" << endl;
        } 
        else {
            cerr << "無法開啟輸出檔案！" << endl;
        }
    }
    
    if (n > 1000) {
        cout << "排序後前15個元素: ";
        for (int i = 0; i < 15 && i < arr.size(); ++i) {
            cout << "\n" << arr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
