#include "utils.h"

void	print(char *str) {
	if (!str)
		return;

	write(1, str, strlen(str));
}