#include <stdio.h>
#include "commands.h"

int cmd_help(void)
{
	puts("Available commands:");
	puts("  init");
    	puts("  insert <name>");
    	puts("  show <name>");
    	puts("  list");
    	puts("  rm <name>");

    	return 0;
}

int cmd_init(void)
{
    	puts("init");
    	return 0;
}

int cmd_insert(const wchar_t *name)
{
    	wprintf(L"insert %ls\n", name);
    	return 0;
}

int cmd_show(const wchar_t *name)
{
    	wprintf(L"show %ls\n", name);
    	return 0;
}

int cmd_list(void)
{
    	puts("list");
    	return 0;
}

int cmd_remove(const wchar_t *name)
{
    	wprintf(L"remove %ls\n", name);
    	return 0;
}
