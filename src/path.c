#include <windows.h>
#include <strsafe.h>
#include <stdbool.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static bool ensure_trailing_backslash(wchar_t *buffer, size_t size)
{
	size_t len = wcslen(buffer);

	if (len == 0)
		return false;

	if (buffer[len - 1] == L'\\')
		return true;

	if (buffer[len - 1] == L'/')
		buffer[len - 1] = L'\\';
	else if (FAILED(StringCchCatW(buffer, size, L"\\")))
		return false;

	return true;
}

static bool normalize_entry_path(wchar_t *dest, size_t dest_size, const wchar_t *entry)
{
	size_t i = 0;
	size_t j = 0;

	while (entry[i] == L'/' || entry[i] == L'\\')
		i++;

	while (entry[i] != L'\0') {
		wchar_t c = entry[i++];

		if (c == L'/')
			c = L'\\';

		if (j + 1 >= dest_size)
			return false;

		dest[j++] = c;
	}

	dest[j] = L'\0';
	return j > 0;
}

bool get_store_path(wchar_t *buffer, size_t size)
{
	const wchar_t *default_name = L"\\.password-store";

	DWORD written;
	DWORD buffer_size = (DWORD)size;

	written = GetEnvironmentVariableW(
			L"PASSWORD_STORE_DIR",
			buffer,
			buffer_size
			);

	if (written >= buffer_size)
		return false;

	if (written != 0)
		return true;

	// fallback
	written = GetEnvironmentVariableW(
			L"USERPROFILE",
			buffer,
			buffer_size
			);

	if (written >= buffer_size || written == 0)
		return false;

	// concat .password_store
	HRESULT result;

	result = StringCchCatW(
			buffer,
			buffer_size,
			default_name
			);

	return SUCCEEDED(result);

}

bool append_entry(
	wchar_t *buffer, // buffer contianing store path
	size_t size, // size of buffer containing store path
	const wchar_t *entry
	)
{
	wchar_t normalized[MAX_PATH];
	HRESULT result;

	if (!ensure_trailing_backslash(buffer, size))
		return false;

	if (!normalize_entry_path(normalized, ARRAY_SIZE(normalized), entry))
		return false;

	result = StringCchCatW(buffer, size, normalized);
	if (!SUCCEEDED(result))
		return false;

	result = StringCchCatW(buffer, size, L".gpg");
	return SUCCEEDED(result);
}
