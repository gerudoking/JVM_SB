/*!
 * \file PilhaJVM.cpp
 * \brief
 */

#include "PilhaJVM.h"

PilhaJVM::PilhaJVM(ClassFile *classFile) {

	Frame *frame = new Frame();

	frame->method = classFile->obterMain();
	frame->constantPool = classFile->obterConstantPool();
	frame->operandsStack = new OperandsStack(frame->method.attributes->info->codeAttribute.max_stack);
	frame->localVariables = new LocalVariables(frame->method.attributes->info->codeAttribute.max_locals);
	inicializarPC(frame);

	stackFrame.push(frame);

	//update operand stack pointers and variables array
	//used spots in current method operations

	Operations::atualizarFrame(stackFrame.top());
	Operations::atualizarStackFrame(&stackFrame);
	Operations::atualizarPilhaJVM(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary

	MethodArea::atualizarPilhaJVM(this);

	opcode = 0; //nop is standard instruction
}

void PilhaJVM::executarMetodos() {
	while (proximaInstrucao()) {
		//cout << "opcode " << opcode << endl;
		Operations::executarOperacao(opcode);
	}

}

bool PilhaJVM::proximaInstrucao() {
	// empty stack?
	if (stackFrame.empty()) {
		return false;
	}

	//checks if current method operations is empty
	if ((stackFrame.top()->pc - stackFrame.top()->method.attributes->info->codeAttribute.codigo)
			< stackFrame.top()->method.attributes->info->codeAttribute.code_length) {
		//get the next opcode to be executed
		opcode = *stackFrame.top()->pc;
		//pc plus 1 instruction
		//if there is any arguments, the called function will use them
		//pc is incremented
		stackFrame.top()->pc++;
		return true;
	}

	//remove the top of stack if there isn't any instructions on current method
	this->popRemoverObjetos();

	//checks if there is any elements left
	if (stackFrame.empty()) {
		return false;
	}

	return true;
}

void PilhaJVM::popRemoverObjetos() {

	if (!stackFrame.empty()) {

		delete stackFrame.top()->operandsStack;
		delete stackFrame.top()->localVariables;
		stackFrame.pop();
	}
	if (stackFrame.empty()) {
		Operations::atualizarFrame(nullptr);
		Operations::atualizarStackFrame(nullptr);
		//exit(0);

	} else {
		Operations::atualizarFrame(stackFrame.top());
		Operations::atualizarStackFrame(&stackFrame);
	}
}

void PilhaJVM::inicializarPC(Frame *frame) {

	//puts PC onto the initial position of top method
	frame->pc = frame->method.attributes->info->codeAttribute.codigo;
}

void PilhaJVM::adicionarFrame(Method_info method, Cp_info *constantPool) {

	Frame *frame = (Frame*) malloc(sizeof(Frame));

	frame->method = method;
	frame->constantPool = constantPool;
	frame->operandsStack = new OperandsStack(frame->method.attributes->info->codeAttribute.max_stack);
	frame->localVariables = new LocalVariables(frame->method.attributes->info->codeAttribute.max_locals);
	inicializarPC(frame);

	//update operand stack pointers and array variables
	//used spots in current method operations
	Operations::atualizarFrame(frame);
	Operations::atualizarStackFrame(&stackFrame);
	Operations::atualizarPilhaJVM(this);

	//include reference to frame stack in method area
	//to be possible to include <clinit> when necessary
	MethodArea::atualizarPilhaJVM(this);
	stackFrame.push(frame);
}

void PilhaJVM::adicionarFrame(Method_info *method, Cp_info *constantPool) {

	this->adicionarFrame(*method, constantPool);
}

void PilhaJVM::atualizarArgumentos(vector<TypedElement> vectorArgumentos) {

	for (int i = 0, j = 0; (unsigned int) i < vectorArgumentos.size(); i++, j++) {

		stackFrame.top()->localVariables->set(j, vectorArgumentos[i]);

		//tests if the i-th argument filled two slots
		if (stackFrame.top()->localVariables->get(j).type == TYPE_LONG || stackFrame.top()->localVariables->get(j).type == TYPE_DOUBLE
				|| (stackFrame.top()->localVariables->get(j).type == TYPE_REFERENCE && BITS)) {

			j++;
		}
	}
}
