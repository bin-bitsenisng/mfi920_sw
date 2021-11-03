#include <glib.h>

GMainLoop *loop;

struct AppCtx {
    GMainContext *context;
    int cnt;
    gboolean timeout;
};

gboolean timeout_cb(gpointer _data)
{
    struct AppCtx *appCtx = (struct AppCtx*) _data;
    int *cnt = &(appCtx->cnt);
    gboolean *timeout = &(appCtx->timeout);

    g_message("(timeout cb) in thread: %p", g_thread_self());
    g_print("cnt: %d %d\n",appCtx->cnt, (*cnt));

    (*cnt)++;
    if (*cnt > 5)
    {
        (*timeout) = TRUE;
        return FALSE;
    }

    return TRUE;
}

gpointer event_loop_thread(gpointer arg)
{   
    struct AppCtx *appCtx = (struct AppCtx *)arg;

    loop = g_main_loop_new(appCtx->context, FALSE);
    g_main_context_push_thread_default(appCtx->context);
    g_timeout_add_seconds(2, timeout_cb, appCtx);
    g_main_loop_run(loop);
    g_main_loop_unref(loop);
    return NULL;
}

int init(struct AppCtx* appCtx)
{
    appCtx->context = g_main_context_default();
    g_thread_new(NULL, event_loop_thread, (gpointer)appCtx);
    return 0;
}

int main()
{
    struct AppCtx appCtx;
    appCtx.cnt = 0;
    appCtx.timeout = FALSE;

    init(&appCtx);

    while (!appCtx.timeout);
    g_print("quit\n");

    return 0;

} 
