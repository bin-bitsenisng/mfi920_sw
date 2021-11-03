#include "elements_factory.h"

int 
get_element (
    GstElement **element,
    const gchar *factoryname,
    const gchar *name
)
{
    if ( factoryname == "pipeline" ) {
        *element = gst_pipeline_new (name);
    }
    *element = gst_element_factory_make (factoryname, name);

    if (!*element) 
    { 
        g_printerr ("%s could not be created. Exiting.\n", factoryname); 
        return -1; 
    }
    return 0;
}
