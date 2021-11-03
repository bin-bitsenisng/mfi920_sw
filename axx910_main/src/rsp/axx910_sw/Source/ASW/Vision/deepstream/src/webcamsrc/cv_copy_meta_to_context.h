#ifndef __CV_COPY_META_TO_CONTEXT_H__
#define __CV_COPY_META_TO_CONTEXT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <gst/gst.h>
#include "context_vision.h"
#include <nvbufsurface.h>

gboolean
copy_meta_to_context (VisionCtx *viCtx, NvDsBatchMeta *batch_meta, NvBufSurface *surface);

#ifdef __cplusplus
}
#endif

#endif
