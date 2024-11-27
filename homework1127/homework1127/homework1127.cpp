#include <iostream>
#include <string>
using namespace std;

// Term 類別
class Term {
    friend class Polynomial; // 允許 Polynomial 類別訪問其私有成員
private:
    float coef; // 係數
    int exp;    // 指數
};

// Polynomial 類別
class Polynomial {
private:
    Term* termArray; // 非零項的陣列
    int capacity;    // termArray 的大小
    int terms;       // 非零項的數量

    // 動態調整陣列大小
    void Resize(int newCapacity) {
        Term* newArray = new Term[newCapacity];
        for (int i = 0; i < terms; ++i) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }

public:
    // 預設建構子
    Polynomial() : termArray(new Term[1]), capacity(1), terms(0) {}

    // 解構子
    ~Polynomial() {
        delete[] termArray;
    }

    // 增加一個項
    void AddTerm(float coef, int exp) {
        if (terms == capacity) {
            Resize(2 * capacity); // 動態擴展陣列
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++;
    }

    // 多載輸入運算子 >>
    friend istream& operator>>(istream& input, Polynomial& poly) {
        int numTerms;
        cout << "請輸入非零項的數量: ";
        input >> numTerms;

        for (int i = 0; i < numTerms; ++i) {
            float coef;
            int exp;
            cout << "請輸入第 " << i + 1 << " 項的係數和指數 (格式: 係數 指數): ";
            input >> coef >> exp;
            poly.AddTerm(coef, exp);
        }

        return input;
    }

    // 多載輸出運算子 <<
    friend ostream& operator<<(ostream& output, const Polynomial& poly) {
        if (poly.terms == 0) {
            output << "0";
            return output;
        }

        for (int i = 0; i < poly.terms; ++i) {
            if (i > 0 && poly.termArray[i].coef > 0) {
                output << " + ";
            }
            if (poly.termArray[i].coef < 0) {
                output << " - ";
            }
            output << abs(poly.termArray[i].coef);
            if (poly.termArray[i].exp != 0) {
                output << "x^" << poly.termArray[i].exp;
            }
        }

        return output;
    }
};

int main() {
    Polynomial p1;

    cout << "輸入多項式:" << endl;
    cin >> p1;

    cout << "多項式為: " << p1 << endl;

    return 0;
}
