#include <stdio.h>
#include <stdlib.h>

void number_input(char* str, int* p) { // функция присвоит необходимое(числовое) значение переменной в основной функции, находящейся по адресу(2-ой аргумент)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void fill_matrix(double** M, int str, int col, char* string, char* ch) { // функция заполнения пользователем матрицы
    printf("\n%s\n", string);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            printf("%s[%d][%d] = ", ch, i, j);
            scanf("%lf", &M[i][j]);
        }
    }
}

void output_matrix(double** M, int str, int col, char* string, char* ch) { // функция выводит значения матрицы
    printf("\n  %s\n", string);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            printf("%s[%d][%d] = %.2lf  ", ch, i, j, M[i][j]);
        }
        printf("\n");
    }
}

void sum_matriсes(double** A, double** B, int str, int col) { // функция для сложения вычитания матриц через параметры
    double** M = malloc(str * sizeof(double*));
    for (int i = 0; i < str; i++) {
        M[i] = malloc(col * sizeof(double));
    }
    int choise;
    getchar();
    do {
        number_input("\nInput number of operation with matrixes ~ (1: A - B; 2: A + B; 3: B - A) -> ", &choise);
    } while (choise != 1 && choise != 2 && choise != 3);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            if (choise == 1)
                M[i][j] = A[i][j] - B[i][j];
            else if (choise == 2)
                M[i][j] = A[i][j] + B[i][j];
            else
                M[i][j] = B[i][j] - A[i][j];
        }
    }
    if (choise == 1)
        output_matrix(M, str, col, "Values of matrix (A - B):", "M");
    else if (choise == 2)
        output_matrix(M, str, col, "Values of matrix (A + B):", "M");
    else
        output_matrix(M, str, col, "Values of matrix (B - A):", "M");

}

int sum_matriсes_from_files() { // функция суммирует или вычитает матрицы, считывая их из файлов, а не получая через аргументы
    int str1, col1, str2, col2;
    FILE* fp = fopen("add1_A_matrix.bin", "rb"); // открываем файл(хранящий первую матрицу) для чтения
    fscanf(fp, "%d %d", &str1, &col1); // считываем количество строк/столбцов первой матрицы
    double** A = malloc(str1 * sizeof(double*));
    for (int i = 0; i < str1; i++) {
        A[i] = malloc(col1 * sizeof(double));
        for (int j = 0; j < col1; j++)
            fscanf(fp, " %lf", &A[i][j]); // считываем элементы матрицы из файла
    }
    fclose(fp);
    fp = fopen("add1_B_matrix.bin", "rb"); // теперь считываем вторую матрицу из её файла
    fscanf(fp, "%d %d", &str2, &col2);
    double** B = malloc(str2 * sizeof(double*));
    for (int i = 0; i < str2; i++) {
        B[i] = malloc(col2 * sizeof(double));
        for (int j = 0; j < col2; j++)
            fscanf(fp, " %lf", &B[i][j]);
    }
    fclose(fp);
    if (str1 != str2 || col1 != col2) { // проверяем, что матрицы имеют одинаковый размер
        printf("\nIt is impossible to sum up the matrices\n");
        getchar();
        return 1;
    }
    double** M = malloc(str1 * sizeof(double*)); // выделяем память под матрицу, которая будет хранить сумму наших матриц
    for (int i = 0; i < str1; i++) {
        M[i] = malloc(col1 * sizeof(double));
    }
    int choise; // переменная будет отвечать за номер операции, которую выберет пользователь
    getchar();
    do {
        number_input("\nInput number of operation with matrixes ~ (1: A + B; 2: A - B; 3: B - A) -> ", &choise);
    } while (choise != 1 && choise != 2 && choise != 3);
    for (int i = 0; i < str1; i++) {
        for (int j = 0; j < col1; j++) {
            if (choise == 1) // записываем в матрицу М значения в зависимости от пользовательского выбора
                M[i][j] = A[i][j] + B[i][j];
            else if (choise == 2)
                M[i][j] = A[i][j] - B[i][j];
            else
                M[i][j] = B[i][j] - A[i][j];
        }
    }
    if (choise == 1) // выводим нашу матрицу суммы 
        output_matrix(M, str1, col1, "Values of matrix (A + B):", "M");
    else if (choise == 2)
        output_matrix(M, str1, col1, "Values of matrix (A - B):", "M");
    else
        output_matrix(M, str1, col1, "Values of matrix (B - A):", "M");
    return 0;
}

void multiply_matriсes(double** A, double** B, int str1, int col1, int str2, int col2) { // функция перемножает матрицы
    int choise;
    double** M; // матрица будет хранить значение перемножения матриц
    do {
        number_input("\nInput number of operation with matrixes ~ (1: A * B; 2: B * A) -> ", &choise);
    } while (choise != 1 && choise != 2);
    if (choise == 1 && col1 == str2) { // в зависимости от выбранной операции проверяем матрицы на возможность перемножения 
        int str_col = col1;
        M = malloc(str1 * sizeof(double*));
        for (int i = 0; i < str1; i++) {
            M[i] = calloc(col2, sizeof(double));
        }
        for (int i = 0; i < str1; i++) { // создаём матрицу М
            for (int j = 0; j < col2; j++) {
                for (int k = 0; k < str_col; k++) {
                    M[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        output_matrix(M, str1, col2, "Values of matrix (A * B):", "M"); // выводим её
    }
    else if (choise == 1)
        printf("\nIt is impossible to multiply the matrices (A * B)\n");
    if (choise == 2 && col2 == str1) { // аналогично для второго случая
        int str_col = col2;
        M = malloc(str2 * sizeof(double*));
        for (int i = 0; i < str2; i++) {
            M[i] = calloc(col1, sizeof(double));
        }
        for (int i = 0; i < str2; i++) {
            for (int j = 0; j < col1; j++) {
                for (int k = 0; k < str_col; k++) {
                    M[i][j] += B[i][k] * A[k][j];
                }
            }
        }
        output_matrix(M, str2, col1, "Values of matrix (B * A):", "M");
    }
    else if (choise == 2)
        printf("\nIt is impossible to multiply the matrices (B * A)\n");
}

void inverse_matrix(double** M, int str_col, char* string) { // функция получает матрицу, обратную данной, но только если она квадратная
    double** M_1 = malloc(str_col * sizeof(double*));
    for (int i = 0; i < str_col; i++) {
        M_1[i] = calloc(str_col, sizeof(double));
        M_1[i][i] = 1;
    } // создали единичную матрицу
    for (int i = 0; i < str_col; i++) { // с помощью расширенной матрицы и метода Гаусса получаем из единичной матрицы, матрицу обратную данной
        double kef = 1 / M[i][i];
        for (int k = 0; k < str_col; k++) {
            M[i][k] *= kef;
            M_1[i][k] *= kef;
        }
        for (int j = 0; j < str_col; j++) {
            if (j == i)
                continue;
            kef = M[j][i];
            for (int k = 0; k < str_col; k++) {
                M[j][k] -= kef * M[i][k];
                M_1[j][k] -= kef * M_1[i][k];
            }
        }
    }
    output_matrix(M_1, str_col, str_col, string, "M");
}

int main() {
    int str1, col1, str2, col2; // переменные отвечают за количество строк/столбцов двух наших матриц
    number_input("Input amount of strings in first matrix: ", &str1); // пользователь вводит значение количества строк/столбцов первой матрицы
    number_input("Input amount of columns in first matrix: ", &col1);
    double** A = malloc(str1 * sizeof(double*)); // создаём первую матрицу 
    for (int i = 0; i < str1; i++)
        A[i] = malloc(col1 * sizeof(double)); // выделили под неё память
    fill_matrix(A, str1, col1, "  Input value in first matrix", "A"); // вводим в неё значения
    getchar();
    number_input("\nInput amount of strings in second matrix: ", &str2); // теперь заполняем вторую матрицу
    number_input("Input amount of columns in second matrix: ", &col2);
    double** B = malloc(str2 * sizeof(double*));
    for (int i = 0; i < str2; i++)
        B[i] = malloc(col2 * sizeof(double));
    fill_matrix(B, str2, col2, "  Input value in second matrix", "B");
    FILE* fp = fopen("add1_A_matrix.bin", "wb"); // открываем файл для записи в него первой матрицы
    fprintf(fp, "%d %d", str1, col1); // в первую очередь записываем в файл количество строк/столбцов матрицы
    for (int i = 0; i < str1; i++)
        for (int j = 0; j < col1; j++)
            fprintf(fp, " %lf", A[i][j]); // теперь поэлементно записываем матрицу
    fclose(fp);
    fp = fopen("add1_B_matrix.bin", "wb"); // записываем вторую матрицу в файл
    fprintf(fp, "%d %d", str2, col2);
    for (int i = 0; i < str2; i++)
        for (int j = 0; j < col2; j++)
            fprintf(fp, " %lf", B[i][j]);
    fclose(fp);
    output_matrix(A, str1, col1, "Values of first matrix:", "A"); // выводим матрицы
    output_matrix(B, str2, col2, "Values of second matrix:", "B");
    //if (str1 == str2 && col1 == col2) // часть кода для сложения матриц через функцию – sum_matrices(), а не sum_matriсes_from_files()
    //    sum_matriсes(A, B, str1, col1);
    //else {
    //    printf("\nIt is impossible to sum up the matrices\n");
    //    getchar();
    //}
    sum_matriсes_from_files(); // складываем или вычитаем матрицы
    multiply_matriсes(A, B, str1, col1, str2, col2); // перемножаем матрицы
    // выводим обратные матрицы, если они квадратные, иначе подсчёт обратной матрицы сильно усложняется
    if (str1 == col1)
        inverse_matrix(A, str1, "Values of matrix inverse to A:");
    else
        printf("\nIt is hard find matrix inverse to A\n");
    if (str2 == col2)
        inverse_matrix(B, str2, "Values of matrix inverse to B:");
    else
        printf("\nIt is hard find matrix inverse to B\n");
    return 0;
}