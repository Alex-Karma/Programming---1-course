#include <stdio.h>
#define N 16 // ������ ��������

int main() {
    int amount = 0; // ����� �������
    int A[N]; // ������� ���������
    int B[N];
    int* C[N * 2]; // ������ ������� �������� ��������� 
    // ������ �������� � �������
    printf("  Input data in array A\n");
    for (int i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    printf("\n  Input data in array B\n");
    for (int i = 0; i < N; i++) {
        printf("B[%d] = ", i);
        scanf("%d", &B[i]);
    }
    // ���������� ���������� �������� �� ���������
    printf("\n  Array A befor processing: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n  Array B befor processing: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", B[i]);
    }
    __asm {
        // ��������� ��������� ��������
        sub ecx, ecx  // ������� ����� � ��������� � �������� A � B
        mov ebx, ecx  // ��������� � ������� � � ������� �������

        // ������ �����
        step : cmp ecx, LENGTH A // ������� ����������
        jae end // ���� �� - ������� ����������

        // ����� ���������� �������� � ���������� �������� ��������
        mov edx, A[ecx * TYPE A] // �������� ������� ������� � � ������� (32 ������)
        cmp edx, B[ecx * TYPE B] // ������������
        jge no // ���� �������� ����� ������������� ��������� A[i] >= B[i], �� ��������� � �����(no), ����� ������� ���������

        lea eax, A[ecx * TYPE A]  // �������� � eax ����� �������� �������� �� �
        mov C[ebx * TYPE C], eax // �������� � ������ � ����� ��������
        inc ebx // ��������� � ���������� �������� ������� �

        lea eax, B[ecx * TYPE B]  // �������� � eax ����� �������� �������� �� B
        mov C[ebx * TYPE C], eax // �������� � ������ � ����� ��������
        inc ebx // ��������� � ���������� �������� ������� �

        xchg edx, B[ecx * TYPE B] // ������ ������� �������� A � B ��������
        mov A[ecx * TYPE A], edx

        // ���� ������ �� ���������, �� ���� A[i] >= B[i]
        no :
        inc ecx  // ��������� � ���������� �������� �������� � � �
        jmp step // ��� � ������ �����

        // ���������� ��� �������� �������� � � �
        end :
        mov amount, ebx // �������� � ���������� ���������� ��������, �� �� � ��� ���� ������, ��� �������
    }
    // ���������� ���������� �������� ����� ���������
    printf("\n\n  Array A after processing: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n  Array B after processing: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", B[i]);
    }
    // ���������� ���������� ��������� � ������ ��������
    printf("\n\n  There is %d changes: \n", amount / 2);
    for (int i = 0; i < amount / 2; i++) {
        printf("A[%d] = %p  ", i, C[2 * i]);
        printf("B[%d] = %p\n", i, C[2 * i + 1]);
    }
    exit(0);
}