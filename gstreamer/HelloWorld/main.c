
#include <stdio.h>
#include <gst/gst.h>

int main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  gst_init(&argc, &argv);
  /*
    gst_init() must always be your first GStreamer command.
    + Initializes internal structures
    + Checks for available plugins
    + Executes any command-line option intended for GStreamer
    passing argc and argv to GStreamer will make your application
    benefit from GStreamer's standard command-line options.
  */
  pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
  /*
    gst_parse_launch() builds a template pipeline instead of
    building every element of the pipeline by itself. In this
    particular case we are building a playbin pipeline, which
    acts as a source and a sink.
  */
  gst_element_set_state(pipeline, GST_STATE_PLAYING);
  /*
    GStreamer Play/Pause button kinda
  */
  bus = gst_element_get_bus(pipeline);
  /*
    Retrieve pipelines bus
  */
  msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
  /*
    Blocks until you recieve an ERROR or an EOS (End Of Stream) kinda
  */
  if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
    g_error("ERROR: Re-run with the GST_DEBUG=*:WARN environment variable set for mode details.");
  }
  gst_message_unref(msg);
  gst_object_unref(bus);
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
  /*
    Cleanup code
  */
  return 0;
}
