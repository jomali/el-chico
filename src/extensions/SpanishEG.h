

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
!!	Version:		3.5
!!	Released:		2014/10/19
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
!!	 -	Iron
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

Default	_grammatical_inflection 2;

!!------------------------------------------------------------------------------
!! Nuevos sin�nimos:
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
!! Extensiones a las acciones de la librer�a por defecto:
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0, 6:	"Nunca he sido un gran bailar�n.";
		1, 7:	"Nunca he sido una gran bailarina.";
		3, 9:	"Nunca hemos sido unos grandes bailarines.";
		4, 10:	"Nunca hemos sido unas grandes bailarinas.";
		}
	2:	switch (gna) {
		0, 6:	"Nunca has sido un gran bailar�n.";
		1, 7:	"Nunca has sido una gran bailarina.";
		3, 9:	"Nunca hab�is sido unos grandes bailarines.";
		4, 10:	"Nunca hab�is sido unas grandes bailarinas.";
		}
	3:	switch (gna) {
		0, 6:	"Nunca ha sido un gran bailar�n.";
		1, 7:	"Nunca ha sido una gran bailarina.";
		3, 9:	"Nunca han sido unos grandes bailarines.";
		4, 10:	"Nunca han sido unas grandes bailarinas.";
		}
	4:	switch (gna) {
		0, 6:	"Nunca fui un gran bailar�n.";
		1, 7:	"Nunca fui una gran bailarina.";
		3, 9:	"Nunca fuimos unos grandes bailarines.";
		4, 10:	"Nunca fuimos unas grandes bailarinas.";
		}
	5:	switch (gna) {
		0, 6:	"Nunca fuiste un gran bailar�n.";
		1, 7:	"Nunca fuiste una gran bailarina.";
		3, 9:	"Nunca fuisteis unos grandes bailarines.";
		4, 10:	"Nunca fuisteis unas grandes bailarinas.";
		}
	6:	switch (gna) {
		0, 6:	"Nunca fue un gran bailar�n.";
		1, 7:	"Nunca fue una gran bailarina.";
		3, 9:	"Nunca fueron unos grandes bailarines.";
		4, 10:	"Nunca fueron unas grandes bailarinas.";
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
!! ##Iron
!!------------------------------------------------------------------------------

Verb	'plancha' 'estira' 'desarruga'
	* noun							-> Iron
;

[ IronSub;
	switch (_grammatical_inflection) {
	1,2,3:	"No tiene sentido intentar hacer algo as�.";
	4,5,6:	"No ten�a sentido intentar hacer algo as�.";
	}
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
	1,2,3:
		if (noun has door) "No contesta nadie.";
		"No ocurre nada.";
	4,5,6:
		if (noun has door) "No contest� nadie.";
		"No ocurri� nada.";
	}
];

!!------------------------------------------------------------------------------
!! ##Masturbate
!!------------------------------------------------------------------------------

Verb	'masturba'
	* '-me'/'-te'					-> Masturbate
;

[ MasturbateSub gna;
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"Ahora no tengo ganas.";
		3,4,9,10:	"Ahora no tenemos ganas.";
		}
	2:	switch (gna) {
		0,1,6,7:	"Ahora no tienes ganas en realidad.";
		3,4,9,10:	"Ahora no teneis ganas en realidad.";
		}
	3:	switch (gna) {
		0,1,6,7:	"Ahora no tiene ganas.";
		3,4,9,10:	"Ahora no tienen ganas.";
		}
	4:	switch (gna) {
		0,1,6,7:	"No ten�a ganas.";
		3,4,9,10:	"No ten�amos ganas.";
		}
	5:	switch (gna) {
		0,1,6,7:	"No ten�as ganas.";
		3,4,9,10:	"No ten�ais ganas.";
		}
	6:	switch (gna) {
		0,1,6,7:	"No ten�a ganas.";
		3,4,9,10:	"No ten�an ganas.";
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
		1,2,3:	"No hay nada que leer en ", (the) noun, ".";
		4,5,6:	"No hab�a nada que leer en ", (the) noun, ".";
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"Grito con fuerza.";
		3,4,9,10:	"Gritamos con fuerza.";
		}
	2:	switch (gna) {
		0,1,6,7:	"Gritas con fuerza.";
		3,4,9,10:	"Gritais con fuerza.";
		}
	3:	switch (gna) {
		0,1,6,7:	"Grita con fuerza.";
		3,4,9,10:	"Gritan con fuerza.";
		}
	4:	switch (gna) {
		0,1,6,7:	"Grit� con fuerza.";
		3,4,9,10:	"Gritamos con fuerza.";
		}
	5:	switch (gna) {
		0,1,6,7:	"Gritaste con fuerza.";
		3,4,9,10:	"Gritasteis con fuerza.";
		}
	6:	switch (gna) {
		0,1,6,7:	"Grit� con fuerza.";
		3,4,9,10:	"Gritaron con fuerza.";
		}
	}
	!! "---�AARRGHH!";
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0, 6:	"Ya estoy bastante c�modo de pie.";
		1, 7:	"Ya estoy bastante c�moda de pie.";
		3, 9:	"Ya estamos bastante c�modos de pie.";
		4, 10:	"Ya estamos bastante c�modas de pie.";
		}
	2:	switch (gna) {
		0, 6:	"Ya est�s bastante c�modo de pie.";
		1, 7:	"Ya est�s bastante c�moda de pie.";
		3, 9:	"Ya est�is bastante c�modos de pie.";
		4, 10:	"Ya est�is bastante c�modas de pie.";
		}
	3:	switch (gna) {
		0, 6:	"Ya est� bastante c�modo de pie.";
		1, 7:	"Ya est� bastante c�moda de pie.";
		3, 9:	"Ya est�n bastante c�modos de pie.";
		4, 10:	"Ya est�n bastante c�modas de pie.";
		}
	4:	switch (gna) {
		0, 6:	"Ya estaba bastante c�modo de pie.";
		1, 7:	"Ya estaba bastante c�moda de pie.";
		3, 9:	"Ya est�bamos bastante c�modos de pie.";
		4, 10:	"Ya est�bamos bastante c�modas de pie.";
		}
	5:	switch (gna) {
		0, 6:	"Ya estabas bastante c�modo de pie.";
		1, 7:	"Ya estabas bastante c�moda de pie.";
		3, 9:	"Ya estabais bastante c�modos de pie.";
		4, 10:	"Ya estabais bastante c�modas de pie.";
		}
	6:	switch (gna) {
		0, 6:	"Ya estaba bastante c�modo de pie.";
		1, 7:	"Ya estaba bastante c�moda de pie.";
		3, 9:	"Ya estaban bastante c�modos de pie.";
		4, 10:	"Ya estaban bastante c�modas de pie.";
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
;

Verb	'haz'
	* 'el' 'amor' 'con' animate		-> SleepWith
;

[ SleepWithSub gna;
	if (noun == player) <<Masturbate>>;
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:  "Ni se me pasa por la cabeza algo as� ahora.";
		3,4,9,10: "Ni se nos pasa por la cabeza algo as� ahora.";
		}
	2:	switch (gna) {
		0,1,6,7:  "En realidad no se te pasar�a por la cabeza algo as� ahora.";
		3,4,9,10: "En realidad no se os pasar�a por la cabeza algo as� ahora.";
		}
	3:	switch (gna) {
		0,1,6,7:  "En realidad no se le pasar�a por la cabeza algo as� ahora.";
		3,4,9,10: "En realidad no se les pasar�a por la cabeza algo as� ahora.";
		}
	4:	switch (gna) {
		0,1,6,7: 	"No se me hubiese pasado por la cabeza algo as� en aquel 
					momento.";
		3,4,9,10:	"No se nos hubiese pasado por la cabeza algo as� en aquel 
					momento.";
		}
	5:	switch (gna) {
		0,1,6,7:	"No se te hubiese pasado por la cabeza algo as� en aquel 
					momento.";
		3,4,9,10:	"No se os hubiese pasado por la cabeza algo as� en aquel 
					momento.";
		}
	6:	switch (gna) {
		0,1,6,7:	"No se le hubiese pasado por la cabeza algo as� en aquel 
					momento.";
		3,4,9,10:	"No se les hubiese pasado por la cabeza algo as� en aquel 
					momento.";
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"No estoy en ning�n sitio del que deba levantarme.";
		3,4,9,10:	"No estamos en ning�n sitio del que debamos levantarnos.";
		}
	2:	switch (gna) {
		0,1,6,7:	"No est�s en ning�n sitio del que debas levantarte.";
		3,4,9,10:	"No estais en ning�n sitio del que debais levantaros.";
		}
	3:	switch (gna) {
		0,1,6,7:	"No est� en ning�n sitio del que deba levantarse.";
		3,4,9,10:	"No est�n en ning�n sitio del que deban levantarse.";
		}
	4:	switch (gna) {
		0,1,6,7:	"No estaba en ning�n sitio del que debiese levantarme.";
		3,4,9,10:	"No est�bamos en ning�n sitio del que debi�semos 
					levantarnos.";
		}
	5:	switch (gna) {
		0,1,6,7:	"No estabas en ning�n sitio del que debieses levantarte.";
		3,4,9,10:	"No estabais en ning�n sitio del que debieseis levantaros.";
		}
	6:	switch (gna) {
		0,1,6,7:	"No estaba en ning�n sitio del que debiese levantarse.";
		3,4,9,10:	"No estaban en ning�n sitio del que debiesen levantarse.";
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0, 6:	"No estoy seguro de c�mo hacerlo.";
		1, 7:	"No estoy segura de c�mo hacerlo.";
		3, 9:	"No estamos seguros de c�mo hacerlo.";
		4, 10:	"No estamos seguras de c�mo hacerlo.";
		}
	2:	switch (gna) {
		0, 6:	"No est�s seguro de c�mo hacerlo.";
		1, 7:	"No est�s segura de c�mo hacerlo.";
		3, 9:	"No est�is seguros de c�mo hacerlo.";
		4, 10:	"No est�is seguras de c�mo hacerlo.";
		}
	3:	switch (gna) {
		0, 6:	"No parece estar seguro de c�mo hacerlo.";
		1, 7:	"No parece estar segura de c�mo hacerlo.";
		3, 9:	"No parecen estar seguros de c�mo hacerlo.";
		4, 10:	"No parecen estar seguras de c�mo hacerlo.";
		}
	4:	switch (gna) {
		0, 6:	"No estaba seguro de c�mo hacer eso.";
		1, 7:	"No estaba segura de c�mo hacer eso.";
		3, 9:	"No est�bamos seguros de c�mo hacer eso.";
		4, 10:	"No est�bamos seguras de c�mo hacer eso.";
		}
	5:	switch (gna) {
		0, 6:	"No estabas seguro de c�mo hacer eso.";
		1, 7:	"No estabas segura de c�mo hacer eso.";
		3, 9:	"No estabais seguros de c�mo hacer eso.";
		4, 10:	"No estabais seguras de c�mo hacer eso.";
		}
	6:	switch (gna) {
		0, 6:	"No estaba seguro de c�mo hacer eso.";
		1, 7:	"No estaba segura de c�mo hacer eso.";
		3, 9:	"No estaban seguros de c�mo hacer eso.";
		4, 10:	"No estaban seguras de c�mo hacer eso.";
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"Pienso en alg�n uso para ", (the) noun ,", pero no 
					termino de decidirme por una acci�n concreta.";
		3,4,9,10:	"Pensamos en alg�n uso para ", (the) noun ,", pero no 
					terminamos de decidirnos por una acci�n concreta."; 
		}
	2:	switch (gna) {
		0,1,6,7:	"Piensas en alg�n uso para ", (the) noun ,", pero no 
					terminas de decidirte por una acci�n concreta.";
		3,4,9,10:	"Pensais en alg�n uso para ", (the) noun ,", pero no 
					terminais de decidiros por una acci�n concreta."; 
		}
	3:	switch (gna) {
		0,1,6,7:	"Piensa en alg�n uso para ", (the) noun ,", pero no 
					termina de decidirse por una acci�n concreta.";
		3,4,9,10:	"Piensan en alg�n uso para ", (the) noun ,", pero no 
					terminan de decidirse por una acci�n concreta."; 
		}
	4:	switch (gna) {
		0,1,6,7:	"Pens� en alg�n uso para ", (the) noun ,", pero no 
					termin� de decidirme por una acci�n concreta.";
		3,4,9,10:	"Pensamos en alg�n uso para ", (the) noun ,", pero no 
					terminamos de decidirnos por una acci�n concreta."; 
		}
	5:	switch (gna) {
		0,1,6,7:	"Pensaste en alg�n uso para ", (the) noun ,", pero no 
					terminaste de decidirte por una acci�n concreta.";
		3,4,9,10:	"Pensasteis en alg�n uso para ", (the) noun ,", pero no 
					terminasteis de decidiros por una acci�n concreta."; 
		}
	6:	switch (gna) {
		0,1,6,7:	"Pens� en alg�n uso para ", (the) noun ,", pero no 
					termin� de decidirse por una acci�n concreta.";
		3,4,9,10:	"Pensaron en alg�n uso para ", (the) noun ,", pero no 
					terminaron de decidirse por una acci�n concreta."; 
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
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"Ahora no tengo nada que escribir.";
		3,4,9,10:	"Ahora no tenemos nada que escribir.";
		}
	2:	switch (gna) {
		0,1,6,7:	"Ahora no tienes nada que escribir.";
		3,4,9,10:	"Ahora no teneis nada que escribir.";
		}
	3:	switch (gna) {
		0,1,6,7:	"Ahora no tiene nada que escribir.";
		3,4,9,10:	"Ahora no tienen nada que escribir.";
		}
	4:	switch (gna) {
		0,1,6,7:	"No ten�a nada que escribir.";
		3,4,9,10:	"No ten�amos nada que escribir.";
		}
	5:	switch (gna) {
		0,1,6,7:	"No ten�as nada que escribir.";
		3,4,9,10:	"No ten�ais nada que escribir.";
		}
	6:	switch (gna) {
		0,1,6,7:	"No ten�a nada que escribir.";
		3,4,9,10:	"No ten�an nada que escribir.";
		}
	}
];

!!------------------------------------------------------------------------------
!! ##Xyzzy
!!------------------------------------------------------------------------------

Verb	'xyzzy' 'plugh' 'plover' 'abracadabra'
	*								-> Xyzzy
;

[ XyzzySub gna;
	gna = GetGNAOfObject(player, true);
	switch (_grammatical_inflection) {
	1:	switch (gna) {
		0,1,6,7:	"Un rumor silencioso responde a mis palabras.";
		3,4,9,10:	"Un rumor silencioso responde a nuestras palabras.";
		}
	2:	switch (gna) {
		0,1,6,7:	"Un rumor silencioso responde a tus palabras.";
		3,4,9,10:	"Un rumor silencioso responde a vuestras palabras.";
		}
	3:	"Un rumor silencioso responde a sus palabras.";
	4:	switch (gna) {
		0,1,6,7:	"Un rumor silencioso respondi� a mis palabras.";
		3,4,9,10:	"Un rumor silencioso respondi� a nuestras palabras.";
		}
	5:	switch (gna) {
		0,1,6,7:	"Un rumor silencioso respondi� a tus palabras.";
		3,4,9,10:	"Un rumor silencioso respondi� a vuestras palabras.";
		}
	6:	"Un rumor silencioso respondi� a sus palabras.";
	}
];


