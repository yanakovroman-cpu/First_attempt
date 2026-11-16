#ifndef DATA_H
#define DATA_H

#include "types.h"

/* Автоматическое заполнение случайными данными. 0 - успех */
int fill_random(Direction *dirs, int n);

/* Демонстрационный набор, который легко посчитать в уме. 0 - успех */
int fill_demo(Direction *dirs, int n);

#endif
