#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>
#include "commands.h"
#include "path.h"

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

int cmd_show(char *buffer, size_t size, const wchar_t *entry)
{
	bool ok;
	char entry_name[MAX_PATH];

	if (WideCharToMultiByte(CP_ACP, 0, entry, -1, entry_name, MAX_PATH, NULL, NULL) == 0) {
		puts("ERROR: Invalid entry name.");
		return 1;
	}

	ok = append_entry(buffer, size, entry_name);

	if (!ok) {
		puts("ERROR: Can't append entry to store path.");
		return 1;
	}

	if (PathFileExistsA(buffer)) {
		printf("show %s\n", buffer);
		return 0;
	}

	printf("ERROR: '%s' does not exist.\n", buffer);
	return 1;
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
