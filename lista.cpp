#include <iostream>
#include <string.h>
#include "nodo.h"
#include "lista.h"

using namespace std;

Lista::Lista(void)
{
	cabeza = NULL;
}

Lista::~Lista(void)
{
	cabeza = NULL;
	free(cabeza);
	cout << "Objeto de Lista borrado." << endl;
}

bool Lista::agregar_elemento(int lugar, struct nodo * n)
{
	if (cabeza == NULL)
	{
		cabeza = n;
		return true;
	}

	if (lugar > dimension())
	{
		cabeza->next = n;
		return true;
	}

	if (dimension() == 1)
	{
		cabeza->next = n;
		return true;
	}

	struct nodo * temporal = cabeza;
	int contador = 0;
	while (temporal->next != NULL)
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
	cabeza = temporal;
	return true;
}

bool Lista::eliminar_elemento(int lugar)
{
	if (cabeza == NULL)
		return false;
	if (lugar > dimension())
		return false;

	cout << "Yendo a sacar al elemento número: " << lugar << endl;

	struct nodo * temporal = cabeza;
	int contador = 0;
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
	cabeza = temporal;
	return true;
}

struct nodo * Lista::obtener_elemento(int lugar)
{
	if (lugar == 0)
		return cabeza;
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

void Lista::imprimir(void)
{
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

struct nodo * Lista::obtener_ultimo(void)
{
	struct nodo * temporal = cabeza;
	while (temporal->next != NULL)
	{
		temporal = temporal->next;
	}
	return (struct nodo *)temporal;
}

void Lista::ordenar(void)
{
	int minimo;

	for (int i=0; i<dimension()-1; i++)
	{
		minimo = i;

		for (int j=i+1; j<dimension(); j++)
		{
			if (obtener_elemento(j)->valor < obtener_elemento(minimo)->valor)
				minimo = j;
		}

		int temporal = obtener_elemento(i)->valor;
		obtener_elemento(i)->valor = obtener_elemento(minimo)->valor;
		obtener_elemento(minimo)->valor = temporal;
	}
}