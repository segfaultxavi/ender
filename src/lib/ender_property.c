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
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
/**
 *
 */
EAPI Ender_Container * ender_property_container_get(Ender_Property *p)
{
	return p->prop;
}
/**
 *
 */
EAPI Ender_Value_Type ender_property_type(Ender_Property *p)
{
	return p->prop->type;
}

/**
 *
 */
EAPI Eina_Bool ender_property_is_relative(Ender_Property *p)
{
	return p->relative;
}

/**
 *
 */
EAPI const char * ender_property_name_get(Ender_Property *p)
{
	return p->name;
}
