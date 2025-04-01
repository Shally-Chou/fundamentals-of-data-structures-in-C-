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
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if ((!reverse && L[i] <= R[j]) || (reverse && L[i] >= R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mergeSort(vector<int>& arr, int left, int right, bool reverse) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, reverse);
        mergeSort(arr, mid + 1, right, reverse);
        merge(arr, left, mid, right, reverse);
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
        for (int i = 0; i < 10 && i < arr.size(); ++i) {
            cout << arr[i] << "\n ";
        }
    }

    return 0;
}
