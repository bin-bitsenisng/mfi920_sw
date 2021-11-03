#!/usr/bin/env python3

################################################################################
# Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
################################################################################

import sys
sys.path.append('../')
import gi
gi.require_version('Gst', '1.0')
from gi.repository import GObject, Gst, GstApp

from common.is_aarch_64 import is_aarch64
from common.bus_call import bus_call


import pyds

PGIE_CLASS_ID_VEHICLE = 0
PGIE_CLASS_ID_BICYCLE = 1
PGIE_CLASS_ID_PERSON = 2
PGIE_CLASS_ID_ROADSIGN = 3


def osd_sink_pad_buffer_probe(pad,info,u_data):
    frame_number=0
    #Intiallizing object counter with 0.
    obj_counter = {
        PGIE_CLASS_ID_VEHICLE:0,
        PGIE_CLASS_ID_PERSON:0,
        PGIE_CLASS_ID_BICYCLE:0,
        PGIE_CLASS_ID_ROADSIGN:0
    }
    num_rects=0

    gst_buffer = info.get_buffer()
    if not gst_buffer:
        print("Unable to get GstBuffer ")
        return

    # Retrieve batch metadata from the gst_buffer
    # Note that pyds.gst_buffer_get_nvds_batch_meta() expects the
    # C address of gst_buffer as input, which is obtained with hash(gst_buffer)
    batch_meta = pyds.gst_buffer_get_nvds_batch_meta(hash(gst_buffer))
    l_frame = batch_meta.frame_meta_list
    while l_frame is not None:
        try:
            # Note that l_frame.data needs a cast to pyds.NvDsFrameMeta
            # The casting is done by pyds.glist_get_nvds_frame_meta()
            # The casting also keeps ownership of the underlying memory
            # in the C code, so the Python garbage collector will leave
            # it alone.
            #frame_meta = pyds.glist_get_nvds_frame_meta(l_frame.data)
            frame_meta = pyds.NvDsFrameMeta.cast(l_frame.data)
        except StopIteration:
            break

        frame_number=frame_meta.frame_num
        num_rects = frame_meta.num_obj_meta
        l_obj=frame_meta.obj_meta_list
        while l_obj is not None:
            try:
                # Casting l_obj.data to pyds.NvDsObjectMeta
                #obj_meta=pyds.glist_get_nvds_object_meta(l_obj.data)
                obj_meta=pyds.NvDsObjectMeta.cast(l_obj.data)
            except StopIteration:
                break
            obj_counter[obj_meta.class_id] += 1
            obj_meta.rect_params.border_color.set(0.0, 0.0, 1.0, 0.0)
            try: 
                l_obj=l_obj.next
            except StopIteration:
                break

        # Acquiring a display meta object. The memory ownership remains in
        # the C code so downstream plugins can still access it. Otherwise
        # the garbage collector will claim it when this probe function exits.
        display_meta=pyds.nvds_acquire_display_meta_from_pool(batch_meta)
        display_meta.num_labels = 1
        py_nvosd_text_params = display_meta.text_params[0]
        # Setting display text to be shown on screen
        # Note that the pyds module allocates a buffer for the string, and the
        # memory will not be claimed by the garbage collector.
        # Reading the display_text field here will return the C address of the
        # allocated string. Use pyds.get_string() to get the string content.
        py_nvosd_text_params.display_text = "Frame Number={} Number of Objects={} Vehicle_count={} Person_count={}".format(frame_number, num_rects, obj_counter[PGIE_CLASS_ID_VEHICLE], obj_counter[PGIE_CLASS_ID_PERSON])

        # Now set the offsets where the string should appear
        py_nvosd_text_params.x_offset = 10
        py_nvosd_text_params.y_offset = 12

        # Font , font-color and font-size
        py_nvosd_text_params.font_params.font_name = "Serif"
        py_nvosd_text_params.font_params.font_size = 10
        # set(red, green, blue, alpha); set to White
        py_nvosd_text_params.font_params.font_color.set(1.0, 1.0, 1.0, 1.0)

        # Text background color
        py_nvosd_text_params.set_bg_clr = 1
        # set(red, green, blue, alpha); set to Black
        py_nvosd_text_params.text_bg_clr.set(0.0, 0.0, 0.0, 1.0)
        # Using pyds.get_string() to get display_text as string
        print(pyds.get_string(py_nvosd_text_params.display_text))
        pyds.nvds_add_display_meta_to_frame(frame_meta, display_meta)
        try:
            l_frame=l_frame.next
        except StopIteration:
            break
			
    return Gst.PadProbeReturn.OK	


def main(args):
    # Check input arguments
    if len(args) != 2:
        sys.stderr.write("usage: %s <media file or uri>\n" % args[0])
        sys.exit(1)

    # Standard GStreamer initialization
    GObject.threads_init()
    Gst.init(None)

    # Create gstreamer elements
    # Create Pipeline element that will form a connection of other elements
    print("Creating Pipeline \n ")
    pipeline = Gst.Pipeline()

    if not pipeline:
        sys.stderr.write(" Unable to create Pipeline \n")

    # Source element for reading from the file
    print("Creating Source \n ")
    source = Gst.ElementFactory.make("filesrc", "file-source")
    if not source:
        sys.stderr.write(" Unable to create Source \n")

    # Since the data format in the input file is elementary h264 stream,
    # we need a h264parser
    print("Creating H264Parser \n")
    h264parser = Gst.ElementFactory.make("h264parse", "h264-parser")
    if not h264parser:
        sys.stderr.write(" Unable to create h264 parser \n")

    # Use nvdec_h264 for hardware accelerated decode on GPU
    print("Creating Decoder \n")
    decoder = Gst.ElementFactory.make("nvv4l2decoder", "nvv4l2-decoder")
    if not decoder:
        sys.stderr.write(" Unable to create Nvv4l2 Decoder \n")

    # Create nvstreammux instance to form batches from one or more sources.
    streammux = Gst.ElementFactory.make("nvstreammux", "Stream-muxer")
    if not streammux:
        sys.stderr.write(" Unable to create NvStreamMux \n")

    # Use nvinfer to run inferencing on decoder's output,
    # behaviour of inferencing is set through config file
    pgie = Gst.ElementFactory.make("nvinfer", "primary-inference")
    if not pgie:
        sys.stderr.write(" Unable to create pgie \n")

    # Use convertor to convert from NV12 to RGBA as required by nvosd
    nvvidconv = Gst.ElementFactory.make("nvvideoconvert", "convertor")
    if not nvvidconv:
        sys.stderr.write(" Unable to create nvvidconv \n")

    # Create OSD to draw on the converted RGBA buffer
    nvosd = Gst.ElementFactory.make("nvdsosd", "onscreendisplay")

    if not nvosd:
        sys.stderr.write(" Unable to create nvosd \n")

    # Finally render the osd output
    if is_aarch64():
        transform = Gst.ElementFactory.make("nvegltransform", "nvegl-transform")

    print("Creating EGLSink \n")
    sink = Gst.ElementFactory.make("nveglglessink", "nvvideo-renderer")
    if not sink:
        sys.stderr.write(" Unable to create egl sink \n")
    
    tee = Gst.ElementFactory.make("tee", "nvtee")
    if not tee:
        sys.stderr.write(" Unable to create tee \n")

    queue1=Gst.ElementFactory.make("queue", "nvtee-que1")
    if not queue1:
        sys.stderr.write(" Unable to create queue1 \n")

    appsink = Gst.ElementFactory.make("appsink", "app-sink")
    if not appsink:
        sys.stderr.write(" Unable to create app sink \n")

    print("Playing file %s " %args[1])
    source.set_property('location', args[1])
    streammux.set_property('width', 1280)
    streammux.set_property('height', 720)
    streammux.set_property('batch-size', 1)
    streammux.set_property('batched-push-timeout', 4000000)
    pgie.set_property('config-file-path', "dstest1_pgie_config.txt")

    print("Adding elements to Pipeline \n")
    pipeline.add(source)
    pipeline.add(h264parser)
    pipeline.add(decoder)
    pipeline.add(streammux)
    pipeline.add(pgie)
    pipeline.add(nvvidconv)
    pipeline.add(nvosd)
    pipeline.add(sink)
    pipeline.add(tee)
    pipeline.add(appsink)
    pipeline.add(queue1)

    if is_aarch64():
        pipeline.add(transform)


    # sinkpad = streammux.get_request_pad("sink_0")
    # srcpad = decoder.get_static_pad("src")

    decoder_src_pad = decoder.get_static_pad("src")
    streammux_sink_pad = streammux.get_request_pad("sink_0")
    tee_src_pad1 = tee.get_request_pad("src_0")
    que1_sink_pad = queue1.get_static_pad("sink")
    #que1_src_pad = queue1.get_static_pad("src")
    osd_sink_pad = nvosd.get_static_pad("sink")
    tee_src_pad2 = tee.get_request_pad("src_1")
    appsink_sink_pad = appsink.get_static_pad("sink")

    if not decoder_src_pad:
        sys.stderr.write(" Unable to get source pad of decoder \n")
    if not streammux_sink_pad:
        sys.stderr.write(" Unable to get the sink pad of streammux \n")
    # if not tee_src_pad1:
    # if not osd_sink_pad:
    # if not tee_src_pad2:
    # if not appsink_sink_psd:


    # we link the elements together
    # file-source -> h264-parser -> nvh264-decoder ->
    # nvinfer -> nvvidconv -> nvosd -> video-renderer
    print("Linking elements in the Pipeline \n")
    source.link(h264parser)
    h264parser.link(decoder)

    decoder_src_pad.link(streammux_sink_pad)
    streammux.link(pgie)
    pgie.link(nvvidconv)
    nvvidconv.link(tee)
    #nvvidconv.link(nvosd)

    tee_src_pad1.link(que1_sink_pad)
    queue1.link(nvosd)

    if is_aarch64():
        nvosd.link(transform)
        transform.link(sink)
    else:
        nvosd.link(sink)

    tee_src_pad2.link(appsink_sink_pad)

    # create an event loop and feed gstreamer bus mesages to it
    loop = GObject.MainLoop()
    bus = pipeline.get_bus()
    bus.add_signal_watch()
    bus.connect ("message", bus_call, loop)

    # Lets add probe to get informed of the meta data generated, we add probe to
    # the sink pad of the osd element, since by that time, the buffer would have
    # had got all the metadata.
    #osdsinkpad = nvosd.get_static_pad("sink")
    #if not osdsinkpad:
    #    sys.stderr.write(" Unable to get sink pad of nvosd \n")

    osd_sink_pad.add_probe(Gst.PadProbeType.BUFFER, osd_sink_pad_buffer_probe, 0)

    # start play back and listen to events
    # print("Starting pipeline \n")
    # pipeline.set_state(Gst.State.PLAYING)
    # try:
    #     loop.run()
    # except:
    #     pass
    # # cleanup
    # pyds.unset_callback_funcs()
    # pipeline.set_state(Gst.State.NULL)

    ret = pipeline.set_state(Gst.State.PAUSED)
    ret = pipeline.set_state(Gst.State.PLAYING)
    # set to PAUSED to make the first frame arrive in the sink
    if ret == Gst.StateChangeReturn.FAILURE:
        sys.stderr.write("failed to play the file")
    elif ret == Gst.StateChangeReturn.NO_PREROLL:
        sys.stderr.write("live sources not supported yet")

    # /* This can block for up to 5 seconds. If your machine is really overloaded,
    # * it might time out before the pipeline prerolled and we generate an error. A
    # * better way is to run a mainloop and catch errors there. */
    # ret = pipeline.get_state(5 * Gst.SECOND)
    # if ret == Gst.StateChangeReturn.FAILURE:
    #     sys.stderr.write("failed to play the file")

    # # get the duration */
    # duration = pipeline.query_duration(Gst.Format.TIME)

    # # duration: (False, duration=-1)
    # if duration[1] != -1:
    #     # /* we have a duration, seek to 5% */
    #     position = duration * 5 / 100
    # else:
    #     # /* no duration, seek to 1 second, this could EOS */
    #     position = 1 * Gst.SECOND

    # # /* seek to the a position in the file. Most files have a black first frame so
    # # * by seeking to somewhere else we have a bigger chance of getting something
    # # * more interesting. An optimisation would be to detect black images and then
    # # * seek a little more */
    # _ = pipeline.seek_simple (Gst.Format.TIME, Gst.SeekFlags.KEY_UNIT | Gst.SeekFlags.FLUSH, position)

    # /* get the preroll buffer from appsink, this block untils appsink really
    # * prerolls */
    #print(appsink.__dict__)

    #sample = appsink.pull_preroll()
    while True:
        sample = GstApp.AppSink.pull_preroll(appsink)

        # /* if we have a buffer now, convert it to a pixbuf. It's possible that we
        # * don't have a buffer because we went EOS right away or had an error. */
        if sample:
            #     /* get the snapshot buffer format now. We set the caps on the appsink so
            #      * that it can only be an rgb buffer. The only thing we have not specified
            #      * on the caps is the height, which is dependant on the pixel-aspect-ratio
            #      * of the source material */
            caps = sample.get_caps()
            if not caps:
                sys.stderr.write("could not get snapshot format")
            s = caps.get_structure(0)
            print(s)
            #print(s.__dict__)
            buffer = sample.get_buffer()
            _map = buffer.map(Gst.MapFlags.READ) #(True, info)

            print(_map.info.data)
            print(_map.info.size)
            print(_map.info.maxsize)
            print(_map.info.user_data)
            ret = pipeline.set_state(Gst.State.READY)
        else:
            print("no sample!")
            break









if __name__ == '__main__':
    sys.exit(main(sys.argv))

