#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Node {
    int coef;
    int exp;
    Node* next;

    Node(int c, int e) : coef(c), exp(e), next(nullptr) {}
};

void insertNode(Node*& head, int coef, int exp) {
    Node* newNode = new Node(coef, exp);
    if (!head || head->exp < exp) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next && temp->next->exp >= exp) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void com_same_term(Node*& head) {
    Node* current = head;
    while (current && current->next) {
        if (current->exp == current->next->exp) {
            current->coef += current->next->coef;
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

Node* multiPoly(Node* poly1, Node* poly2) {
    Node* result = nullptr;
    for (Node* p1 = poly1; p1; p1 = p1->next) {
        for (Node* p2 = poly2; p2; p2 = p2->next) {
            int coef = p1->coef * p2->coef;
            int exp = p1->exp + p2->exp;
            insertNode(result, coef, exp);
        }
    }
    com_same_term(result);
    return result;
}

int main() {
    ofstream outFile("dense_timing.txt");
    outFile << "Dense Polynomial Multiplication Timing Results\n";
    outFile << "m\tn\texecTime\n";

    for (int m = 10; m <= 100; m += 10) {
        for (int n = 10; n <= 100; n += 10) {
            Node* poly1 = nullptr;
            Node* poly2 = nullptr;

            // Dense: 指數連續
            int startExp1 = rand() % 50 + 1;  // 第一個多項式的起始指數
            for (int i = 0; i < m; ++i) {
                insertNode(poly1, 1, startExp1--);  // 每次指數減 1
            }
            int startExp2 = rand() % 50 + 1;  // 第二個多項式的起始指數
            for (int i = 0; i < n; ++i) {
                insertNode(poly2, 1, startExp2--);
            }

            // 計算多項式相乘
            clock_t start = clock();
            Node* result = multiPoly(poly1, poly2);
            clock_t end = clock();
            double execTime = double(end - start) / CLOCKS_PER_SEC;

            // 寫入檔案
            outFile << m << "\t" << n << "\t" << fixed << setprecision(6) << execTime << " s\n";

            // 清除記憶體
            delete poly1;
            delete poly2;
            delete result;
        }
    }

    outFile.close();
    cout << "Dense timing data has been saved to dense_timing.txt." << endl;

    return 0;
}
