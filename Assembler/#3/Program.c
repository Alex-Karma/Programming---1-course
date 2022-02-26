#include <stdio.h>

int main(void) {
	char str[4]; // ������ �������� - ��� ����� ����� - �����
	printf("Input string with 3 numbers: ");
place:;
	fgets(str, 4, stdin); // ��������� fgets ������ scanf, ����� ���������� ���� ������ �� 3 ��������
	// ���������, ��� ������� ������ �� �������� ��������
	if (!((int)str[0] >= 48 && (int)str[0] <= 57 && (int)str[1] >= 48 && (int)str[1] <= 57 && (int)str[2] >= 48 && (int)str[2] <= 57)) {
		printf("Wrong input, try again: ");
		if(!(str[0] == '\n' || str[1] == '\n' || str[2] == '\n')) // ��������, �� ���� ���������� �������� ������, ��� 3
			while ((getchar()) != '\n'); // ����������� �� �������� '\n' �������� � �����
		goto place;
	}
	__asm {
		; ��������� �������� �������� � �������� - � �������� ����� �������� �������� ���� ��������
		mov al, str[0]	; ������ �����
		mov ah, str[1]	; ������ �����
		mov bl, str[2]	; ������ �����

		; ���������, ��� ������������������ ������� ��� ������ ����
		cmp al, ah	; ������������� ����� �� ���������� : AL � AH
		jnge condition	; ���� �������� ����� ������������� ��������� AL < AH, �� ��������� � ����� (condition)
		jz condition; ���� ����� ����������� �� ��������� AL � AH = 0, �� ��������� �� �����(condition)

		; ���������� ������� ����� ������ �������� �����, ����� ���������� �������������� ����������
		sub al, ah	; � AL ��������� ������� ������� � ������� ����� ������������������
		sub ah, bl	; � AH ��������� ������� ������� � �������� ����� ������������������
		cmp al, ah	; ������������� ����� �� ���������� : AL � AH
		jz yes	; ���� ����� ����������� �� ��������� AL � AH = 0, �� ��������� �� ����� (yes)
		jmp condition	; ���� �� �� ������� � ����� (yes), �� ������ � ����� (condition)

	yes:
		; �� ����������, ��� ������������������ �������� ��������� �������������� �����������
		; ����� ������ � �������� ������, ��� ����� ������ ���������� ����� ������������������ � ��������, ����� ���������� ����������
		mov al, str[0]	; ������ �����
		mov bl, str[2]	; ������ �����
		mov str[0], bl	; ������ ����� �������� � �������
		mov str[2], al	; ������ ����� �������� � ������
		jmp end	; ��������� � ����� (end), ����� �� ����� � ��� ����� ����� (condition)

	condition:
		; �� ����������, ��� ������������������ �� �������� ��������� �������������� �����������
		; ������ � ������ ����� �� ��������, ��������� ����������� ��������� 2-�� ����� � 3 ����
		mov al, str[1]	; ������ �����
		sub al, 30h	; �������� ��� ���� �� ��������, ����� ���� �������� � ����� ������, � �� ����� ascii(����� ���� ����� ������� �������� ��������)
		cmp al, 4	; ������������� ����� �� ���������� : AL � 4
		jge end	; ���� �������� ����� ������������� ��������� AL >= 4, �� ��������� � �����(end)
		mov bl, 3	; ���������� ����� 3 � �������, ����� ���������� ������������ �������� ���������
		imul bl	; ���� �� �� ������� � �����(end), �� �������� ����� �� 3
		add al, 30h	; ���������� ����� � ����������� �������������
		mov str[1], al	; ����� ����� � �������� ������
	end:
	}
	printf("\nResult: %s\n", str);
}