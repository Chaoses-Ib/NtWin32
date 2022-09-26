#include <NtWin32/Windows.h>

int main() {
    SetLastError(123);
    DWORD error = GetLastError();
}