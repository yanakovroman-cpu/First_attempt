#include "input.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(NULL));

    do {
        Specialisation all[SPECIALISATION_COUNT] = {0};
        
        if (!input_data(all, SPECIALISATION_COUNT)) { break; }

        printf("\nНАПРАВЛЕНИЯ\n");
        for (int i = 0; i < SPECIALISATION_COUNT; i++) {
            const Specialisation *spec = all + i;
            printf("%2d - %s\n", i + 1, spec -> name);
        }

        printf("\nСТАТИСТИКА ПО НАПРАВЛЕНИЯМ\n\n");
        printf("| Напр. | Без льгот  | С льготами | Минимум    | Максимум   | ОК   | ОтК  | ЦП   | БВИ  | Русский    | Математика | Физика     | Информат.  |\n");
        for (int i = 0; i < SPECIALISATION_COUNT; i++) {
            Statistics result;
            calculate(all + i, &result);

            printf("| %5d | ", i + 1);
            print_score(result.average_without, 2);
            print_score(result.average_with, 2);
            print_score(result.min_score, 0);
            print_score(result.max_score, 0);

            for (int j = BENEFIT_SPECIAL_QUOTA; j < BENEFIT_COUNT; j++) {
                printf("%4d | ", *(result.benefit_counts + j));
            }

            print_score(result.rus_average, 2);
            print_score(result.math_average, 2);
            print_score(result.phys_average, 2);
            print_score(result.inf_average, 2);
            printf("\n");
        }
    }
    while (repeat_work());

    printf("Работа завершена.\n");
    return 0;
}
