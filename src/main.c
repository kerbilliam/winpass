#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

#include <wchar.h>
#include <wctype.h>

#include "commands.h"
#include "path.h"

static int usage(void)
{
    return cmd_help();
}

int wmain(int argc, wchar_t *argv[])
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    wchar_t store_path[MAX_PATH];
    bool ok;
    ok = get_store_path(store_path, MAX_PATH);
    if (ok) {
	    _putws(store_path);
    } else {
	    _putws(L"Error: password store is empty. Try \"pass init\".");
	    return 1;
    }

    if (argc < 2)
        return usage();

    if (wcscmp(argv[1], L"help") == 0)
        return cmd_help();

    if (wcscmp(argv[1], L"init") == 0)
        return cmd_init();

    if (wcscmp(argv[1], L"list") == 0)
        return cmd_list(store_path);

    if (wcscmp(argv[1], L"insert") == 0) {
        if (argc < 3) {
		_putws(L"ERROR: Need a password name!");
            	return 1;
	}

        return cmd_insert(argv[2]);
    }

    if (wcscmp(argv[1], L"show") == 0) {
        if (argc < 3) {
		_putws(L"ERROR: Need a password name!");
            	return 1;
	}

        return cmd_show(store_path, sizeof(store_path), argv[2]);
    }

    if (wcscmp(argv[1], L"rm") == 0) {
        if (argc < 3) {
		_putws(L"ERROR: Need a password name!");
            	return 1;
	}
        return cmd_remove(argv[2]);
    }


    return usage();
}
