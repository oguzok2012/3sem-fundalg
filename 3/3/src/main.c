#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char surname[50];
    double salary;
} Employee;


Employee* allocate_memory(size_t capacity) {
    Employee *employees = malloc(capacity * sizeof(Employee));
    if (!employees) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    return employees;
}

Employee* reallocate_memory(Employee *employees, size_t new_capacity) {
    employees = realloc(employees, new_capacity * sizeof(Employee));
    if (!employees) {
        perror("Error reallocating memory");
        exit(EXIT_FAILURE);
    }
    return employees;
}


int compare_asc(const void *a, const void *b) {
    const Employee *emp1 = (const Employee *)a;
    const Employee *emp2 = (const Employee *)b;

    if (emp1->salary != emp2->salary)
        return (emp1->salary > emp2->salary) - (emp1->salary < emp2->salary);
    int surname_cmp = strcmp(emp1->surname, emp2->surname);
    if (surname_cmp != 0)
        return surname_cmp;
    int name_cmp = strcmp(emp1->name, emp2->name);
    if (name_cmp != 0)
        return name_cmp;
    return emp1->id - emp2->id;
}

int compare_desc(const void *a, const void *b) {
    const Employee *emp1 = (const Employee *)a;
    const Employee *emp2 = (const Employee *)b;

    if (emp1->salary != emp2->salary)
        return (emp2->salary > emp1->salary) - (emp2->salary < emp1->salary);
    int surname_cmp = strcmp(emp2->surname, emp1->surname);
    if (surname_cmp != 0)
        return surname_cmp;
    int name_cmp = strcmp(emp2->name, emp1->name);
    if (name_cmp != 0)
        return name_cmp;
    return emp2->id - emp1->id;
}

void read_employees(const char *input_path, Employee **employees, size_t *count) {
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    *count = 0;
    size_t capacity = 10;
    *employees = allocate_memory(capacity);

    Employee emp;
    while (fscanf(file, "%d %49s %49s %lf", &emp.id, emp.name, emp.surname, &emp.salary) == 4) {
        if (*count >= capacity) {
            capacity *= 2;
            *employees = reallocate_memory(*employees, capacity);
        }
        (*employees)[(*count)++] = emp;
    }
    fclose(file);
}

void write_employees(const char *output_path, Employee *employees, size_t count) {
    FILE *file = fopen(output_path, "w");
    if (!file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %.2f\n", employees[i].id, employees[i].name, employees[i].surname, employees[i].salary);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <-a/-d> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_path = argv[1];
    const char *flag = argv[2];
    const char *output_path = argv[3];
    int ascending = (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0);
    int descending = (strcmp(flag, "-d") == 0 || strcmp(flag, "/d") == 0);

    if (!ascending && !descending) {
        fprintf(stderr, "Error: Invalid flag. Use '-a' or '/a' for ascending, '-d' or '/d' for descending.\n");
        return EXIT_FAILURE;
    }

    Employee *employees = NULL;
    size_t count = 0;
    read_employees(input_path, &employees, &count);

    if (ascending) {
        qsort(employees, count, sizeof(Employee), compare_asc);
    } else {
        qsort(employees, count, sizeof(Employee), compare_desc);
    }

    write_employees(output_path, employees, count);
    free(employees);

    return EXIT_SUCCESS;
}
