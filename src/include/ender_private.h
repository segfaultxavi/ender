/* ENDER - Enesim's descriptor library
 * Copyright (C) 2010 Jorge Luis Zapata
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 * If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _ENDER_PRIVATE_H
#define _ENDER_PRIVATE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define BUILD_SERIALIZE 1

#include <dlfcn.h>

/* core */
#define ERR(...) EINA_LOG_DOM_ERR(ender_log_dom, __VA_ARGS__)
#define WRN(...) EINA_LOG_DOM_WARN(ender_log_dom, __VA_ARGS__)
#define INF(...) EINA_LOG_DOM_INFO(ender_log_dom, __VA_ARGS__)
#define DBG(...) EINA_LOG_DOM_DBG(ender_log_dom, __VA_ARGS__)
extern int ender_log_dom;

#if BUILD_SERIALIZE
typedef struct _Ender_Container_Serialize
{
	char *signature;
	Eina_Bool external;
} Ender_Container_Serialize;
#endif

struct _Ender_Container
{
	/* common */
	char *registered_name;
	Ender_Value_Type type;
	int ref;
	/* structs */
	int num_elements;
	Eina_List *elements;
	/* relative to a parent container */
#if BUILD_SERIALIZE
	Ender_Container_Serialize serialize;
#endif
};

struct _Ender_Value
{
	Ender_Container *container;
	int ref;
	Ender_Value_Free free_cb;
	void *free_cb_data;
	Eina_Bool owned;
	union {
		int32_t i32;
		uint32_t u32;
		int64_t i64;
		uint64_t u64;
		double d;
		void *ptr;
		Enesim_Matrix matrix;
	} data;
};

struct _Ender_Descriptor
{
	char *name;
	Ender_Descriptor_Type type;
	Ender_Descriptor *parent;
	Ender_Creator create;
	Ender_Destructor destroy;
	Eina_Ordered_Hash *properties;
	Ender_Namespace *ns;
};

/* descriptor */
Ender_Descriptor * ender_descriptor_new(const char *name, Ender_Namespace *ns,
		Ender_Creator creator,
		Ender_Destructor destructor,
		Ender_Descriptor *parent, Ender_Descriptor_Type type);
void ender_descriptor_free(Ender_Descriptor *thiz);
const char * ender_descriptor_name_get(Ender_Descriptor *edesc);
void * ender_descriptor_object_create(Ender_Descriptor *thiz);
void ender_descriptor_object_destroy(Ender_Descriptor *thiz, void *object);
Ender_Descriptor * ender_descriptor_find(const char *name);
void ender_descriptor_init(void);
void ender_descriptor_shutdown(void);

/* property */
typedef void (*Ender_Property_Accessor)(Ender_Property *ep, Ender_Element *e, Ender_Value *v, void *data);
typedef Eina_Bool (*Ender_Property_Is_Set)(Ender_Property *ep, Ender_Element *e, void *data);
typedef Ender_Property_Accessor Ender_Property_Getter;
typedef Ender_Property_Accessor Ender_Property_Setter;
typedef Ender_Property_Accessor Ender_Property_Add;
typedef Ender_Property_Accessor Ender_Property_Remove;
typedef void (*Ender_Property_Clear)(Ender_Property *ep, Ender_Element *e, void *data);
typedef void (*Ender_Property_Free)(void *data);
Ender_Property * ender_property_new(const char *name,
		Ender_Container *ec,
		Ender_Property_Getter get,
		Ender_Property_Setter set,
		Ender_Property_Add add,
		Ender_Property_Remove remove,
		Ender_Property_Clear clear,
		Ender_Property_Is_Set is_set,
		Eina_Bool relative,
		Ender_Property_Free free,
		void *data);
void ender_property_free(Ender_Property *p);

void ender_property_element_value_set(Ender_Property *ep, Ender_Element *e,
		Ender_Value *v);
void ender_property_element_value_get(Ender_Property *ep, Ender_Element *e,
		Ender_Value *v);
void ender_property_element_value_add(Ender_Property *ep, Ender_Element *e,
		Ender_Value *v);
void ender_property_element_value_remove(Ender_Property *ep, Ender_Element *e,
		Ender_Value *v);
void ender_property_element_value_clear(Ender_Property *ep, Ender_Element *e);
Eina_Bool ender_property_element_value_is_set(Ender_Property *ep, Ender_Element *e);
/* container */
void ender_container_init(void);
void ender_container_shutdown(void);

/* namespace */
typedef void (*Ender_Namespace_Initialize)(Ender_Namespace *thiz, void *data);
void ender_namespace_initialize_cb_set(Ender_Namespace *thiz, Ender_Namespace_Initialize cb, void *data);
void ender_namespace_init(void);
void ender_namespace_shutdown(void);
void ender_namespace_dump(Ender_Namespace *ns);
Ender_Element * ender_namespace_element_new_from_descriptor(Ender_Namespace *thiz, Ender_Descriptor *desc);

/* element */
Ender_Element * ender_element_new(Ender_Descriptor *d);

/* the loader */
void ender_loader_init(void);
void ender_loader_shutdown(void);
void ender_loader_load_all(void);

/* the parser */
typedef struct _Ender_Parser
{
	const char *file;
	Ender_Parser_Descriptor *descriptor;
	void *data;
} Ender_Parser;

typedef struct _Ender_Parser_Type
{
	char *name;
	Ender_Container *container;
} Ender_Parser_Type;


#endif
