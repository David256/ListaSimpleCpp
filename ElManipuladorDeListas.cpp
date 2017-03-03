#include <iostream>
#include <time.h>
#include "lista.h"

/* Mmm... Manipulador Mmmm... */

/*
* Este código hace uso de la clase Lista
* @author David256 (en github)
*
*/

using namespace std;

int main(int argc, char** argv) {
	// iniciamos los números aleatorios :D
	srand(time(NULL));

	// definimos algunas variables/objetos
	Lista lista;
	int dim;

	// pedimos datos
	cout << "Dime la dimensión de la lista: ";
	cin >> dim;

	cout << "Ok, tamaño de: " << dim << endl;

	// creamos nuevos punteros a estructuras nodos y
	// lo agregamos al objeto lista.
	for (int i=0; i<dim; i++)
	{
		struct nodo * n = (struct nodo *) malloc(16);
		n->valor = (int) rand() % (1000);
		n->next = NULL;
		bool exito = lista.agregar_elemento(0, n);
	}

	// imprimimos en pantalla la lista, tal cual.
	lista.imprimir();

	cout << endl << "Ahora la ordeno:" << endl;

	// ordenamos, usando un algoritmo que no recuerdo
	// el nombre :'v
	lista.ordenar();

	lista.imprimir();

	return 0;
}