/*!
 * \file Frame.cpp
 * \brief
 */

#include "Frame.h"

FrameStack::FrameStack(LeitorExibidor *leitorExibidor) {

	Frame *frame = new Frame();

	frame->method = leitorExibidor->obterMain();
	frame->constantPool = leitorExibidor->obterConstantPool();
	frame->pilhaOperandos = new OperandsStack(frame->method.attributes->info->codigoAtributo.max_stack);
	frame->variaveisLocais = new LocalVariables(frame->method.attributes->info->codigoAtributo.max_locals);
	inicializarPC(frame);

	stackThreads.push(frame);

	//update operand stack pointers and variables array
	//used spots in current method operations

	Operations::atualizarFrame(stackThreads.top());
	Operations::atualizarThreads(&stackThreads);
	Operations::atualizarFrameStack(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary

	MethodArea::atualizarFrameStack(this);

	opcode = 0; //nop is standard instruction
}

void FrameStack::executarMetodos() {
	while (proximaInstrucao()) {
		//cout << "opcode " << opcode << endl;
		Operations::executarOperacao(opcode);
	}

}

bool FrameStack::proximaInstrucao() {
	// empty stack?
	if (stackThreads.empty()) {
		return false;
	}

	//checks if current method operations is empty
	if ((stackThreads.top()->pc - stackThreads.top()->method.attributes->info->codigoAtributo.codigo)
			< stackThreads.top()->method.attributes->info->codigoAtributo.code_length) {
		//get the next opcode to be executed
		opcode = *stackThreads.top()->pc;
		//pc plus 1 instruction
		//if there is any arguments, the called function will use them
		//pc is incremented
		stackThreads.top()->pc++;
		return true;
	}

	//remove the top of stack if there isn't any instructions on current method
	this->popRemoverObjetos();

	//checks if there is any elements left
	if (stackThreads.empty()) {
		return false;
	}

	return true;
}

void FrameStack::popRemoverObjetos() {

	if (!stackThreads.empty()) {

		delete stackThreads.top()->pilhaOperandos;
		delete stackThreads.top()->variaveisLocais;
		stackThreads.pop();
	}
	if (stackThreads.empty()) {
		Operations::atualizarFrame(nullptr);
		Operations::atualizarThreads(nullptr);
		//exit(0);

	} else {
		Operations::atualizarFrame(stackThreads.top());
		Operations::atualizarThreads(&stackThreads);
	}
}

void FrameStack::inicializarPC(Frame *frame) {

	//puts PC onto the initial position of top method
	frame->pc = frame->method.attributes->info->codigoAtributo.codigo;
}

void FrameStack::adicionarFrame(method_info method, cp_info *constantPool) {

	Frame *frame = (Frame*) malloc(sizeof(Frame));

	frame->method = method;
	frame->constantPool = constantPool;
	frame->pilhaOperandos = new OperandsStack(frame->method.attributes->info->codigoAtributo.max_stack);
	frame->variaveisLocais = new LocalVariables(frame->method.attributes->info->codigoAtributo.max_locals);
	inicializarPC(frame);

	//update operand stack pointers and array variables
	//used spots in current method operations
	Operations::atualizarFrame(frame);
	Operations::atualizarThreads(&stackThreads);
	Operations::atualizarFrameStack(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary
	MethodArea::atualizarFrameStack(this);
	stackThreads.push(frame);
}

void FrameStack::adicionarFrame(method_info *method, cp_info *constantPool) {

	this->adicionarFrame(*method, constantPool);
}

void FrameStack::atualizarArgumentos(vector<TypedElement> vectorArgumentos) {

	for (int i = 0, j = 0; (unsigned int) i < vectorArgumentos.size(); i++, j++) {

		stackThreads.top()->variaveisLocais->set(j, vectorArgumentos[i]);

		//tests if the i-th argument filled two slots
		if (stackThreads.top()->variaveisLocais->get(j).type == TYPE_LONG || stackThreads.top()->variaveisLocais->get(j).type == TYPE_DOUBLE
				|| (stackThreads.top()->variaveisLocais->get(j).type == TYPE_REFERENCE && BITS)) {

			j++;
		}
	}
}
