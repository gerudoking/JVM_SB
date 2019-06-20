/*!
 * \file MethodArea.cpp
 * \brief
 */

#include "MethodArea.h"

map<string, StaticClass*> MethodArea::mapClasses;
string MethodArea::path = "";
FrameStack *MethodArea::frameStack = nullptr;

StaticClass *MethodArea::obterClass(string classe) {
	for (map<string, StaticClass*>::const_iterator i = mapClasses.begin(); i != mapClasses.end(); i++) {
		if (i->first == classe) {
			return i->second;
		}
	}
	return nullptr;
}

bool MethodArea::adicionarClasse(string classe) {
	for (map<string, StaticClass*>::const_iterator i = mapClasses.begin(); i != mapClasses.end(); i++) {
		if (i->first == classe) {
			return false;
		}
	}

	LeitorExibidor *leitorExibidor = new LeitorExibidor(string(path + classe));

	if (!leitorExibidor->validarExtensao()) {
		delete leitorExibidor;
		leitorExibidor = new LeitorExibidor(string(path + classe + ".class"));
	}

	if (leitorExibidor->carregar()) {
		return false;
	}

	StaticClass *staticClass = new StaticClass(leitorExibidor);
	mapClasses.insert(pair<string, StaticClass*>(classe, staticClass));

	if (leitorExibidor->existeClinit()) {
		frameStack->adicionarFrame(leitorExibidor->obterClinit(), leitorExibidor->obterConstantPool());
	}

	return true;
}

bool MethodArea::adicionarClasse(LeitorExibidor *leitorExibidor) {
	if (leitorExibidor->obterStatus() == -1) {
		leitorExibidor->carregar();
	}

	switch (leitorExibidor->obterStatus()) {
	case 0:
		break;
	default:
		return false;
	}

	StaticClass *staticClass = new StaticClass(leitorExibidor);
	string indiceReferencia = capturarIndiceDeReferencia(leitorExibidor->obterConstantPool(), leitorExibidor->obterThis_class());

	mapClasses.insert(pair<string, StaticClass*>(indiceReferencia, staticClass));

	if (leitorExibidor->existeClinit()) {
		frameStack->adicionarFrame(leitorExibidor->obterClinit(), leitorExibidor->obterConstantPool());
	}

	return true;
}

void MethodArea::atualizarFrameStack(FrameStack *novoFrameStack) {
	frameStack = novoFrameStack;
}
