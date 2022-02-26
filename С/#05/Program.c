#include <stdio.h>

void cheaked_input(char str1[256], int i, char str2[256], char str3[256], int j, char str4[256], int* p) { // функция для записи значения по указателю с проверкой на корректность ввода
    char string[256];
    printf("%s%d%s%s%d%s", str1, i, str2, str3, j, str4);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s%s%d%s", str1, i, str2, str3, j, str4);
        fgets(string, sizeof(string), stdin);
    }
}

void input_in_array(int* B, int rows, int columns) { //функция ввода чисел в матрицу
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            cheaked_input("Input number B[", i, "]", "[", j, "] = ", (B + i * columns + j)); printf("\r");
        printf("\n");
    }

}

void print_array(int* B, int rows, int columns) { // функцию вывода элементов матрицу
    printf("\nElements of matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%d  ", *(B + i * columns + j));
        printf("\n");
    }
}

void find(int* B, int rows, int columns) { // функция ищет ответ задание варианта
    int n = 0;
    while (n != (rows > columns ? columns : rows)) { // идём по главной диагонали матрицы
        if (*(B + n * columns + n) % 2 == 0) { // ищем строку удовлетворяющую условию
            int m = -1569325056; // переменная, которой будет присвоено максимальное значение строки
            int f = 0; // флаг, чтобы понять, зашли мы в if для записи нечётного максимума
            for (int i = 0; i < columns; i++) { // ищем нечётный максимум в нужной строке
                if (*(B + n * columns + i) > m && *(B + n * columns + i) % 2 != 0) {
                    m = *(B + n * columns + i);
                    f = 1;
                }
            }
            if (f)
                printf("\nmaximum odd number in %d row = %d", n, m);
        }
        n++;
    }
}

void find_2.0(int* B, int rows, int columns) { // функция ищет ответ задание варианта // с побочной диагональю, а не главной
    int n = 0;
    int max_ind = (rows > columns ? columns : rows) - 1; // переменная хранит максимальный индекс элемента строки на побочной диагонали, то есть на первой строке. Далее в цикле индекс этого элемента в строке будет уменьшаться с увеличением номера строки, в которой мы ищем максимальный нечётный элемент.
    while (n != max_ind + 1) { // идём по главной диагонали матрицы
        if (*(B + n * columns + (max_ind - n)) % 2 == 0) { // ищем строку удовлетворяющую условию
            int m = -1569325056; // переменная, которой будет присвоено максимальное значение строки
            int f = 0; // флаг, чтобы понять, зашли мы в if для записи НЕЧЁТНОГО максимума
            for (int i = 0; i < columns; i++) { // ищем нечётный максимум в нужной строке
                if (*(B + n * columns + i) > m && *(B + n * columns + i) % 2 != 0) {
                    m = *(B + n * columns + i);
                    f = 1;
                }
            }
            if (f)
                printf("\nmaximum odd number in %d row = %d", n + 1, m);
        }
        n++;
    }
}

int main(void) {
    int B[3][5]; // создаём двумерный массив(матрицу) размером 3*5 (3 строки, 5 столбцов)
    int rows = sizeof(B) / sizeof(*B); // количество строк
    int columns = sizeof(*B) / sizeof(**B); // количество столбцов
    input_in_array(B, rows, columns);
    print_array(&(B[0][0]), rows, columns);
    find(&(B[0][0]), rows, columns);
    return 0;
}