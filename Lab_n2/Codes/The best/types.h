#ifndef TYPES_H
#define TYPES_H

#define DIRECTION_COUNT   10   /* количество направлений */
#define MIN_APPLICANTS    11   /* абитуриентов на направлении больше 10 */
#define MAX_APPLICANTS    99   /* ... и меньше 100 */
#define NAME_LEN          64
#define DIR_NAME_LEN      48
#define MAX_SUBJECT_SCORE 100
#define BVI_SCORE         300  /* балл за "Без вступительных испытаний" */

typedef enum {
    SUBJ_RUSSIAN = 0,
    SUBJ_MATH,
    SUBJ_PHYSICS,
    SUBJ_INFORMATICS,
    SUBJ_COUNT
} Subject;

typedef enum {
    BEN_NONE = 0,      /* Нет */
    BEN_SPECIAL,       /* Особая квота */
    BEN_SEPARATE,      /* Отдельная квота */
    BEN_TARGET,        /* Целевой прием */
    BEN_BVI,           /* Без вступительных испытаний */
    BEN_COUNT
} Benefit;

/* ФИО, баллы по 4 предметам, льгота */
typedef struct {
    char    name[NAME_LEN];
    int     scores[SUBJ_COUNT];
    Benefit benefit;
} Applicant;

/* Одно направление подготовки */
typedef struct {
    char      name[DIR_NAME_LEN];
    Applicant applicants[MAX_APPLICANTS];
    int       count;
} Direction;

/* Результаты подсчета по направлению */
typedef struct {
    int    has_no_benefit;              /* есть ли абитуриенты без льгот */
    double avg_no_benefit;              /* 1. средний балл без учета льгот   */
    double avg_with_benefit;            /* 2. средний балл с учетом льгот    */
    int    min_score;                   /* 3. минимальная сумма баллов       */
    int    max_score;                   /* 4. максимальная сумма баллов      */
    int    benefit_count[BEN_COUNT];    /* 5. количество по категориям       */
    int    benefit_total;               /*    всего льготников               */
    double avg_subject[SUBJ_COUNT];     /* 6. средний балл по предметам      */
} DirectionStats;

#endif
