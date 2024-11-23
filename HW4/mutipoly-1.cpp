/******************************************************************************
input : 多項式項次(m、n)
input : coef & exp
output : poly1 & poly2
output : poly1 * poly2
output : 1 * 2 所耗時間
*******************************************************************************/
#include <iostream>
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
    Node* newNode = new Node(coef, exp);    //建新點
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

void com_same_term(Node*& head) {   //com=combine
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

void printPoly(Node* head) {
    while (head) {
        cout << head->coef << "x^" << head->exp;
        if (head->next) cout << " + ";
        head = head->next;
    }
    cout << endl;
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


int main()
{
    Node* poly1 = nullptr;
    Node* poly2 = nullptr;
    
    int m, n;
    cout << "enter the terms m : ";
    cin >> m;
    cout << "enter the terms n : ";
    cin >> n;
    
    if(m >= 10){
        int coef = 1, exp;
        for(int i = 0; i<m ; i++){
            exp = rand() % 51;
            insertNode(poly1, coef, exp);
        }
    }
    else{
        cout << "enter the coef & exp of m : " << endl;
        for (int i = 0; i<m; i++) {
            int coef, exp;
            cin >> coef >> exp;
            insertNode(poly1, coef, exp);
        }
    }
    
    if(n >= 10){
        int coef = 1, exp;
        for(int i = 0; i<n ; i++){
            exp = rand() % 51;
            insertNode(poly2, coef, exp);
        }
    }
    else{
        cout << "enter the coef & exp of n : " << endl;
        for (int i = 0; i<n; i++) {
            int coef, exp;
            cin >> coef >> exp;
            insertNode(poly2, coef, exp);
        }
    }
    
    cout << "poly1 : ";
    printPoly(poly1);
    cout << "poly2 : ";
    printPoly(poly2);
    
    clock_t start = clock(); 
    Node* result = multiPoly(poly1, poly2);
    clock_t end = clock();   

    cout << "poly1 * poly2 = ";
    printPoly(result);

    double execTime = double(end - start) / CLOCKS_PER_SEC;
    cout << "time resume of poly1 * poly2 = " << fixed << setprecision(6) << execTime << " s" << endl;

    return 0;
}
