

!!==============================================================================
!!
!!	RECEPTACLES
!!	Contenedores (con capacidad definida)
!!
!!==============================================================================
!!
!!	File:			receptacles.h
!!	Author(s):		Peer Schaefer <peer@wolldingwacht.de> (lib. recept.h)
!!					J. Francisco Mart�n <jfm.lisaso@gmail.com> (traducci�n)
!!	Language:		ES (Castellano)
!!	System:			Inform-INFSP 6
!!	Platform:		M�quina-Z / GLULX
!!	Version:		2.1
!!	Released:		2014/02/06
!!	Notes:			Las funciones pueden no comportarse como se espera si se 
!!					utiliza una versi�n del compilador Inform igual o anterior 
!!					a la 6.15.
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	2.1: 2014/02/06	Traducci�n completa de la documentaci�n.
!!	2.0: 2012/05/03	Correcciones y creaci�n de la propiedad error_messages 
!!					sobre la clase Receptacle para separar la l�gica y los 
!!					mensajes.
!!	1.0				Traducci�n de la librer�a original recept.h v1.0 de Peer 
!!					Schaefer, para implementar contenedores con capacidades 
!!					definidas.
!!
!!------------------------------------------------------------------------------
!!
!!	Copyright (c) 2002, 2006, Peer Schaefer
!!	Copyright (c) 2012, 2014, J. Francisco Mart�n
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
!!	# REFERENCIA
!!
!!	Esta librer�a implementa una nueva clase de objeto, llamada Receptacle. Los 
!!	recept�culos son contenedores o soportes con ciertas capacidades definidas 
!!	sobre el peso, volumen, tama�o y n�mero de objetos que pueden albergar en 
!!	su interior o sobre ellos. Cada vez que se intenta colocar un objeto en un 
!!	Receptacle, �ste comprobar� si sus par�metros de capacidad son suficientes 
!!	para albergar o no al nuevo objeto.
!!
!!	Para indicar su peso, volumen y tama�o, los objetos del juego pueden tener 
!!	definidas las siguientes propiedades (no son obligatorias):
!!
!!	 *	weight	(peso)
!!	 *	volume	(volumen)
!!	 *	size	(tama�o. Representa la longitud m�xima en cualquier eje. Ej: 
!!				la longitud de una flecha o de un bast�n. Resulta obvio que la 
!!				capacidad de volumen de un carcaj termina "agot�ndose" cuando 
!!				se introducen suficientes flechas en �l, pero la capacidad de 
!!				tama�o del carcaj no se agota con la suma de tama�os de las 
!!				flechas almacenadas en �l: la capacidad de tama�o indica si una 
!!				flecha es o no demasiado larga para el carcaj.)
!!
!!	Cada una de estas tres propiedades puede ser un valor num�rico o una rutina 
!!	que retorne un valor num�rico. Si alguna de las tres propiedades no est� 
!!	definida o tiene el valor 0 (cero), se interpretar� que esa caracter�stica 
!!	del objeto ser� 0 (lo que indicar�a que el objeto carece de peso, volumen, 
!!	o tama�o, o que se trata de una medida despreciable).
!!
!!	*** Nota: weight, volume y size se miden en unidades abstractas (son 
!!	simples n�meros sin dimensi�n). Que una unidad se refiera, por ejemplo, a 
!!	un gramo, una libra, una tonelada, o la masa del sol, es decisi�n exclusiva 
!!	del programador.
!!
!!	Para crear un recept�culo que compruebe autom�ticamente peso, volumen y 
!!	tama�o de los objetos que se intenten introducir en �l, se crea una nueva 
!!	clase Receptacle. Estos recept�culos pueden definir tres nuevas propiedades 
!!	(de nuevo, no son obligatorias):
!!
!!	 *	capacity_weight
!!	 *	capacity_volume
!!	 *	capacity_size
!!
!!	Cada una de estas tres propiedades puede ser un valor num�rico o una rutina 
!!	que retorne un valor num�rico. Si alguna de estas propiedades no est� 
!!	definida o tiene el valor INFINITE_CAPACITY (una constante predefinida por 
!!	la librer�a), la capacidad respectiva para esa medida del recept�culo se 
!!	considerar� infinita. 
!!
!!	Desde luego, los contenedores/soportes pueden tener tambi�n definidos un 
!!	peso, volumen y tama�o (ya que no se tratan s�lo de contenedores/soportes, 
!!	si no tambi�n de objetos que pueden ser colocados en otros recept�culos).
!!
!!	En resumen:
!!
!!	 *	El jugador puede almacenar m�ltiples objetos en un Receptacle, siempre 
!!		que el peso total no exceda el valor capacity_weight del recept�culo.
!!	 *	El jugador puede almacenar m�ltiples objetos en un Receptacle, siempre 
!!		que el volumen total no exceda el valor capacity_volume del recept�culo.
!!	 *	Dicho de otra forma: capacity_weight y capacity_volume son valores que 
!!		acaban "agot�ndose" conforme se almacenan objetos en el recept�culo.
!!	 *	La propiedad capacity_size se comporta de forma diferente: no se trata 
!!		de un l�mite que se agote a medida que se va a�adiendo m�s peso o 
!!		volumen al recept�culo, si no que se tiene que comprobar por separado 
!!		cada vez que se intenta introducir un nuevo objeto en �l.
!!
!!	Por �ltimo, un Receptacle puede tambi�n tener definida una nueva propiedad 
!!	capacity_number. Este atributo tiene que ser bien un valor n�merico o una 
!!	rutina que devuelva un valor num�rico, e indica cu�ntos objetos (como 
!!	m�ximo) se pueden almacenar dentro de un recept�culo. Se mostrar� un 
!!	mensaje de error cada vez que se intente introducir cualquier objeto una 
!!	vez se haya alcanzado ese m�ximo.
!!
!!
!!	# DETALLES T�CNICOS
!!
!!	 *	Calcular el peso de un contenedor/soporte es un proceso recursivo: los 
!!		pesos de todos los objetos inmediatamente contenidos en �l se a�aden al 
!!		peso del propio contenedor/soporte. Ocurre igual con los objetos que 
!!		hay en el contenedor/soporte, si �stos a su vez albergan otros objetos, 
!!		y as� sucesivamente.
!!	 *	Si el peso de un objeto viene dado por una rutina, esta rutina deber�a 
!!		devolver el peso TOTAL del objeto, incluyendo los pesos de todos los 
!!		objetos que alberga directa e indirectamente en �l. En este caso, los 
!!		pesos de los objetos contenidos en el recept�culo NO se calculan 
!!		autom�ticamente. Esto a�ade flexibilidad a la hora de crear 
!!		recept�culos especiales (ej: una bolsa m�gica cuyo peso es menor que el 
!!		de los objetos que contiene en su interior).
!!	 *	El volumen y los tama�os de los objetos que alberga un recept�culo NO 
!!		se a�aden al volumen o tama�o del Receptacle (se asume que un 
!!		recept�culo est�ndar no es flexible y tiene unas proporciones fijas y 
!!		predeterminadas). Para reescribir este comportamiento se pueden definir 
!!		nuevas propiedades VOLUME y SIZE, de forma que calculen el volumen y 
!!		tama�o del recept�culo en tiempo de ejecuci�n (ver EJEMPLO 3).
!!	 *	Es perfectamente posible crear un recept�culo cuya capacidad sea 
!!		superior a sus propias medidas (un comportamiento altamente improbable 
!!		en un objeto, pero que permite la creaci�n de cajas m�gicas, agujeros 
!!		negros y otros objetos extra�os).
!!
!!
!!	# VERBOS DE DEPURACI�N
!!
!!	Al compilar en modo depuraci�n (con la constante DEBUG), la librer�a define 
!!	tres meta-acciones nuevas:
!!
!!	 *	xpeso OBJETO			imprime el peso del objeto
!!	 *	xdimensiones OBJETO		imprime todas las dimensiones del objeto
!!	 *	xcapacidad OBJETO		imprime todas laas capacidades del objeto
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 1
!!
!!	Creaci�n de una caja con un volumen de 10 y una capacidad de volumen de 9, 
!!	y una piedra con un volumen de 2. El jugador puede poner hasta 4 piedras en 
!!	la caja (cuyo volumen total ser�a 2*4 = 8). Una quinta piedra no podr�a ser 
!!	introducida en la caja, puesto que su capacidad es 9 y el volumen total de 
!!	5 piedras ser�a de 10:
!!
!!		Receptacle -> box "caja"
!!		 with	name 'caja',
!!				volume 10,			! el volumen de la propia caja
!!				capacity_volume 9,	! la capacidad de la caja
!!		 has	container;
!!
!!		Object -> stone "piedra"
!!		 with	name 'piedra',
!!				volume 2;			! el volumen de la piedra
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 2
!!
!!	El siguiente ejemplo crea una caja de madera y una caja de acero:
!!
!!		Receptacle -> wooden_box "caja de madera"
!!		 with	name 'caja' 'madera',
!!				volume 10,			! volumen del objeto
!!				capacity_volume 9,	! capacidad de volumen del objeto
!!		 has	container;
!!
!!		Receptacle -> stell_box "caja de acero"
!!		 with	name 'caja' 'acero',
!!				volume 8,			! volumen del objeto
!!				capacity_volume 7,	! capacidad de volumen del objeto
!!		 has	container;
!!
!!	El jugador puede introducir la caja de acero (volumen 8) dentro de la caja 
!!	de madera (capacidad 9), pero la caja de madera (volumen 10) no se puede 
!!	introducir en la caja de acero (capacidad 7). Si se introduce un objeto de 
!!	volumen igual o mayor a 2 dentro de la caja de madera (como la piedra del 
!!	EJEMPLO 1), ya no se podr�a introducir la caja de acero en su interior, 
!!	porque �sta requiere un espacio libre de 8 o m�s.
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 3
!!
!!	El volumen y tama�o de los objetos contenidos en un recept�culo NO se 
!!	a�aden a su volumen y tama�o total (se asume que los recept�culos no son 
!!	flexibles y tienen proporciones fijas). Si se desea crear una bolsa 
!!	flexible cuyo volumen aumente conforme se introducen objetos en su 
!!	interior, se debe implementar la rutina apropiada en su propiedad volume:
!!
!!		Receptacle -> bag "bolsa flexible"
!!		 with	name 'bolsa' 'flexible',
!!				capacity_volume 20,
!!				capacity_size 5,
!!				volume [ result i;
!!					!! Volumen m�nimo de la bolsa (cuando est� vac�a):
!!					result = 1;
!!					!! Se suman los vol�menes de los objetos que contiene:
!!					objectloop (i in self)
!!						result = result + VolumeOf(i);
!!					!! Retorna el volumen total acumulado:
!!					return result;
!!				],
!!				size [ result i;
!!					!! Tama�o m�nimo de la bolsa (cuando est� vac�a):
!!					result = 1;
!!					!! Se obtiene el objeto contenido de mayor tama�o:
!!					objectloop(i in self) 
!!						if (SizeOf(i) > result) result = SizeOf(i);
!!					!! El tama�o del mayor objeto contenido en ella determina 
!!					!! el tama�o actual de la bolsa:
!!					return result;
!!				],
!!		 has	container;
!!
!!------------------------------------------------------------------------------
!!
!!	# EJEMPLO 4
!!
!!	Los pesos de los objetos contenidos en �l se a�aden autom�ticamente al peso 
!!	total del recept�culo. Se puede sobreescribir este comportamiento 
!!	definiendo la propiedad weight como una rutina. El siguiente ejemplo crea 
!!	una bolsa m�gica cuyo peso total es s�lo la mitad del peso de los objetos 
!!	contenidos en su interior:
!!
!!		Receptacle -> magic_bag "bolsa m�gica"
!!		 with	name 'bolsa' 'magica' 'maravillosa',
!!				capcity_volume 100,
!!				weight [ result i;
!!					!! Peso base de la bolsa (cuando est� vac�a):
!!					result = 1;
!!					!! Se suman los pesos de los objetos que contiene:
!!					objectloop(i in self)
!!						result = result + WeightOf(i);
!!					!! Retorna el 50% del peso total:
!!					return (result/2);
!!				],
!!		 has	container;
!!
!!------------------------------------------------------------------------------
System_file;

Class	FAKE_RECEPT					! Se definen las siete nuevas
 with	weight	0,					! propiedades sin usar espacio
		size	0,					! de programa ni memoria en
		volume	0,					! tiempo de ejecuci�n
		capacity_weight	0,
		capacity_size	0,
		capacity_volume	0,
		capacity_number	0;

Constant INFINITE_CAPACITY -1;		! (-1) simboliza una capacidad infinita

!!==============================================================================
!! Funciones para calcular el peso, volumen y tama�o de cualquier objeto dado
!!------------------------------------------------------------------------------

[ WeightOf obj		w i;
	if (obj provides weight) {
		if (metaclass(obj.weight) == Routine) return indirect (obj.weight);
		w = obj.weight;
	} else  w = 0;
	if ((obj has container) || (obj has supporter))
		! Add weight of child-objects
		objectloop (i in obj) w = w + WeightOf (i);
	return w;
];

[ SizeOf obj;
	if (obj provides size) {
		if (metaclass(obj.size) == Routine) return indirect (obj.size);
		return obj.size;
	}
	return 0;
];

[ VolumeOf obj;
	if (obj provides volume) {
		if (metaclass(obj.volume) == Routine) return indirect (obj.volume);
		return obj.volume;
	}
	return 0;
];

!!==============================================================================
!! Funciones para calcular la capacidad de cualquier contenedor o soporte dado
!!------------------------------------------------------------------------------

[ CapacityWeightOf obj;
	if (obj provides capacity_weight) {
		if (metaclass(obj.capacity_weight) == Routine)
			return indirect (obj.capacity_weight);
		return obj.capacity_weight;
	}
	return INFINITE_CAPACITY;	! Unlimited weight capacity
];

[ CapacityVolumeOf obj;
	if (obj provides capacity_volume) {
		if (metaclass(obj.capacity_volume) == Routine)
			return indirect (obj.capacity_volume);
		return obj.capacity_volume;
	}
	return INFINITE_CAPACITY;	! Unlimited volume capacity
];

[ CapacitySizeOf obj;
	if (obj provides capacity_size) {
		if (metaclass(obj.capacity_size) == Routine)
			return indirect (obj.capacity_size);
		return obj.capacity_size;
	}
	return INFINITE_CAPACITY;	! Unlimited size capacity
];

[ CapacityNumberOf obj;
	if (obj provides capacity_number) {
		if (metaclass(obj.capacity_number) == Routine)
			return indirect (obj.capacity_number);
		return obj.capacity_number;
	}
	return INFINITE_CAPACITY;	! Unlimited number of objects
];

!!==============================================================================
!! Funci�n auxiliar para comprobar si un contenedor o soporte tiene capacidad 
!! para soportar un objeto, dados ambos como argumentos. Retorna falso si el 
!! objeto no entra, verdadero en caso contrario.
!!------------------------------------------------------------------------------

[ CheckIfObjectFits receiver obj	s i;
	!! Se comprueba si el peso de obj est� dentro de los l�mites de receiver:
	if ( CapacityWeightOf( receiver ) ~= INFINITE_CAPACITY ) {
		if ( WeightOf(obj) > CapacityWeightOf( receiver ))
			return false;
		s = 0; objectloop (i in receiver) s = s + WeightOf(i);
		if ( (s + WeightOf(obj)) > CapacityWeightOf (receiver) )
			return false;
	}
	!! Se comprueba si el volumen de obj est� dentro de los l�mites de receiver:
	if ( CapacityVolumeOf (receiver) ~= INFINITE_CAPACITY ) {
		if ( VolumeOf(obj) > CapacityVolumeOf( receiver ))
			return false;
		s = 0; objectloop (i in receiver) s = s + VolumeOf(i);
		if ( (s + VolumeOf(obj)) > CapacityVolumeOf( receiver ))
			return false;
	}
	!! Se comprueba si el tama�o de obj est� dentro de los l�mites de receiver:
	if ( CapacitySizeOf (receiver) ~= INFINITE_CAPACITY ) {
		if ( SizeOf(obj) > CapacitySizeOf( receiver ))
			return false;
	}
	!! Se comprueba el l�mite de n�mero de objetos de receiver:
	if ( CapacityNumberOf (receiver) ~= INFINITE_CAPACITY ) {
		s = 0; objectloop (i in receiver) s++;
		if ( (s+1) > CapacityNumberOf( receiver ))
			return false;
	}
	!! El objeto encaja en el receptor:
	return true;
];

!!==============================================================================
!! Definici�n de la nueva clase Receptacle
!!------------------------------------------------------------------------------

Class	Receptacle
 with	before [ s i;
			Receive:
				!! Se comprueba el peso (si su capacidad no es infinita):
				if ( CapacityWeightOf( self ) ~= INFINITE_CAPACITY ) {
					if ( WeightOf(noun) > CapacityWeightOf( self ))
						return self.error_messages(1, noun);
					!! Se calcula el peso de todo el contenido
					s = 0; objectloop (i in self) s = s + WeightOf(i);
					if ( (s + WeightOf(noun)) > CapacityWeightOf (self) )
						return self.error_messages(2);
				}

				!! Se comprueba el volumen (si su capacidad no es infinita):
				if ( CapacityVolumeOf (self) ~= INFINITE_CAPACITY ) {
					if ( VolumeOf(noun) > CapacityVolumeOf( self ))
						return self.error_messages(3, noun);
					!! Se calcula el volumen de todo el contenido
					s = 0; objectloop (i in self) s = s + VolumeOf(i);
					if ( (s + VolumeOf(noun)) > CapacityVolumeOf( self ))
						return self.error_messages(4);
				}

				!! Se comprueba el tama�o (si su capacidad no es infinita):
				if ( CapacitySizeOf (self) ~= INFINITE_CAPACITY ) {
					if ( SizeOf(noun) > CapacitySizeOf( self ))
						return self.error_messages(5, noun);
				}

				!! Se comprueba el n�mero (si su capacidad no es infinita):
				if ( CapacityNumberOf (self) ~= INFINITE_CAPACITY ) {
					s = 0; objectloop (i in self) s++;
					if ( (s+1) > CapacityNumberOf( self ))
						return self.error_messages(6);
				}

				return false;
		],
		!! Mensajes de error. Se producen al intentar meter en el recept�culo 
		!! un objeto que viola alguno de los l�mites de capacidad definidos
		error_messages [ id obj;
			switch (id) {
				1:
					!! Intentar meter en el bolsillo un objeto cuyo peso supera 
					!! el l�mite permitido
					print_ret (The) obj, " ", (es) obj, " demasiado pesad", 
					(o) obj ," para ", (the) obj ,".";
				2:
					!! Intentar meter en el bolsillo un objeto cuyo peso, unido 
					!! al del resto de objetos que hay ya en el bolsillo, 
					!! superan el l�mite permitido
					print_ret (The) self ," ha", (n) self ," alcanzado su 
					capacidad m�xima.";
				3:
					!! Intentar meter en el bolsillo un objeto cuyo volumen 
					!! supera el l�mite permitido
					print_ret (The) obj ," no encaja", (n) obj ," dentro de ", 
					(the) self ,".";
				4:
					!! Intentar meter en el bolsillo un objeto cuyo volumen, 
					!! unido al del resto de objetos que hay ya en el bolsillo, 
					!! superan el l�mite permitido
					print_ret (The) self ," ha", (n) self ," alcanzado su 
					capacidad m�xima.";
				5:
					!! Intentar meter en el bolsillo un objeto cuyo tama�o 
					!! supera el l�mite permitido
					print_ret (The) obj ," ", (es) obj ," demasiado grande", 
					(s) obj ," para ", (the) self ,".";
				6:
					!! Intentar meter en el bolsillo un objeto despu�s de haber 
					!! alcanzado el l�mite de objetos introducidos permitido
					"En ", (the) self ," no entran ya m�s cosas.";
			}
		];

!!==============================================================================
!! Verbos de depuraci�n
!!------------------------------------------------------------------------------

#Ifdef DEBUG;

Verb meta 'xpeso' 'xweight'			* noun	-> MetaWeight;
Verb meta 'xdimensiones' 'xmeasure'	* noun	-> MetaMeasure;
Verb meta 'xcapacidad' 'xcapacity'	* noun	-> MetaCapacity;

[ MetaWeightSub;
	print (The) noun, " pesa", (n) noun ," ",
	WeightOf (noun), " unidad";
	if ( WeightOf( noun ) ~= 1 ) print "es";
	new_line;
	return true;
];

[ MetaMeasureSub;
	print (The) noun, ":^";
	spaces(6);	print "Peso: ",		WeightOf(noun),	" unidades^";
	spaces(6);	print "Tama�o: ",	SizeOf(noun),	" unidades^";
	spaces(6);	print "Volumen: ",	VolumeOf(noun),	" unidades^";
	return true;
];

[ MetaCapacitySub;
	print (The) noun, ":^";

	spaces(6); print "Capacidad (peso): ";
	if (CapacityWeightOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityWeightOf(noun), " unidades^";

	spaces(6); print "Capacidad (tama�o): ";
	if (CapacitySizeOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacitySizeOf(noun), " unidades^";

	spaces(6); print "Capacidad (volumen): ";
	if (CapacityVolumeOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityVolumeOf(noun), " unidades^";

	spaces(6); print "Capacidad (n�mero de objetos): ";
	if (CapacityNumberOf(noun) == INFINITE_CAPACITY) print "infinita^";
	else print CapacityNumberOf(noun), "^";

	return true;
];

#Endif; ! DEBUG;


