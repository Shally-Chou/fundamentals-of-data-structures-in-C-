#include <iostream>

using namespace std;

class Quadratic {
private:
    double a, b, c;    //係數

public:
    //Q1
    Quadratic() : a(0), b(0), c(0) {}    //初始化她的值，沒給input就用她

    Quadratic(double a, double b, double c) : a(a), b(b), c(c) {}    //input對應

    //Q2
    Quadratic operator+(const Quadratic& other) const {    //const 前面保護poly2 後面保護1
        return Quadratic(a + other.a, b + other.b, c + other.c);
    }

    //Q3
    friend ostream& operator<<(ostream& out, const Quadratic& poly) {    //跟電腦解釋怎麼輸出字定義的東西
        out << poly.a << "x^2 ";  
        if (poly.b >= 0) out << "+ " << poly.b << "x ";
        else out << "- " << -poly.b << "x ";

        if (poly.c >= 0) out << "+ " << poly.c;
        else out << "- " << -poly.c;
        return out;
    }

    friend istream& operator>>(istream& in, Quadratic& poly) {    //read input
        cout << "Enter coefficient a: ";
        in >> poly.a;
        cout << "Enter coefficient b: ";
        in >> poly.b;
        cout << "Enter coefficient c: ";
        in >> poly.c;
        return in;
    }

    //Q4 
    
    double getA() const { return a; }    //才能訪問private 封裝性的東西
    double getB() const { return b; }
    double getC() const { return c; }
    
    double Eval(double x) const {    //X代入算
        return (a * x * x) + (b * x) + c;
    }
};

int main() {
    Quadratic poly1, poly2;

    cin >> poly1;
    cin >> poly2;

    Quadratic result = poly1 + poly2;
    cout << "多項式和 : " << result << endl;

    double x;
    cout << "輸入 x 的代入值式 : ";
    cin >> x;

    double value = result.Eval(x);    //use get就不用result.a這樣 也不會error(訪問到private)
    cout << "當 x = " << x << " 時，y =  " << value << endl;

    return 0;
}
