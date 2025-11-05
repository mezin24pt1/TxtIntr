#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Проверка, является ли строка числом
bool is_number(const std::string& s) {
    if (s.empty()) return false;
    size_t pos = 0;
    try {
        std::stod(s, &pos);
        return pos == s.length();
    } catch (...) {
        return false;
    }
}

void print_usage() {
    std::cout << "Использование:\n";
    std::cout << "  ./calculator.out [OPTIONS] <число1> <число2> ... <числоN>\n";
    std::cout << "\nОпции:\n";
    std::cout << "  -h, --help           Вывести эту справку\n";
    std::cout << "  -o, --operation      Выбрать операцию (обязательно)\n";
    std::cout << "      -o multiply       Умножить все числа\n";
    std::cout << "      --operation divide Делить первое число на остальные\n";
    std::cout << "\nПримеры:\n";
    std::cout << "  ./calculator.out -o multiply 2 3 4 5 6\n";
    std::cout << "  ./calculator.out --operation divide 100 2 5 10 1\n";
    std::cout << "  ./calculator.out -h\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string operation;
    std::vector<double> operands;
    bool show_help = false;

    // Парсинг аргументов
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            show_help = true;
        } else if (arg == "-o" || arg == "--operation") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: не указано название операции после " << arg << "\n";
                print_usage();
                return 1;
            }
            operation = argv[++i];
        } else if (is_number(arg)) {
            if (operands.size() >= 7) {
                std::cerr << "Ошибка: слишком много операндов (максимум 7)\n";
                return 1;
            }
            operands.push_back(std::stod(arg));
        } else {
            std::cerr << "Ошибка: некорректный аргумент '" << arg << "'\n";
            print_usage();
            return 1;
        }
    }

    // Приоритет: если есть -h --help — выводим справку и выходим
    if (show_help) {
        print_usage();
        return 0;
    }

    // Проверка операции
    if (operation.empty()) {
        std::cerr << "Ошибка: не указана операция (--operation или -o)\n";
        print_usage();
        return 1;
    }

    // Проверка количества операндов
    if (operands.size() < 5 || operands.size() > 7) {
        std::cerr << "Ошибка: количество операндов должно быть от 5 до 7, получено "
                  << operands.size() << "\n";
        print_usage();
        return 1;
    }

    double result = operands[0];

    if (operation == "multiply") {
        for (size_t i = 1; i < operands.size(); ++i) {
            result *= operands[i];
        }
        std::cout << "Результат умножения: " << result << "\n";
    } else if (operation == "divide") {
        for (size_t i = 1; i < operands.size(); ++i) {
            if (operands[i] == 0.0) {
                std::cerr << "Ошибка: деление на ноль!\n";
                return 1;
            }
            result /= operands[i];
        }
        std::cout << "Результат деления: " << result << "\n";
    } else {
        std::cerr << "Ошибка: неизвестная операция '" << operation << "'\n";
        print_usage();
        return 1;
    }

    return 0;
}
