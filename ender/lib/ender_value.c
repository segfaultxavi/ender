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
#include "Ender.h"
#include "ender_private.h"
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
static Ender_Value * _ender_value_new(Ender_Container *ec)
{
	Ender_Value *thiz;

	thiz = calloc(1, sizeof(Ender_Value));
	thiz->container = ec;
	thiz->ref++;

	return thiz;
}

static void _ender_value_free(Ender_Value *thiz)
{
	if (thiz->owned)
	{
		free(thiz->data.ptr);
	}
	else if (thiz->free_cb)
	{
		thiz->free_cb(thiz, thiz->free_cb_data);
	}
	free(thiz);
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value * ender_value_basic_new(Ender_Value_Type type)
{
	Ender_Container *ec;

	if (type == ENDER_LIST || type == ENDER_STRUCT)
		return NULL;

	ec = ender_container_new(type);
	return _ender_value_new(ec);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value * ender_value_new_container_from(Ender_Container *ec)
{
	return _ender_value_new(ec);
}


/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value * ender_value_new_container_static_from(Ender_Container *ec)
{
	Ender_Value *thiz;

	thiz = _ender_value_new(ec);
	/* for structs and unions get the size of the native object */
	if (ec->type == ENDER_UNION || ec->type == ENDER_STRUCT)
	{
		const Ender_Constraint *cnst;
		Ender_Constraint_Type cnst_type;
		Ender_Descriptor *descriptor;
		size_t size;

		cnst = ender_container_constraint_get(ec);
		if (!cnst) return thiz;

		cnst_type = ender_constraint_type_get(cnst);
		if (cnst_type != ENDER_CONSTRAINT_DESCRIPTOR)
			return thiz;
		descriptor = ender_constraint_descriptor_descriptor_get(cnst);
		if (!descriptor)
			return thiz;

		size = ender_descriptor_size_get(descriptor);
		if (!size) return thiz;

		thiz->data.ptr = calloc(1, size);
		thiz->owned = EINA_TRUE;
	}
	return thiz;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value * ender_value_list_new(Ender_Container *child)
{
	Ender_Container *ec;

	ec = ender_container_list_new(child);
	return _ender_value_new(ec);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Container * ender_value_container_get(const Ender_Value *value)
{
	return value->container;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value_Type ender_value_type_get(const Ender_Value *value)
{
	return value->container->type;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_int32_set(Ender_Value *value, int32_t i32)
{
	if (value->container->type != ENDER_INT32)
		return;
	value->data.i32 = i32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI int32_t ender_value_int32_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_INT32)
		return 0;
	return value->data.i32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_uint32_set(Ender_Value *value, uint32_t u32)
{
	if (value->container->type != ENDER_UINT32)
		return;
	value->data.u32 = u32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI uint32_t ender_value_uint32_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_UINT32)
		return 0;
	return value->data.u32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_int64_set(Ender_Value *value, int64_t i64)
{
	if (value->container->type != ENDER_INT64)
		return;
	value->data.i64 = i64;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI int64_t ender_value_int64_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_INT64)
		return 0;
	return value->data.i64;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_uint64_set(Ender_Value *value, uint64_t u64)
{
	if (value->container->type != ENDER_UINT64)
		return;
	value->data.u64 = u64;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI uint64_t ender_value_uint64_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_UINT64)
		return 0;
	return value->data.u64;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_double_set(Ender_Value *value, double d)
{
	if (value->container->type != ENDER_DOUBLE)
		return;
	value->data.d = d;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI double ender_value_double_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_DOUBLE)
		return 0;
	return value->data.d;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_argb_set(Ender_Value *value, uint32_t argb)
{
	if (value->container->type != ENDER_ARGB)
		return;
	value->data.u32 = argb;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI uint32_t ender_value_argb_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_ARGB)
		return 0;
	return value->data.u32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_color_set(Ender_Value *value, uint32_t color)
{
	if (value->container->type != ENDER_COLOR)
		return;
	value->data.u32 = color;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI uint32_t ender_value_color_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_COLOR)
		return 0;
	return value->data.u32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_string_set(Ender_Value *value, char * string)
{
	if (value->container->type != ENDER_STRING)
		return;
	value->data.ptr = string;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_static_string_set(Ender_Value *value, const char * string)
{
	if (!string) return;
	if (value->container->type != ENDER_STRING)
		return;
	value->data.ptr = strdup(string);
	value->owned = EINA_TRUE;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI const char * ender_value_string_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_STRING)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_struct_set(Ender_Value *value, void *structure)
{
	if (value->container->type != ENDER_STRUCT)
		return;
	value->data.ptr = structure;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ender_value_struct_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_STRUCT)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_union_set(Ender_Value *value, int type, void *un)
{
	if (value->container->type != ENDER_UNION)
		return;
	value->data.ptr = un;
	if (un)
	{
		int *d = un;
		*d = type;
	}
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ender_value_union_get(const Ender_Value *value, int *type)
{
	int *d;
	if (value->container->type != ENDER_UNION)
		return NULL;
	d = value->data.ptr;
	if (type)
	{
		if (type) *type = *d;
	}
	return d;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_object_set(Ender_Value *value, void *object)
{
	if (value->container->type != ENDER_OBJECT)
		return;
	value->data.ptr = object;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ender_value_object_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_OBJECT)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_ender_set(Ender_Value *value, Ender_Element *ender)
{
	if (value->container->type != ENDER_ENDER)
		return;
	value->data.ptr = ender;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Element * ender_value_ender_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_ENDER)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_pointer_set(Ender_Value *value, void *ptr, Ender_Value_Free free_cb, void *user_data)
{
	if (value->container->type != ENDER_POINTER)
		return;
	value->data.ptr = ptr;
	value->free_cb = free_cb;
	value->free_cb_data = user_data;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ender_value_pointer_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_POINTER)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_list_add(Ender_Value *value, Ender_Value *child)
{
	Ender_Container *sub;

	if (value->container->type != ENDER_LIST)
		return;

	sub = ender_container_compound_get(value->container, 0, NULL);
	if (!sub)
	{
		ERR("List without sub-container");
		return;
	}
	if (sub->type == ENDER_VALUE)
	{
		value->data.ptr = eina_list_append(value->data.ptr, child);
	}
	else
	{
		printf("%s TODO\n", __FILE__);
	}
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_list_set(Ender_Value *value, Eina_List *list)
{
	if (value->container->type != ENDER_LIST)
		return;
	value->data.ptr = list;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI const Eina_List * ender_value_list_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_LIST)
		return NULL;
	return value->data.ptr;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Eina_Bool ender_value_bool_get(const Ender_Value *value)
{
	if (value->container->type != ENDER_BOOL)
		return EINA_FALSE;
	return value->data.u32;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_bool_set(Ender_Value *value, Eina_Bool boolean)
{
	if (value->container->type != ENDER_BOOL)
		return;
	value->data.u32 = boolean;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Value * ender_value_ref(Ender_Value *thiz)
{
	if (!thiz) return NULL;
	thiz->ref++;
	return thiz;
}
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_value_unref(Ender_Value *thiz)
{
	if (!thiz) return;

	thiz->ref--;
	if (!thiz->ref)
		_ender_value_free(thiz);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void * ender_value_marshal(Ender_Value *v, unsigned int *len)
{
	return ender_serializer_value_marshal(v, len);
}

