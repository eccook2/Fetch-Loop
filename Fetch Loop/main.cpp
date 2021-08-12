// Copyright 2021 Ethan Cook
// Under the MIT License
//
// main.c
//	Main file for the program. Mostly makes calls to functions defined elsewhere.
// 
// Created by: Ethan Cook, 8.10.2021

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "data.h"

// Signal Handler for SIGINT
void sigint_handler(int sig_num) {
	printf("\nExiting... \n");
	
	exit(0);
}

// TODO Setup error handling
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
		printf("System Uptime: %d:%d:%d\n", sys.uptime_dys, sys.uptime_hrs, sys.uptime_min);
		printf("Memory Used: %f of %f GB  CPU Load: %f%%\n", sys.mem_used, sys.mem_total, sys.cpu_load * 100);
		Sleep(2000);
		system("@cls||clear");
	}
}
