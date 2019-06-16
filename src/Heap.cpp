/*!
 * \file Heap.cpp
 * \brief
 */

#include "Heap.h"

vector<Instance*> Heap::vectorInstancia;

void Heap::adicionarInstancia(Instance *classeInstancia) {
	vectorInstancia.push_back(classeInstancia);
}
