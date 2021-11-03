#ifndef _RSP_SIM_H_
#define _RSP_SIM_H_


/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/


/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/


/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/


/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/


/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/
#define TRANS(x) {#x}

#define H5ToSym(group, var){\
	string name = TRANS(var);\
	HDF5_ReadData(group.c_str(), name.c_str(), &var);\
}

#define H5ToArraySym(group, var){\
	string name = TRANS(var);\
	HDF5_ReadData(group.c_str(), name.c_str(), var);\
}

#define H5ToStructSym(group, dataset, var){\
	HDF5_ReadData(group.c_str(), dataset.c_str(), &var);\
}

#define H5ToStructArraySym(group, dataset, var){\
	HDF5_ReadData(group.c_str(), dataset.c_str(), var);\
}

#define SymToH5(group, var){\
	string name = TRANS(var);\
	string type = typeid(var).name();\
	hsize_t dim = 1;\
	HDF5_WriteData(group.c_str(), name.c_str(), type.c_str(), &dim, &var);\
}

#define ArraySymToH5(group, var){\
	string name = TRANS(var);\
	string type = typeid(var).name();\
	hsize_t dims[2]; ReadVarTypeDim(&type, dims);\
	HDF5_WriteArrayData(group.c_str(), name.c_str(), type.c_str(), dims, var);\
}

#define H5ToSimSym(group, var){\
	string name = TRANS(var);\
	if (name.find("Sim_") == 0)\
		name.erase(0, 4);\
	HDF5_ReadData(group.c_str(), name.c_str(), &var);\
}

#define H5ToArraySimSym(group, var){\
	string name = TRANS(var);\
	if (name.find("Sim_") == 0)\
		name.erase(0, 4);\
	HDF5_ReadData(group.c_str(), name.c_str(), var);\
}


#define WEBCAM_OPTION 0

#endif


