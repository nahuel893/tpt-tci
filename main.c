/*
ALUMNOS:
Tolaba, Sofia
Aguirre, Nahuel
Actualmente funciona para cargar listas y conjuntos anidados, es decir
llegamos a la fase 2, sin usar ordenamiento.

llegamos a cumplir las metas para la segunda presentacion.
*Detalles que no afectan al funcionamiento: 
	* al imprimir vacio al final de una estructura se imprime con una coma, no afecta
	* conjuntos y listas anidados no imprimen coma despues de su cierre ( }, ] )
	* se deja una cadena de una afnd para cargarlo sin necesidad del teclado (ver modulo de carga)
	
	Muchas gracias por todo profes!
 */
#include <stdio.h>
#include "CLStr.h"
#include <stdlib.h>
#include <string.h>


#define TAM_MAX 1000

#define NUEVO 1
#define MOSTRAR 2
#define CARD 3
#define PERTENECE 4
#define UNION_ 5   //se pone el guion bajo por colisi�n de nombre con la operacion union
#define INTERSECCION 6
#define	DIFERENCIA 7
#define PUSH_ 8
#define POP_ 9
#define CANT 10
#define SALIR 0

int menu();
void press_enter();




int main(int argc, char *argv[]) {
	// cadena de entrada
	struct dataType* d1 = NULL;
	struct dataType* d2 = NULL;
	struct dataType* d3 = NULL;
	struct dataType* automata1 = NULL , *automata2 = NULL ;//se inicializan los punteros en NULL
	struct dataType* elem;
	char *cadena;
	int rta, b;//bandera
	cadena = (char*)malloc(sizeof(char)*TAM_MAX);	
	do{
		//CLS
		rta = menu();
		switch( rta ){
		case NUEVO:
			printf("Dato a cargar: ");
			FLUSH
			leeCad(cadena, TAM_MAX);
			d1=createData(cadena);
			printf("Nueva estructura: \n");
			printData(d1, 0);printf("\n");
			break;
		case MOSTRAR:
			CLS
			if(d1 != NULL){
				printf("Estructura: \n");
				printData(d1, 0);
				printf("\n");
			}
			else printf("Aun no se han cargado datos. Por favor seleccione la opcion 1.\n");
			break;
		case CARD:
			if(returnType(d1)==SET){
				printf("Cardinal del Conjunto: %d\n",CARDINAL(d1));
			}
			else{
				printf("Tipo de estructura incorrecta para esta operacion\n");
			}
			break;
		case PERTENECE:
			if(returnType(d1)==SET) {
				printf("\nElemento a buscar: ");
				char cad[100];
				FLUSH
				leeCad(cad, TAM_MAX);
				if( cad[0] != '{' && cad[0] != '[' ){
					elem = create_STR( cad ); 
				}
				else
					elem=createData(cad);
				if (IN(d1,elem)) {
					printf("\n");
					printData(elem, 0);
					printf(" %s ", STR_IN);
					printData(d1, 0);
					printf("\n");
				}
				else{
					printf("\n");
					printData(elem, 0);
					printf(" %s ", STR_IN_NO);
					printData(d1, 0);
					printf("\n");
				}
				dataFree(&elem);
				
			}
			else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case UNION_:
			if (returnType(d1)==SET) {
				printf("Operacion a realizar A %s B\n", STR_UNION);
				printf("A= ");printData(d1, 0);
				printf("\nConjunto B=(Ingrese el conjunto) ");
				leeCad(cadena, TAM_MAX);
				d2 = createData(cadena);
				d3 = UNION(d1,d2);
				if (d3!=NULL) {
					printf("A %s B = ", STR_UNION);
					printData(d3, 0);printf("\n");
				} else printf("Error\n");
				dataFree(&d2);
				dataFree(&d3);
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case INTERSECCION:
			if (returnType(d1)==SET) {
				printf("Operacion a realizar A %s B\n", STR_INTER);
				printf("A= ");printData(d1, 0);
				printf("\nConjunto B= ");
				leeCad(cadena, TAM_MAX);
				d2=createData(cadena);
				d3 = INTER(d1,d2);
				if (d3!=NULL) {
					printf("A %s B = ", STR_INTER);printData(d3, 0);printf("\n");
				} else printf("Error\n");
				dataFree(&d2);
				dataFree(&d3);
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case DIFERENCIA:
			if (returnType(d1)==SET) {
				printf("Operacion a realizar A - B\n");
				printf("A= ");printData(d1, 0);
				printf("\nConjunto B= ");
				leeCad(cadena, TAM_MAX);
				d2 = createData(cadena);
				d3 = DIFF(d1,d2);
				if (d3!=NULL) {
					printf("A-B = ");printData(d3, 0);printf("\n");
				} else printf("Error\n");
				dataFree(&d2);
				dataFree(&d3);
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case PUSH_://debe existir un create_STR en caso de insertar un STR
			if(returnType(d1)==LIST) {
				printf("\nElemento a insertar: ");
				leeCad(cadena, TAM_MAX);
				if(cadena[0] == '{' || cadena[0] == '['){
					elem = createData(cadena);
				}
				else{
					elem = create_STR(cadena);
				}
				PUSH(d1,elem);
				printf("Lista modificada: ");
				printData(d1, 0);
				printf("\n");
				// el siguiente dataFree() era bug para las salidas de un lista despues 
				// de hacer PUSH, ocasionaba salidas extrañas con lugares vacios " , , , "
				// pues luego de insertar la lista se mostraba bien pero al usar la opcion de mostrar en menu
				// la lista se mostraba erroneamente. 
				//dataFree(&elem);
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case POP_:
			if (returnType(d1)==LIST) {
				elem=POP(&d1);
				printf("Elemento extraido: ");
				printData(elem, 0);
				printf("\n");
				printf("Lista modificada: ");
				printData(d1, 0);
				printf("\n");
				dataFree(&elem);
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case CANT:
			if (returnType(d1)==LIST) {
				printf("Cantidad de elementos de la lista: %d\n",SIZEL(d1));
			} else printf("Tipo de estructura incorrecta para esta operacion\n");
			break;
		case 11:
			automata1 = carga_automata();	
			printf("Automata cargado: \n");
			muestra_automata(automata1);
			printf("\n");
			break;
		case 12:
			if( automata1 != NULL ){
				muestra_automata( automata1 );
			}
			else printf("No se ha cargado un automata\n");
			break;
		case 13:
			if( automata1 != NULL ){
				printf("Ingrese la cadena:");
				leeCad( cadena, TAM_MAX );
				b = acepta_cadena( automata1, cadena );
				if( b == 1 ){
					printf("La cadena es aceptada por el automata\n");
				}
				else if( b == 0 )
					printf("La cadena no es aceptada por el automata\n");
				else
					printf("La cadena no esta compuesta por el alfabeto\n");
			}
			else
				printf("No se ha cargado un automata\n");
			break;
		case 14:
			automata2 = afnd2afd(automata1);	
			muestra_automata(automata2);
			printf("Ingrese la cadena:");
			leeCad(cadena, TAM_MAX);
			b = acepta_cadena(automata2, cadena);
			if( b == 1 ){
				printf("La cadena es aceptada por el automata\n");
			}
			else if( b == 0 )
				printf("La cadena no es aceptada por el automata\n");
			else
				printf("La cadena no esta compuesta por el alfabeto\n");
			break;
		case SALIR:
			printf("¡Ejecucion del programa terminada!¡Hasta pronto!\n");
			break;
		}
		if( rta != 0 ){
			FLUSH
			press_enter();
			CLS
		}
	}while( rta != 0 );
	return 0;
}
int menu(){
	int op;
	printf("***MENU***\n");
	printf("1. Cargar nueva estructura\n");
	printf("2. Mostrar estructura\n");
	printf("OPERACIONES CON CONJUNTOS\n");
	printf("3. Cardinal\n");
	printf("4. Pertenece\n");
	printf("5. Union\n");
	printf("6. Interseccion\n");
	printf("7. Diferencia\n");
	printf("OPERACIONES CON LISTAS\n");
	printf("8. Push\n");
	printf("9. Pop\n");
	printf("10. Cantidad de elementos\n");
	printf("OPERACIONES CON AUTOMATAS\n");
	printf("11. Cargar automata\n");
	printf("12. Muestra el automata\n");
	printf("13. Determinar si una cadena es aceptada por el automata\n");
	printf("14. Convertir AFND a AFD\n");
	printf("0. SALIR\n");
	printf("Su opcion: ");
	scanf("%d",&op);
	CLS
	return op;
}
void press_enter(){
	int c;
	printf("Presione enter para continuar\n");
	while( (c = getchar()) != '\n' );
}
	
