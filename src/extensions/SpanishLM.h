

!!==============================================================================
!!
!!	MENSAJES DE LA LIBRER�A EN ESPA�OL
!!
!!==============================================================================
!!
!!	File:			SpanishLM.inf
!!	Author(s):		INFSP Task Team
!!					J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		M�quina-Z / GLULX
!!	Version:		0.0
!!	Released:		2017/08/03
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	0.0: 2017/08/03	Versi�n en desarrollo de la extensi�n.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2017, J. Francisco Mart�n
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
!!	# NOTAS
!!
!!	Implementa el conjunto de mensajes por defecto de la librer�a Inform-INFSP,
!!	incluyendo la posibilidad de modificar en tiempo de ejecuci�n tanto el
!!	tiempo verbal (presente, pasado, futuro) y la persona (primera, segunda,
!!	tercera), como el g�nero (masculino, femenino) el n�mero (singular,
!!	plural) ---estos �ltimos, en funci�n de la definici�n del objeto 'player'
!!	controlado por el usuario---. Los mensajes est�n basados en gran medida en
!!	los de 'Spanish.h'.
!!
!!	Incluye adem�s una nueva meta-acci�n de depuraci�n (s�lo est� definida
!!	si la obra se compila con la opci�n DEBUG activada); 'gramatica [opci�n]',
!!	que  permite consultar la flexi�n gramatical actual de los mensajes de la
!!	librer�a (cuando se invoca sin indicar ninguna opci�n), o si se especifica
!!	una opci�n [1-9], modifica la flexi�n gramatical utilizada.
!!
!!
!!	# UTILIZACI�N
!!
!!	A continuaci�n se detallan los 3 pasos que deben seguirse para instalar la
!!	extensi�n:
!!
!!	1)	Declarar la constante SIN_MENSAJES para omitir los mensajes por defecto
!!		de la librer�a Inform (antes de incluir librer�as y extensiones):
!!
!!			Constant SIN_MENSAJES;
!!
!!	2)	Declarar el siguiente conjunto de variables (antes de incluir librer�as
!!		y extensiones):
!!
!!			Global FORMER__TX	= "tu antiguo ~yo~";
!!			Global YOURSELF__TX	= "ti mismo";
!!			Global CANTGO__TX	= "No puedes ir por ah�.";
!!			Global IS__TX		= " ves";
!!			Global ARE__TX		= " ves";
!!			Global IS2__TX		= "ves ";
!!			Global ARE2__TX		= "ves ";
!!			Global YOU__TX		= "T�";
!!			Global PARTICULA_TE	= "te";
!!
!!	3)	Declarar el reemplazo de la rutina 'ChangePlayer' definida en
!!		'parserm.h' (antes de incluir librer�as y extensiones):
!!
!!			Replace ChangePlayer;
!!
!!		Como se ha apuntado anteriormente, 'SpanishLM.h' utiliza un mecanismo
!!		que permite modificar la flexi�n gramatical de los mensajes de la
!!		librer�a en tiempo de ejecuci�n ---permitiendo mensajes en primera,
!!		segunda y tercera persona; presente, pasado y futuro; singular y
!!		plurar; masculino y femenino--- en funci�n, en parte, de los atributos
!!		del personaje controlado por el usuario. As�, al cambiar de personaje,
!!		se hace necesario actualizar el estado de la librer�a Inform.
!!
!!	Una vez instalada, se puede modificar la flexi�n gramatical utilizada en
!!	los mensajes por defecto invocando a la rutina
!!	'SetGrammaticalInflection()'. Por ejemplo, para pasar a utilizar un
!!	narrador en pasado y tercera persona:
!!
!!		SetGrammaticalInflection(THIRD_PERSON_PAST);
!!
!!------------------------------------------------------------------------------


!!------------------------------------------------------------------------------
!! Definici�n de constantes, variables y propiedades
!!------------------------------------------------------------------------------

Constant FIRST_PERSON_PRESENT	= 1;
Constant SECOND_PERSON_PRESENT	= 2;
Constant THIRD_PERSON_PRESENT	= 3;
Constant FIRST_PERSON_PAST		= 4;
Constant SECOND_PERSON_PAST		= 5;
Constant THIRD_PERSON_PAST		= 6;
Constant FIRST_PERSON_FUTURE	= 7;
Constant SECOND_PERSON_FUTURE	= 8;
Constant THIRD_PERSON_FUTURE	= 9;

Global _grammatical_inflection = SECOND_PERSON_PRESENT;

!!==============================================================================
!! La propiedad 'clarification' est� ideada para aquellos objetos que no son
!! localidades y que permiten al personaje controlado por el usuario (PJ)
!! entrar en ellos (objetos con el atributo 'enterable'). Cuando un PJ se
!! encuentra dentro de uno de estos objetos 'enterables', al imprimir la
!! descripci�n de la localidad como resultado de la acci�n ##Look, se imprime
!! el t�tulo de la localidad con un peque�o ap�ndice del tipo ", en el
!! <objeto enterable>" o ", sobre el <objeto enterable>". La propiedad
!! 'clarification' permite personalizar los mensajes de este ap�ndice. Por
!! ejemplo, en una localidad "DORMITORIO" podemos definir un objeto 'enterable'
!! cama con la propiedad:
!!
!!		clarification "sentado en la cama",
!!
!! para conseguir t�tulos del tipo: "DORMITORIO, sentado en la cama", en lugar
!! del: "DORMITORIO, en la cama" por defecto.
!!------------------------------------------------------------------------------
Property clarification; ! string

!!==============================================================================
!! La propiedad 'inhibit_object_list' est� ideada para ser utilizada por los
!! objetos de tipo localidad. Se se define una localidad con la propiedad
!! 'inhibit_object_list' como verdadera, al imprimir su descripci�n como
!! resultado de la acci�n ##Look se omitir� el listado autom�tico de objetos
!! presentes en esa localidad.
!!------------------------------------------------------------------------------
Property inhibit_object_list; ! boolean


!!------------------------------------------------------------------------------
!! Funciones
!!------------------------------------------------------------------------------


!!==============================================================================
!! Imprime la terminaci�n correcta de los verbos de primera conjugaci�n para la
!! inflexi�n gramatical del narrador y el objeto pasado como par�metro. Por
!! defecto utiliza el pret�rito imperfecto para imprimir las inflexiones en
!! pasado; a menos que se invoque con el par�metro 'pastSimple' activado, en
!! cuyo caso se utiliza el pret�rito perfecto simple.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Si se invoca con �l activado
!!		(==true) utiliza el pret�rito perfecto simple para imprimir las
!!		flexiones del verbo en pasado. En caso contrario, se utiliza el
!!		pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_as obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "amos";
			else print "o";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "�is";
			else print "as";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "an";
			else print "a";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "amos";
				else print "�";
			} else {
				if (IsPluralNoun(obj)) print "�bamos";
				else print "aba";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "asteis";
				else print "aste";
			} else {
				if (IsPluralNoun(obj)) print "abais";
				else print "abas";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "aron";
				else print "�";
			} else {
				if (IsPluralNoun(obj)) print "aban";
				else print "aba";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aremos";
			else print "ar�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ar�is";
			else print "ar�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ar�n";
			else print "ar�";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_as()' con el par�metro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pret�rito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_as_ obj; return lm_as(obj, true); ];


!!==============================================================================
!! Imprime la construcci�n correcta (en forma amalgamada o no) formada por la
!! preposici�n 'con' y el pronombre o segmento pronominal que se corresponda
!! con la flexi�n gramatical del narrador y el objeto pasado como par�metro.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_contigo obj;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		FIRST_PERSON_PAST,
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con nosotras";
				else print "con nosotros";
			} else print "conmigo";
		SECOND_PERSON_PRESENT,
		SECOND_PERSON_PAST,
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con vosotras";
				else print "con vosotros";
			} else print "contigo";
		THIRD_PERSON_PRESENT,
		THIRD_PERSON_PAST,
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) {
				if (IsFemaleNoun(obj)) print "con ellas";
				else print "con ellos";
			} else {
				if (IsFemaleNoun(obj)) print "con ella";
				else print "con �l";
			}
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'ser'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_eres obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "somos";
			else print "soy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "sois";
			else print "eres";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "son";
			else print "es";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fuimos";
				else print "fui";
			} else {
				if (IsPluralNoun(obj)) print "�ramos";
				else print "era";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fuisteis";
				else print "fuiste";
			} else {
				if (IsPluralNoun(obj)) print "�rais";
				else print "eras";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "fueron";
				else print "fue";
			} else {
				if (IsPluralNoun(obj)) print "eran";
				else print "era";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "seremos";
			else print "ser�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ser�is";
			else print "ser�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ser�n";
			else print "ser�";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_eres()' con el par�metro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pret�rito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_eres_ obj; return lm_eres(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'ser', usando may�sculas para la
!! primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_eeres obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Somos";
			else print "Soy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Sois";
			else print "Eres";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Son";
			else print "Es";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fuimos";
				else print "Fui";
			} else {
				if (IsPluralNoun(obj)) print "�ramos";
				else print "Era";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fuisteis";
				else print "Fuiste";
			} else {
				if (IsPluralNoun(obj)) print "�rais";
				else print "Eras";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Fueron";
				else print "Fue";
			} else {
				if (IsPluralNoun(obj)) print "Eran";
				else print "Era";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Seremos";
			else print "Ser�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Ser�is";
			else print "Ser�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Ser�n";
			else print "Ser�";
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'estar'.
!! FIXME
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_estas obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "amos";
			else print "oy";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "�is";
			else print "�s";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "�n";
			else print "�";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvimos";
				else print "uve";
			} else {
				if (IsPluralNoun(obj)) print "�bamos";
				else print "aba";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvisteis";
				else print "uviste";
			} else {
				if (IsPluralNoun(obj)) print "abais";
				else print "abas";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "uvieron";
				else print "uvo";
			} else {
				if (IsPluralNoun(obj)) print "aban";
				else print "aba";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "aremos";
			else print "ar�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ar�is";
			else print "ar�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "ar�n";
			else print "ar�";
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'poder'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_puedes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "podemos";
			else print "puedo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "pod�is";
			else print "puedes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "pueden";
			else print "puede";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudimos";
				else print "pude";
			} else {
				if (IsPluralNoun(obj)) print "pod�amos";
				else print "pod�a";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudisteis";
				else print "pudimos";
			} else {
				if (IsPluralNoun(obj)) print "pod�ais";
				else print "pod�as";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "pudieron";
				else print "pudo";
			} else {
				if (IsPluralNoun(obj)) print "pod�an";
				else print "pod�a";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podremos";
			else print "podr�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podr�is";
			else print "podr�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "podr�n";
			else print "podr�";
	}
];


!!==============================================================================
!! Invoca a la rutina 'lm_puedes()' con el par�metro opcional 'pastSimple'
!! activado para imprimir las flexiones en pasado utilizando el pret�rito
!! perfecto simple.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_puedes_ obj; return lm_puedes(obj, true); ];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'poder', usando may�sculas para
!! la primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_ppuedes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Podemos";
			else print "Puedo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Pod�is";
			else print "Puedes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Pueden";
			else print "Puede";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudimos";
				else print "Pude";
			} else {
				if (IsPluralNoun(obj)) print "Pod�amos";
				else print "Pod�a";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudisteis";
				else print "Pudimos";
			} else {
				if (IsPluralNoun(obj)) print "Pod�ais";
				else print "Pod�as";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Pudieron";
				else print "Pudo";
			} else {
				if (IsPluralNoun(obj)) print "Pod�an";
				else print "Pod�a";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podremos";
			else print "Podr�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podr�is";
			else print "Podr�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Podr�n";
			else print "Podr�";
	}
];


!!==============================================================================
!! Imprime el pronombre personal �tono que se corresponde con el objeto pasado
!! como par�metro.
!!
!!	@param {Object} obj
!!------------------------------------------------------------------------------
[ lm_te obj;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		FIRST_PERSON_PAST,
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "nos";
			else print "me";
		SECOND_PERSON_PRESENT,
		SECOND_PERSON_PAST,
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(player)) print "os";
			else print "te";
		THIRD_PERSON_PRESENT,
		THIRD_PERSON_PAST,
		THIRD_PERSON_FUTURE:
			print "se";
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'tener'.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_tienes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "tenemos";
			else print "tengo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "ten�is";
			else print "tienes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "tienen";
			else print "tiene";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvimos";
				else print "tuve";
			} else {
				if (IsPluralNoun(obj)) print "ten�amos";
				else print "ten�a";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvisteis";
				else print "tuviste";
			} else {
				if (IsPluralNoun(obj)) print "ten�ais";
				else print "ten�as";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "tuvieron";
				else print "tuvo";
			} else {
				if (IsPluralNoun(obj)) print "ten�an";
				else print "ten�a";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendremos";
			else print "tendr�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendr�is";
			else print "tendr�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "tendr�n";
			else print "tendr�";
	}
];


!!==============================================================================
!! Similar a la rutina 'lm_as()', con el verbo 'tener', usando may�sculas para
!! la primera letra.
!!
!!	@param {Object} obj
!!	@param {boolean} [pastSimple=false] - Activado (==true) para utilizar el
!!		pret�rito perfecto simple en las flexiones en pasado. En caso contrario
!!		se utiliza el pret�rito imperfecto
!!------------------------------------------------------------------------------
[ lm_ttienes obj pastSimple;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Tenemos";
			else print "Tengo";
		SECOND_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Ten�is";
			else print "Tienes";
		THIRD_PERSON_PRESENT:
			if (IsPluralNoun(obj)) print "Tienen";
			else print "Tiene";
		FIRST_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvimos";
				else print "Tuve";
			} else {
				if (IsPluralNoun(obj)) print "Ten�amos";
				else print "Ten�a";
			}
		SECOND_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvisteis";
				else print "Tuviste";
			} else {
				if (IsPluralNoun(obj)) print "Ten�ais";
				else print "Ten�as";
			}
		THIRD_PERSON_PAST:
			if (pastSimple) {
				if (IsPluralNoun(obj)) print "Tuvieron";
				else print "Tuvo";
			} else {
				if (IsPluralNoun(obj)) print "Ten�an";
				else print "Ten�a";
			}
		FIRST_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendremos";
			else print "Tendr�";
		SECOND_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendr�is";
			else print "Tendr�s";
		THIRD_PERSON_FUTURE:
			if (IsPluralNoun(obj)) print "Tendr�n";
			else print "Tendr�";
	}
];


!!==============================================================================
!! Intercambia el objeto controlado por el usuario por otro objeto dado.
!!
!!	@param {Object} obj
!!	@param {boolean} [flag]
!!	@overrides parserm.h
!!------------------------------------------------------------------------------
[ ChangePlayer obj flag
	i;
	if (actor == player) actor=obj;
    give player ~transparent ~concealed;
    i = obj; while (parent(i) ~= 0) {
        if (i has animate) give i transparent;
        i = parent(i);
    }

	!! XXX - Modificaci�n sobre la rutina original
	SetGrammaticalInflection(_grammatical_inflection, obj);
	!! XXX - Fin de la modificaci�n

    if (player == selfobj) player.short_name = FORMER__TX;

    player = obj;

    if (player == selfobj) player.short_name = NULL;
    give player transparent concealed animate proper;
    i = player; while (parent(i) ~= 0) i = parent(i);
    location = i; real_location = location;
    if (parent(player) == 0) return RunTimeError(10);
    MoveFloatingObjects();
    lightflag = OffersLight(parent(player));
    if (lightflag == 0) location = thedark;
    print_player_flag = flag;
];


!!==============================================================================
!! Determina si un objeto est� definido como nombre femenino o no. En la
!! pr�ctica, en la extensi�n se considera que todos los objetos con nombre no
!! femenino ('~~IsFemaleNoun()') tienen nombre masculino ---aunque en realidad,
!! el inverso del conjunto de GNA femenino: {1, 4, 7, 10}, comprende a un
!! tiempo los conjuntos de GNA masculino: {0, 3, 6, 9}, y GNA neutro:
!! {2, 6, 8, 11}---.
!!
!!	@param {Object} obj
!!	@returns {boolean} Verdadero si el objeto est� definido como nombre
!!		femenino. Falso en caso contrario
!!------------------------------------------------------------------------------
[ IsFemaleNoun obj
	result;
	if (obj provides gender) result = (obj.gender == 2 or 4);
	else result = (GetGNAOfObject(obj) == 1 or 4 or 7 or 10);
	return result;
];


!!==============================================================================
!! Determina si un objeto est� definido como nombre plural o no. En la
!! pr�ctica, en la extensi�n se considera que todos los objetos con nombre no
!! plural ('~~IsPluralNoun()') tienen nombre singular ---ciertamente, el
!! inverso del conjunto de GNA plural: {3, 4, 5, 9, 10, 11}, se corresponde con
!! el conjunto de GNA singular: {0, 1, 2, 6, 7, 8}---.
!!
!!	@param {Object} obj
!!	@returns {boolean} Verdadero si el objeto est� definido como nombre
!!		plural. Falso en caso contrario
!!------------------------------------------------------------------------------
[ IsPluralNoun obj
	result;
	if (obj provides gender) result = (obj.gender == 3 or 4);
	else result = (GetGNAOfObject(obj) == 3 or 4 or 5 or 9 or 10 or 11);
	return result;
];


!!==============================================================================
!! Establece la flexi�n gramatical de los mensajes de la librer�a, actualizando
!! su estado. Para ello, utiliza la definici�n ---para determinar su g�nero y
!! n�mero--- de un objeto dado (si no se especifica uno, por defecto el objeto
!! 'player' controlado por el usuario).
!!
!!	@param {int} [gi=SECOND_PERSON_PRESENT] - Nueva flexi�n gramatical a
!!		utilizar en los mensajes de la librer�a. Si no se especifica un valor o
!!		el valor especificado es err�neo, se establece por defecto la segunda
!!		persona del presente: SECOND_PERSON_PRESENT.
!!	@param {Object} [obj=player] - Objeto del que se cosultan los atributos
!!		referidos a g�nero y n�mero utilizados para actualizar el estado de la
!!		librer�a.
!!------------------------------------------------------------------------------
[ SetGrammaticalInflection gi obj;
	if ((obj == 0) || (metaclass(obj) == nothing)) obj = player;
	switch (gi) {
		FIRST_PERSON_PRESENT:
			_grammatical_inflection = FIRST_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " vemos";
				ARE2__TX		= "vemos ";
				CANTGO__TX		= "No podemos ir por ah�.";
				IS__TX			= " vemos";
				IS2__TX			= "vemos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " veo";
				ARE2__TX		= "veo ";
				CANTGO__TX		= "No puedo ir por ah�.";
				IS__TX			= " veo";
				IS2__TX			= "veo ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� misma";
				} else {
					FORMER__TX		= "mi mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� mismo";
				}
			}
		SECOND_PERSON_PRESENT:
			.defaultInflection;
			_grammatical_inflection = SECOND_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veis";
				ARE2__TX		= "veis ";
				CANTGO__TX		= "No pod�is ir por ah�.";
				IS__TX			= " veis";
				IS2__TX			= "veis ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX			= " ves";
				ARE2__TX		= "ves ";
				CANTGO__TX		= "No puedes ir por ah�.";
				IS__TX			= " ves";
				IS2__TX			= "ves ";
				PARTICULA_TE	= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� mismo";
				}
			}
		THIRD_PERSON_PRESENT:
			_grammatical_inflection = THIRD_PERSON_PRESENT;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ven";
				ARE2__TX		= "ven ";
				CANTGO__TX		= "No pueden ir por ah�.";
				IS__TX			= " ven";
				IS2__TX			= "ven ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " ve";
				ARE2__TX		= "ve ";
				CANTGO__TX		= "No puede ir por ah�.";
				IS__TX			= " ve";
				IS2__TX			= "ve ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "s� misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "�l";
					YOURSELF__TX	= "s� mismo";
				}
			}
		FIRST_PERSON_PAST:
			_grammatical_inflection = FIRST_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ve�amos";
				ARE2__TX		= "ve�amos ";
				CANTGO__TX		= "No pod�amos ir por ah�.";
				IS__TX			= " ve�amos";
				IS2__TX			= "ve�amos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " ve�a";
				ARE2__TX		= "ve�a ";
				CANTGO__TX		= "No pod�a ir por ah�.";
				IS__TX			= " ve�a";
				IS2__TX			= "ve�a ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� misma";
				} else {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� mismo";
				}
			}
		SECOND_PERSON_PAST:
			_grammatical_inflection = SECOND_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ve�ais";
				ARE2__TX		= "ve�ais ";
				CANTGO__TX		= "No pod�ais ir por ah�.";
				IS__TX			= " ve�ais";
				IS2__TX			= "ve�ais ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX			= " ve�as";
				ARE2__TX		= "ve�as ";
				CANTGO__TX		= "No pod�as ir por ah�.";
				IS__TX			= " ve�as";
				IS2__TX			= "ve�as ";
				PARTICULA_TE	= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� mismo";
				}
			}
		THIRD_PERSON_PAST:
			_grammatical_inflection = THIRD_PERSON_PAST;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ve�an";
				ARE2__TX		= "ve�an ";
				CANTGO__TX		= "No pod�an ir por ah�.";
				IS__TX			= " ve�an";
				IS2__TX			= "ve�an ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " ve�a";
				ARE2__TX		= "ve�a ";
				CANTGO__TX		= "No pod�a ir por ah�.";
				IS__TX			= " ve�a";
				IS2__TX			= "ve�a ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "s� misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "�l";
					YOURSELF__TX	= "s� mismo";
				}
			}
		FIRST_PERSON_FUTURE:
			_grammatical_inflection = FIRST_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " veremos";
				ARE2__TX		= "veremos ";
				CANTGO__TX		= "No podremos ir por ah�.";
				IS__TX			= " veremos";
				IS2__TX			= "veremos ";
				PARTICULA_TE	= "nos";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "nuestra antigua ~yo~";
					YOU__TX			= "Nosotras";
					YOURSELF__TX	= "nosotras mismas";
				} else {
					FORMER__TX		= "nuestro antiguo ~yo~";
					YOU__TX			= "Nosotros";
					YOURSELF__TX	= "nosotros mismos";
				}
			} else {
				ARE__TX			= " ver�";
				ARE2__TX		= "ver� ";
				CANTGO__TX		= "No podr� ir por ah�.";
				IS__TX			= " ver�";
				IS2__TX			= "ver� ";
				PARTICULA_TE	= "me";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "mi antigua ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� misma";
				} else {
					FORMER__TX		= "mi antiguo ~yo~";
					YOU__TX			= "Yo";
					YOURSELF__TX	= "m� mismo";
				}
			}
		SECOND_PERSON_FUTURE:
			_grammatical_inflection = SECOND_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ver�is";
				ARE2__TX		= "ver�is ";
				CANTGO__TX		= "No podr�is ir por ah�.";
				IS__TX			= " ver�is";
				IS2__TX			= "ver�is ";
				PARTICULA_TE	= "os";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "vuestra antigua ~yo~";
					YOU__TX			= "Vosotras";
					YOURSELF__TX	= "vosotras mismas";
				} else {
					FORMER__TX		= "vuestro antiguo ~yo~";
					YOU__TX			= "Vosotros";
					YOURSELF__TX	= "vosotros mismos";
				}
			} else {
				ARE__TX				= " ver�s";
				ARE2__TX			= "ver�s ";
				CANTGO__TX			= "No podr�s ir por ah�.";
				IS__TX				= " ver�s";
				IS2__TX				= "ver�s ";
				PARTICULA_TE		= "te";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "tu antigua ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� misma";
				} else {
					FORMER__TX		= "tu antiguo ~yo~";
					YOU__TX			= "T�";
					YOURSELF__TX	= "t� mismo";
				}
			}
		THIRD_PERSON_FUTURE:
			_grammatical_inflection = THIRD_PERSON_FUTURE;
			if (IsPluralNoun(obj)) {
				ARE__TX			= " ver�n";
				ARE2__TX		= "ver�n ";
				CANTGO__TX		= "No podr�n ir por ah�.";
				IS__TX			= " ver�n";
				IS2__TX			= "ver�n ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ellas";
					YOURSELF__TX	= "ellas mismas";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "Ellos";
					YOURSELF__TX	= "ellos mismos";
				}
			} else {
				ARE__TX			= " ver�";
				ARE2__TX		= "ver� ";
				CANTGO__TX		= "No podr� ir por ah�.";
				IS__TX			= " ver�";
				IS2__TX			= "ver� ";
				PARTICULA_TE	= "se";
				if (IsFemaleNoun(obj)) {
					FORMER__TX		= "su antigua ~yo~";
					YOU__TX			= "Ella";
					YOURSELF__TX	= "s� misma";
				} else {
					FORMER__TX		= "su antiguo ~yo~";
					YOU__TX			= "�l";
					YOURSELF__TX	= "s� mismo";
				}
			}
		default:
			jump defaultInflection;
	}
	ChangeDefault(cant_go, CANTGO__TX);
];

#Ifdef	DEBUG;
Verb	meta 'gramatica' 'grammar'
	*								-> Grammar
	* number						-> Grammar
;

[ GrammarSub;
	switch (noun) {
		1:	SetGrammaticalInflection(FIRST_PERSON_PRESENT);
		2:	SetGrammaticalInflection(SECOND_PERSON_PRESENT);
		3:	SetGrammaticalInflection(THIRD_PERSON_PRESENT);
		4:	SetGrammaticalInflection(FIRST_PERSON_PAST);
		5:	SetGrammaticalInflection(SECOND_PERSON_PAST);
		6:	SetGrammaticalInflection(THIRD_PERSON_PAST);
		7:	SetGrammaticalInflection(FIRST_PERSON_FUTURE);
		8:	SetGrammaticalInflection(SECOND_PERSON_FUTURE);
		9:	SetGrammaticalInflection(THIRD_PERSON_FUTURE);
		default:
			"Flexi�n gramatical actual: ", _grammatical_inflection,
			"^ARE__TX: ", (string) ARE__TX,
			"^ARE2__TX: ", (string) ARE2__TX,
			"^CANTGO__TX: ", (string) CANTGO__TX,
			"^IS__TX: ", (string) IS__TX,
			"^IS2__TX: ", (string) IS2__TX,
			"^PARTICULA_TE: ", (string) PARTICULA_TE,
			"^FORMER__TX: ", (string) FORMER__TX,
			"^YOU__TX: ", (string) YOU__TX,
			"^YOURSELF__TX: ", (string) YOURSELF__TX;
	}
	print "Cambio de flexi�n gramatical: ";
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:	print "(1) presente 1a persona";
		SECOND_PERSON_PRESENT:	print "(2) presente 2a persona";
		THIRD_PERSON_PRESENT:	print "(3) presente 3a persona";
		FIRST_PERSON_PAST:		print "(4) pasado 1a persona";
		SECOND_PERSON_PAST:		print "(5) pasado 2a persona";
		THIRD_PERSON_PAST:		print "(6) pasado 3a persona";
		FIRST_PERSON_FUTURE:	print "(7) futuro 1a persona";
		SECOND_PERSON_FUTURE:	print "(8) futuro 2a persona";
		THIRD_PERSON_FUTURE:	print "(9) futuro 3a persona";
	}
	".";
];
#Endif; ! DEBUG;


!!==============================================================================
[ LanguageLM n x1
	i;

	Answer, Ask, AskFor:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				"No hay respuesta.";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				"No hab�a respuesta.";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				"No habr� respuesta.";
		}

!!	Ask:	see Answer
!!	AskFor:	see Answer

	Attack:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "ser�";
		}
		" necesario emprenderla a golpes con ", (the) x1, ".";

	Blow:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no produce";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no produce";
			THIRD_PERSON_PRESENT:
				print "Su soplido no produce";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no produjo";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no produjo";
			THIRD_PERSON_PAST:
				print "Su soplido no produjo";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nuestro";
				else print "Mi";
				print " soplido no producir�";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Vuestro";
				else print "Tu";
				print " soplido no producir�";
			THIRD_PERSON_FUTURE:
				print "Su soplido no producir�";
		}
		" ning�n efecto.";

	Burn:
		print "Con esa peligrosa acci�n no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "�bamos";
				else print "iba";
				" a lograr nada.";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "ibais";
				else print "ibas";
				" a lograr nada.";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "iban";
				else print "iba";
				" a lograr nada.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubi�semos";
				else print "hubiese";
				" logrado nada.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis";
				else print "hubieses";
				" logrado nada.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen";
				else print "hubiese";
				" logrado nada.";
		}

	Buy:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "hay";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "hab�a";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "habr�";
		}
		" nada en venta.";

	Climb:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No creemos que vayamos";
				else print "No creo que vaya";
				" a lograr nada haciendo eso.";
			SECOND_PERSON_PRESENT:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "cre�is que vay�is";
				else print "crees que vayas";
				" a lograr nada haciendo eso.";
			THIRD_PERSON_PRESENT:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen que vayan";
				else print "cree que vaya";
				" a lograr nada haciendo eso.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "No creemos que hubi�semos";
				else print "No creo que hubiese";
				" logrado nada haciendo aquello.";
			SECOND_PERSON_PAST:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "cre�is que hubieseis";
				else print "crees que hubieses";
				" logrado nada haciendo aquello.";
			THIRD_PERSON_PAST:
				print "En realidad no ";
				if (IsPluralNoun(player)) print "creen que hubiesen";
				else print "cree que hubiese";
				" logrado nada haciendo aquello.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograremos";
				else print "No lograr�";
				" nada haciendo eso.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograr�is";
				else print "No lograr�s";
				" nada haciendo eso.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No lograr�n";
				else print "No lograr�";
				" nada haciendo eso.";
		}

	Close:
		!!	1:	Error. El objeto no es *openable*.
		!!	2:	Error. El objeto est� cerrado.
		!!	3:	Mensaje cuando se cierra el objeto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda cerrarse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese cerrar.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No ser� algo que pueda cerrarse.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"Ya estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Ya estar�", (n) x1, " cerrad", (o) x1, ".";
				}
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Cerramos";
						else print "Cierro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Cerr�is";
						else print "Cierras";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Cierran";
						else print "Cierra";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerramos";
						else print "Cerr�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerrasteis";
						else print "Cerraste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Cerraron";
						else print "Cerr�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerraremos";
						else print "Cerrar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerrar�is";
						else print "Cerrar�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Cerrar�n";
						else print "Cerrar�";
				}
				" ", (the) x1, ".";
		}

	CommandsOff:
		switch (n) { ![6/11]
			1:	"[Grabaci�n de �rdenes finalizada.]";
			#Ifdef TARGET_GLULX;
			2:	"[Grabaci�n de �rdenes ya finalizada.]";
			#Endif; ! TARGET_
		}

	CommandsOn:
		switch (n) { ![6/11]
			1:	"[Grabaci�n de �rdenes activada.]";
			#Ifdef TARGET_GLULX;
			2:	"[�rdenes relanzadas.]";
			3:	"[Grabaci�n de �rdenes ya activada.]";
			4:	"[Fallo en la grabaci�n de �rdenes.]";
			#Endif; ! TARGET_
		}

	CommandsRead:
		switch (n) { ![6/11]
			1:	"[Relanzando acciones.]";
			#Ifdef TARGET_GLULX;
			2:	"[Las �rdenes ya est�n siendo relanzadas.]";
			3:	"[Fallo en la reejecuci�n de �rdenes: grabaci�n en curso.]";
			4:	"[Fallo en la reejecuci�n de �rdenes.]";
			5:	"[Acciones ejecutadas: fin del proceso.]";
			#Endif; ! TARGET_
		}

	Consult:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubrimos";
				else print "descubro";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubr�s";
				else print "descubres";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "descubren";
				else print "descubre";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubrimos";
				else print "descubr�";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubristeis";
				else print "descubriste";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "descubrieron";
				else print "descubri�";
				" nada interesante en ", (the) x1, " sobre aquel tema.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubriremos";
				else print "descubrir�";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubrir�is";
				else print "descubrir�s";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "descubrir�n";
				else print "descubrir�";
		}
		" nada interesante en ", (the) x1, " sobre ese tema.";

	Cut:
		print "Cort�ndo", (lo) x1, " no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograremos";
				else print "lograr�";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograr�is";
				else print "lograr�s";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograr�n";
				else print "lograr�";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubi�semos logrado";
				else print "hubiese logrado";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis logrado";
				else print "hubiese logrado";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen logrado";
				else print "hubiese logrado";
		}
		" gran cosa.";

	Dig:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT:
			THIRD_PERSON_PRESENT:
				"Excavar no servir� de nada aqu�.";
			FIRST_PERSON_PAST:
			SECOND_PERSON_PAST:
			THIRD_PERSON_PAST:
				"Excavar no hubiese servido de nada all�.";
			FIRST_PERSON_FUTURE:
			SECOND_PERSON_FUTURE:
			THIRD_PERSON_FUTURE:
				"Excavar no servir� de nada all�.";
		}

	Disrobe:
		!!	1:	Error. El protagonista no lleva el objeto puesto.
		!!	2:	Mensaje cuando el protagonista se quita el objeto.
		switch (n) {
			1:	"No ", (lo) x1, " llev", (lm_as) player, " puest", (o) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos quitamos";
						else print "Me quito";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os quit�is";
						else print "Te quitas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se quitan";
						else print "Se quita";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos quitamos";
						else print "Me quit�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os quitasteis";
						else print "Te quitaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se quitaron";
						else print "Se quit�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos quitaremos";
						else print "Me quitar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os quitar�is";
						else print "Te quitar�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se quitar�n";
						else print "Se quitar�";
				}
				" ", (the) x1, ".";
		}

	Drink:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT:
			THIRD_PERSON_PRESENT:
				"Eso no parece potable.";
			FIRST_PERSON_PAST:
			SECOND_PERSON_PAST:
			THIRD_PERSON_PAST:
				"Aquello no parec�a potable.";
			FIRST_PERSON_FUTURE:
			SECOND_PERSON_FUTURE:
			THIRD_PERSON_FUTURE:
				"Eso no parecer� potable.";
		}

	Drop:
		!!	1:	Error, el objeto dejado no est� en poder del protagonista,
		!!		pero est� en la localidad.
		!!	2:	Error, el objeto dejado no est� en poder del protagonista ni en
		!!		la localidad,
		!!	3:	Aviso, el objeto era una prenda que el protagonista llevaba
		!!		puesta y la librer�a va a quit�rsela autom�ticamente para poder
		!!		dejarla.
		!!	4:	�xito.
		switch (n) {
			1:	print "Para dejar ", (the) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deber�amos";
						else print "deber�a";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deber�ais";
						else print "deber�as";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deber�an";
						else print "deber�a";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubi�semos debido";
						else print "hubiese debido";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubieseis debido";
						else print "hubieses debido";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "hubiesen debido";
						else print "hubiese debido";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deberemos";
						else print "deber�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deber�is";
						else print "deber�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "deber�n";
						else print "deber�";
				}
				" tener", (lo) x1, ".";
			2:	"No ", (lo) x1, " ", (lm_tienes) player, " ",
				(lm_contigo) player, ".";
			3:	print "(Primero ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "nos quitamos";
						else print "me quito";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "os quit�is";
						else print "te quitas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "se quitan";
						else print "se quita";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "nos quitamos";
						else print "me quit�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "os quitasteis";
						else print "te quitaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "se quitaron";
						else print "se quit�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "nos quitaremos";
						else print "me quitar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "os quitar�is";
						else print "te quitar�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "se quitar�n";
						else print "se quitar�";
				}
				" ", (the) x1, ".)";
			4:	"Dejad", (o) x1, ".";
		}

	Eat:
		!!	1:	Error, el objeto no tiene el atributo "comestible".
		!!	2:	�xito. [NOTA: la librer�a permite por defecto comerse
		!!		cualquier cosa que tenga el atributo "comestible", pero la
		!!		�nica acci�n que provoca esto es que el objeto en cuesti�n
		!!		desaparece del juego al ser comido.]
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT:
					THIRD_PERSON_PRESENT:
						"Eso no parece comestible.";
					FIRST_PERSON_PAST:
					SECOND_PERSON_PAST:
					THIRD_PERSON_PAST:
						"Aquello no parec�a comestible.";
					FIRST_PERSON_FUTURE:
					SECOND_PERSON_FUTURE:
					THIRD_PERSON_FUTURE:
						"Eso no parecer� comestible.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos comemos";
						else print "Me como";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os com�is";
						else print "Te comes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se comen";
						else print "Se come";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos comimos";
						else print "Me com�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os comisteis";
						else print "Te comiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se comieron";
						else print "Se comi�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos comeremos";
						else print "Me comer�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os comer�is";
						else print "Te comer�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se comer�n";
						else print "Se comer�";
				}
				" ", (the) x1, ".";
		}

	EmptyT:
		!!	1:	Error, el usuario intenta vaciar un objeto en otro que no es un
		!!		recipiente.
		!!	2:	Error, el usuario intenta vaciar un objeto sobre un recipiente
		!!		cerrado.
		!!	3:	Error, el usuario intenta vaciar un objeto que no tiene nada
		!!		dentro.
		!!	4:	Error, el usuario intenta vaciar un objeto sobre s� mismo.
		!!
		!! [NOTA: No hay mensajes de �xito para esta acci�n, ya que en caso
		!! de haber superado los test anteriores, la librer�a genera
		!! finalmente la acci�n ##Transfer, la cu�l, a su vez, generar� la
		!! acci�n ##PutOn o ##Insert, seg�n el segundo objeto sea soporte o
		!! recipiente. Por tanto los mensajes de �xito ser�n los de las
		!! acciones ##PutOn o ##Insert.]
		switch (n) {
			1:	print (The) x1, " no ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "puede", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "pod�a", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "podr�", (n) x1;
				}
				" tener cosas dentro.";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " estar�", (n) x1;
				}
				" cerrad", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " ya est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " ya estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " ya estar�", (n) x1;
				}
				" vac�", (o) x1, ".";
			4:	"No ", (lm_puedes) player, " vaciar un objeto sobre s� mismo.";
		}

	Enter:
		! [infsp] GoIn (Meterse) se cambi� por Enter.
		!! CUIDADO. La acci�n Meterse se genera en muy diversas
		!! circunstancias: VETE HACIA EL PUENTE, VETE AL PUENTE, VETE POR
		!! EL PUENTE, PASA POR EL PUENTE, ENTRA EN EL PUENTE, ENTRA AL
		!! PUENTE, CRUZA EL PUENTE, CRUZA POR EL PUENTE, METETE EN EL
		!! PUENTE, METETE POR EL PUENTE, ATRAVIESA EL PUENTE, BAJA POR EL
		!! PUENTE.  Todas ellas generar�an la acci�n <Meterse Puente>
		!!
		!! Adem�s, los intentos de entrar en un "entrable", tambi�n, como
		!! por ejemplo: SIENTATE EN EL BANCO, ECHATE EN EL BANCO, SUBETE AL
		!! BANCO, SUBETE EN EL BANCO, SUBE AL BANCO, SUBE POR EL BANCO,
		!! SALTA AL BANCO. Todas ellas generar�an <Meterse Banco>
		!!
		!! Puesto que hay muchos verbos diferentes que dan lugar a la misma
		!! acci�n, es necesaria alguna forma de imprimir qu� verbo concreto
		!! ha sido el que la ha desencadenado, para poder generar mensajes
		!! como "No puedes entrar ahi", "No puedes sentarte ahi", "No
		!! puedes subirte ahi", etc.. seg�n el verbo usado. Para esto puede
		!! usarse una llamada a IdiomaVerbo(palabra_verbo). palabra_verbo
		!! contiene el verbo usado por el usuario (convertido en forma
		!! imperativa), y IdiomaVerbo lo que hace es imprimir la forma
		!! infinitiva.
		!!
		!! Mensajes que puede generar esta acci�n:
		!!	1:	Error, el protagonista ya est� en/sobre el objeto.
		!!	2:	Error, el objeto al que intenta entrar/subirse el usuario
		!!		no tiene el atributo "enterable".
		!!	3:	Error, el objeto al que intenta entrar/subirse el usuario tiene
		!!		los atributos "container" y "enterable", pero est� cerrado.
		!!	4:	Error, el objeto al que intenta entrar/subirse el usuario est�
		!!		en poder del propio usuario.
		!!	5:	�xito, el usuario entra/sube al objeto.
		!!	6:	Aviso, el usuario estaba en otro objeto, la lib. intentar� la
		!!		acci�n SALIR autom�ticamente antes de reintentar entrar el
		!!		nuevo objeto.
		!!	7:	Aviso, el objeto al que intenta entrar/subirse el usuario est�
		!!		dentro de otros objeto. La lib. intentar� autom�ticamente meter
		!!		al usuario en el objeto desde el cual pueda acceder al que el
		!!		usuario le ha indicado.
		switch (n) {
			1:	print "Ya ", (lm_estas) player, " ";
				if (x1 has supporter) print "sobre ";
				else print "en ";
				"", (the) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde podamos";
						else print "No es algo donde pueda";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde pod�is";
						else print "No es algo donde puedas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player))
							print "No es algo donde puedan";
						else print "No es algo donde pueda";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudi�semos";
						else print "No era algo donde pudiese";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudieseis";
						else print "No era algo donde pudieses";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player))
							print "No era algo donde pudiesen";
						else print "No era algo donde pudiese";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No ser� algo donde podremos";
						else print "No ser� algo donde podr�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No ser� algo donde podr�is";
						else print "No ser� algo donde podr�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player))
							print "No ser� algo donde podr�n";
						else print "No ser� algo donde podr�";
				}
				LanguageVerb(verb_word); ".";
			3:	print "No ", (lm_puedes) player, " ";
				LanguageVerb(verb_word);
				print " en ", (the) x1, " porque ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estar�", (n) x1;
				}
				" cerrad", (o) x1, ".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "vamos a poder";
						else print "voy a poder";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "vais a poder";
						else print "vas a poder";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "van a poder";
						else print "va a poder";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "�bamos a poder";
						else print "iba a poder";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "ibais a poder";
						else print "ibas a poder";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "iban a poder";
						else print "iba a poder";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podremos";
						else print "podr�";
						" hacerlo sin soltarlo antes.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podr�is";
						else print "podr�s";
						" hacerlo sin soltarlo antes.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podr�n";
						else print "podr�";
						" hacerlo sin soltarlo antes.";
				}
				LanguageVerb(verb_word);
				print " ah� mientras no ", (lo) x1, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "soltemos";
						else print "suelte";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "solt�is";
						else print "sueltes";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "suelten";
						else print "suelte";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "solt�semos";
						else print "soltase";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "soltaseis";
						else print "soltases";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "soltasen";
						else print "soltase";
				}
				".";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subimos";
							else print "Subo";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entramos";
							else print "Entro";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Sub�s";
							else print "Subes";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entr�is";
							else print "Entras";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Suben";
							else print "Sube";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entran";
							else print "Entra";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subimos";
							else print "Sub�";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entramos";
							else print "Entr�";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subisteis";
							else print "Subiste";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entrasteis";
							else print "Entraste";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subieron";
							else print "Subi�";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entraron";
							else print "Entr�";
							print " en ", (the) x1;
						}
						".";
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subiremos";
							else print "Subir�";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entraremos";
							else print "Entrar�";
							print " en ", (the) x1;
						}
						".";
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subir�is";
							else print "Subir�s";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entrar�is";
							else print "Entrar�s";
							print " en ", (the) x1;
						}
						".";
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Subir�n";
							else print "Subir�";
							print " ", (al_) x1;
						} else {
							if (IsPluralNoun(player)) print "Entrar�n";
							else print "Entrar�";
							print " en ", (the) x1;
						}
						".";
				}
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajamos";
							else print "(Me bajo";
						} else {
							if (IsPluralNoun(player)) print "(Salimos";
							else print "(Salgo";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os baj�is";
							else print "(Te bajas";
						} else {
							if (IsPluralNoun(player)) print "(Sal�s";
							else print "(Sales";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajan";
							else print "(Se baja";
						} else {
							if (IsPluralNoun(player)) print "(Salen";
							else print "(Sale";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajamos";
							else print "(Me baj�";
						} else {
							if (IsPluralNoun(player)) print "(Salimos";
							else print "(Sal�";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os baj�steis";
							else print "(Te bajaste";
						} else {
							if (IsPluralNoun(player)) print "(Salisteis";
							else print "(Saliste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajaron";
							else print "(Se baj�";
						} else {
							if (IsPluralNoun(player)) print "(Salieron";
							else print "(Sali�";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos bajaremos";
							else print "(Me bajar�";
						} else {
							if (IsPluralNoun(player)) print "(Saldremos";
							else print "(Saldr�";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os bajar�is";
							else print "(Te bajar�s";
						} else {
							if (IsPluralNoun(player)) print "(Saldr�is";
							else print "(Saldr�s";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se bajar�n";
							else print "(Se bajar�";
						} else {
							if (IsPluralNoun(player)) print "(Saldr�n";
							else print "(Saldr�";
						}
				}
				" ", (del_) x1, ").";
			7:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subimos";
							else print "(Me subo";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos metemos";
							else print "(Me meto";
						} else {
							if (IsPluralNoun(player)) print "(Entramos";
							else print "(Entro";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os sub�s";
							else print "(Te subes";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os met�is";
							else print "(Te metes";
						} else {
							if (IsPluralNoun(player)) print "(Entr�is";
							else print "(Entras";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se suben";
							else print "(Se sube";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se meten";
							else print "(Se mete";
						} else {
							if (IsPluralNoun(player)) print "(Entran";
							else print "(Entra";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subimos";
							else print "(Me sub�";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos metimos";
							else print "(Me met�";
						} else {
							if (IsPluralNoun(player)) print "(Entramos";
							else print "(Entr�";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os subisteis";
							else print "(Te subiste";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os metisteis";
							else print "(Te metiste";
						} else {
							if (IsPluralNoun(player)) print "(Entrasteis";
							else print "(Entraste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se subieron";
							else print "(Se subi�";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se metieron";
							else print "(Se meti�";
						} else {
							if (IsPluralNoun(player)) print "(Entraron";
							else print "(Entr�";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Nos subiremos";
							else print "(Me subir�";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Nos meteremos";
							else print "(Me meter�";
						} else {
							if (IsPluralNoun(player)) print "(Entraremos";
							else print "(Entrar�";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Os subir�is";
							else print "(Te subir�s";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Os meter�is";
							else print "(Te meter�s";
						} else {
							if (IsPluralNoun(player)) print "(Entrar�is";
							else print "(Entrar�s";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "(Se subir�n";
							else print "(Se subir�";
							" ", (al_) x1, ").^";
						} else if (x1 has container) {
							if (IsPluralNoun(player)) print "(Se meter�n";
							else print "(Se meter�";
						} else {
							if (IsPluralNoun(player)) print "(Entrar�n";
							else print "(Entrar�";
						}
				}
				" en ", (the) x1, ").^";
		}

	Examine:
		!!	1:	Error, el usuario intenta examinar un objeto, pero est� a
		!!		oscuras.
		!!	2:	�xito, pero el objeto examinado no tiene descripcion
		!!	3:	�xito, pero el objeto examinado no tiene descripcion, aunque
		!!		tiene el atributo conmutable, por lo que la librer�a genera
		!!		este mensaje para indicar si est� apagado o encendido.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Est�";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estar�";
				}
				" demasiado oscuro. No ", (lm_puedes) player, " ver nada.";
			2:	"No observ", (lm_as_) player, "  nada especial en ",
				(the) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " estar�", (n) x1;
				}
				if (x1 has on) " encendid", (o) x1, ".";
				else " apagad", (o) x1,".";
		}

	Exit:
		!!	1:	Error, el usuario no est� subido/sentado/metido en ning�n
		!!		objeto. [Nota, si la localidad tiene la propiedad "afuera",
		!!		entonces la acci�n Salir lo sacar� de la localidad. En caso
		!!		contrario es cuando se genera este error.]
		!!	2:	Error, el usuario est� dentro de un recipiente cerrado.
		!!	3:	�xito, el usuario sale/baja del objeto
		!!	4:	Error, m�s espec�fico. [6/11]
		switch (n) {
			1:	print "No ", (lm_estas) player, " en ning�n sitio del que ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "debamos";
						else print "deba";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deb�is";
						else print "debas";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "deban";
						else print "deba";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "debi�semos";
						else print "debiese";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "debieseis";
						else print "debieses";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "debiesen";
						else print "debiese";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "tener que";
				}
				print " ";
				LanguageVerb(verb_word);
				".";
			2:	print "No ", (lm_puedes) player, " salir ", (del_) x1,
				" porque ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estar�", (n) x1;
				}
				" cerrad", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajamos";
							else print "Bajo";
						} else {
							if (IsPluralNoun(player)) print "Salimos";
							else print "Salgo";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Baj�is";
							else print "Bajas";
						} else {
							if (IsPluralNoun(player)) print "Sal�s";
							else print "Sales";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajan";
							else print "Baja";
						} else {
							if (IsPluralNoun(player)) print "Salen";
							else print "Sale";
						}
					FIRST_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajamos";
							else print "Baj�";
						} else {
							if (IsPluralNoun(player)) print "Salimos";
							else print "Sal�";
						}
					SECOND_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajasteis";
							else print "Bajaste";
						} else {
							if (IsPluralNoun(player)) print "Salisteis";
							else print "Saliste";
						}
					THIRD_PERSON_PAST:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajaron";
							else print "Baj�";
						} else {
							if (IsPluralNoun(player)) print "Salieron";
							else print "Sali�";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajaremos";
							else print "Bajar�";
						} else {
							if (IsPluralNoun(player)) print "Saldremos";
							else print "Saldr�";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajar�is";
							else print "Bajar�s";
						} else {
							if (IsPluralNoun(player)) print "Saldr�is";
							else print "Saldr�s";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has supporter) {
							if (IsPluralNoun(player)) print "Bajar�n";
							else print "Bajar�";
						} else {
							if (IsPluralNoun(player)) print "Saldr�n";
							else print "Saldr�";
						}
				}
				" ", (del_) x1, ".";
			4:	print "No ", (lm_puedes) player, ". No ", (lm_estas) player," ";
				if (x1 has supporter) print "encima";
				else print "dentro";
				" ", (del_) x1, ".";
		}

	Fill:
		 "No ", (lm_puedes) player, " llenar", (lo) x1, ".";

	FullScore:
		!! Puntuaci�n en modo "explicativo". Puede activarse porque el
		!! usuario lo pida con el verbo "PUNTUACION LARGA" o porque el
		!! relato haya terminado (y la constante HAY_TAREAS est� definida).
		!!
		!!	1:	Texto introductorio al desglose de puntos
		!!	2:	Texto de objetos importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	3:	Texto de lugares importantes (los que tienen el atributo
		!!		"valepuntos")
		!!	4:	Texto final, tras la suma total impresa por la librer�a
		switch (n) {
			1:	if (deadflag) print "La puntuaci�n se desglos� ";
				else          print "La puntuaci�n se desglosa ";
				"de la siguiente manera:^";
			2: "por encontrar objetos importantes";
			3: "por visitar lugares importantes";
			4: print "total (de ", MAX_SCORE ; ")";
		}

	GetOff:
		!! Esta acci�n se genera ante la frase SAL DEL ARMARIO o similares.
		!! Ante SAL a secas la acci�n es Salir. Si el usuario no est� en el
		!! objeto indicado, se genera el siguiente mensaje de error. Si est�,
		!! la librer�a generar� una acci�n Salir, por lo que el mensaje de
		!! �xito ser� el de Salir.
		"No ", (lm_puedes) player, ". No ", (lm_estas) player, " en ",
		(the) x1, ".";

	Give:
		!!	1:	Error, el usuario intenta dar un objeto que no tiene.
		!!	2:	Error, el usuario se da el objeto a s� mismo.
		!!	3:	Aviso, se ha enviado la acci�n Dar al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto
		!!		que le hemos dado.
		!!
		!! [Observar que por defecto el objeto sigue en poder del
		!! usuario. Si queremos que el PNJ lo acepte, hay que programarlo
		!! como parte de su rutina Vida.]
		switch (n) {
			1:	"No ", (lm_tienes) player, " ", (the) x1, ".";
			2:	"Manose", (lm_as_) player, " ", (the) x1, " durante unos
				momentos, sin conseguir nada.";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"", (The) x1, " no parece", (n) x1,
						" interesad", (o) x1, ".";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"", (The) x1, " no parec�a", (n) x1,
						" interesad", (o) x1, ".";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"", (The) x1, " no parecer�", (n) x1,
						" interesad", (o) x1, ".";
				}
		}

	Go:
		!!	1:	Error, el usuario est� dentro/subido en un objeto del que
		!!		tiene que salir antes.
		!!	2:	Error, la localidad no tiene salida en esa direcci�n (y tampoco
		!!		tiene la propiedad "cant_go", ya que en este caso se habr�a
		!!		impreso el valor de esa propiedad.
		!!	3:	Error, el usuario ha intentado ir hacia arriba, pero all� hay
		!!		una puerta cerrada.
		!!	4:	Error, el usuario ha intentado ir hacia abajo, pero all� hay
		!!		una puerta cerrada.
		!!	5:	Error, en la direcci�n que ha dicho el usuario hay una
		!!		puerta cerrada.
		!!	6:	Error, en la direcci�n que ha dicho el usuario hay una puerta,
		!!		pero �sta no tiene una propiedad "door_to" (probablemente un
		!!		error de programaci�n del juego).
		switch (n) {
			1:	print (lm_ttienes) player, " que ";
				if (x1 has supporter) print "bajar", (lm_te) player;
				else print "salir";
				" ", (del_) x1, " antes.";
			2:	"No ", (lm_puedes) player, " ir por ah�.";
			3:	"", (lm_eeres) player, " incapaz de trepar por ", (the) x1, ".";
			4:	"", (lm_eeres) player, " incapaz de bajar por ", (the) x1, ".";
			5:	"No ", (lm_puedes) player, " pasar a trav�s ", (del_) x1, ".";
			6:	print "No ", (lm_puedes) player, " ir porque ", (the) x1," no ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "lleva", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "llevaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "llevar�", (n) x1;
				}
				" a ning�n sitio.";
		}

	Insert:
		!!	1:	Error, el objeto no est� en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje m�s adecuado].
		!!	2:	Error, el usuario intenta meter el objeto en otro que no tiene
		!!		el atributo "container".
		!!	3:	Error, el usuario intenta meter el objeto en un recipiente
		!!		cerrado.
		!!	4:	Error, el objeto es una prenda que el usuario lleva puesta.
		!!		[ESTE MENSAJE NO SE GENERA NUNCA, PARECE UN BUG DE LA LIBRER�A.
		!!		V�ase en su lugar el mensaje 6].
		!!	5:	Error, se intenta poner un objeto dentro de s� mismo.
		!!	6:	Aviso, el objeto es una prenda puesta, la librer�a va a
		!!		quit�rsela de forma autom�tica antes de reintentar Insert.
		!!	7:	Error, no queda sitio en el recipiente (el n�mero de objetos
		!!		que un recipiente puede contener se indica en su propiedad
		!!		"capacity").
		!!	8:	�xito. Mensaje a mostrar para cada objeto metido cuando se
		!!		meten muchos (ej: METE TODO EN LA BOLSA).
		!!	9:	�xito. Mensaje a mostrar cuando se mete un solo objeto dentro
		!!		de otro.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�amos que ", (coge)"r", (lo) x1,
								" y no sabemos si se dejar�", (n) x1, ".";
							"Antes tendr�a que ", (coge)"r", (lo) x1,
							" y no s� si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitamos";
							else print "Necesito";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�ais que ", (coge)"r", (lo) x1,
								" y no sab�is si se dejar�", (n) x1, ".";
							"Antes tendr�as que ", (coge)"r", (lo) x1,
							" y no sabes si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesit�is";
							else print "Necesitas";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�an que ", (coge)"r", (lo) x1,
								" y no saben si se dejar�", (n) x1, ".";
							"Antes tendr�a que ", (coge)"r", (lo) x1,
							" y no sabe si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitan";
							else print "Necesita";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					FIRST_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�amos que ", (coge)"r", (lo) x1,
								" y no sab�amos si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�a que ", (coge)"r", (lo) x1,
							" y no sab�a si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesit�bamos";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					SECOND_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�ais que ", (coge)"r", (lo) x1,
								" y no sab�ais si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�as que ", (coge)"r", (lo) x1,
							" y no sab�as si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitabais";
							else print "Necesitabas";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					THIRD_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�an que ", (coge)"r", (lo) x1,
								" y no sab�an si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�a que ", (coge)"r", (lo) x1,
							" y no sab�a si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitaban";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde fuese.";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendremos que ", (coge)"r", (lo) x1,
								" y no sabremos si se dejar�", (n) x1, ".";
							"Antes tendr� que ", (coge)"r", (lo) x1,
							" y no sab?e si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaremos";
							else print "Necesitar�";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�is que ", (coge)"r", (lo) x1,
								" y no sabr�is si se dejar�", (n) x1, ".";
							"Antes tendr�s que ", (coge)"r", (lo) x1,
							" y no sabr�s si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitar�is";
							else print "Necesitar�s";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�n que ", (coge)"r", (lo) x1,
								" y no sabr�n si se dejar�", (n) x1, ".";
							"Antes tendr� que ", (coge)"r", (lo) x1,
							" y no sabr� si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitar�n";
							else print "Necesitar�";
							" tener ", (the) x1, " para poder meter", (lo) x1,
							" donde sea.";
						}
				}
			2:	print "No se ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "pueden";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "pod�an";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "podr�n";
				}
				" meter cosas dentro ", (del_) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " estar�", (n) x1;
				}
				" cerrad", (o) x1, ".";
			4:	"", (lm_ttienes) player, " que quit�r", (lm_te) player, "",
				(lo) x1, " antes.";
			5:	"No ",(lm_puedes) player," poner un objeto dentro de s� mismo.";
			6:	"(Primero ", (lm_te) player, "", (lo) x1, " quit",
				(lm_as_) player, ").^";
			7:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "queda";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "quedaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "quedar�";
				}
				" sitio en ", (the) x1, ".";
			8:	"Hecho.";
			9:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Metimos";
						else print "Meto";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Meteis";
						else print "Metes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Meten";
						else print "Metes";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metimos";
						else print "Met�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metisteis";
						else print "Metiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Metieron";
						else print "Meti�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meteremos";
						else print "Meter�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meter�is";
						else print "Meter�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Meter�n";
						else print "Meter�";
				}
				" ", (the) x1, " dentro ", (del_) second, ".";
		}

	Inv:
		!!	1:	Mensaje si el inventario est� vac�o
		!!	2:	Encabezado del inventario, antes de la lista de objetos
		!!		generada por la librer�a
		!!	3 y 4: [6/11]
		switch (n) {
			1:	print "No llev", (lm_as) player, " nada.";
			2:	print "LLev", (lm_as) player;
			3:	print ":^";
			4:	print ".^";
		}

	Jump:
		"Salt", (lm_as_) player, " en el sitio, sin ning�n resultado.";

	JumpOver, Tie:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograremos";
				else print "lograr�";
			SECOND_PERSON_PRESENT,
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograr�is";
				else print "lograr�s";
			THIRD_PERSON_PRESENT,
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "lograr�n";
				else print "lograr�";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubi�semos logrado";
				else print "hubiese logrado";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubieseis logrado";
				else print "hubieses logrado";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "hubiesen logrado";
				else print "hubiese logrado";
		}
		" nada as�.";

	Kiss:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deber�amos.";
				"No creo que deba.";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deber�ais.";
				"En realidad no crees que debas.";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) "En realidad no deber�an.";
				"No cree que deba.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se nos ocurri�";
				else print "No se me ocurri�";
				" hacer algo as� en aquel momento.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se os ocurri�";
				else print "No se te ocurri�";
				" hacer algo as� en aquel momento.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "No se les ocurri�";
				else print "No se le ocurri�";
				" hacer algo as� en aquel momento.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se nos ocurrir�";
				else print "No se me ocurrir�";
				" hacer algo as� en ese momento.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se os ocurrir�";
				else print "No se te ocurrir�";
				" hacer algo as� en ese momento.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "No se le ocurrir�";
				else print "No se le ocurrir�";
				" hacer algo as� en ese momento.";
		}

	Listen:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escuchamos";
				else print "No escucho";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escuch�is";
				else print "No escuchas";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "No escuchas";
				else print "No escucha";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "No se escuchaba";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "No se escuchar�";
		}
		" nada fuera de lo com�n.";

	ListMiscellany:
		!! Los siguientes mensajes se muestran como aclaraciones cuando se est�
		!! listando el inventario del usuario, o los objetos que hay en una
		!! localidad. Junto a cada mensaje se comenta qu� condiciones deben
		!! darse en ese objeto para que se muestre ese mensaje aclaratorio.
		switch (n) {
			1:	print " (alumbrando)";
			!! El objeto tiene "luz" y la localidad no
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que est�", (n) x1, " cerrad", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " cerrad", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estar�", (n) x1, " cerrad", (o) x1, ")";
				}
			!! El objeto tiene "recipiente" pero no "abierto"
			3:	print " (cerrad", (o) x1, " y alumbrando)";
			!! Casos 2 y 1 juntos
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que est�", (n) x1, " vac�", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " vac�", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estar�", (n) x1, " vac�", (o) x1, ")";
				}
			!! El objeto es un recipiente abierto (o transparente) y no
			!!! tiene nada en su interior
			5:	print " (vac�", (o) x1, " y alumbrando)";
			!! Casos 1 y 4 juntos
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que est�", (n) x1, " cerrad", (o) x1,
						" y vac�", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " cerrad", (o) x1,
						" y vac�", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estar�", (n) x1, " cerrad", (o) x1,
						" y vac�", (o) x1, ")";
				}
			!! El objeto tiene "recipiente", no "abierto", pero s�
			!! "transparente"
			7:	print " (cerrad", (o) x1, ", vac�", (o) x1, " y
				alumbrando)";
			!! Casos 1 y 6 juntos

			!! Los casos siguientes son similares, pero se muestran cuando se
			!! solicita a la rutina EscribirListaDesde la opci�n INFOTOTAL. La
			!! librer�a puede combinar varios de estos mensajes, por eso no
			!! deben llevar el cerrado de par�ntesis al final, que lo a�ade la
			!! propia librer�a. *** NO SE ACONSEJA CAMBIAR ESTOS ***

			8:	print " (alumbrando y que llev", (lm_as) player,
				" puest", (o) x1;
			!! El objeto tiene "luz" y "puesto"
			9:	print " (alumbrando";
			!! El objeto tiene "luz" pero no "puesto"
			10:	print " (que llev", (lm_as) player, " puest", (o) x1;
			!! El objeto tiene "puesto" pero no "luz"
			11:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que est�", (n) x1, " ";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " ";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estar�", (n) x1, " ";
				}
			!! Mensaje introductorio para decir "que est�
			!! abierto/cerrado/vacio"...
			12:	print "abiert", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y "abierto" (y cosas dentro)
			13:	print "abiert", (o) x1, ", pero vac�", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y "abierto (pero vacio)
			14:	print "cerrad", (o) x1;
			!! Objeto tiene "recipiente", "abrible" y no "abierto"
			15: print "cerrad", (o) x1, " con llave";
			!! Objeto tiene "recipiente", "abrible" y "cerrojoechado" o
			!! "cerrojo"
			16:	print " vac�", (o) x1;
			!! Objeto tiene "recipiente", no "abrible" y "transparente"
			17:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " (que est�", (n) x1, " vac�", (o) x1, ")";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " (que estaba", (n) x1, " vac�", (o) x1, ")";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " (que estar�", (n) x1, " vac�", (o) x1, ")";
				}
			!! Como el caso anterior, pero mensaje m�s "largo" (que se activa
			!! si EscribirListaDesde es llamada sin el modo BREVE_BIT)
			18:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " que contiene", (n) x1, " ";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " que conten�a", (n) x1, " ";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " que contendr�", (n) x1, " ";
			}
			!! encabezado a la lista de lo que hay dentro del objeto
			19: print " (sobre ", (el_) x1;
			!! Si el objeto tiene "soporte", la librer�a va a listar sus
			!! contenidos. Este es el encabezado de la lista
			20: print ", encima ", (del_) x1;
			!! Como e l9, pero en otra modalidad (que se activa si
			!! EscribirListaDesde es llamada sin el modo BREVE_BIT)
			21: print " (en ", (el_) x1;
			!! Si el contenido tiene "recipiente" y puede verse su interior
			!! y hay cosas, la librer�a va a mostrar sus contenidos. Este
			!! es el encabezado de la lista
			22: print ", dentro ", (del_) x1;
			!! Como el 21, pero en otra modalidad (que se activa si
			!! EscribirListaDesde es llamada sin el modo BREVE_BIT)
		}

 	LMode1:
	    !! La acci�n LMode1 se genera ante el comando BREVE (o NORMAL). La
	    !! librer�a imprime la constante Historia y a continuaci�n este
	    !! mensaje.
		print_ret "[", (string) Story, " est� ahora en su modo normal ~breve~,
		que da s�lo descripciones largas de los lugares la primera vez que son
		visitadas, y descripciones cortas en otro caso].";

	LMode2:
    	!! La acci�n LMode2 se genera ante el comando LARGO. La librer�a
		!! imprime la constante Historia y a continuaci�n este mensaje.
		print_ret "[", (string) Story, " est� ahora en su modo ~largo~, que
		siempre da descripciones largas de los lugares (incluso si ya hab�as
		estado antes)].";

	LMode3:
    	!! La acci�n LMode3 se genera ante el comando SUPERBREVE. La librer�a
		!! imprime la constante Historia y a continuaci�n este mensaje.
		print_ret "[", (string) Story, " est� ahora en su modo ~superbreve~,
		que siempre da descripciones cortas de los lugares (incluso si nunca
		hab�as estado antes).";

	Lock:
		!! Lock se genera con CIERRA <objeto> CON <objeto2>, o
		!! tambi�n ante ECHA CERROJO A <objeto> (sin especificar un
		!! segundo objeto en este caso).
		!!
		!!	1:	Error, el objeto al que se intenta echar el cerrojo no tiene la
		!!		propiedad "lockable".
		!!	2:	Error, el objeto al que se intenta echar el cerrojo tiene la
		!!		propiedad "lockable", pero ya tiene tambi�n "locked".
		!!	3:	Error, el objeto tiene las propiedades "lockable" y "open". No
		!!		se le puede echar el cerrojo hasta que no se cierre.
		!!	4:	Error, el <objeto2> especificado no coincide con el que el
		!!		objeto indica en su propiedad "with_key".
		!!	5:	�xito, se echa el cerrojo al objeto (con el <objeto2> si �ste
		!!		es especificado y se puede encontrar en la variable "second").
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "parece", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "parec�a", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "parecer�", (n) x1;
				}
				" tener ning�n tipo de cerrojo.";
			2:	if (x1 provides with_key) {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print (The) x1, " ya estaba", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print (The) x1, " ya estaba", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print (The) x1, " ya estar�", (n) x1;
					}
					" cerrad", (o) x1, " con llave.";
				}
				else {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print (The) x1, " ya tiene", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print (The) x1, " ya ten�a", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print (The) x1, " ya tendr�", (n) x1;
					}
					" echado el cerrojo.";
				}
			3:	"Primero ", (lm_tienes) player, " que cerrar ", (the) x1, ".";
			4:	if (second) switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No parece", (n) x1, " encajar en la cerradura.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No parec�a", (n) x1, " encajar en la cerradura.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No parecer�", (n) x1, " encajar en la cerradura.";
				}
				"Necesit", (lm_as) player, " alg�n tipo de llave.";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cerramos";
							else print "Cierro";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echamos";
							else print "Echo";
						}
					SECOND_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrais";
							else print "Cierras";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Ech�is";
							else print "Echas";
						}
					THIRD_PERSON_PRESENT:
						if (second) {
							if (IsPluralNoun(player)) print "Cierran";
							else print "Cierra";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echan";
							else print "Echa";
						}
					FIRST_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerramos";
							else print "Cerr�";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echamos";
							else print "Ech�";
						}
					SECOND_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrasteis";
							else print "Cerraste";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echasteis";
							else print "Echaste";
						}
					THIRD_PERSON_PAST:
						if (second) {
							if (IsPluralNoun(player)) print "Cerraron";
							else print "Cerr�";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echaron";
							else print "Ech�";
						}
					FIRST_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerraremos";
							else print "Cerrar�";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echaremos";
							else print "Echar�";
						}
					SECOND_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrar�is";
							else print "Cerrar�s";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echar�is";
							else print "Echar�s";
						}
					THIRD_PERSON_FUTURE:
						if (second) {
							if (IsPluralNoun(player)) print "Cerrar�n";
							else print "Cerrar�";
							" ", (the) x1, " con ", (the) second, ".";
						} else {
							if (IsPluralNoun(player)) print "Echar�n";
							else print "Echar�";
						}
				}
				" el cerrojo ", (al_) x1, ".";
		}

	Look:
		!! La acci�n Look se genera cuando el usuario pone MIRAR, pero tambi�n
		!! de forma autom�tica al entrar en una localidad nueva, o cuando el
		!! usuario sale/se baja de un objeto en el que estaba.
		!!
		!! Algunos de los mensajes que se definen aqu� aparecen en el "t�tulo"
		!! de la localidad (lo que aparece en negrita antes de la descripci�n
		!! de la localidad).
		!!
		!!	1:	Aclaraci�n a a�adir tras el t�tulo si el usuario est� subido
		!!		en un objeto.
		!!	2:	Aclaraci�n a a�adir tras el t�tulo si el usuario est� dentro
		!!		de un objeto.
		!!	3:	Aclaraci�n a a�adir tras el t�tulo si el usuario ha sido
		!!		transformado en otro personaje mediante una llamada a
		!!		ChangePlayer(nuevo, 1); (sin el 1, la librer�a no intentar�
		!!		mostrar este mensaje).
		!!	4:	Una vez que la librer�a ha mostrado la descripci�n de la
		!!		localidad, si el usuario estaba encima de un supporter, la
		!!		librer�a generar� este mensaje 4 para mostrar qu� m�s cosas
		!!		hay sobre el supporter.
		!!	Restante: 5,6 [6/11] antes 'default'
		!!		Son usados por la librer�a para listar los objetos "simples"
		!!		que hay en la localidad. Son objetos "simples" los que no
		!!		dan su propia auto-descrcipcion a trav�s de la propiedad
		!!		"describe" o "initial".
		!!	7:	Respuesta estandar para MirarHacia [6/11]
		switch (n) {
			1:	print ", ";
				!! XXX: Se puede usar un mensaje de aclaraci�n completamente
				!! personalizado definiendo la propiedad "clarification" en un
				!! objeto ("clarification" tiene que devolver un string o una
				!! rutina encargada de imprimir un string). Ej: SALA DE ESTAR,
				!! sentado en el sof�
				if ( x1 provides clarification ) {
					if (x1.clarification ofclass string)
						print (string) x1.clarification;
					else if (x1.clarification ofclass routine)
						indirect(x1.clarification);
				}
				else print "sobre ", (the) x1;
			2:	print ", ";
				!! XXX: Ver comportamiento de Look con n == 1
				if ( x1 provides clarification ) {
					if (x1.clarification ofclass string)
						print (string) x1.clarification;
					else if (x1.clarification ofclass routine)
						indirect( x1.clarification);
				}
				else print ", en ", (the) x1;
			3:	print " (como ", (object) x1 , ")";
			4:	print "^Sobre ", (the) x1;
				WriteListFrom(child(x1),
						ENGLISH_BIT + RECURSE_BIT + PARTINV_BIT
						+ TERSE_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
			5,	!! XXX: Si la localidad actual tiene definida la propiedad
			6:	!! "inhibit_object_list" y est� establecida como verdadero, se
				!! evita que se imprima el listado autom�tico de objetos
				!! simples junto con la descripci�n de la localidad
				if (real_location provides inhibit_object_list)
					if (real_location.inhibit_object_list)
						return true;

				new_line;
				if (x1~=location) {
					if (x1 has supporter) print "Sobre "; else print "En ";
					print (the) x1, " ", (lm_puedes) player, " ver ";
				} else print (lm_ppuedes) player, " ver ";
				if (n==5) print "tambi�n ";
				WriteListFrom(child(x1),
					ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT
					+ PARTINV_BIT + TERSE_BIT + CONCEAL_BIT);
				".";
			7:	"No observ", (lm_as_) player, " nada digno de menci�n al mirar
				hacia ", (the) x1, ".";
			8:	if (x1 has supporter) print " (sobre "; else print " (en ";
				print (the) x1, ")";
		}

	LookUnder:
		!!	1:	Error, estamos a oscuras.
		!!	2:	�xito, mensaje por defecto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Est�";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estar�";
				}
				" demasiado oscuro como para ver algo.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "vemos";
						else print "veo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "veis";
						else print "ves";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "ven";
						else print "ve";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "vimos";
						else print "vi";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "visteis";
						else print "viste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "vieron";
						else print "vio";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "veremos";
						else print "ver�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "ver�is";
						else print "ver�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "ver�n";
						else print "ver�";
				}
				" nada inusual.";
		}

	Mild:
		!! Respuesta si se usa como primera palabra alg�n insulto suave.
		"Bastante.";

	Miscellany:
		!! Esta es una falsa acci�n, que se usa simplemente para agrupar aqu�
		!! todos los mensajes de error del parser, los mensajes ante algunos
		!! metacommandos, o algnouns mensajes de librer�a no relacionados con
		!! acci�n alguna. La asignaci�n de n�meros a mensajes es bastante
		!! caprichosa.
		switch (n) {
			1:
				!! El usuario ha especificado objetos multiples, pero el parser
				!! tiene una lista que no admite m�s de 16, de modo que los
				!! restantes objetos no ser�n procesados.
				"(S�lo se consideran los diecis�is primeros objetos).";
			2:
				!! El usuario ha usado objetos m�ltiples, pero por alguna raz�n
				!! la lista del parser est� vac�a.
				"[No se pudo determinar a qu� objetos te has referido].";
			3:
				!! Mensaje de fin del relato. Has muerto.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hemos muerto ";
						else print " He muerto ";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hab�is muerto ";
						else print " Has muerto ";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Han muerto ";
						else print " Ha muerto ";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�amos muerto ";
						else print " Hab�a muerto ";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�ais muerto ";
						else print " Hab�as muerto ";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�an muerto ";
						else print " Hab�a muerto ";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habremos muerto ";
						else print " Habr� muerto ";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habr�is muerto ";
						else print " Habr�s muerto ";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habr�n muerto ";
						else print " Habr� muerto ";
				}
			4:
				!! Mensaje de fin del relato. Victoria.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hemos ganado ";
						else print " He ganado ";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Hab�is ganado ";
						else print " Has ganado ";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print " Han ganado ";
						else print " Ha ganado ";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�amos ganado ";
						else print " Hab�a ganado ";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�ais ganado ";
						else print " Hab�as ganado ";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print " Hab�an ganado ";
						else print " Hab�a ganado ";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habremos ganado ";
						else print " Habr� ganado ";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habr�is ganado ";
						else print " Habr�s ganado ";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print " Habr�n ganado ";
						else print " Habr� ganado ";
				}
			5:
				!! Mensaje a mostrar tras el fin del juego, para pedir al
				!! usuario si quiere reniciar, recuperar, anular, puntuaci�n,
				!! curiosidades o terminar.
				print "^�Quieres REINICIAR, RECUPERAR un juego guardado";
				#IFDEF DEATH_MENTION_UNDO;
					print ", ANULAR tu �ltimo movimiento";
				#ENDIF;
				#IFNDEF NO_PUNTUACION;
					if (TASKS_PROVIDED==0)
						print ", ver la PUNTUACI�N de este juego";
				#ENDIF; ! NO_PUNTUACION
				if (deadflag==2 && AMUSING_PROVIDED==0)
					print ", ver algunas CURIOSIDADES";
				" o TERMINAR?";
			6:
				!! Error si el int�rprete no tiene "undo"
				"[Tu int�rprete no puede ~DESHACER~ acciones].";
			7:
				#Ifdef TARGET_ZCODE; ![6/11]
				!! Otro error si el int�rprete no tiene "undo", pero no hab�a
				!! sido detectado correctamente.
				"[~DESHACER~ fall�. (Puede que tu int�rprete no permita
				realizar esa acci�n)].";
				#Ifnot; ! TARGET_GLULX
				"[No puedes ~DESHACER~ m�s].";
				#Endif; ! TARGET_
			8:
				!! Si el usuario no responde correctamente a la pregunta del
				!! mensaje [Miscellany,5]
				"[Por favor, introduce una de las respuestas anteriores].";
			9:
				!! Mensaje cuando se detecta, al final del turno, que ya no hay
				!! una fuente de luz en la localidad actual.
				print "^�";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos hemos";
						else print "Me he";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os hab�is";
						else print "Te has";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se han";
						else print "Se ha";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos hab�amos";
						else print "Me hab�a";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os hab�ais";
						else print "Te hab�as";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se hab�an";
						else print "Se hab�a";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos habremos";
						else print "Me habr�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os habr�is";
						else print "Te habr�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se habr�n";
						else print "Se habr�";
				}
				" quedado a oscuras!";
			10:
				!! Mensaje cuando el usuario introduce una linea en blanco.
				"[No has introducido ninguna instrucci�n].";
			11:
				!! Si el usuario intenta "undo" al principio del juego
				"[No se puede ~DESHACER~ algo que no has hecho].";
			12:
				!! Si el usuario pone "undo" dos veces.
				"[No se puede ~DESHACER~ dos veces seguidas].";
			13:
				!! �xito en el "undo".
				"[Retrocediendo al turno anterior].";
			14:
				!! Si el usuario pone EEPA (verbo para corregir), pero el
				!! parser no recordaba ninguna palabra mal. Ejmplo de uso del
				!! comando EEPA:
				!!		> SACA MAZANA VERDE DE LA CESTA
				!!		No vqeo eso por aqu�.
				!!		> EEPA MANZANA
				!!		Sacas la manzana verde de la cesta de mimbre.
				"[Eso no puede corregirse].";
			15:
				!! Se usa EEPA sin especificar la palabra corregida.
				"[Has utilizado ~EEPA~ sin especificar qu� palabra deseabas
				corregir].";
			16:
				!! Si el usuario pone EEPA seguido de dos o m�s palabras.
				"[~EEPA~ s�lo puede corregir una palabra].";
			17:
				!! Descripci�n del objeto Oscuridad.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Est�";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estar�";
				}
				" demasiado oscuro como para poder ver algo.";
			18:
				!! Nombre corto del objeto usuario.
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_PAST,
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "nosotr", (o) player;
						else print "m�";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_PAST,
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "vosotr", (o) player;
						else print "t�";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_PAST,
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "ell", (o) player;
						else print "s�";
				}
				print " mism", (o) player;
			19:
				!! Descripci�n del personaje controlado por el usuario.
				"Tan buen aspecto como siempre.";
			20:
				!! Cuando el usuario pone PNJ, REPITE para que el PNJ haga otra
				!! vez la �ltima acci�n.
				"[Para repetir un comando como ~PERSONAJE, SALTA~, escribe
				~REPITE~, en lugar de ~PERSONAJE, REPITE~].";
			21:
				!! Cuando el usuario pone REPITE como primer commando del juego.
				"[No hay comando que repetir].";
			22:
				!! El usuario ha comenzado la frase con una coma.
				"[No se puede empezar una frase con una coma].";
			23:
				!! Cuando el usuario pone, por ejemplo; PEPE, COGE HACHA, pero
				!! no hay un objeto que responda al name PEPE.
				"[Parece que has tratado de hablar con alguien, pero no se pudo
				identificar con qui�n].";
			24:
				!! Si el usuario intenta hablar con un objeto que no es
				!! "animate" ni "talkable" ("talkable" debe ponerse a objetos
				!! inanimates con los que se podr�a hablar, como un micr�fono).
				"[No es posible hablar con ", (the) x1, "].";
			25:	!! Hay palabras no comprendidas entre el nombre de un PNJ y la
				!! coma, ej: PEPE ZAFDSRGG, SALTA.
				"[Para iniciar una conversaci�n, intenta �rdenes del tipo:
				PERSONAJE, HOLA].";
			26:
				!! La gram�tica especifica que una acci�n debe efectuarse sobre
				!! un objeto en poder del usuario (token 'held'), pero el
				!! usuario lo ha intentado sobre un objeto que no tiene, aunque
				!! est� a su alcance. El parser intentar� autom�ticamente coger
				!! ese objeto antes de efectuar la acci�n. En este mensaje se
				!! avisa al usuario de esta intenci�n.
				"(Primero trat", (lm_as_) player, " de ", (coge) "r ",
				(the) x1, ".)";

			!! ERRORES DE PARSING: Estos errores son generados por la librer�a,
			!! a menos que el programador proporcione su propia funci�n
			!! ParserError para manejo de errores.

			27:
				!! ERROR DE PARSING. El parser se ha atascado. Es el tipo de
				!! error m�s gen�rico. Si el parser puede, se generar� un error
				!! m�s concreto.
				"[No se pudo entender esa instrucci�n.]";

			28:
				!! ERROR DE PARSING. A la instrucci�n le sobraban palabras,
				!! aunque el parser ha entendido gran parte de su significado.
				print "[Intenta de nuevo porque s�lo se pudo entender: ~";
				PrintCommand();
				print "~].^";
				return true;

			29:
				!! ERROR DE PARSING. El parser esperaba un token de tipo
				!! n�mero.
				"[No se pudo comprender ese n�mero].";

			30:
				!! ERROR DE PARSING. El parser no ha comprendido el nombre del
				!! objeto al que se refiere el jugador, o ese objeto no est�
				!! aqu�.
				"[Te has referido a algo con lo que no se puede interactuar en
				este momento].";

			31:
				!! ERROR DE PARSING. Este error parece que no se genera nunca.
				!! Un posible bug de libreria, o restos de versiones arcaicas.
				"[Parece que falta informaci�n en esa instrucci�n].";

			32:
				!! ERROR DE PARSING. El objeto que el usuario intenta usar no
				!! est� en su poder. El parser ha intentado "cogerlo de forma
				!! automatica", pero ha fallado.
				"No ", (lm_tienes) player, " eso.";

			33:
				!! ERROR DE PARSING. El usuario ha intentado usar objetos
				!! m�ltiples (o "TODO") con un verbo que en su gram�tica no lo
				!! admite.
				"[No se pueden especificar objetos m�ltiples con ~",
				(address) verb_word, "~.]";

			34:
				!! ERROR DE PARSING. El usuario ha intentado objetos multiples
				!! para "noun" y para "second", como en METE TODO EN TODO.
				"[S�lo se pueden especificar objetos m�ltiples una vez en cada
				l�nea].";

			35:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! COMELO, pero el parser no tiene asignado un valor a ese
				!! pronombre.
				"[No est� claro a qu� te refieres con ~",
				(address) pronoun_word ,"~].";

			36:
				!! ERROR DE PARSING. El usuario ha puesto una lista de objetos
				!! y ha usado la palabra EXCEPTO para exceptuar algo que no
				!! estaba incluido en la lista, por ejemplo: COGE TODAS LAS
				!! MONEDAS EXCEPTO EL SACO.
				"[Has exceptuado algo que no estaba incluido].";

			37:
				!! ERROR DE PARSING. La gram�tica de un verbo obliga a que el
				!! objeto sobre el que se act�e sea animate (tiene un token de
				!! tipo "creature"), pero el usuario lo ha intentado sobre un
				!! objeto que no es animate.
				"[S�lo se puede hacer eso con seres animados].";

			38:
				!! ERROR DE PARSING. La primera palabra usada por el usuario es
				!! desconocida (o la primera palabra tras la coma, si se trata
				!! de una orden a un PNJ).
				print "[La instrucci�n ~";
				for (i = 0: i < WordLength(1): i++)
					print (char) WordAddress(1) -> i;
				"~ no est� definida].";

			39:
				!! ERROR DE PARSING. El usuario intenta actiones sobre las
				!! palabras que est�n en la propiedad "irrelevante" de la
				!! localidad.
				"[No es necesario referirse a eso para terminar la historia].";

			40:
				!! ERROR DE PARSING. El usuario ha usado un pronombre, como
				!! EXAMINALO, pero el pronombre se refiere a un objeto que ya
				!! no est� visible.
				"[Ahora mismo no se puede encontrar lo que representa el
				pronombre ~", (address) pronoun_word, "~ (", (the) pronoun_obj,
				").]";

			41:
				!! ERROR DE PARSING. Este error no se produce nunca.
				!! Probablemente sigue aqu� por razones de compatibilidad, o
				!! por despiste de Graham. �Tal vez ha sido sustituido en
				!! versiones mas recientes por el mensaje n�mero 28?
				"[No se pudo entender la �ltima parte de la instrucci�n].";

			42:
				!! ERROR DE PARSING. El usuario ha solicitado un n�mero de
				!! objetos en una lista de objetos m�ltiples, pero el parser no
				!! es capaz de encontrar tantos. Por ejemplo: COGE SEIS MONEDAS.
				if (x1==0) "[No hay suficientes].";
		        else if (x1 == 1) {
			    	print "[Aqu� s�lo hay un";
			    	if (multiple_object-->1) print (o) multiple_object-->1;
			    	else print "o";
			    	" disponible].";
			    }
				"[S�lo hay ", (number) lm_o, " disponibles para esa acci�n].";

			43:
				!! ERROR DE PARSING. El usuario ha puesto TODO como objeto
				!! m�ltiple, pero el parser no ha encontrado ning�n objeto. En
				!! realidad este error parece no producirse nunca y el que
				!! acaba gener�ndose siempre es el siguiente (#44, ASKSCOPE_PE).
				"[No se puede encontrar nada con lo que hacer eso].";

			44:
				! TODO - mensaje del parser
				!! El usuario ha intentado objetos m�ltiples usando TODO
				!! pero el parser no ha encontrado ninguno. Por ejemplo, COGE
				!! TODO o DEJA TODO si no hay nada cerca o en el inventario.
				!! Modificado en [020621] para dar un mensaje m�s coherente
				!! si el usuario tiene alg�n objeto en su inventario.
				if (action_to_be == ##Drop) {
					print "�Pero si no llev", (lm_as) player, " nada";
					if (children (player)) " de eso!";
					else "!";
				}
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					FIRST_PERSON_PAST,
					FIRST_PERSON_FUTURE:
						print "No hay nada que ";
					SECOND_PERSON_PRESENT,
					SECOND_PERSON_PAST,
					SECOND_PERSON_FUTURE:
						print "No hab�a nada que ";
					THIRD_PERSON_PRESENT,
					THIRD_PERSON_PAST,
					THIRD_PERSON_FUTURE:
						print "No habr� nada que ";
				}
				LanguageVerb(verb_word);
				".";
			45:
				! TODO - mensaje del parser
				!! El usuario ha nombrado un PNJ ambiguo (hay m�s de noun con
				!! el mismo name cerca). El parser le pide aclaraci�n. Este
				!! mensaje es la primera parte de la pregunta, el resto lo pone
				!! el parser (que es la lista de PNJs entre los que duda).
				!! Debemos poner a 1 la variable PreguntaCualExactamente cuando
				!! se generan este tipo de preguntas aclaratorias.
				print "�Qui�n concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
			46:
				! TODO - mensaje del parser
				!! El usuario ha nombrado un objeto ambiguo (hay m�s de objeto
				!! con el mismo nombre cerca). El parser le pide aclaraci�n.
				!! Este mensaje es la primera parte de la pregunta, el resto lo
				!! pone el parser (que es la lista de objetos entre los que
				!! duda). Debemos poner a 1 la variable PreguntaCualExactamente
				!! cuando se generan este tipo de preguntas aclaratorias.
				print "�Cu�l concretamente, ";
				PreguntaCualExactamente=1;
				ImprimirListaDudosos("o");
				!print "?^";
			47:
				!! El usuario ha respondido "TODOS" o "AMBOS" a una pregunta
				!! aclaratoria como la anterior, pero el verbo no admite
				!! objetos m�ltiples.
				print "[Desafortunadamente s�lo puedes referirte a un objeto
				en este caso. �Cu�l exactamente?]^";
				PreguntaCualExactamente=1;
			48:
				! TODO - Editar mensaje: "Tienes que indicar a qui�n..."
				!! El usuario ha escrito una frase u orden a PSI incompleta,
				!! como BESA (verbo aplicado sobre PSIs normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				if (IniciarPregunta() ==0 ) print "A qui�n";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor~=player) print " ", (the) actor;
				print "?";
				new_line;
			49:
				! TODO - Editar mensaje: "Tienes que indicar a qui�n..."
				!! El usuario ha escrito una frase u orden incompleta, como
				!! COGE (verbo aplicado sobre objetos normalmente). El parser
				!! le pregunta para que complete la frase.
				PreguntaCualExactamente = 1;
				if (IniciarPregunta() ==0 ) print "Qu�";
				if (actor ~= player) print " tiene que ";
				else print " quieres ";
				IdiomaImprimirComando();
				if (actor~=player) print " ", (the) actor;
				print "?";
				new_line;
			!#IFNDEF NO_PUNTUACION;
			50:
				! TODO - mensaje del parser
				!! El usuario acaba de realizar una acci�n que punt�a (la
				!! librer�a ha detectado que la variable score ha cambiado de
				!! valor). Se informa de ello al player. El par�metro x1
				!! contiene el incremento (o decremento) en la puntuaci�n.
				print "Tu puntuaci�n ha ";
				if (x1 > 0) print "aumentado";
				else {
					x1 = -x1;
					print "disminuido";
				}
				print " en ", (number) x1, " punto";
				if (x1 > 1) print "s";
			!#ENDIF; ! NO_PUNTUACION
			51:
				!! El usuario ha intentado una acci�n con objeto m�ltiple
				!! (como COGE TODO). Esta acci�n es convertida por el parser en
				!! una serie de actiones COGE OBJETO1, COGE OBJETO2, etc... Si
				!! en la ejecuci�n de alguna de estas actiones encuentra que la
				!! localidad del player ha cambiado, debe abortar el proceso.
				!! Este mensaje informa de ello al usuario.
				"(Se ha producido un evento inesperado que ha obligado a
				recortar la lista de objetos sobre los que actuabas).";
			52:
				!! En los men�s, se espera a que el player escriba un n�mero
				!! para mostrar una entrada del men�. Si pulsa un numero
				!! incorrecto, se saca este mensaje. El par�metro x1 contiene
				!! el n�mero m�s alto v�lido.
				new_line;
				print "[Escribe un n�mero del 1 al ", x1, ", 0 para volver a
				mostrarlo, o pulsa Intro].";
				new_line;
				return true;
			53:
				!! Mensaje que muestra el sistema de men�s cuando espera una
				!! tecla.
				new_line;
				"[Por favor, pulsa ESPACIO].";
			54:
				! TODO - Guardar comentarios sin imprimir mensajes
				"[Comentario guardado].";
			55:
				"[Comentario NO guardado].";
			56:
				print ".^";
			57:
				print "?^";
		}

	No:
		!! Cuando el usuario pone NO, a secas, se genera esta acci�n. Est�
		!! pensada por si el relato suelta una frase del estilo de "�Pero t�
		!! eres tonto?" y el usuario responde NO. De todas formas, hay un
		!! problema, y es que NO es normalmente la acci�n Ir al noroeste. Si
		!! queremos que NO sea provisionalmente la acci�n No, entonces se debe
		!! poner a 1 la variable PreguntaSiNo antes de escribir el texto
		!! "�Pero t� eres tonto?". En ese caso, el parser interpretar� "NO"
		!! como la acci�n No, pero �nicamente durante el siguiente turno.
		"[S�lo se trataba de una pregunta ret�rica].";

	NotifyOff:
		"[Notificaci�n de puntuaci�n desactivada].";

	Objects:
		! TODO - mensaje del parser
		!! Ante el verbo "OBJETOS" se genera esta acci�n, que muestra una
		!! lista de todos los objetos que el usuario ha manipulado a lo largo
		!! del juego, junto con una indicaci�n de qu� hizo con ellos.
		!!
		!!	1:	Texto introductorio a la lista.
		!!	2:	Si no ha manejado a�n ninguno.
		!!	3:	Indicaci�n de que lo lleva puesto.
		!!	4:	Indicaci�n de que lo lleva en su inventario.
		!!	5:	Indicaci�n de qui�n lo tiene ahora (si lo tiene un PNJ).
		!!	6:	Indicaci�n de d�nde est� el objeto (si est� en una localidad).
		!!	7:	Indicaci�n de d�nde est� el objeto (si est� en un "entrable").
		!!	8:	Indicaci�n de d�nde est� el objeto (si est� en un recipiente).
		!!	9:	Indicaci�n de d�nde est� el objeto (si est� en un soporte).
		!!	10:	Indicaci�n de que se ha perdido (no est� en ninguno de los
		!!		casos anteriores).
		switch (n) {
			1:	"Objetos que has manejado:^";
			2:	"Ninguno.";
			3:	print "   (puest", (o) x1, ")";
			4:	print "   (", (lm_contigo) player, ")";
			5:	print "   (dejad", (o) x1, " con alguien)";
			6:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (name) x1, ")";
			7:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (the) x1, ")";
			8:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " dentro ", (del_) x1, ")";
			9:	print "   (";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ahora";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "entonces";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "en ese momento";
				}
				print " en ", (the) x1, ")";
			10:	print "   (perdid", (o) x1, ")";
		}

	Open:
		!!	1:	Error, el objeto no tiene el atributo "openable".
		!!	2:	Error, el objeto es abrible, pero tiene "locked".
		!!	3:	Error, el objeto es abrible, pero ya tiene el atributo "open".
		!!	4:	�xito, el objeto se abre, y adem�s era recipiente. Se muestra
		!!		entoces la lista de objetos que hab�a en su interior (si habia
		!!		algo).
		!!	5:	�xito, el objeto se abre (pero no tiene nada en su
		!!		interior, o no era recipiente).
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"es algo que pueda abrirse";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"era algo que se pudiese abrir.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"ser� algo que pueda abrirse.";
				}
			2:	switch (_grammatical_inflection) {
				FIRST_PERSON_PRESENT,
				SECOND_PERSON_PRESENT,
				THIRD_PERSON_PRESENT:
					print "Est�", (n) x1;
				FIRST_PERSON_PAST,
				SECOND_PERSON_PAST,
				THIRD_PERSON_PAST:
					print "Estaba", (n) x1;
				FIRST_PERSON_FUTURE,
				SECOND_PERSON_FUTURE,
				THIRD_PERSON_FUTURE:
					print "Estar�", (n) x1;
				}
				" cerrad", (o) x1, " con llave.";
			3:	print "Ya ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "estaba", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estar�", (n) x1;
				}
				" abiert", (o) x1, ".";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abr�is";
						else print "Abres";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abren";
						else print "Abre";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abr�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abristeis";
						else print "Abriste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrieron";
						else print "Abri�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriremos";
						else print "Abrir�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrir�is";
						else print "Abrir�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrir�n";
						else print "Abrir�";
				}
				print " ", (the) x1, ", descubriendo ";
				if (WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT) == 0) {
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							"que est�", (n) x1, " vac�", (o) x1, ".";
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							"que estaba", (n) x1, " vac�", (o) x1, ".";
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							"que estar�", (n) x1, " vac�", (o) x1, ".";
					}
				} else ".";
			5:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abr�is";
						else print "Abres";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Abren";
						else print "Abre";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrimos";
						else print "Abr�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abristeis";
						else print "Abriste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Abrieron";
						else print "Abri�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abriremos";
						else print "Abrir�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrir�is";
						else print "Abrir�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Abrir�n";
						else print "Abrir�";
				}
				"", (the) x1, ".";
		}

	Order:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print (The) x1, " tiene", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print (The) x1, " ten�a", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print (The) x1, " tendr�", (n) x1;
		}
		" mejores cosas que hacer.";

	Places:
		!! El verbo "LUGARES" muestra un listado de los lugares que el usuario
		!! ha visitado. Aqu� debemos escribir el texto introductorio a esa
		!! lista.
		switch (n) {
			1:  print "[Has visitado: ";
			2:  print ".]^";
		}

	Pray:
		print "La fe tal vez ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "pueda";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "pudiese";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "podr�";
		}
		" resultar �til en una ocasi�n diferente.";

	Prompt:
		!! El prompt aparece justo antes de pedir una nueva l�nea al usuario.
		!! Puede definirse para que sea una frase, o se genere una frase
		!! aleatoria en cada turno, por ejemplo.
		new_line;
		print "> ";

	Pronouns:
		!! Esta acci�n (generada por el verbo PRONOMBRES) muestra una lista
		!! de qu� significa en ese momento para el parser cada pronombre:
		!! -lo, -la, -los, -las...
		!!
		!!	1:	Texto introductorio.
		!!	2:	La palabra "es".
		!!	3:	Texto a mostrar si el pronombre no est� definido.
		!!	4:	Si el juego no define pronombres.
		!!	5:	[6/11].
		switch (n) {
			1:	print "[En este momento, ";
			2:	print "es ";
			3:	print "no est� definido";
			4:	print "el juego no conoce ning�n pronombre].";
				new_line;
				return true;
			5:	print "].";
				new_line;
				return true;
		}

	Pull, Push, Turn:
		!! Las acciones Pull, Push y Turn generan todas ellas los
		!! mismos mensajes, pero pueden darse 4 casos:
		!!	1:	El objeto tiene el atributo 'static'.
		!!	2:	El objeto tiene el atributo 'scenery'.
		!!	3:	El objeto no es 'static' ni 'scenery'.
		!!	4:	El objeto es un ser animado.
		!! [Nota, si el objeto tiene ambos 'estatico' y 'escenario' se
		!! est� tambi�n en el caso 1.]
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estar�", (n) x1;
				}
				" firmemente sujet", (o) x1, ".";
			2:	"No ", (lm_eres_) player, " capaz.";
			3:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "ocurre";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "ocurri�";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "ocurrir�";
				}
				" nada, aparentemente.";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Eso ser�a";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Aquello hubiese sido";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Eso ser�a";
				}
				", como poco, maleducado.";
		}

!!	Push:	see Pull.

	PushDir:
		!! La acci�n PushDir se genera ante frases como EMPUJA EL COCHE HACIA
		!! EL NORTE. Hay 3 casos posibles:
		!!	1:	Si el juego no ha previsto la posibilidad de empujar ese
		!!		objeto hacia una direcci�n (o sea, no llama a la rutina
		!!		PermitirEmujarDir). Esta es la respuesta por defecto m�s
		!!		habitual.
		!!	2:	Si el usuario pone tras HACIA algo que no es una direcci�n.
		!!		(respuesta por defecto en este caso).
		!!	3:	Si intenta empujar hacia arriba o hacia abajo.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						print "No ";
						if (IsPluralNoun(player)) "creemos";
						else print "creo";
						" que empujar", (lo) x1, " sirva de nada.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "cre�is";
						else print "crees";
						" que empujar", (lo) x1, " sirva de nada.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que empujar", (lo) x1, " sirva de nada.";
					FIRST_PERSON_PAST:
						print "No ";
						if (IsPluralNoun(player)) print "cre�amos";
						else print "cre�a";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�ais";
						else print "cre�as";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�an";
						else print "cre�a";
						" que empujar", (lo) x1, " hubiese servido de nada.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Empujar ", (the) x1, " no servir� de nada.";
				}
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"Eso no es una direcci�n.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"Aquello no era una direcci�n.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"Eso no ser� una direcci�n.";
				}
			3:	"No ", (lm_puedes) player, " empujar", (lo) x1, " en esa
				direcci�n.";
		}

	PutOn:
		!!	1:	Error, el objeto no est� en poder del usuario. [Nota, conviene
		!!		mirar en este caso si el objeto es animado o no, para generar
		!!		un mensaje m�s adecuado].
		!!	2:	Error, el usuario intenta poner un objeto sobre s� mismo.
		!!	3:	Error, el usuario intenta poner el objeto sobre otro que no
		!!		tiene el atributo "supporter".
		!!	4:	Error, el usuario intenta poner un objeto sobre el propio
		!!		usuario.
		!!	5:	Aviso, el objeto es una prenda puesta. La librer�a va a
		!!		quit�rselo autom�ticamente antes de reintentar la acci�n PutOn.
		!!	6:	Error, se intenta poner el objeto sobre otro en el que ya no
		!!		queda sitio (el n�mero de objetos que caben en el soporte se
		!!		indica en su propiedad "capacity").
		!!	7:	Exito. Mensaje a mostrar para cada objeto puesto cuando se
		!!		ponen muchos (ej: PON TODO SOBRE LA MESA).
		!!	8:	Exito. Mensaje a mostrar cuando se pone un objeto sobre otro.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�amos que ", (coge)"r", (lo) x1,
								" y no sabemos si se dejar�", (n) x1, ".";
							"Antes tendr�a que ", (coge)"r", (lo) x1,
							" y no s� si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitamos";
							else print "Necesito";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�ais que ", (coge)"r", (lo) x1,
								" y no sab�is si se dejar�", (n) x1, ".";
							"Antes tendr�as que ", (coge)"r", (lo) x1,
							" y no sabes si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesit�is";
							else print "Necesitas";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_PRESENT:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�an que ", (coge)"r", (lo) x1,
								" y no saben si se dejar�", (n) x1, ".";
							"Antes tendr�a que ", (coge)"r", (lo) x1,
							" y no sabe si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitan";
							else print "Necesita";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					FIRST_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�amos que ", (coge)"r", (lo) x1,
								" y no sab�amos si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�a que ", (coge)"r", (lo) x1,
							" y no sab�a si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesit�bamos";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					SECOND_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�ais que ", (coge)"r", (lo) x1,
								" y no sab�ais si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�as que ", (coge)"r", (lo) x1,
							" y no sab�as si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitabais";
							else print "Necesitabas";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					THIRD_PERSON_PAST:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes ten�an que ", (coge)"r", (lo) x1,
								" y no sab�an si se hubiese", (n) x1,
								" dejado.";
							"Antes ten�a que ", (coge)"r", (lo) x1,
							" y no sab�a si se hubiese", (n) x1, " dejado.";
						} else {
							if (IsPluralNoun(player)) print "Necesitaban";
							else print "Necesitaba";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde fuese.";
						}
					FIRST_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendremos que ", (coge)"r", (lo) x1,
								" y no sabremos si se dejar�", (n) x1, ".";
							"Antes tendr� que ", (coge)"r", (lo) x1,
							" y no sab?e si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitaremos";
							else print "Necesitar�";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					SECOND_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�is que ", (coge)"r", (lo) x1,
								" y no sabr�is si se dejar�", (n) x1, ".";
							"Antes tendr�s que ", (coge)"r", (lo) x1,
							" y no sabr�s si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitar�is";
							else print "Necesitar�s";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
					THIRD_PERSON_FUTURE:
						if (x1 has animate) {
							if (IsPluralNoun(player))
								"Antes tendr�n que ", (coge)"r", (lo) x1,
								" y no sabr�n si se dejar�", (n) x1, ".";
							"Antes tendr� que ", (coge)"r", (lo) x1,
							" y no sabr� si se dejar�", (n) x1, ".";
						} else {
							if (IsPluralNoun(player)) print "Necesitar�n";
							else print "Necesitar�";
							" tener ", (the) x1, " para poder poner", (lo) x1,
							" donde sea.";
						}
				}
			2:	"No ", (lm_puedes_) player, " poner un objeto sobre s� mismo.";
			3:	print "Poner cosas sobre ", (the) x1, " no ";
				switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print "servir�";
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print "hubiese servido";
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print "servir�";
				}
				" de nada.";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) "Nos falta";
						else print "Me falta";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) "Os falta";
						else print "Te falta";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Les falta";
						else print "Le falta";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos faltaba";
						else print "Me faltaba";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os faltaba";
						else print "Te faltaba";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Les faltaba";
						else print "Le faltaba";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos faltar�";
						else print "Me faltar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os faltar�";
						else print "Te faltar�";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Les faltar�";
						else print "Le faltar�";
				}
				" destreza.";
			5:	"(Primero ", (lm_te) player, " ", (lo) x1, "quit",
				(lm_as_) player, ").^";
			6:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "queda";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "quedaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "quedar�";
				}
				" sitio en ", (the) x1, " para poner nada m�s.";
			7:	"Hecho.";
			8:	if ((_grammatical_inflection == FIRST_PERSON_PAST)
			 		&& (~~IsPluralNoun(player))) print "Coloqu�";
				else print "Coloc", (lm_as_) player;
				" ", (the) x1, " sobre ", (the) second, ".";
		}

	Quit:
		!!	1:	Respuesta al comando FIN.
		!!	2:	Respuesta si el usuario escribe algo distinto de "si" o "no".
		switch (n) {
			1:
				print "[Por favor, responde SI o NO]: ";
			2:
				print "[�Realmente quieres abandonar el relato?] ";
		}
		return true;

	Remove:
		!!	1:	El recipiente que contiene el objeto que el usuario quiere
		!!		sacar, est� cerrado. (x1 apunta al objeto, no al recipiente,
		!!		el cu�l puede obtenerse con parent(x1)).
		!!	2:	El objeto no est� dentro del recipiente que el usuario ha dicho.
		!!	3:	�xito.
		switch (n) {
			1:	print "Por desgracia ", (the) parent(x1);
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print " est�", (n) parent(x1);
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print " estaba", (n) parent(x1);
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print " estar�", (n) parent(x1);
				}
				" cerrad", (o) parent(x1), ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						if (second has animate)
							"�Pero si no ", (lo) x1, " tiene", (n) second,"!";
						"�Pero si no est�", (n) x1, " ah� ahora!";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						if (second has animate)
							"�Pero si no ", (lo) x1, " ten�a", (n) second,"!";
						"�Pero si no estaba", (n) x1, " ah� en aquel momento!";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						if (second has animate)
							"�Pero si no ", (lo) x1, " tendr�", (n) second, "!";
						"�Pero si no estar�", (n) x1, " ah� en ese momento!";
				}
			3:	if (verb_word == 'quita') "Quitad", (o) x1, ".";
				"Sacad", (o) x1, ".";
		}

	Restart:
		!!	1:	Respuesta al comando REINICIAR.
		!!	2:	Si no se puede reiniciar.
		switch (n) {
			1:	print "[�Realmente quieres reiniciar el relato?]";
			2:	"[Error al reiniciar la partida].";
		}

	Restore:
		!!	1:	Si no se pudo cargar la partida con LOAD.
		!!	2:	�xito (no llega a mostrarse, porque en caso de �xito el estado
		!!		del juego cambia al momento en que se salv�. El "Ok" que se ve
		!!		entonces es el del comando Salvar.
		switch (n) {
			1:	"[Error. No se pudo recuperar la partida].";
			2:	print "[Partida cargada].";
				new_line;
				new_line;
				<<Look>>;
		}

	Rub:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Ya est�", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Ya estaba", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Ya estar�", (n) x1;
		}
		" bastante limpi", (o) x1, ".";

	Save:
		!!	1:	Si no se pudo guardar el juego.
		!!	2:	�xito.
		switch (n) {
			1:	"[Error. No se pudo guardar la partida].";
			2:	"[Partida guardada].";
		}

	Score:
		!! Puntuaci�n del juego. Puede activarse porque el usuario lo pide
		!! (con el verbo "PUNTUACION") o porque el juego ha terminado. En
		!! este ultimo caso, la variable "deadflag" valdr� true.
		switch (n) {
			1:
				if (deadflag) print "[En este juego, tu puntuaci�n ha sido ";
				else print "[Hasta el momento tu puntuaci�n es ";
				print score, " de un total de ", MAX_SCORE,
				", en ", turns, " turno";
				if (turns>1) print "s";
				print "].";
				new_line;
				return;
			2:	"[Este relato no tiene conteo de puntuaci�n].";
		}

	ScriptOff:
		!!	1:	Error ya estaba desactivada la transcrcipci�n.
		!!	2:	�xito.
		switch (n) {
			1:	"[La transcripci�n ya estaba desactivada].";
			2:	new_line; "[Fin de la transcripci�n].";
			3:	"[Intento fallido de finalizaci�n de transcripci�n].";
		}

	ScriptOn:
		!!	1:	Error, ya estaba activada la transcrcipci�n.
		!!	2:	�xito (parte inicial del mensaje, la librer�a a�ade el t�tulo
		!!		del juego obtenido de la constante Historia).
		switch (n) {
			1:	"[La transcripci�n ya estaba activada].";
			2:	"[Iniciando la transcripci�n de]:";
			3:	"[Intento fallido de comienzo de la transcripci�n].";
		}

	Search:
		!! La acci�n Search se genera ante la frase MIRA EN RECIPIENTE, MIRA EN
		!! SOPORTE, REGISTRA OBJETO.
		!!
		!!	1:	Error, estamos a oscuras.
		!!	2:	�xito examinando soporte, pero no hay nada sobre �l.
		!!	3:	�xito examinando soporte, listar lo que hay.
		!!	4:	El objeto examinado no es soporte ni recipiente, mensaje
		!!		est�ndar indicando que no se encuentra nada.
		!!	5:	Error, El objeto examinado es recipiente, pero est� cerrado.
		!!	6:	�xito, el objeto examinado es recipiente abierto, pero no
		!!		tiene nada dentro.
		!!	7:	�xito, el objeto examinado es recipiente abierto y tiene
		!!		cosas dentro. Se las lista.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Est�";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Estaba";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Estar�";
				}
				" demasiado oscuro como para ver algo.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "hay";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "hab�a";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "habr�";
				}
				" nada sobre ", (the) x1, ".";
			3:

			3:	print "Sobre ", (the) x1;
				WriteListFrom(child(x1),
					ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT + ISARE_BIT);
				".";
			4:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encontramos";
						else print "encuentro";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encontr�is";
						else print "encuentras";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "encuentran";
						else print "encuentra";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontramos";
						else print "encontr�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontrasteis";
						else print "encontraste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "encontraron";
						else print "encontr�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontraremos";
						else print "encontrar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontrar�is";
						else print "encontrar�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "encontrar�n";
						else print "encontrar�";
				}
				" nada interesante.";
			5:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "podemos";
						else print "puedo";
						" ver lo que hay dentro ", (del_) x1, " porque
						est�", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "pod�is";
						else print "puedes";
						" ver lo que hay dentro ", (del_) x1, " porque
						est�", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "pueden";
						else print "puede";
						" ver lo que hay dentro ", (del_) x1, " porque
						est�", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "pod�amos";
						else print "pod�a";
						" ver lo que hab�a dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "pod�ais";
						else print "pod�as";
						" ver lo que hab�a dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "pod�an";
						else print "pod�a";
						" ver lo que hab�a dentro ", (del_) x1, " porque
						estaba", (n) x1, " cerrad", (o) x1, ".";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podremos";
						else print "podr�";
						" ver lo que haya dentro ", (del_) x1, " porque
						estar�", (n) x1, " cerrad", (o) x1, ".";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podr�is";
						else print "podr�s";
						" ver lo que haya dentro ", (del_) x1, " porque
						estar�", (n) x1, " cerrad", (o) x1, ".";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "podr�n";
						else print "podr�";
						" ver lo que haya dentro ", (del_) x1, " porque
						estar�", (n) x1, " cerrad", (o) x1, ".";
				}
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " estar�", (n) x1;
				}
				" vac�", (o) x1, ".";
			7:	print "En ", (the) x1;
				WriteListFrom(child(x1),
					TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT);
				".";
		}

	Set:
		!! Set sale ante la frase FIJA OBJETO o AJUSTA OBJETO
		"No, no ", (lm_puedes) player, ".";

	SetTo:
		!! SetTo sale ante la frase AJUSTA DIAL A 23 o FIJA CONTROL EN
		!! ACTIVADO, o PON REGULADOR A 30
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Eso no puede";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Aquello no pod�a";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Eso no podr�";
		}
		" regularse a ning�n valor.";

	Show:
		!!	1:	Error, el usuario intenta mostrar un objeto que no tiene.
		!!	2:	Aviso, se ha enviado la acci�n Show al PNJ, pero este no ha
		!!		respondido. En este caso x1 apunta al PNJ y no al objeto que
		!!		le hemos mostrado.
		switch (n) {
			1:	"No ", (lm_tienes) player, " ", (the) x1, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " no muestra", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " no mostraba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " no mostrar�", (n) x1;
				}
				" ning�n inter�s.";
		}

	Sing:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cantamos";
				else print "Canto";
				" bastante mal.";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cant�is";
				else print "Cantas";
				" bastante mal.";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Cantan";
				else print "Canta";
				" bastante mal.";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cant�bamos";
				else print "Cantaba";
				" fatal.";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cant�bais";
				else print "Cantabas";
				" fatal.";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "Cantaban";
				else print "Cantaban";
				" fatal.";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegaremos";
				else print "Nunca llegar�";
				" a cantar especialmente bien.";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegar�is";
				else print "Nunca llegar�s";
				" a cantar especialmente bien.";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nunca llegar�n";
				else print "Nunca llegar�";
				" a cantar especialmente bien.";
			}

	Sleep:
		"No ", (lm_estas) player, " especialmente somnolient", (o) player, ".";

	Smell:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "olemos";
				else print "huelo";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "ol�is";
				else print "hueles";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "huelen";
				else print "huele";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "ol�amos";
				else print "ol�a";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "ol�ais";
				else print "ol�as";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "ol�an";
				else print "ol�a";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "oleremos";
				else print "oler�";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "oler�is";
				else print "oler�s";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "oler�n";
				else print "oler�";
			}
			" nada extra�o.";

	Sorry:
		!! Esta acci�n se genera si el usuario introduce "LO SIENTO",
		!! "PERDONA" o cosas similares.
		"[Oh, no es necesario que te disculpes].";

	Squeeze:
		!!	1:	Tratar de retorcer un ser animado.
		!!	2:	Cualquier otro objeto.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						print "No ";
						if (IsPluralNoun(player)) "creemos que debamos.";
						else "creo que deba";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "cre�is que deb�is.";
						else "crees que debas.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) "creen que deban.";
						else "cree que deba.";
					FIRST_PERSON_PAST:
						print "No ";
						if (IsPluralNoun(player))
							print "se nos hubiese ocurrido";
						else print "se me hubiese ocurrido";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player))
							print "se os hubiese ocurrido";
						else print "se te hubiese ocurrido";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player))
							print "se les hubiese ocurrido";
						else print "se le hubiese ocurrido";
					FIRST_PERSON_FUTURE:
						print "No ";
						if (IsPluralNoun(player)) print "se nos ocurrir�";
						else print "se me ocurrir�";
					SECOND_PERSON_FUTURE:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "se os ocurrir�";
						else print "se te ocurrir�";
					THIRD_PERSON_FUTURE:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "se les ocurrir�";
						else print "se le ocurrir�";
				}
				" hacer algo as�.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "conseguimos";
						else print "consigo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "consegu�s";
						else print "consigues";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "consiguen";
						else print "consigue";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "conseguimos";
						else print "consegu�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "conseguisteis";
						else print "conseguiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "consiguieron";
						else print "consigui�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguiremos";
						else print "conseguir�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguir�is";
						else print "conseguir�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "conseguir�n";
						else print "conseguir�";
				}
				" nada haciendo eso.";
		}

	Strong:
		!! Respuesta si se usa como primera palabra alg�n taco.
		!! TODO - Cambiar por un mensaje m�s apropiado (�recomendar AYUDA?)
		print "[Los verdaderos aventureros no ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "usan";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "usaban";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "usar�n";
		}
		" ese vocabulario].";

	Swim:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "ser�";
		}
		" un sitio apropiado para ponerse a nadar.";

	Swing:
		print "No ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "parece", (n) x1;
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "parec�a", (n) x1;
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "parecer�", (n) x1;
		}
		" el lugar m�s adecuado en el que columpiar", (lm_te) player, ".";

	SwitchOff:
		!!	1:	Error, el objeto no tiene el atributo "switchable".
		!!	2:	Error, el objeto ya tenia desactivado el atributo "on".
		!!	3:	�xito, el objeto tiene ahora desactivado "on".
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda apagarse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese apagar.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No ser� algo que pueda apagarse.";
				}
			2:	print "Ya ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "estaba", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estar�", (n) x1;
				}
				" apagad", (o) x1, ".";
			3:	if (_grammatical_inflection == FIRST_PERSON_PAST
					&& ~~IsPluralNoun(player)) "Apagu� ", (the) x1, ".";
				"Apag", (lm_as_) player, " ", (the) x1, ".";
		}

	SwitchOn:
		!! Generada al intentar ENCIENDE OBJETO si el objeto tiene el
		!! atributo "conmutable". Observar que si no lo tiene, la acci�n
		!! que se genera ser� sin embargo Quemar.
		!!	1:	Error, el objeto no es conmutable (este error no aparecer�
		!!		si el usuario pone ENCIENDE OBJETO, ya que en este caso la
		!!		acci�n generada ser� Quemar objeto, pero puede aparecer si
		!!		pone CONECTA OBJETO).
		!!	2:	Error, el objeto ya ten�a el atributo "on".
		!!	3:	�xito, el objeto tiene ahora activado "on".
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						"No es algo que pueda encenderse.";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						"No era algo que se pudiese encender.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No ser� algo que pueda encenderse.";
				}
			2:	print "Ya ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "estaba", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "estar�", (n) x1;
				}
				" encendid", (o) x1, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Encendemos";
						else print "Enciendo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Encend�is";
						else print "Enciendes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Encienden";
						else print "Enciendes";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendimos";
						else print "Encend�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendisteis";
						else print "Encendiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Encendieron";
						else print "Encendi�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encenderemos";
						else print "Encender�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encender�is";
						else print "Encender�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Encender�n";
						else print "Encender�";
				}
				" ", (the) x1, ".";
		}

	Take:
		!! Hay 13 casos diferentes. Se trata de 1 mensaje de �xito y 11
		!! mensajes de error y un aviso:
		!!	1:	�xito.
		!!	2:	Error, el objeto cogido es el propio usuario.
		!!	3:	Error, el objeto cogido es un objeto animado.
		!!	4:	Error, el usuario est� subido o metido en el objeto que intenta
		!!		coger.
		!!	5:	Error, el usuario ya ten�a ese objeto en su inventario.
		!!	6:	Error, el objeto est� en poder de un ser animado [x1 apunta
		!!		al ser, no al objeto, el cual puede obtenerse en la variable
		!!		"noun"].
		!!	7:	Error, el objeto es un sub-objeto de otro (est� dentro de un
		!!		objeto que tiene el atributo "transparent", pero no tiene el
		!!		atributo "container" ni "supporter").
		!!	8:	Error, el objeto est� dentro de otro, pero este otro no tiene
		!!		el atributo "container" ni "supporter" ni "transparent"
		!!		(probablemente un error de programaci�n).
		!!	9:	Error, el objeto est� dentro de un recipiente cerrado.
		!!	10:	Error, el objeto tiene el atributo "scenery".
		!!	11:	Error, el objeto tiene el atributo "static".
		!!	12:	Error, el usuario lleva demasiados objetos.
		!!	13: Mensaje de aviso, la librer�a ha decidido mover objetos del
		!!		inventario al "objeto saco" para hacer sitio y que el usuario
		!!		pueda coger el objeto. [El objeto saco es uno que puede
		!!		declarar el programador. Si el usuario lo coge y lo lleva
		!!		consigo, la librer�a lo usar� autom�ticamente como mochila
		!!		para descargar al usuario cuando sea necesario].
		switch (n) {
			1:	if (dialecto_sudamericano) print "Tomad";
				else print "Cogid";
				"", (o) noun, ".";
			2:	"Siempre ", (lm_te) player, " ", (lm_tienes) player, " a ",
				(string) YOURSELF__TX, ".";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�is";
						else print "crees";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No cre�amos";
						else print "No cre�a";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�ais";
						else print "cre�as";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�an";
						else print "cre�a";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeremos";
						else print "No lo creer�";
						" buena idea.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creer�is";
						else print "No lo creer�s";
						" buena idea.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creer�n";
						else print "No lo creer�";
						" buena idea.";
				}
			4:	print (lm_ttienes) player, " que ";
				if (x1 has supporter) print "bajar", (lm_te) player;
				else print "salir";
				"", (del_) x1, " antes.";
			5:	"Ya ", (lm_tienes) player, " ", (the) x1, ".";
			6:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Parece", (n) noun;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Parec�a", (n) noun;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Parecer�", (n) noun;
				}
				" pertenecer ", (al_) x1, ".";
			7:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "Parece", (n) noun;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "Parec�a", (n) noun;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "Parecer�", (n) noun;
				}
				" formar parte ", (del_) x1, ".";
			8:	print "No ";
				switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print "est�", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print "estaba", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print "estar�", (n) x1;
					}
					" disponible", (s) x1, ".";
			9:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " no est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " no estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " no estar�", (n) x1;
				}
				" abiert", (o) x1, ".";
			10:	print "Dif�cilmente ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podr�amos llevarnos eso.";
						"podr�a llevarme eso.";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podr�ais llevaros eso.";
						"podr�as llevarte eso.";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) "podr�an llevarse eso.";
						"podr�a llevarse eso.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubi�semos podido llevarnos aquello.";
						"hubiese podido llevarme aquello.";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubi�seis podido llevaros aquello.";
						"hubieses podido llevarte aquello.";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player))
							"hubiesen podido llevarse aquello.";
						"hubiese podido llevarse aquello.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podremos llevarnos eso.";
						"podr� llevarme eso.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podr�is llevaros eso.";
						"podr�s llevarte eso.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) "podr�n llevarse eso.";
						"podr� llevarse eso.";
				}
			11:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " est�", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, "estaba", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, "estar�", (n) x1;
				}
				" fij", (o) x1, " en el sitio.";
			12:	"Ya ", (lm_tienes) player, " las manos ocupadas con demasiadas
				cosas.";
			13:	print "(Primero ";
				if (_grammatical_inflection == FIRST_PERSON_PAST
					&& ~~IsPluralNoun(player)) print "coloqu�";
				else print "coloc", (lm_as_) player;
				" ", (the) x1, " en ", (the) SACK_OBJECT, " para hacer sitio).";
		}

	Taste:
		"No sabore", (lm_as_) player, " nada inesperado.";

	Tell:
		!!	1:	El usuario habla consigo mismo.
		!!	2:	Hablar con cualquier otro ser animado.
		!! [Nota: Hablar con un objeto inanimado no est� permitido por el
		!! parser, que da un error y no llega a generar la acci�n.]
		!! [Los errores de parser se tratan en la secci�n "Miscel�nea" de
		!! esta rutina, al final.]
		switch (n) {
			1:	"Habl", (lm_as_) player, " sol", (o) player," durante un rato.";
			2:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "hemos provocado";
						else print "he provocado";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "hab�is provocado";
						else print "has provocado";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "han provocado";
						else print "ha provocado";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocamos";
						else print "provoqu�";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocasteis";
						else print "provocaste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "provocaron";
						else print "provoc�";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocaremos";
						else print "provocar�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocar�is";
						else print "provocar�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "provocar�n";
						else print "provocar�";
				}
				" ninguna reacci�n.";
		}

	Think:
		"Si, eso intent", (lm_as) player, ".";

	ThrowAt:
		!!  1:	Lanzar cosas a objetos inanimados.
		!!	2:	Lanzar cosas a objetos animados.
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "servir�a";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "hubiese servido";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "servir�";
				}
				" de nada.";
			2:	"En el �ltimo momento ", (lm_te) player, " ech",
				(lm_as_) player, " atr�s.";
		}

!!	Tie: see JumpOver

	Touch:
		!!	1:	Si se intenta tocar a un ser animado.
		!!	2:	Tocar un objeto normal del juego.
		!!	3:	Tocarse a si mismo.
		switch (n) {
			1:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�is";
						else print "crees";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que ", (al_) x1, " le", (s) x1, " gustara.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No cre�amos";
						else print "No cre�a";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�ais";
						else print "cre�as";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�an";
						else print "cre�a";
						" que ", (al_) x1, " le", (s) x1, " hubiese gustado.";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creeremos";
						else print "No lo creer�";
						" buena idea.";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creer�is";
						else print "No lo creer�s";
						" buena idea.";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "No lo creer�n";
						else print "No lo creer�";
						" buena idea.";
				}
			2:	"No not", (lm_as_) player, " nada extra�o al tacto.";
			3:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "No creemos";
						else print "No creo";
						" que eso sirva de nada.";
					SECOND_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�is";
						else print "crees";
						" que eso sirva de nada.";
					THIRD_PERSON_PRESENT:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "creen";
						else print "cree";
						" que eso sirva de nada.";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "No cre�amos";
						else print "No cre�a";
						" que algo as� hubiese servido de nada.";
					SECOND_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�ais";
						else print "cre�as";
						" que algo as� hubiese servido de nada.";
					THIRD_PERSON_PAST:
						print "En realidad no ";
						if (IsPluralNoun(player)) print "cre�an";
						else print "cre�a";
						" que algo as� hubiese servido de nada.";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						"No ser� un buen momento para andar toc�ndo",
						(lm_te) player, ".";
				}
    	}

!!	Turn:	see Pull

	Unlock:
		!! Unlock se genera ante ABRE <objeto> CON <objeto2>, o tambi�n
		!! ante QUITA CERROJO A <objeto> (en este segundo caso no se
		!! especifica la "llave" que abre la puerta).
		!!
		!!	1:	Error, el objeto que se intenta abrir, no tiene el atributo
		!!		cerrojo.
		!!	2:	Error, el objeto que se intenta abrir tiene atributo "cerrojo",
		!!		pero no tiene atributo "cerrojoechado".
		!!	3:	Error, el <objeto2> que se intenta usar como llave, no coincide
		!!		con la propiedad "con_llave" del <objeto> que intenta ser
		!!		abierto.
		!!	4:	�xito. El <objeto> se abre (con <objeto2> si �ste ha sido
		!!		especificado, el cual podemos encontrarlo en la variable "otro".
		switch (n) {
			1:	print "No ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "parece", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "parec�a", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "parecer�", (n) x1;
				}
				" tener ning�n tipo de cerrojo.";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print (The) x1, " ya ten�a", (n) x1;
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print (The) x1, " ya ten�a", (n) x1;
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print (The) x1, " ya tendr�", (n) x1;
				}
				" abierto el cerrojo.";
			3:	if (second) {
					print "No ";
					switch (_grammatical_inflection) {
						FIRST_PERSON_PRESENT,
						SECOND_PERSON_PRESENT,
						THIRD_PERSON_PRESENT:
							print "parece", (n) x1;
						FIRST_PERSON_PAST,
						SECOND_PERSON_PAST,
						THIRD_PERSON_PAST:
							print "parec�a", (n) x1;
						FIRST_PERSON_FUTURE,
						SECOND_PERSON_FUTURE,
						THIRD_PERSON_FUTURE:
							print "parecer�", (n) x1;
					}
					" encajar en la cerradura.";
				} else "Necesit", (lm_as) player, " alg�n tipo de llave.";
			4:	print "Quit", (lm_as_) player, " el cerrojo ", (al_) x1;
				if (second) " con ", (the) second, ".";
				".";
		}

	VagueGo:
		!! El usuario ha dicho IR sin especificar a d�nde
		"[Tienes que especificar en qu� direcci�n ir].";

	Verify:
		!!	1:	�xito.
		!!	2:	Error en la verificaci�n.
		switch (n) {
			1:	"[Fichero de juego verificado e intacto].";
			2:	"[El fichero de juego no parece intacto,
				puede estar corrompido (a menos que est�s jugando con un
				int�rprete muy primitivo que no sea capaz de realizar la
				comprobaci�n)].";
		}

	Wait:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "Pasa";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "Pasaba";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "Pasar�";
		}
		" el tiempo...";

	Wake:
		print "La cruda realidad es que ";
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				print "esto no es";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				print "aquello no era";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				print "eso no ser�";
		}
		" un sue�o.";

	WakeOther:
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT,
			SECOND_PERSON_PRESENT,
			THIRD_PERSON_PRESENT:
				"No parece necesario hacer eso.";
			FIRST_PERSON_PAST,
			SECOND_PERSON_PAST,
			THIRD_PERSON_PAST:
				"No parec�a necesario hacer aquello.";
			FIRST_PERSON_FUTURE,
			SECOND_PERSON_FUTURE,
			THIRD_PERSON_FUTURE:
				"No parecer� necesario hacer eso.";
		}

	Wave:
		!!	1:	Si se intenta agitar un objeto que no est� en el inventario.
		!!	2:	Si se agita un objeto que s� est� en el inventario.
		switch (n) {
			1:	"No l", (o) x1, " ", (lm_tienes) player, ".";
			2:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos sentimos";
						else print "Me siento";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os sent�s";
						else print "Te sientes";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se sienten";
						else print "Se siente";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos sent�amos";
						else print "Me sent�a";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os sent�ais";
						else print "Te sent�as";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se sent�an";
						else print "Se sent�a";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos sentiremos";
						else print "Me sentir�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os sentir�is";
						else print "Te sentir�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se sentir�n";
						else print "Se sentir�";
				}
				" rid�cul", (o) player, " agitando ", (the) x1, ".";
		}

	WaveHands:
		!! La acci�n WaveHands se genera ante las frases "gesticula", "agita la
		!! mano", "sacude la mano", "saluda con la mano", etc.
		switch (_grammatical_inflection) {
			FIRST_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Nos encontramos";
				else print "Me encuentro";
			SECOND_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Os encontr�is";
				else print "Te encuentras";
			THIRD_PERSON_PRESENT:
				if (IsPluralNoun(player)) print "Se encuentran";
				else print "Se encuentra";
			FIRST_PERSON_PAST:
				if (IsPluralNoun(player)) print "Nos encontr�bamos";
				else print "Me encontraba";
			SECOND_PERSON_PAST:
				if (IsPluralNoun(player)) print "Os encontr�bais";
				else print "Te encontrabas";
			THIRD_PERSON_PAST:
				if (IsPluralNoun(player)) print "Se encontraban";
				else print "Se encontraba";
			FIRST_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Nos encontraremos";
				else print "Me encontrar�";
			SECOND_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Os encontrar�is";
				else print "Te encontrar�s";
			THIRD_PERSON_FUTURE:
				if (IsPluralNoun(player)) print "Se encontrar�n";
				else print "Se encontrar�";
		}
		" rid�cul", (o) player, " gesticulando as�.";

	Wear:
		!! 1: Error, el objeto no tiene el atributo "clothing".
		!! 2: Error, el usuario no tiene el objeto.
		!! 3: Error, el objeto ya tiene el atributo "worn".
		!! 4: �xito.
		switch (n) {
			1:	print "No ", (lm_puedes) player, " poner", (lm_te) player, " ";
				switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT,
					SECOND_PERSON_PRESENT,
					THIRD_PERSON_PRESENT:
						print "eso";
					FIRST_PERSON_PAST,
					SECOND_PERSON_PAST,
					THIRD_PERSON_PAST:
						print "aquello";
					FIRST_PERSON_FUTURE,
					SECOND_PERSON_FUTURE,
					THIRD_PERSON_FUTURE:
						print "eso";
				}
				".";
			2:	"No ", (lo) x1, " ", (lm_tienes) player, ".";
			3:	"Ya ", (lo) x1, " llev", (lm_as) player, " puest", (o) x1, ".";
			4:	switch (_grammatical_inflection) {
					FIRST_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Nos ponemos";
						else print "Me pongo";
					SECOND_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Os pon�is";
						else print "Te pones";
					THIRD_PERSON_PRESENT:
						if (IsPluralNoun(player)) print "Se ponen";
						else print "Se pone";
					FIRST_PERSON_PAST:
						if (IsPluralNoun(player)) print "Nos pusimos";
						else print "Me puse";
					SECOND_PERSON_PAST:
						if (IsPluralNoun(player)) print "Os pusisteis";
						else print "Te pusiste";
					THIRD_PERSON_PAST:
						if (IsPluralNoun(player)) print "Se pusieron";
						else print "Se puso";
					FIRST_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Nos pondremos";
						else print "Me pondr�";
					SECOND_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Os pondr�is";
						else print "Te pondr�s";
					THIRD_PERSON_FUTURE:
						if (IsPluralNoun(player)) print "Se pondr�n";
						else print "Se pondr�";
				}
				" ", (the) x1, ".";
		}

	Yes:
		"[La instrucci�n ~S�~ no tiene sentido en esta situaci�n].";

];
