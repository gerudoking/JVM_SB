/*!
 * \file classeVariaveisLocais.cpp
 * \brief
 */

#include "classeVariaveisLocais.h"

VariaveisLocais::VariaveisLocais(uint16_t maxSize) :
		max(maxSize), realMax(2 * maxSize), dois(false) {
	elements = (uint32_t *) calloc(max * 2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max * 2, sizeof(uint8_t));
}

VariaveisLocais::VariaveisLocais(uint16_t maxSize, bool slots) :
		max(maxSize), realMax(2 * maxSize), dois(slots) {
	elements = (uint32_t *) calloc(max * 2, sizeof(uint32_t));
	types = (uint8_t *) calloc(max * 2, sizeof(uint8_t));
}

VariaveisLocais::~VariaveisLocais() {
	if (elements)
		free(elements);
	if (types)
		free(types);
}

void VariaveisLocais::set(int index, TypedElement x) {
	if (index < 0)
		throw std::runtime_error("Indice fora dos limites!");

	index *= 2;

	this->types[index] = x.type;
	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) {
		if (index + 1 >= realMax)
			throw std::runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
		this->elements[++index] = int(x.value.l >> 32);
		this->types[index] = INVALID;
	} else {
		if (index >= realMax)
			throw std::runtime_error("Indice fora dos limites!");

		this->elements[index] = x.value.i;
	}
}

TypedElement VariaveisLocais::get(int index) const {
	index *= 2;
	if (index >= realMax || index < 0)
		throw std::runtime_error("Indice fora dos limites!");

	if (this->types[index] == INVALID)
		throw std::runtime_error("A posicao acessada contem a segunda parte de uma informacao de 2 slots!");

	TypedElement ret;
	ret.type = this->types[index];

	if (this->types[index] == TYPE_LONG || this->types[index] == TYPE_DOUBLE || (this->types[index] == TYPE_REFERENCE && BITS)) {
		ret.value.l = (int64_t(this->elements[index + 1]) << 32) + this->elements[index];
	} else {
		ret.value.i = this->elements[index];
	}

	return ret;
}

void VariaveisLocais::imprimirAll() const {
	for (int i = 0; i < max; ++i) {
		std::cout << i << ": ";

		switch (this->types[i]) {
		case INVALID:
			std::cout << "(Extensao do indice anterior)" << std::endl;
			break;
		case TYPE_NOT_SET:
			std::cout << "(Posicao ainda nao inicializada)" << std::endl;
			break;
		case TYPE_INT:
			std::cout << "(INT) " << this->get(i).value.i << std::endl;
			break;
		case TYPE_FLOAT:
			std::cout << "(FLOAT) " << this->get(i).value.f << std::endl;
			break;
		case TYPE_LONG:
			std::cout << "(LONG) " << this->get(i).value.l << std::endl;
			break;
		case TYPE_DOUBLE:
			std::cout << "(DOUBLE) " << this->get(i).value.d << std::endl;
			break;
		case TYPE_BOOL:
			std::cout << "(BOOL) " << (int) this->get(i).value.b << std::endl;
			break;
		case TYPE_REFERENCE:
			std::cout << "(REFERENCE) " << this->get(i).value.pi << std::endl;
			break;
		}
	}
}

int VariaveisLocais::obterMax() const {
	return max;
}

const TypedElement VariaveisLocais::operator[](const int index) const {
	return this->get(index);
}
