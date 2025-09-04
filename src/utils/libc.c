#include "utils.h"

void	print(char *str) {
	if (!str)
		return;

	write(1, str, strlen(str));
}

void	printNbr(size_t n, short base) {
	char	digit[16] = "0123456789ABCDEF";

	if (!n)
		return;
	printNbr((size_t)n / base, base);
	write(1, digit + (n % base), 1);
}

void	printNumber(size_t n, short base) {
	if (base == HEXA_BASE)
		write(1, "0x", 2);
	else if (n < 0)
		write(1, "-", 1);

	if (!n)
		write(1, "0", 1);
	else
		printNbr(n, base);
}