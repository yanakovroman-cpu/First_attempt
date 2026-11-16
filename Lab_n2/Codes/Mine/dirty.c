#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

// int *find_max(int *arr, int n) {
//     if (arr == NULL || n <= 0) {
//         return NULL;
//     }
//     int *max = arr;
//     for (int *p = arr; p < arr + n; p++) {
//         if (*p > *max) {
//             max = p;
//         }
//     }
//     return max;
// }

// int main(void) {
//     setlocale(LC_ALL, "ru_RU.UTF-8");
//     int arr[5] = {0, 10, 40};
//     int *best = find_max(arr, sizeof(arr) / sizeof(arr[0]));
//     if (best != NULL) {
//         printf("[%d] [%d]", *best, (int) (best - arr));
//     }
//     else {
//         printf("неправильный ввод");
//     }
//     return 0;
// }

// typedef struct {
//     char name[20];
//     int scores[3];
// } Student;

// int main(void) {
//     setlocale(LC_ALL, "ru_RU.UTF-8");
//     Student s = {0};

//     printf("Имя: ");
//     if (fgets(s.name, sizeof(s.name), stdin) == NULL) {
//         return 1;
//     }
//     s.name[strcspn(s.name, "\n")] = '\0';

//     printf("Привет, %s\n", s.name);
//     printf("Счет: %d", s.scores[0]);
//     return 0;
// }

// typedef struct {
//     int w;
//     int h;
// } Rectangle;

// int area(const Rectangle *r) {
//     int area = (r -> w) * (r -> h);
//     return area;
// }

// int main(void) {
//     setlocale(LC_ALL, "ru_RU.UTF-8");
//     int a[2];
//     char line[32];
//     for (int i = 0; i < 2; ) {
//         if (fgets(line, sizeof(line), stdin) == NULL) {
//             return 1;
//         }
//         char *end;
//         long v = strtol(line, &end, 10);
//         while (*end == ' ') {
//             end++;
//         }
//         if (end == line || (*end != '\n' && *end != '\0')) {
//             printf("Ошибка, повторите ввод\n");
//             continue;
//         }
//         *(a + i) = (int) v;
//         i++;
//     }
//     printf("Массив:");
//     for (int i = 0; i < 2; i++){
//         printf(" %d", *(a + i));
//     }
//     printf("\n");
//     Rectangle rec = {*(a), *(a + 1)};
//     int ar = area(&rec);
//     printf("Площадь: %d\n", ar);
//     return 0;
// }

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} vector;

int push_vector(vector *a, int new_el) {
    if (a -> size< a -> capacity) {
        (a -> data)[a -> size] = new_el;
        a -> size ++;
    }
    else {
        int *k = (int *) realloc(a -> data, a -> capacity == 0 ? 2 * sizeof(int) : a -> capacity * 2 * sizeof(int));
        a -> capacity = a -> capacity == 0 ? 2 : a -> capacity * 2;
        if (k == NULL) {
            return -1;
        }
        a -> data = k;
        (a -> data)[a -> size] = new_el;
        a -> size ++;
    }
}

int free_vector(vector *a) {
    free(a -> data);
    a -> size = 0;
    a -> capacity = 0;
    return 0;
}

void main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector a = {NULL, 0, 0};
    if (push_vector(&a, 5) == -1) {
        puts("Ошибка\n");
    }
    else {
        printf("%zu %zu %d", a.size, a.capacity, *(a.data));
    }
    if (push_vector(&a, 10) == -1) {
        puts("Ошибка\n");
    }
    else {
        printf("%zu %zu %d", a.size, a.capacity, *(a.data));
    }
    if (push_vector(&a, 20) == -1) {
        puts("Ошибка\n");
    }
    else {
        printf("%zu %zu %d", a.size, a.capacity, *(a.data));
    }
    return 0;
}