#include <stdio.h>
#include <stdlib.h>
#include <time.h> // ���������� ���������� ��� ���������� �������� ������������ ������ - ��������� srand()
#include <string.h>

// ������� ����������

void number_input(char* str, int* p) { // ������� �������� ����������� �������� ���������� � �������� �������, ����������� �� ������(2-�� ��������)
    char string[256];
    printf("%s", str);
    fgets(string, sizeof(string), stdin);
    while (sscanf(string, "%i", p) != 1) {
        printf("Incorrect input, try again!! %s", str);
        fgets(string, sizeof(string), stdin);
    }
}

int* sort_int_arr(int* arr, int len) { // ������� ���������� ��������������� ������
    for (int i = 1; i < len; i++) { // ���������� ����� �� ����������� (sort algorithm - insertsort)
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

int is_repetition(int* arr, int n, int number) { // �������� ������� ����� number � ������� arr
    for (int i = 0; i < n; i++) {
        if (arr[i] == number)
            return 1;
    }
    return 0;
}

// ���������� ��� ������� ������ � ������

struct Edge { // �������� ��������� �������� ����� �����
    int begin; // ����� ���������� ����
    int weight; // ��� �����
    int end; // ����� ��������� ����
    // struct* Edge next; - ���������� ����� ����� ����������� ������
};

struct Edge* graph = NULL; // ����, � ������� �� ����� �������� � ��������� - ���� ������� �������� ��� ����
int size = 0; // ������ ����� ����� - ���������� ����

void add_edge_in_graph(int begin, int end, int weight) { // ������� ��������� ����� � ����
    size++;
    graph = realloc(graph, size * sizeof(struct Edge));
    graph[size - 1].begin = begin;
    graph[size - 1].weight = weight;
    graph[size - 1].end = end;
}

void print_graph(struct Edge* Graph, int Size) { // ������� ��������� ������� ���� - � ������������� � ������������ (��� �����)
    int node_size = 0;
    int* nodes = NULL;
    for (int i = 0; i < Size; i++) {
        if (!is_repetition(nodes, node_size, Graph[i].begin)) {
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = Graph[i].begin;
        }
    } // �������� ������ ��������� �����
    nodes = sort_int_arr(nodes, node_size); // ��������� ������ �����, ����� ������� ��� � �������
    for (int i = 0; i < node_size; i++) { // ������� ������ �� ������� ��������� ����� - ��� ������, ���� ����� ��� ������� �������
        for (int j = 0; j < Size; j++) {
            if (Graph[j].begin == nodes[i])
                printf("%d -(%d)-> %d\n", Graph[j].begin, Graph[j].weight, Graph[j].end);
        }
        printf("\n");
    }
}

int amount_of_nodes() { // ������� ���������� ���������� ����� � �����
    int node_size = 0;
    int* nodes = NULL;
    for (int i = 0; i < size; i++) {
        if (!is_repetition(nodes, node_size, graph[i].begin)) { // ������ �������� �� ������ ���������� ���� (���������)
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = graph[i].begin;
        }
        if (!is_repetition(nodes, node_size, graph[i].end)) { // ������ �������� �� ������ ���������� ���� (�������� - �� �����-�� ����� ����� �� �������� ����)
            node_size++;
            nodes = realloc(nodes, node_size * sizeof(int));
            nodes[node_size - 1] = graph[i].end;
        }
    }
    return node_size;
}

int is_edge_repetition(struct Edge edge, struct Edge* edges, int edges_sizes) { // ����������� ���������� ���� � �������
    for (int i = 0; i < edges_sizes; i++) {
        if (edges[i].begin == edge.begin && edges[i].end == edge.end)
            return 1;
    }
    return 0;
}

int random_graph_initialization(int nodes_amount) { // ������� ������ ������������ ����
    srand(time(NULL) * 7); // �������������� ��������� ��������� �����, ����� �� ������� �� �������� ������� - ��� ����� ������ ��� �������� ����� ��������
    if (nodes_amount == 1) { // ������ � ����� �������� � �����
        add_edge_in_graph(1, 1, (rand() * 13) % 20 + 1);
        return 1;
    }
    for (int i = 1; i <= nodes_amount; i++) {
        int edges_amount = (rand() * 13) % (nodes_amount - 1); // ���������� ��������� ���������� ���� ��� ������� ����
        if (edges_amount == 0) edges_amount++; // ��������� ����������� ������� ������� ����
        int* ends_arr = calloc(edges_amount, sizeof(int)); // ������ ������, � ������� ����� ��������� ������������ ����, � ������� ���� ��������� ���� - i
        for (int j = 0; j < edges_amount; j++) {
            int end;
            do {
                end = (rand() * 13) % nodes_amount + 1;
            } while (is_repetition(ends_arr, edges_amount, end)); // �������� ��������� �������� ���� �����
            ends_arr[j] = end;
            int weight = (rand() * 13) % 20 + 1; // �������� ��������� ��� �����
            add_edge_in_graph(i, end, weight); // �������� ����� � ����
        }
    }
    return nodes_amount;
}

// ���������� ����������� ��������� � ����� (�����, ��� �������� ������, ��� ����)

// �����

struct Edge** cycles_arr = NULL; // ������, � ������� ����� ��������� ������� ����, ������������ �����
int* cycles_arr_sizes = NULL; // � ������� ����� ��������� ������� ������ ������

void cycles_deep_search(struct Edge* Graph, int Size, int node, int current, int* status_arr, int cycle_size, struct Edge* cycle_arr, int* cycles_amount) { // ����������� ������� ��� ������ ����� � ������� ��� ������ ���� ������ �� ������ ������������ ��������� �����
    /*
    ��������� �������:
    1 - ����, � ������� ��������
    2 - ���������� ���� � ���� �����
    3 - ����, �� �������� �������� ���
    4 - ����, � ������� ������ ���������
    5 - ������, ���������� �� ��������� ����� - ������� ����� � ����������� ����������� ����� �����
    6 - ������ �������� ����
    7 - ������� ���� (������ ����), ������� ���� � ���� current �� node
    8 - ��������� �� ����������, ���������� �� ������� ���������� ������
    */
    // ������ ����� ��������: ���� �����, ������� �������� ����, ������� ������� ��������� �����, ��� ��� ��� �������� ��������� �������� �� ���� ������ � ������� � �� ���� ����� ������������
    int copy_cycle_size = cycle_size;
    struct Edge* copy_cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
    memcpy(copy_cycle_arr, cycle_arr, copy_cycle_size * sizeof(struct Edge));
    int* copy_status_arr = malloc(amount_of_nodes() * sizeof(int));
    memcpy(copy_status_arr, status_arr, amount_of_nodes() * sizeof(int));
    for (int i = 0; i < Size; i++) { // ����������� �� ����� �����, ����� ����� ����, ��� ��������� �������� ��������� ���� - current
        if (Graph[i].begin == current) {
            if (Graph[i].end == node) { // ���� ������
                *(cycles_amount) += 1;
                // ��������� ���� ����� � ������ ������
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount) - 1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount) - 1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // ��������� ������ � ��������� ������
                cycles_arr_sizes[*(cycles_amount) - 1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].end - 1] == 1) // ������ � ��� ���������� ���� - ���������� - ���� ���� ��� �� ����� ������
                continue;
            else
                status_arr[Graph[i].end - 1] = 1; // ���� ���� ��� �� ��������, �� ���������� ����� � ������� �� ����� ����
            cycle_size += 1;   // ��������� ������� ���� �����
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge)); 
            cycle_arr[cycle_size - 1] = Graph[i];
            cycles_deep_search(Graph, Size, node, Graph[i].end, status_arr, cycle_size, cycle_arr, cycles_amount);
            // ��������������� ������������ � ���� ��������� �������� ��� ���������� ���������� ������
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
    }
}

int cycles(struct Edge* Graph, int Size) { // ������� ������� ��� ��������� � ��������������� ����� ����� � ���������� ����� (��������: 1->2->1 == 2->1->2) � �� ����������
    int cycles_amount = 0; // ���������� ������
    for (int i = 1; i <= amount_of_nodes(); i++) { // ���������� ��������� ����, � ������� ���� ������ ���� � ���� �����
        for (int j = 0; j < Size; j++) { // ����������� �� ����� �����, ����� ����� ����, ��� ��������� �������� ��������� ���� - i
            if (Graph[j].begin == i) {
                if (Graph[j].end == i) { // ��������� ����, � �������� ���������� ���� �� ������� �����
                    cycles_amount++;
                    // ��������� � ������ ������ ���� �����
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                int* status_arr = calloc(amount_of_nodes(), sizeof(int)); // �������� ������� ����, ����� ����� � ���� ������ ���� ������� ��� ���������� ���� �����
                status_arr[Graph[j].end - 1] = 1;
                int cycle_size = 1;
                struct Edge* cycle_arr = malloc(cycle_size * sizeof(struct Edge)); 
                cycle_arr[cycle_size - 1] = Graph[j]; // ��������� ����� � ������� ���� �����
                cycles_deep_search(Graph, Size, i, Graph[j].end, status_arr, cycle_size, cycle_arr, &cycles_amount); // ������ ��������� ����� � ������� ��� ���������� ���� ������
            }
        }
    }
    return cycles_amount;
}

void output_cycles() {
    int cycles_amount = cycles(graph, size);
    // ������� ��� �����
    printf("  Here is all cycles in graph:\n");
    for (int i = 0; i < cycles_amount; i++) {
        printf("%d", cycles_arr[i][0].begin);
        for (int j = 0; j < cycles_arr_sizes[i]; j++) {
            printf(" -(%d)-> %d", cycles_arr[i][j].weight, cycles_arr[i][j].end);
        }
        printf("\n");
    }
    printf("  Amount of cycles is %d\n\n", cycles_amount); // �������� �� ����������
    // ������ ��� ���������� ����� � ��������� ������
    int unique_cycles_amount = 0; // ������� ���������� ������
    struct Edge** unique_cycles_arr = NULL; // ������ � ����������� �������
    int* unique_cycles_arr_sizes = NULL; // ������� ������� �����
    for (int i = 0; i < cycles_amount; i++) { // �������� ��������������� ��� �����
        int flag = 1; // ����, ���������� �� ����� �������� ��������� ���� � ������ ���������� ������
        for (int j = i; j > 0; j--) { // ������������ � ��������� ��� ����� �� ���� �� ��������
            if (cycles_arr_sizes[i] == cycles_arr_sizes[j - 1] && cycles_arr_sizes[i] != 1) { // ������ ����� if() ����� �������� �� ���������� ����� - ����������� ��� ���� ��������� ���� ��������� ������, ��� ���� �� ��� ����� ���������� �� ���� ��������� ������������������� (����������� ����� ������� ���� ������)
                // �������� � ���� if(), ���� ������� ������ ��������� � ��� - �� �����
                for (int k = 1; k <= cycles_arr_sizes[i] - 1; k++) { // ������� ��������� ������ ��� ���� ��������� �������
                    struct Edge* copy = malloc(cycles_arr_sizes[i] * sizeof(struct Edge));
                    memcpy(copy, cycles_arr[i], cycles_arr_sizes[i] * sizeof(struct Edge)); // ������ ����� ����, ������� ����� �������
                    for (int t = 0; t < k; t++) { // ����� k ���
                        struct Edge save = copy[cycles_arr_sizes[i] - 1];
                        for (int l = cycles_arr_sizes[i] - 1; l >= 0; l--) {
                            copy[l] = copy[l - 1];
                        }
                        copy[0] = save;
                    }
                    for (int t = 0; t < cycles_arr_sizes[i]; t++) { // �������� �� ������������ ����� ������
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
        if (flag || cycles_arr_sizes[i] == 1) { // ���� ���� �� ��������� - �� ��� �������� ������� ���� ��� � ��� �����
            // ��������� ������� ���������� �� �������� ���������� ������
            unique_cycles_amount++;
            unique_cycles_arr = realloc(unique_cycles_arr, unique_cycles_amount * sizeof(struct Edge*));
            unique_cycles_arr[unique_cycles_amount - 1] = cycles_arr[i];
            unique_cycles_arr_sizes = realloc(unique_cycles_arr_sizes, unique_cycles_amount * sizeof(int));
            unique_cycles_arr_sizes[unique_cycles_amount - 1] = cycles_arr_sizes[i];
        }
    }
    // ������� ���������� �����
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

void undirected_cycles_deep_search(struct Edge* Graph, int Size, int node, int current, int* status_arr, int cycle_size, struct Edge* cycle_arr, int* cycles_amount) { // ����������� ������� ��� ������ ����� � ������� ��� ������ ���� ������ �� ������ ������������ ��������� �����
    /*
    ��������� �������:
    1 - ����, � ������� ��������
    2 - ���������� ���� � ���� �����
    3 - ����, �� �������� �������� ���
    4 - ����, � ������� ������ ���������
    5 - ������, ���������� �� ��������� ����� - ������� ����� � ����������� ����������� ����� �����
    6 - ������ �������� ����
    7 - ������� ���� (������ ����), ������� ���� � ���� current �� node
    8 - ��������� �� ����������, ���������� �� ������� ���������� ������
    */
    // ������ ����� ��������: ���� �����, ������� �������� ����, ������� ������� ��������� �����, ��� ��� ��� �������� ��������� �������� �� ���� ������ � ������� � �� ���� ����� ������������
    int copy_cycle_size = cycle_size;
    struct Edge* copy_cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
    memcpy(copy_cycle_arr, cycle_arr, copy_cycle_size * sizeof(struct Edge));
    int* copy_status_arr = malloc(amount_of_nodes() * sizeof(int));
    memcpy(copy_status_arr, status_arr, amount_of_nodes() * sizeof(int));
    for (int i = 0; i < Size; i++) { // ����������� �� ����� �����, ����� ����� ����, ��� ��������� �������� ��������� ���� - current
        if (Graph[i].begin == current) {
            // ��� ���������� ���� � ���� �� ������ ���� �� ����������
            if (Graph[i].end == node && !is_edge_repetition(Graph[i], cycle_arr, cycle_size)) { // ���� ������
                *(cycles_amount) += 1;
                // ��������� ���� ����� � ������ ������
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount)-1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount)-1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // ��������� ������ � ��������� ������
                cycles_arr_sizes[*(cycles_amount)-1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].end - 1] == 1) // ������ � ��� ���������� ���� - ���������� - ���� ���� ��� �� ����� ������
                continue;
            else
                status_arr[Graph[i].end - 1] = 1; // ���� ���� ��� �� ��������, �� ���������� ����� � ������� �� ����� ����
            cycle_size += 1;   // ��������� ������� ���� �����
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge));
            cycle_arr[cycle_size - 1] = Graph[i];
            undirected_cycles_deep_search(Graph, Size, node, Graph[i].end, status_arr, cycle_size, cycle_arr, cycles_amount);
            // ��������������� ������������ � ���� ��������� �������� ��� ���������� ���������� ������
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
        else if (Graph[i].end == current) {
            if (Graph[i].begin == node && !is_edge_repetition(Graph[i], cycle_arr, cycle_size)) { // ���� ������
                *(cycles_amount) += 1;
                // ��������� ���� ����� � ������ ������
                cycles_arr = realloc(cycles_arr, *(cycles_amount) * sizeof(struct Edge*));
                cycles_arr[*(cycles_amount)-1] = malloc((cycle_size + 1) * sizeof(struct Edge));
                for (int j = 0; j < cycle_size; j++) {
                    cycles_arr[*(cycles_amount)-1][j] = cycle_arr[j];
                }
                cycles_arr[*(cycles_amount)-1][cycle_size] = Graph[i];
                cycles_arr_sizes = realloc(cycles_arr_sizes, *(cycles_amount) * sizeof(int)); // ��������� ������ � ��������� ������
                cycles_arr_sizes[*(cycles_amount)-1] = cycle_size + 1;
                continue;
            }
            if (status_arr[Graph[i].begin - 1] == 1) // ������ � ��� ���������� ���� - ���������� - ���� ���� ��� �� ����� ������
                continue;
            else
                status_arr[Graph[i].begin - 1] = 1; // ���� ���� ��� �� ��������, �� ���������� ����� � ������� �� ����� ����
            cycle_size += 1;   // ��������� ������� ���� �����
            cycle_arr = realloc(cycle_arr, cycle_size * sizeof(struct Edge));
            cycle_arr[cycle_size - 1] = Graph[i];
            undirected_cycles_deep_search(Graph, Size, node, Graph[i].begin, status_arr, cycle_size, cycle_arr, cycles_amount);
            // ��������������� ������������ � ���� ��������� �������� ��� ���������� ���������� ������
            cycle_size = copy_cycle_size;
            cycle_arr = malloc(copy_cycle_size * sizeof(struct Edge));
            memcpy(cycle_arr, copy_cycle_arr, copy_cycle_size * sizeof(struct Edge));
            memcpy(status_arr, copy_status_arr, amount_of_nodes() * sizeof(int));
        }
    }
}

int undirected_cycles(struct Edge* Graph, int Size) { // ������� ������� ���������� ������ � ����� �� ���������� �����������
    int cycles_amount = 0; // ���������� ������
    int* status_arr = NULL; // ������, ���������� �� ��������� ����� - ������� ����� � ����������� ����������� ����� �����
    int cycle_size = 0; // ������ �������� ����
    struct Edge* cycle_arr = NULL; // ������� ���� (������ ����), ������� ���� � ���� current �� node
    for (int i = 1; i <= amount_of_nodes(); i++) { // ���������� ����, � ������� ���� ������ ���� � ���� �����
        for (int j = 0; j < Size; j++) { // ����������� �� ����� �����, ����� ����� ����, ��� ���������\�������� �������� ��������� ���� - i
            // ���������� ���������� ����� �� ���� ����� begin � end ������������ ��������� ������������ ��� ������������� �����
            if (Graph[j].begin == i) {
                if (Graph[j].end == i) { // ��������� ����, � �������� ���������� ���� �� ������� �����
                    cycles_amount++;
                    // ��������� � ������ ������ ���� �����
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                status_arr = calloc(amount_of_nodes(), sizeof(int)); // �������� ������� ����, ����� ����� � ���� ������ ���� ������� ��� ���������� ���� �����
                status_arr[Graph[j].end - 1] = 1;
                cycle_size = 1;
                cycle_arr = malloc(cycle_size * sizeof(struct Edge));
                cycle_arr[cycle_size - 1] = Graph[j]; // ��������� ����� � ������� ���� �����
                undirected_cycles_deep_search(Graph, Size, i, Graph[j].end, status_arr, cycle_size, cycle_arr, &cycles_amount); // ������ ��������� ����� � ������� ��� ���������� ���� ������
            }
            else if (Graph[j].end == i) {
                if (Graph[j].begin == i) { // ��������� ����, � �������� ���������� ���� �� ������� �����
                    cycles_amount++;
                    // ��������� � ������ ������ ���� �����
                    cycles_arr = realloc(cycles_arr, cycles_amount * sizeof(struct Edge*));
                    cycles_arr[cycles_amount - 1] = malloc(1 * sizeof(struct Edge));
                    cycles_arr[cycles_amount - 1][0] = Graph[j];
                    cycles_arr_sizes = realloc(cycles_arr_sizes, cycles_amount * sizeof(int));
                    cycles_arr_sizes[cycles_amount - 1] = 1;
                    continue;
                }
                status_arr = calloc(amount_of_nodes(), sizeof(int)); // �������� ������� ����, ����� ����� � ���� ������ ���� ������� ��� ���������� ���� �����
                status_arr[Graph[j].begin - 1] = 1;
                cycle_size = 1;
                cycle_arr = malloc(cycle_size * sizeof(struct Edge));
                cycle_arr[cycle_size - 1] = Graph[j]; // ��������� ����� � ������� ���� �����
                undirected_cycles_deep_search(Graph, Size, i, Graph[j].begin, status_arr, cycle_size, cycle_arr, &cycles_amount); // ������ ��������� ����� � ������� ��� ���������� ���� ������
            }
        }
    }
    return cycles_amount;
}

// ����������� �������� ������

int deep_search_disconnected_graph(int node, int* visited_arr) { // ����������� ������� ����� ���������� ������ ��������� � node - ������������ �������
    int amount = 1; // ���������� ������� � node ������
    visited_arr[node - 1] = 1; // �������� �������, ��� ����������
    for (int i = 0; i < size; i++) {
        // ���������� �� ������� � node ��������� � �������� ������������
        // ���������� ������������
        if (graph[i].begin == node && visited_arr[graph[i].end - 1] == 0) {
            amount += deep_search_disconnected_graph(graph[i].end, visited_arr);
        }
        else if (graph[i].end == node && visited_arr[graph[i].begin - 1] == 0) {
            amount += deep_search_disconnected_graph(graph[i].begin, visited_arr);
        }
    }
    return amount;
}

int minimum_spanning_tree() { // ����� ������������ ��������� ������ � ����� - ������ �������� ��������
    int* visited_arr = calloc(amount_of_nodes(), sizeof(int)); // ������ � ������������ � �������� ��� ������ ����� � �������
    if (deep_search_disconnected_graph(1, visited_arr) != amount_of_nodes()) { // �������� ����� �� ��������� - ������������ ������� (������� ������) ������� ������� �� �����
        printf("It's disconnected graph!! There is no spannings tree here!!\n\n");
        return 0;
    }
    struct Edge* sort_graph = malloc(size * sizeof(struct Edge)); // ������, � ������� �� ��������� ��� ���� � ����������� ��� ���� �� ����������� �����
    memcpy(sort_graph, graph, size * sizeof(struct Edge));
    for (int i = 1; i < size; i++) { // ���������� ����� �� ����������� ����� ���� (sort algorithm - insertsort)
        int j = i;
        while (j > 0 && sort_graph[j - 1].weight > sort_graph[j].weight) {
            struct Edge k = sort_graph[j - 1];
            sort_graph[j - 1] = sort_graph[j];
            sort_graph[j] = k;
            j--;
        }
    }
    struct Edge* subgraph = NULL; // ������, � ������� ����� �������� ����, ������������ ����������� �������� ������
    int subgraph_size = 0;
    int weight_edges_sum = 0; // ��� ��������� ������
    int* considered_nodes = NULL; // ������ � �������� � ������ ���������
    int considered_nodes_amount = 0; // ���������� ������ ����������� � ������
    for (int i = 0; i < size; i++) { // ����������� �� ���� �����
        if (considered_nodes_amount == 0 || (!is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end))) {
            // ������ ��� ������� �������� �������� ����� � ����� ���������� ���������
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // ��������� ����� � ������
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // ���� ���������� ����� �� ������ ����� � �������������� ��������, �� ��������� ���
                considered_nodes_amount += 2;
                considered_nodes = realloc(considered_nodes, considered_nodes_amount * sizeof(int));
                considered_nodes[considered_nodes_amount - 1] = sort_graph[i].begin; // ��������� ��������� �������
                considered_nodes[considered_nodes_amount - 2] = sort_graph[i].end;
                weight_edges_sum += sort_graph[i].weight; // ����������� ��� ������
            }
            else { // ���� ��������� ����, �� ����� ����� �� ��������
                subgraph_size--;
                subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            }
        }
        else if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
            // ������ ��� ������� �������� �������� ����� � ����� �������� ���������
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // ��������� ����� � ������
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // ���� ���������� ����� �� ������ ����� � ��������, �� ��������� ���
                weight_edges_sum += sort_graph[i].weight; // ����������� ��� ������
            }
            else { // ���� ��������� ����, �� ����� ����� �� ��������
                subgraph_size--;
                subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            }
        }
        else if (!is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) || !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
            // ������, ��� ������� �������� ������ ���� ������� �����
            subgraph_size++;
            subgraph = realloc(subgraph, subgraph_size * sizeof(struct Edge));
            subgraph[subgraph_size - 1] = sort_graph[i]; // ��������� ����� � ������
            if (undirected_cycles(subgraph, subgraph_size) == 0) { // ���� ���������� ����� �� ������ ����� � ��������, �� ��������� ���
                considered_nodes_amount += 1;
                considered_nodes = realloc(considered_nodes, considered_nodes_amount * sizeof(int));
                if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end)) {
                    // ������, ��� ������� �������� ������� ����� �� ���� ������
                    considered_nodes[considered_nodes_amount - 1] = sort_graph[i].end;
                }
                else if (is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].end) && !is_repetition(considered_nodes, considered_nodes_amount, sort_graph[i].begin)) {
                    // ������, ��� ������� ��������� ������� ����� �� ���� ������
                    considered_nodes[considered_nodes_amount - 1] = sort_graph[i].begin;
                }
                weight_edges_sum += sort_graph[i].weight; // ����������� ��� ������
            }
            else { // ���� ��������� ����, �� ����� ����� �� ��������
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

// ����������� ���� ����� ����� ���������

int is_connected_nodes(int node, int second, int* visited_arr) {
    if (node == second) // ������� ��� ������� �� �������� � ������ �������
        return 1;
    visited_arr[node - 1] = 1; // �������� �������, ��� ����������
    for (int i = 0; i < size; i++) {
        // ���������� �� ������� � node ��������� � �������, ���� �� �� ����� ��� ���
        if (graph[i].begin == node && visited_arr[graph[i].end - 1] == 0) {
            if (is_connected_nodes(graph[i].end, second, visited_arr)) // ���� ��������� ���� �������, �� ���
                return 1;
        }
    }
    return 0;
}

int miminum_path_between_nodes(int first, int second) { // ���� ���������� �� ���� ���� ����� ������ - �������� ��������
    int* visited_arr = calloc(amount_of_nodes(), sizeof(int));
    if (!is_connected_nodes(first, second, visited_arr)) {
        printf("\nThere is no path from %d to %d node", first, second);
        return 0;
    }
    int* status_arr = calloc(amount_of_nodes(), sizeof(int)); // �������� ��������� ������������� ����
    int* path_arr = calloc(amount_of_nodes(), sizeof(int)); // ��������� ����������� ����(�����) � ��������
    for (int i = 0; i < amount_of_nodes(); i++) // ����������� ��������� ���� �� ���� ������ ����� ������� ��������, ����� ��� ������ ������������ ����� ������� �������
        path_arr[i] = 99999999999999;
    path_arr[first - 1] = 0; // ���� � ��������� ������� �� ����������, ��� ��� �� �� �� �������
    struct Edge** paths = calloc(amount_of_nodes(), sizeof(struct Edge*)); // ��������� ����������� ���� � ��������
    int* paths_sizes = calloc(amount_of_nodes(), sizeof(int)); // ������� ���� �����
    do {
        int min = 99999999999999; // � ���������� �������� ����������� ���������� �� �����-�� ������� �� ��������� �� ��� �� ������������� ������
        int node = 0; // ����� �������� ���� �������, �� ������� �� ����� �������������� ���� � ��������� �������
        for (int i = 0; i < amount_of_nodes(); i++) { 
            if (path_arr[i] < min && status_arr[i] == 0) {
                min = path_arr[i];
                node = i + 1;
            }
        } // ����� ������� �� ������� ����� ������� ����� ��������� �� ����������
        if (node == 0) break; // ������ ������������� ����, ����������� � ������ ����� ���������
        status_arr[node - 1] = 1; // ������������� ��������������� �������, ��� ����������, ����� ������ �� ������������� ���� �� ��
        for (int i = 0; i < size; i++) {
            if (graph[i].begin == node && status_arr[graph[i].end - 1] == 0) { // ������������� ������������ �������, �������� � ���������������
                if (path_arr[node - 1] + graph[i].weight < path_arr[graph[i].end - 1]) {
                    path_arr[graph[i].end - 1] = path_arr[node - 1] + graph[i].weight; // ������ �������� ���� ��������� �� ������ �������� ���������������, ���� ������ ����� �������� ����
                    // �������� ������ � ������������ ������ ���������� ������
                    paths_sizes[graph[i].end - 1] = paths_sizes[node - 1] + 1;
                    paths[graph[i].end - 1] = realloc(paths[graph[i].end - 1], paths_sizes[graph[i].end - 1] * sizeof(struct Edge));
                    memcpy(paths[graph[i].end - 1], paths[node - 1], paths_sizes[node - 1] * sizeof(struct Edge));
                    paths[graph[i].end - 1][paths_sizes[graph[i].end - 1] - 1] = graph[i];
                }
            }
        }
    } while (is_repetition(status_arr, amount_of_nodes(), 0)); // ��������� ������� �� ��� ���, ���� �� ����� ����������� ��� �������
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
    int f; // ���������� �������� �� ��������� ������������� ����� �� ����
    number_input("Input '0' to create own graph\nInput 'n' to create random graph with n nodes\nInput negative number to get graph from file: ", &f);
    if (f == 0) { // ������������ ��� ������ ����
        int begin = 1; // ������������ �������� ��������� ���� ��� ���� �����
        int choise = 0; // ����, ��� ������ �������� �������������
        // !!! �������������� ���������� ���� ���� ����� - ��� ���������� � ��������� � ���������� - ��� ��� ��� ����������� (�������) ���������� ������������� ����� ����� �������� �� ���������� ��
        do {
            int weight = 0, end = 0; // ��� � �������� ���� ����
            // �������� ���� ����� �� ������������
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
    else if (f < 0) { // ������������ �������� ���������� ����
        FILE* fp = fopen("graph_2.bin", "rb");
        fscanf(fp, "%d ", &size);
        graph = realloc(graph, size * sizeof(struct Edge));
        fread(graph, sizeof(struct Edge), size, fp);
        fclose(fp);
    }
    else { // �������� ��������� ����
        random_graph_initialization(f);
    }
    // ���������� ����������� ������ � ���� ��� ���������� �������������
    /*FILE* fp = fopen("graph_2.bin", "wb");
    fprintf(fp, "%d ", size); // ����������� ���������� ���� �����
    fwrite(graph, sizeof(struct Edge), size, fp); // ��� ����
    fclose(fp);*/
    printf("\n\nHere is your graph:\n");
    print_graph(graph, size); // ������� ����
    printf("In your graph: amount of Nodes = %d, amount of Edges = %d\n\n", amount_of_nodes(), size); // ������� ���������� ���� � ������ � �����
    output_cycles(); // ������� ��� ��������� � ����� ����� � ���������� ����� (��������: 1->2->1 == 2->1->2) � �� ����������
    if (amount_of_nodes() == 1) {
        printf("It's useless to find minimum spanning tree while there is only one node!!\n\n");
        printf("It will be impossible to find path between nodes while there is only one node!!\n");
        return 0;
    }
    minimum_spanning_tree(); // ������� ��� ������������ ��������� ������ � ������������ ��� ����
    int first, second; // ��������� �������, ����� �������� ������ ���������� ����
    do {
        number_input("\nInput node from which the shortest path to the other one will be searched: ", &first);
        number_input("Input node to which the shortest path from the other one will be searched: ", &second);
    } while (first > amount_of_nodes() || second > amount_of_nodes() || first == second);
    miminum_path_between_nodes(first, second);
    printf("\n");
    return 0;
}