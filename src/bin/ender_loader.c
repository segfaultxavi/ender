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
#include "Enesim.h"
/*============================================================================*
 *                                  Local                                     *
 *============================================================================*/
typedef enum _Ender_Library_Case {
	ENDER_LIBRARY_CASE_CAMEL, /* backColor */
	ENDER_LIBRARY_CASE_PASCAL, /* BackColor */
	ENDER_LIBRARY_CASE_UNDERSCORE, /* back_color */
} Ender_Library_Case;

typedef enum _Ender_Library_Notation {
	ENDER_LIBRARY_NOTATION_LATIN, /* foo_back_color_get */
} Ender_Library_Notation;

typedef Eina_Bool (*Ender_Loader_Tag_Attrs_Set_Cb)(Ender_Item *i, const char *key,
		const char *value);
typedef void (*Ender_Loader_Tag_Done_Cb)(Ender_Item *i);

typedef struct _Ender_Loader_Tag
{
	const char *name;
	Ender_Loader_Tag_Attrs_Set_Cb attrs_set_cb;
	Ender_Loader_Tag_Done_Cb done_cb;
} Ender_Loader_Tag;

static Ender_Loader_Tag _tags[] = {
	{ "lib", NULL, NULL },
	{ "type", NULL, NULL },
};

typedef struct _Ender_Loader_Context
{
	Ender_Item *i;
	Ender_Loader_Tag *tag;
} Ender_Loader_Context;

typedef struct _Ender_Loader
{
	Eina_Array *context;
	Ender_Library_Case lcase;
	Ender_Library_Notation lnotation;
	Enesim_Stream *s;
} Ender_Loader;

static void help(void)
{
	printf("Run: ender_loader FILE.ender\n");
}

#if 0
static Eina_Bool _egueb_dom_parser_eina_tag_attributes_set_cb(void *data, const char *key,
		const char *value)
{
}

static void _egueb_dom_parser_eina_tag_attribute_set(Egueb_Dom_Parser_Eina *thiz,
		Egueb_Dom_Node *node, const char *attributes, unsigned int length)
{
	const char *attrs = NULL;
	int attr_length = 0;
	attrs = eina_simple_xml_tag_attributes_find(content, length);
	eina_simple_xml_attributes_parse(attributes, length, _egueb_dom_parser_eina_tag_attributes_set_cb, &data);
}
#endif

/*----------------------------------------------------------------------------*
 *                      Eina's simple XML interface                           *
 *----------------------------------------------------------------------------*/
static Eina_Bool _ender_loader_parse_cb(void *data, Eina_Simple_XML_Type type,
		const char *content, unsigned int offset,
		unsigned int length)
{
	Ender_Loader *thiz = data;

	switch (type)
	{
		case EINA_SIMPLE_XML_OPEN:
		printf("open %.*s\n", length, content);
		//_egueb_dom_parser_eina_xml_open(thiz, content, length);
		break;

		case EINA_SIMPLE_XML_OPEN_EMPTY:
		//_egueb_dom_parser_eina_xml_open(thiz, content, length);
		//_egueb_dom_parser_eina_xml_close(thiz, content, length);
		break;

		case EINA_SIMPLE_XML_CLOSE:
		//_egueb_dom_parser_eina_xml_close(thiz, content, length);
		break;

		case EINA_SIMPLE_XML_DATA:
		//_egueb_dom_parser_eina_tag_text_set(thiz, content, length);
		break;

		case EINA_SIMPLE_XML_CDATA:
		//_egueb_dom_parser_eina_tag_cdata_set(thiz, content, length);
		break;

		case EINA_SIMPLE_XML_DOCTYPE_CHILD:
		case EINA_SIMPLE_XML_IGNORED:
		case EINA_SIMPLE_XML_COMMENT:
		case EINA_SIMPLE_XML_DOCTYPE:
		break;

		default:
		break;
	}
	return EINA_TRUE;
}
/*============================================================================*
 *                                 Global                                     *
 *============================================================================*/
int main(int argc, char **argv)
{
	Ender_Loader *thiz;
	Enesim_Stream *s;
	void *content;
	size_t len = 0;

	if (argc < 2)
	{
		help();
		goto no_file;
	}

	s = enesim_stream_file_new(argv[1], "r");
	if (!s) goto no_file;

	thiz = calloc(1, sizeof(Ender_Loader));
	thiz->context = eina_array_new(1);
	thiz->s = s;

	content = enesim_stream_mmap(thiz->s, &len);
	if (!content) goto no_mmap;

	eina_simple_xml_parse(content, len, EINA_TRUE, _ender_loader_parse_cb, thiz);
	enesim_stream_munmap(thiz->s, content);

no_mmap:
	eina_array_free(thiz->context);
	enesim_stream_unref(thiz->s);
	free(thiz);
no_file:
	return 0;
}
