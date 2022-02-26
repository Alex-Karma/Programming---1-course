#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int latin_letter(char ch) { // функция проверяет, является ли символ допустимым для использования (строчные латинские буквы)
    char aval[] = "qwertyuiopasdfghjklzxcvbnm"; // массив допустимых символов
    for (int i = 0; i < strlen(aval); i++) {
        if (aval[i] == ch) // если находим совпадение, то возвращаем 1 (правда - символ является допустимым)
            return 1;
    }
    return 0; // если не будет возвращена 1, то возвращаем 0 (ложь)
}

char* reverse(char* str) { // функция возвращает строку, обратную введённой(аргумент функции)
    for (int i = 0; i < strlen(str) / 2; i++) {
        char tmp = str[i];
        str[i] = str[strlen(str) - i - 1];
        str[strlen(str) - i - 1] = tmp;
    }
    return str;
}

typedef struct Node { // создаём структуру, элемент которой будет представлять из себя один узел двусвязного списка
    char* value; // значение узла (слово)
    struct Node* next; // адрес следующего узла
    struct Node* prev; // адрес предыдущего узла
} Node;

typedef struct Doble_Linked_List { // создаём структуру, элемент которой будет представлять из себя сам двусвязный список
    // списки хранят в себе:
    size_t size; // количество элементов
    Node* head; // указатель на первый элемент списка
    Node* tail; // указатель на последний элемент списка
} List;

void push_back(List* list, char* value) { // функция "добавляет" новый элемент в конец списка
    Node* tmp = (Node*)malloc(sizeof(Node)); // указатель на новый элемент
    tmp->value = value; // присваиваем значению элемента значение аргумента функции
    // переопределяем указатели для упорядочивания элементов в списке
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail != NULL) { // переопределяем  "хвост" списка
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) { // переопределяем "голову" списка - необходимо для ситуации, когда не было добавлено ни одного элемента
        list->head = tmp;
    }
    list->size++; // увеличиваем значение размера списка
}

Node* getNth(List* list, size_t index) { // функция возвращает указатель на узел списка по индексу в параметре(первый элемент имеет индекс 0)
    Node* tmp = NULL;
    size_t i;
    if (index < list->size / 2) { // делаем максимально эффективный подход к нужному узлу в зависимости от его местоположения(ближе к началу или концу)
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    }
    else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
    return tmp;
}

void insertNth(List* list, size_t index, char* value) { // функция "вставляет" новый узел перед элементом по индексу
    Node* elm = NULL; // указатель на элемент перед которым будем вставлять узел
    Node* ins = NULL; // узел, который будем вставлять в список
    elm = getNth(list, index); // получаем указатель на элемент по индексу
    ins = (Node*)malloc(sizeof(Node));
    ins->value = value;
    // переопределяем указатели для упорядочивания элементов в списке
    ins->next = elm;
    ins->prev = elm->prev;
    if (elm->prev != NULL) {
        elm->prev->next = ins;
    }
    elm->prev = ins;

    if (ins->prev == NULL) {
        list->head = ins;
    }
    if (elm->next == NULL) {
        list->tail = elm;
    }

    list->size++;
}

void print_list(List* list) { // функция печатает предложение, состоящее из слов в списке
    Node* tmp = list->head;
    printf("%s", tmp->value);
    tmp = tmp->next;
    while (tmp) {
        printf(" %s", tmp->value);
        tmp = tmp->next;
    }
    printf(".\n");
}

int condition_and_answer(List* list, char str[256]) { // функция создаёт список и печатает две строки(исходную и финальную)
    int str_length = strlen(str); // переменная хранит размер изначальной строки, введённой пользователем
    if (str[str_length - 1] != '.' || str[0] == '.') // если в конце нет точки, то дальше можно и не смотреть или если пользователь введёт только точку(могли бы возникнуть ошибки доступа при попытке вывода пустого списка)
        return 1;
    char* word = NULL; // динамическая строка, в которую будем записывать наши слова
    int word_len = 0; // длинна слов
    for (int i = 0; i < str_length; i++) { // пробегаемся по каждому символу изначальной строки
        if (latin_letter(str[i])) { // если символ допустим, то мы добавляем его в наше слово
            word_len++;
            word = realloc(word, word_len * sizeof(char));
            word[word_len - 1] = str[i];
        }
        else if (str[i] == ' ' || str[i] == '.') { // если символ недопустим, но это точка или пробел, то мы добавляем слово в список
            if (str[i] == '.' && i != str_length - 1) // проверка на наличие нескольких точек в списке
                return 1;
            if (word_len == 0) // проверяем, что слово состоит хотя бы из одного символа
                continue; // то есть учитываем возможность ввода нескольких разделительных пробелов
            word[word_len] = '\0'; // ставим символ конца строки в конец нашего слова
            push_back(list, word); // "вставляем" слово в список
            word = NULL; // обнуляем наше слово, чтобы записывать в него новые
            word_len = 0;
        }
        else
            return 1;
    }
    printf("\nThe original string: "); // выводим изначальное предложение
    print_list(list);
    int index = 0; // переменная будет хранить индекс
    for (int i = 1; i < list->size; i++) { // получаем индекс минимального слова в списке
        if (strcmp(getNth(list, index)->value, getNth(list, i)->value) < 0) {
            index = i;
        }
    }
    word = malloc(sizeof(getNth(list, index)->value)); // переменная будет хранить копию слово под нужным индексом, чтобы потом вставить его реверсивную запись перед этим словом
    strcpy(word, getNth(list, index)->value);
    insertNth(list, index, reverse(word));
    printf("\nThe final string: "); // выводим итоговое предложение
    print_list(list);
    return 0;
}

int main(void) {
    List* list = malloc(sizeof(List)); // создаём экземпляр двусвязного списка
    char str[256];
    do {
        list->size = 0;
        list->head = list->tail = NULL;
        printf("Input string by task condition: ");
        gets(str);
    } while (condition_and_answer(list, str)); // просим пользователя ввести строку, пока она не будет введена в соответствии с условием задачи и потом печатаем ответ
    return 0;
}