/*!
 * \file OperandsStack.cpp
 * \brief Pilha de operandos
 */

#include "OperandsStack.h"

/**
 * Construtor
 */
OperandsStack::OperandsStack(int maxSize) :
		realMax(maxSize), max(2 * maxSize) {
	typePushed = false;
}

/**
 * Retorna topo da pilha de tipos
 */
uint8_t OperandsStack::desempilhaTopoTipo() {
	return ((!this->estaVazia()) ? (this->stackTipos.top()) : (-1));
}

/**
 * Retorna topo da pilha de valores
 */
Element OperandsStack::desempilhaTopoValor() {
	Element ret;

	//Se pilha estiver vazia, retorna elemento vazio
	if (this->estaVazia()) {
		return ret;
	}

	//Pega primeiro valor da pilha de valores
	ret.i = this->stackElementos.top();

	//Se o tipo do valor empilhado � maior que 32bits, concatena os dois primeiros elementos da pilha na variavel de retorno.
	if (this->stackTipos.top() == TYPE_LONG || this->stackTipos.top() == TYPE_DOUBLE
			|| (this->stackTipos.top() == TYPE_REFERENCE && bits64)) {
		uint32_t aux = ret.i;
		this->stackElementos.pop();
		ret.l = int64_t((int64_t(ret.i) << 32) + this->stackElementos.top());
		this->stackElementos.push(aux);
	}

	return ret;
}

/**
 * Retorna e remove topo da pilha de valores e da pop na pilha de tipos
 */
Element OperandsStack::desempilha() {
	Element ret;
	//Se a pilha estiver vazia, retorna um elemento vazio.
	if (this->estaVazia()) {
		return ret;
	}

	//Pega o valor do topo da pilha
	ret = this->desempilhaTopoValor();

	//Da pop na pilha de valores
	this->stackElementos.pop();

	//Se o valor recebendo pop tiver mais de 32bits, da pop em mais um item (um long fica como dois itens na pilha)
	if (this->stackTipos.top() == TYPE_LONG || this->stackTipos.top() == TYPE_DOUBLE
			|| (this->stackTipos.top() == TYPE_REFERENCE && bits64)) {
		this->stackElementos.pop();
	}

	//remove da pilha de tipos o tipo do elemento que sofreu pop
	this->stackTipos.pop();
	this->stackTiposReais.pop();

	return ret;
}

/**
 * Retorna estrutura com valor e tipo associados e da pop na pilha de valores e na de tipos
 */
TypedElement OperandsStack::desempilhaTyped() {
	TypedElement typedElement;
	typedElement.type = this->stackTipos.top();
	typedElement.realType = this->stackTiposReais.top();
	typedElement.value = this->desempilha();

	return typedElement;
}

/**
 * Auxiliar do printAll, imprime a string correspondente ao tipo do elemento
 */
string OperandsStack::obterString() {
	stringstream ret;

	//Switch no tipo do elemento do topo da pilha de operandos
	switch (this->desempilhaTopoTipo()) {
	case TYPE_INT:
		ret << "(int) " << int(this->desempilhaTopoValor().i);
		break;
	case TYPE_LONG:
		ret << "(long) " << long(this->desempilhaTopoValor().l);
		break;
	case TYPE_FLOAT:
		ret << "(float) " << this->desempilhaTopoValor().f;
		break;
	case TYPE_DOUBLE:
		ret << "(double) " << this->desempilhaTopoValor().d;
		break;
	case TYPE_BOOL:
		ret << "(bool) " << (int) this->desempilhaTopoValor().b;
		break;
	case TYPE_REFERENCE:
		ret << "(reference) " << this->desempilhaTopoValor().pi;
		break;
	}

	return ret.str();
}

/**
 * Empilha um int na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharInt(int x) {
	//Se chegou no limite da pilha, n�o empilha
	if (this->obterTamanho() == max) {
		throw out_of_range("Excedeu o limite maximo da pilha!");
	}

	//empilha o tipo int na pilha de tipos
	this->stackTipos.push(TYPE_INT);
	if (!typePushed) {
		this->stackTiposReais.push(RT_INT);
	}

	//empilha o valor na pilha de valores
	this->stackElementos.push(x);

	typePushed = false;
}

/**
 * Empilha um float na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharFloat(float x) {
	//Se chegou no limite da pilha, n�o empilha
	if (this->obterTamanho() == max) {
		throw out_of_range("Excedeu o limite maximo da pilha!");
	}

	Element aux;
	aux.f = x;

	//empilha o tipo float na pilha de tipos
	this->stackTipos.push(TYPE_FLOAT);
	if (!typePushed)
		this->stackTiposReais.push(RT_FLOAT);

	//empilha o valor na pilha de valores
	this->stackElementos.push(aux.i);

	typePushed = false;
}

/**
 * Empilha um double na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharDouble(double x) {
	//Se n�o houver 2 espa�os dispon�veis na pilha, n�o empilha
	if (this->obterTamanho() + 1 >= max) {
		throw out_of_range("Excedeu o limite maximo da pilha!");
	}

	Element aux;
	aux.d = x;

	//empilha o tipo double na pilha de tipos
	this->stackTipos.push(TYPE_DOUBLE);
	if (!typePushed) {
		this->stackTiposReais.push(RT_DOUBLE);
	}

	//Empilha 32 bits inferiores do valor 
	this->stackElementos.push(aux.i);
	//Traz os 32 bits superiores para baixo
	aux.l >>= 32;
	//Empilha 32 bits inferiores do valor (superiores)
	this->stackElementos.push(aux.i);

	typePushed = false;
}

/**
 * Empilha um long na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharLong(int64_t _x) {
	uint64_t x = _x;
	//Se n�o houver 2 espa�os dispon�veis na pilha, n�o empilha
	if (this->obterTamanho() + 1 >= max) {
		throw out_of_range("Excedeu o limite maximo da pilha!");
	}

	//empilha o tipo long na pilha de tipos
	this->stackTipos.push(TYPE_LONG);
	if (!typePushed) {
		this->stackTiposReais.push(RT_LONG);
	}

	//Empilha 32 bits inferiores do valor
	this->stackElementos.push(x);
	//Traz os 32 bits superiores para baixo
	x >>= 32;
	//Empilha 32 bits inferiores do valor (superiores)
	this->stackElementos.push(x);

	typePushed = false;
}

/**
 * Empilha um bool na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharBool(bool x) {
	//Se chegou no limite da pilha, n�o empilha
	if (this->obterTamanho() == max) {
		throw out_of_range("Excedeu o limite maximo da pilha!");
	}

	Element aux;
	aux.b = x;

	//empilha o tipo bool na pilha de tipos
	this->stackTipos.push(TYPE_BOOL);
	if (!typePushed) {
		this->stackTiposReais.push(RT_BOOL);
	}

	//empilha o valor na pilha de valores
	this->stackElementos.push(aux.i);

	typePushed = false;
}

/**
 * Empilha uma referencia na pilha de valores e seu tipo na pilha de tipos
 */
void OperandsStack::empilharReferencia(int *x) {
	//Se chegou no limite da pilha, não empilha
	if (this->obterTamanho() + bits64 >= max) {
		throw out_of_range("Passou do limite maximo da pilha!");
	}

	Element aux;
	aux.pi = x;

	//empilha o tipo referencia na pilha de tipos
	this->stackTipos.push(TYPE_REFERENCE);
	if (!typePushed) {
		this->stackTiposReais.push(RT_REFERENCE);
	}

	//empilha o valor na pilha de valores
	this->stackElementos.push(aux.i);

	//Se a referencia for de 64bits (x64), empilha mais um valor na pilha de valores
	if (bits64) {
		aux.l >>= 32;
		this->stackElementos.push(aux.i);
	}

	typePushed = false;
}

/**
 * Empilha valor e tipo de estrutura com valor e tipo associados
 */
void OperandsStack::empilharTypedElement(TypedElement typedElement) {
	this->stackTiposReais.push(typedElement.realType);
	typePushed = true;
	this->empilhar(typedElement.value, typedElement.type);
}

/**
 * Chama a função para empilhar de acordo com o tipo do elemento recebido
 */
void OperandsStack::empilhar(Element element, uint8_t tipo) {
	switch (tipo) {
	case TYPE_DOUBLE:
		this->empilharDouble(element.d);
		break;
	case TYPE_LONG:
		//this->empilharLong(long(x.l)); //Implementar método push para longs
		break;
	case TYPE_FLOAT:
		this->empilharFloat(element.f);
		break;
	case TYPE_INT:
		this->empilharInt(int(element.i));
		break;
	case TYPE_REFERENCE:
		this->empilharReferencia((int*) (element.pi));
		break;
	case TYPE_BOOL:
		this->empilharInt(element.b);
		break;
	default:
		break;
	}
}

/**
 * Retorna valor m�ximo da pilha de operandos
 */
int OperandsStack::obterTamanhoMaximoPilha() {
	return this->realMax;
}

/**
 * Retorna o tamanho da pilha de valores
 */
int OperandsStack::obterTamanho() {
	return this->stackElementos.size();
}

/**
 * Percorre e imprime toda a pilha de operandos
 */
void OperandsStack::imprimirTodasOperacoes() {
	OperandsStack aux(this->max);

	while (!this->estaVazia()) {
		cout << this->obterString() << endl;
		aux.empilharTypedElement(this->desempilhaTyped());
	}

	while (!aux.estaVazia()) {
		this->empilharTypedElement(aux.desempilhaTyped());
	}
}

/**
 * returna 1 se a pilha de valores estiver vazia, 0 caso contr�rio
 */
bool OperandsStack::estaVazia() {
	return this->stackElementos.empty();
}
