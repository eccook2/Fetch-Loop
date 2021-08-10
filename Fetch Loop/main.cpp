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

// Stores the system stats for the device.
struct Sys_Stats {
	char device_name[50];
	char os[50];
	char cpu_name[50];
	char gpu_name[50];

	int uptime_min;
	int mem_used;
	int mem_total;
	int cpu_used;
	int gpu_used;
	int cpu_temp;
	int gpu_temp;
	int hd1_temp;
	int hd2_temp;
};

// TODO Setup error handling

// TODO Create helper functions to update each struct member

// TODO Create functions to display the stats on the command line

int main()
{
	
}
