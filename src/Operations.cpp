/*!
 * \file Operations.cpp
 * \brief
 */

#include "Operations.h"

Frame *Operations::flame = nullptr;
stack<struct frame_s*> *Operations::stackThreads = nullptr;
FrameStack *Operations::frameStack = nullptr;
bool Operations::isWide = false;

const funcaoGenerica Operations::funcaoGenericaOpcodes[] = { &Operations::nop, &Operations::aconst_null, &Operations::iconst_m1,
		&Operations::iconst_0, &Operations::iconst_1, &Operations::iconst_2, &Operations::iconst_3, &Operations::iconst_4,
		&Operations::iconst_5, &Operations::lconst_0, &Operations::lconst_1, &Operations::fconst_0, &Operations::fconst_1,
		&Operations::fconst_2, &Operations::dconst_0, &Operations::dconst_1, &Operations::bipush, &Operations::sipush, &Operations::ldc,
		&Operations::ldc_w, &Operations::ldc2_w, &Operations::iload, &Operations::lload, &Operations::fload, &Operations::dload,
		&Operations::aload, &Operations::iload_0, &Operations::iload_1, &Operations::iload_2, &Operations::iload_3, &Operations::lload_0,
		&Operations::lload_1, &Operations::lload_2, &Operations::lload_3, &Operations::fload_0, &Operations::fload_1, &Operations::fload_2,
		&Operations::fload_3, &Operations::dload_0, &Operations::dload_1, &Operations::dload_2, &Operations::dload_3, &Operations::aload_0,
		&Operations::aload_1, &Operations::aload_2, &Operations::aload_3, &Operations::iaload, &Operations::laload, &Operations::faload,
		&Operations::daload, &Operations::aaload, &Operations::baload, &Operations::caload, &Operations::saload, &Operations::istore,
		&Operations::lstore, &Operations::fstore, &Operations::dstore, &Operations::astore, &Operations::istore_0, &Operations::istore_1,
		&Operations::istore_2, &Operations::istore_3, &Operations::lstore_0, &Operations::lstore_1, &Operations::lstore_2,
		&Operations::lstore_3, &Operations::fstore_0, &Operations::fstore_1, &Operations::fstore_2, &Operations::fstore_3,
		&Operations::dstore_0, &Operations::dstore_1, &Operations::dstore_2, &Operations::dstore_3, &Operations::astore_0,
		&Operations::astore_1, &Operations::astore_2, &Operations::astore_3, &Operations::iastore, &Operations::lastore,
		&Operations::fastore, &Operations::dastore, &Operations::aastore, &Operations::bastore, &Operations::castore, &Operations::sastore,
		&Operations::pop, &Operations::pop2, &Operations::dup, &Operations::dup_x1, &Operations::dup_x2, &Operations::dup2,
		&Operations::dup2_x1, &Operations::dup2_x2, &Operations::swap, &Operations::iadd, &Operations::ladd, &Operations::fadd,
		&Operations::dadd, &Operations::isub, &Operations::lsub, &Operations::fsub, &Operations::dsub, &Operations::imul, &Operations::lmul,
		&Operations::fmul, &Operations::dmul, &Operations::idiv, &Operations::ldiv, &Operations::fdiv, &Operations::ddiv, &Operations::irem,
		&Operations::lrem, &Operations::frem, &Operations::drem, &Operations::ineg, &Operations::lneg, &Operations::fneg, &Operations::dneg,
		&Operations::ishl, &Operations::lshl, &Operations::ishr, &Operations::lshr, &Operations::iushr, &Operations::lushr,
		&Operations::iand, &Operations::land, &Operations::ior, &Operations::lor, &Operations::ixor, &Operations::lxor, &Operations::iinc,
		&Operations::i2l, &Operations::i2f, &Operations::i2d, &Operations::l2i, &Operations::l2f, &Operations::l2d, &Operations::f2i,
		&Operations::f2l, &Operations::f2d, &Operations::d2i, &Operations::d2l, &Operations::d2f, &Operations::i2b, &Operations::i2c,
		&Operations::i2s, &Operations::lcmp, &Operations::fcmpl, &Operations::fcmpg, &Operations::dcmpl, &Operations::dcmpg,
		&Operations::ifeq, &Operations::ifne, &Operations::iflt, &Operations::ifge, &Operations::ifgt, &Operations::ifle,
		&Operations::if_icmpeq, &Operations::if_icmpne, &Operations::if_icmplt, &Operations::if_icmpge, &Operations::if_icmpgt,
		&Operations::if_icmple, &Operations::if_acmpeq, &Operations::if_acmpne, &Operations::funcgoto, &Operations::jsr,
		&Operations::funcret, &Operations::tableswitch, &Operations::lookupswitch, &Operations::ireturn, &Operations::lreturn,
		&Operations::freturn, &Operations::dreturn, &Operations::areturn, &Operations::func_return, &Operations::getstatic,
		&Operations::putstatic, &Operations::getfield, &Operations::putfield, &Operations::invokevirtual, &Operations::invokespecial,
		&Operations::invokestatic, &Operations::invokeinterface, &Operations::nop, &Operations::func_new, &Operations::newarray,
		&Operations::anewarray, &Operations::arraylength, &Operations::athrow, &Operations::nop, &Operations::nop, &Operations::nop,
		&Operations::nop, &Operations::wide, &Operations::multianewarray, &Operations::ifnull, &Operations::ifnonnull, &Operations::goto_w,
		&Operations::jsr_w };

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
	funcaoGenericaOpcodes[opcode]();
}

// Do nothing
void Operations::nop() {
}

// Push in the a null reference (0) to the operands stack
void Operations::aconst_null() {
	flame->pilhaOperandos->empilharReferencia((int*) (nullptr));
}

// Push (int) -1 to the operands stack
void Operations::iconst_m1() {
	flame->pilhaOperandos->empilharInt(int(-1));
}

// Push (int) 0 to the operands stack
void Operations::iconst_0() {
	flame->pilhaOperandos->empilharInt(int(0));
}

// Push (int) 1 to the operands stack
void Operations::iconst_1() {
	flame->pilhaOperandos->empilharInt(int(1));
}

// Push (int) 2 to the operands stack
void Operations::iconst_2() {
	flame->pilhaOperandos->empilharInt(int(2));
}

// Push (int) 3 to the operands stack
void Operations::iconst_3() {
	flame->pilhaOperandos->empilharInt(int(3));
}

// Push (int) 4 to the operands stack
void Operations::iconst_4() {
	flame->pilhaOperandos->empilharInt(int(4));
}

// Push (int) 5 to the operands stack
void Operations::iconst_5() {
	flame->pilhaOperandos->empilharInt(int(5));
}

// Push (long) 0 to the operands stack
void Operations::lconst_0() {
	flame->pilhaOperandos->empilharLong(long(0));
}

// Push (long) 1 to the operands stack
void Operations::lconst_1() {
	flame->pilhaOperandos->empilharLong(long(1));
}

// Push (float) 0.0 to the operands stack
void Operations::fconst_0() {
	flame->pilhaOperandos->empilharFloat(float(0.0));
}

// Push (float) 1.0 to the operands stack
void Operations::fconst_1() {
	flame->pilhaOperandos->empilharFloat(float(1.0));
}

// Push (float) 2.0 to the operands stack
void Operations::fconst_2() {
	flame->pilhaOperandos->empilharFloat(float(2.0));
}

// Push (double) 0.0 to the operands stack
void Operations::dconst_0() {
	flame->pilhaOperandos->empilharDouble(double(0.0));
}

// Push (double) 1.0 to the operands stack
void Operations::dconst_1() {
	flame->pilhaOperandos->empilharDouble(double(1.0));
}

// Push a byte with signal extension
void Operations::bipush() {
	int32_t aux;
	int8_t byte = obterNBytesValue(1, &flame->pc);
	aux = (int32_t) (int8_t) byte; // signal extension
	flame->pilhaOperandos->empilharInt(int(aux));
}

// Push two bytes
void Operations::sipush() {
	uint16_t valShort;
	int32_t valPushShort;
	valShort = obterNBytesValue(2, &flame->pc);
	valPushShort = (int32_t) (int16_t) valShort;  // signal extension
	flame->pilhaOperandos->empilharInt(int(valPushShort));
}

// Push a value from constant pool
void Operations::ldc() {
	uint8_t index = obterNBytesValue(1, &flame->pc);
	cp_info constantPool = flame->constantPool[index];
	if (constantPool.tag == STRING) {
		flame->pilhaOperandos->empilharReferencia((int*) (flame->constantPool[constantPool.info[0].u2].info[1].array));
	} else {
		Element element;
		element.i = constantPool.info[0].u4;
		if (constantPool.tag == INTEGER) {
			flame->pilhaOperandos->empilhar(element, TYPE_INT);
		} else {
			flame->pilhaOperandos->empilhar(element, TYPE_FLOAT);
		}
	}
}

// Push a value from constant pool (ldc wide)
void Operations::ldc_w() {
	uint16_t index = obterNBytesValue(2, &flame->pc);
	cp_info constantPool = flame->constantPool[index];
	if (constantPool.tag == STRING) {
		flame->pilhaOperandos->empilharReferencia((int*) (flame->constantPool[constantPool.info[0].u2].info[1].array));
	} else {
		flame->pilhaOperandos->empilharInt(int(constantPool.info[0].u4));
	}
}

// Push a long or double value from constant pool
void Operations::ldc2_w() {
	uint8_t index = obterNBytesValue(2, &flame->pc);
	long valPushLong;
	double valPushDouble;
	if (flame->constantPool[index].tag == LONG) {
		valPushLong = converter_u4_to_long(flame->constantPool[index].info[0], flame->constantPool[index + 1].info[0]);
		flame->pilhaOperandos->empilharLong(long(valPushLong));
	} else {
		valPushDouble = converter_u4_to_double(flame->constantPool[index].info[0], flame->constantPool[index + 1].info[0]);
		flame->pilhaOperandos->empilharDouble(double(valPushDouble));
	}
}

// Reads an integer from the local variables and pushes it
void Operations::iload() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else {
		index = obterNBytesValue(1, &flame->pc);
	}

	TypedElement typedElement = flame->variaveisLocais->get(int(index));
	flame->pilhaOperandos->empilharInt(int(typedElement.value.i));
}

// Reads an long from the local variables and pushes it
void Operations::lload() {
	uint16_t index = 0;
	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	TypedElement typedElement = flame->variaveisLocais->get(int(index));
	flame->pilhaOperandos->empilharLong(long(typedElement.value.l));
}

// Reads an float from the local variables and pushes it
void Operations::fload() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	TypedElement typedElement = flame->variaveisLocais->get(int(index));
	flame->pilhaOperandos->empilharFloat(float(typedElement.value.f));
}

// Reads an double from the local variables and pushes it
void Operations::dload() {
	uint16_t index;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	TypedElement typedElement = flame->variaveisLocais->get(int(index));
	flame->pilhaOperandos->empilharDouble(double(typedElement.value.d));
}

// Reads a reference from the local variables and pushes it
void Operations::aload() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	TypedElement typedElement = flame->variaveisLocais->get(int(index));
	flame->pilhaOperandos->empilharReferencia((int*) (typedElement.value.pi));
}

// Reads an integer from the local variables, in the position 0, and pushes it
void Operations::iload_0() {
	TypedElement typedElement = flame->variaveisLocais->get(0);
	flame->pilhaOperandos->empilharInt(int(typedElement.value.i));
}

// Reads an integer from the local variables, in the position 1, and pushes it
void Operations::iload_1() {
	TypedElement typedElement = flame->variaveisLocais->get(1);
	flame->pilhaOperandos->empilharInt(int(typedElement.value.i));
}

// Reads an integer from the local variables, in the position 2, and pushes it
void Operations::iload_2() {
	TypedElement typedElement = flame->variaveisLocais->get(2);
	flame->pilhaOperandos->empilharInt(int(typedElement.value.i));
}

// Reads an integer from the local variables, in the position 3, and pushes it
void Operations::iload_3() {
	TypedElement typedElement = flame->variaveisLocais->get(3);
	flame->pilhaOperandos->empilharInt(int(typedElement.value.i));
}

// Reads an long from the local variables, in the position 0, and pushes it
void Operations::lload_0() {
	lload_n(0);
}

// Reads an long from the local variables, in the position 1, and pushes it
void Operations::lload_1() {
	lload_n(1);
}

// LLOAD_<N>
void Operations::lload_n(short index) {
	TypedElement typedElement = flame->variaveisLocais->get(index);
	flame->pilhaOperandos->empilharLong(long(typedElement.value.l));
}

void Operations::lload_2() {
	lload_n(2);
}

void Operations::lload_3() {
	lload_n(3);
}

// FLOAD_<N>
void Operations::fload_n(short index) {
	TypedElement typedElement = flame->variaveisLocais->get(index);
	flame->pilhaOperandos->empilharFloat(typedElement.value.f);
}

void Operations::fload_0() {
	fload_n(0);
}

void Operations::fload_1() {
	fload_n(1);
}

void Operations::fload_2() {
	fload_n(2);
}

void Operations::fload_3() {
	fload_n(3);
}

// DLOAD_<N>
void Operations::dload_n(short index) {
	TypedElement typedElement = flame->variaveisLocais->get(index);
	flame->pilhaOperandos->empilharDouble(typedElement.value.d);
}

void Operations::dload_0() {
	dload_n(0);
}

void Operations::dload_1() {
	dload_n(1);
}

void Operations::dload_2() {
	dload_n(2);
}

void Operations::dload_3() {
	dload_n(3);
}

// ALOAD_<N>
void Operations::aload_n(short index) {
	TypedElement typedElement = flame->variaveisLocais->get(index);
	flame->pilhaOperandos->empilharReferencia(typedElement.value.pi);
}

void Operations::aload_0() {
	aload_n(0);
}

void Operations::aload_1() {
	aload_n(1);
}

void Operations::aload_2() {
	aload_n(2);
}

void Operations::aload_3() {
	aload_n(3);
}

void Operations::iaload() {
	element_u element1, element2;

	element1 = flame->pilhaOperandos->desempilha();
	element2 = flame->pilhaOperandos->desempilha();
	int *referencia = element2.pi;

	if (referencia == nullptr)
		throw runtime_error("Null pointer");
	flame->pilhaOperandos->empilharInt(referencia[element1.i]);

}

void Operations::laload() {
	element_u element1, element2;
	//struct typedElement_s typedElement;

	element1 = flame->pilhaOperandos->desempilha();
	element2 = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) element2.pi;
	if (localVariables == nullptr)
		throw runtime_error("Null pointer");

	flame->pilhaOperandos->empilharTypedElement(localVariables->get(element1.i));
}

void Operations::lstore_0() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
	if (typedElement.type == TYPE_LONG) {
		flame->variaveisLocais->set(0, typedElement);
	} else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operations::lstore() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(index, typedElement);
	} else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operations::istore() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(index, typedElement);
	} else
		printf("Operando no topo != TYPE_INT\n");
}

void Operations::fstore() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(index, typedElement);
	} else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operations::dstore() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(index, typedElement);
	} else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operations::astore() {
	uint16_t index = 0;

	if (isWide) {
		index = obterNBytesValue(2, &flame->pc);
		isWide = false;
	} else
		index = obterNBytesValue(1, &flame->pc);

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(index, typedElement);
	} else
		printf("Operando no topo != TYPE_REFERECE\n");
}

void Operations::istore_0() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(0, typedElement);
	} else
		printf("Operando no topo != TYPE_INT\n");
}

void Operations::istore_1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(1, typedElement);
	} else
		printf("Operando no topo != TYPE_INT\n");
}

void Operations::istore_2() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(2, typedElement);
	} else
		printf("Operando no topo != TYPE_INT\n");
}

void Operations::istore_3() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(3, typedElement);
	} else
		printf("Operando no topo != TYPE_INT\n");
}

// Read the fload value from a array and push to the operand stack
void Operations::faload() {
	int index = flame->pilhaOperandos->desempilha().i;
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	if (localVariables == NULL) {
	}
	flame->pilhaOperandos->empilharTypedElement(localVariables->get(index));
}

// Read the double value from a array and push to the operand stack
void Operations::daload() {
	int index = flame->pilhaOperandos->desempilha().i;
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	flame->pilhaOperandos->empilharTypedElement(localVariables->get(index));
}

// Read a reference value from a array and push to the operand stack
void Operations::aaload() {
	int index = flame->pilhaOperandos->desempilha().i;
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	flame->pilhaOperandos->empilharTypedElement(localVariables->get(index));
}

// Read the boolean value from a array and push to the operand stack
void Operations::baload() {
	int index = flame->pilhaOperandos->desempilha().i;
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	flame->pilhaOperandos->empilharTypedElement(localVariables->get(index));
}

// Read the char value from a array and push to the operand stack
void Operations::caload() {
	int index = flame->pilhaOperandos->desempilha().i;
	vector<char> *localVariables = (vector<char> *) flame->pilhaOperandos->desempilha().pi;
	flame->pilhaOperandos->empilharInt(localVariables->at(index));
}

void Operations::saload() {
	int index = flame->pilhaOperandos->desempilha().i;
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	flame->pilhaOperandos->empilharTypedElement(localVariables->get(index));
}

void Operations::lstore_1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(1, typedElement);
	} else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operations::lstore_2() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(2, typedElement);
	} else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operations::lstore_3() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(3, typedElement);
	} else
		printf("Operando no topo != TYPE_LONG\n");
}

void Operations::fstore_0() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(0, typedElement);
	} else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operations::fstore_1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(1, typedElement);
	} else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operations::fstore_2() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(2, typedElement);
	} else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operations::fstore_3() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(3, typedElement);
	} else
		printf("Operando no topo != TYPE_FLOAT\n");
}

void Operations::dstore_0() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(0, typedElement);
	} else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operations::dstore_1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(1, typedElement);
	} else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operations::dstore_2() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(2, typedElement);
	} else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operations::dstore_3() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(3, typedElement);
	} else
		printf("Operando no topo != TYPE_DOUBLE\n");
}

void Operations::astore_0() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(0, typedElement);
	} else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operations::astore_1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(1, typedElement);
	} else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operations::astore_2() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(2, typedElement);
	} else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operations::astore_3() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		flame->variaveisLocais->set(3, typedElement);
	} else
		printf("Operando no topo != TYPE_REFERENCE\n");
}

void Operations::iastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	int *vetor = flame->pilhaOperandos->desempilha().pi;

	if (vetor == nullptr)
		throw runtime_error("NullPointerException");
	/*typedElement aux;
	 aux.value.i = valor.i;
	 aux.type = TYPE_INT;
	 aux.realType = RT_INT;*/
	vetor[indiceElement.i] = valorElement.i;
}

// Stores a double in the operands stack as a array element
void Operations::lastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.l = valorElement.l;
	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	localVariables->set(indiceElement.i, typedElement);
}

// Stores a float in the operands stack as a array element
void Operations::fastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.f = valorElement.f;
	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	localVariables->set(indiceElement.i, typedElement);
}

// Stores a double in the operands stack as a array element
void Operations::dastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.d = valorElement.d;
	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	localVariables->set(indiceElement.i, typedElement);
}

// Stores a reference in the operands stack as a array element
void Operations::aastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.pi = valorElement.pi;
	typedElement.type = TYPE_REFERENCE;
	typedElement.realType = RT_REFERENCE;
	localVariables->set(indiceElement.i, typedElement);
}

// Stores a byte in the operands stack as a array element
void Operations::bastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.i = valorElement.i;
	typedElement.type = TYPE_INT;
	typedElement.realType = RT_BOOL;
	localVariables->set(indiceElement.i, typedElement);
}

// Stores a char in the operands stack as a array element
void Operations::castore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	vector<uint8_t> *vetorLocalVariables = (vector<uint8_t> *) flame->pilhaOperandos->desempilha().pi;

	if (vetorLocalVariables == nullptr)
		throw runtime_error("NullPointerException");
	vetorLocalVariables->at(indiceElement.i) = valorElement.bs;
}

// Stores a short in the operands stack as a array element
void Operations::sastore() {
	Element valorElement = flame->pilhaOperandos->desempilha();
	Element indiceElement = flame->pilhaOperandos->desempilha();
	LocalVariables *localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;

	if (localVariables == nullptr)
		throw runtime_error("NullPointerException");
	TypedElement typedElement;
	typedElement.value.i = valorElement.i;
	typedElement.type = TYPE_INT;
	typedElement.realType = RT_SHORT;
	localVariables->set(indiceElement.i, typedElement);
}

void Operations::iadd() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i + element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ladd() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l + element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::fadd() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	typedElement.value.f = element1.f + element2.f;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::dadd() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	typedElement.value.d = element1.d + element2.d;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::isub() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i - element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lsub() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l - element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::fsub() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	typedElement.value.f = element1.f - element2.f;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::dsub() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	typedElement.value.d = element1.d - element2.d;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::imul() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i * element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lmul() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l * element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::fmul() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	typedElement.value.f = element1.f * element2.f;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::dmul() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	typedElement.value.d = element1.d * element2.d;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::idiv() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_INT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um inteiro!");
	}

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i / element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ldiv() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_LONG) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um long!");
	}

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l / element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::fdiv() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_FLOAT) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um float!");
	}

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	typedElement.value.f = element1.f / element2.f;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ddiv() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element2 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_DOUBLE) {
		element1 = flame->pilhaOperandos->desempilha();
	} else {
		throw runtime_error("Elemento lido nao era um double!");
	}

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	typedElement.value.d = element1.d / element2.d;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::irem() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	if (element2.i == 0) {
		throw runtime_error("Arithmetic Exeption: divisao por z    ");
	}

	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i - int(element1.i / element2.i) * element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lrem() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	if (element2.l == 0) {
		throw runtime_error("Arithmetic Exeption: divisao por zero.");
	}

	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l - int(element1.l / element2.l) * element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::frem() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	if (verificarFloat(element1.f) == 3 || verificarFloat(element2.f) == 3) {
		typedElement.value.i = Float_NaN;
	} else if (verificarFloat(element1.f) == 1 || verificarFloat(element1.f) == 2 || element2.f == 0.0) {
		typedElement.value.i = Float_NaN;
	} else if (verificarFloat(element1.f) == 0 && (verificarFloat(element2.f) == 1 || verificarFloat(element2.f) == 2)) {
		typedElement.value.f = element1.f;
	} else if (element1.f == 0.0 && verificarFloat(element2.f) == 0) {
		typedElement.value.f = 0.0;
	} else {
		typedElement.value.f = fmod(element1.f, element2.f);
	}

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::drem() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	if (verificarDouble(element1.d) == 3 || verificarDouble(element2.d) == 3) {
		typedElement.value.l = Double_NaN;
	} else if (verificarDouble(element1.d) == 1 || verificarDouble(element1.d) == 2 || element2.d == double(0.0)) {
		typedElement.value.l = Double_NaN;
	} else if (verificarDouble(element1.d) == 0 && (verificarDouble(element2.d) == 1 || verificarDouble(element2.d) == 2)) {
		typedElement.value.d = element1.d;
	} else if (element1.d == 0.0 && verificarDouble(element2.d) == 0) {
		typedElement.value.d = 0.0;
	} else {
		typedElement.value.d = fmod(element1.d, element2.d);
	}

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ineg() {
	element_u value;
	struct typedElement_s typedElement;

	value = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.is = 0 - value.is;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lneg() {
	element_u value;
	struct typedElement_s typedElement;

	value = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.ls = 0 - value.ls;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::fneg() {
	element_u value;
	struct typedElement_s typedElement;

	value = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_FLOAT;
	typedElement.realType = RT_FLOAT;
	//inverte o bit 31
	typedElement.value.i = value.i + 0x80000000;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::dneg() {
	element_u value;
	struct typedElement_s typedElement;

	value = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_DOUBLE;
	typedElement.realType = RT_DOUBLE;
	//inverte o bit 63
	typedElement.value.l = value.l + 0x8000000000000000;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ishl() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i << (element2.i & 0b011111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lshl() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l << (element2.i & 0b0111111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ishr() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.is = element1.is >> (element2.i & 0b011111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lshr() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.ls = element1.ls >> (element2.i & 0b0111111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::iushr() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i >> (element2.i & 0b011111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::lushr() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l >> (element2.i & 0b0111111);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::iand() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_INT;
	typedElement.realType = RT_INT;
	typedElement.value.i = element1.i & element2.i;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::land() {
	element_u element1, element2;
	struct typedElement_s typedElement;

	element2 = flame->pilhaOperandos->desempilha();
	element1 = flame->pilhaOperandos->desempilha();

	typedElement.type = TYPE_LONG;
	typedElement.realType = RT_LONG;
	typedElement.value.l = element1.l & element2.l;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::ior() {
	Element element1 = flame->pilhaOperandos->desempilha();
	Element element2 = flame->pilhaOperandos->desempilha();
	element1.i |= element2.i;
	flame->pilhaOperandos->empilhar(element1, TYPE_INT);
}

void Operations::lor() {
	Element element1 = flame->pilhaOperandos->desempilha();
	Element element2 = flame->pilhaOperandos->desempilha();
	element1.l |= element2.l;
	flame->pilhaOperandos->empilhar(element1, TYPE_LONG);
}

void Operations::ixor() {
	Element element1 = flame->pilhaOperandos->desempilha();
	Element element2 = flame->pilhaOperandos->desempilha();
	element1.i ^= element2.i;
	flame->pilhaOperandos->empilhar(element1, TYPE_INT);
}

void Operations::lxor() {
	Element element1 = flame->pilhaOperandos->desempilha();
	Element element2 = flame->pilhaOperandos->desempilha();
	element1.l ^= element2.l;
	flame->pilhaOperandos->empilhar(element1, TYPE_LONG);
}

void Operations::iinc() {
	uint16_t var;
	int16_t n;
	if (isWide) {
		var = obterNBytesValue(2, &flame->pc);
		n = int16_t(obterNBytesValue(2, &flame->pc));
	} else {
		var = obterNBytesValue(1, &flame->pc);
		n = int8_t(obterNBytesValue(1, &flame->pc));
	}

	TypedElement typedElement = flame->variaveisLocais->get(var);
	if (typedElement.type == TYPE_INT)
		typedElement.value.i += (int32_t) n;
	flame->variaveisLocais->set(var, typedElement);
}

void Operations::i2l() {
	flame->pilhaOperandos->empilhar(flame->pilhaOperandos->desempilha(), TYPE_LONG);
}

void Operations::i2f() {
	Element element = flame->pilhaOperandos->desempilha();
	element.f = (float) element.is;
	flame->pilhaOperandos->empilharFloat(element.f);
}

void Operations::i2d() {
	Element element = flame->pilhaOperandos->desempilha();
	element.d = (double) element.is;
	flame->pilhaOperandos->empilharDouble(element.d);
}

void Operations::l2i() {
	Element element = flame->pilhaOperandos->desempilha();
	element.i = (uint32_t) element.l;
	flame->pilhaOperandos->empilhar(element, TYPE_INT);
}

void Operations::l2f() {
	Element element = flame->pilhaOperandos->desempilha();
	element.f = (float) element.l;
	flame->pilhaOperandos->empilhar(element, TYPE_FLOAT);
}

void Operations::l2d() {
	Element element = flame->pilhaOperandos->desempilha();
	element.d = (double) element.l;
	flame->pilhaOperandos->empilharDouble(element.d);
}

void Operations::f2i() {
	Element element = flame->pilhaOperandos->desempilha();
	element.is = (int32_t) element.f;
	flame->pilhaOperandos->empilharInt(element.is);
}

void Operations::f2l() {
	Element element = flame->pilhaOperandos->desempilha();
	element.l = (int64_t) element.f;
	flame->pilhaOperandos->empilhar(element, TYPE_LONG);
}

void Operations::f2d() {
	Element element = flame->pilhaOperandos->desempilha();
	element.d = (double) element.f;
	flame->pilhaOperandos->empilharDouble(element.d);
}

void Operations::d2i() {
	Element element = flame->pilhaOperandos->desempilha();
	element.is = (int32_t) element.d;
	flame->pilhaOperandos->empilharInt(element.is);
}

void Operations::d2l() {
	Element element = flame->pilhaOperandos->desempilha();
	element.l = (int64_t) element.d;
	flame->pilhaOperandos->empilhar(element, TYPE_LONG);
}

void Operations::d2f() {
	Element element = flame->pilhaOperandos->desempilha();
	element.f = (float) element.d;
	flame->pilhaOperandos->empilharFloat(element.f);
}

//le um int do topo da pilha (truncado para byte), extende com sinal para um int e reinsere na pilha de operandos
void Operations::i2b() {
	int8_t value = flame->pilhaOperandos->desempilha().bs;

	flame->pilhaOperandos->empilharInt(int(value));
}

//le um int do topo da pilha (truncado para char), extende com 0 para um int  e reinsere na pilha de operandos
void Operations::i2c() {
	TypedElement typedElement;
	typedElement.type = TYPE_INT;
	typedElement.realType = RT_CHAR;
	typedElement.value.b = flame->pilhaOperandos->desempilha().b;
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

//le um int do topo da pilha (truncado para short), extende com sinal para um int e reinsere na pilha de operandos
void Operations::i2s() {
	TypedElement typedElement;
	typedElement.type = TYPE_INT;
	typedElement.realType = RT_SHORT;
	typedElement.value.ss = flame->pilhaOperandos->desempilha().ss;

	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo long) e os compara
void Operations::lcmp() {
	int64_t value2 = flame->pilhaOperandos->desempilha().ls;
	int64_t value1 = flame->pilhaOperandos->desempilha().ls;

	if (value1 > value2)
		flame->pilhaOperandos->empilharInt(int(1));
	if (value1 == value2)
		flame->pilhaOperandos->empilharInt(int(0));
	if (value1 < value2)
		flame->pilhaOperandos->empilharInt(int(-1));
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo float) e os compara
void Operations::fcmpl() {
	float value2 = flame->pilhaOperandos->desempilha().f;
	float value1 = flame->pilhaOperandos->desempilha().f;
	int res1, res2;

	res1 = verificarFloat(value1);
	res2 = verificarFloat(value2);
	//se value1 ou value2 for NaN entao adiciona -1 na pilha de operandos
	if (res1 == 3 || res2 == 3) {
		flame->pilhaOperandos->empilharInt(int(-1));
	} else {
		if (value1 > value2)
			flame->pilhaOperandos->empilharInt(int(1));
		if (value1 == value2)
			flame->pilhaOperandos->empilharInt(int(0));
		if (value1 < value2)
			flame->pilhaOperandos->empilharInt(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo float) e os compara
void Operations::fcmpg() {
	float value2 = flame->pilhaOperandos->desempilha().f;
	float value1 = flame->pilhaOperandos->desempilha().f;
	int res1, res2;

	res1 = verificarFloat(value1);
	res2 = verificarFloat(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3) {
		flame->pilhaOperandos->empilharInt(int(1));
	} else {
		if (value1 > value2)
			flame->pilhaOperandos->empilharInt(int(1));
		if (value1 == value2)
			flame->pilhaOperandos->empilharInt(int(0));
		if (value1 < value2)
			flame->pilhaOperandos->empilharInt(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo double) e os compara
void Operations::dcmpl() {
	double value2 = flame->pilhaOperandos->desempilha().d;
	double value1 = flame->pilhaOperandos->desempilha().d;
	int res1, res2;

	res1 = verificarDouble(value1);
	res2 = verificarDouble(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3) {
		flame->pilhaOperandos->empilharInt(int(1));
	} else {
		if (value1 > value2)
			flame->pilhaOperandos->empilharInt(int(1));
		if (value1 == value2)
			flame->pilhaOperandos->empilharInt(int(0));
		if (value1 < value2)
			flame->pilhaOperandos->empilharInt(int(-1));
	}
}

//le os dois primeiros elementos da pilha de operandos (dois elementos do tipo double) e os compara
void Operations::dcmpg() {
	double value2 = flame->pilhaOperandos->desempilha().d;
	double value1 = flame->pilhaOperandos->desempilha().d;
	int res1, res2;

	res1 = verificarDouble(value1);
	res2 = verificarDouble(value2);
	//se value1 ou value2 for NaN entao adiciona 1 na pilha de operandos
	if (res1 == 3 || res2 == 3) {
		flame->pilhaOperandos->empilharInt(int(1));
	} else {
		if (value1 > value2)
			flame->pilhaOperandos->empilharInt(int(1));
		if (value1 == value2)
			flame->pilhaOperandos->empilharInt(int(0));
		if (value1 < value2)
			flame->pilhaOperandos->empilharInt(int(-1));
	}
}

//le o valor do topo da pilha, se for igual a 0 salta
void Operations::ifeq() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value == 0)
		flame->pc += branchbyte - 3;

}

//le o valor do topo da pilha, se for diferente de 0 salta
void Operations::ifne() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value != 0)
		flame->pc += branchbyte - 3;

}

//le o valor do topo da pilha, se for menor que 0 salta
void Operations::iflt() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value < 0)
		flame->pc += branchbyte - 3;

}

//le o valor do topo da pilha, se for maior ou igual a 0 salta
void Operations::ifge() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value >= 0)
		flame->pc += branchbyte - 3;

}

//le o valor do topo da pilha, se for maior que 0 salta
void Operations::ifgt() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value > 0)
		flame->pc += branchbyte - 3;
}

//le o valor do topo da pilha, se for menor ou igual a 0 salta
void Operations::ifle() {
	int value = flame->pilhaOperandos->desempilha().i;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (value <= 0)
		flame->pc += branchbyte - 3;
}

//le dois valores da pilha, se forem iguais salta
void Operations::if_icmpeq() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().i;
	value1 = flame->pilhaOperandos->desempilha().i;

	if (value1 == value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_icmpne() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().i;
	value1 = flame->pilhaOperandos->desempilha().i;

	if (value1 != value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_icmplt() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().i;
	value1 = flame->pilhaOperandos->desempilha().i;

	if (value1 < value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_icmpge() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().is;
	value1 = flame->pilhaOperandos->desempilha().is;

	if (value1 >= value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_icmpgt() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().i;
	value1 = flame->pilhaOperandos->desempilha().i;

	if (value1 > value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_icmple() {
	int value1, value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().i;
	value1 = flame->pilhaOperandos->desempilha().i;

	if (value1 <= value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_acmpeq() {
	int *value1, *value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().pi;
	value1 = flame->pilhaOperandos->desempilha().pi;

	if (value1 == value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::if_acmpne() {
	int *value1, *value2;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	value2 = flame->pilhaOperandos->desempilha().pi;
	value1 = flame->pilhaOperandos->desempilha().pi;

	if (value1 != value2) {
		flame->pc += branchbyte - 3;
	}
}

void Operations::funcgoto() {
	int16_t offset;

	offset = int16_t(obterNBytesValue(2, &flame->pc));

	flame->pc += offset - 3;
}

void Operations::jsr() {
	int16_t offset;

	offset = int16_t(obterNBytesValue(2, &flame->pc));

	flame->pilhaOperandos->empilharReferencia((int*) flame->pc);

	flame->pc += offset - 3;
}

//pode ser utilizada em conjunto com wide
void Operations::funcret() {
	if (isWide) {
		flame->pc = (unsigned char *) flame->variaveisLocais->get(obterNBytesValue(2, &flame->pc)).value.pi;
		isWide = false;
	} else
		flame->pc = (unsigned char *) flame->variaveisLocais->get(obterNBytesValue(1, &flame->pc)).value.pi;
}

void Operations::tableswitch() {
	//guarda o valor inicial do pc
	unsigned char *bkpPC = (flame->pc) - 1;
	uint8_t mod = (flame->pc - flame->method.attributes->info->codigoAtributo.codigo) % 4;
	flame->pc += mod;

	int32_t defaults, low, high, offset;
	defaults = int32_t(obterNBytesValue(4, &flame->pc));
	low = int32_t(obterNBytesValue(4, &flame->pc));
	high = int32_t(obterNBytesValue(4, &flame->pc));

	int32_t index = flame->pilhaOperandos->desempilhaTyped().value.is;

	//salto padrão caso index não esteja no range correto
	if (index < low || index > high) {
		flame->pc = bkpPC;
		flame->pc += defaults;
		return;
	}

	for (; low < high + 1; low++) {
		offset = int32_t(obterNBytesValue(4, &flame->pc));
		if (index == low) {
			break;
		}

	}
	flame->pc = bkpPC;
	flame->pc += offset;
}

void Operations::lookupswitch() {
	unsigned char *aux = (flame->pc) - 1;
	int diff = (flame->pc - flame->method.attributes->info->codigoAtributo.codigo) % 4;

	flame->pc += diff;

	int32_t defaultValue = obterNBytesValue(4, &flame->pc);
	int32_t npairs = obterNBytesValue(4, &flame->pc);
	int32_t match, offset, key = flame->pilhaOperandos->desempilha().is;
	int i;

	for (i = 0; i < npairs; i++) {
		match = obterNBytesValue(4, &flame->pc);
		offset = obterNBytesValue(4, &flame->pc);

		if (match == key) {
			flame->pc = aux + offset;
			break;
		}
	}

	if (i == npairs) {
		flame->pc = aux + defaultValue;
	}
}

void Operations::ireturn() {
	int value = flame->pilhaOperandos->desempilha().i;

	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	stackThreads->pop();
	flame = stackThreads->top();
	flame->pilhaOperandos->empilharInt(value);
}

void Operations::lreturn() {
	long value = flame->pilhaOperandos->desempilha().l;

	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	stackThreads->pop();
	flame = stackThreads->top();
	flame->pilhaOperandos->empilharLong(value);
}

void Operations::freturn() {
	float value = flame->pilhaOperandos->desempilha().f;

	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	stackThreads->pop();
	flame = stackThreads->top();
	flame->pilhaOperandos->empilharFloat(value);
}

void Operations::dreturn() {
	double value = flame->pilhaOperandos->desempilha().d;

	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	stackThreads->pop();
	flame = stackThreads->top();
	flame->pilhaOperandos->empilharDouble(value);
}

void Operations::areturn() {
	element_u element;

	if (flame->pilhaOperandos->desempilhaTopoTipo() == TYPE_REFERENCE) {
		element = flame->pilhaOperandos->desempilha();

		while (!flame->pilhaOperandos->estaVazia()) {
			flame->pilhaOperandos->desempilha();
		}

	} else {
		throw runtime_error("Elemento lido nao era uma referencia!");
	}

	stackThreads->pop();
	flame = stackThreads->top();

	flame->pilhaOperandos->empilharReferencia(element.pi);
}

void Operations::func_return() {
	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	frameStack->popRemoverObjetos();
}

StaticClass* Operations::obterStaticClassThatHasField(StaticClass* base, string field_name) {
	TypedElement typedElement = base->obterField(field_name);
	if (typedElement.type != TYPE_NOT_SET) {
		return base;
	}

	int cp_index = base->obterClasseLeitorExibidor()->obterSuper_class();
	if (cp_index == 0) {
		return NULL;
	}

	StaticClass* staticClass = MethodArea::obterClass(
			capturarIndiceDeReferencia(base->obterClasseLeitorExibidor()->obterConstantPool(), cp_index));
	return obterStaticClassThatHasField(staticClass, field_name);
}

void Operations::getstatic() {
	uint16_t indexByte = obterNBytesValue(2, &flame->pc);

	//volta pc para o inicio da instrucao, para caso ela tenha que ser executada novamente
	flame->pc -= 3;

	Frame *flameAux = flame;
	cp_info constantPool_field = flame->constantPool[indexByte];
	if (constantPool_field.tag != FIELD_REF) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para FIELD_REF!");
	}

	string class_name = capturarIndiceDeReferencia(flame->constantPool, constantPool_field.info[0].u2);

	cp_info constantPool_name_and_type = flame->constantPool[constantPool_field.info[1].u2];
	if (constantPool_name_and_type.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, constantPool_name_and_type.info[0].u2);
	string descriptor = capturarIndiceDeReferencia(flame->constantPool, constantPool_name_and_type.info[1].u2);

	// JAVA LANG
	if (class_name == "java/lang/System" && descriptor == "Ljava/io/PrintStream;") {
		flame->pc += 3;
		return;
	}

	StaticClass* staticClass = obterStaticClassThatHasField(MethodArea::obterClass(class_name), name);

	if (staticClass == NULL)
		throw runtime_error("Field nao existe na classe definida!");

	// Caso <clinit> seja empilhado.
	if (stackThreads->top() != flameAux) {
		return;
	}

	TypedElement typedElement = staticClass->obterField(name);

	if (typedElement.type == TYPE_BOOL) {
		typedElement.type = TYPE_INT;
	}

	flame->pilhaOperandos->empilharTypedElement(typedElement);

	//anda com o pc para a proxima instrucao
	flame->pc += 3;
}

void Operations::putstatic() {
	Frame *flameAux = flame;

	uint16_t indexByte = obterNBytesValue(2, &flame->pc);
	cp_info constantPool_field = flame->constantPool[indexByte];
	if (constantPool_field.tag != FIELD_REF) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para FIELD_REF!");
	}

	string class_name = capturarIndiceDeReferencia(flame->constantPool, constantPool_field.info[0].u2);

	cp_info constantPool_name_and_type = flame->constantPool[constantPool_field.info[1].u2];
	if (constantPool_name_and_type.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, constantPool_name_and_type.info[0].u2);
	string descriptor = capturarIndiceDeReferencia(flame->constantPool, constantPool_name_and_type.info[1].u2);

	// JAVA LANG
	if (class_name == "java/lang/System" && descriptor == "Ljava/io/PrintStream;") {
		return;
	}

	StaticClass* static_class = obterStaticClassThatHasField(MethodArea::obterClass(class_name), name);

	if (static_class == NULL)
		throw runtime_error("Field nao existe na classe definida!");

	// Caso <clinit> seja empilhado.
	if (stackThreads->top() != flameAux) {
		return;
	}

	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();

	if (descriptor[0] == 'B') {
		typedElement.type = TYPE_BOOL;
	}

	static_class->atualizarField(name, typedElement);
}

void Operations::getfield() {
	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);

	InstanceClass *instanceClass = (InstanceClass *) flame->pilhaOperandos->desempilha().pi;

	if (instanceClass == nullptr) {
		throw runtime_error("Null Pointer Exception");
	}

	int index = flame->constantPool[indexbyte].info[1].u2;
	index = flame->constantPool[index].info[0].u2;
	TypedElement typedElement = instanceClass->obterField(capturarIndiceDeReferencia(flame->constantPool, index));
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::putfield() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
	InstanceClass *instanceClass = (InstanceClass *) flame->pilhaOperandos->desempilha().pi;
	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);

	if (instanceClass == nullptr) {
		throw runtime_error("Null Pointer Exception");
	}

	int index = flame->constantPool[indexbyte].info[1].u2;
	index = flame->constantPool[index].info[0].u2;

	if (capturarIndiceDeReferencia(flame->constantPool, flame->method.name_index) == "<init>") {
		instanceClass->atualizarFieldFinals(capturarIndiceDeReferencia(flame->constantPool, index), typedElement);
	} else {
		instanceClass->atualizarField(capturarIndiceDeReferencia(flame->constantPool, index), typedElement);
	}
}

void Operations::invokevirtual() {
	Frame *flameAux = flame;

	uint16_t indexByte = obterNBytesValue(2, &flame->pc);

	cp_info constantPool_element = flame->constantPool[indexByte];
	if (constantPool_element.tag != METHOD_REF) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");
	}

	string class_name = capturarIndiceDeReferencia(flame->constantPool, constantPool_element.info[0].u2);

	cp_info name_and_type_element = flame->constantPool[constantPool_element.info[1].u2];
	if (name_and_type_element.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[0].u2);
	string descriptor = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[1].u2);

	if (class_name.find("java/") != string::npos) {
		// simulando println ou print
		if (class_name == "java/io/PrintStream" && (name == "print" || name == "println")) {
			if (descriptor != "()V") {
				TypedElement element = flame->pilhaOperandos->desempilhaTyped();
				switch (element.realType) {
				case RT_DOUBLE:
					printf("%f", element.value.d);
					break;
				case RT_FLOAT:
					printf("%f", element.value.f);
					break;
				case RT_LONG:
					printf("%ld", element.value.ls);
					break;
				case RT_REFERENCE:
					cout << obterUTF8((unsigned char *) element.value.pi, 0);
					break;
				case RT_BOOL:
					printf("%s", element.value.b == 0 ? "false" : "true");
					break;
				case RT_BYTE:
					printf("%d", element.value.b);
					break;
				case RT_CHAR:
					printf("%c", element.value.bs);
					break;
				case RT_SHORT:
					printf("%d", element.value.ss);
					break;
				case RT_INT:
					printf("%d", element.value.is);
					break;
				default:
					// PRECISA ?
					//cout << "" << endl;
					//throw runtime_error("Dado Invalido.");
					printf("%d", element.value.is);
					break;
				}
			}

			if (name == "println")
				printf("\n");

		} else if (class_name == "java/lang/String" && name == "length") {

			TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();

			if (typedElement.realType == RT_REFERENCE) {
				TypedElement ret;
				ret.type = TYPE_INT;
				ret.realType = RT_INT;

				ret.value.i = obterUTF8((unsigned char *) typedElement.value.pi, 0).size();

				flame->pilhaOperandos->empilharTypedElement(ret);
			} else {
				throw runtime_error("Dado Invalido.");
			}

		} else if (class_name == "java/lang/String" && name == "equals") {

			TypedElement typedElement1 = flame->pilhaOperandos->desempilhaTyped();
			TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();

			if (typedElement1.realType == RT_REFERENCE && typedElement2.realType == RT_REFERENCE) {
				TypedElement ret;
				ret.type = TYPE_INT;
				ret.realType = RT_INT;

				if (obterUTF8((unsigned char *) typedElement1.value.pi, 0) == obterUTF8((unsigned char *) typedElement2.value.pi, 0)) {
					ret.value.b = 1;
				} else {
					ret.value.b = 0;
				}

				flame->pilhaOperandos->empilharTypedElement(ret);
			} else {
				throw runtime_error("Dados Invalidos.");
			}

		} else {
			throw runtime_error("Metodo Invalido.");
		}
	} else {

		uint16_t num_args = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (descriptor[i] != ')') {
			char baseType = descriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				num_args += 2;
			} else if (baseType == 'L') {
				num_args++;
				while (descriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				num_args++;
				while (descriptor[++i] == '[')
					;
				if (descriptor[i] == 'L')
					while (descriptor[++i] != ';')
						;
			} else {
				num_args++;
			}
			i++;
		}

		vector<TypedElement> vectorArgumentos;
		for (int i = 0; i < num_args; i++) {
			TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
			vectorArgumentos.insert(vectorArgumentos.begin(), typedElement);
		}

		TypedElement object_element = flame->pilhaOperandos->desempilhaTyped();
		if (object_element.type == TYPE_REFERENCE) {
			throw runtime_error("Elemento não é uma referencia para REFERENCE!");
		}
		vectorArgumentos.insert(vectorArgumentos.begin(), object_element);

		InstanceClass* instanceClass = (InstanceClass *) object_element.value.pi;

		//ClasseEstatica *classRuntime = MethodArea::getClass(class_name);
		MethodArea::obterClass(class_name);

		// Caso <clinit> seja empilhado.
		if (stackThreads->top() != flameAux) {
			flame->pc = flame->pc - 3;
			return;
		}

		frameStack->adicionarFrame(instanceClass->obterStaticClass()->obterClasseLeitorExibidor()->obterMethod(name, descriptor),
				instanceClass->obterStaticClass()->obterClasseLeitorExibidor()->obterClassThatHasSerachedMethod(name, descriptor)->obterConstantPool());
		frameStack->atualizarArgumentos(vectorArgumentos);
	}
}

void Operations::invokespecial() {
	Frame *frameAux = stackThreads->top();
	uint16_t indexByte = obterNBytesValue(2, &flame->pc);

	cp_info cp_element = flame->constantPool[indexByte];
	if (cp_element.tag != METHOD_REF) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");
	}

	string classe = capturarIndiceDeReferencia(flame->constantPool, cp_element.info[0].u2);

	cp_info metodo = flame->constantPool[cp_element.info[1].u2];
	if (metodo.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, metodo.info[0].u2);
	string desc = capturarIndiceDeReferencia(flame->constantPool, metodo.info[1].u2);

	//checa se é uma das classes simuladas
	if ((classe == "java/lang/Object" || classe == "java/lang/String") && name == "<init>") {
		if (classe == "java/lang/String") {
			flame->pilhaOperandos->desempilha();
		}
		return;
	}

	//checa se o metodo que irá executar é válido
	if (classe.find("java/") != string::npos) {
		cerr << "ERRO: \"" << name << "\" nao definido." << endl;
		exit(1);
	} else {
		uint16_t count = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; //variavel para andar pelo descritor

		while (desc[i] != ')') {
			char baseType = desc[i];
			if (baseType == 'D' || baseType == 'J') {
				(++count)++;
			} else if (baseType == 'L') {
				count++;
				//para pular o nome da classe
				while (desc[++i] != ';')
					;
			} else if (baseType == '[') {
				count++;
				//para pegar todas as dimensões mais rapidamente
				while (desc[++i] == '[')
					;
				if (desc[i] == 'L') {
					//para pular o nome da classe
					while (desc[++i] != ';')
						;
				}
			} else {
				count++;
			}
			i++;
		}

		//desempilha a quantidade de parametros calculada acima
		vector<TypedElement> parametros;
		for (int i = 0; i < count; i++) {
			TypedElement prox = flame->pilhaOperandos->desempilhaTyped();
			parametros.insert(parametros.begin(), prox);
		}

		TypedElement object_element = flame->pilhaOperandos->desempilhaTyped();

		parametros.insert(parametros.begin(), object_element);

		InstanceClass* instance = (InstanceClass *) object_element.value.pi;

		//ClasseEstatica *classRuntime = MethodArea::getClass(classe);
		MethodArea::obterClass(classe);

		//checa se houve uma mudança no método corrente, caso tenha, deixa o novo método executar
		if (stackThreads->top() != frameAux) {
			//empilha de volta os operandos desempilhados na ordem contrária que saíram
			flame->pilhaOperandos->empilharTypedElement(parametros[0]);
			while (count-- > 0) {
				flame->pilhaOperandos->empilharTypedElement(parametros[count]);
			}
			//volta com o pc para o opcode que vai ser executado novamente
			//ele já havia sido deslocado para o próximo opcode pela função getNBytes
			flame->pc -= 3;
			return;
		}

		//cria o frame no topo da pilha
		frameStack->adicionarFrame(instance->obterStaticClass()->obterClasseLeitorExibidor()->obterMethod(name, desc),
				instance->obterStaticClass()->obterClasseLeitorExibidor()->obterClassThatHasSerachedMethod(name, desc)->obterConstantPool());
		//adiciona os parâmetros ao vetor de variáveis locais
		frameStack->atualizarArgumentos(parametros);
	}
}

void Operations::invokestatic() {
	Frame *auxFrame = stackThreads->top();
	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);
	cp_info cp_element = flame->constantPool[indexbyte];

	if (cp_element.tag != METHOD_REF)
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para METHOD_REF!");

	string class_name = capturarIndiceDeReferencia(flame->constantPool, cp_element.info[0].u2);
	cp_info name_and_type_element = flame->constantPool[cp_element.info[1].u2];

	if (name_and_type_element.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[0].u2);
	string descriptor = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[1].u2);

	if (class_name == "java/lang/Object" && name == "registerNatives") {
		flame->pc += 3;
		return;
	}

	if (class_name.find("java/") != string::npos) {
		cerr << "Tentando invocar metodo estatico invalido: " << name << endl;
	} else {
		uint16_t quantidade = 0; // numero de argumentos contidos na pilha de operandos
		uint16_t i = 1; // pulando o primeiro '('
		while (descriptor[i] != ')') {
			char baseType = descriptor[i];
			if (baseType == 'D' || baseType == 'J') {
				quantidade += 2;
			} else if (baseType == 'L') {
				quantidade++;
				while (descriptor[++i] != ';')
					;
			} else if (baseType == '[') {
				quantidade++;
				while (descriptor[++i] == '[')
					;
				if (descriptor[i] == 'L')
					while (descriptor[++i] != ';')
						;
			} else {
				quantidade++;
			}
			i++;
		}

		vector<TypedElement> vectorParametros;
		for (int i = 0; i < quantidade; i++) {
			TypedElement elemento = flame->pilhaOperandos->desempilhaTyped();
			vectorParametros.insert(vectorParametros.begin(), elemento);
		}

		StaticClass *ce = MethodArea::obterClass(class_name);

		// Caso <clinit> seja empilhado.
		if (stackThreads->top() != auxFrame) {
			//empilha de volta os operandos desempilhados na ordem contrária que saíram
			while (quantidade-- > 0) {
				flame->pilhaOperandos->empilharTypedElement(vectorParametros[quantidade]);
			}
			//volta com o pc para o opcode que vai ser executado novamente
			//ele já havia sido deslocado para o próximo opcode pela função getNBytes
			flame->pc -= 3;
			return;
		}

		//cria o frame no topo da pilha
		frameStack->adicionarFrame(ce->obterClasseLeitorExibidor()->obterMethod(name, descriptor),
				ce->obterClasseLeitorExibidor()->obterClassThatHasSerachedMethod(name, descriptor)->obterConstantPool());

		//adiciona os parâmetros ao vetor de variáveis locais
		frameStack->atualizarArgumentos(vectorParametros);

	}

}

void Operations::invokeinterface() {
	Frame *auxFrame = stackThreads->top();
	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);
	cp_info cp_element = flame->constantPool[indexbyte];

	if (cp_element.tag != INTERFACE_REF) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para INTERFACE_REF!");
	}

	string class_name = capturarIndiceDeReferencia(flame->constantPool, cp_element.info[0].u2);
	cp_info name_and_type_element = flame->constantPool[cp_element.info[1].u2];
	if (name_and_type_element.tag != NAME_AND_TYPE) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para NAME_AND_TYPE!");
	}

	string name = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[0].u2);
	string descriptor = capturarIndiceDeReferencia(flame->constantPool, name_and_type_element.info[1].u2);

	if (class_name.find("java/") != string::npos) {
		throw runtime_error("Tentativa de invocar metodo de interface invalido!");
	} else {
		uint16_t num_args = 0; //numero de argumentos na pilha de operandos
		uint16_t i = 1; //pulando primeiro argumento '('
		while (descriptor[i] != ')') {
			char baseType = descriptor[i];
			if (baseType == 'D' || baseType == 'J') {      //64 bits
				num_args += 2;
			} else if (baseType == 'L') {                  //referencia - instancia de class
				num_args++;
				while (descriptor[++i] != ';')
					;
			} else if (baseType == '[') {                  // referencia
				num_args++;
				while (descriptor[++i] == '[')
					;
				if (descriptor[i] == 'L')
					while (descriptor[++i] != ';')
						;
			} else {
				num_args++;
			}
			i++;
		}

		vector<TypedElement> vectorParametros;
		for (int i = 0; i < num_args; i++) {
			TypedElement elemento = flame->pilhaOperandos->desempilhaTyped();
			vectorParametros.insert(vectorParametros.begin(), elemento);
		}

		TypedElement object_element = flame->pilhaOperandos->desempilhaTyped();
		if (object_element.type != TYPE_REFERENCE) {
			throw runtime_error("Elemento do topo da pilha não e uma referencia!");
		}
		vectorParametros.insert(vectorParametros.begin(), object_element);

		InstanceClass *instance = (InstanceClass *) object_element.value.pi;

		// Caso <clinit> seja empilhado.
		if (stackThreads->top() != auxFrame) {
			//empilha de volta os operandos desempilhados na ordem contrária que saíram
			while (num_args-- > 0) {
				flame->pilhaOperandos->empilharTypedElement(vectorParametros[num_args]);
			}
			//volta com o pc para o opcode que vai ser executado novamente
			//ele já havia sido deslocado para o próximo opcode pela função getNBytes
			flame->pc -= 3;
			return;
		}
		//cria o frame no topo da pilha
		frameStack->adicionarFrame(instance->obterStaticClass()->obterClasseLeitorExibidor()->obterMethod(name, descriptor),
				instance->obterStaticClass()->obterClasseLeitorExibidor()->obterClassThatHasSerachedMethod(name, descriptor)->obterConstantPool());
		//adiciona os parâmetros ao vetor de variáveis locais
		frameStack->atualizarArgumentos(vectorParametros);
	}
}

void Operations::func_new() {
	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);
	string classe = capturarIndiceDeReferencia(flame->constantPool, indexbyte);
	StaticClass *staticClass = MethodArea::obterClass(classe);

	if (staticClass == nullptr) {
		MethodArea::adicionarClasse(classe);
		staticClass = MethodArea::obterClass(classe);
	}

	flame->pilhaOperandos->empilharReferencia((int*) staticClass->obterInstanceClass());
}

void Operations::newarray() {
	uint8_t type = obterNBytesValue(1, &flame->pc);
	int32_t index = flame->pilhaOperandos->desempilha().is;

	if (index < 0)
		throw runtime_error("Negative Array Size.");

	int *array;

	switch (type) {
	case 4:
		array = (int*) new LocalVariables(index);
		break;
	case 5:
		array = (int*) new vector<uint8_t>(index);
		break;
	case 6:
		array = (int*) new LocalVariables(index);
		break;
	case 7:
		array = (int*) new LocalVariables(2 * index, true);
		break;
	case 8:
		array = (int*) new LocalVariables(index);
		break;
	case 9:
		array = (int*) new LocalVariables(index);
		break;
	case 10:
		array = (int*) malloc(sizeof(index));
		break;
	case 11:
		array = (int*) new LocalVariables(2 * index, true);
		break;
	default:
		array = (int*) new LocalVariables(index);
		break;
	}
	//cout << array << endl;
	flame->pilhaOperandos->empilharReferencia(array);
}

void Operations::anewarray() {
	//uint16_t indexbyte = getNBytesValue(2, &f->pc);
	obterNBytesValue(2, &flame->pc);
	int32_t count = flame->pilhaOperandos->desempilha().is;

	if (count < 0)
		throw runtime_error("Negative Array Size.");

	LocalVariables *localVariables = new LocalVariables(count * (BITS ? 2 : 1), BITS);
	for (int i = 0; i < count; i++) {
		TypedElement typedElement;
		typedElement.type = TYPE_REFERENCE;
		typedElement.value.pi = nullptr;
		localVariables->set(i, typedElement);
	}

	flame->pilhaOperandos->empilharReferencia((int*) localVariables);
}

void Operations::arraylength() {
	LocalVariables *localVariables;

	localVariables = (LocalVariables *) flame->pilhaOperandos->desempilha().pi;
	if (localVariables == nullptr)
		throw runtime_error("Null pointer");

	flame->pilhaOperandos->empilharInt(localVariables->obterMax());
}

void Operations::athrow() {
	int type = flame->pilhaOperandos->desempilhaTopoTipo();
	element_u element = flame->pilhaOperandos->desempilha();

	while (!flame->pilhaOperandos->estaVazia()) {
		flame->pilhaOperandos->desempilha();
	}

	flame->pilhaOperandos->empilhar(element, type);
}

void Operations::wide() {
	//seta a variavel global wide -> TRUE
	isWide = true;
	Operations::executarOperacao(obterNBytesValue(1, &flame->pc));
}

//terminar
void Operations::multianewarray() {

	uint16_t indexbyte = obterNBytesValue(2, &flame->pc);
	uint8_t dimensions = obterNBytesValue(1, &flame->pc);

	cp_info constantPool = flame->constantPool[indexbyte];
	if (constantPool.tag != CLASS) {
		throw runtime_error("Elemento da constant pool apontado por index, não é uma referencia para CLASS!");
	}

	string class_name = capturarIndiceDeReferencia(flame->constantPool, constantPool.info[0].u2);

	TypedElement element;

	int count = 0;

	while (class_name[count] == '[') {
		count++;
	}

	string multiArrayType = class_name.substr(count + 1, class_name.size() - count - 2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)

	switch (class_name[count]) {
	case 'L':
		if (multiArrayType != "java/lang/String") {
			MethodArea::obterClass(multiArrayType); // verifica se existe classe com esse nome
		}
		element.realType = RT_REFERENCE;
		element.type = TYPE_REFERENCE;
		break;
	case 'B':
		element.realType = RT_BYTE;
		element.type = TYPE_INT;
		break;
	case 'C':
		element.realType = RT_CHAR;
		element.type = TYPE_INT;
		break;
	case 'D':
		element.realType = RT_DOUBLE;
		element.type = TYPE_DOUBLE;
		break;
	case 'F':
		element.realType = RT_FLOAT;
		element.type = TYPE_FLOAT;
		break;
	case 'I':
		element.realType = RT_INT;
		element.type = TYPE_INT;
		break;
	case 'J':
		element.realType = RT_LONG;
		element.type = TYPE_LONG;
		break;
	case 'S':
		element.realType = RT_SHORT;
		element.type = TYPE_INT;
		break;
	case 'Z':
		element.realType = RT_BOOL;
		element.type = TYPE_INT;
		break;
	default:
		exit(1);
	}

	stack<int> count_dim;
	for (int i = 0; i < dimensions; i++) {
		// PRECISO VERIFICAR O TIPO (INT)?
		count_dim.push(flame->pilhaOperandos->desempilhaTyped().value.i);
	}

	int* p = (int*) (obterNewMultiArray(count_dim));

	element.value.pi = p;

	flame->pilhaOperandos->empilharTypedElement(element);

}

double Operations::obterValor(N_array array, stack<int> stackIndeces) {
	int index = 1;
	int aux = 0;

	for (int i = 0; (unsigned int) i < sizeof(array.dims) / sizeof(*(array.dims)); i++) {
		aux += array.dims[i] * stackIndeces.top();

		index = (aux * index) + aux;
		stackIndeces.pop();
	}

	return array.array[index];

}

N_array *Operations::obterNewMultiArray(stack<int> stackDimessoes) {
	int size = 1;
	int value;

	N_array *array = (N_array*) malloc(sizeof(N_array));

	int* dims = (int*) malloc(sizeof(double) * stackDimessoes.size());

	for (int i = 0; stackDimessoes.size() > 0; i++) {

		value = stackDimessoes.top();
		size *= value;
		dims[i] = value;
		stackDimessoes.pop();
	}

	int* p = (int*) malloc(sizeof(double) * size);

	for (int i = 0; i < size; i++) {
		p[i] = 0;
	}

	array->dims = dims;
	array->array = p;

	return array;

}

void Operations::ifnull() {
	int* ref = flame->pilhaOperandos->desempilha().pi;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (ref == nullptr)
		flame->pc += branchbyte - 3;
}

void Operations::ifnonnull() {
	int* ref = flame->pilhaOperandos->desempilha().pi;
	int16_t branchbyte = int16_t(obterNBytesValue(2, &flame->pc));

	if (ref != nullptr)
		flame->pc += branchbyte - 3;
}

void Operations::goto_w() {
	int32_t branchbyte = int32_t(obterNBytesValue(4, &flame->pc));

	flame->pc += branchbyte - 5;
}

void Operations::jsr_w() {
	int32_t offset = int32_t(obterNBytesValue(4, &flame->pc));

	flame->pilhaOperandos->empilharBool(flame->pc);

	flame->pc += offset - 5;
}

//Opcionais

void Operations::dup() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
	flame->pilhaOperandos->empilharTypedElement(typedElement);
	flame->pilhaOperandos->empilharTypedElement(typedElement);
}

void Operations::pop() {
	flame->pilhaOperandos->desempilhaTyped();
}

void Operations::pop2() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
	if (typedElement.type == TYPE_LONG || typedElement.type == TYPE_DOUBLE) {
		flame->pilhaOperandos->desempilhaTyped();
	}
}

void Operations::dup_x1() {
	if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
		TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
		if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
			flame->pilhaOperandos->desempilhaTyped();
		} else {
			flame->pilhaOperandos->empilharTypedElement(typedElement);
		}
	}
}

void Operations::dup_x2() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();
	if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		TypedElement typedElement3 = flame->pilhaOperandos->desempilhaTyped();
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement3);
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	} else {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	}
}

void Operations::dup2() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();

	if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	} else {
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	}
}

void Operations::dup2_x1() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();

	if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		TypedElement typedElement3 = flame->pilhaOperandos->desempilhaTyped();
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement3);
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	} else {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		flame->pilhaOperandos->empilharTypedElement(typedElement);
		flame->pilhaOperandos->empilharTypedElement(typedElement2);
		flame->pilhaOperandos->empilharTypedElement(typedElement);
	}
}

void Operations::dup2_x2() {
	TypedElement typedElement = flame->pilhaOperandos->desempilhaTyped();

	if (flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_LONG && flame->pilhaOperandos->desempilhaTopoTipo() != TYPE_DOUBLE) {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		TypedElement typedElement3 = flame->pilhaOperandos->desempilhaTyped();
		if (typedElement3.type == TYPE_LONG || typedElement3.type == TYPE_DOUBLE) {
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
			flame->pilhaOperandos->empilharTypedElement(typedElement3);
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
		} else {
			TypedElement typedElement4 = flame->pilhaOperandos->desempilhaTyped();
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
			flame->pilhaOperandos->empilharTypedElement(typedElement4);
			flame->pilhaOperandos->empilharTypedElement(typedElement3);
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
		}
	} else {
		TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
		if (typedElement2.type == TYPE_LONG || typedElement2.type == TYPE_DOUBLE) {
			flame->pilhaOperandos->empilharTypedElement(typedElement);
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
		} else {
			TypedElement typedElement3 = flame->pilhaOperandos->desempilhaTyped();
			flame->pilhaOperandos->empilharTypedElement(typedElement);
			flame->pilhaOperandos->empilharTypedElement(typedElement3);
			flame->pilhaOperandos->empilharTypedElement(typedElement2);
			flame->pilhaOperandos->empilharTypedElement(typedElement);
		}
	}
}

void Operations::swap() {
	TypedElement typedElement1 = flame->pilhaOperandos->desempilhaTyped();
	TypedElement typedElement2 = flame->pilhaOperandos->desempilhaTyped();
	flame->pilhaOperandos->empilharTypedElement(typedElement1);
	flame->pilhaOperandos->empilharTypedElement(typedElement2);
}

