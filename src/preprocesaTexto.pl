#!/usr/bin/perl

#	Archivo:	preprocesaTexto.pl
#	Autor(es):	J. Francisco Martín <jfm.lisaso@gmail.com>
#	Versión:	1.1
#	Fecha:		2015/02/07
#
#	Script Perl para preprocesar un archivo de texto. Sustituye ciertas 
#	etiquetas (como '*', '**', '[', ']') por funciones definidas dentro del 
#	relato para manipular el estilo de los textos.

if ($#ARGV != 1) {
	print "Se deben especificar los archivos de entrada y salida del script.";
	print "\n\n";
	exit 4;
}

$input_file = $ARGV[0];
$output_file = $ARGV[1];

# Se abre el archivo de entrada:
open (FILE, "<$input_file") 
	or die "No se pudo abrir el archivo de entrada $input_file: $!\n";
@lines = <FILE>;
close FILE;

# Se abre el archivo de salida:
open (STDOUT, ">$output_file")
	or die "No se pudo abrir el archivo de salida $output_file: $!\n";

# Se hacen las sustituciones (EL ORDEN EN QUE SE HACEN IMPORTA)
for (@lines) {

	# Omite las líneas de comentario (aquellas que empiezan por '!' o '#'):
	next if /^\s*(!|#)/;

	# Imprime '**texto**' en estilo fuerte:
	s/\*{2,}(.*?)\*{2,}/", (strong) "\1", "/g;
	# Imprime '*texto*' en estilo enfatizado:
	s/\*(.*?)\*/", (emph) "\1", "/g;
	# Imprime '`texto`' en estilo de tipo código:
	s/\`(.*?)\`/", (code) "\1", "/g;

	# Imprime el nombre corto del objeto con el artículo determinado adecuado:
	s/\[\s*(el|la|los|las)\s+(.+?)\s*\]/", (the) \2, "/g;
	s/\[\s*(El|La|Los|Las)\s+(.+?)\s*\]/", (The) \2, "/g;
	# Igual, considerando contracciones 'al' y 'del':
	s/\[\s*(al|a\s+la|a\s+los|a\s+las)\s+(.+?)\s*\]/", (al) \2, "/g;
	s/\[\s*(Al|A\s+la|A\s+los|A\s+las)\s+(.+?)\s*\]/", (_Al) \2, "/g;
	s/\[\s*(del|de\s+la|de\s+los|de\s+las)\s+(.+?)\s*\]/", (del) \2, "/g;
	s/\[\s*(Del|De\s+la|De\s+los|De\s+las)\s+(.+?)\s*\]/", (_Del) \2, "/g;
	# Imprime el nombre corto del objeto con el artículo indeterminado adecuado:
	s/\[\s*(un|una|unos|unas)\s+(.+?)\s*\]/", (a) \2, "/g;
	s/\[\s*(Un|Una|Unos|Unas)\s+(.+?)\s*\]/", (A) \2, "/g;
	# Igual, con los pronombres demostrativos adecuados:
	s/\[\s*(este|esta|estos|estas)\s+(.+?)\s*\]/", (este) \2, "/g;
	s/\[\s*(Este|Esta|Estos|Estas)\s+(.+?)\s*\]/", (_este) \2, "/g;
	s/\[\s*(ese|esa|esos|esas)\s+(.+?)\s*\]/", (ese) \2, "/g;
	s/\[\s*(Ese|Esa|Esos|Esas)\s+(.+?)\s*\]/", (_ese) \2, "/g;
	s/\[\s*(aquel|aquella|aquellos|aquellas)\s+(.+)\s*\]/", (aquel) \2, "/g;
	s/\[\s*(Aquel|Aquella|Aquellos|Aquellas)\s+(.+)\s*\]/", (_aquel) \2, "/g;

	# Imprime la terminación adecuada:
	s/\[\s*n\s+(.+?)\s*\]/", (n) \1, "/g;
	s/\[\s*o\s+(.+?)\s*\]/", (o) \1, "/g;

	# Imprime lista de objetos contenidos en otro objeto:
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\<\s*(.+?)\s*\>\s*\]/";\nWriteListFrom(child(\2), \3);\nprint "/g;
	s/\[\s*lista\s+de\s+objetos\s+(en|sobre)\s+(.+?)\s*\]/";\nWriteListFrom(child(\2), ENGLISH_BIT + PARTINV_BIT);\nprint "/g;

	# Creación directa de hipervínculos:
	s/\[\@\s*(.+?)\s*\,\s*(.+?)\s*\]/";\nCreateLink(\1, "\2");\nprint "/g;

	# Imprime el nombre corto del objeto:
	s/\[\s*(.+?)\s*\]/", (name) \1, "/g;

	print;
}

# Cierra el archivo de salida:
close STDOUT;

