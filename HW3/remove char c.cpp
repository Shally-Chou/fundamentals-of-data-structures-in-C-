#include <iostream>
#include <string>

using namespace std;

class String {
private:
    string data;

public:
    String(const string& str) : data(str) {}    //詳情請洽前一題歐

    string CharDelete() const {
        string result;
        
        for (char del_char : data) {
            if (del_char != 'c') {    //in short,遇c略過
                result += del_char;
            }
        }
        
        return result;
    }
};

int main() {
    string str;
    cout << "input a string : ";
    getline(cin, str);    //詳情請洽前一題歐

    String myString(str);
    string newStr = myString.CharDelete();

    cout << "after deleting 'c' : " << newStr << endl;

    return 0;
}
