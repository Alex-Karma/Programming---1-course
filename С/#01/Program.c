#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(void) {
    int x = 1, y = 2;
    long float z = 1.5, a = 2.5, b = 0.5;
    char answer[256];
    printf("Enter integer number: x = ");
    fgets(answer, sizeof(answer), stdin); // считываем строку из стандартного потока ввода
    while (sscanf(answer, "%d", &x) != 1) { // пока пользователь не введёт число (а будет вводить только символы, то просим ввести строку заново)
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    printf("Enter integer number: y = ");
    fgets(answer, sizeof(answer), stdin); // вместо связки fgets() + while для проверки корректного ввода можно просто использовать scanf(), но возмоен некорректный ввод
    while (sscanf(answer, "%d", &y) != 1) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    printf("Enter float number: z = ");
    fgets(answer, sizeof(answer), stdin);
    while (sscanf(answer, "%Lf", &z) != 1) {
        printf("Incorrect input. Try again: ");
        fgets(answer, sizeof(answer), stdin);
    }
    a = z + (x - fabs(pow(y, 2) / (y + pow(x, 3) / 3))) / pow(y, 2);
    b = exp(z * pow(y, 2)) * atan(x / sqrt((double)x + (double)y));
    printf("a = %010.4Lf\n", a);
    printf("b = %010.4Lf\n", b);
    printf("x = %010o\n", x);
    printf("y = %010X\n", y);
    printf("z = %010.5E\n", z);
    return 0;
}