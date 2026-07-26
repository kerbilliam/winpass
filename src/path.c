#include <windows.h>
#include <strsafe.h>
#include <stdbool.h>

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

/*
bool append_entry(
		char *buffer,
		size_t size,
		const char *store,
		const char *entry
		)
{

}
*/
