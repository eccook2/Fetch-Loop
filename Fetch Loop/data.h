// Copyright 2021 Ethan Cook
// Under the MIT License
//
// data.h
//	Header file for data.cpp.
// 
// Created by: Ethan Cook, 8.12.2021

#ifndef DATA_H
#define DATA_H

#define GB 1073741824.0;

// Stores the system stats for the device.
struct Sys_Stats {
	TCHAR device_name[50];
	char os[50];
	char cpu_name[50];
	char gpu_name[50];

	int uptime_min;
	double mem_used;
	double mem_total;
	float cpu_load;
	int gpu_used;
	int cpu_temp;
	int gpu_temp;
	int hd1_temp;
	int hd2_temp;
};

// Sets the used physical memory (RAM) of the system (in gigabytes)
// Returns 0 on success, -1 on failure.
int set_mem_used(Sys_Stats* sys);

// Sets the total physical memory (RAM) of the system (in gigabytes)
// Returns 0 on success, -1 on failure.
int set_mem_total(Sys_Stats* sys);

// Calculates the cpu load given idle and total ticks
static float cpu_load_calc(unsigned long long idleTicks, unsigned long long totalTicks);

// Convert FILETIME to int
static unsigned long long FileTimeToInt64(const FILETIME& ft);

// Sets the cpu_load member to a float value from 0.0 - 1.0, readable as a percentage.
// Needs to be called multiple times because it measures load between calls.
void set_cpu_load(Sys_Stats* sys);

// Calls all setter methods to update all the members of the given Sys_Stats struct
// Handles any errors that occur
void update_stats(Sys_Stats* sys);

#endif