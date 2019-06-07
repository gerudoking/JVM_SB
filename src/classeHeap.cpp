/*!
 * \file classeHeap.cpp
 * \brief
 */

#include "classeHeap.h"

vector<ClasseInstancia*> Heap::vectorInstancia;

void Heap::adicionarInstancia(ClasseInstancia *classeInstancia) {
	vectorInstancia.push_back(classeInstancia);
}
