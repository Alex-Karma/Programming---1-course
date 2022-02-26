#include <stdio.h>
#include <stdlib.h> // библиотека для работы с памятью для создания массива, неизвестного размера(динамическое выделение памяти)

void cheaked_input1(char str[256], int* p) { // функция присвоит необходимое значение переменной в основной функции, находящейся по адресу(2-ой аргумент)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void cheaked_input2(char str1[256], int i, char str2[256], int* p) { // перегрузка функций в СИ не работает, поэтому пришлось сделать так, потому что я не придумал, как можно создать одну строку из (строка + число + строка)
    char string[256];
    printf("%s%d%s", str1, i, str2);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s%d%s", str1, i, str2);
        fgets(string, sizeof(string), stdin);
    }
}

int return_min(int B[], int k) { // фнкция возвращает индекс первого минимума массива
    int m = 99999999999999999; // переменная, которой будет присвоено минимальное значение массива
    int ind = 0; // переменная, которой будет присвоен индекс минимального значения массива
    for (int i = 0; i < k; i++) {
        if (B[i] < m) {
            m = B[i];
            ind = i;
        }
    }
    return ind;
}

void input_in_array(int B[], int k) { //функция ввода чисел в массив
    for (int i = 0; i < k; i++)
        cheaked_input2("Input number B[", i, "] = ", &(B[i]));
}

void print_array(char* str, int B[], int k) { // функцию вывода элементов массива
    printf("\nElements of %s array: ", str);
    for (int i = 0; i < k; i++)
        printf("%d  ", B[i]);
}

int* modify_array(int* B, int k, int* p) { // функция модифицирующая массив
    int m = return_min(B, k); // переменная хранящая значение индекса первого минимума массива
    for (int i = m + 1; i < k; i++) { // пробегаем по всем элементам массива с минимального по последний
        if (B[i] % 2 != 0) {
            for (int j = i; j < k - 1; j++)
                B[j] = B[j + 1]; // смещаем необходимый диапозон элементов влево и убираем первый(нечётный)(удаляем его из массива)
            k--; // уменьшаем значение переменной, отвечающей за хранение размера массива(так как мы удалили один элемент)
            B = realloc(B, k * sizeof(int)); // функция вернёт указатель - начало памяти выделенной под наш массив, но меньшего размера, так как переменная k уменьшилась // мы перераспределили память под массив, убрали ненужную в связи с удалением элемента массива
            print_array("during modification", B, k); // выводим состояние массива после удаления элемента
            i--; // уменьшаем текущий индекс массива, так как наш массив сдвинулся влево
        }
    }
    *p = k; // изменяем переменную из main(), отвечающую за хранение размера массива
    return B;
}

int main(void) {
    // объявляем переменную k - количество элементов массива
    int k;
    // записываем данные в k
    do {
        cheaked_input1("Input number k in range[1, ...) = ", &k);
    } while (k <= 0);
    int* B = malloc(k * sizeof(int)); // создаём указатель(наш массив), которому присвоим указатель на начало выделенной под наш массив памяти // or calloc(k, sizeof(int));
    input_in_array(B, k); // используем функцию ввода чисел в массив
    print_array("the original", B, k); // используем функцию вывода элементов массива
    printf("\n");
    B = modify_array(B, k, &k); // изменяем массив
    printf("\n");
    print_array("finaly modified", B, k); // выводим новый массив
    return 0;
}