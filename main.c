#include <stdio.h>
#include <ctype.h>

int power(int base, int exp) {
    int result = 1;
    while(exp) { result *= base; exp--; }
    return result;
}

double calculate(char operator, double left, double right) {
    double result = 0;
    switch (operator) {
        case '+': result = right + left; break;
        case '-': result = right - left; break;
        case '*': result = right * left; break;
        case '/': result = right / left; break;
    }
    return result;
}

int get_priority(char token) {
    int priority = -1;
    switch (token) {
        case '+': priority = 1; break;
        case '-': priority = 1; break;
        case '*': priority = 2; break;
        case '/': priority = 2; break;
        case '(': priority = 0; break;
    }
    return priority;
}

int main() {
    char input[200] = {0};
    char postfix[100], operators[100];
    int postfix_top = -1;
    int operators_top = -1;
    int digit_length = 0;
    double digits[100] = {0};
    int digits_top = -1;
    int negative_reading = 0;

    printf("[❕] Please input infix math expression: ");
    scanf("%s", input);

    for (int i = 0; i < 200; i++) {
        if (isdigit(input[i])) {
            digit_length++;
        }

        if (!isdigit(input[i])) {
            // unify bracets
            if (input[i] == '[' || input[i] == '{') {
                input[i] = '(';
            } else if (input[i] == ']' || input[i] == '}') {
                input[i] = ')';
            }

            if (digit_length) {
                int new_deigits_top = ++digits_top;
                digits[new_deigits_top] = 0;

                // generate new int, push it onto the digits stack and postfix output string
                if (negative_reading) {
                    postfix[++postfix_top] = '-';
                }

                for (int j = 0; j < digit_length; j++) {
                    digits[new_deigits_top] += (input[i - j - 1] - '0') * power(10, j);
                    postfix[++postfix_top] = input[i - digit_length + j];
                }

                // printf("number is: %f\n", digits[new_deigits_top]);
                postfix[++postfix_top] = ' ';

                if (negative_reading) {
                    digits[new_deigits_top] *= -1;
                }

                digit_length = 0;
                negative_reading = 0;
            }

            if (input[i] == '-' && (i == 0 || !isdigit(input[i - 1]) && input[i - 1] != ')')) {
                printf("[🔍] found negative number, setting negative_reading to 1\n");
                negative_reading = 1;
            } else if (input[i] == '(') {
                operators[++operators_top] = input[i];
            } else if (input[i] == ')') {
                // printf("----- found enclosure bracket!\n");
                while (operators[operators_top] != '(') {
                    // calculate and push result to digits
                    if (
                        digits_top &&
                        (
                            operators[operators_top == '+'] ||
                            operators[operators_top == '-'] ||
                            operators[operators_top == '*'] ||
                            operators[operators_top == '/']
                        )
                    ) {
                        double left = digits[digits_top--];
                        double right = digits[digits_top--];
                        double result = calculate(operators[operators_top], left, right);
                        // printf("step calculation %c, left: %f, right: %f, result: %f\n", operators[operators_top], left, right, result);
                        digits[++digits_top] = result;
                    }

                    // printf("--------- dumping operators: %s\n", operators);
                    postfix[++postfix_top] = operators[operators_top--];
                    postfix[++postfix_top] = ' ';
                }

                operators_top--; // pop the "(" out
            } else {
                // + - * / logic
                while (operators_top > -1 && (get_priority(input[i]) <= get_priority(operators[operators_top]))) {
                    // printf("[🌲] scanning: %c, poping: %c, operators_top: %d\n", input[i], operators[operators_top], operators_top);

                    // calculate and push result to digits
                    if (
                        digits_top &&
                        (
                            operators[operators_top == '+'] ||
                            operators[operators_top == '-'] ||
                            operators[operators_top == '*'] ||
                            operators[operators_top == '/']
                        )
                    ) {
                        double left = digits[digits_top--];
                        double right = digits[digits_top--];
                        double result = calculate(operators[operators_top], left, right);
                        // printf("step calculation %c, left: %f, right: %f, result: %f\n", operators[operators_top], left, right, result);
                        digits[++digits_top] = result;
                    }

                    // write to postfix output
                    postfix[++postfix_top] = operators[operators_top--];
                    postfix[++postfix_top] = ' ';
                }

                if (input[i] != '\0') {
                    // printf("[🌲] pushing: %c to operator stack at index: %d\n", input[i], operators_top + 1);
                    operators[++operators_top] = input[i];
                }
            }
        }
    }

    postfix[postfix_top + 1] = '\0';
    printf("[✅] postfix format: %s\n", postfix);
    printf("[✅] evaluation result: %d\n", (int)digits[digits_top]);

    return 0;
}
