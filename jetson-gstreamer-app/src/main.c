#include <gst/gst.h>
// #include <gst/video/video.h>
// #include <gst/gl/gl.h>

int main(int argc, char *argv[]) {
    // Initialize GStreamer
    gst_init(&argc, &argv);

    // Create the pipeline
    GstElement *source = gst_element_factory_make("v4l2src", "video-source");
    GstElement *convert = gst_element_factory_make("videoconvert", "video-convert");
    GstElement *sink = gst_element_factory_make("glimagesink", "video-sink");

    /* 检查元素是否创建成功 */
    if (!source || !convert || !sink) {
        g_printerr("无法创建 GStreamer 元素\n");
        return -1;
    }

    /* 创建 GStreamer 管道 */
    GstElement *pipeline = gst_pipeline_new("video-pipeline");
    if (!pipeline) {
        g_printerr("无法创建 GStreamer 管道\n");
        return -1;
    }

    // Set the properties for the source
    g_object_set(source, "device", "/dev/video0", NULL);

    // Build the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, convert, sink, NULL);
    if (gst_element_link_many(source, convert, sink, NULL) != TRUE) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;  
    }

    // Start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Wait until error or EOS
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
        GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // Free resources
    if (msg != NULL) {
        gst_message_unref(msg);
    }
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
