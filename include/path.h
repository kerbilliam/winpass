#ifndef PATH_H
#define PATH_H

#include <stdbool.h>
#include <stddef.h>

bool get_store_path(wchar_t *buffer, size_t size);
bool append_entry(wchar_t *buffer, size_t size, const wchar_t *entry);
void trim_extension(wchar_t *filepath);

#endif
