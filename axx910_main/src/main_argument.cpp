#include "main_argument.h"
#include "main_cfg.h"
#include "logging/hdf5_ctrl.h"

static int ParseMainArg(int argc, char *argv[], MainArgument* main_argument);
static void ShowUsage(std::string name);

int InitMainArgument(int argc, char *argv[], MainArgument* main_argument)
{
	if(ParseMainArg(argc, argv, main_argument) == PARSING_FAIL)
		return PARSING_FAIL;
	else
	{
		if(!strcmp(main_argument->execution_mode, SIMULATION_MODE))
		{
			ReadSimInfoINI(SIMULATION_FILE_INFO_INI_FILE, main_argument);

			ReadInfoGroup(main_argument->sim_input_file_name);
			//CreateHDF5File(main_argument->sim_result_file_name);
			//StoreInfoGroup(main_argument->sim_result_file_name, main_argument->initial_scan_num, main_argument->final_scan_num);
		}
		else if(main_argument->h5write_mode_num_of_scan != 0)
		{
            strcpy(main_argument->h5write_mode_daq_result_file_name, H5WRITE_MODE_DAQ_RESULT_FILE);
            strcpy(main_argument->h5write_mode_rsp_result_file_name, H5WRITE_MODE_RSP_RESULT_FILE);

			CreateHDF5File(main_argument->h5write_mode_daq_result_file_name);
			StoreInfoGroup(main_argument->h5write_mode_daq_result_file_name, 1, main_argument->h5write_mode_num_of_scan);
			CreateHDF5File(main_argument->h5write_mode_rsp_result_file_name);
			StoreInfoGroup(main_argument->h5write_mode_rsp_result_file_name, 1, main_argument->h5write_mode_num_of_scan);
		}

        return PARSING_SUCCESS;
    }
}

static int ParseMainArg(int argc, char *argv[], MainArgument* main_argument)
{
	if (argc < NUM_OF_ARGC)
	{
		ShowUsage(argv[0]);
		return PARSING_FAIL;
	}

    for (int i = 1; i < argc; ++i)
	{
        std::string arg = argv[i];
        if (arg == "--help")
		{
            ShowUsage(argv[0]);
            return PARSING_FAIL;
        }
		else if ((arg == "-m") || (arg == "--mode"))
		{
            if (i + 1 < argc)
			{
				strcpy(main_argument->execution_mode, argv[++i]);
            }
			else
			{ 
				std::cerr << "-m, --mode option requires one argument." << std::endl;
                return PARSING_FAIL;
            }
        } 
		else if((arg == "-h") || (arg == "--h5write"))
		{
            if (i + 1 < argc)
			{
				main_argument->h5write_mode_num_of_scan = atoi(argv[++i]);
            } else {
				std::cerr << "-h, --h5write option requires one argument." << std::endl;
                return PARSING_FAIL;
            }
		}
		else if((arg == "-d") || (arg == "--num_daq_skip"))
		{
            if (i + 1 < argc)
			{
                main_argument->num_of_daq_skip = atoi(argv[++i]);
            } else {
				std::cerr << "-d, --num_daq_skip option requires one argument." << std::endl;
                return PARSING_FAIL;
            }
		}
		else
		{
			
			printf("1 argc: %d\n", argc);
			ShowUsage(argv[0]);
			return PARSING_FAIL;
		}
    }

	if((strcmp(main_argument->execution_mode, SIMULATION_MODE) && strcmp(main_argument->execution_mode, REALTIME_MODE)))
	{				
		ShowUsage(argv[0]);
		return PARSING_FAIL;
	}
	else
	{
		return PARSING_SUCCESS;
	}
}

static void ShowUsage(std::string name)
{
	std::cerr << "Usage: " << name << " <option(s)>\n"
		 << "\tOptions:\n"
         << "\t--help\tShow this help message\n"
         << "\t-m, --mode\tSpecify the mode [sim_mode/rt_mode]\n"
		 << "\t-h, --h5write\tSpecify the h5 file write the number of samples\n"
		 << "\t-d, --num_daq_scan\tSpecify the number of skipped daq\n"
		 << "\n\tExample: " << name << " -m rt_mode -h 0 -d 20\n"
         << std::endl;
}