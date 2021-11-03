#ifndef _MAIN_ARGUMENT_H_
#define _MAIN_ARGUMENT_H_

#ifdef __cplusplus
#include <iostream>
#include <unistd.h>
#include <cstring>
#endif

#define MAX_FILENAME_BUFFER_SIZE	256
#define MAX_MODENAME_BUFFER_SIZE    10

#define SIMULATION_MODE "sim_mode"
#define REALTIME_MODE "rt_mode"

#define PARSING_FAIL 0
#define PARSING_SUCCESS 1

typedef struct MainArgumentStruct
{
    char execution_mode[MAX_MODENAME_BUFFER_SIZE];
    
    // Simulation mode
    char sim_input_file_name[MAX_FILENAME_BUFFER_SIZE];
    char sim_result_file_name[MAX_FILENAME_BUFFER_SIZE];
    int initial_scan_num;
    int final_scan_num;

    // h5write logging mode
    char h5write_mode_daq_result_file_name[MAX_FILENAME_BUFFER_SIZE];
    char h5write_mode_rsp_result_file_name[MAX_FILENAME_BUFFER_SIZE];
    int h5write_mode_num_of_scan;

    // daq period control
    int num_of_daq_skip;
} MainArgument;

int InitMainArgument(int argc, char *argv[], MainArgument* main_argument);

#endif