#include <string.h>
#include "stats.h"

static const char *BENEFIT_NAMES[BEN_COUNT] = {
    "Нет", "Особая квота", "Отдельная квота", "Целевой прием", "БВИ"
};

const char *benefit_name(Benefit b) {
    if ((int)b < 0 || (int)b >= BEN_COUNT) {
        return "?";
    }
    return *(BENEFIT_NAMES + b);
}

/* Сумма по 3 предметам: Математика + Русский + max(Физика, Информатика) */
int applicant_score(const Applicant *a) {
    if (a == NULL) {
        return 0;
    }
    int phys = *(a->scores + SUBJ_PHYSICS);
    int inf  = *(a->scores + SUBJ_INFORMATICS);
    int best = phys > inf ? phys : inf;
    return *(a->scores + SUBJ_RUSSIAN) + *(a->scores + SUBJ_MATH) + best;
}

/* Балл с учетом льгот: БВИ = 300 баллов */
int applicant_effective_score(const Applicant *a) {
    if (a == NULL) {
        return 0;
    }
    return a->benefit == BEN_BVI ? BVI_SCORE : applicant_score(a);
}

int applicant_is_valid(const Applicant *a) {
    if (a == NULL) {
        return 0;
    }
    for (const int *s = a->scores; s < a->scores + SUBJ_COUNT; s++) {
        if (*s < 0 || *s > MAX_SUBJECT_SCORE) {
            return 0;
        }
    }
    return (int)a->benefit >= 0 && (int)a->benefit < BEN_COUNT;
}

int calculate_direction_stats(const Direction *dir, DirectionStats *out) {
    if (dir == NULL || out == NULL) {
        return STATS_ERR_NULL;
    }
    if (dir->count < MIN_APPLICANTS || dir->count > MAX_APPLICANTS) {
        return STATS_ERR_COUNT;
    }

    memset(out, 0, sizeof(*out));

    long sum_no_benefit = 0;
    long sum_all = 0;
    long subject_sum[SUBJ_COUNT] = {0};
    int  no_benefit_count = 0;
    int  first = 1;

    const Applicant *p = dir->applicants;
    const Applicant *end = p + dir->count;

    for (; p < end; p++) {
        if (!applicant_is_valid(p)) {
            return STATS_ERR_DATA;
        }
        int eff = applicant_effective_score(p);
        sum_all += eff;

        if (p->benefit == BEN_NONE) {
            sum_no_benefit += applicant_score(p);
            no_benefit_count++;
        } else {
            out->benefit_total++;
        }
        *(out->benefit_count + p->benefit) += 1;

        if (first || eff < out->min_score) {
            out->min_score = eff;
        }
        if (first || eff > out->max_score) {
            out->max_score = eff;
        }
        first = 0;

        for (int k = 0; k < SUBJ_COUNT; k++) {
            *(subject_sum + k) += *(p->scores + k);
        }
    }

    out->has_no_benefit = no_benefit_count > 0;
    out->avg_no_benefit = no_benefit_count > 0
                          ? (double)sum_no_benefit / no_benefit_count : 0.0;
    out->avg_with_benefit = (double)sum_all / dir->count;
    for (int k = 0; k < SUBJ_COUNT; k++) {
        *(out->avg_subject + k) = (double)*(subject_sum + k) / dir->count;
    }
    return STATS_OK;
}

int calculate_all_stats(const Direction *dirs, int n, DirectionStats *out) {
    if (dirs == NULL || out == NULL || n <= 0) {
        return STATS_ERR_NULL;
    }
    const Direction *d = dirs;
    DirectionStats *s = out;
    for (; d < dirs + n; d++, s++) {
        int rc = calculate_direction_stats(d, s);
        if (rc != STATS_OK) {
            return rc;
        }
    }
    return STATS_OK;
}

const char *stats_error_text(int code) {
    switch (code) {
        case STATS_OK:        return "нет ошибок";
        case STATS_ERR_NULL:  return "пустой указатель или неверное число направлений";
        case STATS_ERR_COUNT: return "число абитуриентов вне диапазона 11..99";
        case STATS_ERR_DATA:  return "некорректные данные абитуриента (балл вне 0..100 или неверная льгота)";
        default:              return "неизвестная ошибка";
    }
}
