#ifndef LISTA_H
#define LISTA_H

#include "nodo.h"

enum Ordenador {
	QuickSort,
	MergeSort,
	InsertionSort,
	BubbleSort,
	SelectionSort
};

class Lista
{
public:
	Lista(void);
	~Lista(void);

	bool agregar_elemento(int lugar, struct nodo * n);
	bool eliminar_elemento(int lugar);

	struct nodo * obtener_elemento(int lugar);

	void imprimir(void);
	void ordenar(void);
	void ordenar(enum Ordenador);

	int dimension(void);

private:
	struct nodo * obtener_ultimo(void);
	struct nodo * cabeza;
};

#endif