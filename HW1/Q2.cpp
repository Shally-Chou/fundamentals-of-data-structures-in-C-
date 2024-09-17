#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    int x;
    cin >> x;    //共要輸出的名字數量
    cin.ignore();    //忽略前一行輸入緩衝區中保留的'/n'
    string* arr = new string[x];
    
    cout << "請輸入" << x << "個姓名 :" << endl;
    for(int i = 0 ; i < x ; i++){
        getline(cin, arr[i]);    //用getline才能get整行input cin遇到空格就停了
    }
    
    size_t num = 0;
    for(int i = 0 ; i < x ; i++){
        size_t len = arr[i].length();    //int是有符號整數 可出現負號 size_t可避免這個問題
        for(int j = 0 ; j < len ; j++){
            if(arr[i][j] == ' '){
                if(num < j){
                    num = j;
                }
            }
        }
    } //先判斷空格前有幾個char 跟最長的進行比較 取中間插  總長+差=setw
    
    cout << "output :" << endl;
    for(int i = 0 ; i < x ; i++){
        int len = arr[i].length();
        for(int j = 0 ; j < len ; j++){
            if(arr[i][j] == ' '){
                len += num-j;
                cout << setw(len) << arr[i] << endl;
            }
        }
    }
    
    delete[] arr;

    return 0;
}
