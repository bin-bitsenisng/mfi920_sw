#include "hdf5_ctrl.h"
#include "rsp_main.h"

extern char SimResultFname[MAX_FILENAME_BUFFER_SIZE];
extern char LoggingDataFname[MAX_FILENAME_BUFFER_SIZE];
extern char initScanString[MAX_FILENAME_BUFFER_SIZE];
extern char finScanString[MAX_FILENAME_BUFFER_SIZE];

void ReadInfoGroup(char* inputFileName)
{
	string GroupName;

	GroupName = "/DataInfo";
	//H5ToSym(GroupName, initScan);
	//H5ToSym(GroupName, finScan);
}


void ReadScanGroup(char* inputFileName, int32_t scan_idx)
{
	string GroupName;
	string FCWInfoGroup;
	string DataSet;

	GroupName = "/SCAN_";
	if (scan_idx < 10)
	{
		GroupName.append("0000");
	}
	else if (scan_idx < 100)
	{
		GroupName.append("000");
	}
	else if (scan_idx < 1000)
	{
		GroupName.append("00");
	}
	else if (scan_idx < 10000)
	{
		GroupName.append("0");
	}
	GroupName.append(to_string(scan_idx));

	H5ToArraySym(inputFileName, GroupName, Sim_LR_TimeData);
	H5ToArraySym(inputFileName, GroupName, Sim_MR_TimeData);
	H5ToArraySym(inputFileName, GroupName, Sim_SR_TimeData);
	H5ToArraySym(inputFileName, GroupName, Sim_RM_TimeData);

	//H5ToSym(inputFileName, GroupName, Sim_CycleTime);
	/*H5ToArraySym(inputFileName, GroupName, Sim_TimeData);*/
	
	//H5ToSym(GroupName, Sim_SampleNumber);
	//H5ToSym(GroupName, Sim_RadarScanIdx);

	//H5ToSym(GroupName, Sim_PeakCnt);
	//H5ToArraySym(GroupName, Sim_PeakData);

}


void StoreInfoGroup(char* outputFileName, uint32_t initScan, uint32_t finScan)
{
	string GroupName;

	GroupName = "/DataInfo";
	CreateHDF5Group(outputFileName, GroupName.c_str());
	SymToH5(outputFileName, GroupName, initScan);
	SymToH5(outputFileName, GroupName, finScan);
}


void StoreScanGroup(char* outputFileName, int32_t scan_idx)
{
	string GroupName;

	GroupName = "/SCAN_";
	if (scan_idx < 10)
	{
		GroupName.append("0000");
	}
	else if (scan_idx < 100)
	{
		GroupName.append("000");
	}
	else if (scan_idx < 1000)
	{
		GroupName.append("00");
	}
	else if (scan_idx < 10000)
	{
		GroupName.append("0");
	}
	GroupName.append(to_string(scan_idx));

	CreateHDF5Group(outputFileName, GroupName.c_str());
/*
	SymToH5(outputFileName, GroupName, Sim_CycleTime);
	SymToH5(outputFileName, GroupName, Sim_CurrentPRF);
	SymToH5(outputFileName, GroupName, Sim_RadarScanIdx);
	SymToH5(outputFileName, GroupName, Sim_SampleNumber);

	ArraySymToH5(outputFileName, GroupName, Sim_PowSpectrum);
	SymToH5(outputFileName, GroupName, Sim_BaseTh);
	ArraySymToH5(outputFileName, GroupName, Sim_RangeCfarTh);
	ArraySymToH5(outputFileName, GroupName, Sim_DoppCfarTh);
	ArraySymToH5(outputFileName, GroupName, Sim_RangeCfarOut);
	ArraySymToH5(outputFileName, GroupName, Sim_DoppCfarOut);

	SymToH5(outputFileName, GroupName, Sim_PeakCnt);
	ArraySymToH5(outputFileName, GroupName, Sim_PeakData);
	ArraySymToH5(outputFileName, GroupName, Sim_AngleTable);
	ArraySymToH5(outputFileName, GroupName, Sim_APS);

	SymToH5(outputFileName, GroupName, Sim_OutObjCnt);
	SymToH5(outputFileName, GroupName, Sim_OutFilObjCnt);
	ArraySymToH5(outputFileName, GroupName, Sim_ObjInfo);
	ArraySymToH5(outputFileName, GroupName, Sim_FilObjInfo);
	ArraySymToH5(outputFileName, GroupName, Sim_TrkInfo);

	ArraySymToH5(outputFileName, GroupName, Sim_2DfftReal);
	ArraySymToH5(outputFileName, GroupName, Sim_2DfftImag);*/
}

void StoreDAQGroup(char* outputFileName, int32_t scan_idx)
{
	string GroupName;

	GroupName = "/SCAN_";
	if (scan_idx < 10)
	{
		GroupName.append("0000");
	}
	else if (scan_idx < 100)
	{
		GroupName.append("000");
	}
	else if (scan_idx < 1000)
	{
		GroupName.append("00");
	}
	else if (scan_idx < 10000)
	{
		GroupName.append("0");
	}
	GroupName.append(to_string(scan_idx));

	CreateHDF5Group(outputFileName, GroupName.c_str());
/*
	ArraySymToH5(outputFileName, GroupName, Sim_TimeData);*/
}

void StoreRSPGroup(char* outputFileName, int32_t scan_idx)
{
	string GroupName;

	GroupName = "/SCAN_";
	if (scan_idx < 10)
	{
		GroupName.append("0000");
	}
	else if (scan_idx < 100)
	{
		GroupName.append("000");
	}
	else if (scan_idx < 1000)
	{
		GroupName.append("00");
	}
	else if (scan_idx < 10000)
	{
		GroupName.append("0");
	}
	GroupName.append(to_string(scan_idx));

	CreateHDF5Group(outputFileName, GroupName.c_str());
/*
	SymToH5(outputFileName, GroupName, Sim_CycleTime);
	SymToH5(outputFileName, GroupName, Sim_CurrentPRF);
	SymToH5(outputFileName, GroupName, Sim_RadarScanIdx);
	SymToH5(outputFileName, GroupName, Sim_SampleNumber);

	ArraySymToH5(outputFileName, GroupName, Sim_PowSpectrum);
	SymToH5(outputFileName, GroupName, Sim_BaseTh);
	ArraySymToH5(outputFileName, GroupName, Sim_RangeCfarTh);
	ArraySymToH5(outputFileName, GroupName, Sim_DoppCfarTh);
	ArraySymToH5(outputFileName, GroupName, Sim_RangeCfarOut);
	ArraySymToH5(outputFileName, GroupName, Sim_DoppCfarOut);

	SymToH5(outputFileName, GroupName, Sim_PeakCnt);
	ArraySymToH5(outputFileName, GroupName, Sim_PeakData);
	ArraySymToH5(outputFileName, GroupName, Sim_AngleTable);
	ArraySymToH5(outputFileName, GroupName, Sim_APS);

	SymToH5(outputFileName, GroupName, Sim_OutObjCnt);
	SymToH5(outputFileName, GroupName, Sim_OutFilObjCnt);
	ArraySymToH5(outputFileName, GroupName, Sim_ObjInfo);
	ArraySymToH5(outputFileName, GroupName, Sim_FilObjInfo);
	ArraySymToH5(outputFileName, GroupName, Sim_TrkInfo);*/
}

void ReadVarTypeDim(std::string *var_type, hsize_t* dims)
{
	size_t begin_idx, end_idx, temp_strlen;
	string temp_type = (*var_type);
	string result_type;
	string temp_length;


	begin_idx = temp_type.find_first_of("[");
	end_idx = temp_type.find_first_of("]");

	if (begin_idx != -1)
	{
		result_type = temp_type.substr(0, begin_idx - 1);
		temp_strlen = end_idx - begin_idx + 1;
		temp_length = temp_type.substr(begin_idx + 1, temp_strlen - 2);
		dims[0] = stoll(temp_length);

		if (temp_type.length() != end_idx + 1)
		{
			temp_type.erase(begin_idx, temp_strlen);
			end_idx = temp_type.find_first_of("]");
			temp_strlen = end_idx - begin_idx + 1;
			temp_length = temp_type.substr(begin_idx + 1, temp_strlen - 2);
			dims[1] = stoll(temp_length);
		}
		else
		{
			dims[1] = 1;
		}
	}
	else
	{
		result_type = temp_type;
		temp_strlen = 0;
		dims[0] = 1;
		dims[1] = 1;
	}

	(*var_type) = result_type;
}



void CreateHDF5File(char* outputFileName)
{
	hid_t file_id;

	/* Create a new file using default properties. */
	file_id = H5Fcreate(outputFileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	/* Close the file. */
	H5Fclose(file_id);

}



void CreateHDF5Group(char* outputFileName, const char *group_name)
{
	hid_t file_id, group_id;  /* identifiers */
	herr_t status;

	/* Open an existing file. */
	file_id = H5Fopen(outputFileName, H5F_ACC_RDWR, H5P_DEFAULT);

	/* Create group in the root group using absolute name. */
	group_id = H5Gcreate2(file_id, group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	/* Close groups. */
	status = H5Gclose(group_id);
}



void HDF5_ReadData(char* inputFileName, const char *group_name, const char *var_name, void *Data)
{
	hid_t file_id, group_id, dataset_id, dataspace_id;  /* identifiers */
	hid_t filespace;
	hid_t Dtype, Dtype_mem;
	hsize_t dims[2];
	herr_t status;
	int ndims;


	/* Open the file and the dataset. */
	file_id = H5Fopen(inputFileName, H5F_ACC_RDONLY, H5P_DEFAULT);		// Read Only
	group_id = H5Gopen2(file_id, group_name, H5P_DEFAULT);
	dataset_id = H5Dopen2(group_id, var_name, H5P_DEFAULT);

	filespace = H5Dget_space(dataset_id);    /* Get filespace handle first. */
	ndims = H5Sget_simple_extent_dims(filespace, dims, NULL);

	/* Define the memory space to read dataset. */
	dataspace_id = H5Screate_simple(ndims, dims, NULL);

	Dtype = H5Dget_type(dataset_id);
	Dtype_mem = H5Tget_native_type(Dtype, H5T_DIR_DEFAULT);

	status = H5Dread(dataset_id, Dtype_mem, dataspace_id, filespace, H5P_DEFAULT, Data);

	H5Tclose(Dtype_mem);
	H5Tclose(Dtype);

	H5Sclose(dataspace_id);
	H5Dclose(dataset_id);
	H5Gclose(group_id);
	H5Fclose(file_id);
}



void HDF5_WriteArrayData(char* outputFileName, const char *group_name, const char *var_name, const char *var_type, hsize_t* dims, void *Data)
{

	hid_t file_id, group_id, dataset_id, dataspace_id;  /* identifiers */
	herr_t status;

	char *pBufferChar = (char*)Data;
	signed char *pBufferSChar = (signed char*)Data;
	unsigned char *pBufferUChar = (unsigned char*)Data;
	short *pBufferShort = (short*)Data;
	unsigned short *pBufferUShort = (unsigned short*)Data;
	int *pBufferInt = (int*)Data;
	long *pBufferLong = (long*)Data;
	unsigned long *pBufferULong = (unsigned long*)Data;
	long long *pBufferLLong = (long long*)Data;
	unsigned long long *pBufferULLong = (unsigned long long*)Data;
	float *pBufferFloat = (float*)Data;
	double *pBufferDouble = (double*)Data;

	/* Open an existing file. */
	file_id = H5Fopen(outputFileName, H5F_ACC_RDWR, H5P_DEFAULT);

	if (dims[1] == 1)
	{
		dataspace_id = H5Screate_simple(1, dims, NULL);
	}
	else
	{
		dataspace_id = H5Screate_simple(2, dims, NULL);
	}
	

	/* Open an existing group of the specified file. */
	group_id = H5Gopen2(file_id, group_name, H5P_DEFAULT);



	/* Create the dataset in group. */
	/* Write the dataset. */
	if (!strcmp(var_type, "char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferChar);
	}
	else if (!strcmp(var_type, "signed char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_SCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferSChar);
	}
	else if (!strcmp(var_type, "unsigned char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferUChar);
	}
	else if (!strcmp(var_type, "short"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I16LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_SHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferShort);
	}
	else if (!strcmp(var_type, "unsigned short"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U16LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_USHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferUShort);
	}
	else if (!strcmp(var_type, "int"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferInt);
	}
	else if (!strcmp(var_type, "unsigned int"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_UINT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferInt);
	}
	else if (!strcmp(var_type, "long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLong);
	}
	else if (!strcmp(var_type, "unsigned long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_ULONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferULong);
	}
	else if (!strcmp(var_type, "long long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_LLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLLong);
	}
	else if (!strcmp(var_type, "unsigned long long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_ULLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferULLong);
	}
	else if (!strcmp(var_type, "float"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_IEEE_F32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferFloat);
	}
	else if (!strcmp(var_type, "double"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_IEEE_F64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferDouble);
	}
	else
	{
	}


	/* Close the data space */
	status = H5Sclose(dataspace_id);

	/* Close the dataset */
	status = H5Dclose(dataset_id);

	/* Close the group. */
	status = H5Gclose(group_id);

	/* Close the file. */
	status = H5Fclose(file_id);
}



void HDF5_WriteData(char* outputFileName, const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data)
{

	hid_t file_id, group_id, dataset_id, dataspace_id;  /* identifiers */
	herr_t status;

	char *pBufferChar = (char*)Data;
	signed char *pBufferSChar = (signed char*)Data;
	unsigned char *pBufferUChar = (unsigned char*)Data;
	short *pBufferShort = (short*)Data;
	unsigned short *pBufferUShort = (unsigned short*)Data;
	long *pBufferLong = (long*)Data;
	unsigned long *pBufferULong = (unsigned long*)Data;
	long long *pBufferLLong = (long long*)Data;
	unsigned long long *pBufferULLong = (unsigned long long*)Data;
	float *pBufferFloat = (float*)Data;
	double *pBufferDouble = (double*)Data;

	/* Open an existing file. */
	file_id = H5Fopen(outputFileName, H5F_ACC_RDWR, H5P_DEFAULT);

	dataspace_id = H5Screate_simple(1, dim, NULL);

	/* Open an existing group of the specified file. */
	group_id = H5Gopen2(file_id, group_name, H5P_DEFAULT);



	/* Create the dataset in group. */
	/* Write the dataset. */
	if (!strcmp(var_type, "char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_CHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferChar);
	}
	else if (!strcmp(var_type, "signed char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_SCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferSChar);
	}
	else if (!strcmp(var_type, "unsigned char"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U8LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_UCHAR, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferUChar);
	}
	else if (!strcmp(var_type, "short"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I16LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_SHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferShort);
	}
	else if (!strcmp(var_type, "unsigned short"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U16LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_USHORT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferUShort);
	}
	else if (!strcmp(var_type, "int"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLong);
	}
	else if (!strcmp(var_type, "unsigned int"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_UINT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLong);
	}
	else if (!strcmp(var_type, "long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_LONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLong);
	}
	else if (!strcmp(var_type, "unsigned long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_ULONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferULong);
	}
	else if (!strcmp(var_type, "long long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_I64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_LLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferLLong);
	}
	else if (!strcmp(var_type, "unsigned long long"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_STD_U64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_ULLONG, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferULLong);
	}
	else if (!strcmp(var_type, "float"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_IEEE_F32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferFloat);
	}
	else if (!strcmp(var_type, "double"))
	{
		dataset_id = H5Dcreate2(group_id, var_name, H5T_IEEE_F64LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, pBufferDouble);
	}
	else
	{
		std::cout << "var_type has probelm." << std::endl;
		std::cout << "var_type: " << var_type << std::endl;
	}


	/* Close the data space */
	status = H5Sclose(dataspace_id);

	/* Close the dataset */
	status = H5Dclose(dataset_id);

	/* Close the group. */
	status = H5Gclose(group_id);

	/* Close the file. */
	status = H5Fclose(file_id);

}



void ReadSimInfoINI(char* IniFname, MainArgument* main_argument)
{	
	mINI::INIFile inifile(IniFname);
	mINI::INIStructure ini;
	inifile.read(ini);

	strcpy(main_argument->sim_result_file_name, ini.get("FileInfo").get("SimResultFname").c_str()); 
	strcpy(main_argument->sim_input_file_name, ini.get("DataInfo").get("LoggingDataFname").c_str());
	main_argument->initial_scan_num = atoi(ini.get("SimInfo").get("InitialScan").c_str());
	main_argument->final_scan_num = atoi(ini.get("SimInfo").get("FinalScan").c_str());
}


