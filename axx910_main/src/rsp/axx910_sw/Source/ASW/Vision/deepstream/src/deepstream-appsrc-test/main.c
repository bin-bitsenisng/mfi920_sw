#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "gstnvdsmeta.h"

// local
#include "constant.h"
#include "appsrc_data.h"
#include "input_check.h"
#include "input_parse.h"
#include "elements_factory.h"
#include "utils.h"
#include "appsink_callback.h"
#include "bus_callback.h"
#include "caps_filter_init.h"
  
int
main (int argc, char **argv)
{
    GMainLoop 
        *loop = NULL;
    GstElement 
        *pipeline    = NULL,
        *nvvidconv1  = NULL,
        *caps_filter = NULL,
        *streammux   = NULL,
        *sink        = NULL,
        *pgie        = NULL,
        *nvvidconv2  = NULL,
        *nvosd       = NULL,
        *tee         = NULL,
        *appsink     = NULL,
        *transform   = NULL;
    GstBus     
        *bus         = NULL;
    guint bus_watch_id;

    GstPad *tee_source_pad1, 
            *osd_sink_pad, 
            *tee_source_pad2,
            *appsink_sink_pad,
            *srcpad,
            *sinkpad; 

    AppSrcData data;

    long 
        width  = 0,
        height = 0,
        fps    = 0;

    gchar 
        *format     = NULL,
        *filepath   = NULL,
        *configpath = NULL;


    if ( input_check (argc, argv) == -1 ) return -1;
    if ( input_parse ( &format, &filepath, &configpath, &width, &height, &fps, (const char**)(argv)) == -1 ) return -1; 


    // init
    gst_init (&argc, &argv);
    loop = g_main_loop_new (NULL, FALSE);

    memset (&data, 0, sizeof(data));
    pipeline        = gst_pipeline_new        ( "dstest-appsrc-pipeline"                                );
    data.app_source = gst_element_factory_make( "appsrc"                 , "app-source"                 ); /* App Source element for reading from raw video file */
    nvvidconv1      = gst_element_factory_make( "nvvideoconvert"         , "nvvideo-converter1"         ); /* Use convertor to convert from software buffer to GPU buffer */
    caps_filter     = gst_element_factory_make( "capsfilter"             , "capsfilter"                 );
    streammux       = gst_element_factory_make( "nvstreammux"            , "stream-muxer"               ); /* Create nvstreammux instance to form batches from one or more sources. */
    pgie            = gst_element_factory_make( "nvinfer"                , "primary-nvinference-engine" ); /* Use nvinfer to run inferencing on streammux's output, behaviour of inferencing is set through config file */
    nvvidconv2      = gst_element_factory_make( "nvvideoconvert"         , "nvvideo-converter2"         ); /* Use convertor to convert from NV12 to RGBA as required by nvdsosd */
    nvosd           = gst_element_factory_make( "nvdsosd"                , "nv-onscreendisplay"         ); /* Create OSD to draw on the converted RGBA buffer */
    tee             = gst_element_factory_make( "tee"                    , "tee"                        ); /* Finally render the osd output. We will use a tee to render video playback on nveglglessink, and we use appsink to extract metadata from buffer and print object, person and vehicle count. */
    transform       = gst_element_factory_make( "nvegltransform"         , "nvegl-transform"            );
    sink            = gst_element_factory_make( "nveglglessink"          , "nvvideo-renderer"           );
    appsink         = gst_element_factory_make( "appsink"                , "app-sink"                   );

    srcpad           = gst_element_get_static_pad  (caps_filter , "src"    );
    sinkpad          = gst_element_get_request_pad (streammux   , "sink_0" );
    tee_source_pad1  = gst_element_get_request_pad (tee         , "src_0"  );
    osd_sink_pad     = gst_element_get_static_pad  (nvosd       , "sink"   );
    tee_source_pad2  = gst_element_get_request_pad (tee         , "src_1"  );
    appsink_sink_pad = gst_element_get_static_pad  (appsink     , "sink"   );

    // configure
    appsrc_data_init (&data, width, height, fps, format, filepath);
    caps_filter_init (G_OBJECT (caps_filter), data.vidconv_format);

    g_object_set (G_OBJECT (streammux), 
                                        "width"               , width                   ,
                                        "height"              , height                  ,
                                        "batch-size"          , 1                       ,
                                        "live-source"         , TRUE                    ,
                                        "batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC, 
                                        NULL);
    g_object_set (G_OBJECT (pgie),
                                        "config-file-path",     configpath, 
                                        NULL);
    g_object_set (G_OBJECT (appsink), 
                                        "emit-signals", TRUE ,
                                        "async"       , FALSE, 
                                        NULL);
    g_signal_connect (G_OBJECT (appsink), 
                                        "new-sample", G_CALLBACK (new_sample), 
                                        NULL);
    bus          = gst_pipeline_get_bus (     GST_PIPELINE (pipeline)); /* we add a message handler */
    bus_watch_id = gst_bus_add_watch    (bus, bus_call    , loop     );


    // link
    gst_bin_add_many (GST_BIN (pipeline),
                                        data.app_source, 
                                        nvvidconv1, caps_filter, streammux, pgie,
                                        nvvidconv2, nvosd, tee, sink, appsink, transform, 
                                        NULL);

    if (!gst_element_link_many (data.app_source, nvvidconv1, caps_filter,      NULL) ||
        !gst_element_link_many (nvosd          , transform , sink       ,      NULL) ||
        !gst_element_link_many (streammux      , pgie      , nvvidconv2 , tee, NULL)) {
        g_printerr ("Elements could not be linked: Exiting.\n");
        return -1;
    }

    LINK_PAD (srcpad , sinkpad);
    LINK_PAD (tee_source_pad1, osd_sink_pad);
    //LINK_PAD (tee_source_pad2, appsink_sink_pad);


    // run

    GST_DEBUG_BIN_TO_DOT_FILE(pipeline, GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");

    g_print ("Now playing: %s\n", filepath);
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    g_print ("Running...\n");
    g_main_loop_run (loop);


    // final
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);

    g_print           ("Deleting pipeline\n");
    gst_object_unref  (bus                  );
    gst_object_unref  (srcpad               );
    gst_object_unref  (sinkpad              );
    gst_object_unref  (tee_source_pad1      );
    gst_object_unref  (osd_sink_pad         );
    gst_object_unref  (tee_source_pad2      );
    gst_object_unref  (appsink_sink_pad     );
    gst_object_unref  (GST_OBJECT (pipeline));
    g_source_remove   (bus_watch_id         );
    g_main_loop_unref (loop                 );
    return 0;
}
