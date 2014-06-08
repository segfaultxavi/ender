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

#ifndef _ENDER_ITEM_FUNCTION_H
#define _ENDER_ITEM_FUNCTION_H

/**
 * @defgroup Ender_Function_Group Function
 * @{
 */

typedef enum _Ender_Item_Function_Flags
{
	ENDER_ITEM_FUNCTION_FLAG_IS_METHOD = (1 << 0),
	ENDER_ITEM_FUNCTION_FLAG_THROWS    = (1 << 1),
} Ender_Item_Function_Flags;

EAPI Eina_List * ender_item_function_args_get(Ender_Item *i);
EAPI int ender_item_function_args_count(Ender_Item *i);
EAPI Ender_Item * ender_item_function_ret_get(Ender_Item *i);
Eina_Bool ender_item_function_call(Ender_Item *i,
		Ender_Value *args);
EAPI int ender_item_function_flags_get(Ender_Item *i);

/**
 * @}
 */
#endif