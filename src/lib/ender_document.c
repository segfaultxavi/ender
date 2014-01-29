/* ENDER - Enesim's descriptor library
 * Copyright (C) 2010 - 2012 Jorge Luis Zapata
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
typedef struct _Ender_Document
{
	/* a list of every instance created */
	Eina_List *instances;
} Ender_Document;
/*----------------------------------------------------------------------------*
 *                     The exernal document interface                         *
 *----------------------------------------------------------------------------*/
static Egueb_Dom_Node * _ender_document_element_create(Egueb_Dom_Node *n,
		void *data, const char *name)
{
	/* we can only create states/state/set/animate */
	/* any other object needs to be created using the topmost ender */
	if (!strcmp(name, "states"))
	{
		return ender_element_states_new();
	}
	else if (!strcmp(name, "state"))
	{
		return ender_element_state_new();
	}
	else if (!strcmp(name, "object"))
	{
		return ender_element_object_new();
	}
	else if (!strcmp(name, "ender"))
	{
		return ender_element_ender_new();
	}

	return NULL;
}

static Egueb_Dom_Document_External_Descriptor _descriptor = {
	/* init 		= */ NULL,
	/* deinit 		= */ NULL,
	/* element_create	= */ _ender_document_element_create,
	/* process 		= */ NULL,
	/* needs process 	= */ NULL,
};
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
EAPI Egueb_Dom_Node * ender_document_new(void)
{
	return egueb_dom_document_external_new(&_descriptor, NULL);
}

EAPI Egueb_Dom_Node * ender_document_instance_new(Egueb_Dom_Node *n,
		const char *id, Eina_Error *err)
{
	Egueb_Dom_Node *ret;
	Egueb_Dom_Node *rel;
	Egueb_Dom_String *sid;
	
	sid = egueb_dom_string_new_with_static_string(id);
	rel = egueb_dom_document_element_get_by_id(n, sid, err);
	egueb_dom_string_unref(sid);
	if (!rel) return NULL;

	if (!ender_element_is_object(n))
		return NULL;

	ret = ender_element_instance_new(rel);
	return ret;
}
