#include <Windows.h>
#include <psapi.h>
#include <memory.h>
#include <stdio.h>

int
main() {
    PROCESS_MEMORY_COUNTERS pmc = {};

    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    printf("WS: %d\tPeak WS: %d\tCommit: %d\tPeak commit: %d\n", pmc.WorkingSetSize, pmc.PeakWorkingSetSize, pmc.PagefileUsage, pmc.PeakPagefileUsage);

    auto mem = malloc(1024 * 1024 * 1024);
    printf("malloc(1Gb) - %s\n", (mem != nullptr) ? "check" : "uncheck");

    ZeroMemory(&pmc, sizeof(pmc));
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    printf("WS: %d\tPeak WS: %d\tCommit: %d\tPeak commit: %d\n", pmc.WorkingSetSize, pmc.PeakWorkingSetSize, pmc.PagefileUsage, pmc.PeakPagefileUsage);

    if (mem != nullptr) {
        free(mem);
        mem = nullptr;
        printf("Fre-e-e-e-e-edom\n");

        ZeroMemory(&pmc, sizeof(pmc));
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        printf("WS: %d\tPeak WS: %d\tCommit: %d\tPeak commit: %d\n", pmc.WorkingSetSize, pmc.PeakWorkingSetSize, pmc.PagefileUsage, pmc.PeakPagefileUsage);
    }
}