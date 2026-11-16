#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "data.h"
#include "stats.h"

#define COLS 14

static const int W[COLS] = {22, 10, 10, 5, 5, 6, 6, 6, 6, 6, 5, 5, 5, 5};
static const char *H[COLS] = {
    "Направление", "Ср.б/льгот", "Ср.с льгот", "Мин", "Макс", "Всего",
    "Особ", "Отдел", "Целев", "БВИ", "Рус", "Мат", "Физ", "Инф"
};

/* ---------- ввод ---------- */

static void clear_rest(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Читает строку через fgets. 0 - конец ввода (EOF) */
static int read_line(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        return 0;
    }
    char *nl = strchr(buf, '\n');
    if (nl != NULL) {
        *nl = '\0';
    } else {
        clear_rest();
    }
    return 1;
}

/* Спрашивает число в диапазоне [min, max]. -1 - конец ввода */
static int ask_int(const char *prompt, int min, int max) {
    char line[64];
    while (1) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            return -1;
        }
        char *end;
        long v = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t') {
            end++;
        }
        if (end == line || *end != '\0') {
            printf("Ошибка: введите целое число.\n");
            continue;
        }
        if (v < min || v > max) {
            printf("Ошибка: число должно быть от %d до %d.\n", min, max);
            continue;
        }
        return (int)v;
    }
}

/* ---------- вывод ---------- */

/* Печать строки с выравниванием по числу символов UTF-8, а не байт */
static void print_padded(const char *s, int width) {
    int len = 0;
    for (const char *p = s; *p; p++) {
        if (((unsigned char)*p & 0xC0) != 0x80) {
            len++;
        }
    }
    fputs(s, stdout);
    for (int i = len; i < width; i++) {
        putchar(' ');
    }
}

static void print_sep(void) {
    for (int c = 0; c < COLS; c++) {
        putchar('+');
        for (int k = 0; k < *(W + c); k++) {
            putchar('-');
        }
    }
    puts("+");
}

static void cell(int col, const char *s) {
    putchar('|');
    print_padded(s, *(W + col));
}

static void cell_int(int col, int v) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", v);
    cell(col, buf);
}

static void cell_dbl(int col, double v) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%.2f", v);
    cell(col, buf);
}

static void print_table(const Direction *dirs, const DirectionStats *stats, int n) {
    print_sep();
    for (int c = 0; c < COLS; c++) {
        cell(c, *(H + c));
    }
    puts("|");
    print_sep();

    const Direction *d = dirs;
    const DirectionStats *s = stats;
    for (int i = 0; i < n; i++, d++, s++) {
        char buf[DIR_NAME_LEN + 16];
        snprintf(buf, sizeof(buf), "%d. %s", i + 1, d->name);
        cell(0, buf);
        if (s->has_no_benefit) {
            cell_dbl(1, s->avg_no_benefit);
        } else {
            cell(1, "-");
        }
        cell_dbl(2, s->avg_with_benefit);
        cell_int(3, s->min_score);
        cell_int(4, s->max_score);
        cell_int(5, s->benefit_total);
        cell_int(6, *(s->benefit_count + BEN_SPECIAL));
        cell_int(7, *(s->benefit_count + BEN_SEPARATE));
        cell_int(8, *(s->benefit_count + BEN_TARGET));
        cell_int(9, *(s->benefit_count + BEN_BVI));
        for (int k = 0; k < SUBJ_COUNT; k++) {
            cell_dbl(10 + k, *(s->avg_subject + k));
        }
        puts("|");
    }
    print_sep();
    printf("Ср.б/льгот - средний балл зачисленных только по проходному баллу (без льгот)\n"
           "Ср.с льгот - средний балл всех категорий, БВИ = %d баллов\n"
           "Мин/Макс - минимальная/максимальная сумма баллов (БВИ = %d)\n"
           "Всего - льготников всех категорий; Особ - особая квота, Отдел - отдельная квота,\n"
           "Целев - целевой прием, БВИ - без вступительных испытаний\n"
           "Рус/Мат/Физ/Инф - средний балл по предмету\n"
           "Сумма баллов = Математика + Русский + max(Физика, Информатика)\n",
           BVI_SCORE, BVI_SCORE);
}

static void print_demo_hint(void) {
    printf("\nПроверка демо-набора в уме (направление k, 12 абитуриентов):\n"
           "  Русский = 59 + k, Математика = 70, Физика = 80, Информатика = 50,\n"
           "  льготы: по 1 особая, отдельная, целевой, БВИ; остальные 8 без льгот.\n"
           "  Сумма = (59 + k) + 70 + 80 = 209 + k\n"
           "  Ср.б/льгот = 209 + k;  Ср.с льгот = (11 * (209 + k) + 300) / 12\n"
           "  Мин = 209 + k;  Макс = 300;  Всего = 4;  Особ = Отдел = Целев = БВИ = 1\n"
           "  Рус = 59 + k;  Мат = 70;  Физ = 80;  Инф = 50\n");
}

static void print_applicants(const Direction *dir) {
    printf("\nАбитуриенты направления \"%s\" (%d чел.):\n", dir->name, dir->count);
    printf("%-4s", "N");
    print_padded("ФИО", 34);
    printf("Рус Мат Физ Инф Сумма  Льгота\n");
    const Applicant *a = dir->applicants;
    for (int i = 0; i < dir->count; i++, a++) {
        printf("%-4d", i + 1);
        print_padded(a->name, 34);
        printf("%-4d%-4d%-4d%-4d%-7d%s\n",
               *(a->scores + SUBJ_RUSSIAN), *(a->scores + SUBJ_MATH),
               *(a->scores + SUBJ_PHYSICS), *(a->scores + SUBJ_INFORMATICS),
               applicant_effective_score(a), benefit_name(a->benefit));
    }
}

/* ---------- main: только ввод/вывод ---------- */

int main(void) {
#ifdef _WIN32
    (void)system("chcp 65001 > nul");
#endif
    static Direction dirs[DIRECTION_COUNT];
    DirectionStats stats[DIRECTION_COUNT];

    srand((unsigned)time(NULL));
    printf("Лабораторная работа 2, вариант 1: подсчет статистик по направлениям\n");

    while (1) {
        int mode = ask_int("\nЗаполнить данные: 1 - случайно, 2 - демо-набор, 0 - выход: ", 0, 2);
        if (mode <= 0) {
            break;
        }

        int rc = (mode == 1) ? fill_random(dirs, DIRECTION_COUNT)
                             : fill_demo(dirs, DIRECTION_COUNT);
        if (rc != 0) {
            printf("Ошибка: не удалось заполнить данные.\n");
            continue;
        }

        rc = calculate_all_stats(dirs, DIRECTION_COUNT, stats);
        if (rc != STATS_OK) {
            printf("Ошибка подсчета: %s\n", stats_error_text(rc));
            continue;
        }

        printf("\n");
        print_table(dirs, stats, DIRECTION_COUNT);
        if (mode == 2) {
            print_demo_hint();
        }

        int d = ask_int("\nПоказать абитуриентов направления (1-10, 0 - не показывать): ",
                        0, DIRECTION_COUNT);
        if (d < 0) {
            break;
        }
        if (d > 0) {
            print_applicants(dirs + (d - 1));
        }

        int again = ask_int("\nПовторить работу? (1 - да, 0 - выход): ", 0, 1);
        if (again <= 0) {
            break;
        }
    }
    printf("Bye\n");
    return 0;
}
