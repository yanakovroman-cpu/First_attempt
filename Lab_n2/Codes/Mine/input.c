#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int write_str(char *out, int size) {
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

                if ((ch < 32 && ch != '\t' && ch != '\r') || ch == 127) { invalid = 1; }

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
            if (ch == ' ' || ch == '\t' || ch == '\r') {
                
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

int write_num(int *out) {
    
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

static int read_range(const char *text, int min, int max, int *out) {
    for (;;) {
        printf("%s (%d–%d):\n", text, min, max);

        if (!write_num(out)) { return 0; }

        if (*out >= min && *out <= max) { return 1; }

        printf("Введите число от %d до %d.\n", min, max);
    }
}

int choose_mode(void) {
    int mode;

    printf("\nВыберите режим:\n");
    printf("1 - Автоматическое заполнение\n");
    printf("2 - Ручной ввод\n");
    printf("0 - Выход\n");

    if (!read_range("Ваш выбор", 0, 2, &mode)) { return 0; }

    return mode;
}

void random_students(Specialisation *spec, const char *n) {
    if (spec == NULL || n == NULL) { return; }
    snprintf(spec -> name, sizeof(spec -> name), "%s", n);
    const char *names[] = {
        "Александр", "Дмитрий", "Максим", "Иван", "Артём",
        "Михаил", "Даниил", "Кирилл", "Андрей", "Роман"
    };

    const char *surnames[] = {
        "Иванов", "Петров", "Смирнов", "Кузнецов", "Попов",
        "Соколов", "Лебедев", "Козлов", "Новиков", "Морозов"
    };

    const char *patronymics[] = {
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

void random_specialisations(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return; }
    const char *specialisation_names[] = {
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

int students(Specialisation *spec, const char *n) {
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

int specialisations(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return 0; }
    const char *specialisation_names[] = {
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

int input_data(Specialisation *spec, int n) {
    if (spec == NULL || n < 1 || n > SPECIALISATION_COUNT) { return 0; }

    switch (choose_mode()) {
        case 1:
            random_specialisations(spec, n);
            return 1;
        case 2:
            if (!specialisations(spec, n)) {
                printf("Ввод прекращён. Незавершённый набор не обрабатывается.\n");
                return 0;
            }
            return 1;
        default:
            return 0;
    }
}
