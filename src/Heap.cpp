/*!
 * \file Heap.cpp
 * \brief
 */

#include "Heap.h"

vector<InstanceClass*> Heap::vectorInstanceClass;

void Heap::adicionarInstancia(InstanceClass *instanceClass) {
	vectorInstanceClass.push_back(instanceClass);
}
