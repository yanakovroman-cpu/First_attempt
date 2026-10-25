#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <locale.h>
#define DEL 127
#define ASCII_LIM 32



void cln(void) {
    int trash = getchar();
    if (trash == ASCII_LIM) {
        printf("ASCII_LIM");
    }
    while (trash > ASCII_LIM && trash != DEL) {
        if(trash == DEL){
            printf("DEL");
        } else if(trash == ASCII_LIM){
            printf("ASCII_LIM");
        }
        trash = getchar();
    }
}

int tenth_format( long long  y,  long long  *p_m,  long long  *p_n) {
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

int main(void) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    signed long long int x1, x2, x, y1, y2, y, nod, m = 0, n = 0, precision = 1;
    int flag1 = 0, flag2, repeat, c = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    char mode, operand;
    for( ; ; ) {
        for ( ; ; ) {
            printf("Выберите режим работы 1, 2 или 3:\n\t1 -- Арифметическое действие\n\t2 -- Сокращение\n\t3 -- Десятичное представление\n");
            c = scanf("%c", &mode);
            if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c != 1) {
                printf("\nОшибка ввода.\n");
                cln();
                break;
            }
            if (mode == '1') {
                printf("\nВведите первую дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель - целые числа в пределах от %ld до %ld, знаменатель не равен 0:\t", LONG_MIN, LONG_MAX);
                c1 = scanf("%lld / %lld", &x1, &y1);
                if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c1 != 2) {
                    printf("\nОшибка ввода.\n");
                    cln();
                    break;
                }
                
                if (y1 == 0) {
                    printf("\nОшибка. Знаменатель не может быть равен нулю!\nДелить на ноль нельзя.\n");
                    break;
                }

                if (LONG_MAX - fabs(x1) < 0 || LONG_MAX - fabs(y1) < 0) {
                    printf("\nОшибка. Слишком большое числовое значение.\n");
                    break;
                }

                printf("\nВведите вторую дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель - целые числа в пределах от %ld до %ld, знаменатель не равен 0:\t", LONG_MIN, LONG_MAX);
                c2 = scanf("%lld / %lld", &x2, &y2);
                if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c2 != 2) {
                    printf("\nОшибка ввода.\n");
                    cln();
                    break;
                }

                if (y2 == 0) {
                    printf("\nОшибка. Знаменатель не может быть равен нулю!\nДелить на ноль нельзя.\n");
                    break;
                }

                if (LONG_MAX - fabs(x2) < 0 || LONG_MAX - fabs(y2) < 0) {
                    printf("\nОшибка. Слишком большое числовое значение.\n");
                    break;
                }

                printf("\nВведите оператор +, -, * или /:\t");
                c3 = scanf("%c", &operand);
                if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c3 != 1) {
                    printf("\nОшибка ввода.\n");
                    cln();
                    break;
                }
                if (operand == '/' && x2 == 0) {
                    printf("\nОшибка. Числитель второй дроби равен нулю!\nДелить на ноль нельзя.\n");
                    break;
                }
                
                x1 = (y1 > 0) ? x1 : (-1 * x1);
                x2 = (y2 > 0) ? x2 : (-1 * x2);
                y1 = (signed long long int) fabs(y1);
                y2 = (signed long long int) fabs(y2);

                if (operand == '+') {
                    x = y2 * x1 + x2 * y1;
                    y = y1 * y2;
                }
                else if (operand == '-') {
                    x = y2 * x1 - x2 * y1;
                    y = y1 * y2;
                }
                else if (operand == '*') {
                    x = x1 * x2;
                    y = y1 * y2;
                }
                else if (operand == '/') {
                    x = x1 * y2;
                    y = y1 * x2;
                }
                else {
                    printf("\nОшибка. Неправильный оператор.\n");
                    break;
                }
                if (x == 0) {
                    printf("\nОтвет: (%lld / %lld) %c (%lld / %lld) = %d\n", x1, y1, operand, x2, y2, 0);
                    break;
                }
                nod = evklid(x, y);
                x = x / nod, y = y / nod;
                if (y == 1) {
                    printf("\nОтвет: (%lld / %lld) %c (%lld / %lld) = %lld\n", x1, y1, operand, x2, y2, x);
                    break;
                }
                printf("\nОтвет: (%lld / %lld) %c (%lld / %lld) = %lld / %lld\n", x1, y1, operand, x2, y2, x, y);
                break;

            }
            else if (mode == '2') {
                printf("\nВведите дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель - целые числа в пределах от %ld до %ld, знаменатель не равен 0:\t", LONG_MIN, LONG_MAX);
                c1 = scanf("%lld / %lld", &x, &y);
                if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c1 != 2) {
                    printf("\nОшибка ввода.\n");
                    cln();
                    break;
                }

                if (y == 0) {
                    printf("\nОшибка. Знаменатель не может быть равен нулю!\nДелить на ноль нельзя.\n");
                    break;
                }

                if (LONG_MAX - fabs(x) < 0 || LONG_MAX - fabs(y) < 0) {
                    printf("\nОшибка. Слишком большое числовое значение.\n");
                    break;
                }
                
                if (x == 0) {
                    printf("\nОтвет: %d\n", 0);
                    break;
                }
                x = (y > 0) ? x : (-1 * x);
                y = (signed long long int) fabs(y);
                nod = evklid(x, y);
                x = x / nod, y = y / nod;
                if (y == 1) {
                    printf("\nОтвет: %lld\n", x);
                    break;
                }
                printf("\nОтвет: %lld / %lld\n", x, y);
                break;


            }
            else if (mode == '3') {
                printf("\nВведите дробь в формате 'числитель/знаменатель'.\nЧислитель и знаменатель - целые числа в пределах от %ld до %ld, знаменатель не равен 0:\t", LONG_MIN, LONG_MAX);
                c1 = scanf("%lld / %lld", &x, &y);
                if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c1 != 2) {
                    printf("\nОшибка ввода.\n");
                    cln();
                    break;
                }

                if (y == 0) {
                    printf("\nОшибка. Знаменатель не может быть равен нулю!\nДелить на ноль нельзя.\n");
                    break;
                }

                if (LONG_MAX - fabs(x) < 0 || LONG_MAX - fabs(y) < 0) {
                    printf("\nОшибка. Слишком большое числовое значение.\n");
                    break;
                }

                x = (y > 0) ? x : (-1 * x);
                y = (signed long long int) fabs(y);
                nod = evklid(x, y);
                x = x / nod, y = y / nod;
                if (tenth_format(y, &m, &n)) {
                    precision = (m > n) ? m : n;
                    printf("\nОтвет: %.*lf\n", precision, ((double) x) / y);
                }
                else {
                    printf("\nЧисло не может быть представлено в десятичном формате.\n");
                }
                break;
            }
            else {
                printf("\nОшибка. Неправильный ответ.\n");
                break;
            }
        }

        for ( ; ; ) {
            printf("\nНачать заново?\nВведите y/n\n");
            c4 = scanf("%c", &repeat);
            if (((flag2 = getchar()) > ASCII_LIM && flag2 != DEL) || c4 != 1) {
                printf("\nОшибка ввода.\n");
                cln();
                continue;
            }
            if (repeat == 'Y' || repeat == 'y') {
                flag1 = 1;
                break;
            }
            else if (repeat == 'N' || repeat == 'n') {
                return 0;
            } else {
                printf("\nОшибка. Неправильный ответ.\n");
                continue;
            }
        }
        if (flag1) {
            continue;
        }
        else {
            return 0;
        }
    }

    //Дойти сюда
    return -1;
}