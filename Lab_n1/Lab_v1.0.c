#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <limits.h>
#include <ctype.h>


int evklid(signed long long int x, signed long long int y) {
    signed long long int c;
    x = fabs(x);
    y = fabs(y);
    while (x != 0 && y != 0) {
        c = y;
        y = x % y;
        x = c;
    }
    if (x == 0) {
        return y;
    }
    else {
        return x;
    }

}


int tenth_format(signed long long int y, signed long long int *p_m, signed long long int *p_n) {
    while (y % 2 == 0 || y % 5 == 0) {
        if (y % 2 == 0) {
            y = y / 2;
            *p_m += 1;
        }
        if (y % 5 == 0) {
            y = y / 5;
            *p_n += 1;
        }
    }
    if (y == 1) {
        return 1;
    }
    else {
        return 0;
    }
}


int trash_cleaning(void) {
    int c;
    int t = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isspace((unsigned char) c)) {
            t = 1;
        }
    }
    return t;
}


int repeat(void) {
    int ans, c;
    int k;
    for (;;) {
        printf("\nНачать выполнение программы заново?\nВведите 1(Да) или 0(Нет).\n");
        c = scanf("%d", &ans);
        if (trash_cleaning()) {
            printf("\nОШИБКА. Неправильный формат входных данных.\nВводите корректное значение.\n");
            repeat();
        }
        if (c == EOF) {
            return -1;
        }
        if (c == 1 && (ans == 0 || ans == 1)) {
            return ans;
        }
        printf("\nОШИБКА. Неправильный формат входных данных.\nВводите корректное значение.\n");
    }
}


int main(void) {
    signed long long int x, x1, x2, y, y1, y2, test_y, precision, m = 0, n = 0, f;
    int c1, c2, choice, ans;
    char operator;
    setlocale(LC_ALL, "ru_RU.UTF-8");
    printf("Выберите режим работы 1, 2 или 3:\n\t1 -- Арифметическое действие\n\t2 -- Сокращение\n\t3 -- Десятичное представление\n");
    ans = scanf("%d", &choice);
    switch (ans) {
        case 1: {
            if (trash_cleaning()) {
                printf("\nОШИБКА. Неправильный формат входных данных!\nВводите только 1, 2 или 3.\n");
                if (repeat()) {
                    main();
                }
                else {
                    return 0;
                }
                break;
            }
            switch (choice) {
                case 1: {
                    printf("Введите первую дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель в пределах от %ld до %ld:\t", LONG_MIN, LONG_MAX);
                    c1 = scanf("%lld / %lld", &x1, &y1);
                    if (trash_cleaning()) {
                        printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                        break;
                    }
                    switch (c1) {
                        case 2:
                            if (y1 == 0) {
                                printf("\nОШИБКА. Делить на ноль нельзя!\nЗнаменатель равен нулю.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(x1) > LONG_MAX) {
                                if (fabs(y1) > LONG_MAX) {
                                    printf("\nОШИБКА. Числитель и знаменатель слишком большие!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                else {
                                    printf("\nОШИБКА. Числитель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(y1) > LONG_MAX) {
                                printf("\nОШИБКА. Знаменатель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            break;
                        default: {
                            printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                    }
                    printf("Введите вторую дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель в пределах от %ld до %ld:\t", LONG_MIN, LONG_MAX);
                    c2 = scanf("%lld / %lld", &x2, &y2);
                    if (trash_cleaning()) {
                        printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                        break;
                    }
                    switch (c2) {
                        case 2:
                            if (y2 == 0) {
                                printf("\nОШИБКА. Делить на ноль нельзя!\nЗнаменатель равен нулю.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(x2) > LONG_MAX) {
                                if (fabs(y2) > LONG_MAX) {
                                    printf("\nОШИБКА. Числитель и знаменатель слишком большие!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                else {
                                    printf("\nОШИБКА. Числитель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(y2) > LONG_MAX) {
                                printf("\nОШИБКА. Знаменатель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            break;
                        default: {
                            printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                    }
                    x1 = (y1 > 0) ? x1 : (-1 * x1);
                    x2 = (y2 > 0) ? x2 : (-1 * x2);
                    printf("Введите оператор +, -, * или /:\t");
                    scanf("%c", &operator);
                    if (trash_cleaning()) {
                            printf("\nОШИБКА. Неправильный формат входных данных.\nВведите корректный оператор: +, -, * или /.\n");
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                        break;
                    }
                    switch (operator) {
                        case '+' : {
                            x = x1 * y2 + x2 * y1, y = y1 * y2;
                            f = evklid(x, y);
                            x = x / f, y = y / f;
                            printf("\nОтвет: (%lld / %lld) + (%lld / %lld) =  %lld / %lld\n", x1, y1, x2, y2, x, y);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                        case '-' : {
                            x = x1 * y2 - x2 * y1, y = y1 * y2;
                            f = evklid(x, y);
                            x = x / f, y = y / f;
                            printf("\nОтвет: (%lld / %lld) - (%lld / %lld) = %lld / %lld\n", x1, y1, x2, y2, x, y);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                        case '*': {
                            x = x1 * x2, y = y1 * y2;
                            f = evklid(x, y);
                            x = x / f, y = y / f;
                            printf("\nОтвет: (%lld / %lld) * (%lld / %lld) = %lld / %lld\n", x1, y1, x2, y2, x, y);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                        case '/': {
                            if (x2 == 0) {
                                printf("\nОШИБКА. Делить на ноль нельзя!\nЧислитель второй дроби равен нулю.\n");
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                                break;
                            }
                            x = x1 * y2, y = y1 * x2;
                            f = evklid(x, y);
                            x = x / f, y = y / f;
                            printf("\nОтвет: (%lld / %lld) / (%lld / %lld) = %lld / %lld\n", x1, y1, x2, y2, x, y);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                        default: {
                            printf("\nОШИБКА. Неправильный формат входных данных.\nВведите корректный оператор: +, -, * или /.\n");
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    printf("Введите дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель в пределах от %ld до %ld:\t", LONG_MIN, LONG_MAX);
                    c1 = scanf("%lld / %lld", &x, &y);
                    if (trash_cleaning()) {
                        printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                        break;
                    }
                    switch (c1) {
                        case 2:
                            if (y == 0) {
                                printf("\nОШИБКА. Делить на ноль нельзя!\nЗнаменатель равен нулю.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(x) > LONG_MAX) {
                                if (fabs(y) > LONG_MAX) {
                                    printf("\nОШИБКА. Числитель и знаменатель слишком большие!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                else {
                                    printf("\nОШИБКА. Числитель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(y) > LONG_MAX) {
                                printf("\nОШИБКА. Знаменатель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            break;
                        default: {
                            printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                    }
                    f = evklid(x, y);
                    x = x / f, y = y / f;
                    printf("\nОтвет: %lld / %lld\n", x, y);
                    if (repeat()) {
                        main();
                    }
                    else {
                        return 0;
                    }
                    break;
                }
                case 3: {
                    printf("Введите дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель в пределах от %ld до %ld:\t", LONG_MIN, LONG_MAX);
                    c1 = scanf("%lld / %lld", &x, &y);
                    if (trash_cleaning()) {
                        printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                        break;
                    }
                    switch (c1) {
                        case 2:
                            if (y == 0) {
                                printf("\nОШИБКА. Делить на ноль нельзя!\nЗнаменатель равен нулю.\n");
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(x) > LONG_MAX) {
                                if (fabs(y) > LONG_MAX) {
                                    printf("\nОШИБКА. Числитель и знаменатель слишком большие!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                else {
                                    printf("\nОШИБКА. Числитель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                }
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            if (fabs(y) > LONG_MAX) {
                                printf("\nОШИБКА. Знаменатель слишком большой!\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                                if (repeat()) {
                                    main();
                                }
                                else {
                                    return 0;
                                }
                            }
                            break;
                        default: {
                            printf("\nОШИБКА. Неправильный формат входных данных.\n\tПравила ввода:\n\t\t-Числитель и знаменатель - целые числа в пределах от %ld до %ld\n\t\t-Знаменатель не может быть равен 0\n", LONG_MIN, LONG_MAX);
                            if (repeat()) {
                                main();
                            }
                            else {
                                return 0;
                            }
                            break;
                        }
                    }
                    test_y = y;
                    f = evklid(x, y);
                    x = x / f, y = y / f;
                    if (tenth_format(y, &m, &n)) {
                        precision = (m > n) ? m : n;
                        printf("\nОтвет: %.*lf\n", precision, ((double) x) / y);
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                    }
                    else {
                        printf("\nВведенная дробь не может быть представлена в десятичном формате.\n");
                        if (repeat()) {
                            main();
                        }
                        else {
                            return 0;
                        }
                    }
                    break;
                }
                default: {
                    printf("\nОШИБКА. Неправильный формат входных данных!\nВводите только 1, 2 или 3.\n");
                    if (repeat() == 1) {
                        main();
                    }
                    else {
                        return 0;
                    }
                    break;
                }
            }
            break;
        }
        default: {
            if (trash_cleaning()) {
                printf("\nОШИБКА. Неправильный формат входных данных!\nВводите только 1, 2 или 3.\n");
                if (repeat()) {
                    main();
                }
                else {
                    return 0;
                }
                break;
            }
            printf("\nОШИБКА. Неправильный формат входных данных!\nВводите только 1, 2 или 3.\n");
            if (repeat()) {
                main();
            }
            else {
                return 0;
            }
            break;
        }
    }
    return 0;
}