#pragma once
#include <Windows.h>

typedef struct _UNICODE_STRING {
    USHORT  Length;
    USHORT  MaximumLength;
    PWSTR   Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG               nextoff;
    ULONG               NumberOfThreads;
    LARGE_INTEGER       WorkingSetPrivateSize;
    ULONG               HardFaultCount;
    ULONG               NumberOfThreadsHighWatermark;
    ULONGLONG           CycleTime;
    LARGE_INTEGER       CreateTime;
    LARGE_INTEGER       UserTime;
    LARGE_INTEGER       KernelTime;
    UNICODE_STRING      ImageName;
    LONG                BasePriority;
    PVOID               UniqueProcessId;
    PVOID               InheritedFromUniqueProcessId;
    ULONG               HandleCount;
    ULONG               SessionId;
    ULONG_PTR           UniqueProcessKey;
    ULONG_PTR           PeakVirtualSize;
    ULONG_PTR           VirtualSize;
    ULONG               PageFaultCount;
    ULONG_PTR           PeakWorkingSetSize;
    ULONG_PTR           WorkingSetSize;
    ULONG_PTR           QuotaPeakPagedPoolUsage;
    ULONG_PTR           QuotaPagedPoolUsage;
    ULONG_PTR           QuotaPeakNonPagedPoolUsage;
    ULONG_PTR           QuotaNonPagedPoolUsage;
    ULONG_PTR           PagefileUsage;
    ULONG_PTR           PeakPagefileUsage;
    ULONG_PTR           PrivatePageCount;
    LARGE_INTEGER       ReadOperationCount;
    LARGE_INTEGER       WriteOperationCount;
    LARGE_INTEGER       OtherOperationCount;
    LARGE_INTEGER       ReadTransferCount;
    LARGE_INTEGER       WriteTransferCount;
    LARGE_INTEGER       OtherTransferCount;
} SYSTEM_PROCESS_INFORMATION, * SYSTEM_PROCESS_INFORMATION_t;

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation        = 0,
    SystemProcessorInformation    = 1,
    SystemPerformanceInformation  = 2,
    SystemTimeOfDayInformation    = 3,
    SystemProcessInformation      = 5
} SYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* NtQuerySystemInformation_t)
(
    SYSTEM_INFORMATION_CLASS    SystemInformationClass,
    PVOID                       SystemInformation,
    ULONG                       SystemInformationLength,
    PULONG                      ReturnLength
);


#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)