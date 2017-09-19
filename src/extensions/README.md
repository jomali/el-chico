# I6-EXTENSIONES


Relación de extensiones incluidas:

- **Aim and fire**: Sistema de apuntado y disparo a través de un mecanismo QTE (Quick Time Event). Utiliza la ventana de estado de la aventura para mostrar la animación de una retícula desplazándose de un extremo a otro de la ventana. El jugador debe detener la retí­cula lo más cerca posible del centro de la pantalla. El éxito o fracaso de la acción se determina en función de lo cerca o lejos del centro de la pantalla que el jugador haya acertado a detener la retícula. *Autor(es): J. Francisco Martín*.

- **Dainunek**: DreamBytes Adventures - Inicialización unificada de extensiones en Glk. Facilita un objeto capaz de implementar y gestionar automáticamente los siguientes puntos de entrada para Glk que proporciona la librería Inform: ``IdentifyGlkObject()`` y ``HandleGlkEvent()``. *Autor(es): Eliuk Blau*.

- **Damusix**: DreamBytes Adventures - Administrador unificado de sonido en Glulx. Proporciona un objeto administrador encargado de gestionar todas las funciones necesarias para la reproducción de música y efectos de sonido en la máquina virtual Glulx. *Autor(es): Eliuk Blau*.

- **GStatusX Window**: Módulo de ventana de estado para la librería ``GWindows``, de *L. Ross Raszewski*. Define una ventana de estado en la que se imprime el nombre de la localidad actual del personaje protagonista, centrado en pantalla. *Autor(es): J. Francisco Martín*.

- **Parsing Preprocessor**: Preprocesador de la entrada de teclado del usuario utilizando análisis no estricto para el reconocimiento de patrones. Trata de identificar la entrada de usuario con alguno de los objetos modelados en el entorno simulado de la obra (facilita la utilización de comandos que cuenten tan sólo con el nombre de objetos presentes en el entorno, sin necesidad de especificar un verbo concreto). *Autor(es): J. Francisco Martín*.

- **Receptacles**: Implementación de la clase de objetos ``Receptacle``; un tipo de contenedores o soportes con atributos de peso, volumen, tamaño y número de objetos que pueden albergar en su interior (o sobre ellos). Cada vez que se intenta colocar un objeto en un ``Receptacle``, éste comprobará si tiene capacidad suficiente para albergar o no al nuevo objeto. *Autor(es): Peer Schaefer y J. Francisco Martín*.

- **Spanish Extended Grammar**: Gramática española extendida. Define un nuevo conjunto de acciones (así­ como sinónimos sobre acciones ya definidas en la gramática por defecto) que pueden ser utilizadas en una obra. Los mensajes por defecto de las nuevas acciones contemplan inflexiones de género y número del actor y tiempo verbal del narrador. *Autor(es): Emily Short, J. Francisco Martín y Mapache*.

- **Spanish Library Messages**: Mensajes por defecto de la librería en español con inflexiones de género y número del actor y tiempo verbal del narrador. Basadas en la librería ``Spanish.h`` de INFSP6. *Autor(es): J. Francisco Martín*.

- **Topic Inventory**: Sistema de conversación con selección de temas utilizando análisis no estricto de la entrada de usuario para el reconocimiento de patrones. Basada en las notas de Eric Eve sobre sistemas de conversación: <http://www.tads.org/howto/convbkg.htm>, y construida sobre la extensión ``NPC_Conversacion`` v1.0 de *Mastodon*. *Autor(es): J. Francisco Martín*.

- **Types**: Rutinas biplataforma (Máquina-Z/GLULX) para imprimir texto con diferentes estilos. Además de los estilos básicos: romana, itálica, negrita y monoespaciada; defne cuatro estilos abstractos que varían dependiendo del contexto: enfático, fuerte, código y parser. *Autor(es): J. Francisco Martín*.

Otras herramientas:

- **Preprocesador de texto**: Script Perl para preprocesar un archivo de texto. Sustituye ciertas etiquetas de texto por funciones definidas dentro del relato para manipular el estilo de los textos, listar objetos contenidos por otro objeto, o crear hipervínculos, por ejemplo. *Autor(es): J. Francisco Martín*.

Incluye además un directorio *discarded* con algunas extensiones no analizadas, pero que pueden implementar conceptos y soluciones de interés.
