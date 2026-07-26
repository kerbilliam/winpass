#ifndef COMMANDS_H
#define COMMANDS_H

int cmd_help(void);
int cmd_init(void);
int cmd_insert(const wchar_t *name);
int cmd_show(const wchar_t *name);
int cmd_list(void);
int cmd_remove(const wchar_t *name);

#endif
