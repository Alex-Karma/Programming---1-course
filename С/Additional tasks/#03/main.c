#include <stdio.h>
#include <stdlib.h>
#include <time.h> // библиотека необхадима для реализации создания произвольных графов - настройка srand()
#include <string.h>

// Базовый функционал

void number_input(char* str, int* p) { // функция присвоит необходимое значение переменной в основной функции, находящейся по адресу(2-ой аргумент)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

int* sort_int_arr(int* arr, int len) { // функция возвращает отсортированный массив
    for (int i = 1; i < len; i++) { // сортировка чисел по возрастанию (sort algorithm - insertsort)
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            int k = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = k;
            j--;
        }
    }
    return arr;
}

int is_repetition(int* arr, int n, int number) { // проверка наличия числа number в массиве arr
    for (int i = 0; i < n; i++) {
        if (arr[i] == number)
            return 1;
    }
    return 0;
}

// Функционал для базовой работы с графом

struct Edge { // объектом структуры является ребро графа
    int begin; // номер начального узла
    int weight; // вес ребра
    int end; // номер конечного узла
    // struct* Edge next; - построение графа через односвязный список
};

struct Edge* graph = NULL; // граф, с которым мы будем работать в программе - граф задаётся массивом его рёбер
int size = 0; // размер этого графа - количество рёбер

void add_edge_in_graph(int begin, int end, int weight) { // функция добавляет ребро в граф
    size++;
    graph = realloc(graph, size * sizeof(struct Edge));
    graph[size - 1].begin = begin;
    graph[size - 1].weight = weight;
    graph[size - 1].end = end;
}

void print_graph(struct Edge* Graph, int Size) { // функция аккуратно выводит граф - с разделителями и упорядоченно (при нужде)
    int node_size = 0;
    int* nodes = NULL;
    for (int i = 0; i < Size; i++) {
        if (!is_repetition(nodes, node_size, Graph[i].begin)) {
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = Graph[i].begin;
        }
    } // получили массив начальных узлов
    nodes = sort_int_arr(nodes, node_size); // сортируем массив узлов, чтобы вывести его в порядке
    for (int i = 0; i < node_size; i++) { // выводим массив по порядку начальных узлов - для случая, если вдруг был нарущен порядок
        for (int j = 0; j < Size; j++) {
            if (Graph[j].begin == nodes[i])
                printf("%d -(%d)-> %d\n", Graph[j].begin, Graph[j].weight, Graph[j].end);
        }
        printf("\n");
    }
}

int amount_of_nodes() { // функция возвращает количество узлов в графе
    int node_size = 0;
    int* nodes = NULL;
    for (int i = 0; i < size; i++) {
        if (!is_repetition(nodes, node_size, graph[i].begin)) { // делаем проверку на первый попавшийся узел (начальный)
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = graph[i].begin;
        }
        if (!is_repetition(nodes, node_size, graph[i].end)) { // делаем проверку на первый попавшийся узел (конечный - из каких-то узлов могут не выходить рёбра)
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = graph[i].end;
        }
    }
    return node_size;
}

int is_edge_repetition(struct Edge edge, struct Edge* edges, int edges_sizes) { // определение повторения рёбер в массиве
    for (int i = 0; i < edges_sizes; i++) {
        if (edges[i].begin == edge.begin && edges[i].end == edge.end)
            return 1;
    }
    return 0;
}

int random_graph_initialization(int nodes_amount) { // функция создаёт произвольный граф
    srand(time(NULL) * 7); // инициализируем генератор случайных чисел, чтобы он зависел от текущего времени - так можно каждый раз получать новые значения
    if (nodes_amount == 1) { // случай с одной вершиной в графе
        add_edge_in_graph(1, 1, (rand() * 13) % 20 + 1);
        return 1;
    }
    for (int i = 1; i <= nodes_amount; i++) {
        int edges_amount = (rand() * 13) % (nodes_amount - 1); // определяем рандомное количество рёбер для каждого узла
        if (edges_amount == 0) edges_amount++; // исключаем возможность наличия пустого узла
        int* ends_arr = calloc(edges_amount, sizeof(int)); // создаём массив, в котором будут храниться произвольные узлы, к которым ведёт выбранный узел - i
        for (int j = 0; j < edges_amount; j++) {
            int end;
            do {
                end = (rand() * 13) % nodes_amount + 1;
            } while (is_repetition(ends_arr, edges_amount, end)); // выбираем рандомный конечный узел ребра
            ends_arr[j] = end;
            int weight = (rand() * 13) % 20 + 1; // выбираем рандомный вес ребра
            add_edge_in_graph(i, end, weight); // добавлем ребро в граф
        }
    }
    return nodes_amount;
}

// Функционал реализующий алгоритмы в графе (циклы, мин оставное дерево, мин путь)

// Циклы

struct Edge** cycles_arr = NULL; // массив, в котором будут храниться массивы рёбер, состовляющие циклы
int* cycles_arr_sizes = NULL; // в массиве будут храниться размеры каждых циклов

void cycles_deep_search(struct Edge* Graph, int Size, int node, int current, int* status_arr, int cycle_size, struct Edge* cycle_arr, int* cycles_amount) { // рекурсивная функция для обхода графа в глубину для поиска всех циклов на основе маркирования пройдённых узлов
    /*
    Аргументы функции:
    1 - граф, с которым работаем
    2 - количество рёбер в этом графе
    3 - узел, из которого начинаем ход
    4 - узел, в котором сейчас находимся
    5 - массив, отвечающий за посещение узлов - главное звено в определении простейщего цикла графа
    6 - размер текущего пути
    7 - текущий путь (массив рёбер), который ведёт к узлу current из node
    8 - указатель на переменную, отвечающую за счётчик количества циклов
    */
    // делаем копию значений: пути цикла, размера текущего пути, массива статуса посещения узлов, так как эти значения постоянно меняются по ходу поиска в глубину и их надо будет восстановить
    int copy_cycle_size = cycle_size;
    struct Edge* copy_cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
    memcpy(copy_cycle_arr, cycle_arr, copy_cycle_size * sizeof(struct Edge));
    int* copy_status_arr = malloc(amount_of_nodes() * sizeof(int));
    memcpy(copy_status_arr, status_arr, amount_of_nodes() * sizeof(int));
    for (int i = 0; i < Size; i++) { // пробегаемся по всему графу, чтобы найти рёбра, где начальным является выбранный узел - current
        if (Graph[i].begin == current) {
            if (Graph[i].end == node) { // цикл найден
                *(cycles_amount) += 1;
                // добавляем путь цикла в массив циклов
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount) - 1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount) - 1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // обновляем массив с размерами циклов
                cycles_arr_sizes[*(cycles_amount) - 1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].end - 1] == 1) // попали в уже посещённый узел - пропускаем - этот путь уже не будет циклом
                continue;
            else
                status_arr[Graph[i].end - 1] = 1; // если узел ещё не посетили, то продолжаем поиск в глубину от этого узла
            cycle_size += 1;   // обновляем текущий путь цикла
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge)); 
            cycle_arr[cycle_size - 1] = Graph[i];
            cycles_deep_search(Graph, Size, node, Graph[i].end, status_arr, cycle_size, cycle_arr, cycles_amount);
            // восстанавливаем изменившиеся в ходе алгоритма значения для дальнейщей корректной работы
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
    }
}

int cycles(struct Edge* Graph, int Size) { // функция выводит все имеющиеся в ОРИЕНТИРОВАННОМ графе циклы и уникальные циклы (например: 1->2->1 == 2->1->2) И их количество
    int cycles_amount = 0; // количество циклов
    for (int i = 1; i <= amount_of_nodes(); i++) { // отыскиваем начальные узлы, к которым ведёт каждый узел и ищем петли
        for (int j = 0; j < Size; j++) { // пробегаемся по всему графу, чтобы найти рёбра, где начальным является выбранный узел - i
            if (Graph[j].begin == i) {
                if (Graph[j].end == i) { // проверяем узел, с которого начинается цикл на наличие петли
                    cycles_amount++;
                    // добавляем в массив циклов наши петли
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                int* status_arr = calloc(amount_of_nodes(), sizeof(int)); // отмечаем текущий узел, чтобы потом в него нельзя было попасть при построении пути цикла
                status_arr[Graph[j].end - 1] = 1;
                int cycle_size = 1;
                struct Edge* cycle_arr = malloc(cycle_size * sizeof(struct Edge)); 
                cycle_arr[cycle_size - 1] = Graph[j]; // добавляем ребро в текущий путь цикла
                cycles_deep_search(Graph, Size, i, Graph[j].end, status_arr, cycle_size, cycle_arr, &cycles_amount); // теперь реализуем поиск в глубину для нахождения всех циклов
            }
        }
    }
    return cycles_amount;
}

void output_cycles() {
    int cycles_amount = cycles(graph, size);
    // выводим все циклы
    printf("  Here is all cycles in graph:\n");
    for (int i = 0; i < cycles_amount; i++) {
        printf("%d", cycles_arr[i][0].begin);
        for (int j = 0; j < cycles_arr_sizes[i]; j++) {
            printf(" -(%d)-> %d", cycles_arr[i][j].weight, cycles_arr[i][j].end);
        }
        printf("\n");
    }
    printf("  Amount of cycles is %d\n\n", cycles_amount); // печатаем их количество
    // отберём все цникальные циклы в отдельный массив
    int unique_cycles_amount = 0; // счётчик уникальных циклов
    struct Edge** unique_cycles_arr = NULL; // массив с уникальными циклами
    int* unique_cycles_arr_sizes = NULL; // размеры каждого цикла
    for (int i = 0; i < cycles_amount; i++) { // выбираем последовательно все циклы
        int flag = 1; // флаг, отвечающий за нужду добавить выбранный цикл в массив уникальных циклов
        for (int j = i; j > 0; j--) { // сопостовляем с выбранным все циклы до него на сходство
            if (cycles_arr_sizes[i] == cycles_arr_sizes[j - 1] && cycles_arr_sizes[i] != 1) { // внутри этого if() лежит проверка на одинаковые циклы - реализуется это путём сравнения двух выбранных циклов, где один из них будет рассмотрен во всех возможных последовательностях (циклический сдвиг массива рёбер вправо)
                // попадаем в тело if(), если размеры циклов одинаковы и они - не петли
                for (int k = 1; k <= cycles_arr_sizes[i] - 1; k++) { // сделаем сравнения циклов для всех возможных сдвигов
                    struct Edge* copy = malloc(cycles_arr_sizes[i] * sizeof(struct Edge));
                    memcpy(copy, cycles_arr[i], cycles_arr_sizes[i] * sizeof(struct Edge)); // делаем копию пути, которую будем двигать
                    for (int t = 0; t < k; t++) { // сдвиг k раз
                        struct Edge save = copy[cycles_arr_sizes[i] - 1];
                        for (int l = cycles_arr_sizes[i] - 1; l >= 0; l--) {
                            copy[l] = copy[l - 1];
                        }
                        copy[0] = save;
                    }
                    for (int t = 0; t < cycles_arr_sizes[i]; t++) { // проверка на идентичность после сдвига
                        if (copy[t].begin == cycles_arr[j - 1][t].begin && copy[t].end == cycles_arr[j - 1][t].end) {
                            flag = 0;
                            break;
                        }
                    }
                    if (!flag) break;
                }
                if (!flag) break;
            }
        }
        if (flag || cycles_arr_sizes[i] == 1) { // если флаг не изменился - не был встречен похожий цикл или у нас петля
            // обновляем массивы отвечающие за хранение цникальных циклов
            unique_cycles_amount++;
            unique_cycles_arr = realloc(unique_cycles_arr, unique_cycles_amount * sizeof(struct Edge*));
            unique_cycles_arr[unique_cycles_amount - 1] = cycles_arr[i];
            unique_cycles_arr_sizes = realloc(unique_cycles_arr_sizes, unique_cycles_amount * sizeof(int));
            unique_cycles_arr_sizes[unique_cycles_amount - 1] = cycles_arr_sizes[i];
        }
    }
    // выводим уникальные циклы
    printf("  Here is all unique cycles in graph:\n");
    for (int i = 0; i < unique_cycles_amount; i++) {
        printf("%d", unique_cycles_arr[i][0].begin);
        for (int j = 0; j < unique_cycles_arr_sizes[i]; j++) {
            printf(" -(%d)-> %d", unique_cycles_arr[i][j].weight, unique_cycles_arr[i][j].end);
        }
        printf("\n");
    }
    printf("  Amount of unique cycles is %d\n\n", unique_cycles_amount);
    free(cycles_arr_sizes);
    cycles_arr_sizes = NULL;
    free(cycles_arr);
    cycles_arr = NULL;
}

void undirected_cycles_deep_search(struct Edge* Graph, int Size, int node, int current, int* status_arr, int cycle_size, struct Edge* cycle_arr, int* cycles_amount) { // рекурсивная функция для обхода графа в глубину для поиска всех циклов на основе маркирования пройдённых узлов
    /*
    Аргументы функции:
    1 - граф, с которым работаем
    2 - количество рёбер в этом графе
    3 - узел, из которого начинаем ход
    4 - узел, в котором сейчас находимся
    5 - массив, отвечающий за посещение узлов - главное звено в определении простейщего цикла графа
    6 - размер текущего пути
    7 - текущий путь (массив рёбер), который ведёт к узлу current из node
    8 - указатель на переменную, отвечающую за счётчик количества циклов
    */
    // делаем копию значений: пути цикла, размера текущего пути, массива статуса посещения узлов, так как эти значения постоянно меняются по ходу поиска в глубину и их надо будет восстановить
    int copy_cycle_size = cycle_size;
    struct Edge* copy_cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
    memcpy(copy_cycle_arr, cycle_arr, copy_cycle_size * sizeof(struct Edge));
    int* copy_status_arr = malloc(amount_of_nodes() * sizeof(int));
    memcpy(copy_status_arr, status_arr, amount_of_nodes() * sizeof(int));
    for (int i = 0; i < Size; i++) { // пробегаемся по всему графу, чтобы найти рёбра, где начальным является выбранный узел - current
        if (Graph[i].begin == current) {
            // при добавлении рёбер в цикл не должно быть их повторений
            if (Graph[i].end == node && !is_edge_repetition(Graph[i], cycle_arr, cycle_size)) { // цикл найден
                *(cycles_amount) += 1;
                // добавляем путь цикла в массив циклов
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount)-1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount)-1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // обновляем массив с размерами циклов
                cycles_arr_sizes[*(cycles_amount)-1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].end - 1] == 1) // попали в уже посещённый узел - пропускаем - этот путь уже не будет циклом
                continue;
            else
                status_arr[Graph[i].end - 1] = 1; // если узел ещё не посетили, то продолжаем поиск в глубину от этого узла
            cycle_size += 1;   // обновляем текущий путь цикла
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge));
            cycle_arr[cycle_size - 1] = Graph[i];
            undirected_cycles_deep_search(Graph, Size, node, Graph[i].end, status_arr, cycle_size, cycle_arr, cycles_amount);
            // восстанавливаем изменившиеся в ходе алгоритма значения для дальнейщей корректной работы
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
        else if (Graph[i].end == current) {
            if (Graph[i].begin == node && !is_edge_repetition(Graph[i], cycle_arr, cycle_size)) { // цикл найден
                *(cycles_amount) += 1;
                // добавляем путь цикла в массив циклов
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount)-1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount)-1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // обновляем массив с размерами циклов
                cycles_arr_sizes[*(cycles_amount)-1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].begin - 1] == 1) // попали в уже посещённый узел - пропускаем - этот путь уже не будет циклом
                continue;
            else
                status_arr[Graph[i].begin - 1] = 1; // если узел ещё не посетили, то продолжаем поиск в глубину от этого узла
            cycle_size += 1;   // обновляем текущий путь цикла
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge));
            cycle_arr[cycle_size - 1] = Graph[i];
            undirected_cycles_deep_search(Graph, Size, node, Graph[i].begin, status_arr, cycle_size, cycle_arr, cycles_amount);
            // восстанавливаем изменившиеся в ходе алгоритма значения для дальнейщей корректной работы
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
    }
}

int undirected_cycles(struct Edge* Graph, int Size) { // функция выводит количество циклов в графе со сброшенной ориентацией
    int cycles_amount = 0; // количество циклов
    int* status_arr = NULL; // массив, отвечающий за посещение узлов - главное звено в определении простейщего цикла графа
    int cycle_size = 0; // размер текущего пути
    struct Edge* cycle_arr = NULL; // текущий путь (массив рёбер), который ведёт к узлу current из node
    for (int i = 1; i <= amount_of_nodes(); i++) { // отыскиваем узлы, к которым ведёт каждый узел и ищем петли
        for (int j = 0; j < Size; j++) { // пробегаемся по всему графу, чтобы найти рёбра, где НАЧАЛЬНЫМ\КОНЕЧНЫМ является выбранный узел - i
            // сбрасываем ориентацию графа за счёт смены begin и end относительно алгоритма применяемого для направленного цикла
            if (Graph[j].begin == i) {
                if (Graph[j].end == i) { // проверяем узел, с которого начинается цикл на наличие петли
                    cycles_amount++;
                    // добавляем в массив циклов наши петли
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                status_arr = calloc(amount_of_nodes(), sizeof(int)); // отмечаем текущий узел, чтобы потом в него нельзя было попасть при построении пути цикла
                status_arr[Graph[j].end - 1] = 1;
                cycle_size = 1;
                cycle_arr = malloc(cycle_size * sizeof(struct Edge));
                cycle_arr[cycle_size - 1] = Graph[j]; // добавляем ребро в текущий путь цикла
                undirected_cycles_deep_search(Graph, Size, i, Graph[j].end, status_arr, cycle_size, cycle_arr, &cycles_amount); // теперь реализуем поиск в глубину для нахождения всех циклов
            }
            else if (Graph[j].end == i) {
                if (Graph[j].begin == i) { // проверяем узел, с которого начинается цикл на наличие петли
                    cycles_amount++;
                    // добавляем в массив циклов наши петли
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                status_arr = calloc(amount_of_nodes(), sizeof(int)); // отмечаем текущий узел, чтобы потом в него нельзя было попасть при построении пути цикла
                status_arr[Graph[j].begin - 1] = 1;
                cycle_size = 1;
                cycle_arr = malloc(cycle_size * sizeof(struct Edge));
                cycle_arr[cycle_size - 1] = Graph[j]; // добавляем ребро в текущий путь цикла
                undirected_cycles_deep_search(Graph, Size, i, Graph[j].begin, status_arr, cycle_size, cycle_arr, &cycles_amount); // теперь реализуем поиск в глубину для нахождения всех циклов
            }
        }
    }
    return cycles_amount;
}

// Минимальное оставное дерево

int deep_search_disconnected_graph(int node, int* visited_arr) { // рекурсивная функция вернёт количество вершин связанных с node - произвольная вершина
    int amount = 1; // количество связных с node вершин
    visited_arr[node - 1] = 1; // помечаем вершину, как пройденную
    for (int i = 0; i < size; i++) {
        // проходимся по смежным с node вершинами и помечаем непройденные
        // ориентация сбрасывается
        if (graph[i].begin == node && visited_arr[graph[i].end - 1] == 0) {
            amount += deep_search_disconnected_graph(graph[i].end, visited_arr);
        }
        else if (graph[i].end == node && visited_arr[graph[i].begin - 1] == 0) {
            amount += deep_search_disconnected_graph(graph[i].begin, visited_arr);
        }
    }
    return amount;
}

int minimum_spanning_tree() { // поиск минимального оставного дерева в графе - жадный Алгоритм Краскала
    int* visited_arr = calloc(amount_of_nodes(), sizeof(int)); // массив с присутствием в вершинах для обхода графа в глубину
    if (deep_search_disconnected_graph(1, visited_arr) != amount_of_nodes()) { // проверка графа на связность - произвольная вершина (выбрана первая) связана связана со всеми
        printf("It's disconnected graph!! There is no spannings tree here!!\n\n");
        return 0;
    }
    struct Edge* sort_graph = malloc(size * sizeof(struct Edge)); // массив, в который мы скопируем наш граф и отсортируем его рёбра по возрастанию весов
    memcpy(sort_graph, graph, size * sizeof(struct Edge));
    for (int i = 1; i < size; i++) { // сортировка графа по возрастанию весов рёбер (sort algorithm - insertsort)
        int j = i;
        while (j > 0 && sort_graph[j - 1].weight > sort_graph[j].weight) {
            struct Edge k = sort_graph[j - 1];
            sort_graph[j - 1] = sort_graph[j];
            sort_graph[j] = k;
            j--;
        }
    }
    struct Edge* subgraph = NULL; // массив, в котором будут состоять рёбра, составляющие минимальное оставное дерево
    int subgraph_size = 0;
    int weight_edges_sum = 0; // вес оставного дерева
    int* considered_nodes = NULL; // массив с учтёнными в дереве вершинами
    int considered_nodes_amount = 0; // количество вершин зачислинных в дерево
    for (int i = 0; i < size; i++) { // пробегаемся по всем рёбрам
        if (considered_nodes_amount == 0 || (!is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end))) {
            // случай при котором пытаемся добавить ребро с двумя неучтёнными вершинами
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // добавляем ребро в дерево
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // если добавление ребра не создаёт циклы в ненаправленном подграфе, то добавляем его
                considered_nodes_amount += 2;
                considered_nodes = realloc(considered_nodes, considered_nodes_amount * sizeof(int));
                considered_nodes[considered_nodes_amount - 1] = sort_graph[i].begin; // добавляем неучтённые вершины
                considered_nodes[considered_nodes_amount - 2] = sort_graph[i].end;
                weight_edges_sum += sort_graph[i].weight; // увеличиваем вес дерева
            }
            else { // если возникает цикл, то такое ребро не подходит
                subgraph_size--;
                subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            }
        }
        else if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
            // случай при котором пытаемся добавить ребро с двумя учтёнными вершинами
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // добавляем ребро в дерево
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // если добавление ребра не создаёт циклы в подграфе, то добавляем его
                weight_edges_sum += sort_graph[i].weight; // увеличиваем вес дерева
            }
            else { // если возникает цикл, то такое ребро не подходит
                subgraph_size--;
                subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            }
        }
        else if (!is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) || !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
            // случай, при котором неучтена только одна вершина ребра
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // добавляем ребро в дерево
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // если добавление ребра не создаёт циклы в подграфе, то добавляем его
                considered_nodes_amount += 1;
                considered_nodes = realloc(considered_nodes, considered_nodes_amount * sizeof(int));
                if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
                    // случай, при котором конечная вершина ребра не была учтена
                    considered_nodes[considered_nodes_amount - 1] = sort_graph[i].end;
                }
                else if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin)) {
                    // случай, при котором начальная вершина ребра не была учтена
                    considered_nodes[considered_nodes_amount - 1] = sort_graph[i].begin;
                }
                weight_edges_sum += sort_graph[i].weight; // увеличиваем вес дерева
            }
            else { // если возникает цикл, то такое ребро не подходит
                subgraph_size--;
                subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            }
        }
        free(cycles_arr_sizes);
        cycles_arr_sizes = NULL;
        free(cycles_arr);
        cycles_arr = NULL;
    }
    printf("Sum of weights of edges in minimum spanning tree = %d\n", weight_edges_sum);
    printf("  Edges in this tree:\n\n");
    print_graph(subgraph, subgraph_size);
    return 1;
}

// Минимальный путь между двумя вершинами

int is_connected_nodes(int node, int second, int* visited_arr) {
    if (node == second) // условие при котором мы приходим в нужную вершину
        return 1;
    visited_arr[node - 1] = 1; // помечаем вершину, как пройденную
    for (int i = 0; i < size; i++) {
        // проходимся по смежным с node вершинами и смотрим, были ли мы здесь или нет
        if (graph[i].begin == node && visited_arr[graph[i].end - 1] == 0) {
            if (is_connected_nodes(graph[i].end, second, visited_arr)) // если встретили нашу вершину, то УРА
                return 1;
        }
    }
    return 0;
}

int miminum_path_between_nodes(int first, int second) { // ищем кратчайщий по весу путь между узлами - алгоритм Дейкстры
    int* visited_arr = calloc(amount_of_nodes(), sizeof(int));
    if (!is_connected_nodes(first, second, visited_arr)) {
        printf("\nThere is no path from %d to %d node", first, second);
        return 0;
    }
    int* status_arr = calloc(amount_of_nodes(), sizeof(int)); // отмечаем полностью рассмотренные узлы
    int* path_arr = calloc(amount_of_nodes(), sizeof(int)); // сохраняем минимальные пути(число) к вершинам
    for (int i = 0; i < amount_of_nodes(); i++) // присваиваем значениям пути до всех вершин очень большое значение, чтобы при поиске минимального точно нашлось меньшее
        path_arr[i] = 99999999999999;
    path_arr[first - 1] = 0; // пути в начальную вершину не существует, так как мы из неё выходим
    struct Edge** paths = calloc(amount_of_nodes(), sizeof(struct Edge*)); // сохраняем минимальные пути к вершинам
    int* paths_sizes = calloc(amount_of_nodes(), sizeof(int)); // размеры этих путей
    do {
        int min = 99999999999999; // в переменной окажется минимальное расстояние до какой-то вершины от начальной из ещё не рассмотренный вершин
        int node = 0; // здесь окажется сама вершина, из которой мы будем оптимизировать пути в следующие вершины
        for (int i = 0; i < amount_of_nodes(); i++) { 
            if (path_arr[i] < min && status_arr[i] == 0) {
                min = path_arr[i];
                node = i + 1;
            }
        } // нашли вершину до которой можно быстрее всего добраться из начальнойы
        if (node == 0) break; // начали рассматривать узлы, несвязанные с нашими двумя вершинами
        status_arr[node - 1] = 1; // устанавливаем рассматриваемую вершину, как посещённую, чтобы больше не анализировать пути из неё
        for (int i = 0; i < size; i++) {
            if (graph[i].begin == node && status_arr[graph[i].end - 1] == 0) { // рассматриваем непосещённые вершины, соседние с рассматриваемой
                if (path_arr[node - 1] + graph[i].weight < path_arr[graph[i].end - 1]) {
                    path_arr[graph[i].end - 1] = path_arr[node - 1] + graph[i].weight; // меняем значение пути достижеия до вершин соседних рассматриваемой, если найден более короткий путь
                    // изменяем массив с минимальными путями достижения вершин
                    paths_sizes[graph[i].end - 1] = paths_sizes[node - 1] + 1;
                    paths[graph[i].end - 1] = realloc(paths[graph[i].end - 1], paths_sizes[graph[i].end - 1] * sizeof(struct Edge));
                    memcpy(paths[graph[i].end - 1], paths[node - 1], paths_sizes[node - 1] * sizeof(struct Edge));
                    paths[graph[i].end - 1][paths_sizes[graph[i].end - 1] - 1] = graph[i];
                }
            }
        }
    } while (is_repetition(status_arr, amount_of_nodes(), 0)); // применяем алгортм до тех пор, пока не будут рассмотрены все вершины
place:;
    printf("\nMinimum path from %d to %d node = %d\n", first, second, path_arr[second - 1]);
    printf("  Here is path: ");
    printf("%d", paths[second - 1][0].begin);
    for (int i = 0; i < paths_sizes[second - 1]; i++) {
        printf(" -(%d)-> %d", paths[second - 1][i].weight, paths[second - 1][i].end);
    }
    return 1;
}

int main() {
    int f; // переменная отвечает за выбранный пользователем режим из меню
    number_input("Input '0' to create own graph\nInput 'n' to create random graph with n nodes\nInput negative number to get graph from file: ", &f);
    if (f == 0) { // пользователь сам создаёт граф
        int begin = 1; // пользователь выбирает начальный узел для рёбер графа
        int choise = 0; // флаг, для выбора действий пользователем
        // !!! Предполагается корректный ввод рёбер графа - без повторений и глупостей с нумерацией - так как при графическом (удобном) оформлении инициализации графа такие проблемы не появлялись бы
        do {
            int weight = 0, end = 0; // вес и конечный узел рёбер
            // получаем рёбра графа от пользователя
            printf("\nInput node to which the %d node leads", begin);
            number_input(": ", &end);
            printf("Input weight of edge between nodes %d -> %d", begin, end);
            number_input(": ", &weight);
            printf("\n  If you want to continue creating edges to %d node, Input '1'\n", begin);
            printf("  If you want to create edges to other nodes, Input '2'\n");
            printf("  If you finished creating your graph, Input '0'\n");
            number_input("Input: ", &choise);
            add_edge_in_graph(begin, end, weight); // add struct Edge to arr
            if (choise == 2)
                number_input("\nInput number of node to which you want to create edges: ", &begin);
        } while (choise != 0);
    }
    else if (f < 0) { // пользователь получает сохранённый граф
        FILE* fp = fopen("graph_2.bin", "rb");
        fscanf(fp, "%d ", &size);
        graph = realloc(graph, size * sizeof(struct Edge));
        fread(graph, sizeof(struct Edge), size, fp);
        fclose(fp);
    }
    else { // создаётся рандомный граф
        random_graph_initialization(f);
    }
    // сохранение самодельных графов в файл для повторного использования
    /*FILE* fp = fopen("graph_2.bin", "wb");
    fprintf(fp, "%d ", size); // записывааем количество рёбер графа
    fwrite(graph, sizeof(struct Edge), size, fp); // сам граф
    fclose(fp);*/
    printf("\n\nHere is your graph:\n");
    print_graph(graph, size); // выводим граф
    printf("In your graph: amount of Nodes = %d, amount of Edges = %d\n\n", amount_of_nodes(), size); // выводим количество рёбер и вершин в графе
    output_cycles(); // выводим все имеющиеся в графе циклы и уникальные циклы (например: 1->2->1 == 2->1->2) И их количество
    if (amount_of_nodes() == 1) {
        printf("It's useless to find minimum spanning tree while there is only one node!!\n\n");
        printf("It will be impossible to find path between nodes while there is only one node!!\n");
        return 0;
    }
    minimum_spanning_tree(); // выводим вес минимального оставного дерева и составляющие его рёбра
    int first, second; // различные вершины, между которыми ищется кратчайщий путь
    do {
        number_input("\nInput node from which the shortest path to the other one will be searched: ", &first);
        number_input("Input node to which the shortest path from the other one will be searched: ", &second);
    } while (first > amount_of_nodes() || second > amount_of_nodes() || first == second);
    miminum_path_between_nodes(first, second);
    printf("\n");
    return 0;
}