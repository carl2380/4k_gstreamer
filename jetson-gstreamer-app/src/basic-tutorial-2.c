#include <gst/gst.h>
#include <glib.h>

int main(int argc, char *argv[]) {


    /* 初始化 GStreamer */
    gst_init(&argc, &argv);

    /* 创建 GStreamer 元素 */
    GstElement *source = gst_element_factory_make("v4l2src", "source");
    GstElement *convert = gst_element_factory_make("videoconvert", "convert");
    GstElement *sink = gst_element_factory_make("autovideosink", "sink");

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

    /* 设置摄像头设备 */
    g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);

    /* 组装管道 */
    gst_bin_add_many(GST_BIN(pipeline), source, convert, sink, NULL);
    if (!gst_element_link_many(source, convert, sink, NULL)) {
        g_printerr("GStreamer 元素连接失败\n");
        gst_object_unref(pipeline);
        return -1;
    }

    /* 启动管道 */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* 监听总线消息，等待 EOS（End Of Stream） 或者错误 */
    GstBus *bus;
    GstMessage *msg;
    GError *error = NULL;
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* 处理消息 */
    if (msg != NULL) {
        gst_message_parse_error(msg, &error, NULL);
        g_printerr("GStreamer 运行错误: %s\n", error->message);
        g_clear_error(&error);
        gst_message_unref(msg);
    }

    /* 释放资源 */
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
