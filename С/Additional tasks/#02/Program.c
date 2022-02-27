#include <stdio.h>
#include <stdlib.h>

void number_input(char* str, int* p) { // ������� �������� �����������(��������) �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void fill_matrix(double** M, int str, int col, char* string, char* ch) { // ������� ���������� ������������� �������
    printf("\n%s\n", string);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            printf("%s[%d][%d] = ", ch, i, j);
            scanf("%lf", &M[i][j]);
        }
    }
}

void output_matrix(double** M, int str, int col, char* string, char* ch) { // ������� ������� �������� �������
    printf("\n  %s\n", string);
    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            printf("%s[%d][%d] = %.2lf  ", ch, i, j, M[i][j]);
        }
        printf("\n");
    }
}

void sum_matri�es(double** A, double** B, int str, int col) { // ������� ��� �������� ��������� ������ ����� ���������
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

int sum_matri�es_from_files() { // ������� ��������� ��� �������� �������, �������� �� �� ������, � �� ������� ����� ���������
    int str1, col1, str2, col2;
    FILE* fp = fopen("add1_A_matrix.bin", "rb"); // ��������� ����(�������� ������ �������) ��� ������
    fscanf(fp, "%d %d", &str1, &col1); // ��������� ���������� �����/�������� ������ �������
    double** A = malloc(str1 * sizeof(double*));
    for (int i = 0; i < str1; i++) {
        A[i] = malloc(col1 * sizeof(double));
        for (int j = 0; j < col1; j++)
            fscanf(fp, " %lf", &A[i][j]); // ��������� �������� ������� �� �����
    }
    fclose(fp);
    fp = fopen("add1_B_matrix.bin", "rb"); // ������ ��������� ������ ������� �� � �����
    fscanf(fp, "%d %d", &str2, &col2);
    double** B = malloc(str2 * sizeof(double*));
    for (int i = 0; i < str2; i++) {
        B[i] = malloc(col2 * sizeof(double));
        for (int j = 0; j < col2; j++)
            fscanf(fp, " %lf", &B[i][j]);
    }
    fclose(fp);
    if (str1 != str2 || col1 != col2) { // ���������, ��� ������� ����� ���������� ������
        printf("\nIt is impossible to sum up the matrices\n");
        getchar();
        return 1;
    }
    double** M = malloc(str1 * sizeof(double*)); // �������� ������ ��� �������, ������� ����� ������� ����� ����� ������
    for (int i = 0; i < str1; i++) {
        M[i] = malloc(col1 * sizeof(double));
    }
    int choise; // ���������� ����� �������� �� ����� ��������, ������� ������� ������������
    getchar();
    do {
        number_input("\nInput number of operation with matrixes ~ (1: A + B; 2: A - B; 3: B - A) -> ", &choise);
    } while (choise != 1 && choise != 2 && choise != 3);
    for (int i = 0; i < str1; i++) {
        for (int j = 0; j < col1; j++) {
            if (choise == 1) // ���������� � ������� � �������� � ����������� �� ����������������� ������
                M[i][j] = A[i][j] + B[i][j];
            else if (choise == 2)
                M[i][j] = A[i][j] - B[i][j];
            else
                M[i][j] = B[i][j] - A[i][j];
        }
    }
    if (choise == 1) // ������� ���� ������� ����� 
        output_matrix(M, str1, col1, "Values of matrix (A + B):", "M");
    else if (choise == 2)
        output_matrix(M, str1, col1, "Values of matrix (A - B):", "M");
    else
        output_matrix(M, str1, col1, "Values of matrix (B - A):", "M");
    return 0;
}

void multiply_matri�es(double** A, double** B, int str1, int col1, int str2, int col2) { // ������� ����������� �������
    int choise;
    double** M; // ������� ����� ������� �������� ������������ ������
    do {
        number_input("\nInput number of operation with matrixes ~ (1: A * B; 2: B * A) -> ", &choise);
    } while (choise != 1 && choise != 2);
    if (choise == 1 && col1 == str2) { // � ����������� �� ��������� �������� ��������� ������� �� ����������� ������������ 
        int str_col = col1;
        M = malloc(str1 * sizeof(double*));
        for (int i = 0; i < str1; i++) {
            M[i] = calloc(col2, sizeof(double));
        }
        for (int i = 0; i < str1; i++) { // ������ ������� �
            for (int j = 0; j < col2; j++) {
                for (int k = 0; k < str_col; k++) {
                    M[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        output_matrix(M, str1, col2, "Values of matrix (A * B):", "M"); // ������� �
    }
    else if (choise == 1)
        printf("\nIt is impossible to multiply the matrices (A * B)\n");
    if (choise == 2 && col2 == str1) { // ���������� ��� ������� ������
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

void inverse_matrix(double** M, int str_col, char* string) { // ������� �������� �������, �������� ������, �� ������ ���� ��� ����������
    double** M_1 = malloc(str_col * sizeof(double*));
    for (int i = 0; i < str_col; i++) {
        M_1[i] = calloc(str_col, sizeof(double));
        M_1[i][i] = 1;
    } // ������� ��������� �������
    for (int i = 0; i < str_col; i++) { // � ������� ����������� ������� � ������ ������ �������� �� ��������� �������, ������� �������� ������
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
    int str1, col1, str2, col2; // ���������� �������� �� ���������� �����/�������� ���� ����� ������
    number_input("Input amount of strings in first matrix: ", &str1); // ������������ ������ �������� ���������� �����/�������� ������ �������
    number_input("Input amount of columns in first matrix: ", &col1);
    double** A = malloc(str1 * sizeof(double*)); // ������ ������ ������� 
    for (int i = 0; i < str1; i++)
        A[i] = malloc(col1 * sizeof(double)); // �������� ��� �� ������
    fill_matrix(A, str1, col1, "  Input value in first matrix", "A"); // ������ � �� ��������
    getchar();
    number_input("\nInput amount of strings in second matrix: ", &str2); // ������ ��������� ������ �������
    number_input("Input amount of columns in second matrix: ", &col2);
    double** B = malloc(str2 * sizeof(double*));
    for (int i = 0; i < str2; i++)
        B[i] = malloc(col2 * sizeof(double));
    fill_matrix(B, str2, col2, "  Input value in second matrix", "B");
    FILE* fp = fopen("add1_A_matrix.bin", "wb"); // ��������� ���� ��� ������ � ���� ������ �������
    fprintf(fp, "%d %d", str1, col1); // � ������ ������� ���������� � ���� ���������� �����/�������� �������
    for (int i = 0; i < str1; i++)
        for (int j = 0; j < col1; j++)
            fprintf(fp, " %lf", A[i][j]); // ������ ����������� ���������� �������
    fclose(fp);
    fp = fopen("add1_B_matrix.bin", "wb"); // ���������� ������ ������� � ����
    fprintf(fp, "%d %d", str2, col2);
    for (int i = 0; i < str2; i++)
        for (int j = 0; j < col2; j++)
            fprintf(fp, " %lf", B[i][j]);
    fclose(fp);
    output_matrix(A, str1, col1, "Values of first matrix:", "A"); // ������� �������
    output_matrix(B, str2, col2, "Values of second matrix:", "B");
    //if (str1 == str2 && col1 == col2) // ����� ���� ��� �������� ������ ����� ������� � sum_matrices(), � �� sum_matri�es_from_files()
    //    sum_matri�es(A, B, str1, col1);
    //else {
    //    printf("\nIt is impossible to sum up the matrices\n");
    //    getchar();
    //}
    sum_matri�es_from_files(); // ���������� ��� �������� �������
    multiply_matri�es(A, B, str1, col1, str2, col2); // ����������� �������
    // ������� �������� �������, ���� ��� ����������, ����� ������� �������� ������� ������ �����������
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