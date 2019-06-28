/*!
 * \file PilhaJVM.h
 * \brief Contém tudo necessário para a execução de um método.
 */

#ifndef PILHA_JVM_H
#define PILHA_JVM_H

class PilhaJVM;

#include "ClassFile.h"
#include "OperandsStack.h"
#include "LocalVariables.h"
#include "BasicTypes.h"
#include "Operations.h"
#include "Attributes.h"
#include "MethodArea.h"

using namespace std;

/** @struct frame_s
 * @brief Estrutura de armazenamento
 * @brief Responsável por todas as informações necessárias para a execução de um método.
 */
typedef struct frame_s {
	unsigned char *pc;
	Cp_info *constantPool;
	OperandsStack *operandsStack;
	LocalVariables *localVariables;
	Method_info method;
} Frame;

/** @class PilhaJVM
 * @brief Classe de pilha de frames
 * @brief Responsável por todas as operações que usam o frame.
 */
class PilhaJVM {
private:
	stack<Frame*> stackFrame;
	/** @fn bool proximaInstrucao()
	 * @brief Atualiza o PC, se não for possível atualizar, dá um pop no método atual
	 */
	bool proximaInstrucao();

	/** @var int opcode
	 * @brief Contêm o opcode que corresponde a uma instrução.
	 */
	int opcode;

	/** @fn void inicializarPC(frame *frame)
	 * @brief Põe o PC na posição inicial
	 * @param frame Estrutura do tipo frame.
	 */
	void inicializarPC(Frame *frame);
public:
	/** @fn PilhaJVM(ClassFile *classFile)
	 * @brief Contrutor da pilha de frame
	 * @param classFile O que é lido do arquivo .class.
	 */
	PilhaJVM(ClassFile *classFile);

	/** @fn void atualizarArgumentos(vector<typedElement> vectorArgumentos)
	 * @brief Configura os argumentos.
	 * @param vectorArgumentos Vetor com os argumentos a serem copiados para o vetor de variáveis locais
	 */
	void atualizarArgumentos(vector<TypedElement> vectorArgumentos);

	/** @fn void executarMetodos();
	 * @brief Executa o método atual e os métodos chamados.
	 */
	void executarMetodos();

	/** @fn void adicionarFrame(Method_info method, Cp_info *constantPool);
	 * @brief Adiciona um frame no topo da pilha.
	 * @param method Método no qual o frame será criado.
	 * @param constantPool Um ponteiro para o pool de constantes.
	 */
	void adicionarFrame(Method_info method, Cp_info *constantPool);

	/** @fn void adicionarFrame(Method_info *method, Cp_info *constantPool);
	 * @brief Adiciona um frame no topo da pilha.
	 * @param method Ponteiro para o método no qual o frame será criado.
	 * @param constantPool Um ponteiro para o pool de constantes.
	 */
	void adicionarFrame(Method_info *method, Cp_info *constantPool);

	/** @fn void popRemoverObjetos()
	 * @brief Dá um pop no método atual.
	 */
	void popRemoverObjetos();
};

#endif
