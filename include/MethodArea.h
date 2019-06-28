/*!
 * \file MethodArea.h
 * \brief Responsável por todas as operações que gerenciam os métodos
 */
#ifndef METHOD_AREA_H
#define METHOD_AREA_H

#include "StaticClass.h"
#include <map>
#include <algorithm>
#include <string.h>

#include "BasicTypes.h"
#include "ClassFile.h"
#include "ConstantPool.h"
#include "PilhaJVM.h"

using namespace std;

/** @class MethodArea
 * @brief Classe responsável por todas as operações que gerenciam os métodos
 */
class MethodArea {
private:
	static map<string, StaticClass*> mapStaticClass;
	static PilhaJVM *pilhaJVM;

public:
	static string path;

	/** @fn static StaticClass *obterClass(string)
	 * @brief Retorna referência para classe estática
	 * @param classe Nome da classe
	 */
	static StaticClass *obterClass(string classe);

	/** @fn static bool adicionarClasse(string classe)
	 * @brief Carrega a classe na memória
	 * @param classe Nome da classe
	 */
	static bool adicionarClasse(string classe);

	/** @fn static bool adicionarClasse(ClassFile *classFile)
	 * @brief Carrega classe na memória
	 * @param classFile informação do arquivo .class na memória
	 */
	static bool adicionarClasse(ClassFile *classFile);

	/** @fn static void atualizarPilhaJVM(FrameStack *pStackFrame)
	 * @brief Atualiza a pilha referência da pilha da jvm para o próximo instrução
	 * @param pPilhaJVM a pilha da jvm
	 */
	static void atualizarPilhaJVM(PilhaJVM *pPilhaJVM);
};

#endif
