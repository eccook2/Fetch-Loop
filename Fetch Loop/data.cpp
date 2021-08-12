// Copyright 2021 Ethan Cook
// Under the MIT License
//
// data.c
//	Containes functions to set all members of the Sys_Stats struct
// 
// Created by: Ethan Cook, 8.12.2021

#include <string.h>
#include <windows.h>
#include "data.h"

#define GB 1073741824.0;

/////////
// Below are setter methods to update each member of the Sys_Stats struct
// 
// Functions
//	TODO set_device_name
//	TODO set_os
//	TODO set_cpu_name
//	TODO set_gpu_name
//	TODO set_uptime
//	DONE set_mem_used
//	DONE set_mem_total
//	DONE set_cpu_load
//	TODO set_gpu_load
//	TODO set_cpu_temp
//	TODO set_gpu_temp
//	TODO set_hd_temp
//  WIP  update_stats  // calls all setter methods and checks for errors
/////////

// Sets the uptime members (days, hours, minutes)
// No return value because GetTickCount64() doesn't return error values
void set_uptime(Sys_Stats* sys) {
	int uptime_ms = (int)GetTickCount64();

	sys->uptime_dys = uptime_ms / (1000 * 60 * 60 * 24);
	uptime_ms -= sys->uptime_dys * 86400000;

	sys->uptime_hrs = uptime_ms / (1000 * 60 * 60);
	uptime_ms -= sys->uptime_hrs * 3600000;

	sys->uptime_min = uptime_ms / (1000 * 60);
}

// Set device name by accessing sysinfoapi.h
// Currently broken. Trouble using TCHARs etc.
// Likely would cause even bigger problems when trying to port to linux.
// Need to find another way to get the device name.
int set_device_name(Sys_Stats* sys) {
	TCHAR buffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD sz = sizeof(buffer) / sizeof(TCHAR);
	int name = 4;

	if (GetComputerNameEx((COMPUTER_NAME_FORMAT)name, buffer, &sz) == 0) {
		return -1;
	}

	// sys->device_name = (TEXT)buffer;
	return 0;
}

// Sets the used physical memory (RAM) of the system (in gigabytes)
// Returns 0 on success, -1 on failure.
int set_mem_used(Sys_Stats* sys) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&meminfo) == 0) {
		return -1;
	}

	sys->mem_used = (meminfo.ullTotalPhys - meminfo.ullAvailPhys) / GB;
	return 0;
}

// Sets the total physical memory (RAM) of the system (in gigabytes)
// Returns 0 on success, -1 on failure.
int set_mem_total(Sys_Stats* sys) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&meminfo) == 0) {
		return -1;
	}

	sys->mem_total = meminfo.ullTotalPhys / GB;
	return 0;
}

// Calculates the cpu load given idle and total ticks
static float cpu_load_calc(unsigned long long idleTicks, unsigned long long totalTicks) {
	static unsigned long long prevTotalTicks = 0;
	static unsigned long long prevIdleTicks = 0;

	unsigned long long newTotalTicks = totalTicks - prevTotalTicks;
	unsigned long long newIdleTicks = idleTicks - prevIdleTicks;

	float usage = 1.0f - ((newTotalTicks > 0) ? ((float)newIdleTicks) / newTotalTicks : 0);

	prevTotalTicks = totalTicks;
	prevIdleTicks = idleTicks;
	return usage;
}

// Convert FILETIME to int
static unsigned long long FileTimeToInt64(const FILETIME& ft) {
	return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

// Sets the cpu_load member to a float value from 0.0 - 1.0, readable as a percentage.
// Needs to be called multiple times because it measures load between calls.
void set_cpu_load(Sys_Stats* sys) {
	FILETIME idleTime, kernelTime, userTime;
	sys->cpu_load = GetSystemTimes(&idleTime, &kernelTime, &userTime) ? cpu_load_calc(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}

// Calls all setter methods to update all the members of the given Sys_Stats struct
// Handles any errors that occur
void update_stats(Sys_Stats* sys) {
	if (set_mem_used(sys) == -1) {
		// TODO handle error
	}

	if (set_mem_total(sys) == -1) {
		// TODO handle error
	}
	set_cpu_load(sys);
	if (sys->cpu_load == -1.0) {
		// TODO handle error
	}
	set_uptime(sys);
}
