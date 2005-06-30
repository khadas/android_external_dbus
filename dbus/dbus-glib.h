/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-glib.h GLib integration
 *
 * Copyright (C) 2002, 2003  CodeFactory AB
 * Copyright (C) 2003, 2004 Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#ifndef DBUS_GLIB_H
#define DBUS_GLIB_H

#include <glib-object.h>
#include <dbus/dbus-shared.h>

G_BEGIN_DECLS

#define DBUS_INSIDE_DBUS_GLIB_H 1


/**
 * Convert to DBusConnection with dbus_g_connection_get_connection() in dbus-glib-lowlevel.h
 */
typedef struct _DBusGConnection DBusGConnection;
/**
 * Convert to DBusMessage with dbus_g_message_get_message() in dbus-glib-lowlevel.h
 */
typedef struct _DBusGMessage DBusGMessage;
/**
 * Deliberately not possible to convert to DBusPendingCall
 */
typedef struct _DBusGPendingCall DBusGPendingCall;

typedef void (* DBusGPendingCallNotify) (DBusGPendingCall *pending,
                                         void             *user_data);


#define DBUS_TYPE_G_CONNECTION   (dbus_g_connection_get_g_type ())
#define DBUS_TYPE_G_MESSAGE      (dbus_g_message_get_g_type ())
#define DBUS_TYPE_G_PENDING_CALL (dbus_g_message_get_g_type ())
GType dbus_g_connection_get_g_type   (void) G_GNUC_CONST;
GType dbus_g_message_get_g_type      (void) G_GNUC_CONST;
GType dbus_g_pending_call_get_g_type (void) G_GNUC_CONST;


DBusGConnection*  dbus_g_connection_ref          (DBusGConnection        *connection);
void              dbus_g_connection_unref        (DBusGConnection        *connection);
DBusGPendingCall* dbus_g_pending_call_ref        (DBusGPendingCall       *call);
void              dbus_g_pending_call_unref      (DBusGPendingCall       *call);
DBusGMessage*     dbus_g_message_ref             (DBusGMessage           *message);
void              dbus_g_message_unref           (DBusGMessage           *message);

void              dbus_g_connection_flush        (DBusGConnection        *connection);

void              dbus_g_pending_call_set_notify (DBusGPendingCall       *call,
                                                  DBusGPendingCallNotify  callback,
                                                  void                   *callback_data,
                                                  GDestroyNotify          free_data_func);
void              dbus_g_pending_call_cancel     (DBusGPendingCall       *call);


GQuark dbus_g_error_quark (void);
#define DBUS_GERROR dbus_g_error_quark ()

typedef enum
{
#include <dbus/dbus-glib-error-enum.h>    
} DBusGError;

gboolean         dbus_g_error_has_name    (GError      *error,
					   const char  *name);
const char *     dbus_g_error_get_name    (GError      *error);

void             dbus_g_thread_init (void);
DBusGConnection* dbus_g_bus_get     (DBusBusType   type,
                                     GError      **error);

typedef struct _DBusGObjectInfo DBusGObjectInfo;
typedef struct _DBusGMethodInfo DBusGMethodInfo;

/**
 * Object typically generated by dbus-binding-tool that
 * stores a mapping from introspection data to a
 * function pointer for a C method to be invoked.
 */
struct _DBusGMethodInfo
{
  GCallback                 function;    /**< C method to invoke */
  GClosureMarshal           marshaller;  /**< Marshaller to invoke method */
  int                       data_offset; /**< Offset into the introspection data */
};

/**
 * Introspection data for a GObject, normally autogenerated by
 * a tool such as dbus-binding-tool.
 */
struct _DBusGObjectInfo
{
  int   format_version;         /**< Allows us to change the rest of this struct
                                 *   by adding DBusGObjectInfo2, DBusGObjectInfo3, etc.
                                 */
  const DBusGMethodInfo *method_infos; /**< Array of method pointers */
  int   n_method_infos;                /**< Length of the infos array */
  const char *data;             /**< Introspection data */
  const char *exported_signals;  /**< Exported signals */
  const char *exported_properties;  /**< Exported properties */
};

void       dbus_g_object_type_install_info     (GType                 object_type,
                                                const DBusGObjectInfo *info);

void       dbus_g_error_domain_register        (GQuark                domain,
						const char *          default_iface,
						GType                 code_enum);

void       dbus_g_connection_register_g_object (DBusGConnection       *connection,
						const char            *at_path,
						GObject               *object);
GObject *  dbus_g_connection_lookup_g_object   (DBusGConnection       *connection,
						const char            *at_path);


/**
 * Generic recursive value
 */

typedef struct _DBusGValueIterator DBusGValueIterator;
struct _DBusGValueIterator
{
  void *dummy1;         /**< Don't use this */
  void *dummy2;         /**< Don't use this */
  guint32 dummy3;     /**< Don't use this */
  int dummy4;           /**< Don't use this */
  int dummy5;           /**< Don't use this */
  int dummy6;           /**< Don't use this */
  int dummy7;           /**< Don't use this */
  int dummy8;           /**< Don't use this */
  int dummy9;           /**< Don't use this */
  int dummy10;          /**< Don't use this */
  int dummy11;          /**< Don't use this */
  int pad1;             /**< Don't use this */
  int pad2;             /**< Don't use this */
  void *pad3;           /**< Don't use this */
  void *pad4;           /**< Don't use this */
  void *pad5;           /**< Don't use this */
};

typedef struct _DBusGValue DBusGValue;

#ifdef DBUS_COMPILATION
#include "glib/dbus-gtype-specialized.h"
#else
#include <dbus/dbus-gtype-specialized.h>
#endif

/* definitions for some basic array types */
#define DBUS_TYPE_G_BOOLEAN_ARRAY  (dbus_g_type_get_collection ("GArray", G_TYPE_BOOLEAN))
#define DBUS_TYPE_G_UCHAR_ARRAY    (dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR))
#define DBUS_TYPE_G_UINT_ARRAY     (dbus_g_type_get_collection ("GArray", G_TYPE_UINT))
#define DBUS_TYPE_G_INT_ARRAY      (dbus_g_type_get_collection ("GArray", G_TYPE_INT))
#define DBUS_TYPE_G_UINT64_ARRAY   (dbus_g_type_get_collection ("GArray", G_TYPE_UINT64))
#define DBUS_TYPE_G_INT64_ARRAY    (dbus_g_type_get_collection ("GArray", G_TYPE_INT64))
#define DBUS_TYPE_G_OBJECT_ARRAY   (dbus_g_type_get_collection ("GPtrArray", G_TYPE_OBJECT))

#define DBUS_TYPE_G_STRING_STRING_HASHTABLE (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_STRING))

/* Generic recursive value */
GType        dbus_g_value_get_g_type               (void) G_GNUC_CONST;
#define DBUS_TYPE_G_VALUE                (dbus_g_value_get_g_type ())

GType        dbus_g_object_path_get_g_type         (void) G_GNUC_CONST;
#define DBUS_TYPE_G_OBJECT_PATH (dbus_g_object_path_get_g_type ())

void         dbus_g_value_open              (DBusGValue          *value,
					     DBusGValueIterator  *iter);

GType        dbus_g_value_iterator_get_value        (DBusGValueIterator   *iter,
						     GValue               *value);

gboolean     dbus_g_value_iterator_get_values       (DBusGValueIterator   *iter,
						     GError              **error,
						     GValue               *first_val,
						     ...);

void         dbus_g_value_iterator_recurse          (DBusGValueIterator   *iter,
						     DBusGValueIterator   *sub);

void         dbus_g_value_free                      (DBusGValue          *value);


void         dbus_g_object_register_marshaller      (GClosureMarshal  marshaller,
						     GType            rettype,
						     ...);
void         dbus_g_object_register_marshaller_array(GClosureMarshal  marshaller,
						     GType            rettype,
						     guint            n_types,
						     const GType*     types);

typedef struct _DBusGProxy       DBusGProxy;
typedef struct _DBusGProxyClass  DBusGProxyClass;

#define DBUS_TYPE_G_PROXY              (dbus_g_proxy_get_type ())
#define DBUS_G_PROXY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), DBUS_TYPE_G_PROXY, DBusGProxy))
#define DBUS_G_PROXY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), DBUS_TYPE_G_PROXY, DBusGProxyClass))
#define DBUS_IS_G_PROXY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), DBUS_TYPE_G_PROXY))
#define DBUS_IS_G_PROXY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), DBUS_TYPE_G_PROXY))
#define DBUS_G_PROXY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), DBUS_TYPE_G_PROXY, DBusGProxyClass))


GType             dbus_g_proxy_get_type              (void) G_GNUC_CONST;
DBusGProxy*       dbus_g_proxy_new_for_name          (DBusGConnection   *connection,
                                                      const char        *name,
                                                      const char        *path,
                                                      const char        *interface);
DBusGProxy*       dbus_g_proxy_new_for_name_owner    (DBusGConnection   *connection,
                                                      const char        *name,
                                                      const char        *path,
                                                      const char        *interface,
                                                      GError           **error);
DBusGProxy*       dbus_g_proxy_new_from_proxy        (DBusGProxy        *proxy,
                                                      const char        *interface,
                                                      const char        *path_name);
DBusGProxy*       dbus_g_proxy_new_for_peer          (DBusGConnection   *connection,
                                                      const char        *path_name,
                                                      const char        *interface_name);

void              dbus_g_proxy_set_interface         (DBusGProxy        *proxy,
						      const char        *interface_name);
void              dbus_g_proxy_add_signal            (DBusGProxy        *proxy,
						      const char        *signal_name,
						      GType              first_type, 
						      ...);

void              dbus_g_proxy_connect_signal        (DBusGProxy        *proxy,
                                                      const char        *signal_name,
                                                      GCallback          handler,
                                                      void              *data,
                                                      GClosureNotify     free_data_func);
void              dbus_g_proxy_disconnect_signal     (DBusGProxy        *proxy,
                                                      const char        *signal_name,
                                                      GCallback          handler,
                                                      void              *data);

gboolean          dbus_g_proxy_call                  (DBusGProxy        *proxy,
						      const char        *method,
						      GError           **error,
						      GType              first_arg_type,
						      ...);

void              dbus_g_proxy_call_no_reply         (DBusGProxy        *proxy,
                                                      const char        *method,
                                                      GType              first_arg_type,
                                                      ...);

DBusGPendingCall* dbus_g_proxy_begin_call            (DBusGProxy        *proxy,
                                                      const char        *method,
                                                      GType              first_arg_type,
                                                      ...);
gboolean          dbus_g_proxy_end_call              (DBusGProxy        *proxy,
                                                      DBusGPendingCall  *pending,
                                                      GError           **error,
                                                      GType              first_arg_type,
                                                      ...);

const char*       dbus_g_proxy_get_path              (DBusGProxy        *proxy);

const char*       dbus_g_proxy_get_bus_name          (DBusGProxy        *proxy);

const char*       dbus_g_proxy_get_interface         (DBusGProxy        *proxy);

typedef struct _DBusGMethodInvocation DBusGMethodInvocation;

void              dbus_g_method_return               (DBusGMethodInvocation *context, ...);

void              dbus_g_method_return_error         (DBusGMethodInvocation *context, GError *error);

typedef struct {
  DBusGProxy *proxy;
  gpointer cb;
  gpointer userdata;
} DBusGAsyncData;

#undef DBUS_INSIDE_DBUS_GLIB_H

G_END_DECLS

#endif /* DBUS_GLIB_H */



