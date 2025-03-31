#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <math.h>

char *get_binary(int decimal_num);

void calc(char *value1, char *op, char *value2)
{
    double num1 = atof(value1);
    double num2 = atof(value2);

    double res;

    switch (op[0])
    {
    case '+':
        res = num1 + num2;
        break;
    case '-':
        res = num1 - num2;
        break;
    case '*':
        res = num1 * num2;
        break;
    case '/':
        if (num2 == 0)
        {
            perror("Invalid input. Can't divide by 0.");
            return;
        }
        else
        {
            res = num1 / num2;
        }
        break;
    case '^':
        res = pow(num1, num2);
        break;
    default:
        perror("Invalid operator. Only +, -, *, / and ^ are supported");
        return;
    }

    printf("Resultado calc %.2f %s %.2f = %.2f\n", num1, op, num2, res);
}

void bits(char *value1, char *op, char *value2)
{
    unsigned short int num1 = atoi(value1);
    unsigned short int num2 = atoi(value2);
    unsigned short int res;
    switch (op[0])
    {
    case '&':
        res = num1 & num2;
        break;
    case '|':
        res = num1 | num2;
        break;
    case '^':
        res = num1 ^ num2;
        break;
    default:
        perror("Invalid operator. Only &, ^ and | are supported.");
        break;
    }

    printf("Result bits %d %c %d = %d\n", num1, op[0], num2, res);
}

char *get_binary(int decimal_num)
{
    char *binary = (char *)malloc(33 * sizeof(char));

    binary[32] = '\0';
    int index = 31;

    while (decimal_num > 0)
    {
        int bit = decimal_num % 2;
        binary[index--] = '0' + bit;
        decimal_num /= 2;
    }

    return &binary[index + 1];
}