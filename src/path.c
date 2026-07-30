#include <windows.h>
#include <strsafe.h>
#include <stdbool.h>
#include <string.h>

static bool ensure_trailing_backslash(char *buffer, size_t size)
{
	size_t len = strlen(buffer);

	if (len == 0)
		return false;

	if (buffer[len - 1] == '\\')
		return true;

	if (buffer[len - 1] == '/')
		buffer[len - 1] = '\\';
	else if (FAILED(StringCchCatA(buffer, size, "\\")))
		return false;

	return true;
}

static bool normalize_entry_path(char *dest, size_t dest_size, const char *entry)
{
	size_t i = 0;
	size_t j = 0;

	while (entry[i] == '/' || entry[i] == '\\')
		i++;

	while (entry[i] != '\0') {
		char c = entry[i++];

		if (c == '/')
			c = '\\';

		if (j + 1 >= dest_size)
			return false;

		dest[j++] = c;
	}

	dest[j] = '\0';
	return j > 0;
}

bool get_store_path(char *buffer, size_t size)
{
	const char *default_name = "\\.password-store";

	DWORD written;
	DWORD buffer_size = (DWORD)size;

	written = GetEnvironmentVariable(
			"PASSWORD_STORE_DIR",
			buffer,
			buffer_size
			);

	if (written >= buffer_size)
		return false;

	if (written != 0)
		return true;

	// fallback
	written = GetEnvironmentVariable(
			"USERPROFILE",
			buffer,
			buffer_size
			);

	if (written >= buffer_size || written == 0)
		return false;

	// concat .password_store
	HRESULT result;

	result = StringCchCatA(
			buffer,
			buffer_size,
			default_name
			);

	return SUCCEEDED(result);

}

bool append_entry(
	char *buffer, // buffer contianing store path
	size_t size, // size of buffer containing store path
	const char *entry
	)
{
	char normalized[MAX_PATH];
	HRESULT result;

	if (!ensure_trailing_backslash(buffer, size))
		return false;

	if (!normalize_entry_path(normalized, sizeof(normalized), entry))
		return false;

	result = StringCchCatA(buffer, size, normalized);
	if (!SUCCEEDED(result))
		return false;

	result = StringCchCatA(buffer, size, ".gpg");
	return SUCCEEDED(result);
}
