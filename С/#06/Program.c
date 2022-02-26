#include <stdio.h>
#include <stdlib.h> // ���������� ��� ������ � ������� ��� �������� �������, ������������ �������(������������ ��������� ������)

void cheaked_input1(char str[256], int* p) { // ������� �������� ����������� �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void cheaked_input2(char str1[256], int i, char str2[256], int* p) { // ���������� ������� � �� �� ��������, ������� �������� ������� ���, ������ ��� � �� ��������, ��� ����� ������� ���� ������ �� (������ + ����� + ������)
    char string[256];
    printf("%s%d%s", str1, i, str2);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s", str1, i, str2);
        fgets(string, sizeof(string), stdin);
    }
}

int return_min(int B[], int k) { // ������ ���������� ������ ������� �������� �������
    int m = 99999999999999999; // ����������, ������� ����� ��������� ����������� �������� �������
    int ind = 0; // ����������, ������� ����� �������� ������ ������������ �������� �������
    for (int i = 0; i < k; i++) {
        if (B[i] < m) {
            m = B[i];
            ind = i;
        }
    }
    return ind;
}

void input_in_array(int B[], int k) { //������� ����� ����� � ������
    for (int i = 0; i < k; i++)
        cheaked_input2("Input number B[", i, "] = ", &(B[i]));
}

void print_array(char* str, int B[], int k) { // ������� ������ ��������� �������
    printf("\nElements of %s array: ", str);
    for (int i = 0; i < k; i++)
        printf("%d  ", B[i]);
}

int* modify_array(int* B, int k, int* p) { // ������� �������������� ������
    int m = return_min(B, k); // ���������� �������� �������� ������� ������� �������� �������
    for (int i = m + 1; i < k; i++) { // ��������� �� ���� ��������� ������� � ������������ �� ���������
        if (B[i] % 2 != 0) {
            for (int j = i; j < k - 1; j++)
                B[j] = B[j + 1]; // ������� ����������� �������� ��������� ����� � ������� ������(��������)(������� ��� �� �������)
            k--; // ��������� �������� ����������, ���������� �� �������� ������� �������(��� ��� �� ������� ���� �������)
            B = realloc(B, k * sizeof(int)); // ������� ����� ��������� - ������ ������ ���������� ��� ��� ������, �� �������� �������, ��� ��� ���������� k ����������� // �� ���������������� ������ ��� ������, ������ �������� � ����� � ��������� �������� �������
            print_array("during modification", B, k); // ������� ��������� ������� ����� �������� ��������
            i--; // ��������� ������� ������ �������, ��� ��� ��� ������ ��������� �����
        }
    }
    *p = k; // �������� ���������� �� main(), ���������� �� �������� ������� �������
    return B;
}

int main(void) {
    // ��������� ���������� k - ���������� ��������� �������
    int k;
    // ���������� ������ � k
    do {
        cheaked_input1("Input number k in range[1, ...) = ", &k);
    } while (k <= 0);
    int* B = malloc(k * sizeof(int)); // ������ ���������(��� ������), �������� �������� ��������� �� ������ ���������� ��� ��� ������ ������ // or calloc(k, sizeof(int));
    input_in_array(B, k); // ���������� ������� ����� ����� � ������
    print_array("the original", B, k); // ���������� ������� ������ ��������� �������
    printf("\n");
    B = modify_array(B, k, &k); // �������� ������
    printf("\n");
    print_array("finaly modified", B, k); // ������� ����� ������
    return 0;
}