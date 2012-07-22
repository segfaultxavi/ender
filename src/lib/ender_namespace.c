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
struct _Ender_Namespace
{
	char *name;
	Eina_Hash *descriptors;
};

/* TODO */
typedef void (*Ender_Namespace_Init)(void);

static Eina_Hash *_namespaces = NULL;

static void _ender_namespace_free(void *data)
{
	Ender_Namespace *thiz = data;

	if (thiz->name)
		free(thiz->name);
	eina_hash_free(thiz->descriptors);
	free(thiz);
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
void ender_namespace_init(void)
{
	_namespaces = eina_hash_string_superfast_new(_ender_namespace_free);
}

void ender_namespace_shutdown(void)
{
	eina_hash_free(_namespaces);
}

void ender_namespace_dump(Ender_Namespace *ns)
{
	Eina_Iterator *it;
	Ender_Descriptor *descriptor;

	it = eina_hash_iterator_data_new(ns->descriptors);
	printf("namespace \"%s\" {\n", ns->name);

	while (eina_iterator_next(it, (void **)&descriptor))
	{
		Ender_Descriptor_Type type;

		type = ender_descriptor_type(descriptor);
		printf("\t %s \"%s\" {\n", ender_descriptor_type_string_to(type), ender_descriptor_name_get(descriptor));
		printf("\t};\n");
	}
	printf("};\n");
	eina_iterator_free(it);
}
/*============================================================================*
 *                                   API                                      *
 *============================================================================*/
/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Namespace * ender_namespace_new(const char *name)
{
	Ender_Namespace *namespace;

	if (!name) return NULL;

	/* check if we already have the namespace */
	namespace = eina_hash_find(_namespaces, name);
	if (!namespace)
	{
		namespace = malloc(sizeof(Ender_Namespace));
		namespace->name = strdup(name);
		namespace->descriptors = eina_hash_string_superfast_new(
				(Eina_Free_Cb)ender_descriptor_free);
		eina_hash_add(_namespaces, name, namespace);
	}
	return namespace;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_namespace_list(Ender_List_Callback cb, void *data)
{
	Eina_Iterator *it;
	char *name;

	it = eina_hash_iterator_key_new(_namespaces);
	while (eina_iterator_next(it, (void **)&name))
	{
		cb(name, data);
	}
	eina_iterator_free(it);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Namespace * ender_namespace_find(const char *name)
{
	Ender_Namespace *namespace;

	if (!name) return NULL;

	namespace = eina_hash_find(_namespaces, name);
	return namespace;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Descriptor * ender_namespace_descriptor_find(Ender_Namespace *ns, const char *name)
{
	if (!ns || !name) return NULL;

	return eina_hash_find(ns->descriptors, name);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI void ender_namespace_descriptor_list(Ender_Namespace *ns, Ender_List_Callback cb, void *data)
{
	Eina_Iterator *it;
	char *name;

	if (!ns) return;

	it = eina_hash_iterator_key_new(ns->descriptors);
	while (eina_iterator_next(it, (void **)&name))
	{
		cb(name, data);
	}
	eina_iterator_free(it);
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI Ender_Descriptor * ender_namespace_descriptor_add(Ender_Namespace *ens, const char *name, Ender_Creator creator, Ender_Destructor destructor, Ender_Descriptor *parent, Ender_Descriptor_Type type)
{
	Ender_Descriptor *desc;

	if (!name || !ens) return NULL;
	desc = ender_descriptor_new(name, ens, creator, destructor, parent, type);
	if (!desc) return NULL;
	DBG("class %s@%s registered correctly %p", name, ens->name, desc);
	eina_hash_add(ens->descriptors, name, desc);

	return desc;
}

/**
 * To be documented
 * FIXME: To be fixed
 */
EAPI const char * ender_namespace_name_get(Ender_Namespace *ns)
{
	if (!ns) return NULL;
	return ns->name;
}
