#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header_8.h" // ���������� � ��������� ������������ ���� � ������ �����������
#define CHOISE 1 // ������ ����� ������ � ������ ������������� (����� ���� 2, ����� ����� ������ ������ ������� ������ ����� ������� ��������� ������)

void print_TV_array(struct TV* arr, int n) { // ������� ������ ��������� �������
    printf("\nTelevisions:\n");
    for (int i = 0; i < n; i++)
        printf("%d -> Brand - %s, City - %s, Factory - %s, Release year - %d, Price - %d rubles, Screen size - %d'' \n", i + 1, arr[i].brand, arr[i].Produser.city, arr[i].Produser.factory, arr[i].Produser.release_year, arr[i].Params.price, arr[i].Params.screen_size);
    printf("\n");
}

void number_input(char* str, int* p) { // ������� �������� �����������(��������) �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

void input_in_array(struct TV* arr, int n) { // ������� ����� ������ � ������ ��������
    struct TV Arr[] = {
        { "Sony", { "Shenzhen", "Foxconn", 2010 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2010 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2010 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2010 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2011 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2011 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2011 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2011 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2012 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2012 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2012 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2012 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2013 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2013 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2013 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2013 }, { 35000, 48 } },
        { "Sony", { "Shenzhen", "Foxconn", 2014 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2014 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2014 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2014 }, { 35000, 48 } }
    }; // ������ � �������������� �����������, ������� ����� ������� ������������, ����� �� ��������� ���� �����������
    int size = sizeof(Arr) / sizeof(Arr[0]);
    print_TV_array(Arr, size); // ������� ���� ������ ��������, ����� ������������ ��� �������� � ��������
    printf("Choose some of those structers & input their numbers, or write 0 and create your own (you can create only %d): \n", n);
    int number = 0; // ������� �������� ������� ������ ������� ��������
    do { // ������������ �������� ������������� ���������
        int i = 0; // ����� ��������� ���������
        do {
            printf("Input arr[%d] [1, %d] : ", number, size + 1);
            number_input("", &i);
        } while (i < 0 || i > size + 1);
        if (i == 0)
            break;
        arr[number] = Arr[i - 1];
        number++;
    } while (number != n);
    while (number != n) { // ������������ ������ ���� ����������� ���������
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

void print_answer(struct TV arr[], int n, int year) { // �������, ������� ������� ����� �� ������� ������ ��������
    int max_cnt = 0; // ���������� ����� ��������� ������������ ���������� ���������� ���������� ������� ��������� � �������
    int max_ind = 0; // ���������� ����� ��������� ������ ���� ���������, ����� ������� ����������� ���� �����
    int* inds = NULL; // ������ ����� ��������� ������� ��������, ����� ������� ����������� ���� ����� � ������� (���������� ���������� ��������� - ��� ��� ����� ���� ��������� ����� ���������� �������)
    int size = 0; // ������ ������� inds
    for (int i = 0; i < n; i++) { // ����������� �� ������ ������� ��������
        if (arr[i].Produser.release_year > year) {
            int count = -1; // ���������� ���������� �������� �������� // -1, �.�. ��� ����������� ������� ����� �������� ������ ������� ��� �������� i
            for (int j = 0; j < n; j++) {
                if (arr[j].Produser.release_year > year && !strcmp(arr[i].brand, arr[j].brand)) // ������� ������� ��� ����������� ����� ����������� � �������
                    count++;
            }
            if (count > max_cnt) { // ���� ������������ ���������� ���������� ������
                max_cnt = count;
                max_ind = i;
                size = 1;
                inds = realloc(inds, size * sizeof(int)); // ��������� ������ ��������� ������ ����������� ������ � ��� ������
                inds[0] = max_ind;
            }
            else if (count == max_cnt) { // ������������� �������� � ���������� ����������� ���������� ������ ������� ( - ��������� ����� ����������)
                for (int j = 0; j < size; j++) {
                    if (!strcmp(arr[inds[j]].brand, arr[i].brand)) // ��������� ����������� �� �����, ��� ��� ������
                        goto place;
                }
                size++;
                inds = realloc(inds, size * sizeof(int)); // ���� ������ ��������� ������ ��� �� ��� �������� � inds, �� ������ ���
                inds[size - 1] = i;
            }
        place:;
        }
    }
    if (size == 0) { // �������� ����� � ����������� �� ������������� (��� ������ �����������, �.�. ��� �� �������; ���� ����� - ����� ����������; ��������� ����������)
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
    int year = 2010; // ���, ����� �������� ����� ������ ����� ���������� �����

#if CHOISE == 1 // ������� ����������� �������� � ��������� ����������� ��� � ����������� �� �������
    int n = 5; // ���������� � ����������� ��������� ������� ��������
    do {
        number_input("Input number (1-20) of elements in array: ", &n);
    } while (n < 1 || n > 20);
    struct TV* arr = malloc(n * sizeof(struct TV)); // ������ ������������ ������ �������� TV
    input_in_array(arr, n); // ������ �������� � ������

#elif CHOISE == 2

// ������ ������� ������ (����� ������� ����� ��������� ���� TV)
    struct TV arr[] = { { "Sony", { "Shenzhen", "Foxconn", 2010 }, { 255000, 65 } }, { "LG", { "Shenzhen", "Foxconn", 2010 }, { 175000, 55 } }, { "Samsung", { "Shenzhen", "Foxconn", 2010 }, { 21280, 32 } }, { "Panasonic", { "Shenzhen", "Foxconn", 2010 }, { 35000, 48 } }, { "Sony", { "Shenzhen", "Foxconn", 2011 }, { 255000, 65 } } };
    int n = sizeof(arr) / sizeof(arr[0]);

#endif // �������� ��� ���������� ����������� ������ ��������� �����

    print_TV_array(arr, n); // �������� ������ ��������
    number_input("Input year according to the task condition: ", &year); // ������ ���
    print_answer(arr, n, year); // ������� ����� �� ������ ��������
    printf("\n");
    return 0;
}