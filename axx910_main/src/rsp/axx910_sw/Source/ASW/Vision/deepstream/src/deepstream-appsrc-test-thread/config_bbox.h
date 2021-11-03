#ifndef __CONFIG_BBOX_H__
#define __CONFIG_BBOX_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include <gst/gst.h>
#include "gstnvdsmeta.h"

#define GROUP        "bbox"
#define BORDER_WIDTH "border-width"
#define BORDER_COLOR "border-color"

typedef struct
{
        gint               border_width      ;
        NvOSD_ColorParams  border_color      ;
        GHashTable        *border_color_table;
} BboxConfig;

static int
parse_border_color (BboxConfig *config, GKeyFile *key_file, gchar *key) 
{
        NvOSD_ColorParams *clr_params;
        gchar *class_id = key + sizeof(BORDER_COLOR) - 1;
        gchar *endptr;
        gint64 class_index = -1;
        GError *error = NULL;

        /* Check if the key is specified for a particular class or for all classes.
        * For generic key "bbox-border-color", strlen (key1) will return 0 and·
        * class_index will be -1.
        * For class-specific key "bbox-border-color<class-id>", strlen (key1)
        * will return a positive value and·class_index will have a value >= 0.
        */
        if (strlen(class_id) > 0) {
                class_index = g_ascii_strtoll(class_id, &endptr, 10);
                if (class_index == 0 && endptr == class_id) {
                        NVGSTDS_WARN_MSG_V("BBOX colors should be specified with key '%s%%d'", BORDER_COLOR);
                        return -1; 
                }
        }

        gsize length;
        gdouble *list = g_key_file_get_double_list(key_file, GROUP, key, &length, &error);

        if (error) {
                g_print ("%s", error->message);
                return -1;
        }
        if (length != 4) {
                NVGSTDS_ERR_MSG_V("Number of Color params should be exactly 4 "
                                        "floats {r, g, b, a} between 0 and 1");
                return -1;
        }

        if (class_index == -1) {
                clr_params = &(config->border_color);
        }
        else {
                clr_params = (NvOSD_ColorParams *)g_malloc(sizeof(NvOSD_ColorParams));
                g_hash_table_insert(config->border_color_table,
                                        class_index + (gchar *)NULL, clr_params);
        }

        clr_params->red = list[0];
        clr_params->green = list[1];
        clr_params->blue = list[2];
        clr_params->alpha = list[3];
        return 0;
}

gboolean
config_bbox_parse (BboxConfig *config, gchar *cfg_file_path)
{
        gboolean ret = FALSE;
        gchar **keys = NULL;
        gchar **key = NULL;
        GError *error = NULL;
        GKeyFile *key_file = NULL;
        gchar **groups = NULL;
        gchar **group;

        key_file = g_key_file_new();

        if (!g_key_file_load_from_file(key_file, cfg_file_path, G_KEY_FILE_NONE, &error)) {
                g_print("Failed to load uri file: %s", error->message);
                goto done;
        }

        groups = g_key_file_get_groups(key_file, NULL);
        for (group = groups; *group; group++) {
                if (!g_strcmp0(*group, GROUP)) {
                        break;
                }
        }
        if (group == NULL) { 
                g_print("Can't find %s group in config file: %s", GROUP, error->message);
                goto done;
        }

        keys = g_key_file_get_keys(key_file, GROUP, NULL, &error);

        config->border_color_table = g_hash_table_new(NULL, NULL);

        CHECK_ERROR(error);
        for (key = keys; *key; key++) {
                if (!g_strcmp0(*key, BORDER_WIDTH)) {
                        config->border_width = g_key_file_get_integer(key_file, GROUP, BORDER_WIDTH, &error);
                }
                else if (!strncmp(*key, BORDER_COLOR, sizeof(BORDER_COLOR) - 1)) {
                        if (-1 == parse_border_color (config, key_file, *key) ) {
                                goto done;
                        }
                }
        }

        ret = TRUE;
done:
        if (error)
        {
                g_error_free(error);
        }
        if (keys)
        {
                g_strfreev(keys);
        }
        if (!ret)
        {
                NVGSTDS_ERR_MSG_V("%s failed", __func__);
        }
        return ret;
        if (key_file)
        {
                g_key_file_free(key_file);
        }
}

#ifdef __cplusplus
}
#endif

#endif