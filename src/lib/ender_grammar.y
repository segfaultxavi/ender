%name-prefix="ender_"
%defines
%error-verbose
%locations
%pure-parser
%parse-param { void * scanner }
%parse-param { Ender_Parser *parser }
%lex-param { void * scanner }

%{
#include <stdio.h>
#include <string.h>
#include "Ender.h"
#include "ender_private.h"

%}

%union {
	Ender_Type etype;
	Ender_Property_Type ptype;
	Ender_Property *prop;
	Ender_Descriptor *descriptor;
	char *s;
	Eina_Bool b;
	Eina_List *list; // use this for every _list nonterminal
}

%token <ptype> UINT
%token <ptype> INT
%token <ptype> ARGB
%token <ptype> DOUBLE
%token <ptype> IMAGE
%token <ptype> SURFACE
%token <ptype> STRING
%token <ptype> MATRIX
%token <ptype> ENDER
%token <etype> ABSTRACT
%token <etype> CLASS
%token NAMESPACE
%token REL
%token USING
%token <s> WORD
%type <s>using
%type <b> type_relative
%type <prop> type_specifier
%type <ptype> basic_type
%type <etype> definition
%type <prop> compound_type
%type <descriptor> renderer_inheritance
%%

main
	: using
	{
		if ($1 != NULL)
			ender_parser_parse($1);
	}
	namespace_list
	;

using
	: { $$ = NULL; }
	| USING WORD ';' using { $$ = $2; }
	;

namespace
	: NAMESPACE WORD
	{
		strcpy(parser->ns, $2);
	}
	namespace_name '{' renderer_list '}' ';'
	;

namespace_list
	:
	| namespace namespace_list
	;

namespace_name
	:
	| '.' WORD
	{
		strcat(parser->ns, ".");
                strcat(parser->ns, $2);
	}
	namespace_name
	;

renderer_list
	:
	| renderer renderer_list
	;

definition
	: CLASS { $$ = $1; }
	| ABSTRACT { $$ = $1; }
	;

renderer
	: definition WORD renderer_inheritance
	{ parser->descriptor = ender_parser_register(parser->ns, $2, $3, $1); }
	'{' declaration_list '}' ';'
	;

renderer_inheritance
	: { $$ = NULL; }
	| ':' WORD { $$ = ender_descriptor_find($2); }
	;

types
	: type_specifier ',' types
	| type_specifier
	;

basic_type
	: UINT { $$ = $1; }
	| INT { $$ = $1; }
	| ARGB { $$ = $1; }
	| DOUBLE { $$ = $1; }
	| STRING { $$ = $1; }
	| SURFACE { $$ = $1; }
	| WORD { $$ = ENDER_RENDERER; }
	| ENDER { $$ = $1; }
	| MATRIX { $$ = $1; }
	;

compound_type
	: '[' types ']'
	{
		$$ = ender_property_new(ENDER_LIST);
	}
	;

type_specifier
	: basic_type { $$ = ender_property_new($1); }
	| compound_type { $$ = $1; }
	;

type_relative
	: {$$=EINA_FALSE; }
	| REL { $$=EINA_TRUE; }
	;
declaration
	: 
	type_relative type_specifier WORD ';'
	{
		ender_parser_property_add(parser->ns, parser->descriptor, $3, $2, $1);
	} 
	;

declaration_list
	:
	| declaration declaration_list
	;
%%

void ender_error(YYLTYPE *lloc, void *scanner, Ender_Parser *parser, const char *str)
{
        ERR("Parsing error at %d: %d.%d %s", lloc->last_line, lloc->first_column, lloc->last_column, str);
}
