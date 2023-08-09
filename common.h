#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define container_of(ptr, type, member) \
	((type*)((char*)(1 ? (ptr) : &((type*)0)->member) - offsetof(type, member)))

#endif /* !COMMON_H */
