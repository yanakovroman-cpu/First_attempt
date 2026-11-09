#include "stats.h"
#include <stdio.h>

static double average_with(const Specialisation *spec) {
    double average;
    int count = spec -> count, sum = 0;

    if (count == 0) { return NO_DATA; }

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;

        if (student -> benefit == BENEFIT_BVI) { sum = sum + BVI_SCORE; continue; }

        int third_score = (student -> inf > student -> phys) ? student -> inf : student -> phys;
        sum += student -> rus + student -> math + third_score;
    }

    average = (double) sum / count;
    return average;
}

static double average_without(const Specialisation *spec) {
    double average;
    int count = spec -> count, included = 0, sum = 0;

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;

        if (student -> benefit != BENEFIT_NONE) { continue; }

        int third_score = (student -> inf > student -> phys) ? student -> inf : student -> phys;
        sum += student -> rus + student -> math + third_score;
        included++;
    }

    if (included == 0) { return NO_DATA; }

    average = (double) sum / included;
    return average;
}

static int min_score(const Specialisation *spec) {
    int mn = MAX_TOTAL_SCORE, count = spec -> count, k;

    if (count == 0) { return NO_DATA; }

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        int third_score = (student -> inf > student -> phys) ? student -> inf : student -> phys;
        k = student -> rus + student -> math + third_score;
        mn = (mn < k) ? mn : k;
    }

    return mn;
}

static int max_score(const Specialisation *spec) {
    int mx = MIN_SCORE, count = spec -> count, k;

    if (count == 0) { return NO_DATA; }

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        int third_score = (student -> inf > student -> phys) ? student -> inf : student -> phys;
        k = student -> rus + student -> math + third_score;
        mx = (mx < k) ? k : mx;
    }

    return mx;
}

static int benefit_count(const Specialisation *spec, Benefit benefit) {
    int count = spec -> count, k = 0;

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;

        if (student -> benefit == benefit) { k++; }
    }

    return k;
}

static double rus_average(const Specialisation *spec) {
    int count = spec -> count, k = 0;
    double average;

    if (count == 0) { return NO_DATA; }


    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        k += student -> rus;
    }

    average = (double) k / count;
    return average;
}

static double math_average(const Specialisation *spec) {
    int count = spec -> count, k = 0;
    double average;

    if (count == 0) { return NO_DATA; }


    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        k += student -> math;
    }

    average = (double) k / count;
    return average;
}

static double inf_average(const Specialisation *spec) {
    int count = spec -> count, k = 0;
    double average;

    if (count == 0) { return NO_DATA; }


    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        k += student -> inf;
    }

    average = (double) k / count;
    return average;
}

static double phys_average(const Specialisation *spec) {
    int count = spec -> count, k = 0;
    double average;

    if (count == 0) { return NO_DATA; }

    for (int i = 0; i < count; i++) {
        const Guy *student = spec -> massive + i;
        k += student -> phys;
    }

    average = (double) k / count;
    return average;
}

void calculate(const Specialisation *spec, Statistics *result) {

    if (result == NULL) { return; }

    if (spec == NULL || spec -> count < 0 || spec -> count > MAX_STUDENTS) { return; }
    
    *result = (Statistics){
        .average_with = NO_DATA, .average_without = NO_DATA,
        .min_score = NO_DATA, .max_score = NO_DATA,
        .rus_average = NO_DATA, .math_average = NO_DATA,
        .inf_average = NO_DATA, .phys_average = NO_DATA
    };
    
    for (int i = 0; i < spec -> count; i++) {
        const Guy *student = spec -> massive + i;
    
        if (student -> rus < MIN_RUS_SCORE || student -> rus > MAX_SCORE ||
            student -> math < MIN_MATH_SCORE || student -> math > MAX_SCORE ||
            student -> phys < MIN_PHYS_SCORE || student -> phys > MAX_SCORE ||
            student -> inf < MIN_INF_SCORE || student -> inf > MAX_SCORE ||
            student -> benefit < BENEFIT_NONE || student -> benefit >= BENEFIT_COUNT) { return; }
    }

    result -> average_with = average_with(spec);
    result -> average_without = average_without(spec);
    result -> min_score = min_score(spec);
    result -> max_score = max_score(spec);
    result -> rus_average = rus_average(spec);
    result -> math_average = math_average(spec);
    result -> inf_average = inf_average(spec);
    result -> phys_average = phys_average(spec);

    for (int i = 0; i < BENEFIT_COUNT; i++) {
        *(result -> benefit_counts + i) = benefit_count(spec, (Benefit) i);
    } 
}

void print_score(double value, int precision) {

    if (value < 0) { printf("Нет данных | "); }

    else { printf("%10.*f | ", precision, value); }
}