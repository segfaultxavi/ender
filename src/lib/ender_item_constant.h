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

#ifndef _ENDER_ITEM_CONSTANT_H
#define _ENDER_ITEM_CONSTANT_H

/**
 * @defgroup Ender_Constant_Group Constant
 * @brief A constant represents an identifier with its associated value
 * @{
 */

EAPI Ender_Item * ender_item_constant_type_get(Ender_Item *i);
EAPI void ender_item_constant_value_get(Ender_Item *i, Ender_Value *v);

/**
 * @}
 */
#endif
