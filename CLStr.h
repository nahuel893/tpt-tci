#ifndef CLSTR_H
#define CLSTR_H
#define STR 1
#define SET 2
#define LIST 3

#define ESTADOS  1
#define ALFABETO 2
#define DELTA    3
#define INICIAL  4
#define ACEPTACION 5

#ifdef __WIN32__
#define FLUSH fflush(stdin);
#define CLS system("cls");
#define STR_VACIO "vacio" 
#define STR_IN    "pertenece"
#define STR_IN_NO "no pertenece"
#define STR_INTER "^"
#define STR_UNION "U"
#elif __linux__
// macros para unicode
#define STR_VACIO "\u2205" 
#define STR_IN    "\u2208"
#define STR_IN_NO "\u2209"
#define STR_INTER "\u2229"
#define STR_UNION "\u222a"

#include <stdio_ext.h>
#define FLUSH __fpurge(stdin);
#define CLS system("clear");
#endif
// definicion de un vector de cadenas para guardar salidas para el automata
typedef char* vec_cadena[6];

struct dataType{
	int nodeType;// == STR
	union{
		char *dataStr;
		struct{
			struct dataType *data;
			struct dataType *next; 
		};
	};
};
void leeCad(char cadena[], int tam);
/*operaciones generales*/
//a partir de una cadena dada por el usuario, crea un nuevo dato (STR, SET o LIST)
//considerar la posibilidad que un conjunto o lista pueden ser vac�as
struct dataType* createData(char *s);
//elimina un dato
void dataFree(struct dataType** d);
//imprime un dato por pantalla
void printData(struct dataType* d);

/*operaciones con SET y LIST*/
/*Desde lo concpetual no pueden acceder a los elementos de los conjuntos usando
posiciones porque no tienen orden. Pero la mayor�a de los lenguajes de prog 
tratan a los conjuntos como vectores y tienen habilitadas funciones que no son 
propias de conjuntos desde el punto de vista matem�tico pero que son muy �tiles 
para resolver problemas computacionales que modelan conjuntos*/

struct dataType* returnElem(struct dataType* CL, int pos);

// crea un str simple
struct dataType* create_STR( char *str );
//retorna tipo de dato
int returnType(struct dataType* CL);

/*operaciones con LIST*/
//todas las operciones retornan -1 o NULL cundo no corresponde el tipo 
//agrega un elemento a la lista por el final, la lista no es con par�metro por 
//ref porque si o si se inicia con un puntero que puede o no tener sus hijos 
//nulos (ambos nulos es lista vac�a
void PUSH(struct dataType* L, struct dataType* elem);
//elimina el �ltimo elemento de la lista y lo devuelve como salida
struct dataType* POP(struct dataType** L); 
//retorna el tama�o de la lista
int SIZEL(struct dataType* L); 

/*operaciones con SET*/
//todas las operciones retornan -1 o NULL cundo no corresponde el tipo 
//calcula la cantidad de elementos de un conjunto
int CARDINAL(struct dataType* S);
//determina si un elemento pertenece a un conjunto
int IN(struct dataType* S, struct dataType* elem);
//genera un nuevo conjunto que resulta de la uni�n de dos conjuntos
struct dataType* UNION(struct dataType* A,struct dataType* B);
//genera un nuevo conjunto que resulta de la intersecci�n de dos conjuntos
struct dataType* INTER(struct dataType* A,struct dataType* B);
//genera un nuevo conjunto que resulta de la diferencia de dos conjuntos
struct dataType* DIFF(struct dataType* A,struct dataType* B);
/*operaciones para automatas*/
struct dataType * carga_automata();
void muestra_automata( struct dataType * automata );
int acepta_cadena( struct dataType* automata, char *cadena );  
struct dataType* afnd2afd( struct dataType* A );
#endif
