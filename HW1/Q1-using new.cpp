#include <iostream>
#include <string>

using namespace std;

int main() {
    int x, y;
    cin >> x;   // 字串數量
    cin >> y;   // 字串長度

    string* arr = new string[x];

    cout << "請輸入" << x << "個字串" << endl;
    for (int i = 0; i < x; i++) {
        cout << "輸入字串" << i + 1 << " : " << endl;
        cin >> arr[i];

        if (arr[i].length() > y) {
            cout << "the length must < " << y << ", please enter again" << endl;
            i--;
        }
    }

    for (int i = 0; i < x - 1; i++) {
        string* p1 = &arr[0]; 
        string* p2 = &arr[0] + 1; 

        for (int j = 0; j < x - i - 1; j++) {
            if ((*p1)[0] < (*p2)[0]) { 
                string temp = *p1;
                *p1 = *p2;
                *p2 = temp;
            }
            p1++;    // 移動 p1 指向下一個字串
            p2++;    // 移動 p2 指向下一個字串
        }
    }

    cout << "You entered:" << endl;
    for (int i = 0; i < x; i++) {
        cout << arr[i] << endl;    // 輸出字串
    }

    delete[] arr;

    return 0;
}
