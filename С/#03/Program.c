#include <stdio.h>
#include <math.h>

int factorial(int y) { // ������� ��� �������� ���������� �����
    int ans = 1;
    for (int r = y; r != 0; r--) {
        ans *= r;
    }
    return ans;
}

double formula(double i, double x) { // ������� ��� �������� �������� ���� ��� ������� i � ���������� �
    return ((pow(-1, i) * factorial(2 * i) * pow(x, i)) / ((1 - 2 * i) * pow(factorial(i), 2) * pow(4, i)));
}

double cheak(char str[256]) { // ������� ������ ��������, ������� ����� ��������� ���������� ����� �������� �� ������������ ����� (������ ���� ������� ����� ���� double)
    double a;
    char string[256];
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%lf", &a) != 1) {
        printf("Incorrect input, try again, %s", str);
        fgets(string, sizeof(string), stdin);
    }
    return a;
}

int main(void) {
    // �������������� ����������: ���������� ���������, ������ ������� ������, ���������� �, �����, ��������
    int n = 4, choise = 1;
    double x, answer = 1.0, accuracy;

    // ������ ������
    printf("Input number x in range(-1; 1) = ");
    x = cheak("x in range(-1; 1) = "); // ���������� ������� cheak(), ����� ��������� ��������
    while (x <= -1 || x >= 1) { // ��������� �� ��������� � ������� �����������
        printf("Wrong input, try again, x in range(-1; 1) = ");
        x = cheak("x in range(-1; 1) = ");
    }

    printf("Input number of the way to solve task (1, 2): ");
    choise = (int)cheak("way to solve task (1, 2): ");
    while (choise != 1 && choise != 2) { // ���������, ��� �������� �������� ��� ���������� ����� 1 ��� 2
        printf("Wrong input, try again, way to solve task (1, 2): ");
        choise = (int)cheak("way to solve task (1, 2): ");
    }

    switch (choise) { // ���������� �������� ������
    case 1:
        printf("Input accuracy (~ 0.01; 0.001) = ");
        accuracy = cheak("accuracy (~ 0.01; 0.001) = ");

        int i = 1; // ������ ����� n �� �������
        while (fabs(formula(i, x)) >= accuracy) { // ��� ���������� ����������������� ����� ���������� ��������� ��������: ����� ������� ����������� �� ��� ���, ���� ��� �� ������ ������ �������� ��������
            answer += formula(i, x);
            i++;
        }
        break;
    case 2:
        printf("Input number n = ");
        n = (int)cheak("n = ");

        for (int i = 1; i <= n; i++) {
            answer += formula(i, x);
        }
        break;

    }
    printf("Answer is %.50f", answer); // ������� �����

    // ����� ���������� ������ -nan(ind) (���������������� �����), ��-�� ������� ����� ��������� �� �������� �����(�� 68)
    return 0;
}