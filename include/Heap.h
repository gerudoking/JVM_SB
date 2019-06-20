/*!
 * \file Heap.h
 * \brief Gerencia a execução do heap.
 */


#ifndef HEAP_H
#define HEAP_H

#include <vector>

#include "InstanceClass.h"

using namespace std;

/** @class Heap
 * @brief Classe do heap
 * @brief Gerencia as operações do heap.
 */
class Heap {
private:
	static vector<InstanceClass*> vectorInstancia;

public:
	/** @fn static void adicionarInstancia(Instance *classeInstancia)
	 * @brief Adiciona novo objeto no heap.
	 * @param classeInstancia - ponteiro para o novo objeto.
	 */
	static void adicionarInstancia(InstanceClass *classeInstancia);
};

#endif
