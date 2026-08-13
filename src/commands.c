#include <stdio.h>
#include <windows.h>
#include <shlwapi.h>
#include "commands.h"
#include "path.h"
#include "tree.h"

int cmd_help(void)
{
	_putws(L"Available commands:");
	_putws(L"  init");
    	_putws(L"  insert <name>");
    	_putws(L"  show <name>");
    	_putws(L"  list");
    	_putws(L"  rm <name>");

    	return 0;
}

int cmd_init(void)
{
    	_putws(L"init");
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
		_putws(L"ERROR: Can't append entry to store path.");
		return 1;
	}

	if (PathFileExistsW(buffer)) {
		wprintf(L"show %ls\n", buffer);
		return 0;
	}

	wprintf(L"ERROR: '%ls' does not exist.\n", buffer);
	return 1;
}

int cmd_list(wchar_t *path)
{
		int err = tree(path);
		if (err)
			return 1;
    	return 0;
}

int cmd_remove(const wchar_t *name)
{
    	wprintf(L"remove %ls\n", name);
    	return 0;
}
