

!!==============================================================================
!!
!!	PARSING PREPROCESSOR
!!
!!==============================================================================
!!
!!	File:			pPreprocessor.h
!!	Author(s):		J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		1.1
!!	Released:		2014/07/29
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.1: 2014/07/29	Ante objetos con el mismo �ndice de coincidencia, ahora se 
!!					da preferencia a aquellos que se encuentren en el foco del 
!!					jugador.
!!	1.0: 2014/05/29	Versi�n preliminar.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2014, J. Francisco Mart�n
!!
!!	Este programa es software libre: usted puede redistribuirlo y/o 
!!	modificarlo bajo los t�rminos de la Licencia P�blica General GNU 
!!	publicada por la Fundaci�n para el Software Libre, ya sea la versi�n 
!!	3 de la Licencia, o (a su elecci�n) cualquier versi�n posterior.
!!
!!	Este programa se distribuye con la esperanza de que sea �til, pero 
!!	SIN GARANT�A ALGUNA; ni siquiera la garant�a impl�cita MERCANTIL o 
!!	de APTITUD PARA UN PROP�SITO DETERMINADO. Consulte los detalles de 
!!	la Licencia P�blica General GNU para m�s informaci�n.
!!
!!	Deber�a haber recibido una copia de la Licencia P�blica General GNU 
!!	junto a este programa. En caso contrario, consulte
!!	<http://www.gnu.org/licenses/>.
!!
!!------------------------------------------------------------------------------
System_file;

!! Descomentar para obtener info. de depuraci�n del preprocesador:
!Constant DEBUG_PARSING_PREPROCESSOR;

!! Descomentar para obtener info. de depuraci�n de la rutina CompareWord():
!Constant DEBUG_COMPARE_WORD_ROUTINE;

#Ifndef COMPARE_WORD_ROUTINE;
Constant COMPARE_WORD_ROUTINE;
!!==============================================================================
!!	Compara una palabra de la entrada del usuario con una de las palabras de 
!!	diccionario. La palabra de entrada se pasa a la funci�n a trav�s de 
!!	*num_word_prompt*, un n�mero que indica el orden de la palabra en el vector 
!!	de entrada, y la palabra de diccionario se pasa a trav�s de *dictword* 
!!	(hay que volcarla en un vector antes de hacer la comprobaci�n).
!!
!!	Se retorna 1 si las palabras son iguales, o 0 si son diferentes.
!!------------------------------------------------------------------------------

!! Vector para guardar palabras temporalmente:
Array tmp_text -> 64;

[ CompareWord num_word_prompt dictword
	i len;

	!! A) Se vuelca la palabra de diccionario a un array:

	#Ifdef TARGET_ZCODE;
	@output_stream 3 tmp_text;
	print (address) dictword;
	@output_stream -3;
	#Ifnot;	! TARGET_GLULX;
	tmp_text->(WORDSIZE-1) = PrintAnyToArray(tmp_text+WORDSIZE, 60, dictword);
	#Endif; ! TARGET_

	len = tmp_text->(WORDSIZE-1); 

	!! B) Si el ultimo car�cter es una coma, se elimina para evitar conflictos 
	!! con la conversi�n de infitivos y los diccionarios en informATE --> NO 
	!! DEBE HABER NUNCA PALABRAS EN INFINITIVO EN EL DICCIONARIO. No vale para 
	!! palabras que antes de ponerles la coma tengan 9 o m�s caracteres 
	!! (limitaci�n de Inform):

	if (tmp_text->(len+WORDSIZE-1) == ',') {
		tmp_text->(len+WORDSIZE-1) = 0;	! Se elimina el caracter del buffer
		(tmp_text->(WORDSIZE-1))--;		! Se reducen las dimensiones
		len = tmp_text->(WORDSIZE-1);	! Se actualiza el valor de 'len'
	}

	#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
	print "Comparando prompt: <", (PrintPromptWord) num_word_prompt, 
	"> con palabra de diccionario:<", (PrintStringArray) tmp_text, ">^";
	#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;

	!! Si la longitud de las palabras no es igual, se retorna NO coincidente. 
	!! (NOTA: Hay que contemplar el caso especial de palabras de m�s de 9 
	!! caracteres por las limitaciones de Inform):
	if (WordLength(num_word_prompt) ~= len && 
			~~(WordLength(num_word_prompt) > 9 && len == 9)) 
		return 0;

	!! Si las palabras tienen la misma longitud, se comparan caracter a 
	!! caracter y se retorna NO coincidente si se encuentra una diferencia:
	for (i = 0: i < len: i++) {
		if (WordAddress(num_word_prompt)->i ~= tmp_text->(i+WORDSIZE))
			return 0;
	}

	!! Las palabras son iguales:
	return 1;
];

#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
!!==============================================================================
!!	Funciones de depuraci�n
!!------------------------------------------------------------------------------

!! Funci�n para pintar un String Array
[ PrintStringArray the_array i;
	print "(", the_array-->0, ")";
	for (i = WORDSIZE : i < (the_array-->0) + WORDSIZE : i++) 
		print (char) the_array->i;
];

!! Funci�n para pintar una palabra del Prompt de entrada del jugador
[ PrintPromptWord num_word dir i;
	dir = WordAddress(num_word);
	for (i = 0 : i < WordLength(num_word) : i++)
		print (char) dir->i;
];

#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;
#Endif; ! COMPARE_WORD_ROUTINE;


!!==============================================================================
!!	Preprocesador de la entrada de usuario. Implementa las siguientes 
!!	funciones:
!!
!!	 -	get_selected_object() - Retorna el �ltimo objeto reconocido en la 
!!		entrada del usuario por el preprocesador.
!!
!!	 -	run() - Comprueba la entrada del usuario y trata de reconocer patrones 
!!		en ella mediante an�lisis no estricto para identificar si puede 
!!		referirse a alguno de los objetos definidos en el modelo del mundo.
!!------------------------------------------------------------------------------
Object	ParsingPreprocessor "(Parsing preprocessor)"
 with	get_selected_object [;
			return self.selected_object;
		],
		run [
			obj i j n m valid hits max_hits;

			!! A) Inicializaciones del m�todo:
			self.selected_object = 0;

			!! B) Da un repaso a los objetos presentes en el relato, 
			!! comprobando si alguno encaja con la entrada de usuario:
			objectloop (obj ofclass Object) {
				n = m = 0;
				valid = false;

				if (obj.adjectives ~= 0) {
					for (i = 0 : i < (obj.#adjectives)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&adjectives-->i)) {
								if (j == 1) valid = true;
								m++;
							}
						}
					}
				}
				if (obj.name_f ~= 0) {
					for (i = 0 : i < (obj.#name_f)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_f-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_fp ~= 0) {
					for (i = 0 : i < (obj.#name_fp)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_fp-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_m ~= 0) {
					for (i = 0 : i < (obj.#name_m)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_m-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (obj.name_mp ~= 0) {
					for (i = 0 : i < (obj.#name_mp)/WORDSIZE : i++) {
						for (j = 1 : j <= num_words : j++) {
							if (CompareWord(j, obj.&name_mp-->i)) {
								if (j == 1) valid = true;
								n++;
							}
						}
					}
				}
				if (n ~= 0) n = n+m;

				!! Se calcula el n�mero de coincidencias del objeto actual en 
				!! relaci�n al total de palabras (%):
				hits = (n*100) / num_words;

				!! Si el objeto actual tiene m�s coincidencias que el mejor 
				!! candidato hasta ahora lo sustituye:
				if ((valid) && (hits > max_hits)) {
					self.selected_object = obj;
					max_hits = hits;
				}
				!! Si el objeto actual y el mejor candidato hasta ahora tienen 
				!! el mismo n�mero de coincidencias, comprueba si el actual se 
				!! encuentra en el foco del jugador y si es as� se lo 
				!! selecciona como candidato:
				else if ((valid) && (hits == max_hits)) {
					if (TestScope(obj, player)) {
						self.selected_object = obj;
					}
				}
			}

			#Ifdef DEBUG_PARSING_PREPROCESSOR;
			if (self.selected_object ~= 0) {
				print "** PARSING PREPROCESSOR **^", "Coincidencia: ", 
				(name) self.selected_object, ", ", max_hits, "%.^";
			}
			else {
				print "** PARSING PREPROCESSOR **^", "No hay coincidencias.^";
			}
			#Endif; ! DEBUG_PARSING_PREPROCESSOR;

		],
 private
		selected_object 0;


