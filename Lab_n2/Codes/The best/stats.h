#ifndef STATS_H
#define STATS_H

#include "types.h"

#define STATS_OK        0
#define STATS_ERR_NULL  1
#define STATS_ERR_COUNT 2
#define STATS_ERR_DATA  3

int         applicant_score(const Applicant *a);
int         applicant_effective_score(const Applicant *a);
int         applicant_is_valid(const Applicant *a);
const char *benefit_name(Benefit b);

int         calculate_direction_stats(const Direction *dir, DirectionStats *out);
int         calculate_all_stats(const Direction *dirs, int n, DirectionStats *out);
const char *stats_error_text(int code);

#endif
