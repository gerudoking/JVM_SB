/*!
 * \file classeHeap.h
 * \brief Gerencia a execução do heap.
 */

/** @def HEAP 
 * @brief Macro
 * @brief Define uso para evitar a inclusão múltipla de arquivos.
 */
#ifndef HEAP
#define HEAP

#include "classeInstancia.h"
#include <vector>

using namespace std;

/** @class Heap
 * @brief Classe do heap
 * @brief Gerencia as operações do heap.
 */
class Heap {
private:
	static vector<ClasseInstancia*> vectorInstancia;

public:
	/** @fn static void adicionarInstancia(ClasseInstancia *classeInstancia)
	 * @brief Adiciona novo objeto no heap.
	 * @param classeInstancia - ponteiro para o novo objeto.
	 */
	static void adicionarInstancia(ClasseInstancia *classeInstancia);
};

#endif
