#include <stdio.h>

void cheaked_input1(char str[256], int* p) { // ������� �������� ����������� �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void cheaked_input2(char str1[256], int i, char str2[256], int x, char str3[256], int y, char str4[256], int* p) { // ���������� ������� � �� �� ��������, ������� �������� ������� ���, ������ ��� � �� ��������, ��� ����� ������� ���� ������ �� (������ + ����� + ������)
    char string[256];
    printf("%s%d%s%d%s%d%s", str1, i, str2, x, str3, y, str4);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s%d%s%d%s", str1, i, str2, x, str3, y, str4);
        fgets(string, sizeof(string), stdin);
    }
}

void print_max(int B[], int k) { // ������� �������� �������� �������
    int m = -99999999999999999; // ����������, ������� ����� ��������� ������������ �������� �������
    for (int i = 0; i < k; i++) {
        if (B[i] > m)
            m = B[i];
    }
    printf("\nMaximum of array = %d", m);
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

int main(void) {
    // ��������� ���������� � - ������ ����� ������� // � - ������� ����� �������
    int x, y;
    // ���������� ������ � ����������
    do {
        cheaked_input1("Input number x = ", &x);
        cheaked_input1("Input number y(bigger than 'x') = ", &y);
    } while (x > y);
    // ������ ������������ �������� �������
    int B[5]; // ��������� ������������� ������ �� 5 ���������(������ 5 ����� �������� ����� �����)
    int k = sizeof(B) / sizeof(B[0]); // ���������� � ���������� ������ �������
    // ������ ����� � ������
    for (int i = 0; i < k; i++) {
        do {
            cheaked_input2("Input number B[", i, "] in range[", x, ", ", y, "] = ", &(B[i]));
        } while (!(B[i] >= x && B[i] <= y)); // ��������� ��������� �������� � �������� [�, �]
    }
    // ����� ������������ �������� �������
    // ������ ������������ ������ �������
    printf("Elements of array: ");
    for (int i = 0; i < k; i++)
        printf("\t%d", B[i]);
    // ����� ������������ ������ �������
    print_max(B, k); // ���������� ������� ��� ������ ���������
    int m = return_min(B, k); // ���������� �������� �������� �������
    double avrg = 0; // ����������, ������� ����� ���������� ����� ���������, ������� �������������� �������� ������� �� �������
    for (int i = 0; i < m; i++)
        avrg += B[i];
    if (m != 0) // ������������ ������, ����� �� ����� ��.�����. �� �������� ���������� ���������
        printf("\nThe arithmetic mean of the array = %f", avrg / m);
    else
        printf("\nthe arithmetic mean of the array = 0, because the arithmetic mean is taken from the zero number of elements");
    return 0;
}