#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_number(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    char *endptr;
    strtod(str, &endptr);
    return endptr != str && *endptr == '\0';
}

void print_usage() {
    printf("Использование:\n");
    printf("  calculator --operation <multiply|divide> <число1> <число2> ... <числоN>\n");
    printf("  Где N — количество операндов от 5 до 7.\n");
    printf("\nПримеры:\n");
    printf("  calculator --operation multiply 2 3 4 5 6\n");
    printf("  calculator --operation divide 100 2 5 10 1\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    char *op = NULL;
    double operands[7];
    int operand_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--operation") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Ошибка: не указано название операции после --operation\n");
                return 1;
            }
            op = argv[++i];
        } else if (is_number(argv[i])) {
            if (operand_count >= 7) {
                fprintf(stderr, "Ошибка: слишком много операндов (максимум 7)\n");
                return 1;
            }
            operands[operand_count++] = atof(argv[i]);
        } else {
            fprintf(stderr, "Ошибка: некорректный аргумент '%s'\n", argv[i]);
            return 1;
        }
    }


    if (op == NULL) {
        fprintf(stderr, "Ошибка: не указана операция (--operation)\n");
        print_usage();
        return 1;
    }


    if (operand_count < 5 || operand_count > 7) {
        fprintf(stderr, "Ошибка: количество операндов должно быть от 5 до 7, получено %d\n", operand_count);
        return 1;
    }

    double result = operands[0];

    if (strcmp(op, "multiply") == 0) {
        for (int i = 1; i < operand_count; i++) {
            result *= operands[i];
        }
        printf("Результат умножения: %.6f\n", result);
    } else if (strcmp(op, "divide") == 0) {
        for (int i = 1; i < operand_count; i++) {
            if (operands[i] == 0.0) {
                fprintf(stderr, "Ошибка: деление на ноль!\n");
                return 1;
            }
            result /= operands[i];
        }
        printf("Результат деления: %.6f\n", result);
    } else {
        fprintf(stderr, "Ошибка: неизвестная операция '%s'\n", op);
        print_usage();
        return 1;
    }

    return 0;
}
