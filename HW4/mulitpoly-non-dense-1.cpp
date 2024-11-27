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
    ofstream outFile("non_dense_timing.txt");
    outFile << "Non-Dense Polynomial Multiplication Timing Results\n";
    outFile << "m\tn\texecTime\n";

    // Start with m = n = 5, and increase by 5 in each iteration
    for (int m = 5; m <= 100; m += 5) {
        Node* poly1 = nullptr;
        Node* poly2 = nullptr;

        // Non-Dense: 指數不連續
        for (int i = 0; i < m; ++i) {
            insertNode(poly1, 1, rand() % 50+1);  // 隨機生成多項式
        }
        for (int i = 0; i < m; ++i) {
            insertNode(poly2, 1, rand() % 50+1);  // 隨機生成多項式
        }

        // 計算多項式相乘
        clock_t start = clock();
        Node* result = multiPoly(poly1, poly2);
        clock_t end = clock();
        double execTime = double(end - start) / CLOCKS_PER_SEC;

        // 寫入檔案
        outFile << m << "\t" << m << "\t" << fixed << setprecision(6) << execTime << " s\n";

        // 清除記憶體
        delete poly1;
        delete poly2;
        delete result;
    }

    outFile.close();
    cout << "Non-Dense timing data has been saved to non_dense_timing.txt." << endl;

    return 0;
}
