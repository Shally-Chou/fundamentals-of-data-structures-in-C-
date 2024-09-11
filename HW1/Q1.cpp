#include <iostream>
#include <string>

using namespace std ;

int main()
{
    int x, y ;
    cin >> x ;   //字串數量
    cin >> y ;   //字串長度
    
    string* arr = new string[x] ;
    
    cout << "請輸入" << x << "個字串" << endl ;
    for(int i = 0 ; i<x ; i++){
        cout << "輸入字串" << i+1 << " : " << endl ;
        cin >> arr[i] ;
        
        if( arr[i].length() > y){
            cout << "the lenth must < " << y << ",please enter again" << endl ;
            i-- ;
        }
    }
    
    for(int i=0 ; i<x-1 ; i++){   //不知道x-1哪來的就手寫試一遍就知道了
        for(int j=0 ; j<x-i-1 ; j++){    //最後一個是確定的所以就不用再排了
            if(arr[j][0] < arr[j+1][0]){
                swap(arr[j] , arr[j+1]) ;   //也可以設臨時變數來換，但這個比較快
            }
        }
    }
    
    cout << "You entered:" << endl;
    for (int i = 0; i < x; i++) {
        cout << arr[i] << endl;   //輸出字串
    }

    delete[] arr;
    
    return 0;
}
