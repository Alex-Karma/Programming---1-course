// печать квадратов в диапозоне углов 0-90 с пмощью звёздочек 

#include <stdio.h>
#include <math.h>
#include <io.h>
#include <Windows.h> // библиотека для отрисовки многоугольника(квадрата) в консоле и использования структуры POINT

int in_out(POINT arr[4], POINT xy) { // с помощью формулы скалярного произведения определяем принадлежность точки многоугольнику
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
    // если ans примерно равен 0 градусов, то точка лежит вне многоугольника
    // если 360 градусов (2пи), то внутри многоугольника
    if (ans > -0.1 && ans < 0.1)
        return 0;
    return 1;
}

int main(void) {
    // наглядные значения: 0, 10, 30, 45, 60, 80, 90
    double alpha = 0; // угол поворота квадрата в градусах = от 0 до 90
    int r = 10; // половина стороны квадрата   // 50 для отрисовки
    // изначальные координаты центра квадрата
    int X = 25; // 500 для отрисовки
    int Y = 5; // 100 для отрисовки
    for (int k = 0; k < 91; k++) {
        alpha = (double)k * 3.1415926535 / 180;
        // массив структура POINT определяет координаты точки x и y 4 вершин квадрата
        POINT arr[4] = { {X - r, Y + r}, {X + r, Y + r}, {X + r, Y - r}, {X - r, Y - r} };
        // изменяем координаты вершин квадрата с учётом поворота на угол alpha
        for (int i = 0; i < 4; i++) {
            int x = arr[i].x;
            int y = arr[i].y;
            // + 300 для отрисовки
            arr[i].x = x * cos(alpha) - y * sin(alpha) + 12; // прибавляем значение, чтобы квадрат не вышал за границы окна консоли при заданных изначальных координатах и размере квадрата
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