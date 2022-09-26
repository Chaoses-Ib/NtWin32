#pragma once
#include "minwindef.h"

#pragma push_macro("DECLSPEC_IMPORT")
#pragma push_macro("NTSYSAPI")
#pragma push_macro("NTSYSCALLAPI")

#undef DECLSPEC_IMPORT
#undef NTSYSAPI
#undef NTSYSCALLAPI

#define DECLSPEC_IMPORT
#define NTSYSAPI __declspec(dllimport)
#define NTSYSCALLAPI NTSYSAPI

#pragma warning(push)
#pragma warning(disable:4005)
#include <phnt_windows.h>
#pragma warning(pop)

#pragma pop_macro("NTSYSCALLAPI")
#pragma pop_macro("NTSYSAPI")
#pragma pop_macro("DECLSPEC_IMPORT")