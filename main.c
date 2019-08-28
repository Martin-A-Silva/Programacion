/*
 * main.c
 *
 *  Created on: 22 ago. 2019
 *      Author: martin
 *
 *      El programa debe leer una oración (longitud no especificada)
 *      y contar la cantidad de palabras que terminan en una vocal.
 *      La oración termina en un punto, en caso de haber más de un punto debe dar error.
 */

#include <stdio.h>
#include <ctype.h>

int main(){

	char str[256];
	int i=0, con_vocal=0;

	printf("Inicio del programa...\n");
	printf("Ingrese la oración (máximo arbitrario de 256 caracteres y debe terminar con un punto):\n");

	scanf("%[^\n]",str);							//con "[^\n]" se continúa leyendo hasta que se encuentre el caracter de nueva línea.

	printf("La oración que ingresó es:\n%s\nY sólo se la evaluará hasta el primer punto.\n",str);

	while(*(str+i)!='.'){							//Se evalua la cadena caracter a caracter hasta que llegue al punto. Todo lo que esté después no es considerado (se supone que es sólo una oración!)

		if((*(str+i)==' ')||(*(str+i)==',')||(*(str+i)==';')){				//Se toma como separadores de palabras a los espacios, comas, y punto y comas
			if((*(str+i-1)=='a')||(*(str+i-1)=='e')||(*(str+i-1)=='i')||	//Una vez separada la palabra, se ve si la ultima letra es una vocal
			   (*(str+i-1)=='o')||(*(str+i-1)=='u')){

				con_vocal++;												//Y se aumenta el contador en caso de ser así.

			}
		}

		i++;																//Se usa la variable i como iterador para la cadena.

	}

	if(*(str+i)=='.'){													//Esta sección es sólo
		if((*(str+i-1)=='a')||(*(str+i-1)=='e')||(*(str+i-1)=='i')||	//para evaluar si la ÚLTIMA palabra
 		   (*(str+i-1)=='o')||(*(str+i-1)=='u')){						//de la oración termina en vocal.

			con_vocal++;

		}

	}

	printf("La oración tiene %d palabra(s) terminada(s) en vocal.\n",con_vocal);
	printf("Fin del programa.\n");
	return 0;
}
