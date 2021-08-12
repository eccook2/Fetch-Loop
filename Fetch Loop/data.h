// Copyright 2021 Ethan Cook
// Under the MIT License
//
// data.h
//	Header file for data.cpp.
// 
// Created by: Ethan Cook, 8.12.2021

#ifndef DATA_H
#define DATA_H

// Stores the system stats for the device.
struct Sys_Stats {
	TCHAR device_name[50];
	char os[50];
	char cpu_name[50];
	char gpu_name[50];

	int uptime_dys;
	int uptime_hrs;
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

// Calls all setter methods to update all the members of the given Sys_Stats struct
// Handles any errors that occur
void update_stats(Sys_Stats* sys);

#endif