#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits> // Добавляем для использования numeric_limits

using namespace std;

void swapColumns(vector<vector<int>>& matrix, vector<int>& columnLabels, int col1, int col2) 
{ 
    int rows = matrix.size(); 

    for (int i = 0; i < rows; ++i) 
    { 
        if (col1 != col2) 
        { 
            matrix[i][col1] ^= matrix[i][col2]; // Шаг 1: XOR первого столбца со вторым 
            matrix[i][col2] ^= matrix[i][col1]; // Шаг 2: Получаем значение второго столбца 
            matrix[i][col1] ^= matrix[i][col2]; // Шаг 3: Получаем значение первого столбца 
        } 
    }

    // Обмен нумерации столбцов
    swap(columnLabels[col1], columnLabels[col2]);
} 

void printMatrix(const vector<vector<int>>& matrix, const vector<int>& columnLabels) 
{ 
    // Печатаем нумерацию столбцов
    for (int label : columnLabels) {
        cout << setw(4) << label;
    }
    cout << endl;

    // Печатаем строки матрицы
    for (const auto& row : matrix) 
    { 
        for (int val : row) 
        { 
            cout << setw(4) << val; 
        } 
        cout << endl; 
    } 
} 

int getPositiveIntegerFromUser(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 1) {
            cin.clear(); // Сбрасываем состояние потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем неправильный ввод
            cout << "Пожалуйста, введите число не меньше 1." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Чистим ввод
            return value;
        }
    }
}

int main() 
{ 
    int n = getPositiveIntegerFromUser("Введите количество строк: ");
    int m = getPositiveIntegerFromUser("Введите количество столбцов: ");
    vector<vector<int>> a(n, vector<int>(m)); 
    vector<int> columnLabels(m);
    srand(static_cast<unsigned>(time(0))); // Используйте static_cast для обозначения типа

    // Заполняем матрицу случайными числами от 1 до n*m и задаем номера столбцов
    for (int i = 0; i < m; i++) {
        columnLabels[i] = i + 1; // Инициализация нумерации столбцов
    }

    for (int i = 0; i < n; i++) 
    { 
        for (int j = 0; j < m; j++) 
        { 
            a[i][j] = rand() % (n * m) + 1; // Генерация от 1 до n*m
        } 
    } 

    cout << "Оригинальная матрица" << endl; 
    printMatrix(a, columnLabels); 
    cout << endl; 

    for (int k = 1; k <= (m - 1) / 2 * 2; k += 2)
    { 
        int col1 = k; 
        int col2 = m - 1; 
        swapColumns(a, columnLabels, col1, col2); 
        for (int i = k + 1; i <= m - 1; i++) 
        { 
            int col1 = i;  
            int col2 = m - 1; 
            swapColumns(a, columnLabels, col1, col2); 
        } 
    } 

    cout << endl; 
    cout << "Изменённая матрица" << endl; 
    printMatrix(a, columnLabels);
    return 0; 
}