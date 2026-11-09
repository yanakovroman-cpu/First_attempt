#ifndef LAB_MATH_H
#define LAB_MATH_H

#include "input.h"

#define BVI_SCORE 300
#define MAX_TOTAL_SCORE (3 * MAX_SCORE)
#define NO_DATA (-1)

typedef struct {
    double average_with;
    double average_without;

    int min_score;
    int max_score;

    int benefit_counts[BENEFIT_COUNT];

    double rus_average;
    double math_average;
    double inf_average;
    double phys_average;
} Statistics;

void calculate(const Specialisation *spec, Statistics *result);
void print_score(double value, int precision);

#endif
