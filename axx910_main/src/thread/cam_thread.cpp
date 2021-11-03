/************************************************************************
 | Project Name: AFI910
 |    File Name: cam_thread.cpp
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
 | 2021.02.05  0.0   mhkim   Creation;
 |***********************************************************************/


#include <vector>
#include <thread>
#include <unistd.h>
#include <zmq.hpp>
#include <mutex>

#include "cam_thread_cfg.h"
#include "cam_thread.h"
#include "print_common.h"
#include "device_ctrl.h"
#include "inference.h"
#include "lane_data_output.h"

#include "camera_device_cfg.h"

uint32_t jpg_image_size = 0;
uint8_t jpg_image[CAM_IMAGE_SIZE_MAX];
std::mutex g_mutex_get_image;

extern std::queue<int32_t> g_inference_request_queue;
extern ai_object_t ai_object[AI_OBJECT_MAX_SIZE];
extern LaneDataOut lane_data_output;

void StartCAMthread(void)
{
	//std::thread daq_thread(ServiceCAM); 

	//cam_thread.join();
}

void ServiceCAM(void)
{
	TRACE_SYS_MSG("CAM Thread starts.\n");
	
    zmq::context_t context(1);
    zmq::socket_t sock (context, ZMQ_REQ);
    zmq::message_t connect_request;
    zmq::message_t image_message;
    zmq::message_t ai_message;
    zmq::message_t lane_data_message;
    sock.connect(BIND_STRING);

    TRACE_SYS_MSG("Try to connect server\n");
    sock.send(connect_request);
    sock.recv(&connect_request);
    TRACE_SYS_MSG("Connect server success.\n");
    
    while(1)
    {
        if(!g_inference_request_queue.empty())
        {
            if(g_inference_request_queue.size() > 1)
            {
                TRACE_ERR_MSG("[WARNING] cam queue size is over 1.. it is %d\n", g_inference_request_queue.size());
            }
            while(!g_inference_request_queue.empty()) 
            {
                g_inference_request_queue.pop();
            }

            sock.send(image_message);
            sock.recv(&image_message);
            usleep(10);
            sock.send(ai_message);           
            sock.recv(&ai_message);
            usleep(10);
            sock.send(lane_data_message);           
            sock.recv(&lane_data_message);
            jpg_image_size = image_message.size();
            memcpy(jpg_image, image_message.data(), jpg_image_size);
            ai_object[0].Ai_num_of_class = ai_message.size() / sizeof(ai_object);
            memcpy(ai_object, ai_message.data(), ai_message.size());
            memcpy(&lane_data_output, lane_data_message.data(), lane_data_message.size());
            
            TRACE_SYS_MSG("Received cam data.\n");
        }
    }

    sock.close();

	TRACE_SYS_MSG("CAM Thread Finished.\n");
}

int32_t GetCamJpgFrame(uint8_t* dst_image_packet, uint32_t image_max_size, cam_drv_camera_info_t* frameinfo)
{
    frameinfo->format = CAMERA_FORMAT_JPEG;
    frameinfo->height = CAPTURE_HEIGHT;
    frameinfo->width = CAPTURE_WIDTH;
    frameinfo->size = jpg_image_size;
    
    if((memcpy(dst_image_packet, jpg_image, jpg_image_size) == NULL) || (frameinfo->size > image_max_size))
    {
        return retFail;
    }
    else
    {
        return retOK;
    }
}
