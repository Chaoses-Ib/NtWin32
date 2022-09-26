#include <NtWin32/ntdll.h>

#undef DECLSPEC_IMPORT
#define DECLSPEC_IMPORT

extern "C" {

WINBASEAPI
_Check_return_
_Post_equals_last_error_
DWORD
WINAPI
GetLastError(
    VOID
    )
{
    return (DWORD)NtCurrentTeb()->LastErrorValue;
}

WINBASEAPI
VOID
WINAPI
SetLastError(
    _In_ DWORD dwErrCode
    )
{
    NtCurrentTeb()->LastErrorValue = (LONG)dwErrCode;
}

}