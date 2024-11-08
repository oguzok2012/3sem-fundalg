#ifndef __REPO__
#define __REPO__

#include "responses.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>


#define grade_count 5

typedef struct {
    unsigned int id;
    char name[50];
    char surname[50];
    char group[20];
    unsigned char *grades;
} Student;

typedef struct {
    Student *students;
    int number;
    const char *input_file;
    const char *output_file;
} Metadata;

typedef int (*CompareFunc)(const void *a, const void *b);


Response allocate_students(size_t capacity);
Response reallocate_students(Student *students, size_t new_capacity);
void free_students(Student *students, int count);


Response read_students(const char *filepath, int *count);

Response find_students_by(Student *students, int count, const char *field_name, const void *value, CompareFunc cmp_func, int *found_st_num);
void sort_students(Student *students, int count, const char sort_option);


int compare_uint(const void *a, const void *b);
int compare_string(const void *a, const void *b);
int compare_by_id(const void *a, const void *b);
int compare_by_surname(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_group(const void *a, const void *b);


void print_student(Student *student);
void print_students(Student *students, int count);
double calculate_average_of_grades(Student student);

int find_student_by_id_and_write_to_file(const char *filename, Student *students, int count, int *id);
int find_best_and_write_to_file(const char *filename, Student *students, int count);


#endif
