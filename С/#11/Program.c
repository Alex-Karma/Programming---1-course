#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "header_11.h" // подключаем заголовочный файл со структурой, прототипами функций для работы с БД и вспомогательными функциями

// создаём глобальные переменные, для упрощения работы с функциями, обрабатывающими БД (массив структур)
FILE* fp; // указатель на поток
struct member* arr = NULL; // массив, в котором будут храниться структуры участников, для упрощения работы с данными
int arr_len = 0; // длина массива arr - текущее количество членов сборной
int max_sizes[] = { 0, 0, 0, 0, 0, 0, 0 }; // массив хранит максимальные длины столбцов по порядку; нужен для вывода БД в табличной форме

void change_max_sizes() { // функция редактирует значения максимальных размеров столбцов
    for (int i = 0; i < arr_len; i++) { // проходимся по каждой структуре и изменяем размеры столбцов
        if (strlen(arr[i].full_name) > max_sizes[1])
            max_sizes[1] = strlen(arr[i].full_name);
        if (strlen(arr[i].club) > max_sizes[2])
            max_sizes[2] = strlen(arr[i].club);
        if (strlen(arr[i].role) > max_sizes[3])
            max_sizes[3] = strlen(arr[i].role);
        if (num_len(arr[i].age) > max_sizes[4])
            max_sizes[4] = num_len(arr[i].age);
        if (num_len(arr[i].matches) > max_sizes[5])
            max_sizes[5] = num_len(arr[i].matches);
        if (num_len(arr[i].goals_scored) > max_sizes[6])
            max_sizes[6] = num_len(arr[i].goals_scored);
    }
}

void input_data(int i) { // функция для ввода данных в элемент массива(структуру) по выбору
    printf("\n");
    do {
        printf("Full name - ");
        gets(arr[i].full_name); // записываем строку с консоли в строковую переменную
    } while (!contain_latin_letters(arr[i].full_name, strlen(arr[i].full_name)));
    do {
        printf("Club - ");
        gets(arr[i].club);
    } while (!contain_latin_letters(arr[i].club, strlen(arr[i].club)));
    do {
        printf("Role (goalkeeper, defender, midfielder, striker) - ");
        gets(arr[i].role);
    } while (!(!strcmp(arr[i].role, "goalkeeper") || !strcmp(arr[i].role, "defender") || !strcmp(arr[i].role, "midfielder") || !strcmp(arr[i].role, "striker")));
    number_input("Age of member - ", &arr[i].age);
    number_input("Number of matches played for team - ", &arr[i].matches);
    number_input("Number of scored goals - ", &arr[i].goals_scored);
    change_max_sizes();
}

void add_data() {
    fp = fopen("database.bin", "ab"); // открываем поток на наш файл в режиме добавления данных в конец файла
    arr_len++;
    arr = realloc(arr, sizeof(struct member) * arr_len);
    printf("  Input information about new member:");
    getchar();
    input_data(arr_len - 1);
    char* c = (char*)&(arr[arr_len - 1]); // устанавливаем указатель на начало структуры
    // посимвольно дописываем в файл структуру
    for (int i = 0; i < sizeof(struct member); i++)
    {
        putc(*c++, fp);
    }
    fclose(fp);
}

void remove_data() {
    if (arr_len == 0) {
        printf("There is no elements to remove\n");
        return 0;
    }
    fp = fopen("database.bin", "wb");
    int n = 0; // переменная отвечает за позицию члена сборной, чьи данные хотят удалить
    output_database(); // выводим БД, чтобы пользователь мог видеть её перед собой для удобной работы
    getchar(); // нужен, чтобы избавится от \n оставшегося после последнего scanf()
    do {
        number_input("Input number of member in the database who you want to remove: ", &n);
    } while (!(n > 0 && n <= arr_len));
    arr_len--;
    for (int i = n - 1; i < arr_len; i++) { // смещаем влево элементы массива, идущие после выбранного - таким образом удаляем его из массива
        arr[i] = arr[i + 1];
    }
    arr = realloc(arr, sizeof(struct member) * arr_len);
    char* c = (char*)arr; // устанавливаем указатель на начало массива структур
    // посимвольно записываем в файл массив структур
    for (int i = 0; i < sizeof(struct member) * arr_len; i++)
    {
        putc(*c++, fp);
    }
    fclose(fp);
    // приводим значения ширины столбцов к длине заголовков, чтобы учесть удаление данных
    max_sizes[0] = strlen("#");
    max_sizes[1] = strlen("Full name");
    max_sizes[2] = strlen("Club");
    max_sizes[3] = strlen("Role");
    max_sizes[4] = strlen("Age");
    max_sizes[5] = strlen("Matches");
    max_sizes[6] = strlen("Goals");
    change_max_sizes();
}

void search_data() {
    if (arr_len == 0) {
        printf("There is nothing to search\n");
        return 0;
    }
    output_database();
    getchar(); // нужен, чтобы избавится от \n оставшегося после последнего scanf()
    int n = 0;
    do {
        number_input("\n  Input number of column by which you want to search(1 - Full name; 2 - Club...) -> ", &n);
    } while (!(n > 0 && n <= 6));
place2:;
    int f = 0; // флаг, который будет отвечать за наличие введённого значения в столбце в БД, чтобы можно было попросить пользователя заново ввести значение
    printf("Input value from chosen column: ");
    if (n > 3) { // разбиваем задачу отдельно на работу с числами и строками для экономии памяти
        int value = 0; // значение, по которому будем искать структуру
        number_input("", &value);
        printf("\n");
        for (int i = 0; i < arr_len; i++) {
            if (n == 4 && value == arr[i].age || n == 5 && value == arr[i].matches || n == 6 && value == arr[i].goals_scored) { // выводим все данные по члену сборной, у которого найдено соответствие
                printf("%d -> Full name - %s; Club - %s; Role - %s; Age - %d; Matches number - %d; Goals number - %d.\n", i + 1, arr[i].full_name, arr[i].club, arr[i].role, arr[i].age, arr[i].matches, arr[i].goals_scored);
                f = 1;
            }
        }
    }
    else {
        char value[60]; // значение, по которому будем искать структуру
        gets(value);
        printf("\n");
        for (int i = 0; i < arr_len; i++) {
            if (n == 1 && !strcmp(value, arr[i].full_name) || n == 2 && !strcmp(value, arr[i].club) || n == 3 && !strcmp(value, arr[i].role)) {
                printf("%d -> Full name - %s; Club - %s; Role - %s; Age - %d; Matches number - %d; Goals number - %d.\n", i + 1, arr[i].full_name, arr[i].club, arr[i].role, arr[i].age, arr[i].matches, arr[i].goals_scored);
                f = 1;
            }
        }
    }
    if (f == 0) {
        printf("  There is no such value in this column. ");
        goto place2;
    }
    else {
        printf("  It's all members of national team with inputed value in the chosen column\n");
    }
}

void edit_data() {
    if (arr_len == 0) {
        printf("There are no elements to edit\n");
        return 0;
    }
    fp = fopen("database.bin", "wb");
    int n = 0;
    output_database();
    getchar();
    do {
        number_input("Input number of member in the database whose data you want to edit: ", &n);
    } while (!(n > 0 && n <= arr_len));
    input_data(n - 1);
    fclose(fp);
}

void sort_database() {
    if (arr_len == 0) {
        printf("There is no data to sort\n");
        return 0;
    }
    output_database();
    getchar();
    fp = fopen("database.bin", "wb");
    int choise = 0;
    do {
        number_input("\n  Input number of column(1 - Full name; 2 - Club...) -> ", &choise);
    } while (!(choise > 0 && choise <= 6));
    for (int i = 1; i < arr_len; i++) { // сортировка чисел по убыванию и строк в алфавитном порядке (sort algorithm - insertsort)
        int j = i;
        while (j > 0 && (strcmp(arr[j - 1].full_name, arr[j].full_name) > 0 && choise == 1 || strcmp(arr[j - 1].club, arr[j].club) > 0 && choise == 2 || strcmp(arr[j - 1].role, arr[j].role) > 0 && choise == 3 || arr[j - 1].age < arr[j].age && choise == 4 || arr[j - 1].matches < arr[j].matches && choise == 5 || arr[j - 1].goals_scored < arr[j].goals_scored && choise == 6)) {
            struct member k = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = k;
            j--;
        }
    }
    fwrite(arr, sizeof(struct member), arr_len, fp); // записываем массив в поток
    fclose(fp);
}

void output_database() {
    fp = fopen("database.bin", "rb");
    if (arr == NULL) {
        printf("There aren't any elements in database. First of all input data\n");
        return 0;
    }
    fread(arr, sizeof(struct member), arr_len, fp); // записываем данные из потока в массив
    if (num_len(arr_len) > max_sizes[0]) // обрабатываем размер БД для возможного увеличения первого столбца
        max_sizes[0] = num_len(arr_len);
    printf("  Members of national team:\n\n");
    // выводим БД в табличном виде путём настраивания ширины поля и выравнивания по левому краю
    printf("%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s\n", max_sizes[0], "#", max_sizes[1], "Full name", max_sizes[2], "Club", max_sizes[3], "Role", max_sizes[4], "Age", max_sizes[5], "Matches", max_sizes[6], "Goals");
    for (int i = 0; i < arr_len; i++)
        printf("%-*d | %-*s | %-*s | %-*s | %-*d | %-*d | %-*d\n", max_sizes[0], i + 1, max_sizes[1], arr[i].full_name, max_sizes[2], arr[i].club, max_sizes[3], arr[i].role, max_sizes[4], arr[i].age, max_sizes[5], arr[i].matches, max_sizes[6], arr[i].goals_scored);
    fclose(fp);
}

int main(void) {
    remove("database.bin"); // удаляем созданный в прошлый раз файл с базой данных
    // приводим значения ширины столбцов к длине заголовков
    max_sizes[0] = strlen("#");
    max_sizes[1] = strlen("Full name");
    max_sizes[2] = strlen("Club");
    max_sizes[3] = strlen("Role");
    max_sizes[4] = strlen("Age");
    max_sizes[5] = strlen("Matches");
    max_sizes[6] = strlen("Goals");
    int f; // переменная отвечает за выбранный пользователем режим из меню
    printf("\tMenue:\n1 -> Add data\n2 -> Remove data\n3 -> Search data\n4 -> Edit data\n5 -> Sort database\n6 -> Output database\n0 -> End process\n");
    do {
    place1:;
        printf("\nInput number of the option from menue: ");
        scanf("%d", &f);
        switch (f) {
        case 0:
            return 0;
            break;
        case 1:
            add_data();
            break;
        case 2:
            remove_data();
            break;
        case 3:
            search_data();
            break;
        case 4:
            edit_data();
            break;
        case 5:
            sort_database();
            break;
        case 6:
            output_database();
            break;
        default:
            printf("Wrong input, make it again!! ");
            goto place1;
            break;
        }
    } while (f != 0);
    return 0;
}