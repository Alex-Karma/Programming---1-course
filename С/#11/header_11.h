struct member { // структура члена сборной команды по футболу
    char full_name[60]; // ФИО
    char club[30];
    char role[11]; // goalkeeper, defender, midfielder, striker
    int age;
    int matches;
    int goals_scored;
};

// прототипы функций для работы с базой данных
void add_data(); // Добавление записи в базу

void remove_data(); // Удаление заданной записи из базы

void search_data(); // Поиск записей по заданному пользователем (любому) полю

void edit_data(); // Редактирование заданной записи в базе

void sort_database(); // Сортировка данных в базе по заданному пользователем (любому) полю

void output_database(); // Вывод на экран содержимого базы в табличном виде

int contain_latin_letters(char* str, int len) { // функция проверяет, является ли символ допустимым для использования (латинские буквы и цифры)
    char aval[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM "; // массив допустимых символов
    int aval_length = strlen(aval); // подсчитываем длину строки aval c помощью функции из библиотеки string.h
    int f = 0;
    for (int j = 0; j < len; j++) {
        for (int i = 0; i < aval_length; i++) {
            if (aval[i] == str[j]) // если находим совпадение, то возвращаем 1 (правда - символ является допустимым)
                f++;
        }
    }
    if(f == len)
        return 1;
    return 0; // если не будет возвращена 1, то возвращаем 0 (ложь)
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

int num_len(int num) { // функция возвращает длину числа (~ 7 -> 1; 145 -> 3)
    int ans = 0;
    do {
        ans++;
        if (num < pow(10, ans))
            return ans;
    } while (1);
}