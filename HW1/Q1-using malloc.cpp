#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
    int x, y;
    cin >> x;   // 字串數量
    cin >> y;   // 字串長度

    char** arr = (char**)malloc(x * sizeof(char*));

    cout << "請輸入" << x << "個字串" << endl;
    for (int i = 0; i < x; i++) {
        arr[i] = (char*)malloc((y + 1) * sizeof(char));   //幫每個字串分內存

        cout << "輸入字串" << i + 1 << " : " << endl;
        cin >> arr[i];

        if (strlen(arr[i]) > y) {
            cout << "the length must < " << y << ", please enter again" << endl;
            free(arr[i]); 
            i--;
        }
    }

    for (int i = 0; i < x - 1; i++) {
        for (int j = 0; j < x - i - 1; j++) {
            if (arr[j][0] < arr[j + 1][0]) {
                char* temp = arr[j]; 
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp;  
            }
        }
    }

    cout << "You entered:" << endl;
    for (int i = 0; i < x; i++) {
        cout << arr[i] << endl;    //輸出字串
        free(arr[i]);    //釋放每個字串的內存
    }

    free(arr);    //釋放字串指標陣列的內存
  
    return 0;
}
