/************************************************************************
 | Project Name: AFI910
 |    File Name: inference.cpp
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
 | 2021.02.01  0.0   mhkim   Creation;
 |***********************************************************************/

#include "inference.h"
#include "inference_cfg.h"

#include <unistd.h>
#include <cstring>

#include <yolov5/yolov5.h>

bts::YoloV5 *yolov5;
ai_object_t ai_object[AI_OBJECT_MAX_SIZE];
std::map<int, std::string> labels;

//char id_parser[10][100] = {"bike", "bus", "car", "motor", "person", "rider", "traffic light", "traffic sign", "train", "truck"};
//char id_parser[9][100] = {"bus", "truck", "long truck", "sedan", "suv", "van", "motocycle", "pedestrian", "others"};

void InitInference(double confThresh, double nmsThresh)
{
    int deviceId = 0;
    int inputH = AI_INPUT_X;
    int inputW = AI_INPUT_Y;
    int maxOutputBboxCount = 1000;

    int classNum = 10;
    int batchSize = 1;

    yolov5 = new bts::YoloV5(INPUT_BLOB,
                        OUTPUT_BLOB,
                        ANCHOR_FILE,
                        deviceId,
                        inputH,
                        inputW,
                        maxOutputBboxCount,
                        classNum,
                        batchSize,
                        confThresh,
                        nmsThresh);

    printf("[AI] load engine.\n");
    yolov5->load_engine(ENGINE_FILE);

    printf("[AI] prepare inference.\n");
    yolov5->prepare_infer();
    yolov5->set_grids();

    if (classNum == 80) {
        labels = {{0, "person"}, {1, "bicycle"}, {2, "car"}, {3, "motorbike"}, {4, "aeroplane"},
        {5, "bus"}, {6, "train"}, {7, "truck"}, {8, "boat"}, {9, "traffic light"}, {10, "fire hydrant"}, {11, "stop sign"},
        {12, "parking meter"}, {13, "bench"}, {14, "bird"}, {15, "cat"}, {16, "dog"}, {17, "horse"}, {18, "sheep"}, {19, "cow"},
        {20, "elephant"}, {21, "bear"}, {22, "zebra"}, {23, "giraffe"}, {24, "backpack"}, {25, "umbrella"}, {26, "handbag"},
        {27, "tie"}, {28, "suitcase"}, {29, "frisbee"}, {30, "skis"}, {31, "snowboard"}, {32, "sports ball"}, {33, "kite"},
        {34, "baseball bat"}, {35, "baseball glove"}, {36, "skateboard"}, {37, "surfboard"}, {38, "tennis racket"}, {39, "bottle"},
        {40, "wine glass"}, {41, "cup"}, {42, "fork"}, {43, "knife"}, {44, "spoon"}, {45, "bowl"}, {46, "banana"}, {47, "apple"},
        {48, "sandwich"}, {49, "orange"}, {50, "broccoli"}, {51, "carrot"}, {52, "hot dog"}, {53, "pizza"}, {54, "donut"},
        {55, "cake"}, {56, "chair"}, {57, "sofa"}, {58, "pottedplant"}, {59, "bed"}, {60, "diningtable"}, {61, "toilet"},
        {62, "tvmonitor"}, {63, "laptop"}, {64, "mouse"}, {65, "remote"}, {66, "keyboard"}, {67, "cell phone"}, {68, "microwave"},
        {69, "oven"}, {70, "toaster"}, {71, "sink"}, {72, "refrigerator"}, {73, "book"}, {74, "clock"}, {75, "vase"}, {76, "scissors"},
        {77, "teddy bear"}, {78, "hair drier"}, {79, "toothbrush"}};
    }
    else if (classNum == 9) {
        labels = {{0, "bus"}, {1, "truck"}, {2, "long truck"}, {3, "sedan"}, {4, "suv"},
        {5, "van"}, {6, "motocycle"}, {7, "pedestrian"}, {8, "others"}};
    }
    else if (classNum == 10) {
        labels = {{0, "bike"}, {1, "bus"}, {2, "car"}, {3, "motor"}, {4, "person"},
        {5, "rider"}, {6, "traffic light"}, {7, "traffic sign"}, {8, "train"}, {9, "truck"}};
    }
    else {
        std::cout << "class Num should be 80(coco) or 9(atm220) or 10(afi910)" << std:: endl;
        //return -1;
    }
}

cv::Mat Inference(cv::Mat img)
{
    yolov5->infer(img);
    yolov5->onnx_post_process(img);

    auto objects = yolov5->get_objects_info(img);

    ai_object[0].Ai_num_of_class = objects.size();

    for(int i = 0; i < objects.size(); i++)
    {
        auto class_id0 = objects[i].class_id;
        auto conf_score0 = objects[i].conf_score;
        auto bbox0 = objects[i].bbox_info;
        /*
        printf("object class id: %d\n", class_id0);
        printf("object confidence score: %d\n", conf_score0);
        printf("object bbox height: %d\n", bbox0.height);
        printf("object bbox width:  %d\n", bbox0.width);
        printf("object bbox x: %d\n", bbox0.x);
        printf("object bbox y: %d\n", bbox0.y);
*/
        ai_object[i].Ai_class_id = objects[i].class_id;   
        ai_object[i].Ai_confidence = objects[i].conf_score;
        ai_object[i].Ai_height = objects[i].bbox_info.height;
        ai_object[i].Ai_width = objects[i].bbox_info.width;
        ai_object[i].Ai_x_location = objects[i].bbox_info.x;
        ai_object[i].Ai_y_location = objects[i].bbox_info.y;
    }

    //return yolov5->draw_objects(img, labels);
    return img;
}