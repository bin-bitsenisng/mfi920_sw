#include <gst/gst.h>

typedef struct
{
        GMainContext *context;
        GSource *timeout_source;
        gint count;
} ContextData;

gboolean
callback_timeout(gpointer user_data)
{
        ContextData *ctxData = (ContextData *)user_data;
        ctxData->count +=1;
        g_print ("count: %d\n", ctxData->count);
        g_main_context_wakeup (ctxData->context);
        return G_SOURCE_CONTINUE;
}

int main(void)
{
        ContextData ctxData;
        gint source_id = 0;
        ctxData.count = 0;
        ctxData.context = g_main_context_new();

        ctxData.timeout_source = g_timeout_source_new_seconds (1);
        source_id = g_source_attach (ctxData.timeout_source, ctxData.context);
        g_source_set_callback (ctxData.timeout_source, callback_timeout, &ctxData, NULL);
        // g_timeout_add_seconds(5, callback_timeout, &ctxData); when GMainLoop exist

        while (ctxData.count < 5)
        {
                g_print("g_main_context_iteration\n");
                g_main_context_iteration(ctxData.context, TRUE);
        }

        return 0;
}