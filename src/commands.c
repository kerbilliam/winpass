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

int cmd_show(wchar_t *buffer, size_t size, const wchar_t *entry)
{
	bool ok;

	ok = append_entry(buffer, size, entry);

	if (!ok) {
		puts("ERROR: Can't append entry to store path.");
		return 1;
	}

	if (PathFileExistsW(buffer)) {
		wprintf(L"show %ls\n", buffer);
		return 0;
	}

	wprintf(L"ERROR: '%ls' does not exist.\n", buffer);
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
