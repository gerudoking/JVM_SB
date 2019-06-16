/*!
 * \file Heap.h
 * \brief Gerencia a execução do heap.
 */

/** @def HEAP 
 * @brief Macro
 * @brief Define uso para evitar a inclusão múltipla de arquivos.
 */
#ifndef HEAP_H
#define HEAP_H

#include "Instance.h"
#include <vector>

using namespace std;

/** @class Heap
 * @brief Classe do heap
 * @brief Gerencia as operações do heap.
 */
class Heap {
private:
	static vector<Instance*> vectorInstancia;

public:
	/** @fn static void adicionarInstancia(Instance *classeInstancia)
	 * @brief Adiciona novo objeto no heap.
	 * @param classeInstancia - ponteiro para o novo objeto.
	 */
	static void adicionarInstancia(Instance *classeInstancia);
};

#endif
