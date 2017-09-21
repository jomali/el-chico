

!!==============================================================================
!!
!!	CHOICE SET
!!	Sistema para hacer selecciones entre un conjunto de opciones
!!
!!==============================================================================
!!
!!	File:			choiceSet.h
!!	Author(s):		J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!					Mastodon
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		1.0
!!	Released:		2017/09/18
!!
!!------------------------------------------------------------------------------
!!
!!	This program is free software; you can redistribute it and/or modify
!!	it under the terms of the GNU General Public License as published by
!!	the Free Software Foundation; either version 2 of the License, or
!!	(at your option) any later version.
!!
!!	This program is distributed in the hope that it will be useful,
!!	but WITHOUT ANY WARRANTY; without even the implied warranty of
!!	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!!	GNU General Public License for more details.
!!
!!	You should have received a copy of the GNU General Public License along
!!	with this program; if not, write to the Free Software Foundation, Inc.,
!!	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. Or see
!!	<http://www.gnu.org/licenses/>.
!!
!!	Copyright (c) 2009, Mastodon
!!	Copyright (C) 2017, J. Francisco Mart�n
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	0.0: 2016/07/24	Inicio de la adaptaci�n de la extensi�n 'topicInventory'
!!					v2.2 para generalizar el sistema de conversaci�n con
!!					inventario de temas.
!!
!!------------------------------------------------------------------------------
!!
!!	# INTRODUCCI�N
!!
!!	La extensi�n CHOICE SET permite implementar sistemas de conversaci�n con
!!	inventario de temas ---y, en general, cualquier otro sistema que utilice
!!	un mecanismo de selecci�n de opciones de entre un conjunto dado---
!!	utilizando an�lisis no estricto de la entrada de usuario para el
!!	reconocimiento de patrones. Est� basada en las notas de Eric Eve sobre
!!	sistemas de conversaci�n: <http://www.tads.org/howto/convbkg.htm>, y
!!	constru�da sobre las extensiones NPC_Conversacion v1.0 de Mastodon, y
!!	TOPIC INVENTORY v2.1 ---CHOICE SET es una generalizaci�n actualizada de
!!	sobre �sta �ltima---. Permite interacciones del tipo:
!!
!!		Te detienes un momento a pensar en qu� hacer esta tarde...
!!		(Puedes escoger entre escribir documentaci�n, salir a tomar algo o ver
!!		una pel�cula.)
!!
!!		> lo de la peli
!!
!!
!!	# APLICACIONES
!!
!!	CHOICE SET permite listar ante el usuario un conjunto de opciones de entre
!!	las que puede seleccionar una introduciendo alguna de las palabras clave de
!!	la opci�n; una funcionalidad que facilita, por ejemplo, la construcci�n de
!!	CONVERSACIONES utilizando un sistema de INVENTARIO DE TEMAS. Estos sistemas
!!	de conversaci�n est�n ideados con el objetivo de esquivar los problemas que
!!	suelen presentar los sistemas de conversaci�n m�s habituales en los relatos
!!	interactivos; dificultades para adivinar la palabra clave en sistemas
!!	basados en acciones ASK/TELL, simplificaci�n excesiva en sistemas basados
!!	en la acci�n TALK TO, o falta de libertad y ruptura de la interfaz textual
!!	en sistemas de men�s.
!!
!!	Al utilizar un inventario de temas, en esencia, se presenta al usuario una
!!	lista de temas de conversaci�n sugeridos bas�ndose en el conocimiento del
!!	personaje protagonista. De esta forma, el usuario puede hacer referencia a
!!	los temas que quiera lanzar utilizando una interfaz similar a la de los
!!	sistemas ASK/TELL, pero sin necesidad de tener que adivinar por s� mismo la
!!	palabra clave que lanza el tema.
!!
!!	En concreto, el sistema se podr�a presentar de una forma similar a la
!!	del siguiente ejemplo (las diferentes opciones posibles se ordenan
!!	aleatoriamente con cada listado):
!!
!!		> hablar con el programador
!!		---Disculpe...
!!		El programador levanta la vista de la pantalla de su ordenador y se
!!		quita las gafas. ---�Si?
!!
!!		(Puedes preguntar por sus aficiones, hablarle del proyecto en que
!!		trabaja o hablar del tema que nunca se acaba.)
!!
!!		> hablar del proyecto
!!		---He o�do que llevas un tiempo trabajando en el proyecto de un relato
!!		interactivo... ---empiezas.
!!		El hombre se pone muy nervioso de pronto. ---�Qui�n te ha hablado de
!!		eso? Ese proyecto est� aparcado desde hace a�os. Despu�s de aquel... de
!!		aquel asunto.
!!
!!		> hablar al programador
!!		Simula limpiarse las gafas, inquieto.
!!
!!		(Puedes hablar del tema que nunca se acaba, preguntar por el asunto o
!!		preguntar por sus aficiones.)
!!
!!		> asunto
!!		---�A qu� asunto te refieres?
!!		�l se coloca las gafas y vuelve de nuevo su atenci�n al ordenador,
!!		claramente agitado. ---T-tengo mucho trabajo que hacer. Si me
!!		disculpas...
!!
!!		(Puedes insistir en el asunto, preguntar por sus aficiones o hablar
!!		del tema que nunca se acaba.)
!!
!!		> tema interminable
!!		---T�o, �d�nde est� mi coche?
!!		---�Y tu coche, t�o?
!!
!!		(Puedes hablar del tema que nunca se acaba, preguntar por sus aficiones
!!		o insistir en el asunto.)
!!
!!	Adem�s de para conversaciones, el sistema se puede utilizar en general para
!!	crear cualquier otra interacci�n similar con un objeto cualquiera. Por
!!	ejemplo:
!!
!!		> abrir nevera
!!		Abres la nevera buscando algo que comer.
!!
!!		(Puedes prepararte un sandwich o hacerte un cocido monta��s.)
!!
!!		> cocido
!!		[...]
!!
!!
!!	# AN�LISIS NO ESTRICTO
!!
!!	El reconocimiento de patrones entre la entrada de usuario y las palabras
!!	clave de cada elecci�n se lleva a cabo por medio de an�lisis no estricto;
!!	si entre todas las palabras introducidas por el usuario se reconocen claves
!!	de una o m�s elecciones, se lanza aquella con m�s coincidencias, ignorando
!!	el resto de la entrada.
!!
!!
!!	# SOBRE EL FORMATO DE LOS MENSAJES
!!
!!	El formato con el que se imprime el listado de opciones se puede modificar.
!!	Para ello, el autor cuenta con 8 constantes diferentes que puede definir
!!	libremente:
!!
!!	 -	CSET_STYLE [0-3]: Define el estilo con el que se imprime el listado de
!!		opciones: 0 -> romana, 1 -> it�lica, 2 -> negrita, 3 -> monoespaciada.
!!
!!	 -	CSET_PREFIX: Cadena de texto previa al listado de elecciones.
!!
!!	 -	CSET_SUFIX: Cadena de texto posterior al listado de elecciones.
!!
!!	 -	CSET_MSG1: Antecede al conjunto de elecciones cuando son listadas.
!!
!!	 -	CSET_MSG2: Si hay m�s de una elecci�n en el conjunto, se imprime entre
!!		CSET_MSG1 y el conjunto de elecciones cuando son listadas.
!!
!!	 -	CSET_COMMA: Separador general de las elecciones del conjunto cuando son
!!		listadas.
!!
!!	 -	CSET_OR: Separador de las dos �ltimas elecciones del conjunto cuando
!!		son listadas.
!!
!!	 -	CSET_NO_MSG: Mensaje cuando se hace un listado si no hay elecciones en
!!		el conjunto.
!!
!!	La configuraci�n por defecto de estas constantes: CSET_STYLE=1,
!!	CSET_PREFIX="(", CSET_SUFIX=".)", CSET_MSG1="Puedes ", CSET_MSG2="escoger
!!	entre ", CSET_COMMA=", ", CSET_OR=" o ", CSET_NO_MSG="Listado de opciones
!!	vac�o", imprime listados en estilo romana del tipo*:
!!
!!		(Puedes escoger entre la opci�n 1, la opci�n 2 o la opci�n 3.)
!!
!!	*.- El �ltimo separador en la configuraci�n por defecto es la cadena " o ".
!!	Cabe se�alar que ante opciones que empiecen igualmente por 'o', el
!!	separador deber�a ser " u ", en lugar de " o ". Aunque hacer esto
!!	autom�ticamente es t�cnicamente posible, la manipulaci�n de cadenas de
!!	caracteres en Inform resulta muy engorrosa y requerir�a transformar cada
!!	una de las opciones del listado en vectores de caracteres primero, y luego
!!	realizar las comprobaciones oportunas antes de imprimir el separador
!!	correcto. En lugar de todo esto, se insta al autor a no utilizar opciones
!!	que empiecen por la letra 'o' si utiliza ese " o " por defecto como
!!	separador final del listado. (En el listado del ejemplo, en lugar de
!!	"opci�n 1", "opci�n 2", etc, se ha utilizado: "LA opci�n 1", "LA opci�n
!!	2"... No as� en el pr�ximo ejemplo, m�s abajo).
!!
!!	Se podr�a, por ejemplo, cambiar por la siguiente configuraci�n alternativa:
!!	CSET_STYLE=1, CSET_PREFIX="[", CSET_SUFIX="]", CSET_MSG1="Escoge: ",
!!	CSET_MSG2="", CSET_COMMA=" / ", CSET_OR=" / ", CSET_NO_MSG="Listado de
!!	opciones vac�o", para imprimir listados en cursiva con el siguiente formato:
!!
!!		[Escoge: opci�n 1 / opci�n 2 / opci�n 3]
!!
!!
!!	# UTILIZACI�N
!!
!!	Para usar la librer�a �nicamente hay que incluir la siguiente l�nea en la
!!	rutina BeforeParsing (crearla si no existe):
!!
!!		[ BeforeParsing;
!!			ChoiceSetManager.run();
!!		];
!!
!!
!!	# LIMITACIONES Y POSIBLES MEJORAS
!!
!!	Podr�a ser interesante contemplar la posibilidad de crear elecciones
!!	ocultas ('concealed') que no aparezcan sugeridas autom�ticamente al
!!	imprimir el conjunto de elecciones disponibles. Permitir�a implementar, por
!!	ejemplo, temas de conversaci�n ocultos.
!!
!!------------------------------------------------------------------------------
System_file;
#Ifndef _CHOICE_SET_;
Constant _CHOICE_SET_;
Message "[Including <choiceSet>]";

!! Descomentar para obtener info. de depuraci�n del controlador:
!Constant DEBUG_CHOICE_SET;

!! Descomentar para obtener info. de depuraci�n de la rutina 'CompareWord()'':
!Constant DEBUG_COMPARE_WORD_ROUTINE;

!! Descomentar y compilar para probar la extensi�n:
!Constant TEST_CHOICE_SET;

!! Estilo y textos por defecto de la extensi�n:
Default CSET_STYLE	1; ! [0-3]
Default CSET_PREFIX	"(";
Default CSET_SUFIX	".)";
Default CSET_MSG1	"Puedes ";
Default CSET_MSG2	"escoger entre ";
Default CSET_COMMA	", ";
Default CSET_OR		" o ";
Default CSET_NO_MSG	"Listado de opciones vac�o";

!! Objeto de apoyo para reordenar los temas de una conversaci�n:
Object	ChoiceBag "(ChoiceSet Bag)";


#Ifndef _COMPARE_WORD_ROUTINE_;
Constant _COMPARE_WORD_ROUTINE_;
!! Array para guardar palabras temporalmente:
Array compare_word_tmp_text -> 64;
!!==============================================================================
!! Compara una palabra de la entrada del usuario con una de las palabras de
!! diccionario. La palabra de entrada se pasa a la funci�n a trav�s de
!! 'num_word_prompt', un n�mero que indica el orden de la palabra en el vector
!! de entrada, y la palabra de diccionario se pasa a trav�s de 'dictword'
!! (hay que volcarla en un vector antes de hacer la comprobaci�n).
!!
!!	@param {integer} num_word_prompt - Indica el orden de la palabra en el
!!		vector de entrada
!!	@param {string} dictword - Palabra de diccionario
!!	@returns {integer} 1 si las palabras son iguales, 0 si son diferentes
!!	@version 1.2
!!------------------------------------------------------------------------------
[ CompareWord num_word_prompt dictword
	i length;

	!! A) Se vuelca la palabra de diccionario a un array:

	#Ifdef TARGET_ZCODE;
	@output_stream 3 compare_word_tmp_text;
	print (address) dictword;
	@output_stream -3;
	#Ifnot;	! TARGET_GLULX;
	compare_word_tmp_text->(WORDSIZE-1) =
		PrintAnyToArray(compare_word_tmp_text + WORDSIZE, 60, dictword);
	#Endif; ! TARGET_

	length = compare_word_tmp_text->(WORDSIZE-1);

	!! B) Si el ultimo car�cter es una coma, se elimina para evitar conflictos
	!! con la conversi�n de infinitivos y los diccionarios en informATE --> NO
	!! DEBE HABER NUNCA PALABRAS EN INFINITIVO EN EL DICCIONARIO. No vale para
	!! palabras que antes de ponerles la coma tengan 9 o m�s caracteres
	!! (limitaci�n de Inform):

	if (compare_word_tmp_text->(length+WORDSIZE-1) == ',') {
		!! Se elimina el caracter del buffer:
		compare_word_tmp_text->(length+WORDSIZE-1) = 0;
		!! Se reducen las dimensiones:
		(compare_word_tmp_text->(WORDSIZE-1))--;
		!! Se actualiza el valor de 'length':
		length = compare_word_tmp_text->(WORDSIZE-1);
	}

	#Ifdef DEBUG_COMPARE_WORD_ROUTINE;
	print "Comparando prompt: <", (PrintPromptWord) num_word_prompt,
	"> con palabra de diccionario:<", (PrintStringArray) compare_word_tmp_text,
	">^";
	#Endif; ! DEBUG_COMPARE_WORD_ROUTINE;

	!! Si la longitud de las palabras no es igual, se retorna NO coincidente.
	!! (NOTA: Hay que contemplar el caso especial de palabras de m�s de 9
	!! caracteres por las limitaciones de Inform):
	if (WordLength(num_word_prompt) ~= length &&
			~~(WordLength(num_word_prompt) > 9 && length == 9)) {
		return 0;
	}

	!! Si las palabras tienen la misma longitud, se comparan car�cter a
	!! car�cter y se retorna NO coincidente si se encuentra una diferencia:
	for (i = 0: i < length: i++) {
		if (WordAddress(num_word_prompt)->i ~=
				compare_word_tmp_text->(i+WORDSIZE)) {
			return 0;
		}
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
#Endif; ! _COMPARE_WORD_ROUTINE_;


!!==============================================================================
!!	Representa una elecci�n que puede ser seleccionada por el usuario.
!!------------------------------------------------------------------------------
Class	ChoiceSetItem
 with	!!----------------------------------------------------------------------
		!! Determina el n�mero de coincidencias entre la entrada del usuario y
		!! el �tem.
		!!----------------------------------------------------------------------
		compare_prompt [
			i j;
			self.hits = 0;
			if (self.keys ~= 0) {
				for (i = 0 : i < (self.#keys)/WORDSIZE : i++) {
					for (j = 1 : j <= num_words : j++) {
						if (CompareWord(j, self.&keys-->i)) {
							self.hits++;
						}
					}
				}
			}
		],
		!!----------------------------------------------------------------------
		!! Otras propiedades:
		!!----------------------------------------------------------------------
		!! Indica si el turno en que se trata este tema debe finalizar
		!! mostrando el inventario de temas restantes de la conversaci�n de la
		!! que forma parte.
		append_choice_set false,
		!! Descripci�n del �tem. Es el texto que se imprime al mostrar el
		!! listado de elecciones de un conjunto:
		entry 0,
		!! Indica si el �tem pone fin a la selecci�n:
		final_choice false,
   		!! N�mero de coincidencias de la entrada del usuario con el �tem:
   		hits 0,
		!! Palabras clave con las que el usuario puede hacer alusi�n al �tem:
		keys 0,
		!! Indica si el �tem es persistente. Cuando el gestor trata un �tem no
		!! persistente, autom�ticamente le da el atributo 'visited' para
		!! marcarlo como �tem ya seleccionado y luego lo elimina del conjunto
		!! (junto con todos sus parientes):
		persistent false,
		!! Rutina a ejecutar despu�s de seleccionar el �tem:
		reaction 0,
		!! Array de �tems relacionados. Cuando �ste se elimina, todos sus
		!! parientes se eliminan a su vez (y son marcados como tratados si �ste
		!! ha sido marcado tambi�n):
		relatives 0,
		!! Rutina a ejecutar cuando se selecciona el �tem:
		reply 0,
		!! Array de �tems que se a�aden al conjunto de elecciones tras tratar
		!! �ste:
		subchoices 0,
;


!!==============================================================================
!!	Representa un conjunto de elecciones que pueden ser seleccionadas y
!!	exploradas por el usuario. Implementa la siguiente interfaz:
!!------------------------------------------------------------------------------
Class	ChoiceSet
 with	!!----------------------------------------------------------------------
		!! A�ade un �tem al conjunto de elecciones (a menos que el �tem pasado
		!! como par�metro est� marcado como tratado ---atributo 'visited'---,
		!! en cuyo caso no hace nada). Los otros dos par�metros de la funci�n
		!! son opcionales y permiten a�adir �tems temporales. Si se invoca con
		!! 'temp_flag' como verdadero, el �tem formar� parte del conjunto de
		!! elecciones �nicamente durante una cantidad 'countdown' de turnos (si
		!! no se especifica un valor, se considera una cuenta atr�s de 1).
		!!
		!!	@param {ChoiceSetItem} choice - Elecci�n a a�adir al conjunto
		!!	@param {boolean} [temp_flag=false] - Indica si la nueva elecci�n es
		!!		temporal o no
		!!	@param {integer} [countdown=0} - Cantidad de turnos que ha de
		!!		permanecer la elecci�n en el conjunto (en caso de tratarse de
		!!		una elecci�n temporal)
		!!	@returns {boolean} Verdadero si la elecci�n se a�ade correctamente
		!!		al conjunto. Falso en caso contrario
		!!----------------------------------------------------------------------
		add_choice [ choice temp_flag countdown;
			!! Se comprueba que el tema pasado sea v�lido:
			if (choice == 0) return false;
			if (~~(choice ofclass ChoiceSetItem)) return false;
			if (choice has visited) return false;
			!! Si es necesario se establece como tema temporal:
			if (temp_flag) {
				if (countdown < 1) countdown = 1;
				self.temporal_choice = choice;
				StopTimer(self);
				StartTimer(self, countdown);
			}
			!! Se a�ade a la conversaci�n:
			move choice to self;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Invoca a la funci�n 'add_choice() para a�adir un �tem temporal a
		!! partir de los par�metros dados.
		!!
		!!	@param {ChoiceSetItem} choice - Elecci�n a a�adir al conjunto como
		!!		elecci�n temporal
		!!	@param {integer} [countdown=1] - Cantidad de turnos que ha de
		!!		permanecer la elecci�n en el conjunto
		!!	@returns {boolean} Verdadero si la elecci�n se a�ade correctamente
		!!		al conjunto como elecci�n temporal. Falso en caso contrario
		!!----------------------------------------------------------------------
		add_temporal_choice [ choice countdown;
			return self.add_choice(choice, true, countdown);
		],
		!!----------------------------------------------------------------------
		!! A�ade al conjunto las sub-elecciones (si tiene alguna) de aquella
		!! pasada como par�metro.
		!!
		!!	@param {ChoiceSetItem} choice - Se a�aden las sub-elecciones
		!!		definidas para 'choice'
		!!	@returns {boolean} Verdadero si los sub-�tems se a�aden con �xito.
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		add_subchoices [ choice
			i;
			if ((choice == 0) || ~~(choice provides subchoices)) return false;
			if (choice.subchoices ~= 0) {
				for (i=0 : i<(choice.#subchoices)/WORDSIZE : i++) {
					self.add_choice(choice.&subchoices-->i);
				}
			}
			return true;
		],
		!!----------------------------------------------------------------------
		!! Marca un conjunto de elecciones como agotado. (Para hacerlo se
		!! utiliza el atributo 'general' contemplado por la librer�a Inform.)
		!!
		!!	@returns {boolean} Verdadero para indicar que el conjunto se ha
		!!		marcado como agotado con �xito
		!!----------------------------------------------------------------------
		end [;
			give self general;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones est� o no agotado.
		!!
		!!	@returns {boolean} Verdadero si el conjunto est� agotado. Falso en
		!!		caso contrario
		!!----------------------------------------------------------------------
		has_ended [;
			return (self has general);
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones tiene la elecci�n concreta
		!! pasada como par�metro.
		!!
		!!	@param {ChoiceSetItem} choice
		!!	@returns {boolean} Verdadero si el conjunto tiene la elecci�n dada.
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		has_choice [ choice;
			return parent(choice) == self;
		],
		!!----------------------------------------------------------------------
		!! Elimina un �tem del conjunto de elecciones. Si se invoca con
		!! 'visited_flag' verdadero, se fuerza adem�s que el �tem quede marcado
		!! como tratado aunque no haya llegado a mostrarse al usuario en
		!! realidad.
		!!
		!!	@returns {boolean} Verdadero si la elecci�n se elimina con �xito
		!!		del conjunto. Falso en caso contrario
		!!----------------------------------------------------------------------
		remove_choice [ choice visited_flag
			obj i x;
			if ((choice == 0) || (parent(choice) ~= self)) return false;
			if (visited_flag) give choice visited;
			!! Se marca a los parientes de la elecci�n como tratados (si
			!! procede), y se eliminan del conjunto (si est�n en �l):
			if (choice.relatives ~= 0) {
				for (i=0 : i<(choice.#relatives)/WORDSIZE : i++) {
					x = choice.&relatives-->i;
					if (choice has visited) give x visited;
					for (obj=child(self) : obj~=nothing : obj=sibling(obj)) {
						if (obj == x) {
							remove x;
							break;
						}
					}
				}
			}
			!! Se elimina la elecci�n:
			remove choice;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Si hay alguna elecci�n temporal en el conjunto, la elimina.
		!!
		!!	@returns {boolean} Verdadero si elimina la elecci�n temporal del
		!!		conjunto correctamente. Falso en caso contrario
		!!----------------------------------------------------------------------
		remove_temporal_choice [
			x;
			if (self.temporal_choice ~= 0) {
				x = self.temporal_choice;
				self.temporal_choice = 0;
				StopTimer(self);
				self.time_left = -1;
				self.remove_choice(x);
				return true;
			}
			return false;
		],
		!!----------------------------------------------------------------------
		!! Retorna el n�mero de elecciones del conjunto.
		!!
		!!	@returns {integer} N�mero de elecciones del conjunto
		!!----------------------------------------------------------------------
		get_size [
			choice size;
			choice = 0; ! para evitar un desconcertante warning del compilador
			objectloop(choice in self) size++;
			return size;
		],
		!!----------------------------------------------------------------------
		!! Ordena aleatoriamente e imprime un listado con el conjunto de
		!! elecciones. Si la entidad tiene definida la propiedad 'title', �sta
		!! se imprime antes de mostrar el resto del listado.
		!!----------------------------------------------------------------------
		show_choice_set [
			choice size i n;
			!! XXX - Puesto que el temporizador comprueba si se deben eliminar
			!! las elecciones temporales al finalizar el turno (es decir, justo
			!! despu�s de mostrar el conjunto de elecciones), puede ocurrir que
			!! algunas de las elecciones del listado no est�n en realidad
			!! disponibles. Por ello, antes de imprimir el listado, si procede
			!! se eliminan las elecciones temporales.
			if (self.time_left == 0) self.remove_temporal_choice();

			!! Si el conjunto tiene una propiedad 'title' definida, se imprime:
			if (self.title ~= 0) {
				switch (metaclass(self.title)) {
					Object:		print (The) self.title;
					String:		print (string) self.title;
					Routine:	indirect(self.title);
				}
				print ": ";
			}

			!! Se calcula el n�mero de temas de la conversaci�n:
			size = self.get_size();

			!! Se imprimen los mensajes previos al inventario:
			if ((size == 0) && (CSET_NO_MSG ~= 0))
				print (string) CSET_NO_MSG;
			if ((size > 0) && (CSET_MSG1 ~= 0))
				print (string) CSET_MSG1;
			if ((size > 1) && (CSET_MSG2 ~= 0))
				print (string) CSET_MSG2;

			!! Se recolocan los temas en la conversaci�n de forma aleatoria:
			for (i = size : i > 0 : i--) {
				n = random(i);
				choice = child(self);
				while (n > 1) {
					choice = sibling(choice);
					n--;
				}
				move choice to ChoiceBag;
			}
			while (child(ChoiceBag)) move child(ChoiceBag) to self;

			!! Por �ltimo se imprime el listado de �tems:
			for (choice = child(self) : choice~=nothing
					: choice = sibling(choice)) {
				PrintOrRun(choice, entry, true);
				if (sibling(choice) ~= nothing) {
					if (sibling(sibling(choice)) == nothing) {
						if (CSET_OR ~= 0) {
							print (string) CSET_OR;
						}
					} else {
						if (CSET_COMMA ~= 0) {
							print (string) CSET_COMMA;
						}
					}
				}
			}
			return true;
		],
		!!----------------------------------------------------------------------
		!! Otras propiedades:
		!!----------------------------------------------------------------------
		!! Acci�n al intentar activar un conjunto de elecciones agotado:
		final_action 0,
		!! Acci�n al activar un conjunto de elecciones:
		initial_action 0,
		!! Acci�n al intentar activar un conjunto de elecciones ya activado:
		inter_action 0,
		!! Permite indicar un t�tulo para el conjunto que se imprimir� junto
		!! con el listado de elecciones:
		title 0,
		!! La siguiente propiedad ofrece soporte para bloquear el conjunto, de
		!! forma que mientras un conjunto se encuentre bloqueado se fuerce al
		!! usuario a seleccionar una de las elecciones sin posibilidad de
		!! hacer ninguna otra interacci�n. Para implementar esta funcionalidad
		!! se debe incluir incluir una rutina 'react_before' en el objeto que
		!! lanza el sistema CHOICE SET. (Consultar TEST para ver un ejemplo de
		!! uso de un conjunto bloqueado.)
		fixed false,
		!! Temporizadores:
		time_left -1,
		time_out [; self.remove_temporal_choice(); ],
 private
		!! Guarda el tema temporal.
		temporal_choice 0;


!!==============================================================================
!!	Objeto gestor que controla la l�gica del sistema. Su funci�n principal,
!!	run(), debe invocarse desde el punto de entrada *BeforeParsing()* (crear
!!	este punto de entrada si no existe):
!!
!!		[ BeforeParsing;
!!			ChoiceSetManager.run();
!!		];
!!------------------------------------------------------------------------------
Object ChoiceSetManager "(ChoiceSet Manager)"
 with	!!----------------------------------------------------------------------
		!! Retorna el valor de la propiedad 'choice_set_flag' utilizado por la
		!! acci�n 'CSETSelected' para determinar si debe listar o no el
		!! conjunto de elecciones activo.
		!!
		!!	@returns {boolean} Propiedad 'choice_set_flag' del objeto
		!!----------------------------------------------------------------------
		get_choice_set_flag [;
			return self.choice_set_flag;
		],
		!!----------------------------------------------------------------------
		!! Indica si el conjunto de elecciones pasado como par�metro est� o no
		!! activado en el gestor. Si no se pasa ning�n par�metro, indica si hay
		!! activado un conjunto de elecciones cualquiera.
		!!
		!!	@param {ChoiceSet} [choiceSet] - Si se especifica uno, la funci�n
		!!		indica si el conjunto 'choiceSet' est� activado en el gestor
		!!	@returns {boolean} Verdadero si el conjunto pasado como par�metro
		!!		est� activo (si no se ha especificado uno, retorna verdadero en
		!!		caso de que haya un conjunto cualquiera activado en el gestor).
		!!		Falso en caso contrario
		!!----------------------------------------------------------------------
		is_running [ choiceSet;
			if (choiceSet ~= nothing) {
				return self.current_choice_set == choiceSet;
			} else return self.current_choice_set ~= nothing;
		],
		!!----------------------------------------------------------------------
		!! Funci�n principal del gestor. Comprueba si la entrada de usuario se
		!! refiere a alguna de las elecciones disponibles en el conjunto
		!! activo y lanza la acci�n adecuada para tratarla si es as�. Debe
		!! invocarse desde el punto de entrada 'BeforeParsing()'.
		!!
		!!	@returns {boolean} Falso, para que el flujo de ejecuci�n del relato
		!!		interactivo contin�e normalmente
		!!----------------------------------------------------------------------
		run [
			o o_tmp_hits;
			if (self.current_choice_set) {
				if (self.current_choice_set.has_ended()) return false;

				!! A) Inicializaciones del m�todo:
				self.choice_set_flag = false;
				self.hits = 0;
				self.selected_choice = 0;

				!! B) Explora las elecciones del conjunto actual, comprobando
				!! si alguna encaja con la entrada de usuario:
				objectloop (o in self.current_choice_set) {
					#Ifdef DEBUG_CHOICE_SET;
					print "Probando: ", (string) o.entry, "... ";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Se calcula el n�mero de coincidencias de la elecci�n en
					!! relaci�n al total de palabras de la entrada (en %):
					o.compare_prompt();
					o_tmp_hits = (o.hits*100) / num_words;

					#Ifdef DEBUG_CHOICE_SET;
					print "Ajuste de ", o.hits, " sobre ",
					o.#keys / WORDSIZE, " palabras: ", o_tmp_hits, "%^";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Si la elecci�n coincide con m�s exactitud que la
					!! mejor provisional:
					if (o_tmp_hits > self.hits) {
						self.hits = o_tmp_hits;
						self.selected_choice = o;
					}
				}

				!! C) Si se ha seleccionado una elecci�n, se ejecutan las
				!! acciones asociadas a ella, se elimina del conjunto (si
				!! procede), y se a�aden las posibles sub-elecciones:
				if (self.hits) {
					#Ifdef DEBUG_CHOICE_SET;
					print "Tema seleccionado: ",
					(string) self.selected_choice.entry, "^";
					#Endif; ! DEBUG_CHOICE_SET;

					!! Si no es persistente, la elecci�n queda marcada como
					!! tratada:
					if (~~(self.selected_choice.persistent)) {
						give self.selected_choice visited;
					}

					!! Acci�n al seleccionar la elecci�n:
					if (self.selected_choice.reply ~= 0) {
						PrintOrRun(self.selected_choice, reply);
					}

					!! Se establece la propiedad 'choice_set_flag' del gestor
					!! en funci�n de las propiedades de la elecci�n:
					self.choice_set_flag
						= self.selected_choice.append_choice_set;

					!! La elecci�n se elimina del conjunto si est� agotada y
					!! se a�aden todas sus sub-elecciones (si tiene alguna):
					if (self.selected_choice has visited) {
						self.current_choice_set.remove_choice(
							self.selected_choice);
					}
					self.current_choice_set.add_subchoices(
						self.selected_choice);

					!! Acci�n despu�s de tratar la elecci�n:
					if (self.selected_choice.reaction ~= 0) {
						PrintOrRun(self.selected_choice, reaction);
					}

					!! Si es un �tem final, termina la selecci�n:
					if (self.selected_choice.final_choice) {
						self.current_choice_set.end();
					}

					!! Se modifica la entrada de usuario para que la librer�a
					!! lance la acci�n de apoyo ##CSETSelected (referenciada
					!! por el verbo de apoyo 'cset.selected'):
					parse-->1 = 'cset.selected';
					num_words = 1;
					!! A partir de este punto, la librer�a Inform lanzar� la
					!! acci�n ##CSETSelected, encargada de listar el conjunto
					!! de elecciones (si es preciso).
				}
			}

			!! Retorna de la funci�n y deja el flujo de ejecuci�n de nuevo en
			!! manos de la librer�a, para que haga el tratamiento normal de la
			!! entrada del usuario:
			return false;
		],
		!!----------------------------------------------------------------------
		!! Lista el conjunto de elecciones activo.
		!!
		!!	@returns {boolean} Verdadero si el conjunto se lista correctamente.
		!!		Falso si no hay un conjunto de elecciones activo en el gestor
		!!----------------------------------------------------------------------
		show_choice_set [
			st;
			if (self.current_choice_set == 0) return false;
			#Ifdef _TYPES_;
			st = _current_style;
			#Ifnot;
			st = 0; ! Por evitar warnings del compilador
			#Endif; ! _TYPES_;
			switch (CSET_STYLE) {
			0:	!! Estilo: Romana
				#Ifdef TARGET_ZCODE;
				font_on; style roman;
				#Ifnot; ! TARGET_GLULX;
				glk($0086, 0);
				#Endif;	! TARGET_
			1:	!! Estilo: It�lica
				#Ifdef	TARGET_ZCODE;
				font on; style underline;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 1);
				#Endif;	! TARGET_
			2:	!! Estilo: Negrita
				#Ifdef	TARGET_ZCODE;
				font on; style bold;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 3);
				#Endif;	! TARGET_
			3:	!! Estilo: Monoespaciada
				#Ifdef	TARGET_ZCODE;
				font off;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 2);
				#Endif;	! TARGET_
			}
			if (CSET_PREFIX ~= 0) print (string) CSET_PREFIX;
			self.current_choice_set.show_choice_set();
			if (CSET_SUFIX ~= 0) print (string) CSET_SUFIX;
			#Ifdef	TARGET_ZCODE;		!!
			font on; style roman;		!!
			#Ifnot;	! TARGET_GLULX;		!! Romana
			glk($0086, 0);				!!
			#Endif; ! TARGET_			!!
			#Ifdef _TYPES_;
			SetTextStyle(st);
			#Endif; ! _TYPES_;
			new_line;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Inicia y deja activo en el gestor el conjunto de elecciones pasado
		!! como par�metro. Si adem�s se invoca con 'no_action' verdadero, se
		!! evita la ejecuci�n de las acciones asociadas a la activaci�n (o
		!! reactivaci�n) del conjunto.
		!!
		!!	@param {ChoiceSet} choice_set - Conjunto de elecciones que se
		!!		activa en el gestor
		!!	@param {boolean} [no_action=false] - Si se invoca como verdadero,
		!!		evita la ejecucci�n de las acciones asociadas con la activaci�n
		!!		y reactivaci�n del conjunto
		!!	@returns {boolean} Verdadero si el conjunto de elecciones se activa
		!!		(o reactiva) correctamente. Falso si el conjunto no es v�lido o
		!!		est� marcado como agotado
		!!----------------------------------------------------------------------
		start [ choice_set no_action;
			!! Se comprueba que el conjunto pasado sea v�lido:
			if ((choice_set == 0) || ~~(choice_set ofclass ChoiceSet)) {
				#Ifdef DEBUG_CHOICE_SET;
				print "ERROR. El conjunto introducido no es v�lido.^";
				#Endif;
				return false;
			}
			!! Si el conjunto est� agotado, se ejecuta su acci�n final (si hay
			!! una definida) y retorna:
			if (choice_set.has_ended()) {
				if ((choice_set.final_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, final_action);
				}
				return false;
			}
			!! Si el conjunto ya est� activado, ejecuta su acci�n de conjunto
			!! en ejecuci�n (si hay una definida):
			if (self.is_running(choice_set)) {
				if ((choice_set.inter_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, inter_action);
					new_line;
				}
			}
			!! Se ejecuta la acci�n inicial del conjunto (si hay una definida)
			!! y lo activa en el gestor:
			else {
				if ((choice_set.initial_action ~= 0) && ~~(no_action)) {
					PrintOrRun(choice_set, initial_action);
					new_line;
				}
				self.current_choice_set = choice_set;
			}
			!! Imprime el listado de elecciones del conjunto activo:
			self.show_choice_set();
			return true;
		],
		!!----------------------------------------------------------------------
		!! Quita del gestor el conjunto activo.
		!!
		!!	@returns {boolean} Verdadero
		!!----------------------------------------------------------------------
		stop [;
			self.current_choice_set = 0;
			return true;
		],
		!!----------------------------------------------------------------------
		!! Retorna el tama�o del conjunto de elecciones activo en el gestor.
		!!
		!!	@returns {integer} N�mero de elecciones del conjunto activo
		!!----------------------------------------------------------------------
		get_size [;
			if (self.is_running()) return self.current_choice_set.get_size();
			else return 0;
		],
 private
		 !! Indica si hay que mostrar el inventario de temas al terminar de
		 !! desarrollar uno de los temas de la conversaci�n actual.
		 choice_set_flag false,
 		!! Conversaci�n actual activa en el gestor.
 		current_choice_set 0,
		!! N�mero de coincidencias del tema con m�s coincidencias de la
		!! conversaci�n (en tanto por 100 sobre el n�mero de palabras clave).
		hits 0,

		!! Tema con mayor porcentaje de coincidencias hasta el momento.
		!! FIXME
		selected_choice 0,
;


!!==============================================================================
!!	Definici�n de la acci�n de apoyo (y su gram�tica) que se lanza si se
!!	reconoce en la entrada de usuario un intento de tratar alguna de las
!!	elecciones del conjunto activo en el gestor.
!!------------------------------------------------------------------------------
Verb	'cset.selected'
	*								-> CSETSelected
	* topic							-> CSETSelected
;

[ CSETSelectedSub;
	if (ChoiceSetManager.is_running()) {
		if (ChoiceSetManager.get_choice_set_flag()) {
			new_line;
			ChoiceSetManager.show_choice_set();
		}
	}
	return false;
];


!!------------------------------------------------------------------------------
!! FIXME
#Ifdef TEST_CHOICE_SET;
Constant Story "ChoiceSet Test";

Include "Parser";
Include "Verblib";

[ Initialise;
	location = Habitacion;
	lookmode = 2;
];

[ BeforeParsing;
	ChoiceSetManager.run();
];

Include "SpanishG.h";

Extend	'habla' replace
	* noun						-> TalkTo
	* 'a'/'con' noun			-> TalkTo
;

[ TalkToSub;
	if (noun == player) "Hablar con uno mismo es una locura.";
	if (noun hasnt animate) "Eso no podr�a contestarte.";
	print_ret (The) noun, " no parece", (n) noun, " interesad", (o) noun,
	" en hablar contigo.";
];

Object	Habitacion "Habitaci�n"
 with	description
			"Hay una persona en la habitaci�n. Teclea HABLAR CON PERSONA para
			iniciar una conversaci�n con ella.",
 has	light;

Object	-> "persona"
 with	name 'persona' 'individuo' 'ser' 'hombre' 'pepe' 'pepito',
		react_before [;
			CSETSelected, TalkTo:
				return false;
			default:
				if (conversaction.fixed) <<TalkTo self>>;
		],
		before [;
			TalkTo:
				ChoiceSetManager.start(conversacion);
				return true;
			default:
				"Teclea HABLAR CON PERSONA para hablar con ella.";
			],
 has	animate concealed female;

ChoiceSet conversaction "(Conversaci�n con la persona)"
 with	initial_action [;
			self.add_choice(cset_item_1);
			self.add_choice(cset_item_2);
			self.add_choice(cset_item_4);
			"---Hola.";
		],
		inter_action [;
			"El hombre te mira, curioso.";
		],
		final_action [;
			"No hay nada m�s que comentar.";
		];

ChoiceSetItem	cset_item_1
 with	entry	"preguntar nombre",
		keys	'preguntar' 'pregunta' 'nombre',
		reply [;
			"---Me presento,---le dices--- mi nombre es Don Pepito. �Puedo
			preguntarle el suyo?
			^^
			---Por supuesto Don Pepito, faltar�a m�s. Encantado de conocerle,
			yo soy Don Jos�. Don Jos� Villaescusa Lacio.";
		],
		subchoices cset_item_12,
		append_choice_set true;

ChoiceSetItem	cset_item_12
 with	entry	"interesarte por sus apellidos",
		keys	'apellidos' 'apellido',
		reply [;
			"---Apellidos curiosos, �de d�nde vienen, si me permite la
			indiscreci�n?
			^^
			---Se la permito, por supuesto. Se va a sorprender usted; vienen de
			mi padre, uno, y de mi madre el segundo. Curioso, �no es as�?";
		],
		reaction [;
			!! Alternativo a utilizar la propiedad *subchoices*:
			conversacion.add_topic(cset_item_3);
		],
		append_choice_set true;

ChoiceSetItem	cset_item_2
 with	entry	"investigar en qu� trabaja",
		keys	'trabaja' 'trabajo',
		reply [;
			"---�Tendr�a la bondad de explicarme su trabajo?
			^^
			---Mi querido amigo, yo hago de todo, pero digamos que
			principalmente me dedico al ramo de los viajes.";
		],
		subchoices cset_item_21 cset_item_22,
		append_choice_set true;

ChoiceSetItem	cset_item_21
 with	entry	"preguntar sobre los viajes"
		keys	'viajes',
		reply [;
			"---Oh, viajes. �Me encanta viajar! Claro que como turista. Supongo
			que dedicarse a ello debe resultar cansado.
			^^
			---Cansado y aburrido. No imagina usted lo tedioso que es explicar
			las mismas cosas sobre la Torre Eiffel una y otra vez. Un
			aut�ntico tost�n... perdone el exabrupto.";
		],
		append_choice_set false;

ChoiceSetItem	cset_item_22
 with	entry	"pedir que te aclare qu� quiere decir con ~de todo~",
		keys	'aclarar' 'aclare' 'decir' 'todo',
		reply [;
			"---Perdone, Don Jos�. �De todo? �A qu� se refiere?
			^^
			---Oh, pues exactamente a eso, Don Pepito. Un poco a todo tipo de
			negocio; apuestas, inversiones en bolsa, compra-venta de activos,
			robo de bancos... cualquier cosa que usted imagine. ---Sonr�e.
			---No ponga esa cara, hombre. Era broma, por supuesto.";
		]
		append_choice_set false;

ChoiceSetItem	cset_item_3
 with	entry	"insultarle",
		keys	'insultar' 'insulta' 'insultarle' 'insultale'
		reply [;
			"---Me parece usted un borde.
			^^
			---�C�mo dice? Retire eso, por favor.";
		],
		append_choice_set true;

ChoiceSetItem	cset_item_31
 with	entry	"negarse",
		keys	'negarse' 'negate' 'negar' 'negarte',
		reply [;
			"---�Jam�s! Es usted un borde. �Un borde!
			^^
			---Amigo m�o, estoy ya ha pasado de casta�o oscuro. No pienso
			tolerar m�s insultos. Zanjo aqu� nuestra conversaci�n. Que tenga
			usted buen d�a.";
		],
		append_choice_set false;

ChoiceSetItem	cset_item_32
 with	entry	"retirar el insulto"
		keys	'retirar' 'retira' 'insulto',
		reply [;
			"---Disc�lpeme. Reconozco que ha sido una descortes�a. Y era una
			afirmaci�n infundada, adem�s.
			^^
			---No hay nada que disculpar. Olvidemos esta absurda disgresi�n
			de nuestra agradable conversaci�n.";
		],
		append_choice_set true;

ChoiceSetItem	cset_item_4
 with	entry	"saludarle con el sombrero"
		keys	'saludar' 'saluda' 'saludarle' 'saludale' 'sombrero',
		reply [;
			"Inclinas el ala de tu sombrero en un gesto amistoso, y �l te
			responde con un gesto id�ntico.";
		],
		append_choice_set true,
		permanent true;

#Endif; ! TEST_CHOICE_SET;
!!------------------------------------------------------------------------------

#Endif; ! _CHOICE_SET_;
