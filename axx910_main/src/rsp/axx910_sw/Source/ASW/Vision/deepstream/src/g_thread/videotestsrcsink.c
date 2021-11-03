#include <gst/gst.h>
#include <signal.h>

struct AppCtx {
    int argc;
    char **argv;
    GMainContext *context;
    int cnt;
    gboolean timeout;
    int ThreadReturnValue;
    gboolean quit; 
};

struct AppCtx appCtx;
static GMainLoop *loop;
static GstElement *pipeline;

static gboolean
my_bus_callback (GstBus *bus, GstMessage *message, gpointer data);

gpointer event_loop_thread(gpointer arg) {
  struct AppCtx *appCtx = (struct AppCtx *)arg;

  GstElement *source, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GMainLoop *main_loop;
  gboolean terminate = FALSE;
  guint bus_watch_id;

  /* Initialize GStreamer */
  gst_init (&(appCtx->argc), &(appCtx->argv));

  loop = g_main_loop_new(appCtx->context, FALSE);
  g_main_context_push_thread_default(appCtx->context);

  /* Create the elements */
  source = gst_element_factory_make ("videotestsrc", "source");
  sink = gst_element_factory_make ("autovideosink", "sink");

  /* Create the empty pipeline */
  pipeline = gst_pipeline_new ("test-pipeline");

  if (!pipeline || !source || !sink) {
    g_printerr ("Not all elements could be created.\n");
    appCtx->ThreadReturnValue = -1;
  }

  /* Build the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), source, sink, NULL);
  if (gst_element_link (source, sink) != TRUE) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    appCtx->ThreadReturnValue = -1;
  }

  /* Modify the source's properties */
  g_object_set (source, "pattern", 0, NULL);

  /* Start playing */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    appCtx->ThreadReturnValue = -1;
  }

  /* Wait until error or EOS */
  bus = gst_pipeline_get_bus (GST_PIPELINE(pipeline));
  bus_watch_id = gst_bus_add_watch (bus, my_bus_callback, NULL);
  gst_object_unref(bus);

  g_main_loop_run (loop);

  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  g_source_remove (bus_watch_id);
  g_main_loop_unref (loop);
  appCtx->quit = TRUE;

  return NULL;
}

static gboolean
my_bus_callback (GstBus *bus, GstMessage *msg, gpointer data) 
{
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_STATE_CHANGED:
      /* We are only interested in state-changed messages from the pipeline */
      if (GST_MESSAGE_SRC (msg) == GST_OBJECT (pipeline)) {
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
        g_print ("Pipeline state changed from %s to %s:\n",
            gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
      }
      break;
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug_info;
      gst_message_parse_error (msg, &err, &debug_info);
      g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
      g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
      g_clear_error (&err);
      g_free (debug_info);
      g_main_loop_quit(loop);
      break;
    }
    case GST_MESSAGE_EOS:
      g_print ("End-Of-Stream reached.\n");
      g_main_loop_quit(loop);
      break;
    default:
      /* We should not reach here because we only asked for ERRORs and EOS */
      g_printerr ("Unexpected message received.\n");
      break;
  }
  return TRUE;
}

int init(struct AppCtx* appCtx)
{
    appCtx->context = g_main_context_default();
    g_thread_new(NULL, event_loop_thread, (gpointer)appCtx);
    return 0;
}


void intHandler(int dummy) {
    g_print("intHandler called.\n");
    appCtx.quit = TRUE;
}


int main(int argc, char *argv[])
{
    appCtx.argc = argc;
    appCtx.argv = argv;
    appCtx.cnt = 0;
    appCtx.quit = FALSE;

    init(&appCtx);

    signal(SIGINT, intHandler);
    while (!appCtx.quit);    
    g_print("quit\n");

    return 0;
} 