#include <windows.h>
#include <stdio.h>
#include <strsafe.h>

// print dirs in bright blue using ANSI Escape Sequence
#define PRINT_DIR(y) wprintf(L"\x1b[94m%ls\x1b[0m\n", (y))
#define PRINT_ENTRY(y) wprintf(L"%ls\n", (y))
#define PRINT_BRANCH wprintf(L"├──")
#define PRINT_END_BRANCH wprintf(L"└──")

static void spacer(int count)
{
	if (count > 0)
		wprintf(L"│");

	while (count-- > 0) {
		wprintf(L"   ");
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
	WIN32_FIND_DATAW next_ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	wchar_t working_path[MAX_PATH];

	StringCchCopyW(working_path, MAX_PATH, path);
	StringCchCatW(working_path, MAX_PATH, L"\\*");

	hFind = FindFirstFileW(working_path, &ffd);

	if (INVALID_HANDLE_VALUE == hFind) {
		_putws(L"ERROR: FindFirstFile - INVALID_HANDLE_VALUE.");
		return(1);
	}

	// list loop
	BOOL current = TRUE;
	
	while (current) {
		BOOL next_exists = FindNextFileW(hFind, &next_ffd);

		if(ffd.cFileName[0] == L'.') {
			if (!next_exists)
				break;

			ffd = next_ffd;
			continue;
		}
		
		spacer(depth);

		if (next_exists) {
			PRINT_BRANCH;
		} else {
			PRINT_END_BRANCH;
		}
		
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			PRINT_DIR(ffd.cFileName);
			
			wchar_t newdir[MAX_PATH];
			build_new_dir(newdir, path, ffd.cFileName);
			walk(newdir, depth + 1);
		} else {
			PRINT_ENTRY(ffd.cFileName);
		}
		
		ffd = next_ffd;
		current = next_exists;
	}

	FindClose(hFind);
	return 0;
}

int tree(wchar_t *path)
{
	return walk(path, 0);
}