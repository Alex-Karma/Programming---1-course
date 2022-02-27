// ������ ��������� � ��������� ����� 0-90 � ������ �������� 

#include <stdio.h>
#include <math.h>
#include <io.h>
#include <Windows.h> // ���������� ��� ��������� ��������������(��������) � ������� � ������������� ��������� POINT

int in_out(POINT arr[4], POINT xy) { // � ������� ������� ���������� ������������ ���������� �������������� ����� ��������������
    POINT arr_vect[5] = {
        { arr[0].x - xy.x, arr[0].y - xy.y },
        { arr[1].x - xy.x, arr[1].y - xy.y },
        { arr[2].x - xy.x, arr[2].y - xy.y },
        { arr[3].x - xy.x, arr[3].y - xy.y },
        { arr[0].x - xy.x, arr[0].y - xy.y }
    };
    double ans = 0;
    for (int i = 0; i < 4; i++) {
        if(arr_vect[i].x * arr_vect[i + 1].y - arr_vect[i].y * arr_vect[i + 1].x > 0)
            ans += acos((arr_vect[i].x * arr_vect[i + 1].x + arr_vect[i].y * arr_vect[i + 1].y) / sqrt(pow(arr_vect[i].x, 2) + pow(arr_vect[i].y, 2)) / sqrt(pow(arr_vect[i + 1].x, 2) + pow(arr_vect[i + 1].y, 2)));
        else
            ans -= acos((arr_vect[i].x * arr_vect[i + 1].x + arr_vect[i].y * arr_vect[i + 1].y) / sqrt(pow(arr_vect[i].x, 2) + pow(arr_vect[i].y, 2)) / sqrt(pow(arr_vect[i + 1].x, 2) + pow(arr_vect[i + 1].y, 2)));
    }
    // ���� ans �������� ����� 0 ��������, �� ����� ����� ��� ��������������
    // ���� 360 �������� (2��), �� ������ ��������������
    if (ans > -0.1 && ans < 0.1)
        return 0;
    return 1;
}

int main(void) {
    // ��������� ��������: 0, 10, 30, 45, 60, 80, 90
    double alpha = 0; // ���� �������� �������� � �������� = �� 0 �� 90
    int r = 10; // �������� ������� ��������   // 50 ��� ���������
    // ����������� ���������� ������ ��������
    int X = 25; // 500 ��� ���������
    int Y = 5; // 100 ��� ���������
    for (int k = 0; k < 91; k++) {
        alpha = (double)k * 3.1415926535 / 180;
        // ������ ��������� POINT ���������� ���������� ����� x � y 4 ������ ��������
        POINT arr[4] = { {X - r, Y + r}, {X + r, Y + r}, {X + r, Y - r}, {X - r, Y - r} };
        // �������� ���������� ������ �������� � ������ �������� �� ���� alpha
        for (int i = 0; i < 4; i++) {
            int x = arr[i].x;
            int y = arr[i].y;
            // + 300 ��� ���������
            arr[i].x = x * cos(alpha) - y * sin(alpha) + 12; // ���������� ��������, ����� ������� �� ����� �� ������� ���� ������� ��� �������� ����������� ����������� � ������� ��������
            arr[i].y = x * sin(alpha) + y * cos(alpha) + 5;
        }
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 70; j++) {
                POINT xy = { i, j };
                if (in_out(arr, xy))
                    printf(" *");
                else
                    printf("  ");
            }
            printf("\n");
        }
        Sleep(1);
    }
    return 0;
}