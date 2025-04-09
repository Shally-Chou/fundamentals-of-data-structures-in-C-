/******************************************************************************
兩個兩個比 直到匯聚成一個排好的(這要搞一個額外的空間)
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

void merge(vector<int>& arr, int left, int mid, int right, bool reverse) {
    int n1 = mid - left + 1;    //左長度
    int n2 = right - mid;    //右長度

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)    //copy一份因為等等會改到值
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;    //這裡的left是放進去區間的left

    while (i < n1 && j < n2) {    //只要裡面有東西
        if ((!reverse && L[i] <= R[j]) || (reverse && L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];    //如果其中一個已經放完就把剩的直接加到後面
    while (j < n2) arr[k++] = R[j++];
}


void mergeSort(vector<int>& arr, int left, int right, bool reverse) {    //arr需要先拆成單一元素 這樣才算排好了 mergesort只合併排好的
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, reverse);    //左遞迴
        mergeSort(arr, mid + 1, right, reverse);    //右遞迴
        merge(arr, left, mid, right, reverse);    //每層mergesort都會呼叫merge
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
    mergeSort(arr, 0, arr.size() - 1, reverse);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << fixed << setprecision(8) << duration.count() << endl;
    
    if(n<=1000){
        ofstream outfile("merge_sorted.txt");
        if (outfile.is_open()) {
            for (int num : arr) {
                outfile << num << "\n";
            }
            outfile.close();
            cout << "已儲存排序結果至 merge_sorted.txt" << endl;
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
    }

    return 0;
}
