#include "repo.h"
#include <stdarg.h>


Response char_to_val(char c, int base) {
    int val;

    if (isdigit(c)) {
        val = c - '0';
    } else if (isalpha(c)) {
        val = toupper(c) - 'A' + 10;
    } else {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect digit for base");
    }

    if (val >= base) {
        return CreateErrorResponse(ERROR_VALUE, "Incorrect digit for base");
    }

    return CreateSuccessResponse(&val);
}


char val_to_char(int val) {
    if (val < 10) {
        return '0' + val;
    } else {
        return 'A' + (val - 10);
    }
}

Response add_in_base(const char *num1, const char *num2, int base) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = len1 > len2 ? len1 : len2;

    char *result = (char *)malloc(max_len + 2);
    if (result == NULL) {
        return CreateErrorResponse(ERROR_MEMORY, "Memory allocation error");
    }
    result[max_len + 1] = '\0';

    int carry = 0;
    int i = len1 - 1, j = len2 - 1, k = max_len;

    while (k >= 0) {  // Изменяем условие на k >= 0 для правильного размещения результата
        int sum = carry;
        
        if (i >= 0) {
            Response r_part1 = char_to_val(num1[i--], base);
            if (r_part1.status.code != OK) {
                free(result);  // Освобождаем память при ошибке
                return r_part1;
            }
            sum += *(int*)(r_part1.data);
        }
        if (j >= 0) {
            Response r_part2 = char_to_val(num2[j--], base);
            if (r_part2.status.code != OK) {
                free(result);  // Освобождаем память при ошибке
                return r_part2;
            }
            sum += *(int*)(r_part2.data);
        }

        result[k--] = val_to_char(sum % base);
        carry = sum / base;
    }

    if (carry > 0) {
        result[0] = val_to_char(carry);
        return CreateSuccessResponse(result);  // Возвращаем результат, если есть перенос
    } else {
        // Если нет переноса, создаем новую строку без ведущих нулей
        char *new_result = strdup(result + 1);  // Строка без ведущего нуля
        free(result);  // Освобождаем память для оригинального результата
        return CreateSuccessResponse(new_result);
    }
}

Response sum_in_base(int base, int num_count, ...) {
    va_list args;
    va_start(args, num_count);

    char *sum = strdup("0");
    if (sum == NULL) {
        return CreateErrorResponse(ERROR_MEMORY, "Memory allocation error");
    }

    for (int i = 0; i < num_count; ++i) {
        const char *num = va_arg(args, const char *);

        Response r_new_sum = add_in_base(sum, num, base);
        if (r_new_sum.status.code != OK) {
            free(sum);
            return r_new_sum;
        }
        char *new_sum = (char*)(r_new_sum.data);

        free(sum);
        sum = new_sum;
    }

    va_end(args);


    char *start = sum;  // Указатель на начало результата
    while (*sum == '0' && *(sum + 1) != '\0') {
        sum++;
    }

    // Если было смещение, создаем новую строку без ведущих нулей
    if (start != sum) {
        char *new_sum = strdup(sum);
        free(start);  // Освобождаем оригинальную строку
        sum = new_sum;  // Обновляем указатель на новую строку
    }

    return CreateSuccessResponse(sum);
}
