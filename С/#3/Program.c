#include <stdio.h>
#include <math.h>

int factorial(int y) { // функция для подсчёта факториала числа
    int ans = 1;
    for (int r = y; r != 0; r--) {
        ans *= r;
    }
    return ans;
}

double formula(double i, double x) { // функция для рассчёта элемента ряда под номером i и аргументом х
    return ((pow(-1, i) * factorial(2 * i) * pow(x, i)) / ((1 - 2 * i) * pow(factorial(i), 2) * pow(4, i)));
}

double cheak(char str[256]) { // функция выдаст значение, которое нужно присвоить переменной после проверки на корректность ввода (должны быть введены числа типа double)
    double a;
    char string[256];
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%lf", &a) != 1) {
        printf("Incorrect input, try again, %s", str);
        fgets(string, sizeof(string), stdin);
    }
    return a;
}

int main(void) {
    // инициализируем переменные: количество элементов, способ решения задачи, переменная х, ответ, точность
    int n = 4, choise = 1;
    double x, answer = 1.0, accuracy;

    // вводим данные
    printf("Input number x in range(-1; 1) = ");
    x = cheak("x in range(-1; 1) = "); // используем функцию cheak(), чтобы присвоить значение
    while (x <= -1 || x >= 1) { // проверяем на попадание в область определения
        printf("Wrong input, try again, x in range(-1; 1) = ");
        x = cheak("x in range(-1; 1) = ");
    }

    printf("Input number of the way to solve task (1, 2): ");
    choise = (int)cheak("way to solve task (1, 2): ");
    while (choise != 1 && choise != 2) { // проверяем, что введённое значение для переменной равно 1 или 2
        printf("Wrong input, try again, way to solve task (1, 2): ");
        choise = (int)cheak("way to solve task (1, 2): ");
    }

    switch (choise) { // используем оператор выбора
    case 1:
        printf("Input accuracy (~ 0.01; 0.001) = ");
        accuracy = cheak("accuracy (~ 0.01; 0.001) = ");

        int i = 1; // замена числа n из формулы
        while (fabs(formula(i, x)) >= accuracy) { // Для сходящихся знакочередующихся рядов справедлив следующий критерий: члены следует суммировать до тех пор, пока они по модулю больше заданной точности
            answer += formula(i, x);
            i++;
        }
        break;
    case 2:
        printf("Input number n = ");
        n = (int)cheak("n = ");

        for (int i = 1; i <= n; i++) {
            answer += formula(i, x);
        }
        break;

    }
    printf("Answer is %.50f", answer); // выводим ответ

    // может возникнуть ошибка -nan(ind) (недействительное число), из-за попытки взять факториал от большого числа(от 68)
    return 0;
}