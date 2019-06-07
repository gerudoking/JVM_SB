/*!
 * \file ClasseEstatica.cpp
 * \brief
 */

#include "classeEstatica.h"

ClasseEstatica::ClasseEstatica(LeitorExibidor *leitorExibidor) {
	this->leitorExibidor = leitorExibidor; ///class file lido
	int tamanho = leitorExibidor->obterFieldsCount(); ///get numero de fields
	field_info *field = leitorExibidor->obterFields();

	for (int i = 0; i < tamanho; i++) {
		if ((field[i].accessFlags & 0x08) && (field[i].accessFlags & 0x010) == 0) {
			TypedElement *typedElement = (TypedElement *) malloc(sizeof(TypedElement));
			typedElement->value.l = 0;
			string type = capturarIndiceDeReferencia(leitorExibidor->obterConstantPool(), field[i].descriptor_index);

			switch (type[0]) {
			case 'B':
				typedElement->type = TYPE_BOOL;
				break;
			case 'C':
				typedElement->type = TYPE_INT;
				break;
			case 'D':
				typedElement->type = TYPE_DOUBLE;
				break;
			case 'F':
				typedElement->type = TYPE_FLOAT;
				break;
			case 'I':
				typedElement->type = TYPE_INT;
				break;
			case 'J':
				typedElement->type = TYPE_LONG;
				break;
			case 'L':
				typedElement->type = TYPE_REFERENCE;
				break;
			case 'S':
				typedElement->type = TYPE_INT;
				break;
			case 'Z':
				typedElement->type = TYPE_BOOL;
				break;
			case '[':
				typedElement->type = TYPE_REFERENCE;
				break;
			}

			string nomeField = capturarIndiceDeReferencia(leitorExibidor->obterConstantPool(), field[i].name_index);
			mapStaticFields.insert(pair<string, TypedElement*>(nomeField, typedElement));
		}
	}
}

TypedElement ClasseEstatica::obterField(string field) {
	TypedElement typedElement;
	typedElement.type = TYPE_NOT_SET;
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapStaticFields.begin();

	while (mapField != mapStaticFields.end()) {
		if (mapField->first == field) {
			return *(mapField->second);
		}
		mapField++;
	}

	return typedElement;
}

bool ClasseEstatica::atualizarField(string field, TypedElement typedElement) {
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapStaticFields.begin();

	while (mapField != mapStaticFields.end()) {
		if (mapField->first == field) {
			if (mapField->second->type == typedElement.type) {
				*(mapField->second) = typedElement;
				return true;
			} else {
				break;
			}
		}
		mapField++;
	}

	return false;
}

bool ClasseEstatica::atualizarFieldFinals(string field, TypedElement typedElement) {
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapStaticFields.begin();

	while (mapField != mapStaticFields.end()) {
		if (mapField->first == field) {
			if (mapField->second->type == typedElement.type) {
				*(mapField->second) = typedElement;
				return true;
			} else {
				break;
			}
		}
		mapField++;
	}

	return false;
}

LeitorExibidor *ClasseEstatica::obterClasseLeitorExibidor() {
	return leitorExibidor;
}

ClasseInstancia *ClasseEstatica::obterInstanceClasseInstancia() {
	ClasseInstancia *classeInstancia = new ClasseInstancia(this);
	Heap::adicionarInstancia(classeInstancia);

	return classeInstancia;
}
