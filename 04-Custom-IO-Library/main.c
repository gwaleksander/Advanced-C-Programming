#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>

int print_scan_counter = 0;

struct point_t
{
    int x;
    int y;
};

int my_scanf(char *format, ...);

void print_int(int a, int check)
{
    if (a == 0)
    {
        if (check)
        {
            for (int i = 0; i < 4; ++i)
            {
                putchar('0');
                print_scan_counter++;
            }
        }
        putchar('0');
        print_scan_counter++;
        return;
    }
    if (a < 0)
    {
        putchar('-');
        print_scan_counter++;
        a *= -1;
    }
    long long int reverse = 0, a_length = (int)log10(a) + 1;
    for (int i = 0; i < a_length; i++)
    {
        reverse = reverse * 10 + a % 10;
        a /= 10;
    }
    for (int i = 0; i < a_length; i++)
    {
        putchar('0' + reverse % 10);
        reverse /= 10;
        print_scan_counter++;
    }
}

int my_printf(char *c, ...)
{
    print_scan_counter = 0;
    int num;
    va_list arg;
    va_start(arg, c);
    char *chr;
    double db;
    struct point_t pnt;
    while (*c != '\0')
    {
        if (*c == '%')
        {
            c++;
            switch (*c)
            {
            case 'd':
            case 'D':
                num = va_arg(arg, int);
                print_int(num, 0);
                break;

            case 'c':
            case 'C':
                num = va_arg(arg, int);
                putchar(num);
                print_scan_counter++;
                break;

            case 's':
            case 'S':
                chr = va_arg(arg, char *);
                while (*chr != '\x0')
                {
                    putchar(*chr);
                    print_scan_counter++;
                    chr++;
                }
                break;

            case 'f':
            case 'F':
                db = va_arg(arg, double);

                if (db == 0)
                {
                    putchar('0');
                    putchar('.');
                    for (int i = 0; i < 5; ++i)
                    {
                        putchar('0');
                    }
                    print_scan_counter += 7;
                    break;
                }

                int db_bef_dot = (int)db;
                print_int(db_bef_dot, 0);
                putchar('.');
                print_scan_counter++;
                int db_after_dot = (int)((float)(db - db_bef_dot) * pow(10, 5));
                if (db_bef_dot < 0)
                    db_after_dot *= -1;
                for (int i = (int)log10(db_after_dot) + 1; i <= 4; ++i)
                {
                    putchar('0');
                    print_scan_counter++;
                }
                print_int(db_after_dot, 1);
                break;

            case 'p':
            case 'P':
                pnt = va_arg(arg, struct point_t);
                putchar('(');
                print_int(pnt.x, 0);
                putchar(' ');
                print_int(pnt.y, 0);
                putchar(')');
                print_scan_counter += 3;
                break;
            }
        }
        else
        {
            putchar(*c);
            print_scan_counter++;
        }
        c++;
    }
    va_end(arg);
    return print_scan_counter;
}

int my_scanf(char *format, ...)
{
    print_scan_counter = 0;
    int scanned = 0;
    va_list arg;
    va_start(arg, format);
    int *res_ptr;
    long long int num = 0;
    double *db_res_ptr;
    struct point_t *point_ptr;
    char chr, chrr;
    int sign = 1;
    while (*format != '\0')
    {
        if (*format == '%')
        {
            scanned++;
            format++;
            switch (*format)
            {
            case 'd':
            case 'D':
                num = 0;
                sign = 1;
                print_scan_counter = 0;
                res_ptr = va_arg(arg, int *);
                while ((chr = getchar()) != '\n')
                {
                    if (isalpha(chr))
                    {
                        if (print_scan_counter == 0)
                            scanned = 0;
                        break;
                    }
                    if (chr == ' ')
                        break;
                    if (chr == '-')
                        sign = -1;
                    else
                        num += (chr - '0') * pow(10, print_scan_counter);
                    print_scan_counter++;
                }
                long long int reverse = 0, a_length = (int)log10(num) + 1;
                for (int i = 0; i < a_length; i++)
                {
                    reverse = reverse * 10 + num % 10;
                    num /= 10;
                }
                if (print_scan_counter != a_length)
                    reverse *= pow(10, (print_scan_counter - a_length));
                *res_ptr = (int)reverse;
                *res_ptr *= sign;
                break;

            case 'f':
            case 'F':
                db_res_ptr = va_arg(arg, double *);
                if ((chr = getchar()) == '0')
                {
                    if ((chrr = getchar()) != '.')
                    {
                        *db_res_ptr = 0;
                        return 1;
                    }
                    else
                        ungetc(chrr, stdin);
                }
                else
                    ungetc(chr, stdin);
                num = 0;
                sign = 1;
                print_scan_counter = 0;
                long long int bef_dot = 0;
                while ((chr = getchar()) != '.' && chr != '\n')
                {
                    if (isalpha(chr))
                    {
                        if (print_scan_counter == 0)
                        {
                            *db_res_ptr = 0;
                            return 0;
                        }
                        long long int reverse4 = 0, a_length4 = (int)log10(bef_dot) + 1;
                        for (int i = 0; i < a_length4; i++)
                        {
                            reverse4 = reverse4 * 10 + bef_dot % 10;
                            bef_dot /= 10;
                        }
                        if (print_scan_counter != a_length4)
                            reverse4 *= pow(10, (print_scan_counter - a_length4));
                        bef_dot = reverse4;
                        *db_res_ptr = sign * bef_dot;
                        return scanned;
                    }
                    if (chr == ' ')
                        break;
                    if (chr == '-')
                        sign = -1;
                    else
                    {
                        bef_dot += (chr - '0') * pow(10, print_scan_counter);
                        print_scan_counter++;
                    }
                }

                if (bef_dot != 0)
                {
                    long long int reverse4 = 0, a_length4 = (int)log10(bef_dot) + 1;
                    for (int i = 0; i < a_length4; i++)
                    {
                        reverse4 = reverse4 * 10 + bef_dot % 10;
                        bef_dot /= 10;
                    }
                    if (print_scan_counter != a_length4)
                        reverse4 *= pow(10, (print_scan_counter - a_length4));
                    bef_dot = reverse4;
                }

                long long int after_dot = 0;
                print_scan_counter = 0;

                while ((chr = getchar()) != '\n')
                {
                    if (isalpha(chr))
                        break;
                    if (chr == ' ')
                        break;
                    after_dot += (chr - '0') * pow(10, print_scan_counter);
                    print_scan_counter++;
                }

                long long int reverse5 = 0, a_length5 = (int)log10(after_dot) + 1;
                for (int i = 0; i < a_length5; i++)
                {
                    reverse5 = reverse5 * 10 + after_dot % 10;
                    after_dot /= 10;
                }
                if (print_scan_counter != a_length5)
                    reverse5 *= pow(10, (print_scan_counter - a_length5));
                double db_after_dot = reverse5;
                long long int t = pow(10, a_length5);
                db_after_dot /= t;

                *db_res_ptr = sign * (bef_dot + db_after_dot);

                break;

            case 'p':
            case 'P':
                num = 0;
                sign = 1;
                print_scan_counter = 0;
                getchar();
                point_ptr = va_arg(arg, struct point_t *);

                if (isalpha(chr = getchar()))
                {
                    point_ptr->x = 0;
                    point_ptr->y = 0;
                    return 0;
                }
                else
                    ungetc(chr, stdin);

                while ((chr = getchar()) != ' ')
                {
                    if (chr == ' ')
                        break;
                    if (chr == '-')
                        sign = -1;
                    else if (!isdigit(chr))
                    {
                        return 0;
                    }
                    else
                        num += (chr - '0') * pow(10, print_scan_counter);
                    print_scan_counter++;
                }
                long long int reverse2 = 0, a_length2 = (int)log10(num) + 1;
                for (int i = 0; i < a_length2; i++)
                {
                    reverse2 = reverse2 * 10 + num % 10;
                    num /= 10;
                }
                if (print_scan_counter != a_length2)
                    reverse2 *= pow(10, (print_scan_counter - a_length2));
                point_ptr->x = (int)reverse2;
                point_ptr->x *= sign;

                num = 0;
                sign = 1;
                print_scan_counter = 0;
                while ((chr = getchar()) != '\n')
                {
                    if (chr == ' ')
                        break;
                    if (chr == ')')
                    {
                        getchar();
                        break;
                    }
                    if (chr == '-')
                        sign = -1;
                    else if (!isdigit(chr))
                    {
                        return 0;
                    }
                    else
                        num += (chr - '0') * pow(10, print_scan_counter);
                    print_scan_counter++;
                }
                long long int reverse3 = 0, a_length3 = (int)log10(num) + 1;
                for (int i = 0; i < a_length3; i++)
                {
                    reverse3 = reverse3 * 10 + num % 10;
                    num /= 10;
                }
                if (print_scan_counter != a_length3)
                    reverse3 *= pow(10, (print_scan_counter - a_length3));
                point_ptr->y = (int)reverse3;
                point_ptr->y *= sign;

                scanned++;
                break;
            }
        }
        format++;
    }
    va_end(arg);
    return scanned;
}

int main()
{

    return 0;
}