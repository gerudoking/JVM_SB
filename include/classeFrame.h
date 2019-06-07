/*!
 * \file classeFrame.h
 * \brief Contém tudo necessário para a execução de um método.
*/

/** @def FRAME 
 * @brief Macro
 * @brief Define uso para evitar a inclusão múltipla de arquivos.
*/
#ifndef FRAME
#define FRAME

class FrameStack;

#include "classeLeitorExibidor.h"
#include "classePilhaOperandos.h"
#include "classeVariaveisLocais.h"
#include "classeTiposBasicos.h"
#include "classeOperacoes.h"
#include "attributes.h"
#include "classeMethodArea.h"

using namespace std;

/** @struct frame_s
 * @brief Estrutura de armazenamento
 * @brief Responsável por todas as informações necessárias para a execução de um método.
*/	
typedef struct frame_s{
	unsigned char *pc;
	cp_info *constantPool;
	PilhaOperandos *pilhaOperandos;
	VariaveisLocais *variaveisLocais;
	method_info method;
} Frame;


/** @class FrameStack
 * @brief Classe de pilha de frames
 * @brief Responsável por todas as operações que usam o frame.
*/	
class FrameStack {
private:
	stack<Frame*> stackThreads;
	/** @fn bool proximaInstrucao()
	 * @brief Atualiza o PC, se não for possível atualizar, dá um pop no método atual
	*/
	bool proximaInstrucao();

	/** @var int opcode
	 * @brief Contêm o opcode que corresponde a uma instrução.
	*/
	int opcode;

	/** @fn void inicializarPC(frame *flame)
	 * @brief Põe o PC na posição inicial
	 * @param frame Estrutura do tipo frame.
	*/
	void inicializarPC(Frame *frame);
public:
	/** @fn FrameStack (LeitorExibidor *leitorExibidor)
	 * @brief Contrutor da pilha de frame
	 * @param leitorExibidor O que é lido do arquivo .class.
	*/
	FrameStack (LeitorExibidor *leitorExibidor);

	/** @fn void atualizarArgumentos(vector<typedElement> vectorArgumentos)
	 * @brief Configura os argumentos.
	 * @param vectorArgumentos Vetor com os argumentos a serem copiados para o vetor de variáveis locais
	*/
	void atualizarArgumentos(vector<TypedElement> vectorArgumentos);

	/** @fn void executarMetodos();
	 * @brief Executa o método atual e os métodos chamados.
	*/
	void executarMetodos();

	/** @fn void adicionarFrame(method_info method, cp_info *constantPool);
	 * @brief Adiciona um frame no topo da pilha.
	 * @param method Método no qual o frame será criado.
	 * @param constantPool Um ponteiro para o pool de constantes.
	*/
	void adicionarFrame(method_info method, cp_info *constantPool);

	/** @fn void adicionarFrame(method_info *method, cp_info *constantPool);
	 * @brief Adiciona um frame no topo da pilha.
	 * @param method Ponteiro para o método no qual o frame será criado.
	 * @param constantPool Um ponteiro para o pool de constantes.
	*/
	void adicionarFrame(method_info *method, cp_info *constantPool);

	/** @fn void pop()
	 * @brief Dá um pop no método atual.
	*/
	void popRemoverObjetos();
};

#endif
