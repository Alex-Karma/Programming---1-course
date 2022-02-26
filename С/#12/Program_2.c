#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int latin_letter(char ch) { // ������� ���������, �������� �� ������ ���������� ��� ������������� (�������� ��������� �����)
    char aval[] = "qwertyuiopasdfghjklzxcvbnm"; // ������ ���������� ��������
    for (int i = 0; i < strlen(aval); i++) {
        if (aval[i] == ch) // ���� ������� ����������, �� ���������� 1 (������ - ������ �������� ����������)
            return 1;
    }
    return 0; // ���� �� ����� ���������� 1, �� ���������� 0 (����)
}

char* reverse(char* str) { // ������� ���������� ������, �������� ��������(�������� �������)
    for (int i = 0; i < strlen(str) / 2; i++) {
        char tmp = str[i];
        str[i] = str[strlen(str) - i - 1];
        str[strlen(str) - i - 1] = tmp;
    }
    return str;
}

typedef struct Node { // ������ ���������, ������� ������� ����� ������������ �� ���� ���� ���� ����������� ������
    char* value; // �������� ���� (�����)
    struct Node* next; // ����� ���������� ����
    struct Node* prev; // ����� ����������� ����
} Node;

typedef struct Doble_Linked_List { // ������ ���������, ������� ������� ����� ������������ �� ���� ��� ���������� ������
    // ������ ������ � ����:
    size_t size; // ���������� ���������
    Node* head; // ��������� �� ������ ������� ������
    Node* tail; // ��������� �� ��������� ������� ������
} List;

void push_back(List* list, char* value) { // ������� "���������" ����� ������� � ����� ������
    Node* tmp = (Node*)malloc(sizeof(Node)); // ��������� �� ����� �������
    tmp->value = value; // ����������� �������� �������� �������� ��������� �������
    // �������������� ��������� ��� �������������� ��������� � ������
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail != NULL) { // ��������������  "�����" ������
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) { // �������������� "������" ������ - ���������� ��� ��������, ����� �� ���� ��������� �� ������ ��������
        list->head = tmp;
    }
    list->size++; // ����������� �������� ������� ������
}

Node* getNth(List* list, size_t index) { // ������� ���������� ��������� �� ���� ������ �� ������� � ���������(������ ������� ����� ������ 0)
    Node* tmp = NULL;
    size_t i;
    if (index < list->size / 2) { // ������ ����������� ����������� ������ � ������� ���� � ����������� �� ��� ��������������(����� � ������ ��� �����)
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

void insertNth(List* list, size_t index, char* value) { // ������� "���������" ����� ���� ����� ��������� �� �������
    Node* elm = NULL; // ��������� �� ������� ����� ������� ����� ��������� ����
    Node* ins = NULL; // ����, ������� ����� ��������� � ������
    elm = getNth(list, index); // �������� ��������� �� ������� �� �������
    ins = (Node*)malloc(sizeof(Node));
    ins->value = value;
    // �������������� ��������� ��� �������������� ��������� � ������
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

void print_list(List* list) { // ������� �������� �����������, ��������� �� ���� � ������
    Node* tmp = list->head;
    printf("%s", tmp->value);
    tmp = tmp->next;
    while (tmp) {
        printf(" %s", tmp->value);
        tmp = tmp->next;
    }
    printf(".\n");
}

int condition_and_answer(List* list, char str[256]) { // ������� ������ ������ � �������� ��� ������(�������� � ���������)
    int str_length = strlen(str); // ���������� ������ ������ ����������� ������, �������� �������������
    if (str[str_length - 1] != '.' || str[0] == '.') // ���� � ����� ��� �����, �� ������ ����� � �� �������� ��� ���� ������������ ����� ������ �����(����� �� ���������� ������ ������� ��� ������� ������ ������� ������)
        return 1;
    char* word = NULL; // ������������ ������, � ������� ����� ���������� ���� �����
    int word_len = 0; // ������ ����
    for (int i = 0; i < str_length; i++) { // ����������� �� ������� ������� ����������� ������
        if (latin_letter(str[i])) { // ���� ������ ��������, �� �� ��������� ��� � ���� �����
            word_len++;
            word = realloc(word, word_len * sizeof(char));
            word[word_len - 1] = str[i];
        }
        else if (str[i] == ' ' || str[i] == '.') { // ���� ������ ����������, �� ��� ����� ��� ������, �� �� ��������� ����� � ������
            if (str[i] == '.' && i != str_length - 1) // �������� �� ������� ���������� ����� � ������
                return 1;
            if (word_len == 0) // ���������, ��� ����� ������� ���� �� �� ������ �������
                continue; // �� ���� ��������� ����������� ����� ���������� �������������� ��������
            word[word_len] = '\0'; // ������ ������ ����� ������ � ����� ������ �����
            push_back(list, word); // "���������" ����� � ������
            word = NULL; // �������� ���� �����, ����� ���������� � ���� �����
            word_len = 0;
        }
        else
            return 1;
    }
    printf("\nThe original string: "); // ������� ����������� �����������
    print_list(list);
    int index = 0; // ���������� ����� ������� ������
    for (int i = 1; i < list->size; i++) { // �������� ������ ������������ ����� � ������
        if (strcmp(getNth(list, index)->value, getNth(list, i)->value) < 0) {
            index = i;
        }
    }
    word = malloc(sizeof(getNth(list, index)->value)); // ���������� ����� ������� ����� ����� ��� ������ ��������, ����� ����� �������� ��� ����������� ������ ����� ���� ������
    strcpy(word, getNth(list, index)->value);
    insertNth(list, index, reverse(word));
    printf("\nThe final string: "); // ������� �������� �����������
    print_list(list);
    return 0;
}

int main(void) {
    List* list = malloc(sizeof(List)); // ������ ��������� ����������� ������
    char str[256];
    do {
        list->size = 0;
        list->head = list->tail = NULL;
        printf("Input string by task condition: ");
        gets(str);
    } while (condition_and_answer(list, str)); // ������ ������������ ������ ������, ���� ��� �� ����� ������� � ������������ � �������� ������ � ����� �������� �����
    return 0;
}