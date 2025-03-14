#include <gst/gst.h>
// #include <gst/video/video.h>
// #include <gst/gl/gl.h>

int main(int argc, char *argv[]) {
    // Initialize GStreamer
    gst_init(&argc, &argv);

    // Create the pipeline
    GstElement *pipeline = gst_pipeline_new("video-pipeline-pipeline");
    GstElement *source = gst_element_factory_make("v4l2src", "camera-source");
    GstElement *filter = gst_element_factory_make("video/x-raw,format=YUV,width=1920,height=2160", "video-filter");
    GstElement *sink = gst_element_factory_make("glimagesink", "video-sink");

    if (!pipeline ) {
        g_printerr("pipeline could be created.\n");
        return -1;
    }

    if (!source ) {
        g_printerr("source could be created.\n");
        return -1;
    }

    if (!filter ) {
        g_printerr("filter could be created.\n");
        return -1;
    }

    if (!sink) {
        g_printerr("sink could be created.\n");
        return -1;
    }


    // Set the properties for the source
    g_object_set(source, "framerate", 30, NULL);

    // Build the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, filter, sink, NULL);
    if (gst_element_link_many(source, filter, sink, NULL) != TRUE) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // Start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Wait until error or EOS
    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // Free resources
    if (msg != NULL) {
        gst_message_unref(msg);
    }
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}