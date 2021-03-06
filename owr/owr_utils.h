/*
 * Copyright (c) 2014-2015, Ericsson AB. All rights reserved.
 * Copyright (c) 2014, Centricular Ltd
 *     Author: Sebastian Dröge <sebastian@centricular.com>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */

#ifndef __OWR_UTILS_H__
#define __OWR_UTILS_H__

#include "owr_types.h"

#include <glib.h>
#include <gst/gst.h>

#ifndef __GTK_DOC_IGNORE__

G_BEGIN_DECLS

#define OWR_UNUSED(x) (void)x

#define _owr_codec_type_is_raw(codec_type) (codec_type == OWR_CODEC_TYPE_NONE)

void *_owr_require_symbols(void);
guint _owr_get_unique_uint_id();
OwrCodecType _owr_caps_to_codec_type(GstCaps *caps);
const gchar* _owr_codec_type_to_caps_mime(OwrMediaType media_type, OwrCodecType codec_type);
gpointer _owr_detect_codecs(gpointer data);
const GList *_owr_get_detected_h264_encoders();
const GList *_owr_get_detected_vp8_encoders();
GstElement *_owr_try_codecs(const GList *codecs, const gchar *name_prefix);
GstElement *_owr_create_decoder(OwrCodecType codec_type);
GstElement *_owr_create_parser(OwrCodecType codec_type);
const gchar* _owr_get_encoder_name(OwrCodecType codec_type);
void _owr_bin_link_and_sync_elements(GstBin *bin, gboolean *out_link_ok, gboolean *out_sync_ok, GstElement **out_first, GstElement **out_last);
void _owr_utils_call_closure_with_list(GClosure *callback, GList *list);
GClosure *_owr_utils_list_closure_merger_new(GClosure *final_callback,
    GCopyFunc list_item_copy,
    GDestroyNotify list_item_destroy);

/* FIXME: This should be removed when the GStreamer required version
 * is 1.6 and gst_caps_foreach() can be used.
 * Upstream commit: http://cgit.freedesktop.org/gstreamer/gstreamer/commit/?id=bc11a1b79dace8ca73d3367d7c70629f8a6dd7fd
 * The author of the above commit, Sebastian Dröge, agreed
 * relicensing this copy of the function under BSD 2-Clause. */
typedef gboolean (*OwrGstCapsForeachFunc) (GstCapsFeatures *features,
                                           GstStructure    *structure,
                                           gpointer         user_data);
gboolean _owr_gst_caps_foreach(const GstCaps *caps, OwrGstCapsForeachFunc func, gpointer user_data);

void _owr_deep_notify(GObject *object, GstObject *orig,
    GParamSpec *pspec, gpointer user_data);

void _owr_update_flip_method(GObject *renderer, GParamSpec *pspec, GstElement *flip);

GHashTable *_owr_value_table_new();
GValue *_owr_value_table_add(GHashTable *table, const gchar *key, GType type);

G_END_DECLS

#endif /* __GTK_DOC_IGNORE__ */

#endif /* __OWR_UTILS_H__ */
