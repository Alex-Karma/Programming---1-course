#include <stdio.h>

void cheaked_input(char str1[256], int i, char str2[256], char str3[256], int j, char str4[256], int* p) { // ������� ��� ������ �������� �� ��������� � ��������� �� ������������ �����
    char string[256];
    printf("%s%d%s%s%d%s", str1, i, str2, str3, j, str4);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s%s%d%s", str1, i, str2, str3, j, str4);
        fgets(string, sizeof(string), stdin);
    }
}

void input_in_array(int* B, int rows, int columns) { //������� ����� ����� � �������
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            cheaked_input("Input number B[", i, "]", "[", j, "] = ", (B + i * columns + j)); printf("\r");
        printf("\n");
    }

}

void print_array(int* B, int rows, int columns) { // ������� ������ ��������� �������
    printf("\nElements of matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%d  ", *(B + i * columns + j));
        printf("\n");
    }
}

void find(int* B, int rows, int columns) { // ������� ���� ����� ������� ��������
    int n = 0;
    while (n != (rows > columns ? columns : rows)) { // ��� �� ������� ��������� �������
        if (*(B + n * columns + n) % 2 == 0) { // ���� ������ ��������������� �������
            int m = -1569325056; // ����������, ������� ����� ��������� ������������ �������� ������
            int f = 0; // ����, ����� ������, ����� �� � if ��� ������ ��������� ���������
            for (int i = 0; i < columns; i++) { // ���� �������� �������� � ������ ������
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

void find_2.0(int* B, int rows, int columns) { // ������� ���� ����� ������� �������� // � �������� ����������, � �� �������
    int n = 0;
    int max_ind = (rows > columns ? columns : rows) - 1; // ���������� ������ ������������ ������ �������� ������ �� �������� ���������, �� ���� �� ������ ������. ����� � ����� ������ ����� �������� � ������ ����� ����������� � ����������� ������ ������, � ������� �� ���� ������������ �������� �������.
    while (n != max_ind + 1) { // ��� �� ������� ��������� �������
        if (*(B + n * columns + (max_ind - n)) % 2 == 0) { // ���� ������ ��������������� �������
            int m = -1569325056; // ����������, ������� ����� ��������� ������������ �������� ������
            int f = 0; // ����, ����� ������, ����� �� � if ��� ������ ��ר����� ���������
            for (int i = 0; i < columns; i++) { // ���� �������� �������� � ������ ������
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
    int B[3][5]; // ������ ��������� ������(�������) �������� 3*5 (3 ������, 5 ��������)
    int rows = sizeof(B) / sizeof(*B); // ���������� �����
    int columns = sizeof(*B) / sizeof(**B); // ���������� ��������
    input_in_array(B, rows, columns);
    print_array(&(B[0][0]), rows, columns);
    find(&(B[0][0]), rows, columns);
    return 0;
}