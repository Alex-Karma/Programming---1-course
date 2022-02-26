#include <stdio.h>
#include <math.h>
#include <string.h>

void fill_file() { // ������� ��� ������ ������ � �������� ���� f
    FILE* fp = fopen("f.bin", "wb"); // ��������� ���� ��� �������� ������
    printf("  Input string of integer numbers separated by space:\n");
    char str[256];
    gets(str);
    fputs(str, fp); // ���������� ������ � ����
    fclose(fp);
}

int contain(char ch) { // ������� ���������, �������� �� ������ ���������� ��� ������������� (�����)
    char aval[] = "1234567890"; // ������ ���������� ��������
    int aval_length = strlen(aval); // ������������ ����� ������ aval c ������� ������� �� ���������� string.h
    for (int i = 0; i < aval_length; i++) {
        if (aval[i] == ch) // ���� ������� ����������, �� ���������� 1 (������ - ������ �������� ����������)
            return 1;
    }
    return 0; // ���� �� ����� ���������� 1, �� ���������� 0 (����)
}

void change_file() { // ������� ��� ���������� �����
place:;
    FILE* fp = fopen("f.bin", "rb"); // ����� ��� ������ �� ��������� ��������� �����
    int count = 0; // ����������, � ������� ����� ��������� ����� ��������� �������� �����
    int num = 0; // ������� �����
    char ch = getc(fp); // ���������� ��� �������� �������� ������� �� �����
    char zero_ascii = '0';
    char str[256]; // ������, � ������� ��������� ���������� �����, �� � ����������� ������������� �������������� ��������
    int str_len = 0; // ����� ������
    int f1 = 0, f2 = 0; // ����� ��� ������ � �������������� �������
    int f3 = 0; // ���� ��� ������������ ���������� ��������
    while (ch != EOF) {
        if (ch == ' ') {
            f3++;
            if (f3 <= 1) {
                str[str_len] = ch;
                str_len++;
            }
        }
        else {
            f3 = 0;
            str[str_len] = ch;
            str_len++;
        }
        if (ch == '-' && num == 0) { // ��������� ���� ����� ����� �������, �� ����� ����� ������������� ���������������
            f1 = 1;
        }
        else if (ch != ' ') {
            if (contain(ch)) { // ���� ����� ������������ ����� ������������ ������ (�� �����), �� ������ ��� ������ ������ ������
                num = num * 10 + (int)ch - (int)zero_ascii; // �������������� �������� � ����� �� ������� ����� ����� � ������ ascii
                if (f2) {
                    num *= -1;
                    f2 = 0;
                }
            }
            else {
                printf("\nInput string again, couse you input not an integer number somewhere:\n");
                fill_file();
                goto place; // �������� ������� ������, ��� ��� � ��� ��������� ����� ������ � ������� ���������� ��� �� �����
            }
        }
        else {
            if (sqrt(num) == (int)sqrt(num) && (int)sqrt(num) % 2 != 0) // ���������, ��� ����� - ������� ��������� �����
                count++;
            num = 0;
        }
        ch = getc(fp);
        if (f1 && !contain(ch)) { // ���������, ���� ����� ����� �� ����� ������, �� ���� ��� ������������ �������
            printf("\nInput string again, couse you input not an integer number somewhere:\n");
            fill_file();
            goto place; // �������� ������� ������, ��� ��� � ��� ��������� ����� ������ � ������� ���������� ��� �� �����
        }
        else if (f1) {
            f2 = 1; // ������ ����, ����� ������� ����� num �������������, ����� ��� �� ������� � �������� �������� �����
        }
        f1 = 0;
    }
    if (sqrt(num) == (int)sqrt(num) && (int)sqrt(num) % 2 != 0) // �������� ���������� �����
        count++;
    fclose(fp);
    //������ �������������� ���� �� �������� ���������� count � ������ // ����� ������ ���������������� ������ �� ��������
    fp = fopen("f.bin", "wb");
    fprintf(fp, "%d -> ", count); // ���������� ���������� �������� ��������� �� ������ ����� � ����� � �������������� ���������� ��� �������
    for (int j = 0; j < str_len; j++)
        putc(str[j], fp);
    fclose(fp);
}

void print_file() { // ������� ��� ������ ����������� �����
    FILE* fp = fopen("f.bin", "rb");
    char ch;
    printf("\n  Answer:\n");
    while ((ch = getc(fp)) != EOF)
        printf("%c", ch);
    fclose(fp);
}

int main(void) {
    // ���������� ���� ������� � ������ ������� ��� ������� ������
    fill_file();
    change_file();
    print_file();
    return 0;
}