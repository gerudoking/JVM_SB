/*!
 * \file LocalVariables.cpp
 * \brief
 */

#include "LocalVariables.h"

LocalVariables::LocalVariables(uint16_t maxSize) :
		max(maxSize), realMax(2 * maxSize), dois(false) {
	elements = (uint32_t *) calloc(max * 2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max * 2, sizeof(uint8_t));
}

LocalVariables::LocalVariables(uint16_t maxSize, bool slots) :
		max(maxSize), realMax(2 * maxSize), dois(slots) {
	elements = (uint32_t *) calloc(max * 2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max * 2, sizeof(uint8_t));
}

LocalVariables::~LocalVariables() {
	if (elements)
		free(elements);
	if (types)
		free(types);
}

void LocalVariables::set(int index, TypedElement x) {
	if (index < 0)
		throw runtime_error("Indice fora dos limites!");

	index *= 2;

	this->types[index] = x.type;
	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) {
		if (index + 1 >= realMax)
			throw runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
		this->elements[++index] = int(x.value.l >> 32);
		this->types[index] = INVALID;
	} else {
		if (index >= realMax)
			throw runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
	}
}

TypedElement LocalVariables::get(int index) const {
	index *= 2;
	if (index >= realMax || index < 0)
		throw runtime_error("Indice fora dos limites!");

	if (this->types[index] == INVALID)
		throw runtime_error("A posicao acessada contem a segunda parte de uma informacao de 2 slots!");

	TypedElement typedElement;
	typedElement.type = this->types[index];

	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) {
		typedElement.value.l = (int64_t(this->elements[index + 1]) << 32) + this->elements[index];
	} else {
		typedElement.value.i = this->elements[index];
	}

	return typedElement;
}

void LocalVariables::imprimirAll() const {
	for (int i = 0; i < max; ++i) {
		cout << i << ": ";

		switch (this->types[i]) {
		case INVALID:
			cout << "(Extensao do indice anterior)" << endl;
			break;
		case TYPE_NOT_SET:
			cout << "(Posicao ainda nao inicializada)" << endl;
			break;
		case TYPE_INT:
			cout << "(INT) " << this->get(i).value.i << endl;
			break;
		case TYPE_FLOAT:
			cout << "(FLOAT) " << this->get(i).value.f << endl;
			break;
		case TYPE_LONG:
			cout << "(LONG) " << this->get(i).value.l << endl;
			break;
		case TYPE_DOUBLE:
			cout << "(DOUBLE) " << this->get(i).value.d << endl;
			break;
		case TYPE_BOOL:
			cout << "(BOOL) " << (int) this->get(i).value.b << endl;
			break;
		case TYPE_REFERENCE:
			cout << "(REFERENCE) " << this->get(i).value.pi << endl;
			break;
		}
	}
}

int LocalVariables::obterMax() const {
	return max;
}

const TypedElement LocalVariables::operator[](const int index) const {
	return this->get(index);
}
