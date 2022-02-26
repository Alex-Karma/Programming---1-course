#include <stdio.h>

void cheaked_input1(char str[256], int* p) { // функци€ присвоит необходимое значение переменной в основной функции, наход€щейс€ по адресу(2-ой аргумент)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void cheaked_input2(char str1[256], int i, char str2[256], int x, char str3[256], int y, char str4[256], int* p) { // перегрузка функций в —» не работает, поэтому пришлось сделать так, потому что € не придумал, как можно создать одну строку из (строка + число + строка)
    char string[256];
    printf("%s%d%s%d%s%d%s", str1, i, str2, x, str3, y, str4);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s%d%s%d%s", str1, i, str2, x, str3, y, str4);
        fgets(string, sizeof(string), stdin);
    }
}

void print_max(int B[], int k) { // функци€ печатает максимум массива
    int m = -99999999999999999; // переменна€, которой будет присвоено максимальное значение массива
    for (int i = 0; i < k; i++) {
        if (B[i] > m)
            m = B[i];
    }
    printf("\nMaximum of array = %d", m);
}

int return_min(int B[], int k) { // фнкци€ возвращает индекс первого минимума массива
    int m = 99999999999999999; // переменна€, которой будет присвоено минимальное значение массива
    int ind = 0; // переменна€, которой будет присвоен индекс минимального значени€ массива
    for (int i = 0; i < k; i++) {
        if (B[i] < m) {
            m = B[i];
            ind = i;
        }
    }
    return ind;
}

int main(void) {
    // объ€вл€ем переменную х - нижн€€ грань массива // у - верхн€€ грань массива
    int x, y;
    // записываем данные в переменные
    do {
        cheaked_input1("Input number x = ", &x);
        cheaked_input1("Input number y(bigger than 'x') = ", &y);
    } while (x > y);
    // начало подпрограммы создани€ массива
    int B[5]; // объ€вл€ем целочисленный массив из 5 элементов(вместо 5 можно написать любое число)
    int k = sizeof(B) / sizeof(B[0]); // записываем в переменную размер массива
    // вводим числа в массив
    for (int i = 0; i < k; i++) {
        do {
            cheaked_input2("Input number B[", i, "] in range[", x, ", ", y, "] = ", &(B[i]));
        } while (!(B[i] >= x && B[i] <= y)); // провер€ем попадание элемента в диапозон [х, у]
    }
    // конец подпрограммы создани€ массива
    // начало подпрограммы вывода массива
    printf("Elements of array: ");
    for (int i = 0; i < k; i++)
        printf("\t%d", B[i]);
    // конец подпрограммы вывода массива
    print_max(B, k); // используем функцию дл€ печати максимума
    int m = return_min(B, k); // переменна€ хран€ща€ значение функции
    double avrg = 0; // переменна€, которой будет присвоенна сумма элементов, среднее арифметическое значение которых мы считаем
    for (int i = 0; i < m; i++)
        avrg += B[i];
    if (m != 0) // обрабатываем случай, когда мы берем ср.арифм. из нулевого количества элементов
        printf("\nThe arithmetic mean of the array = %f", avrg / m);
    else
        printf("\nthe arithmetic mean of the array = 0, because the arithmetic mean is taken from the zero number of elements");
    return 0;
}