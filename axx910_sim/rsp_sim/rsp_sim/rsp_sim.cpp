#include <chrono>	
#include <typeinfo>
#include "hdf5.h"
#include "stdafx.h"
using namespace std;

#include "rsp_sim.h"
#include "Sim_Main.h"


#define MAX_FILENAME_BUFFER_SIZE	256
#define ID_ReUse								1

hid_t gSrcFid, gDstFid;
uint32_t initScan, finScan;

char SimIniFname[MAX_FILENAME_BUFFER_SIZE];
char SimResultFname[MAX_FILENAME_BUFFER_SIZE];
char LoggingDataFname[MAX_FILENAME_BUFFER_SIZE];
char initScanString[MAX_FILENAME_BUFFER_SIZE];
char finScanString[MAX_FILENAME_BUFFER_SIZE];
char peakModeString[MAX_FILENAME_BUFFER_SIZE];


uint8_t image[1000000];
uint8_t webcam[10000000];

void ReadVarTypeDim(string *var_type, hsize_t* dims);
void HDF5_WriteArrayData(const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data);
void HDF5_WriteData(const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data);
void CreateHDF5File(void);
void CreateHDF5Group(const char *group_name);
void StoreInfoGroup(void);
void StoreScanGroup(int32_t scan_idx);

void ReadInfoGroup(void);
void ReadScanGroup(int32_t scan_idx);
void HDF5_ReadData(const char *group_name, const char *var_name, void *Data);

void ReadSimInfoINI(char* IniFname);


int main(int argc, char *argv[])
{
	uint32_t ScanIndexCurrent;
	chrono::system_clock::time_point total_time_start, total_time_end, time_start, time_end;

	if (argc != 2)
	{
		printf("%d is invalid argument count!\n", argc);
		printf("RADAR_Sim [configuration filename]\n");
		printf("ex : RADAR_Sim.exe SimFileInfo.ini\n");
	}

	// INI 파일이름을 copy 한다.
	strcpy_s(SimIniFname, MAX_FILENAME_BUFFER_SIZE, argv[1]);

	/* Read keys from resiminfo.ini file */
	ReadSimInfoINI(SimIniFname);

	initScan = atoi(initScanString);
	finScan = atoi(finScanString);

	peakMode = atoi(peakModeString);

	if (peakMode == 0)
		printf("==== Re Simulation Mode : Time Data ==== \n");
	else
		printf("==== Re Simulation Mode : Peak Data ==== \n");


	/* Preparing input	*/
	gSrcFid = H5Fopen(LoggingDataFname, H5F_ACC_RDONLY, H5P_DEFAULT);		// Read Only
	ReadInfoGroup();

	/* Preparing output	*/
	CreateHDF5File();
	StoreInfoGroup();
#ifdef CUDA_ACC
	printf("================ CUDA =================\n");
#else
	printf("================ CPU =================\n");
#endif

	for (ScanIndexCurrent = initScan; ScanIndexCurrent <= finScan; ScanIndexCurrent++)
	{
		printf("=============== Now Processing : %d Scan =============== \n", ScanIndexCurrent);

		/* Read data */
		time_start = chrono::system_clock::now();

		ReadScanGroup(ScanIndexCurrent);

		time_end = chrono::system_clock::now();
		printf("Elapsed time Data Read= %lld us\n", chrono::duration_cast<chrono::microseconds>(time_end - time_start).count());

		/* Initialize system */
		if (ScanIndexCurrent == initScan)
		{
			Sim_SysInit();
		}

		/* Process data */
		time_start = chrono::system_clock::now();

		Sim_RadarMain();

		time_end = chrono::system_clock::now();
		printf("Elapsed time RSP = %lld us\n", chrono::duration_cast<chrono::microseconds>(time_end - time_start).count());

		/* Write data */
		time_start = chrono::system_clock::now();

		StoreScanGroup(ScanIndexCurrent);

		time_end = chrono::system_clock::now();
		printf("Elapsed time  Data Store= %lld us\n", chrono::duration_cast<chrono::microseconds>(time_end - time_start).count());

	}

	time_start = chrono::system_clock::now();
	H5Fclose(gSrcFid);
	H5Fclose(gDstFid);

	time_end = chrono::system_clock::now();

	printf("Elapsed time  H5FClose %lld us\n", chrono::duration_cast<chrono::microseconds>(time_end - time_start).count());

}


void ReadInfoGroup(void)
{
	string GroupName;

	GroupName = "/DataInfo";
	//H5ToSym(GroupName, initScan);
	//H5ToSym(GroupName, finScan);
}


void ReadScanGroup(int32_t scan_idx)
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


	//H5ToSym(GroupName, Sim_CycleTime);

	/* Use time data	*/


	if (peakMode == 0)
	{
		H5ToArraySym(GroupName, Sim_RM_TimeData);
		H5ToArraySym(GroupName, Sim_LR_TimeData);
		H5ToArraySym(GroupName, Sim_MR_TimeData);
		H5ToArraySym(GroupName, Sim_SR_TimeData);
	}
	else
	{

		H5ToArraySym(GroupName, Sim_RM_PowSpectrum);
		H5ToArraySym(GroupName, Sim_LR_PowSpectrum);
		H5ToArraySym(GroupName, Sim_MR_PowSpectrum);
		H5ToArraySym(GroupName, Sim_SR_PowSpectrum);


		H5ToSym(GroupName, Sim_RM_PeakCnt);
		H5ToArraySym(GroupName, Sim_RM_PeakData);

		H5ToSym(GroupName, Sim_LR_PeakCnt);
		H5ToArraySym(GroupName, Sim_LR_PeakData);

		H5ToSym(GroupName, Sim_MR_PeakCnt);
		H5ToArraySym(GroupName, Sim_MR_PeakData);

		H5ToSym(GroupName, Sim_SR_PeakCnt);
		H5ToArraySym(GroupName, Sim_SR_PeakData);
	}

	H5ToArraySym(GroupName, image);
	H5ToArraySym(GroupName, AI);
	H5ToArraySym(GroupName, Can);
	H5ToArraySym(GroupName, Object);
	
	
#if (WEBCAM_OPTION == 1)
		H5ToArraySym(GroupName, webcam);
#endif
	
	

}


void StoreInfoGroup(void)
{
	string GroupName;

	GroupName = "/DataInfo";
	CreateHDF5Group(GroupName.c_str());
	SymToH5(GroupName, initScan);
	SymToH5(GroupName, finScan);

}


void StoreScanGroup(int32_t scan_idx)
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

	CreateHDF5Group(GroupName.c_str());

	SymToH5(GroupName, Sim_CycleTime);
	SymToH5(GroupName, Sim_CurrentPRF);
	SymToH5(GroupName, Sim_RadarScanIdx);
	SymToH5(GroupName, Sim_SampleNumber);

	if (peakMode == 0)
	{
		ArraySymToH5(GroupName, Sim_RM_TimeData);
		ArraySymToH5(GroupName, Sim_LR_TimeData);
		ArraySymToH5(GroupName, Sim_MR_TimeData);
		ArraySymToH5(GroupName, Sim_SR_TimeData);
	}

	ArraySymToH5(GroupName, Sim_RM_PowSpectrum);
	ArraySymToH5(GroupName, Sim_LR_PowSpectrum);
	ArraySymToH5(GroupName, Sim_MR_PowSpectrum);
	ArraySymToH5(GroupName, Sim_SR_PowSpectrum);

	ArraySymToH5(GroupName, Sim_RM_PowSpectrum_log);
	ArraySymToH5(GroupName, Sim_LR_PowSpectrum_log);
	ArraySymToH5(GroupName, Sim_MR_PowSpectrum_log);
	ArraySymToH5(GroupName, Sim_SR_PowSpectrum_log);

	ArraySymToH5(GroupName, Sim_RM_PowSpectrum_mask);
	ArraySymToH5(GroupName, Sim_LR_PowSpectrum_mask);
	ArraySymToH5(GroupName, Sim_MR_PowSpectrum_mask);
	ArraySymToH5(GroupName, Sim_SR_PowSpectrum_mask);

	SymToH5(GroupName, Sim_RM_BaseTh);
	ArraySymToH5(GroupName, Sim_RM_RangeCfarTh);
	ArraySymToH5(GroupName, Sim_RM_DoppCfarTh);
	ArraySymToH5(GroupName, Sim_RM_RangeCfarOut);
	ArraySymToH5(GroupName, Sim_RM_DoppCfarOut);

	SymToH5(GroupName, Sim_LR_BaseTh);
	ArraySymToH5(GroupName, Sim_LR_RangeCfarTh);
	ArraySymToH5(GroupName, Sim_LR_DoppCfarTh);
	ArraySymToH5(GroupName, Sim_LR_RangeCfarOut);
	ArraySymToH5(GroupName, Sim_LR_DoppCfarOut);

	SymToH5(GroupName, Sim_MR_BaseTh);
	ArraySymToH5(GroupName, Sim_MR_RangeCfarTh);
	ArraySymToH5(GroupName, Sim_MR_DoppCfarTh);
	ArraySymToH5(GroupName, Sim_MR_RangeCfarOut);
	ArraySymToH5(GroupName, Sim_MR_DoppCfarOut);

	SymToH5(GroupName, Sim_SR_BaseTh);
	ArraySymToH5(GroupName, Sim_SR_RangeCfarTh);
	ArraySymToH5(GroupName, Sim_SR_DoppCfarTh);
	ArraySymToH5(GroupName, Sim_SR_RangeCfarOut);
	ArraySymToH5(GroupName, Sim_SR_DoppCfarOut);

	SymToH5(GroupName, Sim_RM_PeakCnt);
	SymToH5(GroupName, Sim_LR_PeakCnt);
	SymToH5(GroupName, Sim_MR_PeakCnt);
	SymToH5(GroupName, Sim_SR_PeakCnt);

	ArraySymToH5(GroupName, Sim_RM_PeakData);
	ArraySymToH5(GroupName, Sim_LR_PeakData);
	ArraySymToH5(GroupName, Sim_MR_PeakData);
	ArraySymToH5(GroupName, Sim_SR_PeakData);


	ArraySymToH5(GroupName, Sim_RM_PeakInfo);
	ArraySymToH5(GroupName, Sim_LR_PeakInfo);
	ArraySymToH5(GroupName, Sim_MR_PeakInfo);
	ArraySymToH5(GroupName, Sim_SR_PeakInfo);


	ArraySymToH5(GroupName, Sim_LR_AziAngleTable);
	ArraySymToH5(GroupName, Sim_LR_EleAngleTable);
	ArraySymToH5(GroupName, Sim_LR_APS);

	ArraySymToH5(GroupName, Sim_MR_AziAngleTable);
	ArraySymToH5(GroupName, Sim_MR_EleAngleTable);
	ArraySymToH5(GroupName, Sim_MR_APS);

	ArraySymToH5(GroupName, Sim_SR_AziAngleTable);
	ArraySymToH5(GroupName, Sim_SR_EleAngleTable);
	ArraySymToH5(GroupName, Sim_SR_APS);


	ArraySymToH5(GroupName, Sim_RM_AziAngleTable);
	ArraySymToH5(GroupName, Sim_RM_APS);

	SymToH5(GroupName, Sim_OutObjCnt);
	SymToH5(GroupName, Sim_OutFilObjCnt);
	SymToH5(GroupName, Sim_REF_OutObjCnt);

	ArraySymToH5(GroupName, Sim_ObjInfo);
	ArraySymToH5(GroupName, Sim_REF_ObjInfo);

	ArraySymToH5(GroupName, Sim_FilObjInfo);

	ArraySymToH5(GroupName, Sim_TrkletInfo);
	ArraySymToH5(GroupName, Sim_TrkInfo);

	ArraySymToH5(GroupName, image);
	ArraySymToH5(GroupName, Object);
	ArraySymToH5(GroupName, Can);

#if WEBCAM_OPTION
	ArraySymToH5(GroupName, webcam);
#endif

}



void ReadVarTypeDim(string *var_type, hsize_t* dims)
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



void CreateHDF5File(void)
{
	hid_t file_id;

	/* Create a new file using default properties. */
	gDstFid = H5Fcreate(SimResultFname, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}



void CreateHDF5Group(const char *group_name)
{
	hid_t group_id;  /* identifiers */
	herr_t status;

	/* Create group in the root group using absolute name. */
	group_id = H5Gcreate2(gDstFid, group_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	/* Close groups. */
	status = H5Gclose(group_id);
}



void HDF5_ReadData(const char *group_name, const char *var_name, void *Data)
{
	hid_t group_id, dataset_id, dataspace_id;  /* identifiers */
	hid_t filespace;
	hid_t Dtype, Dtype_mem;
	hsize_t dims[2];
	herr_t status;
	int ndims;

	group_id = H5Gopen2(gSrcFid, group_name, H5P_DEFAULT);

	/* Open the file and the dataset. */
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
}



void HDF5_WriteArrayData(const char *group_name, const char *var_name, const char *var_type, hsize_t* dims, void *Data)
{

	hid_t group_id, dataset_id, dataspace_id;  /* identifiers */
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

	if (dims[1] == 1)
	{
		dataspace_id = H5Screate_simple(1, dims, NULL);
	}
	else
	{
		dataspace_id = H5Screate_simple(2, dims, NULL);
	}


	/* Open an existing group of the specified file. */
	group_id = H5Gopen2(gDstFid, group_name, H5P_DEFAULT);



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

}



void HDF5_WriteData(const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data)
{

	hid_t group_id, dataset_id, dataspace_id;  /* identifiers */
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

	dataspace_id = H5Screate_simple(1, dim, NULL);

	/* Open an existing group of the specified file. */
	group_id = H5Gopen2(gDstFid, group_name, H5P_DEFAULT);

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
	}


	/* Close the data space */
	status = H5Sclose(dataspace_id);

	/* Close the dataset */
	status = H5Dclose(dataset_id);

	/* Close the group. */
	status = H5Gclose(group_id);

}



void ReadSimInfoINI(char* IniFname)
{
	// fromresimInfo.ini import [DataInfo] section
	GetPrivateProfileString((LPCTSTR)"FileInfo", (LPCTSTR)"SimResultFname", (LPCTSTR)"NoExist", (LPTSTR)SimResultFname, MAX_FILENAME_BUFFER_SIZE, (LPCTSTR)IniFname);
	GetPrivateProfileString((LPCTSTR)"DataInfo", (LPCTSTR)"LoggingDataFname", (LPCTSTR)"NoExist", (LPTSTR)LoggingDataFname, MAX_FILENAME_BUFFER_SIZE, (LPCTSTR)IniFname);
	GetPrivateProfileString((LPCTSTR)"SimInfo", (LPCTSTR)"InitialScan", (LPCTSTR)"NoExist", (LPTSTR)initScanString, MAX_FILENAME_BUFFER_SIZE, (LPCTSTR)IniFname);
	GetPrivateProfileString((LPCTSTR)"SimInfo", (LPCTSTR)"FinalScan", (LPCTSTR)"NoExist", (LPTSTR)finScanString, MAX_FILENAME_BUFFER_SIZE, (LPCTSTR)IniFname);
	GetPrivateProfileString((LPCTSTR)"LogModInfo", (LPCTSTR)"peakMode", (LPCTSTR)"NoExist", (LPTSTR)peakModeString, MAX_FILENAME_BUFFER_SIZE, (LPCTSTR)IniFname);

}

