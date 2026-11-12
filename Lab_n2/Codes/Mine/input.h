#ifndef INPUT_H
#define INPUT_H

#define MIN_SCORE 0
#define MAX_SCORE 100
#define MIN_STUDENTS 11
#define MAX_STUDENTS 99
#define STUDENT_CAPACITY 100
#define SPECIALISATION_COUNT 10
#define NAME_SIZE 64
#define NAME_VARIANTS_COUNT 10
#define SPECIALISATION_NAME_SIZE 128
#define INPUT_BUFFER_SIZE 128

typedef enum {
    BENEFIT_NONE,
    BENEFIT_SPECIAL_QUOTA,
    BENEFIT_SEPARATE_QUOTA,
    BENEFIT_TARGET,
    BENEFIT_BVI,
    BENEFIT_COUNT
} Benefit;

typedef struct {
    char name[NAME_SIZE], surname[NAME_SIZE], patronymic[NAME_SIZE];
    int rus, math, inf, phys;
    Benefit benefit;
} Guy;

typedef struct {
    char name[SPECIALISATION_NAME_SIZE];
    int count;
    Guy massive[STUDENT_CAPACITY];
} Specialisation;

int repeat_work(void);
/* Число заполненных направлений; 0 при выходе или прекращении ввода. */
int input_data(Specialisation *spec, int n);

#endif
