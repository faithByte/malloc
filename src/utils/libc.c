#include "utils.h"

void	print(char *str) {
	if (!str)
		return;

	write(1, str, strlen(str));
}

void	printNumber(size_t n, short base) {
	char	digit[16] = "0123456789ABCDEF";

	if (!n)
		return;
	printNumber((size_t)n / base, base);
	write(1, digit + (n % base), 1);
}