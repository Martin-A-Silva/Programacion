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
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


char leeTec(int conEco) {					//Para leer caracter a caracter sin esperar '\n'
    struct termios oldattr, newattr;
    char ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~(conEco ? ICANON : ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


int esVocal(char *a){			//Para verificar si el caracter es una vocal (retorna 1 en caso de serlo)

	*a=tolower(*a);
	int r=0;
	char *b;
	char str[]="aeiouáéíóú";

	b=(strchr(str,*a));			//Si la función no encuentra el caracter en la cadena patrón
								//devuelve un apuntador nulo, de lo contrario el caracter ha sido encontrado
	if(b==NULL){
		//Nada que hacer acá.
	}
	else{
		r=1;
	}

	return r;

}

int finPalabra(char *a){						//Será fin de palabra cuando no sea un
	int r=0;									//caracter del alfabeto ni una vocal acentuada

	if((isalpha(*a)==0)&&(esVocal(a)==0)){
		r=1;

	}


	return r;
}

int main(){

	char *str,aux;
	int i=0, con_vocal=0;
	str=(char*)calloc(1,sizeof(char));					//Memoria dinámica para soportar cualquier longitud de oración

	puts("Inicio del programa...");
	puts("Ingrese la oración (termina al detectar un punto)");

	while(1){

		aux=leeTec(1);
		if(aux=='.'){

			*(str+i)=aux;							//Se finaliza la cadena con un punto

			if(*str=='.'){
				puts("\nNO COMENZAR CON UN PUNTO");
				exit(1);
			}

			//*(str+i+1)='\0';
			break;
		}

		char *tmp_ptr=(char *)realloc(str,(i+1)*sizeof(char));		//Se intenta aumentar el tamaño de memoria de la cadena.

		if(tmp_ptr==NULL){												//Si no se logra se cierra el programa

			free(str);
			puts("ERROR DE REALLOC");
			exit(1);
		}
		else{
			str = tmp_ptr;												//Sino, se aumenta efectivamente
		}

		*(str+i)=aux;													//Y asignamos a la cadena, el caracter que se acaba de leer.
		i++;
	}

	i=0;

	while(*(str+i)!='\0'){							//Se evalua la cadena caracter a caracter hasta que llegue al caracter nulo.

		if(finPalabra(str+i)){				//Cuando la función esta devuelve 1
											//es porque se llegó al fin de una palabra.

			if(i>0){						//Esta condición es para que en caso de iniciar la cadena
											//con un símbolo, que no lo tome como fin de palabra
				if(esVocal((str+i-1))){

					con_vocal++;			//Si el caracter anterior al finalizador de
											//palabra es vocal se aumenta el contador
				}
			}
		}

		i++;								//Se usa la variable i como iterador para la cadena.

	}

	free(str);
	printf("\nLa oración tiene %d palabra(s) terminada(s) en vocal.\n",con_vocal);
	puts("Fin del programa.");
	return 0;
}
