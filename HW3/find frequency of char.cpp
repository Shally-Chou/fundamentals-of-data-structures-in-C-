#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class String {
private:
    string data;

public:
    String(const string& str) : data(str) {}    //跟前一個一樣避免修改到+高效率

    void Frequency() const {    //主要func 只能說const很好用(但沒有也行辣就是有點風險)
        unordered_map<char, int> Ans_freq;    //不要求排列就不用map 而且她效率高 所以不要沒事找事不然寫得好累QQ

        for (char ch : data) {
            Ans_freq[ch]++;
        }

        for (const auto& pair : Ans_freq) {    //auto會根據Ans_freq推pair
            cout << "the frequency of Character '" << pair.first << "' is " << pair.second << endl;
        }
    }
};

int main() {
    string input;
    cout << "請輸入一個字串: ";
    
    getline(cin, input);        //跟HW1一樣 不然遇空格會GG

    String str(input);
    str.Frequency();

    return 0;
}
