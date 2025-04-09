// sort_all_in_one.cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

// ----------- 隨機數生成 -----------
void generateRandomNumbers(vector<int>& arr, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand() % 50000 + 1);
    }
}

// ----------- Quick Sort -----------
int partition(vector<int>& arr, int low, int high, bool reverse) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[low]);
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while ((!reverse && arr[i] < pivot) || (reverse && arr[i] > pivot)) i++;
        while ((!reverse && arr[j] > pivot) || (reverse && arr[j] < pivot)) j--;
        if (i >= j) break;
        swap(arr[i], arr[j]);
        i++; j--;
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int low, int high, bool reverse) {
    if (low < high) {
        int pi = partition(arr, low, high, reverse);
        quickSort(arr, low, pi - 1, reverse);
        quickSort(arr, pi + 1, high, reverse);
    }
}

// ----------- Merge Sort -----------
void merge(vector<int>& arr, int left, int mid, int right, bool reverse) {
    int n1 = mid - left + 1, n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((!reverse && L[i] <= R[j]) || (reverse && L[i] >= R[j])) arr[k++] = L[i++];
        else arr[k++] = R[j++];
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

// ----------- Heap Sort -----------
void heapify(vector<int>& arr, int n, int i, bool reverse) {
    int target = i, left = 2 * i + 1, right = 2 * i + 2;
    if (!reverse) {
        if (left < n && arr[left] > arr[target]) target = left;
        if (right < n && arr[right] > arr[target]) target = right;
    } else {
        if (left < n && arr[left] < arr[target]) target = left;
        if (right < n && arr[right] < arr[target]) target = right;
    }
    if (target != i) {
        swap(arr[i], arr[target]);
        heapify(arr, n, target, reverse);
    }
}

void justify(vector<int>& arr, bool reverse) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i, reverse);
    }
}

void heapSort(vector<int>& arr, bool reverse) {
    int n = arr.size();
    justify(arr, reverse);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, reverse);
    }
}

// ----------- Main ----------
int main() {
    int n;
    char order, method;

    cout << "請輸入要產生的隨機數字數量: ";
    cin >> n;
    cout << "請輸入排序順序 (a: 遞增, d: 遞減): ";
    cin >> order;
    bool reverse = (order == 'd');

    cout << "請選擇排序方式: (q: Quick Sort, m: Merge Sort, h: Heap Sort): ";
    cin >> method;

    vector<int> arr;
    generateRandomNumbers(arr, n);

    auto start = chrono::high_resolution_clock::now();

    if (method == 'q') quickSort(arr, 0, arr.size() - 1, reverse);
    else if (method == 'm') mergeSort(arr, 0, arr.size() - 1, reverse);
    else if (method == 'h') heapSort(arr, reverse);
    else {
        cerr << "無效的排序方法。" << endl;
        return 1;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n排序時間: " << fixed << setprecision(8) << duration.count() << " 秒\n";

    if (n <= 1000) {
        ofstream outfile("sorted.txt");
        if (outfile.is_open()) {
            for (int num : arr) outfile << num << "\n";
            outfile.close();
            cout << "已儲存排序結果至 sorted.txt\n";
        } else {
            cerr << "無法開啟輸出檔案！\n";
        }
    }

    if (n > 1000) {
        cout << "排序後前15個元素:";
        for (int i = 0; i < 15 && i < arr.size(); ++i)
            cout << "\n" << arr[i];
        cout << endl;
    }

    return 0;
}
