

!!==============================================================================
!!
!!	TOPIC INVENTORY
!!	Sistema de conversaci�n con inventario de temas
!!
!!==============================================================================
!!
!!	File:			topicInventory.h
!!	Author(s):		J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!					Mastodon
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		Z-Machine / Glulx
!!	Version:		2.1
!!	Released:		2014/06/12
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	2.1: 2014/06/12	Modificaciones en la propiedad *show_topic_inventory* del 
!!					objeto gestor. Nueva constante CONVERSATION_COMMA.
!!	2.0: 2014/04/03	Mejora la gesti�n del cambio de distintas conversaciones y 
!!					a�ade temas con presencia temporizada, temas relacionados 
!!					(an�logos a los subtopics, pero a la inversa; se eliminan 
!!					al eliminar un tema), y otras peque�as modificaciones. 
!!					Envuelve la rutina *CompareWord(num_word_prompt, dictword)* 
!!					entre #Ifdefs; para evitar que se incluya si ya se ha 
!!					definido previamente en alg�n archivo externo.
!!	1.8: 2014/02/05	Cambiado el nombre de la clase *ConversationEntry* por 
!!					*ConversationTopic* y otras peque�as correcciones.
!!	1.7: 2014/01/29	Cambiados los nombres de las clases y peque�as correcciones.
!!	1.4: 2013/04/13	Modificaci�n de la propiedad *show_topic_inventory* del 
!!					objeto gestor.
!!	1.3: 2013/04/01 A�adidas nuevas propiedades a la clase *ConversationTopic* 
!!					y modificaci�n de la rutina *NPCTalkSub()*.
!!	1.2: 2013/03/30	A�adidos a la documentaci�n.
!!	1.1: 2013/03/30 A�adidas nuevas propiedades al objeto *ConversationManager* 
!!					y modificaci�n de la rutina *NPCTalkSub()*.
!!	1.0: 2013/03/30	Primera versi�n de la extensi�n.
!!	0.1: 2013/03/28	Versi�n preliminar.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2009, Mastodon
!!	Copyright (c) 2013, 2014, J. Francisco Mart�n
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
!!
!!	# INTRODUCCI�N
!!
!!	*TOPIC INVENTORY* es una extensi�n para implementar sistemas de 
!!	conversaci�n utilizando inventario de temas y an�lisis no estricto de la 
!!	entrada de usuario para el reconocimiento de patrones. Est� basada en las 
!!	notas de Eric Eve sobre sistemas de conversaci�n:
!!	<http://www.tads.org/howto/convbkg.htm>, y construida sobre la extensi�n 
!!	*NPC_Conversacion* v1.0 de Mastodon.
!!
!!
!!	# CONVERSACIONES CON INVENTARIO DE TEMAS
!!
!!	El sistema de conversaci�n con invantario de temas est� ideado con el 
!!	objetivo de esquivar los problemas que suelen presentar los sistemas de 
!!	conversaci�n m�s habituales en los relatos interactivos; dificultades para 
!!	adivinar la palabra clave en sistemas basados en acciones ASK/TELL, 
!!	simplificaci�n excesiva en sistemas basados en la acci�n TALK TO, o falta 
!!	de libertad y ruptura de la interfaz textual en sistemas de men�s. 
!!
!!	Al utilizar un inventario de temas, en esencia, se presenta al usuario una 
!!	lista de temas de conversaci�n sugeridos bas�ndose en el conocimiento del 
!!	personaje protagonista. De esta forma, el usuario puede hacer referencia a 
!!	los temas que quiera lanzar utilizando una interfaz similar a la de los 
!!	sistemas ASK/TELL, pero sin necesidad de tener que adivinar por s� mismo la 
!!	palabra clave que lanza el tema.
!!
!!	En concreto, el sistema se presentar�a de forma similar a la siguiente:
!!
!!		> hablar con Bob
!!		---Disculpe...
!!		Bob levanta la vista de su libro y se quita las gafas- ---�Si?
!!
!!		(Puedes preguntar por la antena, hablarle sobre el faro o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> hablar sobre el faro
!!		---He pasado junto al faro esta ma�ana ---empiezas.
!!		Bob se pone muy nervioso de pronto. ---�De qu� est�s hablando? Esa cosa 
!!		se vino abajo hace a�os. Despu�s de aquel... asunto.
!!
!!		> hablar con Bob
!!		Bob simula limpiar las gafas, inquieto. 
!!
!!		(Puedes preguntar por la antena, preguntar por el asunto o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> asunto
!!		---�A qu� "asunto" te refieres?
!!		Bob se coloca las gafas y vuelve de nuevo su atenci�n al libro, 
!!		claramente agitado. ---T-Tengo mucho trabajo que hacer. Si me 
!!		disculpas...
!!
!!		(Puedes insistir con el "asunto", preguntar por la antena o hablarle 
!!		del tema que nunca se acaba.)
!!
!!		> tema interminable
!!		---T�o, �d�nde est� mi coche?
!!		---�Y tu coche, t�o?
!!
!!		(Puedes insistir con el "asunto", preguntar por la antena o hablarle 
!!		del tema que nunca se acaba.)
!!
!!	El reconocimiento de patrones entre la entrada de usuario y las claves de 
!!	cada tema se lleva a cabo por medio de an�lisis no estricto; si entre todas 
!!	las palabras introducidas se reconocen claves de uno o m�s temas, se lanza 
!!	aquel tema con m�s coincidencias ignorando el resto de la entrada.
!!
!!
!!	# SOBRE LOS MENSAJES
!!
!!	El autor puede definir hasta 8 constantes para modificar los textos por 
!!	defecto de la extensi�n:
!!
!!	 *	TINV_STYLE: (0-3) Define el estilo con el que se imprimen los textos de 
!!		la extensi�n: 0-romana, 1-it�lica, 2-negrita, 3-monoespaciada.
!!
!!	 *	TINV_PREFIX: Cadena de texto previa a cualquier otro mensaje.
!!
!!	 *	TINV_SUFIX: Cadena de texto posterior a cualquier otro mensaje.
!!
!!	 *	TINV_MSG1: Antecede a la lista de temas del inventario.
!!
!!	 *	TINV_MSG2: Si hay m�s de un tema en el inventario, se imprime entre 
!!		TINV_MSG1 y la lista de temas.
!!
!!	 *	TINV_COMMA: Separador de los temas del inventario.
!!
!!	 *	TINV_OR: Separador de los dos �ltimos temas del inventario.
!!
!!	 *	TINV_NO_MSG: Mensaje cuando no hay temas en el inventario.
!!
!!
!!	# UTILIZACI�N
!!
!!	Para usar la librer�a �nicamente hay que incluir la siguiente l�nea en la 
!!	rutina BeforeParsing (crearla si no existe):
!!
!!		[ BeforeParsing;
!!			ConversationManager.run();
!!		];
!!
!!
!!	# LIMITACIONES Y POSIBLES MEJORAS
!!
!!	Podr�a ser interesante contemplar la posibilidad de crear temas ocultos que 
!!	no aparezcan sugeridos autom�ticamente al imprimir el inventario de temas 
!!	disponibles.
!!
!!------------------------------------------------------------------------------
System_file;

!! Descomentar para obtener info. de depuraci�n del controlador:
!Constant DEBUG_TOPICINVENTORY;

!! Descomentar para obtener info. de depuraci�n de la rutina CompareWord():
!Constant DEBUG_COMPARE_WORD_ROUTINE;

!! Estilo y textos por defecto de la extensi�n:
Default TINV_STYLE	1; ! (0-3)
Default TINV_PREFIX	"(";
Default TINV_SUFIX	".)";
Default TINV_MSG1	"Puedes ";
Default TINV_MSG2	"escoger entre ";
Default TINV_COMMA	", ";
Default TINV_OR		" o ";
Default TINV_NO_MSG	"No hay temas que tratar";

!! Objeto de apoyo para reordenar los temas de una conversaci�n:
Object	TopicBag "(Topic Bag)";


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
!!	Representa un tema sobre el que se puede hablar en una conversaci�n.
!!------------------------------------------------------------------------------

Class	ConversationTopic
 with	!! Determina el n�mero de coincidencias entre la entrada del usuario y 
		!! el tema.
		compare_prompt [i j;
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
		!! N�mero de coincidencias de la entrada del usuario con el tema.
		hits 0,
		!! Descripci�n del tema. Es el texto que se imprime al mostrar el 
		!! inventario de temas de una conversaci�n.
		entry 0,
		!! Palabras clave con las que el usuario puede hacer alusi�n al tema.
		keys 0,
		!! Rutina a ejecutar cuando se selecciona el tema.
		reply 0,
		!! Rutina a ejecutar despu�s de tratar el tema.
		reaction 0,
		!! Vector de temas relacionados. Cuando �ste se elimina, todos sus 
		!! parientes se eliminan a la vez (y se marcan adem�s como tratados si 
		!! lo est� tambi�n �l).
		relatives 0,
		!! Vector de temas que se a�aden a la conversaci�n tras tratar �ste.
		subtopics 0,
		!! Indica si el turno en que se trata este tema debe finalizar 
		!! mostrando el inventario de temas restantes de la conversaci�n de la 
		!! que forma parte.
		append_topic_inventory true,
		!! Indica si el tema es persistente. Cuando el gestor trata un tema no 
		!! persistente, autom�ticamente le da el atributo *visited* para 
		!! marcarlo como tema tratado y luego lo elimina de la conversaci�n.
		persistent false;

!!==============================================================================
!!	Representa una conversaci�n con una lista de temas que pueden ser tratados 
!!	a elecci�n del usuario. Implementa las siguientes funciones:
!!
!!	 *	add_topic(topic:ConversationTopic, temp_flag:boolean, period:integer) - 
!!		A�ade un tema a la conversaci�n (a menos que el tema pasado como 
!!		par�metro est� marcado como ya tratado). Los otros dos par�metros son 
!!		opcionales y permiten a�adir temas temporales. Si se invoca con 
!!		*temp_flag* como verdadero, el tema formar� parte de la conversaci�n 
!!		�nicamente durante una cantidad *period* de turnos (si no se indica un 
!!		valor, por defecto se considera periodo de 1).
!!
!!	 *	add_temporal_topic(topic:ConversationTopic, period:integer) - Invoca a 
!!		la funci�n add_topic para a�adir un tema temporal a partir de los 
!!		par�metros dados.
!!
!!	 *	add_subtopics(topic:ConversationTopic) - A�ade a la conversaci�n los 
!!		subtemas del tema pasado como par�metro (si tiene alguno).
!!
!!	 *	end() - Marca la conversaci�n como finalizada.
!!
!!	 *	has_ended() - Indica si la conversaci�n ha finalizado o no.
!!
!!	 *	remove_topic(topic:ConversationTopic, visited_flag:boolean) - Elimina 
!!		un tema de la conversaci�n. Si se invoca con *visited_flag* verdadero, 
!!		adem�s se fuerza que el tema quede marcado como tratado aunque no haya 
!!		llegado a mostrarse al jugador en realidad.
!!
!!	 *	remove_temporal_topic() - Si hay alg�n tema temporal en la conversaci�n 
!!		lo elimina.
!!
!!	 *	topic_inventory_size() - Retorna el n�mero de temas de la conversaci�n.
!!
!!	 *	show_topic_inventory(flag:boolean) - Ordena aleatoriamente e imprime el 
!!		inventario de temas. Si se invoca con *flag* verdadero y la 
!!		conversaci�n tiene definida la propiedad *talker*, �sta se imprime 
!!		antes de imprimir el inventario.
!!------------------------------------------------------------------------------

Class	Conversation
 with	add_topic [ topic temp_flag period;
			!! Se comprueba que el tema pasado sea v�lido:
			if (topic == 0) return false;
			if (~~(topic ofclass ConversationTopic)) return false;
			if (topic has visited) return false;
			!! Si es necesario se establece como tema temporal:
			if (temp_flag) {
				if (period < 1) period = 1;
				self.temporal_topic = topic;
				StopTimer(self);
				StartTimer(self, period);
			}
			!! Se a�ade a la conversaci�n:
			move topic to self;
			return true;
		],
		add_temporal_topic [ topic period;
			return self.add_topic(topic, true, period);
		],
		add_subtopics [ topic i;
			if ((topic == 0) || ~~(topic provides subtopics)) return false;
			if (topic.subtopics ~= 0) {
				for (i=0 : i<(topic.#subtopics)/WORDSIZE : i++) {
					self.add_topic(topic.&subtopics-->i);
				}
			}
			return true;
		],
		end [;
			give self general;
		],
		has_ended [;
			if (self has general) return true;
			else return false;
		],
		remove_topic [ topic visited_flag obj i x;
			if (parent(topic) ~= self) return false;
			if (visited_flag) give topic visited;
			!! Se marca a los parientes del tema como tratados (si procede), y 
			!! se eliminan de la conversaci�n (si est�n en ella):
			if (topic.relatives ~= 0) {
				for (i=0 : i<(topic.#relatives)/WORDSIZE : i++) {
					x = topic.&relatives-->i;
					if (topic has visited) give x visited;
					for (obj=child(self) : obj~=nothing : obj=sibling(obj)) {
						if (obj == x) {
							remove x;
							break;
						}
					}
				}
			}
			!! Se elimina el tema:
			remove topic;
			return true;
		], 
		remove_temporal_topic [;
			self.remove_topic(self.temporal_topic);
			StopTimer(self);
			self.time_left = -1;
			self.temporal_topic = 0;
		],
		topic_inventory_size [ topic size;
			topic = 0; ! para evitar un desconcertante warning del compilador
			objectloop(topic in self) size++;
			return size;
		],
		show_topic_inventory [ flag		topic size i n;
			!! XXX - Puesto que el temporizador comprueba si se deben eliminar 
			!! los temas temporales al finalizar el turno (es decir, despu�s de 
			!! de mostrar el inventario de temas), puede ocurrir que algunos de 
			!! los temas del listado no est�n en realidad disponibles. Por 
			!! ello, antes de imprimir el inventario, si procede se eliminan 
			!! los temas temporales.
			if (self.time_left == 0) self.remove_temporal_topic();

			!! Si la funci�n se invoca con *flag* activado y la conversaci�n 
			!! tiene el par�metro *talker* definido, se imprime:
			if ((flag) && (self.talker ~= 0)) {
				switch (metaclass(self.talker)) {
					Object:		print (The) self.talker;
					String:		print (string) self.talker;
					Routine:	indirect(self.talker);
				}
				print ": ";
			}

			!! Se calcula el n�mero de temas de la conversaci�n:
			size = self.topic_inventory_size();

			!! Se imprimen los mensajes previos al inventario:
			if ((size == 0) && (TINV_NO_MSG ~= 0))
				print (string) TINV_NO_MSG;
			if ((size > 0) && (TINV_MSG1 ~= 0))
				print (string) TINV_MSG1;
			if ((size > 1) && (TINV_MSG2 ~= 0))
				print (string) TINV_MSG2;

			!! Se recolocan los temas en la conversaci�n de forma aleatoria:
			for (i=size : i>0 : i--) {
				n = random(i);
				topic = child(self);
				while (n>1) {
					topic = sibling(topic);
					n--;
				}
				move topic to TopicBag;
			}
			while (child(TopicBag)) move child(TopicBag) to self;

			!! Por �ltimo se imprime el listado de temas:
			for (topic=child(self) : topic~=nothing : topic=sibling(topic)) {
				PrintOrRun(topic, entry, true);
				if (sibling(topic) ~= nothing) {
					if (sibling(sibling(topic)) == nothing) {
						if (TINV_OR ~= 0) {
							print (string) TINV_OR;
						}
					} else {
						if (TINV_COMMA ~= 0) {
							print (string) TINV_COMMA;
						}
					}
				}
			}
			return true;
		],
		!! Permite indicar con qui�n se lleva a cabo la conversaci�n. Puede ser 
		!! un objeto, un string o una rutina.
		talker 0,
		!! Acci�n al activar una conversaci�n.
		initial_action 0,
		!! Acci�n al intentar iniciar una conversaci�n ya activada.
		inter_action 0,
		!! Acci�n al intentar iniciar una conversaci�n agotada.
		final_action 0,
		!! Temporizadores.
		time_left -1,
		time_out [; self.remove_temporal_topic(); ],
 private
		!! Guarda el tema temporal.
		temporal_topic 0;

!!==============================================================================
!!	Objeto gestor del sistema de conversaci�n. Cuenta con el siguiente conjunto 
!!	de funciones que pueden ser utilizadas por un autor de relatos interactivos 
!!	para manejar conversaciones:
!!
!!	 *	get_topic_inventory_flag() - Retorna el valor del atributo 
!!		*inventory_flag* (booleano).
!!
!!	 *	is_running(conv:Conversation) - Retorna verdadero si la conversaci�n 
!!		pasada como par�metro est� activada en el gestor. Si no se pasan 
!!		par�metros, retorna verdadero si hay una conversaci�n cualquiera 
!!		activada. Retorna falso en otro caso.
!!
!!	 *	run() - Funci�n principal del gestor. Comprueba si la entrada de 
!!		usuario se refiere a alguno de los temas disponibles en la conversaci�n 
!!		activa  y lanza la acci�n adecuada para tratarlo si es as�. Debe 
!!		invocarse desde el punto de entrada *BeforeParsing()*.
!!
!!	 *	show_topic_inventory(flag:boolean) - Invoca la funci�n 
!!		*show_topic_inventory(flag)* de la conversaci�n activa para imprimir el 
!!		inventario de temas.
!!
!!	 *	start(conv:Conversation, no_action:boolean) - Inicia y deja activa en 
!!		el gestor la conversaci�n pasada como par�metro. Si adem�s se invoca 
!!		con *no_action* verdadero, se evita la ejecuci�n de las acciones 
!!		previas a la activaci�n de la conversaci�n. Retorna verdadero si la 
!!		conversaci�n se activa correctamente, falso si la conversaci�n no es 
!!		v�lida o est� marcada como finalizada.
!!
!!	 *	stop() - Quita del gestor la conversaci�n activa.
!!
!!	 *	topic_inventory_size() - Retorna el n�mero de temas de la conversaci�n 
!!		activa.
!!------------------------------------------------------------------------------

Object ConversationManager "(Conversation Manager)"
 with	get_topic_inventory_flag [;
			return self.topic_inventory_flag;
		],
		is_running [ conv;
			if (conv ~= nothing) return self.current_conversation == conv;
			else return self.current_conversation ~= nothing;
		],
		run [ o o_tmp_hits;
			if (self.current_conversation) {

				!! A) Inicializaciones del m�todo:
				self.topic_inventory_flag = false; 
				self.hits = 0;
				self.topic = 0;

				!! B) Da un repaso a los temas actuales comprobando si alguno 
				!! encaja con la entrada de usuario:
				objectloop (o in self.current_conversation) {
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Probando: ", (string) o.entry, "... ";
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Se calcula el n�mero de coincidencias del tema en 
					!! relaci�n al total de palabras (%):
					o.compare_prompt();
					o_tmp_hits = (o.hits*100) / num_words; 
					
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Ajuste de ", o.hits, " sobre ", 
					o.#keys / WORDSIZE, " palabras: ", o_tmp_hits, "%^";
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Si coincide m�s que el m�ximo actual:
					if (o_tmp_hits > self.hits) {
						self.hits = o_tmp_hits;
						self.topic = o;
					}
				}

				!! C) Si se ha seleccionado un tema, se ejecutan las acciones 
				!! del tema, se elimina de la conversaci�n (si procede), y se 
				!! a�aden los posibles subtemas:
				if (self.hits) {
					#Ifdef DEBUG_TOPICINVENTORY;
					print "Tema seleccionado: ", (string) self.topic.entry;
					new_line;
					#Endif; ! DEBUG_TOPICINVENTORY;

					!! Si no es persistente, el tema queda marcado como tratado:
					if (~~(self.topic.persistent)) give self.topic visited;

					!! Acci�n al tratar el tema:
					if (self.topic.reply ~= 0)
						PrintOrRun(self.topic, reply);

					!! Se establece la propiedad *topic_inventory_flag* del 
					!! gestor en funci�n de las propiedades del tema:
					self.topic_inventory_flag
						= self.topic.append_topic_inventory;

					!! Se elimina el tema seleccionado si est� agotado y se 
					!! a�aden a la conversaci�n todos sus subtemas, si los hay:
					if (self.topic has visited)
						self.current_conversation.remove_topic(self.topic);
					self.current_conversation.add_subtopics(self.topic);

					!! Acci�n despu�s de tratar el tema:
					if (self.topic.reaction ~= 0)
						PrintOrRun(self.topic, reaction);

					!! Se modifica la entrada de usuario para que la librer�a 
					!! lance la acci�n de apoyo ##NPCTalk (referenciada con la 
					!! palabra clave 'npc.talk'):

					parse-->1 = 'npc.talk';
					num_words = 1;

					!! A partir de este punto, la librer�a lanzar� la acci�n 
					!! ##NPCTalk, que imprimir� el inventario de temas 
					!! disponibles (si es preciso) o pondr� fin a la 
					!! conversaci�n actual
				}
			}

			!! Retorna de la funci�n sin hacer nada -> tratamiento normal de 
			!! la entrada del usuario:
			return false;
		],
		show_topic_inventory [ flag;
			if (self.current_conversation == 0) return false;
			switch (TINV_STYLE) {
			0:	!! Estilo: Romana
				#Ifdef _TYPES_;
				RomanStyle();
				#Ifnot;
				#Ifdef TARGET_ZCODE;
				font_on; style roman;
				#Ifnot; ! TARGET_GLULX;
				glk($0086, 0);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			1:	!! Estilo: It�lica
				#Ifdef _TYPES_;
				ItalicStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font on; style underline;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 1);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			2:	!! Estilo: Negrita
				#Ifdef _TYPES_;
				BoldStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font on; style bold;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 3);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			3:	!! Estilo: Monoespaciada
				#Ifdef _TYPES_;
				MonospacedStyle();
				#Ifnot;
				#Ifdef	TARGET_ZCODE;
				font off;
				#Ifnot;	! TARGET_GLULX;
				glk($0086, 2);
				#Endif;	! TARGET_
				#Endif; ! _TYPES_;
			}
			if (TINV_PREFIX ~= 0)
				print (string) TINV_PREFIX;
			self.current_conversation.show_topic_inventory(flag);
			if (TINV_SUFIX ~= 0)
				print (string) TINV_SUFIX;
			#Ifdef _TYPES_;				!!
			RomanStyle();				!!
			#Ifnot;						!!
			#Ifdef	TARGET_ZCODE;		!!
			font on; style roman;		!! Romana
			#Ifnot;	! TARGET_GLULX;		!!
			glk($0086, 0);				!!
			#Endif; ! TARGET_			!!
			#Endif; ! _TYPES_;			!!
			new_line;
			return true;
		],
		start [ conv no_action;
			!! Se comprueba que la conversaci�n pasada sea v�lida:
			if ((conv == 0) || ~~(conv ofclass Conversation)) {
				#Ifdef DEBUG_TOPICINVENTORY;
				print "ERROR. La conversaci�n introducida no es v�lida.^";
				#Endif;
				return false;
			}
			!! Si la conversaci�n ha finalizado, ejecuta la acci�n de final de 
			!! conversaci�n (si est� definida) y retorna:
			if (conv.has_ended()) {
				if ((conv.final_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, final_action);
				}
				return false;
			}
			!! Si la conversaci�n ya est� activada, ejecuta la acci�n de 
			!! conversaci�n en ejecuci�n (si est� definida):
			if (self.is_running(conv)) {
				if ((conv.inter_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, inter_action);
					new_line;
				}
			}
			!! Se ejecuta la acci�n de inicio de conversaci�n (si est� 
			!! definida) y activa la conversaci�n en el gestor:
			else {
				if ((conv.initial_action ~= 0) && ~~(no_action)) {
					PrintOrRun(conv, initial_action);
					new_line;
				}
				self.current_conversation = conv;
			}
			!! Imprime el inventario de temas de la conversaci�n activa:
			self.show_topic_inventory();
			return true;
		],
		stop [;
			self.current_conversation = 0;
			return true;
		],
		topic_inventory_size [;
			return self.current_conversation.topic_inventory_size();
		],
 private
		!! Tema con mayor porcentaje de coincidencias hasta el momento.
		topic 0,
		!! N�mero de coincidencias del tema con m�s coincidencias de la 
		!! conversaci�n (en tanto por 100 sobre el n�mero de palabras clave).
		hits 0, 
		!! Conversaci�n actual activa en el gestor.
		current_conversation 0, 
		!! Indica si hay que mostrar el inventario de temas al terminar de 
		!! desarrollar uno de los temas de la conversaci�n actual.
		topic_inventory_flag false;

!!==============================================================================
!!	Definici�n de la acci�n de apoyo (y su gram�tica) que se lanza si se 
!!	reconoce en la entrada de usuario un intento de seguir con alguno de los 
!!	temas de la conversaci�n activa en el gestor.
!!------------------------------------------------------------------------------

Verb	'npc.talk'
	*								-> NPCTalk
	* topic							-> NPCTalk
;

[ NPCTalkSub;
	if (ConversationManager.is_running()) {
		if (ConversationManager.get_topic_inventory_flag()) {
			new_line;
			ConversationManager.show_topic_inventory();
		}
	}
	return false;
];


