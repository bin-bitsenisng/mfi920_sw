#ifndef _HDF5_CTRL_H_
#define _HDF5_CTRL_H_

#include "stdafx.h"
#include <stdlib.h>
#include <chrono>
#include <queue>
#include <thread>
#include <functional>
#include <boost/core/demangle.hpp>
#include "hdf5.h"
#include "ini.h"
#include "main_argument.h"

using namespace std;

#define TRANS(x) {#x}

#define H5ToSym(file, group, var){\
	string name = TRANS(var);\
	HDF5_ReadData(file, group.c_str(), name.c_str(), &var);\
}

#define H5ToArraySym(file, group, var){\
	string name = TRANS(var);\
	HDF5_ReadData(file, group.c_str(), name.c_str(), var);\
}

#define H5ToStructSym(file, group, dataset, var){\
	HDF5_ReadData(file, group.c_str(), dataset.c_str(), &var);\
}

#define H5ToStructArraySym(file, group, dataset, var){\
	HDF5_ReadData(file, group.c_str(), dataset.c_str(), var);\
}

#define SymToH5(file, group, var){\
	string name = TRANS(var);\
	string type = boost::core::demangle(typeid(var).name());\
	hsize_t dim = 1;\
	HDF5_WriteData(file, group.c_str(), name.c_str(), type.c_str(), &dim, &var);\
}

#define ArraySymToH5(file, group, var){\
	string name = TRANS(var);\
	string type = boost::core::demangle(typeid(var).name());\
	hsize_t dims[2]; ReadVarTypeDim(&type, dims);\
	HDF5_WriteArrayData(file, group.c_str(), name.c_str(), type.c_str(), dims, var);\
}

#define H5ToSimSym(file, group, var){\
	string name = TRANS(var);\
	if (name.find("Sim_") == 0)\
		name.erase(0, 4);\
	HDF5_ReadData(file, group.c_str(), name.c_str(), &var);\
}

#define H5ToArraySimSym(file, group, var){\
	string name = TRANS(var);\
	if (name.find("Sim_") == 0)\
		name.erase(0, 4);\
	HDF5_ReadData(file, group.c_str(), name.c_str(), var);\
}

void ReadVarTypeDim(string *var_type, hsize_t* dims);
void HDF5_WriteArrayData(char* outputFileName, const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data);
void HDF5_WriteData(char* outputFileName, const char *group_name, const char *var_name, const char *var_type, hsize_t* dim, void *Data);
void CreateHDF5File(char* outputFileName);
void CreateHDF5Group(char* outputFileName, const char *group_name);
void StoreInfoGroup(char* outputFileName, uint32_t initScan, uint32_t finScan);
void StoreScanGroup(char* outputFileName, int32_t scan_idx);
void StoreDAQGroup(char* outputFileName, int32_t scan_idx);
void StoreRSPGroup(char* outputFileName, int32_t scan_idx);

void ReadInfoGroup(char* inputFileName);
void ReadScanGroup(char* inputFileName, int32_t scan_idx);
void HDF5_ReadData(char* inputFileName, const char *group_name, const char *var_name, void *Data);

void ReadSimInfoINI(char* IniFname, MainArgument* main_argument);

#endif
