/*!
 * \file Heap.cpp
 * \brief
 */

#include "Heap.h"

vector<InstanceClass*> Heap::vectorInstancia;

void Heap::adicionarInstancia(InstanceClass *classeInstancia) {
	vectorInstancia.push_back(classeInstancia);
}
