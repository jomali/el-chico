

!!==============================================================================
!!
!!	GSTATUSX WINDOW
!!	M�dulo de ventana de estado para GWindows
!!
!!==============================================================================
!!
!!	Archivo:		gstatusX.h
!!	Autor(es):		J. Francisco Martín <jfm.lisaso@gmail.com>
!!	Idioma:			ES (Castellano)
!!	Sistema:		Inform-INFSP 6
!!	Plataforma:		GLULX
!!	Versi�n:		1.1
!!	Fecha:			2014/10/20
!!
!!	GStatusXWin crea una l�nea de estado en la que se imprime el nombre,
!!	centrado en la ventana, de la localidad actual del personaje protagonista.
!!
!!	Hereda de TextGrid.
!!
!!------------------------------------------------------------------------------
!!
!!	# HISTORIAL DE VERSIONES
!!
!!	1.1: 2014/10/20	Modificado el vector utilizado para tratar los contenidos
!!					de la barra de estado, la rutina para imprimir el nombre de
!!					la localidad en que se encuentra el personaje controlado
!!					por el usuario, y la propiedad GStatusXWin.update.
!!	1.0: 2014/06/06
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

#Ifndef GW_GSTATUS_H;

System_file;
Constant GW_GSTATUS_H;

!! Vector auxiliar para manejar los contenidos de la barra de estado:
#Ifdef VN_1630;	! compilador 6.30 o superior
Array _gstatusx_buffer buffer 160; ! 150 y algo caracteres deber�an bastar
#Ifnot;			! compiladores anteriores
Array _gstatusx_buffer -> 160 + WORDSIZE;
#Endif; ! VN_1630

!! Clase con la que se define la extensi�n de barra de estado:
Class	GStatusXWin
 class	TextGrid
 with	redraw [; self.update(); ],
		update [ pos i;
			if (location == 0 || player == 0 || parent(player) == 0) return;
			glk_set_window(self.winid);
			pos = (self.width -
				PrintToBuffer(_gstatusx_buffer, 160, self.locationName)) / 2;
			glk_window_clear(self.winid);
			glk_window_move_cursor(self.winid, pos, 0);
			for (i=0 : i<_gstatusx_buffer-->0 : i++) {
				if (i ~= 0) print (char) _gstatusx_buffer->(i+WORDSIZE);
				else print (char) UpperCase(_gstatusx_buffer->(i+WORDSIZE));
			}
		],
		locationName [;
			if (location == thedark) print (name) location;
			else {
				FindVisibilityLevels();
				if (visibility_ceiling == location) print (name) location;
				else print (The) visibility_ceiling;
			}
		],
		split 1,
		split_dir winmethod_Above,
		stylehints style_Normal stylehint_Reversecolor 1,
 has	abssplit;

#Endif; ! GW_GSTATUS_H;
