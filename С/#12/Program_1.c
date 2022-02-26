#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void number_input(char* str, int* p) { // ������� �������� �����������(��������) �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

typedef struct { // ���������� ���������, �������� ������� ����� ���������� ����������� ������
    // ��� ��������:
    int coefficient; // ����������� ����� � � �����-�� �������
    int degree; // ������� �
    struct Node* next; // ������(��������� �� ��������� ������� � ������
} Node;

int condition(const Node* head, int degree) { // �������� �� ���������� ���������� ������� ��� �
    while (head) {
        if (head->degree == degree)
            return 1;
        head = head->next;
    }
    return 0;
}

void push(Node** head) { // ������� "���������" ����� ������� � ������ ������
    Node* tmp = (Node*)malloc(sizeof(Node)); // ����� ����, ������� ����� ������� � ������
    do {
        number_input("Input positive degree of the element (without repeating): ", &(tmp->degree));
    } while (condition(*head, tmp->degree) || tmp->degree < 0);
    do {
        number_input("Input coefficient of the element: ", &(tmp->coefficient));
    } while (tmp->coefficient == 0);
    // �������������� ��������� ��� �������������� ��������� � ������
    tmp->next = (*head);
    (*head) = tmp;
}

Node* getNth(Node* head, int n) { // ������� ���������� ��������� �� ������� ������ ��� ��������(�������� �������)
    int counter = 1;
    while (counter < n&& head) {
        head = head->next;
        counter++;
    }
    return head;
}

void print_list(const Node* head, int n) { // ������� �������� ������(�� ������� ����� ��������) � ������ ���� ��������� �������� ������������� � ��������
    Node* tmp = (Node*)malloc(sizeof(Node));
    for (int i = n; i > 0; i--) {
        tmp = getNth(head, i);
        if (i != n) {
            printf(" %c ", (tmp->coefficient > 0) ? '+' : '-');
            if (tmp->degree == 0)
                printf("%d", abs(tmp->coefficient));
            else if (abs(tmp->coefficient) == 1)
                printf("x");
            else
                printf("%dx", abs(tmp->coefficient));
        }
        else {
            if (tmp->degree == 0)
                printf("%d", tmp->coefficient);
            else if (tmp->coefficient == 1)
                printf("x");
            else if (tmp->coefficient == -1)
                printf("-x");
            else
                printf("%dx", tmp->coefficient);
        }
        if (tmp->degree > 1)
            printf("^%d", tmp->degree);
    }
    printf("\n");
}

void print_final_polynomial(Node* L1, Node* L2, int len1, int len2) { // ������� ������ �������� ��������� � �������� ���
    Node* L = NULL; // ��������� �� ������ ������� ���������� ����������
    int n = 0;
    for (int i = 0; i < len1; i++) {
        Node* tmp = (Node*)malloc(sizeof(Node)); // ���������� ����� ��������� ������ �� ��������, ������� �� ����� ��������� � �������� ������
        Node* tmp2 = (Node*)malloc(sizeof(Node)); // ���������� ����� ��������� �� ������ ���������, ����� ����� ���� ��������� ��� �� ���� �����������
        tmp2 = L2;
        for (int j = 0; j < len2; j++) {
            if (L1->degree == tmp2->degree) {
                n++;
                tmp->degree = L1->degree;
                tmp->coefficient = (tmp2->coefficient > L1->coefficient) ? tmp2->coefficient : L1->coefficient;
                tmp->next = L;
                L = tmp;
                break;
            }
            tmp2 = tmp2->next;
        }
        L1 = L1->next;
    }
    printf("L = ");
    if (n != 0)
        print_list(L, n);
    else
        printf("There's no elements in L");
}

int main(void) {
    Node* head1 = NULL; // ��������� �� ������ ������� ������� ����������
    Node* head2 = NULL; // ������� ����������
    int n[] = { 0, 0 }; // ������ ���������� ��������� �������
    // ������ �� ������� ��� ������
    for (int i = 0; i < 2; i++) {
        int choise = 0;
        printf("\nCreate %d polynomial:\n", i + 1);
        do {
            push((i == 0) ? &head1 : &head2);
            n[i]++;
            do {
                number_input("\n  If you wnat to input one more element of the polynomial press 1, else 0: ", &choise);
            } while (choise != 1 && choise != 0);
        } while (choise != 0);
    }
    // ������� �� ������� ��� ����������
    printf("\n    Your polynomials:\nL1 = ");
    print_list(head1, n[0]);
    printf("L2 = ");
    print_list(head2, n[1]);
    print_final_polynomial(head1, head2, n[0], n[1]);
    return 0;
}