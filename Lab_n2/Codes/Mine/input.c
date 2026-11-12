#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int write_str(char *out, int size) {
    if (out == NULL || size < 2) { return 0; }

    for (;;) {
        int length = 0, invalid = 0, finished = 0;
        char part[INPUT_BUFFER_SIZE];

        while (!finished) {

            if (fgets(part, sizeof(part), stdin) == NULL) {

                if (length == 0 && !invalid) { return 0; }

                break;
            }

            int count = 0;
            while (*(part + count) != '\0') { count++; }

            for (int i = 0; i < count; i++) {
                unsigned char ch = (unsigned char) *(part + i);

                if (ch == '\n') { finished = 1; break; }

                if ((ch < 32 && ch != '\t') || ch == 127) { invalid = 1; }

                if (length < size - 1) {
                    *(out + length) = (char) ch;
                    length++;
                } else {
                    invalid = 1;
                }
            }

            if (count < (int) sizeof(part) - 1) { finished = 1; }
        }

        *(out + length) = '\0';

        if (invalid) {
            printf("Строка слишком длинная или содержит недопустимые символы. Максимум %d байт. Повторите ввод:\n", size - 1);
            continue;
        }

        int written = 0, space = 0;
        for (int i = 0; i < length; i++) {
            char ch = *(out + i);
            if (ch == ' ' || ch == '\t') {
                
                if (written > 0) { space = 1; }
                
            } else {
                
                if (space) {
                    *(out + written) = ' ';
                    written++;
                    space = 0;
                }
                
                *(out + written) = ch;
                written++;
            }
        }
        *(out + written) = '\0';

        if (written == 0) {
            printf("Строка не должна быть пустой. Повторите ввод:\n");
            continue;
        }
        return 1;
    }
}

static int write_num(int *out) {
    
    if (out == NULL) { return 0; }

    char line[INPUT_BUFFER_SIZE];

    for (;;) {

        if (!write_str(line, sizeof(line))) { return 0; }

        char *end;
        errno = 0;
        long value = strtol(line, &end, 10);

        if (end == line || *end != '\0') {
            printf("Введите целое число без лишних символов.\n");
            continue;
        }

        if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
            printf("Число слишком большое или слишком маленькое для int. Повторите ввод:\n");
            continue;
        }

        *out = (int) value;
        return 1;
    }
}

static int read_range(char *text, int min, int max, int *out) {
    for (;;) {
        printf("%s (%d–%d):\n", text, min, max);

        if (!write_num(out)) { return 0; }

        if (*out >= min && *out <= max) { return 1; }

        printf("Введите число от %d до %d.\n", min, max);
    }
}

static int choose_mode(void) {
    int mode;

    printf("\nВыберите режим:\n");
    printf("1 - Автоматическое заполнение\n");
    printf("2 - Ручной ввод\n");
    printf("3 - Проверочный пример (4 студента)\n");
    printf("0 - Выход\n");

    if (!read_range("Ваш выбор", 0, 3, &mode)) { return 0; }

    return mode;
}

static void random_students(Specialisation *spec, char *n) {
    if (spec == NULL || n == NULL) { return; }
    snprintf(spec -> name, sizeof(spec -> name), "%s", n);
    char *names[] = {
        "Александр", "Дмитрий", "Максим", "Иван", "Артём",
        "Михаил", "Даниил", "Кирилл", "Андрей", "Роман"
    };

    char *surnames[] = {
        "Иванов", "Петров", "Смирнов", "Кузнецов", "Попов",
        "Соколов", "Лебедев", "Козлов", "Новиков", "Морозов"
    };

    char *patronymics[] = {
        "Александрович", "Дмитриевич", "Максимович", "Иванович", "Артёмович",
        "Михайлович", "Даниилович", "Кириллович", "Андреевич", "Романович"
    };

    int c = MIN_STUDENTS + rand() % (MAX_STUDENTS - MIN_STUDENTS + 1);
    spec -> count = c;
    for (int i = 0; i < c; i++) {
        Guy *student = spec -> massive + i;
        student -> rus = MIN_RUS_SCORE + rand() % (MAX_SCORE - MIN_RUS_SCORE + 1);
        student -> math = MIN_MATH_SCORE + rand() % (MAX_SCORE - MIN_MATH_SCORE + 1);
        student -> inf = MIN_INF_SCORE + rand() % (MAX_SCORE - MIN_INF_SCORE + 1);
        student -> phys = MIN_PHYS_SCORE + rand() % (MAX_SCORE - MIN_PHYS_SCORE + 1);
        student -> benefit = (Benefit) (rand() % BENEFIT_COUNT);
        snprintf(student -> name, sizeof(student -> name), "%s", names[rand() % NAME_VARIANTS_COUNT]);
        snprintf(student -> surname, sizeof(student -> surname), "%s", surnames[rand() % NAME_VARIANTS_COUNT]);
        snprintf(student -> patronymic, sizeof(student -> patronymic), "%s", patronymics[rand() % NAME_VARIANTS_COUNT]);
    }
}

static void random_specialisations(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return; }
    char *specialisation_names[] = {
        "Автоматизация технологических процессов и производств",
        "Информатика и вычислительная техника",
        "Информационная безопасность",
        "Информационные системы и технологии",
        "Мехатроника и робототехника",
        "Прикладная информатика",
        "Прикладная математика и информатика",
        "Программная инженерия",
        "Радиотехника",
        "Электроника и наноэлектроника"
    };
    for (int i = 0; i < n; i++) { random_students(spec + i, specialisation_names[i]); }
}

static int students(Specialisation *spec, char *n) {
    if (spec == NULL || n == NULL) { return 0; }

    snprintf(spec -> name, sizeof(spec -> name), "%s", n);
    spec -> count = 0;

    int count;

    if (!read_range("Количество студентов", MIN_STUDENTS, MAX_STUDENTS, &count)) { return 0; }

    for (int i = 0; i < count; i++) {
        Guy *student = spec -> massive + i;

        printf("\nСтудент %d\n", i + 1);

        printf("Фамилия:\n");
        if (!write_str(student -> surname, sizeof(student -> surname))) { return 0; }

        printf("Имя:\n");
        if (!write_str(student -> name, sizeof(student -> name))) { return 0; }

        printf("Отчество:\n");
        if (!write_str(student -> patronymic, sizeof(student -> patronymic))) { return 0; }

        if (!read_range("Русский язык", MIN_RUS_SCORE, MAX_SCORE, &student -> rus)) { return 0; }

        if (!read_range("Математика", MIN_MATH_SCORE, MAX_SCORE, &student -> math)) { return 0; }

        if (!read_range("Физика", MIN_PHYS_SCORE, MAX_SCORE, &student -> phys)) { return 0; }

        if (!read_range("Информатика", MIN_INF_SCORE, MAX_SCORE, &student -> inf)) { return 0; }

        printf(
            "Льгота:\n"
            "0 - Нет\n"
            "1 - Особая квота\n"
            "2 - Отдельная квота\n"
            "3 - Целевой прием\n"
            "4 - Без вступительных испытаний\n"
        );

        int benefit;

        if (!read_range("Номер льготы", 0, BENEFIT_COUNT - 1, &benefit)) { return 0; }

        student -> benefit = (Benefit) benefit;
        spec -> count++;
    }
    return 1;
}

static int specialisations(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return 0; }
    char *specialisation_names[] = {
        "Автоматизация технологических процессов и производств",
        "Информатика и вычислительная техника",
        "Информационная безопасность",
        "Информационные системы и технологии",
        "Мехатроника и робототехника",
        "Прикладная информатика",
        "Прикладная математика и информатика",
        "Программная инженерия",
        "Радиотехника",
        "Электроника и наноэлектроника"
    };

    for (int i = 0; i < n; i++) {
        printf("\n=== Заполнение направления %d из %d ===\n", i + 1, n);
        printf("%s\n", specialisation_names[i]);

        if (!students(spec + i, specialisation_names[i])) { return 0; }
    }
    return 1;
}

int repeat_work(void) {
    int repeat;

    if (!read_range("\nПовторить работу? 1 - да, 0 - выход", 0, 1, &repeat)) { return 0; }

    return repeat;
}

static void example_students(Specialisation *spec) {
    *spec = (Specialisation) {
        .name = "Программная инженерия (проверочный пример)",
        .count = 4,
        .massive = {
            {.name = "Иван", .surname = "Иванов", .patronymic = "Иванович",
             .rus = 40, .math = 40, .inf = 60, .phys = 50, .benefit = BENEFIT_NONE},
            {.name = "Пётр", .surname = "Петров", .patronymic = "Петрович",
             .rus = 60, .math = 60, .inf = 50, .phys = 80, .benefit = BENEFIT_NONE},
            {.name = "Анна", .surname = "Иванова", .patronymic = "Ивановна",
             .rus = 80, .math = 80, .inf = 100, .phys = 90, .benefit = BENEFIT_SPECIAL_QUOTA},
            {.name = "Ольга", .surname = "Петрова", .patronymic = "Петровна",
             .rus = 100, .math = 100, .inf = 70, .phys = 60, .benefit = BENEFIT_BVI}
        }
    };
}

int input_data(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return 0; }

    switch (choose_mode()) {
        case 1:
            random_specialisations(spec, n);
            return n;
        case 2:
            if (!specialisations(spec, n)) {
                printf("Ввод прекращён. Незавершённый набор не обрабатывается.\n");
                return 0;
            }
            return n;
        case 3:
            example_students(spec);
            return 1;
        default:
            return 0;
    }
}
