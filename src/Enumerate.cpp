#include <Windows.h>
#include <string>
#include <iostream>
#include "Structures.h"
#include "xorstr.hpp" // String security

std::wstring UniToString(const UNICODE_STRING& us) {
    return std::wstring(us.Buffer, us.Length / sizeof(WCHAR));
}

int main() {

    // Load NTDLL dynamically & get addr of NtQuerySystemInformation
    HMODULE ntdll = LoadLibraryW(xorstr_(L"ntdll.dll"));
    NtQuerySystemInformation_t NtQuerySystemInformation = (NtQuerySystemInformation_t)GetProcAddress(ntdll, xorstr_("NtQuerySystemInformation"));

    ULONG bufferSize = 0x10000; // 64kb
    PVOID buffer = malloc(bufferSize);

    NTSTATUS status;
    ULONG returnLength = 0;

    // Buffer fit-check, resize
    while ((status = NtQuerySystemInformation(SystemProcessInformation, buffer, bufferSize, &returnLength)) == STATUS_INFO_LENGTH_MISMATCH) {
        bufferSize *= 2;
        buffer = realloc(buffer, bufferSize);
    }

    // Parse & print output
    SYSTEM_PROCESS_INFORMATION_t processInfo = (SYSTEM_PROCESS_INFORMATION_t)buffer;
    do {
        std::wstring processName = processInfo->ImageName.Length ? UniToString(processInfo->ImageName) : xorstr_(L"System Idle Process");
        ULONG parentPID = (ULONG)(ULONG_PTR)processInfo->InheritedFromUniqueProcessId;
        std::wcout
            << xorstr_(L"Process Name: ")
            << processName
            << xorstr_(L" | Process ID: ")
            << std::dec << static_cast<ULONG>(reinterpret_cast<ULONG_PTR>(processInfo->UniqueProcessId))
            << xorstr_(L" | Parent Process: ")
            << parentPID
            << std::endl;
        if (processInfo->nextoff == 0) break;
        processInfo = (SYSTEM_PROCESS_INFORMATION_t)((BYTE*)processInfo + processInfo->nextoff);
    } while (true);

    free(buffer);
    FreeLibrary(ntdll);
    return 0;

}
