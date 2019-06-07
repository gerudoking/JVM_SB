/** \file classeOperacoes.h
*	\brief
*/
#ifndef OPERACOES
#define OPERACOES

#include "classeEstatica.h"
#include "classeFrame.h"
#include "classeLeitorExibidor.h"
#include "classeMethodArea.h"

using namespace std;

typedef void (*funcaoGenerica)(void);

class Operacoes {
private:

	/** @fn uint32_t obterNBytesValue(uint8_t n, unsigned char** code)
	 * @brief Function that returns a n bytes value
	 * @param n Defines how many positions will be shifted and many bytes will be read.
	 * @param pc Pointer to pc.
	 */
	static uint32_t obterNBytesValue(uint8_t n, unsigned char** pc);

	/** @fn ClasseEstatica* obterStaticClassThatHasField(ClasseEstatica* base, string field_name)
	 * @brief Recursively search for a static class that contains specific field.
	 * @param base ClasseEstatica that is the base for searching field, caso o campo nao seja encontrado nessa classe, go to SuperClasse.
	 * @param field_name Name of field to will be searched.
	 */
	static ClasseEstatica* obterStaticClassThatHasField(ClasseEstatica* base, string field_name);

	static n_array* obterNewMultiArray(stack<int> stackDimessoes);
	static double obterValor(n_array array, stack<int> stackIndeces);

	static bool isWide;
	static struct frame_s *flame;
	static stack<struct frame_s*> *stackThreads;
	static FrameStack *frameStack;
	//tem que adicionar os operandos aqui pra todas as funcoes terem a mesma assinatura


	const static funcaoGenerica funcaoGenericaOpcodes[];
public:
	Operacoes(struct frame_s *flame);

	static void atualizarFrame(struct frame_s *flame);
	static void atualizarThreads(stack<struct frame_s*> *stackThreads);
	static void atualizarFrameStack(FrameStack *frameStack);

	static void executarOperacao(int opcode);
};

#endif
