#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

void section(char *title)
{
    printf("\n==================== %s ====================\n", title);
}

void compare(const char *fmt, ...)
{
    va_list ap1;
    va_list ap2;
    int r1, r2;

    va_start(ap1, fmt);
    va_copy(ap2, ap1);

    r1 = vprintf(fmt, ap1);
    r2 = ft_vprintf(fmt, ap2);

    va_end(ap1);
    va_end(ap2);

    printf("printf return    = %d\n", r1);
    printf("ft_printf return = %d\n", r2);
}

int main(void)
{
    section("CHAR");
    compare("Char: %c\n", 'A');
    compare("Char null: %c\n", 0);

    section("STRING");
    compare("String: %s\n", "Hello");
    compare("Empty: %s\n", "");
    compare("NULL: %s\n", NULL);

    section("POINTER");
    compare("Pointer: %p\n", (void *)0x1234);
    compare("Pointer NULL: %p\n", NULL);

    section("INT / DECIMAL");
    compare("Zero: %d\n", 0);
    compare("Positive: %d\n", 42);
    compare("Negative: %d\n", -42);
    compare("INT_MIN: %d\n", INT_MIN);
    compare("INT_MAX: %d\n", INT_MAX);

    section("UNSIGNED");
    compare("Unsigned: %u\n", 42);
    compare("Unsigned max: %u\n", UINT_MAX);

    section("HEXA");
    compare("Hex x: %x\n", 42);
    compare("Hex X: %X\n", 42);
    compare("Hex zero: %x\n", 0);

    section("PERCENT");
    compare("Percent: %%\n");

    section("MULTIPLE CONVERSIONS");
    compare("Mix: %c %s %d %x %%\n", 'A', "test", 42, 42);
    compare("%d %d %d\n", 1, 2, 3);

    section("FLAGS - WIDTH / ALIGN");
    compare("|%5d|\n", 42);
    compare("|%-5d|\n", 42);
    compare("|%05d|\n", 42);

    section("PRECISION");
    compare("|%.5d|\n", 42);
    compare("|%.0d|\n", 0);
    compare("|%.3s|\n", "Hello");

    section("FLAG COMBINATIONS");
    compare("|%8.5d|\n", 42);
    compare("|%-8.5d|\n", 42);
    compare("|%08.5d|\n", 42);

    section("ADVANCED FLAGS");
    compare("%+d\n", 42);
    compare("% d\n", 42);
    compare("%#x\n", 42);
    compare("%#X\n", 42);
    compare("%+#08x\n", 42);

    section("EDGE CASES");
    compare("%.d\n", 0);
    compare("%-.5d\n", 42);
    compare("%\n");

    return (0);
}
