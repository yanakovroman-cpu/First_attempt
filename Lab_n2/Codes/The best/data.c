#include <stdio.h>
#include <stdlib.h>
#include "data.h"

static const char *DIRECTION_NAMES[DIRECTION_COUNT] = {
    "Информатика и ВТ", "Прикл. математика", "Физика", "Прогр. инженерия",
    "Кибербезопасность", "Радиотехника", "Механика", "Робототехника",
    "Электроника", "Приборостроение"
};
static const char *SURNAMES[]  = {"Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов",
                                  "Попов", "Васильев", "Соколов", "Михайлов", "Новиков"};
static const char *FIRSTS[]    = {"Алексей", "Дмитрий", "Иван", "Сергей",
                                  "Андрей", "Михаил", "Николай", "Павел"};
static const char *PATRONYMS[] = {"Александрович", "Дмитриевич", "Иванович",
                                  "Сергеевич", "Андреевич", "Петрович"};

#define ARR_LEN(a) ((int)(sizeof(a) / sizeof((a)[0])))

static Benefit random_benefit(void) {
    int r = rand() % 100;
    if (r < 70) return BEN_NONE;
    if (r < 78) return BEN_SPECIAL;
    if (r < 86) return BEN_SEPARATE;
    if (r < 94) return BEN_TARGET;
    return BEN_BVI;
}

static int set_direction_name(Direction *d, int index) {
    int len = snprintf(d->name, sizeof(d->name), "%s", *(DIRECTION_NAMES + index));
    return (len < 0 || len >= (int)sizeof(d->name)) ? -1 : 0;
}

int fill_random(Direction *dirs, int n) {
    if (dirs == NULL || n <= 0 || n > DIRECTION_COUNT) {
        return -1;
    }
    Direction *d = dirs;
    for (int i = 0; i < n; i++, d++) {
        if (set_direction_name(d, i) != 0) {
            return -1;
        }
        d->count = MIN_APPLICANTS + rand() % (MAX_APPLICANTS - MIN_APPLICANTS + 1);

        Applicant *a = d->applicants;
        for (int j = 0; j < d->count; j++, a++) {
            int len = snprintf(a->name, sizeof(a->name), "%s %s %s",
                               *(SURNAMES + rand() % ARR_LEN(SURNAMES)),
                               *(FIRSTS + rand() % ARR_LEN(FIRSTS)),
                               *(PATRONYMS + rand() % ARR_LEN(PATRONYMS)));
            if (len < 0 || len >= (int)sizeof(a->name)) {
                return -1;
            }
            for (int *s = a->scores; s < a->scores + SUBJ_COUNT; s++) {
                *s = 30 + rand() % 71;           /* 30..100 */
            }
            a->benefit = random_benefit();
        }
    }
    return 0;
}

/*
 * Демо: на каждом направлении 12 абитуриентов с одинаковыми баллами.
 * Направление k (k = 1..10): Русский = 59 + k, Математика = 70,
 * Физика = 80, Информатика = 50. Льготы: 1 особая, 1 отдельная,
 * 1 целевой, 1 БВИ, остальные 8 - без льгот.
 */
int fill_demo(Direction *dirs, int n) {
    if (dirs == NULL || n <= 0 || n > DIRECTION_COUNT) {
        return -1;
    }
    Direction *d = dirs;
    for (int i = 0; i < n; i++, d++) {
        if (set_direction_name(d, i) != 0) {
            return -1;
        }
        d->count = 12;

        Applicant *a = d->applicants;
        for (int j = 0; j < d->count; j++, a++) {
            int len = snprintf(a->name, sizeof(a->name), "Абитуриент %d-%d", i + 1, j + 1);
            if (len < 0 || len >= (int)sizeof(a->name)) {
                return -1;
            }
            *(a->scores + SUBJ_RUSSIAN)     = 60 + i;
            *(a->scores + SUBJ_MATH)        = 70;
            *(a->scores + SUBJ_PHYSICS)     = 80;
            *(a->scores + SUBJ_INFORMATICS) = 50;
            switch (j) {
                case 0:  a->benefit = BEN_SPECIAL;  break;
                case 1:  a->benefit = BEN_SEPARATE; break;
                case 2:  a->benefit = BEN_TARGET;   break;
                case 3:  a->benefit = BEN_BVI;      break;
                default: a->benefit = BEN_NONE;     break;
            }
        }
    }
    return 0;
}
