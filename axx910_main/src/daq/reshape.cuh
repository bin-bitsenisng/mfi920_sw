#/************************************************************************
 | Project Name: AFI910
 |    File Name: reshape.cuh
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.03.12  0.0   mhkim   Creation;
 |***********************************************************************/

void cudamalloc_data(int16_t* daq_rm_data, int16_t* daq_lr_data, int16_t* daq_mr_data, int16_t* daq_sr_data,   \
                       int16_t* rm_reshaped_data, int16_t* lr_reshaped_data, int16_t* mr_reshaped_data, int16_t* sr_reshaped_data);

void reshape_raw_data(int16_t* daq_rm_data, int16_t* daq_lr_data, int16_t* daq_mr_data, int16_t* daq_sr_data, int16_t* reshaped_data);