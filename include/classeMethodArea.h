/*!
 * \file classeMethodArea.h
 * \brief Responsável por todas as operações que gerenciam os métodos
 */
#ifndef METHOD_AREA
#define METHOD_AREA

#include "classeLeitorExibidor.h"
#include "constantPool.h"
#include "classeEstatica.h"
#include <map>
#include <algorithm>
#include <string.h>
#include "classeFrame.h"
#include "classeTiposBasicos.h"

using namespace std;

/** @class MethodArea
 * @brief Classe responsável por todas as operações que gerenciam os métodos
 */
class MethodArea {
private:
	static map<string, ClasseEstatica*> mapClasses;
	static FrameStack *frameStack;

public:
	static string path;

	/** @fn static ClasseEstatica *obterClass(string)
	 * @brief Retorna referência para classe estática
	 * @param s Nome da classe
	 */
	static ClasseEstatica *obterClass(string);

	/** @fn static bool adicionarClasse(string classe)
	 * @brief Carrega a classe na memória
	 * @param classe Nome da classe
	 */
	static bool adicionarClasse(string classe);

	/** @fn static bool adicionarClass(LeitorExibidor *leitorExibidor)
	 * @brief Carrega classe na memória
	 * @param leitorExibidor informação do arquivo .class na memória
	 */
	static bool adicionarClasse(LeitorExibidor *leitorExibidor);

	/** @fn static void atualizarFrameStack(FrameStack *novoFrameStack)
	 * @brief Atualiza a referência da pilha de frames para o próximo frame
	 * @param novoFrameStack próximo frame
	 */
	static void atualizarFrameStack(FrameStack *novoFrameStack);
};

#endif
