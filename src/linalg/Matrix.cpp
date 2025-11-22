#include <iostream>  
#include <Windows.h>
using namespace std;

class Matrix {
public:
    unsigned int rows;
    unsigned int columns;
    void print() {
        cout << "rows: " << rows <<
        "\tcolumns: " << columns << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Matrix matrix;
    matrix.rows = 3;
    matrix.columns = 3;
    matrix.print();
}