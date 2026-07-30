#include <stdio.h>
#include <windows.h>

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
    char store_path[MAX_PATH];
    bool ok;
    ok = get_store_path(store_path, MAX_PATH);
    if (ok) {
	    puts(store_path);
    } else
	    puts("ERROR: Store path could not be resolved.");

    if (argc < 2)
        return usage();

    if (wcscmp(argv[1], L"help") == 0)
        return cmd_help();

    if (wcscmp(argv[1], L"init") == 0)
        return cmd_init();

    if (wcscmp(argv[1], L"list") == 0)
        return cmd_list();

    if (wcscmp(argv[1], L"insert") == 0) {
        if (argc < 3) {
		puts("ERROR: Need a password name!");
            	return 1;
	}

        return cmd_insert(argv[2]);
    }

    if (wcscmp(argv[1], L"show") == 0) {
        if (argc < 3) {
		puts("ERROR: Need a password name!");
            	return 1;
	}

        return cmd_show(store_path, sizeof(store_path), argv[2]);
    }

    if (wcscmp(argv[1], L"rm") == 0) {
        if (argc < 3) {
		puts("ERROR: Need a password name!");
            	return 1;
	}
        return cmd_remove(argv[2]);
    }


    return usage();
}
