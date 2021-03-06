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
#ifndef _ENDER_VALUE_H
#define _ENDER_VALUE_H

/**
 * @defgroup Ender_Value_Group Value
 * @brief A value represents every C primitive data types
 * @{
 */

/**
 * A representation of all different value types
 */
typedef union _Ender_Value
{
	Eina_Bool b;
	int8_t i8;
	uint8_t u8;
	int32_t i32;
	uint32_t u32;
	int64_t i64;
	uint64_t u64;
	double d;
	void *ptr;
	size_t sz;
} Ender_Value;

/**
 * Different types of a value
 */
typedef enum _Ender_Value_Type
{
	/** Represents an Eina_Bool */
	ENDER_VALUE_TYPE_BOOL,
	/** Represents an uint8_t */
	ENDER_VALUE_TYPE_UINT8,
	/** Represents an int8_t */
	ENDER_VALUE_TYPE_INT8,
	/** Represents an uint32_t */
	ENDER_VALUE_TYPE_UINT32,
	/** Represents an int32_t */
	ENDER_VALUE_TYPE_INT32,
	/** Represents an uint64_t */
	ENDER_VALUE_TYPE_UINT64,
	/** Represents an int64_t */
	ENDER_VALUE_TYPE_INT64,
	/** Represents a double */
	ENDER_VALUE_TYPE_DOUBLE,
	/** Represents a char * */
	ENDER_VALUE_TYPE_STRING,
	/** Represents a void * */
	ENDER_VALUE_TYPE_POINTER,
	/** Represents a size_t */
	ENDER_VALUE_TYPE_SIZE,
} Ender_Value_Type;

/**
 * @}
 */

#endif
