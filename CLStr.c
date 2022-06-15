#include "CLStr.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ESTADOS  1
#define ALFABETO 2
#define DELTA    3
#define INICIAL  4
#define ACEPTACION 5
vec_cadena vec = {
			"Conjunto de Estados:", "Alfabeto:           ",
			"Funcion Delta:      ",
			"Estado inicial:     ",
			"Estados aceptacion: ",
};

/* Operaciones generales y privadas */
void getElem(char**s, char**aux){ 
	char* s_aux;
	int i=0; 
	int cont_abre_l=0;

	int cont_cierra_l=0;

	int cont_abre_c=0;

	int cont_cierra_c=0;

	int j,salir;

	*aux=(char*) malloc(sizeof(char)*1000); 

	s_aux=(char*) malloc(sizeof(char)*1000);

	//verfica si es una lista o conjunto
	if ((*s)[0]!='{' && (*s)[0]!='[') {
		//si es str copia la cadena 
		while ((*s)[i]!='\0' && (*s)[i]!=',') {

			(*aux)[i]=(*s)[i];
			i++;
		}
		(*aux)[i]='\0';
	} else {
		salir=0;
		while ((*s)[i]!='\0' && !salir) {
			(*aux)[i]=(*s)[i];
			switch ((*s)[i]) {
				case '{':
					cont_abre_l++;
					break;
				case '[':
					cont_abre_c++;
					break;	
				case '}':
					cont_cierra_l++;
					break;
				case ']':
					cont_cierra_c++;
					break;
			}
			if (cont_abre_l-cont_cierra_l==0 && cont_abre_c-cont_cierra_c==0) 
				salir=1;
			i++;
		}
		(*aux)[i]='\0';
	}
	i++;
	if (i<strlen(*s)) {
		j=0;
		while ((*s)[i]!='\0'){

			s_aux[j]=(*s)[i];

			j++;

			i++;

		}

		s_aux[j]='\0';

		*s=s_aux;

	} else *s=NULL;

}
// si quiere eliminar solo un elemento, esta obligado a desconectar ese elemento de su siguiente 
void dataFree(struct dataType** d){
	struct dataType *aux;
	aux = (*d);
	if( aux != NULL ){
		if( aux->nodeType == STR ){
			free(aux->dataStr);
			aux->dataStr = NULL;
		}
		else{
			dataFree( &aux->data );
			dataFree( &aux->next );
		}
	}
	free((*d));	
}
char* clean(char* s){
	int i=1;
		char* aux;
		aux=(char*) malloc(sizeof(char)*1000); 
		while (s[i]!='\0'){
			aux[i-1]=s[i];
				i++;
		}
	aux[i-2]='\0';
		return aux;
}
// modulos para la creacion de espacios de memoria 
// para cada tipo de dato.
struct dataType* create_data_str(){
	struct dataType* data;
	data = (struct dataType*)malloc(sizeof(struct dataType));
	data->dataStr = (char*)malloc(sizeof(char)*100);
	data->nodeType = STR;
	return data;
}
struct dataType* create_data_set(){
	struct dataType* data;
	data = (struct dataType*)malloc(sizeof(struct dataType));
	data->nodeType = SET;
	data->next = NULL;
	data->data = NULL;
	return data;
}
struct dataType* create_data_list(){
	struct dataType* data;
	data = (struct dataType*)malloc(sizeof(struct dataType));
	data->nodeType = LIST;
	data->next = NULL;
	data->data = NULL;
	return data;
} 
void ORDENA( struct dataType** S , struct dataType* ant, struct dataType* ult, struct dataType* str ){
	struct dataType *A ,*B = NULL , *C = NULL, *D = NULL;
	int tipo = ult->data->nodeType, band = 0, band2 = 0, band3 = 0;
	A = ( *S );
	//C = A;
	if( ant != ult ){
		if( tipo == STR ){
			while( ( A != NULL ) && ( band == 0 ) ){
				if( A->data->nodeType == STR ){
					if( strcmp( ult->data->dataStr, A->data->dataStr ) < 0 ){
						ult->next = A;
						A = ult;
						ant->next = NULL;
						if(B != NULL ){

							B->next = ult;
						}
						else{
							(*S) = A;
						}
						band = 1;
					}
					else{
						if( strcmp( ult->data->dataStr , A->data->dataStr ) > 0 ){
							B = A;
							A = A->next;
						}
						else
							A = A->next;
					}
				}
				else{
					ult->next = A;
					A = ult;
					ant->next = NULL;
					if(B != NULL ){
						B->next = ult;
					}
					else{
						(*S) = A;
					}
					band = 1;

				}
			}	
		}
		else{
			if( tipo == SET ){
				D = ant;
				if( str != NULL ){
					A = str->next;
					band3 = 1;
				}	
				if( A != ult ){
					if( A->data->nodeType == LIST ){
						while( ( A->data->nodeType == LIST ) && ( A != NULL ) ){
							A = A->next;
						}
					}
					ant = A;
					while( ( A != NULL ) && ( band == 0 ) ){
						if( A != ult ){
							B = A->data;
							C = ult->data;
							band2 = 0;
							while( ( B != NULL ) && ( C != NULL ) && ( band2 == 0 ) ){
								if( strcmp( C->data->dataStr, B->data->dataStr ) < 0 ){
									ult->next = A;
									D->next = NULL;
									if( ant != A ){
										ant->next = ult;
									}
									else{
										if( ( band3 == 1 ) && ( str->next == A ) ){
											str->next = ult;
										}
										else{
											(*S) = ult;
										}
									}
									if( A->next == ult ){
										A->next = NULL;
									}
									band = 1;
									band2 = 1;
								}
								else{
									if( strcmp( C->data->dataStr, B->data->dataStr ) > 0 ){
										ant = A;
										A = A->next;
										band2 = 1;
									}
									else{
										B = B->next;
										C = C->next;
									}
								}
							}
							
							if( band2 == 0 ){
								if( ( C == NULL ) && ( B != NULL ) ){
									//Aqui colocamos al conjunto ultimo antes del analizado
									ult->next = A;
									D->next = NULL;
									if( A == (*S) ){
										(*S) = ult;
									}
					
									else{
										ant->next = ult;
									}
									band = 1;
								}
								else{
									if( ( B == NULL ) && ( C != NULL ) ){
										//Aqui lo ponemos al conjunto ultimo despues del analizado si es que no estaban en ese orden
										if( ant->next != ult ){
											ult->next = ant->next;
											ant->next = ult;
											D->next = NULL;
											band = 1;
										}
										else{
											band = 1;
										}

									}

								}
							}	

						}
						else{
							A = A->next;
						}

					}
				}		
		
			}
			else{
				D = ant;
				if( str != NULL ){
					ant = str;
					A = str->next;
				}	
				if( A != ult ){
					if( A->data->nodeType == LIST ){
						while( ( A->data->nodeType == LIST ) && ( A != ult ) ){
							ant = A;
							A = A->next;
						}
					}
					if( A != ult ){
						ult->next = A;
						if( ( A == ant ) && ( str == NULL ) ){
							(*S) = ult;
						}
						else{
							if( ant != A){
								ant->next = ult;
								D->next = NULL;
							}
						}
						if( A->next == ult ){
							A->next = NULL;
						}
					}	

				}


			}
		}
	}	

}

struct dataType* createData(char *s){
	char *limpia;
	char *elemento;
	int band = 0, band2;
	struct dataType *cab = NULL, *aux, *ant, *grand = NULL, *rep;
	// limpio la cadena y luego extraigo el token
	limpia = clean( s );
	getElem( &limpia, &elemento );
	if( (*s) == '[' ){
		band = LIST;
		cab = create_data_list();
	}
	else if( *s == '{' ){
		band = SET;
		cab = create_data_set();
	}
	aux = cab;
	ant = cab;
/****modificacion******/
	if ( limpia == NULL && elemento[0] == '\0' ){
		elemento = NULL;
	}


	while( elemento != NULL ){
		band2 = 0;

		// controlo la condicion del elemento extraido
		if( elemento[0] == '{' ){
			rep = createData( elemento );
			if( band != LIST ) {
				if( IN( cab, rep ) == 0 ){
					aux->data = rep;
				}
				else{
					band2 = 1;
				}
			}
			else{
				aux->data = rep;
			}
		}
		//a�adido 
		else if( elemento[0] == '[' ){
			aux->data = createData( elemento );
		}
		else{
			rep = create_STR( elemento );
			if( cab->data == NULL ){
				aux->data = rep;
				grand = aux;
			}
			else{
				if( band != LIST ){
					if( IN( cab, rep ) == 0 ){
						aux->data = rep;
						if( grand != NULL ){	
							if( strcmp( grand->data->dataStr, aux->data->dataStr ) < 0 ){
								grand = aux;
							}
						}
						else{
							grand = aux;
						}
					}
					else{
						band2 = 1;
					}
				}
				else{
					aux->data = rep;
				}
			}
		}
		if( ( band != LIST ) && ( band2 == 0 ) ){
			ORDENA( &cab, ant, aux, grand );
		}
		if( limpia != NULL ){
			if( ant->next == NULL ){
				if ( band == SET )
					ant->next = create_data_set();
				else if ( band == LIST )
					ant->next = create_data_list();
				getElem( &limpia , &elemento );
				aux = ant;
			}
			else{
				if ( band == SET )
					aux->next = create_data_set();
				else if ( band == LIST )
					aux->next = create_data_list();
				getElem( &limpia , &elemento );
				ant = aux;
			}	
		}
		else
			elemento = NULL;
		
		aux = aux->next;
	}
	return cab;
}
struct dataType* createData_old(char *s){
	char *limpia;
	char *elemento;
	int band = 0;
	struct dataType *cab = NULL, *aux;
	// limpio la cadena y luego extraigo el token
	limpia = clean( s );
	getElem( &limpia, &elemento );
	if( (*s) == '[' ){
		band = LIST;
		cab = create_data_list();
	//	cab->data = NULL;
	}
	else if( *s == '{' ){
		band = SET;
		cab = create_data_set();
	//	cab->data = NULL;
	}
	aux = cab;
	
	if( limpia == NULL && elemento[0] == '\0' ){
		elemento = NULL;
	}

	while( elemento != NULL ){
		// controlo la condicion del elemento extraido
		if( elemento[0] == '{' ){
			aux->data = createData( elemento );
		}
		//a�adido 
		else if( elemento[0] == '[' ){
			aux->data = createData( elemento );	
		}
		else{
			aux->data = create_data_str();
			strcpy( aux->data->dataStr, elemento );
		}

		if( limpia != NULL ){
			if ( band == SET )
				aux->next = create_data_set();
			else if ( band == LIST )
				aux->next = create_data_list();
			getElem( &limpia , &elemento );
		}
		else
			elemento = NULL;

		aux = aux->next;
	}
	return cab;
}
// Nuevo printData refactorizado.
// Utiliza una bandera para saber cuando imprimir { o [ segun el tipo de dato.
// Es puramente recursivo por lo que se mejoro bastante la lectura y compresion del modulo.
// El registro de cambios queda en el repositorio de github. Por si se quiere ver los antiguis printData.
void printData(struct dataType *node, short flag){
	if(node != NULL){
		if(node->nodeType == STR){// caso base
			printf("%s", node->dataStr);
		}
		else if(node->nodeType == SET){
			if(flag == 0)
				printf("{");
			printData(node->data, 0);
			if(node->next == NULL)
				printf("}");
			else{printf(",");printData(node->next, 1);}
		}
		else if(node->nodeType == LIST){
			if(flag == 0)
				printf("[");
			printData(node->data, 0);
			if(node->next == NULL)
				printf("]");
			else{printf(",");printData(node->next, 1);}
		}
	}
}


struct dataType* create_STR( char *str ){
	struct dataType *d;
	d = create_data_str();
	strcpy( d->dataStr, str );
	return d;
}
/*Operaciones con SET y LIST */
int returnType(struct dataType* CL){
	return CL->nodeType; 
}
struct dataType* copy( struct dataType *a ){
	struct dataType *b = NULL;
	if( a != NULL ){
		if( a->nodeType == SET ){
			b = create_data_set();	
			b->data = copy( a->data );
			b->next = copy( a->next );
		}
		else if( a->nodeType == LIST ){
			b = create_data_list();
			b->data = copy( a->data );
			b->next = copy( a->next );
		}
		else if( a->nodeType == STR ){
			return create_STR( a->dataStr ); 
		}
	}
	return b;
}
struct dataType* retorna_cola( struct dataType* d ){
	while( d->next != NULL )
		d = d->next;
	return d;
}
struct dataType* returnElem(struct dataType* CL, int pos);
/*Operaciones con SET */
int CARDINAL(struct dataType* S){
	int c = 0;
	// para el caso en que cad == "{}"
	// en ese caso S == NULL
	if( S->nodeType == LIST ){
		return -1;
	} else{
		while( S != NULL ){
			if( S->data != NULL )
				c++;
			S = S->next;
		}
	}
	return c;
}
/*Operacions con LIST*/
/* LIST */
void PUSH(struct dataType* L, struct dataType* elem){
	if( L->data != NULL && L->next != NULL ){
		while(L->next != NULL){
			L = L->next;
		}
		L->next = create_data_list();
		L = L->next;
		L->data = elem;
	}	
	else{
		printf( "Lista vacia, queda conformada solo por el elemento.\n" );
		L->data = elem;
	}	
}
/* Breve descripcion. 
 POP debe eliminar el primer elemento de una lista.
 Se le pasa por parametro la cabeza.
 A partir del if se realiza esta operacion. Muevo mi cabeza original al
 segundo elemento, luego el primer nodo se lo desconecta, poniendo sus hijos en NULL, antes resguardando en elem el hijo data. Lo siguiente es dataFree() al primer nodo. Es decir se elimina el nodo de la jerarquia no el nodo del dato. */
struct dataType* POP(struct dataType** L){
	struct dataType *aux, *elem;
	aux = (*L);
	if(aux->data != NULL && aux->next != NULL){
		(*L) = (*L)->next;
		elem = aux->data;
		aux->data = NULL;
		aux->next = NULL;
		dataFree(&aux);
		return elem;
	}
	return NULL;
}
int SIZEL(struct dataType* L){
	int cant = 0;
	if( L->data == NULL && L->next == NULL ){
		printf( "Lista vacia.\n" );
		return cant;
	}
	else{
		while( L->next != NULL ){
			cant = cant + 1;
			L = L->next;
		}
		return cant + 1;
	}

}
int COMPARE_LIST( struct dataType* list1, struct dataType *list2 ){
	struct dataType *d1, *d2;

	if( list1 != NULL && list2 != NULL ){	
		d1 = list1->data;
		d2 = list2->data;
		if( d1 != NULL && d2 != NULL ){ 
			if( d1->nodeType == STR && d2->nodeType == STR ){
				if( strcmp( d1->dataStr, d2->dataStr ) == 0 ){
					return COMPARE_LIST( list1->next, list2->next );
				}
			}
			else if( d1->nodeType == SET && d2->nodeType == SET ){
				if( COMPARE_LIST( list1->data, list2->data ) ){
					return COMPARE_LIST( list1->next, list2->next );	
				}
			}
			else if( d1->nodeType == LIST && d2->nodeType == LIST ){
				if( COMPARE_LIST( list1->data, list2->data ) ){
					return COMPARE_LIST( list1->next, list2->next );
				}
			}
		}
		else if( d1 == NULL && d2 == NULL )
			return 1;
	}
	else if( list1 == NULL && list2 == NULL )
		return 1;

	return 0;
}
// ====================================================
/*OPERACIONES CON SET */
/* 
IN se encarga de determinar si un elemento pertenece a un conjunto
elemento pude ser LIST, STR o SET; pero si o si la structura de 
primer nivel debe ser un SET
 */
int es_vacio( struct dataType* C ){
	if( C->nodeType == SET ){
		if( C->data == NULL && C->next == NULL )
		return 1;
	}
	return 0;
}
int IN(struct dataType* S, struct dataType* elem){
	int tipo = elem->nodeType, c = 0;
	struct dataType *d, *aux;
	if( S == NULL && elem == NULL )
		return 1;
	//while para recorrer el conjunto o nivel correspondiente, a la instancia del modulo
	while( S != NULL ){
		//me fijo en el tipo de dato de la izq
		d = S->data;
		if( d != NULL ){
			if(elem->data != NULL){
				if( d->nodeType == tipo ){
					if( tipo == STR ){
						if( strcmp( d->dataStr, elem->dataStr ) == 0 ){
							return 1;
						}
					}
					else if( tipo == SET  ){
						aux = elem;
						c = 0;
						while( aux != NULL ){
							if( IN( d, aux->data ) == 1 ){
								aux = aux->next;
								c++;
							}else
								break;
						}
						if( aux == NULL && (CARDINAL(d) == c ) ){
							return 1;
						}
					}
					else if( tipo == LIST ){
						return COMPARE_LIST( d, elem );	
					}
				}
			}
			else if( d->data == NULL && elem->data == NULL )
				return 1;
		}
		S = S->next;
	}
	/* } */
	return 0;
}
// modulos a ubicar
// Copia struct dataType *a, en un nuevo espacio de memoria y retorna un puntero a ese espacio.

// aqui quede

/*
para tener en cuenta, en la listas no se deben eliminar repetidos
solo en un conjunto se eliminan listas que son iguales
 */
struct dataType* elimina_repetidos( struct dataType* cab ){
	struct dataType *aux, *ant, *d;	
	aux = ant = (cab);
	while( aux != NULL ){
		d = aux->data;// d apunta al hijo izq
		if ( d != NULL ){
			if( d->nodeType == SET ){
				aux->data = elimina_repetidos( d );	
			}
			
			if( aux->next != NULL ){
				
				if( IN( aux->next, aux->data ) ){
					if( aux == (cab) ){
						(cab) = aux->next;
						aux->next = NULL;//debo hacer esto porque dataFree va por izq y por derecha
						dataFree( &aux );
						ant = aux = (cab);
					}
					else{
						ant->next = aux->next;
						aux->next = NULL;
						dataFree( &aux );
						aux = ant->next;
					}
				}
				else{
					ant = aux;
					aux = aux->next;	
				}
			}
			else{
				ant = aux;
				aux = aux->next;
			}
		}
		else{
			ant = aux;
			aux = aux->next;
		}
	
	}
	return cab;
}
struct dataType* UNION( struct dataType* A, struct dataType* B ){
	// si alguno de los punteros es null lo tomare como que nos es un elemento
	// con el que se pueda operar, por ejemplo; A != NULL y B == NULL, entonces no se
	// puede operar, retorno NULL
	if( A != NULL && B != NULL ){
		if( es_vacio(A) ){
			return copy( B );
		}
		else if( es_vacio(B) ){
			return copy( A );
		}
		A = copy( A );
		B = copy( B );
		retorna_cola( A )->next = B;
		A = elimina_repetidos( A );
	}
	else
		return NULL;
	return A;
}
struct dataType* INTER( struct dataType* A, struct dataType* B){
	struct dataType *C, *aux; 
	aux = C = create_data_set();
	while( A != NULL ){
		if( IN( B, A->data) ){
			if( C->data != NULL ){
				C->next = create_data_set();
				C = C->next;
			}
			C->data = copy( A->data );
		}	
		A = A->next;
	}
	return aux;
}
struct dataType* DIFF( struct dataType* A, struct dataType* B ){
	struct dataType *C, *aux;
	aux = C = create_data_set();
	while( A != NULL ){
		if( IN( B, A->data) == 0 ){
			if( C->data != NULL ){
				C->next = create_data_set();
				C = C->next;
			}
			C->data = copy( A->data );
		}	
		A = A->next;
	}
	return aux;
}
// ============================================
// MODULOS PARA AUTOMATAS
void muestra_ternasSaltadas( struct dataType *C ){
	printf("\n");
	while( C != NULL ){
		printData(C->data, 0);
		printf("\n");
		C = C->next;
	}
}
void muestra_automata( struct dataType* automata ){
	int i;
	for( i = 0; i <= 4; i++ ){
		printf("%s", vec[i]);// contiene las etiquetas o nombres de cada elemento del AF
		if( i != 2 ){
		printData(automata->data, 0);
		printf("\n");
		}
		else
			muestra_ternasSaltadas( automata->data );
		automata = automata->next;
	}
}
void leeCad(char cadena[], int tam){
	int j, m;
	/*obtener el primer caracter del stdin*/
	m=getchar();
	/*ANALIZAR EL PRIMER CARACTER LE�DO*/
	if (m!=EOF) { /*si el primer caracter no es fin de archivo*/
		
		/*inicializacion del �ndice que maneja el vector de char*/
		j=0;
		/*si el primer caracter leido no es un enter, se lo guarda en la cadena*/
		if (m!='\n'){ 
			cadena[j]=m; 
			j++;
		}
		/*LEER DEL SEGUNDO CARACTER EN ADELANTE*/
		/*leer el resto de los caractaeres y ponerlos en el vector de char*/
		m=getchar();
		while (j<tam-1 && m!=EOF && m!='\n') {
			cadena[j]=m;
			m=getchar();
			j++;
		}
		/*agregar marca de fin de cadena*/
		cadena[j]='\0';
		
		/*vaciar la pila*/
		while(m!=EOF && m!='\n')
			m=getchar();
		
	} else {
		/*si se lee el fin del archivo en el primer caracter, no hay cadena*/
		/*solo poner la marca de fin de cadena*/
		cadena[0]='\0';
	}
	
}
struct dataType* carga_automata(){
	struct dataType *automata;
	char cadena[4200];
	/* char estados[1000], alfabeto[1000], delta[100], estado_ini[100], estados_aceptacion[1000]; */
	/* FLUSH */
	/* printf("Ingrese el conjunto de estados\n"); */
	/* leeCad(	estados, 1000 ); */
	/* printf("Ingrese el alfabeto\n"); */
	/* leeCad( alfabeto, 1000 ); */
	/* printf("Ingrese delta\n"); */
	/* leeCad( delta, 100 ); */
	/* printf("Ingrese el estado inicial\n"); */
	/* leeCad( estado_ini, 100 ); */
	/* printf("Ingrese los estados de aceptacion\n"); */
	/* leeCad( estados_aceptacion, 1000 ); */
	/* sprintf(cadena, "[%s,%s,%s,%s,%s]",estados, alfabeto, delta, estado_ini, estados_aceptacion); */
	// automata pre-cargado, comentar lineas 910 a 922  
	strcpy(cadena,
			"[{q0,q1,q2,q3,q4,q5},{0,1},{[q0,0,{q0}],[q0,1,{q0,q1,q2}],[q1,0,{q2,q3}],[q1,1,{}],[q2,0,{}],[q2,1,{q4}],[q3,0,{q5}],[q3,1,{}],[q4,0,{}],[q4,1,{q5}],[q5,0,{q5}],[q5,1,{q5}],[{},0,{}],[{},1,{}]},q0,{q5}]");
	automata = createData_old(cadena);
	return automata;
}
// retorna un elemento de la upla que contiene a automata
struct dataType* return_upla( struct dataType *nivel, int elem ){
	int i = 1;
	while( i < elem && nivel != NULL ){
		nivel = nivel->next;
		i++;
	}
	return nivel->data;
}
// verifica si una cadena pertenece a un alfabeto.
int verifica_cadena( char * cadena, struct dataType* alfabeto ){
	// Se utiliza una cadena que sirve para cargarle caracter por caracter de la cadena recibida 
	char caracter[2]; 
	int i = 0;
	struct dataType *aux_str_node; // nodo auxiliar
	// se acomodaron mejor las lineas de este modulo para mejorar su legibilidad.

	// se crea un nodo STR para colocarle el caracter extraido de la cadena.
	// importante cambio. Solo se crea una sola vez, y no en cada vuelta del ciclo.
	aux_str_node = create_STR("");
	caracter[1] = '\0'; 
	while( cadena[i] != '\0' ){// recorro hasta el fin de cadena.
		caracter[0] = cadena[i];	
		strcpy(aux_str_node->dataStr, caracter);
		if(IN(alfabeto, aux_str_node) == 0){ // luego ese mismo se utiliza para preguntar si pertenece al alfabeto
			dataFree(&aux_str_node);// si no pertenece se termina la ejecucion del modulo, se elimina el nodo auxiliar
			return 0;
		}
		i++;
	}
	dataFree(&aux_str_node);//	
	return 1;
}

struct dataType* delta( struct dataType *estado, struct dataType* ternas, char* caracter ){
	struct dataType* q;

	if(estado != NULL){
			// printf("estado:");
			// printData(estado);
			// printf("caracter:%s\n",caracter);
		while( ternas != NULL ){
			q = ternas->data;	
			if( strcmp( q->data->dataStr, estado->dataStr) == 0 && strcmp( q->next->data->dataStr, caracter) == 0 ){
				return q->next->next->data;
			}
			ternas = ternas->next;
		}	
	}
	return create_data_set();
}
struct dataType* delta_extend( struct dataType* estado, struct dataType* ternas, char* cadena, int p ){
	char caracter[2]; caracter[1] = '\0'; caracter[0] = cadena[p];
	struct dataType *_union;
	if( cadena[p] == '\0' ){
		return estado;
	}
	else{
		if( estado->nodeType == STR ){
			p = p + 1;//nota: no incrementar cuando este como parametro x'D
			return delta_extend( delta( estado, ternas, caracter ), ternas, cadena, p );	
		}
		else if( estado->nodeType == SET ){
			// printf("estado conj");
			// printData(estado);
			// printf("\n");
			_union = create_data_set();// para que sea un conj vacio, para poder realizar la union
			while( estado != NULL ){
				_union = UNION( _union, delta( estado->data, ternas, caracter ) );
				estado = estado->next;
			}
			p = p + 1;
			return delta_extend( _union, ternas, cadena, p );
		}
	}
	return NULL;//añadido para solucionar warning, por falta de un caso de retorno
}
int acepta_cadena( struct dataType *automata, char* cadena ){
	struct dataType *aux; 
	if(verifica_cadena( cadena, return_upla(automata, ALFABETO)) == 0){
		return -1;
	}
	aux = delta_extend(return_upla(automata,INICIAL),return_upla(automata,DELTA),cadena,0);
	if( aux->nodeType == STR ){
		if( IN( return_upla( automata, ACEPTACION ), aux )){
			return 1;
		}
		else 
			return 0;
	}
	else{
		if( es_vacio(INTER( return_upla( automata, ACEPTACION), aux )) )
			return 0;
		else
			return 1;
	}

}

int COMPARA_CONJ( struct dataType *A, struct dataType *B ){
	struct dataType *aux;
	int c = 0;
	aux = A;
	while( aux != NULL ){
		if(IN( B, aux->data ) ){
			aux = aux->next;
		}
		else
			break;
		c++;
	}
	if( aux == NULL ){
		if( c == CARDINAL( B ) )
			return 1;
	}
	return 0;
}

/* conversion afnd a afd */
struct dataType* deltaB( struct dataType *estado_conj, struct dataType *ternas, char* caracter ){
	struct dataType *q;
	if( es_vacio( ternas ) == 0 ){
		while( ternas != NULL ){
			q = ternas->data;
			if( COMPARA_CONJ( q->data, estado_conj ) && strcmp( q->next->data->dataStr, caracter ) == 0 ){
				return q->next->next->data;
			}
			ternas = ternas->next;
		}
	}
	return NULL;
}
struct dataType* crea_terna( struct dataType* entrada,struct dataType *str, struct dataType *salida ){
	struct dataType *cab, *aux;
	
	cab = aux = create_data_list();
	cab->data = copy(entrada);
	for( int i = 1; i < 3; i++ ){
		aux->next = create_data_list();
		aux = aux->next;
	}
	cab->next->data = copy(str);
	aux->data = copy(salida);
	return cab;
}
struct dataType* afnd2afd( struct dataType* A ){
	struct dataType *B, *aux;
	struct dataType *estadosB, *inicial, *P;
	struct dataType *alfabeto, *ternas, *nuevo, *aceptA, *inter ;
	char * caracter;
	B = create_data_list();
	aux = B;
	for( int i = 1; i < 5; i++ ){
		aux->next = create_data_list();
		aux = aux->next;
	}
	//coloco inicial 
	inicial = create_data_set();
	inicial->data = copy(return_upla(A,INICIAL));
	B->next->next->next->data = inicial;
	B->data = create_data_set();
	B->data->data = copy(inicial);
	estadosB = B->data;
	//estadosB = B->data = create_data_set()->data = copy( inicial );
	//coloco el alfabeto 
	alfabeto = B->next->data = copy( return_upla(A, ALFABETO) );
	//coloco delta (conjunto de transiciones)
	ternas = B->next->next->data = create_data_set();

	
	while( estadosB != NULL /*&& deltaB(P, ternas, alfabeto->data->dataStr) == NULL*/ ){
		alfabeto = B->next->data;
		while( alfabeto != NULL ){
			P        = estadosB->data;
			caracter = alfabeto->data->dataStr;
			nuevo    = create_data_set();
			while( P != NULL ){
				nuevo = UNION( nuevo, delta( P->data, return_upla( A, DELTA ), caracter ));
				P = P->next;
			}
			ternas->data = crea_terna( estadosB->data, alfabeto->data, nuevo );

			ternas->next = create_data_set();
			ternas = ternas->next;	
			if( IN( B->data, nuevo ) == 0 ){
				aux = create_data_set();
				aux->data = nuevo;
				nuevo = aux;
				aux = retorna_cola( B->data );	
				aux->next = nuevo;
			}
			alfabeto = alfabeto->next;
		}
		estadosB = estadosB->next;
	}
	if( ternas->data == NULL && ternas->next == NULL ){
		dataFree( &ternas );
	}
	B->next->next->next->next->data = create_data_set();
	P = B->next->next->next->next; 	
	estadosB = B->data;

	aceptA = return_upla(A, ACEPTACION);
	while( estadosB != NULL ){
		inter = INTER( estadosB->data, aceptA ); // uso otra var para despues poder borrar
		if( es_vacio( inter ) == 0 ){
			nuevo       = create_data_set();
			nuevo->data = copy( estadosB->data );
			aux = P->data; 
			P->data = UNION( P->data, nuevo );
			dataFree( &aux );
		}
		dataFree( &inter );
		estadosB = estadosB->next;
	}
	return B;
}
