#include <windows.h>
#include <stdio.h>
#include <strsafe.h>

// print dirs in bright blue using ANSI Escape Sequence
#define PRINT_DIR(y) wprintf(L"\x1b[94m%ls\x1b[0m\n", (y))
#define PRINT_ENTRY(y) wprintf(L"%ls\n", (y))
#define PRINT_BRANCH wprintf(L"├─")
#define PRINT_END_BRANCH wprintf(L"└─")

static void spacer(int count)
{
	while (count > 0) {
		wprintf(L"    ");
		count--;
	}
}

static int build_new_dir(wchar_t *buffer, const wchar_t *basedir, const wchar_t *dir)
{
	HRESULT ok;
	ok = StringCchCopyW(buffer, MAX_PATH, basedir);
	
	if (FAILED(ok)) {
		_putws(L"ERROR: cannot copy basedir to buffer for new path.");
		return 1;
	}

	StringCchCatW(buffer, MAX_PATH, L"\\");

	if (FAILED(ok)) {
		_putws(L"ERROR: cannot cat dir to buffer for new path.");
		return 1;
	}

	StringCchCatW(buffer, MAX_PATH, dir);
	
	if (FAILED(ok)) {
		_putws(L"ERROR: cannot cat dir to buffer for new path.");
		return 1;
	}
	
	return 0;
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
			if (ffd.cFileName[0] == L'.') {
				continue;
			}
			spacer(depth);
			PRINT_BRANCH;
			PRINT_DIR(ffd.cFileName);
			
			// build new dirpath and recurse
			wchar_t newdir[MAX_PATH];
			build_new_dir(newdir, path, ffd.cFileName);
				
			walk(newdir, depth + 1);

		} else {
			spacer(depth);
			PRINT_END_BRANCH;
			PRINT_ENTRY(ffd.cFileName);
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

int tree(wchar_t *path)
{
	return walk(path, 0);
}