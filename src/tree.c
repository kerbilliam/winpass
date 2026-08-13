#include <windows.h>
#include <stdio.h>
#include <strsafe.h>

// print dirs in bright blue using ANSI Escape Sequence
#define PRINT_DIR(y) wprintf(L"\x1b[94m%ls\x1b[0m\n", (y))

static int walk(wchar_t *path, int depth);

int tree(wchar_t *path)
{
	return walk(path, 0);
}

static int walk(wchar_t *path, int depth)
{
	WIN32_FIND_DATAW ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	wchar_t szDir[MAX_PATH];

	StringCchCopyW(szDir, MAX_PATH, path);
	StringCchCatW(szDir, MAX_PATH, L"\\*");

	hFind = FindFirstFileW(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		_putws(L"ERROR: FindFirstFile - INVALID_HANDLE_VALUE.");
		return(1);
	}

	// list loop

	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			PRINT_DIR(ffd.cFileName);
		} else {
			wprintf(L"%ls\n", ffd.cFileName);
		}
	} while (FindNextFileW(hFind, &ffd) != 0);

	DWORD dwError = 0;
	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) {
		_putws(L"ERROR: NO MORE FILES");
	}

	FindClose(hFind);
	return 0;
}