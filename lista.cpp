/**
 * Definición de la clase Lista.
 *
 * Esta es una clase que permite, a través de una estructura
 * de tipo nodo (definida en nodo.h), permite usar diferentes
 * métodos para agregar elementos nuevos, eliminar un elemento
 * específico, obtener el tamaño de la lista, obtener un
 * elemento de una posición específica, imprimir la lista y lo
 * más importante: ordenar la lista usando diferentes algoritmos
 * de ordenamiento. Por defecto se usa el algoritmo SelectionSort.
 *
 * TODO:
 * Crear un sistema de respaldo al último valor de la lista, antes
 * de realizar cualquier ordenamiento.
 *
 * Fuente de información:
 * https://es.wikipedia.org/wiki/Ordenamiento_por_selecci%C3%B3n
 * https://es.khanacademy.org/computing/computer-science/algorithms
 * 
 */
#include <iostream>
#include <string.h>
#include "nodo.h"
#include "lista.h"

using namespace std;


/**
 * Constructor de la clase.
 */
Lista::Lista(void)
{
	cabeza = NULL;
}


/**
 * Destructor de la clase.
 */
Lista::~Lista(void)
{
	cabeza = NULL;
	free(cabeza);
	cout << "Objeto de Lista borrado." << endl;
}


/**
 * Agrega una estructura nodo en la posición deseada.
 * 
 * @param  lugar lugar donde insertaremos.
 * @param  n     puntero a estructura nodo.
 * @return       true si es exitoso, false si hay problemas.
 */
bool Lista::agregar_elemento(int lugar, struct nodo * n)
{
	if (cabeza == NULL)
	{
		cabeza = n;
		return true;
	}

	if (lugar > dimension())
	{
		obtener_ultimo()->next = n;
		return true;
	}

	if (lugar == 0)
	{
		n->next = cabeza;
		cabeza = n;
		return true;
	}

	if (dimension() == 1)
	{
		cabeza->next = n;
		return true;
	}

	struct nodo * temporal = cabeza;
	int contador = 1;
	while (temporal != NULL)
	{
		if (contador == lugar)
		{
			n->next = temporal->next;
			temporal->next = n;
			break;
		}
		else
		{
			temporal = temporal->next;
			contador++;
		}
	}
	return true;
}


/**
 * Elimina, de la lista, el elemento ubicado en la
 * posición solicitada.
 * 
 * @param  lugar entero del lugar desde donde eliminaremos
 * @return       true si es exitoso, false si la posición solicitada es mayor que la dimensión.
 */
bool Lista::eliminar_elemento(int lugar)
{
	if (cabeza == NULL)
		return false;

	if (lugar > dimension())
		return false;

	if (lugar == 0 && dimension() == 1)
	{
		cabeza = NULL;
		return true;
	}

	if (lugar == 0)
	{
		cabeza = cabeza->next;
		return true;
	}

	cout << "Yendo a sacar al elemento número: " << lugar << endl;

	struct nodo * temporal = cabeza;
	int contador = 1;
	while (temporal->next != NULL)
	{
		if (contador == lugar)
		{
			if (temporal->next->next == NULL)
			{
				temporal->next = NULL;
				break;
			}
			else
			{
				temporal->next = temporal->next->next;
				break;
			}
		}
		temporal = temporal->next;
		contador++;
	}
	return true;
}


/**
 * Retorna una estructura nodo ubicada en la posición
 * solicitada. Si la posición de la cual queremos obtener
 * el nodo, es mayor que la dimensión de la lista, entonces
 * retorna el último.
 * 
 * @param  lugar entero del lugar desde donde queremos
 *               sacar el elemento.
 * @return       estructura de tipo nodo.
 */
struct nodo * Lista::obtener_elemento(int lugar)
{
	// si es cero, sacamos la cabeza.
	if (lugar == 0)
		return cabeza;
	// si el número es mayor que la dimension,
	// retornamos el último.
	if (lugar > dimension())
		return obtener_ultimo();

	struct nodo * temporal = cabeza;
	int contador = 0;

	while (temporal->next != NULL)
	{
		contador++;
		temporal = temporal->next;
		if (contador == lugar)
			return temporal;
	}
}


/**
 * Imprime una representación de la lista.
 */
void Lista::imprimir(void)
{
	// Si no hay nada, imprimimos una lista vacia.
	if (cabeza == NULL)
	{
		cout << "[]" << endl;
		return;
	}

	cout << "[";

	struct nodo * temporal = cabeza;
	cout << temporal->valor;
	if (temporal->next != NULL)
		cout << ", ";

	while (temporal->next != NULL)
	{
		temporal = temporal->next;
		cout << temporal->valor;
		if (temporal->next != NULL)
			cout << ", ";
	}

	cout << "]" << endl;
}


/**
 * Retorna el número de elementos en la lista.
 * 
 * @return  entero
 */
int Lista::dimension(void)
{
	if (cabeza == NULL)
		return 0;

	int contador = 0;
	struct nodo * temporal = cabeza;

	while (temporal->next != NULL)
	{
		temporal = temporal->next;
		contador++;
	}
	return ++contador;
}

/**
 * Retorna el último elemento en la lista.
 * 
 * @return  estructura de tipo nodo.
 */
struct nodo * Lista::obtener_ultimo(void)
{
	struct nodo * temporal = cabeza;
	while (temporal->next != NULL)
	{
		temporal = temporal->next;
	}
	return (struct nodo *)temporal;
}


/**
 * Ordena la lista.
 *
 * Este  método ordena la lista usando el algoritmo de
 * Selection Sort.
 */
void Lista::ordenar(void)
{
	ordenar(SelectionSort);
}


/**
 * Ordena la lista.
 *
 * Este método ordena la lista usando el algoritmo que
 * se le proporsione a través de un enum de tipo
 * Ordenador que puede tener los valor:
 * 
 * QuickSort, MergeSort, InsertionSort, BubbleSort,
 * SelectionSort.
 * 
 * @param ordenador enum Ordenador
 */
void Lista::ordenar(enum Ordenador ordenador)
{
	/**
	 * Si ha elegido SelectionSort:
	 */
	if (ordenador == SelectionSort)
	{
		/**
		 * pivote
		 */
		int minimo;

		for (int i=0; i<dimension()-1; i++)
		{
			minimo = i;

			for (int j=i+1; j<dimension(); j++)
			{
				if (obtener_elemento(j)->valor < obtener_elemento(minimo)->valor)
					minimo = j;
			}

			/**
			 * intercambiamos entre el valor actual y el minimo último
			 */
			int temporal = obtener_elemento(i)->valor;
			obtener_elemento(i)->valor = obtener_elemento(minimo)->valor;
			obtener_elemento(minimo)->valor = temporal;
		}
	}

	/**
	 * Si ha elegido QuickSort:
	 */
	else if (ordenador == QuickSort)
	{
		// Do thing.
	}


	/**
	 * Si ha elegido MergeSort:
	 */
	else if (ordenador == MergeSort)
	{
		// Do thing.
	}


	/**
	 * Si ha elegido InsertionSort:
	 */
	else if (ordenador == InsertionSort)
	{
		if (dimension() == 1)
		{
			// «Toda lista de un elemento, está ordenada por defecto».
			return;
		}

		struct nodo * temporal = cabeza;
		for (int i=0; i<dimension()-1; i++)
		{
			for (int j=i+1; j<dimension(); j++)
			{
				if (obtener_elemento(i)->valor > obtener_elemento(j)->valor)
				{
					struct nodo * sacado = obtener_elemento(j);
					obtener_elemento(j-1)->next = obtener_elemento(j)->next;
					agregar_elemento(i, sacado);
					break;
				}
			}
		}
	}


	/**
	 * Si ha elegido BubbleSort:
	 */
	else if (ordenador == BubbleSort)
	{
		if (dimension() == 1)
			return;

		for (int i=dimension()-1; i>0; i--)
		{
			for (int j=0; j<i; j++)
			{
				if (obtener_elemento(j)->valor > obtener_elemento(j+1)->valor)
				{
					int temporal = obtener_elemento(j)->valor;
					obtener_elemento(j)->valor = obtener_elemento(j+1)->valor;
					obtener_elemento(j+1)->valor = temporal;
				}
			}
		}
	}
}