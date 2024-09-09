#include <iostream>

using namespace std ;

int main()
{
    int x, y ;
    cin >> x ; //字串數量
    cin >> y ; //字串長度
    
    string* arr = new string[x] ;
    
    cout << "請輸入" << x << "個字串" << endl ;
    for(int i = 0 ; i<x ; i++){
        cout << "輸入字串" << i+1 << " : " << endl ;
        cin >> arr[i] ;
        if(strlen(arr[i]) > y){
            
    }
    

    return 0;
}
