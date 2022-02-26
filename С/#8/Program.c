#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header_8.h" // подключаем в программу заголовочный файл с нашими структурами
#define CHOISE 1 // способ ввода данных в массив пользователем (может быть 2, тогда будет выбран способ решения задачи через заранее созданный массив)

void print_TV_array(struct TV* arr, int n) { // функция вывода элементов массива
    printf("\nTelevisions:\n");
    for (int i = 0; i < n; i++)
        printf("%d -> Brand - %s, City - %s, Factory - %s, Release year - %d, Price - %d rubles, Screen size - %d'' \n", i + 1, arr[i].brand, arr[i].Produser.city, arr[i].Produser.factory, arr[i].Produser.release_year, arr[i].Params.price, arr[i].Params.screen_size);
    printf("\n");
}

void number_input(char* str, int* p) { // функция присвоит необходимое(числовое) значение переменной в основной функции, находящейся по адресу(2-ой аргумент)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void input_in_array(struct TV* arr, int n) { // функция ввода данных в массив структур
    struct TV Arr[] = {
        { "Sony", { "Shenzhen", "Foxconn", 2010 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2010 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2010 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2010 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2011 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2011 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2011 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2011 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2012 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2012 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2012 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2012 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2013 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2013 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2013 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2013 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2014 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2014 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2014 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2014 }, { 35000, 48 } }
    }; // массив с заготовленными структурами, которые может выбрать пользователь, чтобы не создавать свои собственные
    int size = sizeof(Arr) / sizeof(Arr[0]);
    print_TV_array(Arr, size); // выводим этот массив структур, чтобы пользователь мог смотреть и выбирать
    printf("Choose some of those structers & input their numbers, or write 0 and create your own (you can create only %d): \n", n);
    int number = 0; // счётчик текущего индекса нашего массива структур
    do { // пользователь выбирает заготовленные структуры
        int i = 0; // номер выбранной заготовки
        do {
            printf("Input arr[%d] [1, %d] : ", number, size + 1);
            number_input("", &i);
        } while (i < 0 || i > size + 1);
        if (i == 0)
            break;
        arr[number] = Arr[i - 1];
        number++;
    } while (number != n);
    while (number != n) { // пользователь создаёт свои собственные структуры
        printf("\t create arr[%d]: \n", number);
        printf("Brand - ");
        scanf("%s", &(arr[number].brand));
        printf("City - ");
        scanf("%s", &(arr[number].Produser.city));
        printf("Factory - ");
        scanf("%s", &(arr[number].Produser.factory));
        getchar();
        number_input("Release year - ", &(arr[number].Produser.release_year));
        number_input("Price (in rubles) - ", &(arr[number].Params.price));
        number_input("Screen size (in inches) - ", &(arr[number].Params.screen_size));
        number++;
    }
}

void print_answer(struct TV arr[], int n, int year) { // функция, которая выведет ответ на условие задачи варианта
    int max_cnt = 0; // переменная будет содержать максимальное количество повторений одинаковых брендов структуры в массиве
    int max_ind = 0; // переменная будет содержать индекс этой структуры, бренд которой повторяется чаще всего
    int* inds = NULL; // массив будет содержать индексы структур, бренд которых повторяется чаще всего в массиве (количество повторений одинаково - так как может быть несколько самых популярных брендов)
    int size = 0; // размер массива inds
    for (int i = 0; i < n; i++) { // пробегаемся по нашему массиву структур
        if (arr[i].Produser.release_year > year) {
            int count = -1; // количество повторений текущего элемента // -1, т.к. при последующем проходе будет прочитан заново элемент под индексом i
            for (int j = 0; j < n; j++) {
                if (arr[j].Produser.release_year > year && !strcmp(arr[i].brand, arr[j].brand)) // смторим сколько раз определённый бренд повторяется в массиве
                    count++;
            }
            if (count > max_cnt) { // ищем максимальное количество повторений бренда
                max_cnt = count;
                max_ind = i;
                size = 1;
                inds = realloc(inds, size * sizeof(int)); // добавляем индекс структуры самого популярного бренда в наш массив
                inds[0] = max_ind;
            }
            else if (count == max_cnt) { // рассматриваем ситуацию с одинаковым количеством повторений разных брендов ( - несколько самых популярных)
                for (int j = 0; j < size; j++) {
                    if (!strcmp(arr[inds[j]].brand, arr[i].brand)) // проверяем повторяется ли бренд, или это другой
                        goto place;
                }
                size++;
                inds = realloc(inds, size * sizeof(int)); // если индекс структуры бренда ещё не был добавлен в inds, то делаем это
                inds[size - 1] = i;
            }
        place:;
        }
    }
    if (size == 0) { // печатаем ответ в зависимости от обстоятельств (нет самого популярного, т.к. год не подошёл; один бренд - самый популярный; несколько популярных)
        printf("There is not the most popular city after %d year", year);
    }
    else if (size == 1) {
        printf("The most popular city after %d year is %s", year, arr[max_ind].brand);
    }
    else {
        printf("The most popular cities after %d year are %s", year, arr[max_ind].brand);
        for (int i = 1; i < size; i++)
            printf(", %s", arr[inds[i]].brand);
    }
}

int main(void) {
    int year = 2010; // год, после которого будем искать самый популярный бренд

#if CHOISE == 1 // говорим компилятору вставить в программу определённый код в зависимости от условия
    int n = 5; // переменная с количеством элементов массива структур
    do {
        number_input("Input number (1-20) of elements in array: ", &n);
    } while (n < 1 || n > 20);
    struct TV* arr = malloc(n * sizeof(struct TV)); // создаём динамический массив структур TV
    input_in_array(arr, n); // вводим значения в массив

#elif CHOISE == 2

// создаём готовый массив (можно вписать любые структуры типа TV)
    struct TV arr[] = { { "Sony", { "Shenzhen", "Foxconn", 2010 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2010 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2010 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2010 }, { 35000, 48 } }, { "Sony", { "Shenzhen", "Foxconn", 2011 }, { 255000, 65 } } };
    int n = sizeof(arr) / sizeof(arr[0]);

#endif // директвы для управления компиляцией частей исходного файла

    print_TV_array(arr, n); // печатаем массив структур
    number_input("Input year according to the task condition: ", &year); // вводим год
    print_answer(arr, n, year); // выводим ответ на задачу варианта
    printf("\n");
    return 0;
}