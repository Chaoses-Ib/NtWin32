# Documentation
`__imp_Function` with a static library cannot be linked correctly, workarounds:
- ```c
  #include <winnt.h>  // defines NTSYSAPI and NTSYSCALLAPI anyway
  #define DECLSPEC_IMPORT
  #define NTSYSAPI __declspec(dllimport)
  #define NTSYSCALLAPI NTSYSAPI
  #include <Windows.h>
  ```
- `#define dllimport`  
  Because `Windows.h` includes `winnt.h` which declares some functions of Ntdll.dll, if we want to keep `__declspec(import)` for Ntdll functions [for performance](https://github.com/Chaoses-Ib/Cpp/blob/main/Build/Compiling/Dynamic%20Linking.md#msvc-__declspecdllimport), we cannot directly include `Windows.h` and `ntdll.h` in the same source file. One solution is to include `winnt.h` first by ourselves. However, there is still one problem: `ntdll.h` (Ntdll.dll) and `sysinfoapi.h` (Kernel32.dll) both declare `VerSetConditionMask()`.
- Declare every API without `__declspec(dllimport)`  
  Example: [DetoursNT](https://github.com/wbenny/DetoursNT)