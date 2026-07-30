#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>
#include <wchar.h>

int cmd_help(void);
int cmd_init(void);
int cmd_insert(const wchar_t *name);
int cmd_show(char *buffer, size_t size, const wchar_t *entry);
int cmd_list(void);
int cmd_remove(const wchar_t *name);

#endif
