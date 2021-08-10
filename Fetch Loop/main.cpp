// Copyright 2021 Ethan Cook
// Under the MIT License
//
// Written by members of the FOSS Club at UW-Madison
// 
// Contributors:
//		Ethan Cook [eccook2@wisc.edu]
// 
// main.c
// Created by: Ethan Cook, 8.10.2021

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

// Stores the system stats for the device.
struct Sys_Stats {
	char device_name[50];
	char os[50];
	char cpu_name[50];
	char gpu_name[50];

	int uptime_min;
	double mem_used;
	double mem_total;
	int cpu_used;
	int gpu_used;
	int cpu_temp;
	int gpu_temp;
	int hd1_temp;
	int hd2_temp;
};

// Signal Handler for SIGINT
void sigint_handler(int sig_num) {
	printf("\nExiting... \n");
	
	exit(0);
}

// TODO Setup error handling

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
//	TODO set_cpu_used
//	TODO set_gpu_used
//	TODO set_cpu_temp
//	TODO set_gpu_temp
//	TODO set_hd_temp
//  WIP  update_stats  // calls all setter methods and checks for errors
/////////

int set_os(Sys_Stats* sys) {
	#ifdef _WIN32
		#ifdef _WIN64
			strcpy(sys->os, "Windows 64 bit");
		#else
			strcpy(sys->os, "Windows 32 bit");
		#endif
	#endif


}

// Sets the used physical memory (RAM) of the system (in gigabytes)
// Returns 0 on success, -1 on failure.
int set_mem_used(Sys_Stats* sys) {
	MEMORYSTATUSEX meminfo;
	meminfo.dwLength = sizeof(MEMORYSTATUSEX);

	if (GlobalMemoryStatusEx(&meminfo) == 0) {
		return -1;
	}

	sys->mem_used = (meminfo.ullTotalPhys - meminfo.ullAvailPhys) / 1000000000.0;
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

	sys->mem_total = meminfo.ullTotalPhys / 1000000000.0;
	return 0;
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
}

// TODO Create functions to display the stats on the command line

int main()
{
	Sys_Stats sys = { NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	signal(SIGINT, sigint_handler);

	// Infinite loop;
	//	1. Update all struct members
	//	2. Print to command line TODO Pretty display functions will replace this
	//	3. Sleep for a bit
	//	4. Clear the Screen

	while (1) {
		update_stats(&sys);
		printf("Memory Used: %f of %f GB\n", sys.mem_used, sys.mem_total);
		Sleep(2000);
		system("@cls||clear");
	}
}
