#include "repo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Response allocate_students(size_t capacity) {
    Student *students = (Student *)malloc(capacity * sizeof(Student));
    if (!students) {
        return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Error allocating memory for students");
    }
    return CreateSuccessResponse(students);
}

Response reallocate_students(Student *students, size_t new_capacity) {
    Student *new_students = (Student *)realloc(students, new_capacity * sizeof(Student));
    if (!new_students) {
        return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Error reallocating memory for students");
    }
    return CreateSuccessResponse(new_students);
}


void free_students(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].grades);
    }
    free(students);
}


Response read_students(const char *filepath, int *count) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        return CreateErrorResponse(ERROR_FILE, "Error opening file");
    }

    size_t capacity = 10;
    Response alloc_response = allocate_students(capacity);
    if (alloc_response.status.code != OK) {
        fclose(file);
        return alloc_response;
    }

    Student *students = (Student *)alloc_response.data;

    while (1) {
        Student student;

        if (fscanf(file, "%u %49s %49s %19s", 
                   &student.id, 
                   student.name, 
                   student.surname, 
                   student.group) != 4) {
            break;
        }

        student.grades = (unsigned char *)malloc(grade_count * sizeof(unsigned char));
        if (!student.grades) {
            fclose(file);
            free(students);
            return CreateErrorResponse(ERROR_BUFFER_OVERFLOW, "Error allocating memory for grades");
        }

        for (int i = 0; i < grade_count; i++) {
            if (fscanf(file, "%hhu", &student.grades[i]) != 1) {
                free(student.grades);
                fclose(file);
                free_students(students, grade_count);
                return CreateErrorResponse(ERROR_FILE, "Error reading grade");
            }
        }

        if (*count >= capacity) {
            Response realloc_response = reallocate_students(students, capacity * 2);
            if (realloc_response.status.code != OK) {
                fclose(file);
                free_students(students, *count);
                return realloc_response;
            }
            students = (Student *)realloc_response.data;
            capacity *= 2;
        }
        int k = (*count)++;
        students[k] = student;
    }

    fclose(file);
    return CreateSuccessResponse(students);
}



typedef int (*CompareFunc)(const void *a, const void *b);

int compare_uint(const void *a, const void *b) {
    return (*(unsigned int *)a - *(unsigned int *)b);
}

int compare_string(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int compare_by_id(const void *a, const void *b) {
    return ((Student *)a)->id - ((Student *)b)->id;
}

int compare_by_surname(const void *a, const void *b) {
    return strcmp(((Student *)a)->surname, ((Student *)b)->surname);
}

int compare_by_name(const void *a, const void *b) {
    return strcmp(((Student *)a)->name, ((Student *)b)->name);
}

int compare_by_group(const void *a, const void *b) {
    return ((Student *)a)->group - ((Student *)b)->group;
}

Response find_students_by(Student *students, int count, const char *field_name, const void *value, CompareFunc cmp_func, int *found_st_num) {
    Student *results = malloc(count * sizeof(Student));
    int result_count = 0;

    for (size_t i = 0; i < count; i++) {
        const void *field_value;

        if (strcmp(field_name, "id") == 0) {
            field_value = &students[i].id;
        } else if (strcmp(field_name, "name") == 0) {
            field_value = students[i].name;
        } else if (strcmp(field_name, "surname") == 0) {
            field_value = students[i].surname;
        } else if (strcmp(field_name, "group") == 0) {
            field_value = students[i].group;
        } else {
            free(results);
            return CreateErrorResponse(ERROR_ATOI, "Invalid field name");
        }

        if (cmp_func(field_value, value) == 0) {
            results[result_count++] = students[i];
        }
    }
    if (result_count == 0) {
        free(results);
        return CreateErrorResponse(ERROR_ATOI, "No students found with the specified criteria");
    }
    *found_st_num = result_count;
    results = realloc(results, result_count * sizeof(Student));
    return CreateSuccessResponse(results);
}


void print_student(Student *student) {
    printf("ID: %u\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Surname: %s\n", student->surname);
    printf("Group: %s\n", student->group);
    
    if (student->grades != NULL) {
        printf("Grades: ");
        for (size_t i = 0; i < grade_count; i++) { 
            printf("%u ", student->grades[i]);
        }
        printf("\n");
    } else {
        printf("Grades: No grades available\n");
    }
}

void print_students(Student *students, int count) {
    printf("-----------------------\n");
    for (int i = 0; i < count; i++) {
        print_student(&students[i]);
        printf("-----------------------\n");
    }
}

void sort_students(Student *students, int count, char sort_option) {
    
    if (sort_option == 'i') {
        qsort(students, count, sizeof(Student), compare_by_id);
    } else if (sort_option == 's') {
        qsort(students, count, sizeof(Student), compare_by_surname);
    } else if (sort_option == 'n') {
        qsort(students, count, sizeof(Student), compare_by_name);
    } else if (sort_option == 'g') {
        qsort(students, count, sizeof(Student), compare_by_group);
    } else {
        fprintf(stderr, "Invalid sort option\n");
    }
}

double calculate_average_of_grades(Student student) {
    double sum = 0;
    for (int i = 0; i < grade_count; i++) {
        sum += student.grades[i];
    }
    return sum / (double)grade_count;
}

int find_student_by_id_and_write_to_file(const char *filename, Student *students, int count, int *id) {
    int found;
    Response response_found = find_students_by(students, count, "id", (const void*)id, compare_uint, &found);
    if (response_found.status.code != OK) {
        printf("%s\n", response_found.status.msg);
        return 0;
    }
    Student *found_students = (Student *)(response_found.data);
    Student student = found_students[0];
    double avg = calculate_average_of_grades(student);
    FILE *file = fopen(filename, "w");
    if (!file) {
        return 1;
    }
    fprintf(file, "id: %d\nname: %s\nsurname: %s\ngroup: %s\navg: %f", 
            student.id,
            student.name,
            student.surname,
            student.group,
            avg);
    
    printf("Data of the student was written to file\n");
    fclose(file);
    free_students(found_students, found);
    return 0;
}

int find_best_and_write_to_file(const char *filename, Student *students, int count) {
    double *students_avg = malloc(count * sizeof(double)); 

    double total_avg = 0.0;
    for (int i = 0; i < count; i++) {
        double student_avg = calculate_average_of_grades(students[i]);
        students_avg[i] = student_avg;
        total_avg += student_avg;
    }
    total_avg /= count;


    FILE *file = fopen(filename, "w");
    if (!file) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        if (students_avg[i] > total_avg) {
            fprintf(file, "%s %s\n", students[i].surname, students[i].name);
        }
    }
    printf("Data of students was written to file\n");
    fclose(file);
    free(students_avg);
    return 0;
}


