/*!
 * \file operacoes.cpp
 * \brief
 */

#include "Operations.h"

Frame *Operations::flame = nullptr;
stack<struct frame_s*> *Operations::stackThreads = nullptr;
FrameStack *Operations::frameStack = nullptr;
bool Operations::isWide = false;


Operations::Operations(struct frame_s *flame) {
	this->flame = flame;
}

uint32_t Operations::obterNBytesValue(uint8_t n, unsigned char** pc) {
	uint32_t value = **pc;
	*pc += 1;

	for (int i = 1; i < n; i++) {
		value = (value << 8) | **pc;
		*pc += 1;
	}

	return value;
}

void Operations::atualizarFrame(struct frame_s *pFlame) {
	flame = pFlame;
}

void Operations::atualizarThreads(stack<struct frame_s*> *pStackThreads) {
	stackThreads = pStackThreads;
}

void Operations::atualizarFrameStack(FrameStack* pFrameStack) {
	frameStack = pFrameStack;
}

void Operations::executarOperacao(int opcode) {
	// implementar a função generica para os opcodes das operações
	//funcaoGenericaOpcodes[opcode]();
}
