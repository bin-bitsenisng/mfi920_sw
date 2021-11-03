#include <unistd.h>

#include "radar.h"
#include "radar_device_cfg.h"
#include "print_common.h"

void InitRadar(RADAR_DEVICE* radar_device)
{
    /*
    while(1)
    {
        radar_device->radar_cap.open(RADAR_DEVICE_NUM, RADAR_API_PREFERENCE);

        if (!radar_device->radar_cap.isOpened())
        {
            TRACE_SYS_MSG("Radar Videocapture Open Fail.. Retry!\n");
        }	
        else
        {
            TRACE_SYS_MSG("Radar Videocapture Open Success!\n");
            break;
        }

        usleep(100000);
    }
    
    radar_device->radar_cap.set(CAP_PROP_CONVERT_RGB, 0.0); // raw data: 24bit(RGB) => 16bit
    */

    TRACE_SYS_MSG("Radar Initialization should be changed!\n");
}

void CaptureRadar(RADAR_DEVICE* radar_device)
{
    // From afi910_example source

    
}