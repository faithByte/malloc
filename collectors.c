#include "list.h"

_ptr	**getCollectors(short type) {
	static _ptr	*list1, *list2, *list3;

	if (type == 0)
		return &list1;
	else if (type == 1)
		return &list2;
	else
		return &list3;
}