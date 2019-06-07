/*!
 * \file operacoes.cpp
 * \brief
 */

#include "classeOperacoes.h"

Frame *Operacoes::flame = nullptr;
stack<struct frame_s*> *Operacoes::stackThreads = nullptr;
FrameStack *Operacoes::frameStack = nullptr;
bool Operacoes::isWide = false;


Operacoes::Operacoes(struct frame_s *flame) {
	this->flame = flame;
}

uint32_t Operacoes::obterNBytesValue(uint8_t n, unsigned char** pc) {
	uint32_t value = **pc;
	*pc += 1;

	for (int i = 1; i < n; i++) {
		value = (value << 8) | **pc;
		*pc += 1;
	}

	return value;
}

void Operacoes::atualizarFrame(struct frame_s *pFlame) {
	flame = pFlame;
}

void Operacoes::atualizarThreads(stack<struct frame_s*> *pStackThreads) {
	stackThreads = pStackThreads;
}

void Operacoes::atualizarFrameStack(FrameStack* pFrameStack) {
	frameStack = pFrameStack;
}

void Operacoes::executarOperacao(int opcode) {
	// implementar a função generica para os opcodes das operações
	//funcaoGenericaOpcodes[opcode]();
}
