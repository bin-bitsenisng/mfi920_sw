/************************************************************************
| Project Name: AFI910
|    File Name: can.c
|  Description: detailed Description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company                        
| --------     ---------------------     -------------------------------
| 11010        Heungsun Yoon             bitsensing Corporation
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description                                 
| ----------  ----  ------  --------------------------------------------
| 2021.03.15   0.0  11010   Creation;
|***********************************************************************/

#ifndef _CAN_C_
#define _CAN_C_

/* include system primitive types */
#include "bts.h"
#include "can_cfg.h"

/* include system driver header */

/* include system bsp header */
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>


#include <linux/can.h>
#include <linux/can/raw.h>

/* include system application header */

/* final include module header */
#include "can.h"
#include "can_sig.h"
#include "sys_param.h"

/* declare global variables */
can_handler_t can_handler;

/* declare static variables */

/* static function prototypes */

/* functions */
/***************************************************
 * function name : can_init
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
can_ret_t can_init(void)
{
    const char* ifName = CAN_NAME;
    memset(&can_handler, 0, sizeof(can_handler));

    if ((can_handler.socketInd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return retFail;
    }

    strcpy(can_handler.ifr.ifr_name, ifName);
    ioctl(can_handler.socketInd, SIOCGIFINDEX, &(can_handler.ifr));

    can_handler.sAddr.can_family = AF_CAN;
    can_handler.sAddr.can_ifindex = can_handler.ifr.ifr_ifindex;

    printf("%s at index %d\n", ifName, can_handler.ifr.ifr_ifindex);

    if (bind(can_handler.socketInd, (struct sockaddr*)&(can_handler.sAddr),
            sizeof(can_handler.sAddr))
        == -1) {
        perror("Error in socket bind");
        return retFail;
    }

    return retOK;
}

can_ret_t can_close(int socketIndex)
{
    if (close(socketIndex) < 0) {
        perror("Close");
        return retFail;
    }
}

can_ret_t can_read(void)
{
    int nbytes;
    int i;
    struct can_frame frame;
    f32_t rxsigdata;
    int32_t ret;

    nbytes = read(can_handler.socketInd, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
        perror("Read");
        can_close(can_handler.socketInd);
        return retFail;
    }

    // printf("received canId: 0x%03X, length: %d", frame.can_id, frame.can_dlc);
    // for (i = 0; i < frame.can_dlc; i++) {
    //     printf("%02X ", frame.data[i]);
    // }
    // printf("\r\n");

    for (i = 0; i < CANSIGNAL_MAX; i++) {
        if (SYS_PARAM_CANRX.signal[i].en == 1) {
            if (SYS_PARAM_CANRX.signal[i].msgid & 0x80000000) {
                // extid
                if ((SYS_PARAM_CANRX.signal[i].msgid & 0x00FFFF00) != (frame.can_id & 0x00FFFF00)) {
                    continue;
                }
            } else {
                // stdid
                if ((SYS_PARAM_CANRX.signal[i].msgid & 0x7FF) != (frame.can_id & 0x7FF)) {
                    continue;
                }
            }
            rxsigdata = 0.0f;

            ret = can_sig_getsignal(frame.data, &rxsigdata, &SYS_PARAM_CANRX.signal[i]);
            if (ret == retOK) {
                switch (SYS_PARAM_CANRX.signal[i].sigid) {
                case can_sig_id_vehicle_speed:
                    can_sig_data.vehicle_speed = rxsigdata;
                    //printf("vehicle_speed: %f\r\n", can_sig_data.vehicle_speed);
                    break;
                case can_sig_id_wheel_speed_fl:
                    can_sig_data.wheel_speed_fl = rxsigdata;
                    //printf("wheel_speed_fl: %f\r\n", can_sig_data.wheel_speed_fl);
                    break;
                case can_sig_id_wheel_speed_fr:
                    can_sig_data.wheel_speed_fr = rxsigdata;
                    //printf("wheel_speed_fr: %f\r\n", can_sig_data.wheel_speed_fr);
                    break;
                case can_sig_id_wheel_speed_rl:
                    can_sig_data.wheel_speed_rl = rxsigdata;
                    //printf("wheel_speed_rl: %f\r\n", can_sig_data.wheel_speed_rl);
                    break;
                case can_sig_id_wheel_speed_rr:
                    can_sig_data.wheel_speed_rr = rxsigdata;
                    //printf("wheel_speed_rr: %f\r\n", can_sig_data.wheel_speed_rr);
                    break;
                case can_sig_id_steerangle:
                    can_sig_data.steerangle = rxsigdata;
                    //printf("steerangle: %f\r\n", can_sig_data.steerangle);
                    break;
                case can_sig_id_steeranglespeed:
                    can_sig_data.steeranglespeed = rxsigdata;
                    //printf("steeranglespeed: %f\r\n", can_sig_data.steeranglespeed);
                    break;
                case can_sig_id_yawrate:
                    can_sig_data.yawrate = rxsigdata;
                    //printf("yawrate: %f\r\n", can_sig_data.yawrate);
                    break;
                case can_sig_id_longaccel:
                    can_sig_data.longaccel = rxsigdata;
                    //printf("longaccel: %f\r\n", can_sig_data.longaccel);
                    break;
                case can_sig_id_lataccel:
                    can_sig_data.lataccel = rxsigdata;
                    //printf("lataccel: %f\r\n", can_sig_data.lataccel);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

can_ret_t can_filter_setting(void)
{
    return retOK;
}

can_ret_t can_osinit(void)
{

    return retOK;
}

#endif //_CAN_C_