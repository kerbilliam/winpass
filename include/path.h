#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
#include <stddef.h>

bool get_store_path(char *buffer, size_t size);
bool append_entry(char *buffer, size_t size, const char *entry);

#endif
