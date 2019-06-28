/*!
 * \file MethodArea.cpp
 * \brief
 */

#include "MethodArea.h"

map<string, StaticClass*> MethodArea::mapStaticClass;
string MethodArea::path = "";
PilhaJVM *MethodArea::pilhaJVM = nullptr;

StaticClass *MethodArea::obterClass(string classe) {
	for (map<string, StaticClass*>::const_iterator i = mapStaticClass.begin(); i != mapStaticClass.end(); i++) {
		if (i->first == classe) {
			return i->second;
		}
	}
	return nullptr;
}

bool MethodArea::adicionarClasse(string classe) {
	for (map<string, StaticClass*>::const_iterator i = mapStaticClass.begin(); i != mapStaticClass.end(); i++) {
		if (i->first == classe) {
			return false;
		}
	}

	ClassFile *classFile = new ClassFile(string(path + classe));

	if (!classFile->validarExtensao()) {
		delete classFile;
		classFile = new ClassFile(string(path + classe + ".class"));
	}

	if (classFile->carregar()) {
		return false;
	}

	StaticClass *staticClass = new StaticClass(classFile);
	mapStaticClass.insert(pair<string, StaticClass*>(classe, staticClass));

	if (classFile->existeClinit()) {
		pilhaJVM->adicionarFrame(classFile->obterClinit(), classFile->obterConstantPool());
	}

	return true;
}

bool MethodArea::adicionarClasse(ClassFile *classFile) {
	if (classFile->obterStatus() == -1) {
		classFile->carregar();
	}

	switch (classFile->obterStatus()) {
	case 0:
		break;
	default:
		return false;
	}

	StaticClass *staticClass = new StaticClass(classFile);
	string indiceReferencia = capturarIndiceDeReferencia(classFile->obterConstantPool(), classFile->obterThis_class());

	mapStaticClass.insert(pair<string, StaticClass*>(indiceReferencia, staticClass));

	if (classFile->existeClinit()) {
		pilhaJVM->adicionarFrame(classFile->obterClinit(), classFile->obterConstantPool());
	}

	return true;
}

void MethodArea::atualizarPilhaJVM(PilhaJVM *pPilhaJVM) {
	pilhaJVM = pPilhaJVM;
}
