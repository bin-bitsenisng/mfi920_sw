/************************************************************************
| Project Name: bts_comm_appl_raw
|    File Name: bts_comm_appl_raw.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Lobeye
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2018.06.26   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include <string.h>

/* include system driver header */
//#include "drivers.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"
//#include "cam_task.h"
#include "cam_thread.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
#include "bts_comm_cfg.h"
#include "bts_comm_appl_dataset.h"
//#include "rsp_task.h"
//#include "drivers.h"

#include "bts_comm_appl_image.h"


#if bts_COMM_APPL_IMAGE_TESTMODE == 1
extern uint8_t image_test0[];
extern uint8_t image_test1[];
extern uint8_t image_test2[];
extern uint32_t size_image_test0;
extern uint32_t size_image_test1;
extern uint32_t size_image_test2;
#endif

/* declare global variables */
bts_comm_appl_imagepacket_t bts_comm_appl_imagepacket;
uint8_t bts_comm_appl_imagepacketbuff[bts_COMM_APPL_IMAGE_SIZE_MAX];
uint32_t bts_comm_appl_imagepacketsize = 0;
uint32_t bts_comm_appl_imagepacket_skipcnt = 0;
/* declare static variables */

/* static function prototypes */

/* functions */
//int32_t GetCamJpgFrame(uint8_t* dst_image_packet, uint32_t image_max_size, cam_drv_camera_info_t* frameinfo);

/******************************************************************************
 * function name : bts_comm_appl_raw_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_image_init(void)
{
	bts_comm_appl_imagepacket_skipcnt = 0;

}

/******************************************************************************
 * function name : bts_comm_appl_pid_image_packetbuild
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.07.27
 *****************************************************************************/
void bts_comm_appl_pid_image_packetbuild(void)
{

#if SYS_CAM_ENABLE == 1
	static int32_t apppkt_skipcnt = 0;
	int32_t i;
    cam_drv_camera_info_t frameinfo;

	//if(cam_get_frame(bts_comm_appl_imagepacket.image_data, bts_COMM_APPL_IMAGE_SIZE_MAX, &frameinfo, 0)==retOK)
	if(GetCamJpgFrame(bts_comm_appl_imagepacket.image_data, bts_COMM_APPL_IMAGE_SIZE_MAX, &frameinfo) == retOK)
	{
		bts_comm_appl_imagepacket.image_info.format = frameinfo.format;
		bts_comm_appl_imagepacket.image_info.height = frameinfo.height;
		bts_comm_appl_imagepacket.image_info.width = frameinfo.width;
		bts_comm_appl_imagepacket.image_info.size = frameinfo.size;
		
		bts_comm_appl_imagepacketsize = 0;
		bts_comm_appl_imagepacketsize = (uint32_t)bts_commpacket_make_dto_packet(bts_comm_appl_imagepacketbuff,
																						bts_comm_pid_image,
																						0,
																						0,
																						(uint32_t)(bts_comm_get_timestamp() / 100UL),
																						(uint8_t *)&bts_comm_appl_imagepacket,
																						sizeof(bts_comm_appl_image_info_t) + bts_comm_appl_imagepacket.image_info.size);

		for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
		{
			if(SYS_PARAM_SENSORTYPE.pid_image_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_image_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
			{
				bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)bts_comm_appl_imagepacketbuff, bts_comm_appl_imagepacketsize);
			}
		}
		apppkt_skipcnt++;


#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
		krs_log("image packetsize : %d\n\r", bts_comm_appl_imagepacketsize);
#endif
	}
	else
	{
		bts_comm_appl_imagepacketsize = 0;
	}
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_pid_image_packetsend
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_pid_image_packetsend(void)
{
#if SYS_CAM_ENABLE == 1
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_image])==retOK)
	{
		if((bts_comm_daqinfo_is_start(bts_comm_pid_image) == retOK) && SYS_PARAM_ITS_CONFIG.misc.camera_on == true)
		{
			bts_comm_addpacket(bts_comm_appl_imagepacketbuff, bts_comm_appl_imagepacketsize, NULL);
		}
	}
#endif
}
/* end of file */
