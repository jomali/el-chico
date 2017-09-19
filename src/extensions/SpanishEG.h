

!!==============================================================================
!!
!!	GRAM�TICA ESPA�OLA EXTENDIDA
!!
!!==============================================================================
!!
!!	File:			SpanishEG.inf
!!	Author(s):		Emily Short <emshort@mindspring.com>
!!					J. Francisco Mart�n <jfm.lisaso@gmail.com>
!!					Mapache
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		M�quina-Z / GLULX
!!	Version:		5.1
!!	Released:		2017/08/04
!!
!!------------------------------------------------------------------------------
!!
!!	# NOTAS
!!
!!	Basada en "ExpertGrammar.h", de Emily Short <emshort@mindspring.com>
!!	y en su traducci�n al castellano "GramaticaExperta.h", de Mapache.
!!
!!
!!	# DERECHOS
!!
!!	Esta librer�a puede tratarse como de dominio p�blico. Puede incluirse
!!	con o sin citar al autor original. Puede ser modificada a discreci�n
!!	por el usuario. Se puede distribuir libremente. Pueden extraerse
!!	fragmentos de la librer�a.
!!
!!
!!	# INSTALACI�N
!!
!!	Incluye "SpanishEG.h" despu�s de SpanishG en tu archivo de juego.
!!
!!	Se puede definir la variable '_grammatical_inflection' en el archivo de
!!	juego, que puede tomar los valores: 1 (PRESENTE 1� PERSONA), 2 (PRESENTE 2�
!!	PERSONA), 3 (PRESENTE 3� PERSONA), 4 (PASADO 1� PERSONA), 5 (PASADO 2�
!!	PERSONA) o 6 (PASADO 3� PERSONA) para modificar la conjugaci�n gramatical
!!	de los mensajes de la librer�a. Si no se define ninguna
!!	'_grammatical_inflection', la librer�a interpreta que se usa el valor 2:
!!	los mensajes de "SpanishEG.h" se imprimen en presente y segunda persona.
!!
!!
!!	# NUEVAS ACCIONES
!!
!!	 -	Dance
!!	 -	GoDown
!!	 -	GoUp
!!	 -	KnockOn
!!	 -	Masturbate
!!	 -	Read
!!	 -	Shout
!!	 -	Sit
!!	 -	SleepWith
!!	 -	StandUp
!!	 -	Untie
!!	 -	Use
!!	 -	Write
!!	 -	Xyzzy
!!
!!------------------------------------------------------------------------------

!!------------------------------------------------------------------------------
!! Valores de la extensi�n por defecto
!!------------------------------------------------------------------------------

Default	FIRST_PERSON_PRESENT 1;
Default	SECOND_PERSON_PRESENT 2;
Default THIRD_PERSON_PRESENT 3;
Default FIRST_PERSON_PAST 4;
Default SECOND_PERSON_PAST 5;
Default THIRD_PERSON_PAST 6;
Default FIRST_PERSON_FUTURE 7;
Default SECOND_PERSON_FUTURE 8;
Default THIRD_PERSON_FUTURE 9;

Default	_grammatical_inflection 2;

!!------------------------------------------------------------------------------
!! Nuevos sin�nimos
!!------------------------------------------------------------------------------

Verb	'machaca'						= 'ataca';
Verb	'silba' 'tararea' 'tatarea'		= 'canta';
Verb	'roba' 'agarra'					= 'coge';
Verb	'talla' 'esculpe'				= 'corta';
Verb	'emplaza' 'deposita' 'abandona'	= 'deja';
Verb	'berrea' 'aulla'				= 'grita';
Verb	'marcha'						= 'ir';
Verb	'incinera' 'tuesta'				= 'quema';
VerboIrregular "tostar" with imperativo 'tuesta';
Verb	'acaricia'						= 'toca';

!!------------------------------------------------------------------------------
!! Extensiones a las acciones de la librer�a por defecto
!!------------------------------------------------------------------------------

Extend	'sopla'
	* 'sobre' / 'dentro' / 'a' noun	-> Blow
	* 'a' 'traves' 'de' noun		-> Blow
;

Extend	'prende' last
	* 'fuego' noun					-> Burn
	* noun 'fuego'					-> Burn
	* 'fuego' 'a//' noun			-> Burn
	* 'a//' noun 'fuego'			-> Burn
	* 'fuego' noun 'con' held		-> Burn
	* noun 'fuego' 'con' held		-> Burn
	* 'fuego' 'a//' noun 'con' held	-> Burn
	* 'a//' noun 'fuego' 'con' held	-> Burn
;

Verb	'muerde'
	* noun							-> Eat
	* edible						-> Eat
!	* animate						-> Attack
!	* 'a' animate					-> Attack
; VerboIrregular "morder" with imperativo 'muerde';

Extend	'salta'
	* 'en' noun						-> JumpOver
;

Extend	'mira'
	* 'alrededor'					-> Look
	* 'a' 'mi'/'tu' 'alrededor'		-> Look
	* 'a' 'nuestro' 'alrededor'		-> Look
	* 'a' 'vuestro' 'alrededor'		-> Look
	* 'a' 'su' 'alrededor'			-> Look
;

Extend	'busca'
	* 'bajo' noun					-> LookUnder
	* 'debajo' 'de' noun			-> LookUnder
	* 'entre' noun					-> Search
;

Extend	'mira'
	* 'entre' noun					-> Search
;

Extend	'duerme'
	* '-te'/'-me'					-> Sleep
	* noun							-> Sleep
	* '-te'/'-me' noun				-> Sleep
	* 'en' noun						-> Sleep
	* '-te'/'-me' 'en' noun			-> Sleep
;

Verb	meta 'creditos' 'credits' 'autor' 'author' 'informacion' 'info'
	*								-> Version
;

!!------------------------------------------------------------------------------
!! ##Dance
!!------------------------------------------------------------------------------

Verb	'baila'
	*								-> Dance
;

[ DanceSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca he sido un gran bailar�n.";
				1, 7:
					"Nunca he sido una gran bailarina.";
				3, 9:
					"Nunca hemos sido unos grandes bailarines.";
				4, 10:
					"Nunca hemos sido unas grandes bailarinas.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca has sido un gran bailar�n.";
				1, 7:
					"Nunca has sido una gran bailarina.";
				3, 9:
					"Nunca hab�is sido unos grandes bailarines.";
				4, 10:
					"Nunca hab�is sido unas grandes bailarinas.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Nunca ha sido un gran bailar�n.";
				1, 7:
					"Nunca ha sido una gran bailarina.";
				3, 9:
					"Nunca han sido unos grandes bailarines.";
				4, 10:
					"Nunca han sido unas grandes bailarinas.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fui un gran bailar�n.";
				1, 7:
					"Nunca fui una gran bailarina.";
				3, 9:
					"Nunca fuimos unos grandes bailarines.";
				4, 10:
					"Nunca fuimos unas grandes bailarinas.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fuiste un gran bailar�n.";
				1, 7:
					"Nunca fuiste una gran bailarina.";
				3, 9:
					"Nunca fuisteis unos grandes bailarines.";
				4, 10:
					"Nunca fuisteis unas grandes bailarinas.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Nunca fue un gran bailar�n.";
				1, 7:
					"Nunca fue una gran bailarina.";
				3, 9:
					"Nunca fueron unos grandes bailarines.";
				4, 10:
					"Nunca fueron unas grandes bailarinas.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegar� a ser un gran bailar�n.";
				1, 7:
					"No llegar� a ser una gran bailarina.";
				3, 9:
					"No llegaremos a ser unos grandes bailarines.";
				4, 10:
					"No llegaremos a ser unas grandes bailarinas.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegar�s a ser un gran bailar�n.";
				1, 7:
					"No llegar�s a ser una gran bailarina.";
				3, 9:
					"No llegar�is a ser unos grandes bailarines.";
				4, 10:
					"No llegar�is a ser unas grandes bailarinas.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No llegar� a ser un gran bailar�n.";
				1, 7:
					"No llegar� a ser una gran bailarina.";
				3, 9:
					"No llegar�n a ser unos grandes bailarines.";
				4, 10:
					"No llegar�n a ser unas grandes bailarinas.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##GoDown, ##GoUp
!!------------------------------------------------------------------------------

Verb	'desciende'
	*								-> GoDown
	* noun							-> Enter
	* 'por' noun					-> Enter
; VerboIrregular "descender" with imperativo 'desciende';

Verb	'asciende'
	*								-> GoUp
	* noun							-> Enter
	* 'por' noun					-> Enter
; VerboIrregular "ascender" with imperativo 'asciende';

[ GoDownSub;
	<<Go d_obj>>;
];

[ GoUpSub;
	<<Go u_obj>>;
];

!!------------------------------------------------------------------------------
!! ##KnockOn
!!------------------------------------------------------------------------------

Extend only 'golpea' first
	* door							-> KnockOn
	* 'a' door						-> KnockOn
;

Verb	'llama'
	* door							-> KnockOn
	* 'a' door						-> KnockOn
	* animate						-> Tell
	* 'a' animate					-> Tell
;

[ KnockOnSub;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		SECOND_PERSON_PRESENT,
		THIRD_PERSON_PRESENT:
			if (noun has door) "No contesta nadie.";
			"No ocurre nada.";
		FIRST_PERSON_PAST,
		SECOND_PERSON_PAST,
		THIRD_PERSON_PAST:
			if (noun has door) "No contest� nadie.";
			"No ocurri� nada.";
		FIRST_PERSON_FUTURE,
		SECOND_PERSON_FUTURE,
		THIRD_PERSON_FUTURE:
			if (noun has door) "No contestar� nadie.";
			"No ocurrir� nada.";
	}
];

!!------------------------------------------------------------------------------
!! ##Masturbate
!!------------------------------------------------------------------------------

Verb	'masturba'
	* '-me'/'-te'					-> Masturbate
;

[ MasturbateSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tengo ganas.";
				3, 4, 9, 10:
					"Ahora no tenemos ganas.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tienes ganas en realidad.";
				3, 4, 9, 10:
					"Ahora no ten�is ganas en realidad.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tiene ganas.";
				3, 4, 9, 10:
					"Ahora no tienen ganas.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No ten�a ganas.";
				3, 4, 9, 10:
					"No ten�amos ganas.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No ten�as ganas.";
				3, 4, 9, 10:
					"No ten�ais ganas.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No ten�a ganas.";
				3, 4, 9, 10:
					"No ten�an ganas.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr� ganas.";
				3, 4, 9, 10:
					"No tendremos ganas.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr�s ganas.";
				3, 4, 9, 10:
					"No tendr�is ganas.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr� ganas.";
				3, 4, 9, 10:
					"No tendr�n ganas.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Read
!!------------------------------------------------------------------------------

Extend	'lee' first
	* noun							-> Read
;

[ ReadSub;
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT,
		SECOND_PERSON_PRESENT,
		THIRD_PERSON_PRESENT:
			"No hay nada que leer en ", (the) noun, ".";
		FIRST_PERSON_PAST,
		SECOND_PERSON_PAST,
		THIRD_PERSON_PAST:
			"No hab�a nada que leer en ", (the) noun, ".";
		FIRST_PERSON_FUTURE,
		SECOND_PERSON_FUTURE,
		THIRD_PERSON_FUTURE:
			"No habr� nada que leer en ", (the) noun, ".";
	}
];

!!------------------------------------------------------------------------------
!! ##Shout
!!------------------------------------------------------------------------------

Verb	'chilla'
	*								-> Shout
;

Extend	'grita' last
	*								-> Shout
;

[ ShoutSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Grito con fuerza.";
				3, 4, 9, 10:
					"Gritamos con fuerza.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Gritas con fuerza.";
				3, 4, 9, 10:
					"Gritais con fuerza.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Grita con fuerza.";
				3, 4, 9, 10:
					"Gritan con fuerza.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Grit� con fuerza.";
				3, 4, 9, 10:
					"Gritamos con fuerza.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Gritaste con fuerza.";
				3, 4, 9, 10:
					"Gritasteis con fuerza.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Grit� con fuerza.";
				3, 4, 9, 10:
					"Gritaron con fuerza.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritar� con fuerza.";
				3, 4, 9, 10:
					"Gritaremos con fuerza.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritar�s con fuerza.";
				3, 4, 9, 10:
					"Gritar�is con fuerza.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Gritar� con fuerza.";
				3, 4, 9, 10:
					"Gritar�n con fuerza.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Sit
!!------------------------------------------------------------------------------

Extend    'sienta' replace
    * 								-> Sit
	* '-te' / '-me'					-> Sit
	* noun							-> Sit
	* '-te' / '-me' noun			-> Sit
	* 'en' noun						-> Sit
	* '-te' / '-me'	'en' noun		-> Sit
; VerboIrregular "sentar" with imperativo 'sientate';

[ SitSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya estoy bastante c�modo de pie.";
				1, 7:
					"Ya estoy bastante c�moda de pie.";
				3, 9:
					"Ya estamos bastante c�modos de pie.";
				4, 10:
					"Ya estamos bastante c�modas de pie.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya est�s bastante c�modo de pie.";
				1, 7:
					"Ya est�s bastante c�moda de pie.";
				3, 9:
					"Ya est�is bastante c�modos de pie.";
				4, 10:
					"Ya est�is bastante c�modas de pie.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"Ya est� bastante c�modo de pie.";
				1, 7:
					"Ya est� bastante c�moda de pie.";
				3, 9:
					"Ya est�n bastante c�modos de pie.";
				4, 10:
					"Ya est�n bastante c�modas de pie.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estaba bastante c�modo de pie.";
				1, 7:
					"Ya estaba bastante c�moda de pie.";
				3, 9:
					"Ya est�bamos bastante c�modos de pie.";
				4, 10:
					"Ya est�bamos bastante c�modas de pie.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estabas bastante c�modo de pie.";
				1, 7:
					"Ya estabas bastante c�moda de pie.";
				3, 9:
					"Ya estabais bastante c�modos de pie.";
				4, 10:
					"Ya estabais bastante c�modas de pie.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"Ya estaba bastante c�modo de pie.";
				1, 7:
					"Ya estaba bastante c�moda de pie.";
				3, 9:
					"Ya estaban bastante c�modos de pie.";
				4, 10:
					"Ya estaban bastante c�modas de pie.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estar� bastante c�modo de pie.";
				1, 7:
					"Ya estar� bastante c�moda de pie.";
				3, 9:
					"Ya estaremos bastante c�modos de pie.";
				4, 10:
					"Ya estaremos bastante c�modas de pie.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estar�s bastante c�modo de pie.";
				1, 7:
					"Ya estar�s bastante c�moda de pie.";
				3, 9:
					"Ya estar�is bastante c�modos de pie.";
				4, 10:
					"Ya estar�is bastante c�modas de pie.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"Ya estar� bastante c�modo de pie.";
				1, 7:
					"Ya estar� bastante c�moda de pie.";
				3, 9:
					"Ya estar�n bastante c�modos de pie.";
				4, 10:
					"Ya estar�n bastante c�modas de pie.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##SleepWith
!!------------------------------------------------------------------------------

Verb	'folla' 'copula'
	* animate						-> SleepWith
	* '-te' / '-me' animate			-> SleepWith
	* 'a//' / 'con' animate			-> SleepWith
	* '-te' / '-me' 'a' animate		-> SleepWith
;

Extend	only 'jode' first
	* animate						-> SleepWith
	* 'a//' / 'con' animate			-> SleepWith
;

Verb	'ten'
	* 'sexo' 'con' animate			-> SleepWith
	* 'coito' 'con' animate			-> SleepWith
; VerboIrregular "tener" with imperativo 'ten';

Verb	'haz'
	* 'el' 'amor' 'con' animate		-> SleepWith
; VerboIrregular "hacer el amor" with imperativo 'haz';


[ SleepWithSub gna;
	if (noun == player) <<Masturbate>>;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se me pasa por la cabeza algo as� ahora.";
				3, 4, 9, 10:
					"Ni se nos pasa por la cabeza algo as� ahora.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"En realidad no se te pasar�a por la cabeza algo as�
					ahora.";
				3, 4, 9, 10:
					"En realidad no se os pasar�a por la cabeza algo as�
					ahora.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"En realidad no se le pasar�a por la cabeza algo as�
					ahora.";
				3, 4, 9, 10:
					"En realidad no se les pasar�a por la cabeza algo as�
					ahora.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se me hubiese pasado por la cabeza algo as� en aquel
					momento.";
				3, 4, 9, 10:
					"No se nos hubiese pasado por la cabeza algo as� en aquel
					momento.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se te hubiese pasado por la cabeza algo as� en aquel
					momento.";
				3, 4, 9, 10:
					"No se os hubiese pasado por la cabeza algo as� en aquel
					momento.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No se le hubiese pasado por la cabeza algo as� en aquel
					momento.";
				3, 4, 9, 10:
					"No se les hubiese pasado por la cabeza algo as� en aquel
					momento.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se me pasar� por la cabeza algo as� en ese momento.";
				3, 4, 9, 10:
					"Ni se nos pasar� por la cabeza algo as� en ese momento.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se te pasar� por la cabeza algo as� en ese momento.";
				3, 4, 9, 10:
					"Ni se os pasar� por la cabeza algo as� en ese momento.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Ni se le pasar� por la cabeza algo as� en ese momento.";
				3, 4, 9, 10:
					"Ni se les pasar� por la cabeza algo as� en ese momento.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##StandUp
!!------------------------------------------------------------------------------

Extend	only 'levantate' 'levantarse' 'levantarte' first
	*								-> StandUp
	* 'de' noun						-> StandUp
;

Verb    'levanta' 'incorpora'
    * 								-> StandUp
	* '-te'/'-me'					-> StandUp
    * 'de' noun 					-> StandUp
	* '-te'/'-me' 'de//' noun		-> StandUp
;

[ StandUpSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No estoy en ning�n sitio del que deba levantarme.";
				3, 4, 9, 10:
					"No estamos en ning�n sitio del que debamos levantarnos.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No est�s en ning�n sitio del que debas levantarte.";
				3, 4, 9, 10:
					"No est�is en ning�n sitio del que debais levantaros.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"No est� en ning�n sitio del que deba levantarse.";
				3, 4, 9, 10:
					"No est�n en ning�n sitio del que deban levantarse.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estaba en ning�n sitio del que debiese levantarme.";
				3, 4, 9, 10:
					"No est�bamos en ning�n sitio del que debi�semos
					levantarnos.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estabas en ning�n sitio del que debieses levantarte.";
				3, 4, 9, 10:
					"No estabais en ning�n sitio del que debieseis levantaros.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No estaba en ning�n sitio del que debiese levantarse.";
				3, 4, 9, 10:
					"No estaban en ning�n sitio del que debiesen levantarse.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estar� en ning�n sitio del que debiese
					levantarme.";
				3, 4, 9, 10:
					"No estaremos en ning�n sitio del que debi�semos
					levantarnos.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estar�s en ning�n sitio del que debieses
					levantarte.";
				3, 4, 9, 10:
					"No estar�is en ning�n sitio del que debi�sesis
					levantaros.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No estar� en ning�n sitio del que debiese
					levantarse.";
				3, 4, 9, 10:
					"No estar�n en ning�n sitio del que debiesen
					levantarse.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Untie
!!------------------------------------------------------------------------------

Verb	'desata' 'libera' 'desune' 'desenchufa'
	* noun							-> Untie
	* 'a//' creature				-> Untie
	* 'a//' creature 'de' noun		-> Untie
	* noun 'de' noun				-> Untie
;

Extend	only 'desconecta' last
	* noun 'de' noun				-> Untie
;

[ UntieSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No estoy seguro de c�mo hacerlo.";
				1, 7:
					"No estoy segura de c�mo hacerlo.";
				3, 9:
					"No estamos seguros de c�mo hacerlo.";
				4, 10:
					"No estamos seguras de c�mo hacerlo.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No est�s seguro de c�mo hacerlo.";
				1, 7:
					"No est�s segura de c�mo hacerlo.";
				3, 9:
					"No est�is seguros de c�mo hacerlo.";
				4, 10:
					"No est�is seguras de c�mo hacerlo.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 6:
					"No parece estar seguro de c�mo hacerlo.";
				1, 7:
					"No parece estar segura de c�mo hacerlo.";
				3, 9:
					"No parecen estar seguros de c�mo hacerlo.";
				4, 10:
					"No parecen estar seguras de c�mo hacerlo.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estaba seguro de c�mo hacer eso.";
				1, 7:
					"No estaba segura de c�mo hacer eso.";
				3, 9:
					"No est�bamos seguros de c�mo hacer eso.";
				4, 10:
					"No est�bamos seguras de c�mo hacer eso.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estabas seguro de c�mo hacer eso.";
				1, 7:
					"No estabas segura de c�mo hacer eso.";
				3, 9:
					"No estabais seguros de c�mo hacer eso.";
				4, 10:
					"No estabais seguras de c�mo hacer eso.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 6:
					"No estaba seguro de c�mo hacer eso.";
				1, 7:
					"No estaba segura de c�mo hacer eso.";
				3, 9:
					"No estaban seguros de c�mo hacer eso.";
				4, 10:
					"No estaban seguras de c�mo hacer eso.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estar� seguro de c�mo hacer eso.";
				1, 7:
					"No estar� segura de c�mo hacer eso.";
				3, 9:
					"No estaremos seguros de c�mo hacer eso.";
				4, 10:
					"No estaremos seguras de c�mo hacer eso.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estar�s seguro de c�mo hacer eso.";
				1, 7:
					"No estar�s segura de c�mo hacer eso.";
				3, 9:
					"No estar�is seguros de c�mo hacer eso.";
				4, 10:
					"No estar�is seguras de c�mo hacer eso.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 6:
					"No estar� seguro de c�mo hacer eso.";
				1, 7:
					"No estar� segura de c�mo hacer eso.";
				3, 9:
					"No estar�n seguros de c�mo hacer eso.";
				4, 10:
					"No estar�n seguras de c�mo hacer eso.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Use
!!------------------------------------------------------------------------------

Verb	'emplea' 'usa' 'utiliza'
	* noun							-> Use
	* noun 'con'/'en' noun			-> Use
;

Verb	'actua' 'interactua'
	* noun							-> Use
	* 'con' noun					-> Use
	* noun 'con'/'en' noun			-> Use
	* 'con' noun 'en' noun			-> Use
	* 'en' noun 'con' noun			-> Use reverse
;

[ UseSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Pienso en alg�n uso para ", (the) noun ,", pero no
					termino de decidirme por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensamos en alg�n uso para ", (the) noun ,", pero no
					terminamos de decidirnos por una acci�n concreta.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Piensas en alg�n uso para ", (the) noun ,", pero no
					terminas de decidirte por una acci�n concreta.";
				3, 4, 9, 10:
					"Pens�is en alg�n uso para ", (the) noun ,", pero no
					termin�is de decidiros por una acci�n concreta.";
			}
		THIRD_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Piensa en alg�n uso para ", (the) noun ,", pero no
					termina de decidirse por una acci�n concreta.";
				3, 4, 9, 10:
					"Piensan en alg�n uso para ", (the) noun ,", pero no
					terminan de decidirse por una acci�n concreta.";
			}
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pens� en alg�n uso para ", (the) noun ,", pero no
					termin� de decidirme por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensamos en alg�n uso para ", (the) noun ,", pero no
					terminamos de decidirnos por una acci�n concreta.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pensaste en alg�n uso para ", (the) noun ,", pero no
					terminaste de decidirte por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensasteis en alg�n uso para ", (the) noun ,", pero no
					terminasteis de decidiros por una acci�n concreta.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Pens� en alg�n uso para ", (the) noun ,", pero no
					termin� de decidirse por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensaron en alg�n uso para ", (the) noun ,", pero no
					terminaron de decidirse por una acci�n concreta.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensar� en alg�n uso para ", (the) noun ,", pero no
					terminar� de decidirme por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensaremos en alg�n uso para ", (the) noun ,", pero no
					terminaremos de decidirnos por una acci�n concreta.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensar�s en alg�n uso para ", (the) noun ,", pero no
					terminar�s de decidirte por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensar�is en alg�n uso para ", (the) noun ,", pero no
					terminar�is de decidiros por una acci�n concreta.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Pensar� en alg�n uso para ", (the) noun ,", pero no
					terminar� de decidirse por una acci�n concreta.";
				3, 4, 9, 10:
					"Pensar�n en alg�n uso para ", (the) noun ,", pero no
					terminar�n de decidirse por una acci�n concreta.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Write
!!------------------------------------------------------------------------------

Verb	'escribe'
	* noun							-> Write
	* 'en'/'el' noun				-> Write
	* noun 'con' noun				-> Write
	* 'en'/'el' noun 'con' noun		-> Write
; VerboIrregular "escribir" with imperativo 'escribe';

[ WriteSub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Ahora no tengo nada que escribir.";
				3, 4, 9, 10:
					"Ahora no tenemos nada que escribir.";
			}
		SECOND_PERSON_PRESENT:
		2:	switch (gna) {
				0, 1, 6, 7:
					"Ahora no tienes nada que escribir.";
				3, 4, 9, 10:
					"Ahora no teneis nada que escribir.";
			}
		THIRD_PERSON_PRESENT:
		3:	switch (gna) {
				0, 1, 6, 7:
					"Ahora no tiene nada que escribir.";
				3, 4, 9, 10:
					"Ahora no tienen nada que escribir.";
			}
		FIRST_PERSON_PAST:
		4:	switch (gna) {
				0, 1, 6, 7:
					"No ten�a nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No ten�amos nada que escribir en aquel momento.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No ten�as nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No ten�ais nada que escribir en aquel momento.";
			}
		THIRD_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"No ten�a nada que escribir en aquel momento.";
				3, 4, 9, 10:
					"No ten�an nada que escribir en aquel momento.";
			}
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr� nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendremos nada que escribir en ese momento.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr�s nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendr�is nada que escribir en ese momento.";
			}
		THIRD_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"No tendr� nada que escribir en ese momento.";
				3, 4, 9, 10:
					"No tendr�n nada que escribir en ese momento.";
			}
	}
];

!!------------------------------------------------------------------------------
!! ##Xyzzy
!!------------------------------------------------------------------------------

Verb	'xyzzy' 'plugh' 'plover' 'abracadabra'
	*								-> Xyzzy
; VerboIrregular "xyzzy" with imperativo 'xyzzy';

[ XyzzySub gna;
	gna = GetGNAOfObject(player);
	switch (_grammatical_inflection) {
		FIRST_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responde a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responde a nuestras palabras.";
			}
		SECOND_PERSON_PRESENT:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responde a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responde a vuestras palabras.";
			}
		THIRD_PERSON_PRESENT:
			"Un rumor silencioso responde a sus palabras.";
		FIRST_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso respondi� a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso respondi� a nuestras palabras.";
			}
		SECOND_PERSON_PAST:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso respondi� a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso respondi� a vuestras palabras.";
			}
		THIRD_PERSON_PAST:
			"Un rumor silencioso respondi� a sus palabras.";
		FIRST_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responder� a mis palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responder� a nuestras palabras.";
			}
		SECOND_PERSON_FUTURE:
			switch (gna) {
				0, 1, 6, 7:
					"Un rumor silencioso responder� a tus palabras.";
				3, 4, 9, 10:
					"Un rumor silencioso responder� a vuestras palabras.";
			}
		THIRD_PERSON_FUTURE:
			"Un rumor silencioso responder� a sus palabras.";
	}
];
