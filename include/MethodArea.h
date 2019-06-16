/*!
 * \file MethodArea.h
 * \brief Responsável por todas as operações que gerenciam os métodos
 */
#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include "classeLeitorExibidor.h"
#include "ConstantPool.h"
#include "StaticClass.h"
#include <map>
#include <algorithm>
#include <string.h>
#include "Frame.h"
#include "BasicTypes.h"

using namespace std;

/** @class MethodArea
 * @brief Classe responsável por todas as operações que gerenciam os métodos
 */
class MethodArea {
private:
	static map<string, StaticClass*> mapClasses;
	static FrameStack *frameStack;

public:
	static string path;

	/** @fn static StaticClass *obterClass(string)
	 * @brief Retorna referência para classe estática
	 * @param s Nome da classe
	 */
	static StaticClass *obterClass(string);

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
