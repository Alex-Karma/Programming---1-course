struct member { // ��������� ����� ������� ������� �� �������
    char full_name[60]; // ���
    char club[30];
    char role[11]; // goalkeeper, defender, midfielder, striker
    int age;
    int matches;
    int goals_scored;
};

// ��������� ������� ��� ������ � ����� ������
void add_data(); // ���������� ������ � ����

void remove_data(); // �������� �������� ������ �� ����

void search_data(); // ����� ������� �� ��������� ������������� (������) ����

void edit_data(); // �������������� �������� ������ � ����

void sort_database(); // ���������� ������ � ���� �� ��������� ������������� (������) ����

void output_database(); // ����� �� ����� ����������� ���� � ��������� ����

int contain_latin_letters(char* str, int len) { // ������� ���������, �������� �� ������ ���������� ��� ������������� (��������� ����� � �����)
    char aval[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM "; // ������ ���������� ��������
    int aval_length = strlen(aval); // ������������ ����� ������ aval c ������� ������� �� ���������� string.h
    int f = 0;
    for (int j = 0; j < len; j++) {
        for (int i = 0; i < aval_length; i++) {
            if (aval[i] == str[j]) // ���� ������� ����������, �� ���������� 1 (������ - ������ �������� ����������)
                f++;
        }
    }
    if(f == len)
        return 1;
    return 0; // ���� �� ����� ���������� 1, �� ���������� 0 (����)
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

int num_len(int num) { // ������� ���������� ����� ����� (~ 7 -> 1; 145 -> 3)
    int ans = 0;
    do {
        ans++;
        if (num < pow(10, ans))
            return ans;
    } while (1);
}