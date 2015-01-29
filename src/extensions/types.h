

!!==============================================================================
!!
!!	TYPES
!!	Rutinas biplataforma (Z/GLULX) para imprimir texto con diferentes estilos
!!
!!==============================================================================
!!
!!	File:			types.h
!!	Author(s):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Máquina-Z / GLULX
!!	Version:		4.5
!!	Released:		2014/09/21
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	4.5: 2014/09/21	Modificada definición del estilo del 'parser' para 
!!					diferenciar claramente que se trata de una variable que 
!!					puede ser modificada en tiempo de ejecución, y no de una 
!!					constante.
!!	4.4: 2014/07/28	Adoptado el estilo CamelCase para los nombres de las 
!!					rutinas.
!!	4.3: 2014/06/12	Añadida constante TYPES para permitir comprobar si la 
!!					extensión ha sido incluida.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2013, 2014, J. Francisco Martín
!!
!!	Este programa es software libre: usted puede redistribuirlo y/o 
!!	modificarlo bajo los términos de la Licencia Pública General GNU 
!!	publicada por la Fundación para el Software Libre, ya sea la versión 
!!	3 de la Licencia, o (a su elección) cualquier versión posterior.
!!
!!	Este programa se distribuye con la esperanza de que sea útil, pero 
!!	SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita MERCANTIL o 
!!	de APTITUD PARA UN PROPÓSITO DETERMINADO. Consulte los detalles de 
!!	la Licencia Pública General GNU para más información.
!!
!!	Debería haber recibido una copia de la Licencia Pública General GNU 
!!	junto a este programa. En caso contrario, consulte
!!	<http://www.gnu.org/licenses/>.
!!
!!------------------------------------------------------------------------------
!!
!!	# ESTILOS DE TEXTO
!!
!!	 -	romana (roman style)
!!	 -	itálica (italic style)
!!	 -	negrita (bold style)
!!	 -	monoespaciada (monospaced style)
!!
!!	# ESTILOS ABSTRACTOS
!!
!!	 -	enfático (emph/em)
!!	 -	fuerte (strong)
!!	 -	código (code)
!!	 -	parser
!!
!!------------------------------------------------------------------------------
System_file;

#Ifndef _TYPES_;
Constant _TYPES_;

Constant _RST_	= 0;
Constant _IST_	= 1;
Constant _MST_	= 2;
Constant _BST_	= 3;

Default	PARSER_PREFIX	"";
Default PARSER_SUFIX	"";
Default _parser_style	_RST_;

Global _current_style = _RST_;

!!==============================================================================
!!	Selección de estilo de texto
!!------------------------------------------------------------------------------

[ RomanStyle;
	#Ifdef	TARGET_ZCODE;
	font on; style roman;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 0);
	#Endif;	! TARGET_
	_current_style = _RST_;
];

[ ItalicStyle;
	#Ifdef	TARGET_ZCODE;
	font on; style underline;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 1);
	#Endif;	! TARGET_
	_current_style = _IST_;
];

[ BoldStyle;
	#Ifdef	TARGET_ZCODE;
	font on; style bold;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 3);
	#Endif;	! TARGET_
	_current_style = _BST_;
];

[ MonospacedStyle;
	#Ifdef	TARGET_ZCODE;
	font off;
	#Ifnot;	! TARGET_GLULX;
	glk($0086, 2);
	#Endif;	! TARGET_
	_current_style = _MST_;
];

[ StartParserStyle;
	switch (_parser_style) {
	_RST_:	RomanStyle();
	_IST_:	ItalicStyle();
	_BST_:	BoldStyle();
	_MST_:	MonospacedStyle();
	}
	if (PARSER_PREFIX ~= 0)
		print (string) PARSER_PREFIX;
];

[ EndParserStyle;
	if (PARSER_SUFIX ~= 0)
		print (string) PARSER_SUFIX;
	RomanStyle();
];

!!==============================================================================
!!	Imprimir texto en diferentes estilos
!!------------------------------------------------------------------------------

[ emph text st;
	if (text == 0) return false;
	st = _current_style;
	switch (st) {
	_RST_:	ItalicStyle();
	_IST_:	RomanStyle();
	_BST_:	RomanStyle();
	_MST_:	ItalicStyle();
	}
	print (string) text;
	switch (st) {
	_RST_:	RomanStyle();
	_IST_:	ItalicStyle();
	_BST_:	BoldStyle();
	_MST_:	MonospacedStyle();
	}
	return true;
];

[ strong text st;
	if (text == 0) return false;
	st = _current_style;
	switch (st) {
	_RST_:	BoldStyle();
	_IST_:	BoldStyle();
	_BST_:	ItalicStyle();
	_MST_:	BoldStyle();
	}
	print (string) text;
	switch (st) {
	_RST_:	RomanStyle();
	_IST_:	ItalicStyle();
	_BST_:	BoldStyle();
	_MST_:	MonospacedStyle();
	}
	return true;
];

[ code text st;
	if (text == 0) return false;
	st = _current_style;
	switch (st) {
	_RST_:	MonospacedStyle();
	_IST_:	MonospacedStyle();
	_BST_:	MonospacedStyle();
	_MST_:	ItalicStyle();
	}
	print (string) text;
	switch (st) {
	_RST_:	RomanStyle();
	_IST_:	ItalicStyle();
	_BST_:	BoldStyle();
	_MST_:	MonospacedStyle();
	}
	return true;
];

[ parser text st;
	if (text == 0) return false;
	st = _current_style;
	StartParserStyle();
	print (string) text;
	EndParserStyle();
	switch (st) {
	_RST_:	RomanStyle();
	_IST_:	ItalicStyle();
	_BST_:	BoldStyle();
	_MST_:	MonospacedStyle();
	}
	return true;
];

!! Alias:

[ em text; return emph (text); ];

#Endif; ! _TYPES_;


