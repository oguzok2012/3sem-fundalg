#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "responses.h"
#include "repo.h"
#include "textmenu.h"
#include "context.h"

Context context;

void *create_students() {
    Response read_response = read_students(context.input_file, &(context.students_number));
    if (read_response.status.code != OK) {
        perror(read_response.status.msg);
    }
    Student *students = (Student *)read_response.data;
    return students;
}


void destroyer_students(void *obj) {
    Student *students = (Student *)obj;
    free_students(students, context.students_number);
}


// Handlers

void sort_students_(void *obj) {
    Student *students = (Student *)obj;
    char sort_option;
    scanf(" %c", &sort_option);
    sort_students(students, context.students_number, sort_option);
}

void print_students_(void *obj) {
    Student *students = (Student *)obj;
    print_students(students, context.students_number);
}

void find_best_(void *obj) {
    Student *students = (Student *)obj;
    find_best_and_write_to_file(context.output_file, students, context.students_number);
}

void find_by_id_(void *obj) {
    Student *students = (Student *)obj;
    int id;
    scanf("%d", &id);
    find_student_by_id_and_write_to_file(context.output_file, students, context.students_number, &id);
}


void find_students_by_(void *obj) {
    Student *students = (Student *)obj;
    char find_option[20];
    void *value = NULL;
    CompareFunc cmp_func = NULL;

    printf("Enter field for searching (id, name, surname, group): ");
    scanf("%s", find_option);

    if (strcmp(find_option, "id") == 0) {
        value = malloc(sizeof(int));
        if (value == NULL) {
            perror("Memory allocation error");
            return;
        }
        printf("Enter id: ");
        scanf("%d", (int *)value);
        cmp_func = compare_uint; 

    } else if (strcmp(find_option, "name") == 0) {
        value = malloc(50 * sizeof(char));
        if (value == NULL) {
            perror("Memory allocation error");
            return;
        }
        printf("Enter name: ");
        scanf("%49s", (char *)value);
        cmp_func = compare_by_name;

    } else if (strcmp(find_option, "surname") == 0) {
        value = malloc(50 * sizeof(char));
        if (value == NULL) {
            perror("Memory allocation error");
            return;
        }
        printf("Enter surname: ");
        scanf("%49s", (char *)value);
        cmp_func = compare_by_surname;

    } else if (strcmp(find_option, "group") == 0) {
        value = malloc(sizeof(int));
        if (value == NULL) {
            perror("Memory allocation error");
            return;
        }
        printf("Enter group: ");
        scanf("%d", (int *)value);
        cmp_func = compare_by_group;

    } else {
        printf("Incorrect oprion for searching.\n");
        return;
    }
    int found_students_number;
    Response response = find_students_by(students, context.students_number, find_option, value, cmp_func, &found_students_number);
    if (response.status.code == OK) {
        Student *found_students = (Student *) response.data;
        print_students(found_students, found_students_number);
        free_students(found_students, found_students_number);
    } else {
        printf("Students not found\n");
    }
    
}



int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    

    create_context(&context, input_file, output_file);

    textMenuFastInitialize(5,
                            "print", "print - print_students.", print_students_,
                            "sort", "sort - sort_students.", sort_students_,
                            "find_best", "find_best - finds students with average value or marks more than average value of all students\n                and writes to output file", find_best_,
                            "find_by_id", "find_by_id <value> - finds student by id and wriye information about him to output file", find_by_id_,
                            "find_by", "find_by <op> <value> - finds and print found student(s)", find_students_by_
                            );
    textMenuFastStart(create_students, destroyer_students);
    textMenuFastClose();
}