/*!
 * \file InstanceClass.cpp
 * \brief
 */

#include "InstanceClass.h"

InstanceClass::InstanceClass(StaticClass* staticClass) {
	this->staticClass = staticClass;

	int tamanho = staticClass->obterClassFile()->obterFieldsCount();
	Field_info *field = staticClass->obterClassFile()->obterFields();

	for (int i = 0; i < tamanho; i++) {
		if ((field[i].accessFlags & 0x08) == 0) {
			TypedElement *typedElement = (TypedElement *) malloc(sizeof(TypedElement));
			typedElement->value.l = 0;
			string type = capturarIndiceDeReferencia(staticClass->obterClassFile()->obterConstantPool(), field[i].descriptor_index);

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
			string nomeField = capturarIndiceDeReferencia(staticClass->obterClassFile()->obterConstantPool(), field[i].name_index);
			mapLocalFields.insert(pair<string, TypedElement*>(nomeField, typedElement));
		}
	}
}

TypedElement InstanceClass::obterField(string field) {
	TypedElement typedElement;
	typedElement.type = TYPE_NOT_SET;

	for (map<string, TypedElement*>::const_iterator mapField = mapLocalFields.begin(); mapField != mapLocalFields.end(); mapField++) {
		if (mapField->first == field) {
			return *(mapField->second);
		}
	}

	return typedElement;
}

StaticClass *InstanceClass::obterStaticClass() {
	return staticClass;
}

bool InstanceClass::atualizarField(string field, TypedElement typedElement) {
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapLocalFields.begin();

	while (mapField != mapLocalFields.end()) {
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

bool InstanceClass::atualizarFieldFinals(string field, TypedElement typedElement) {
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapLocalFields.begin();

	while (mapField != mapLocalFields.end()) {
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

void InstanceClass::imprimirInstance() {
	map<string, TypedElement*>::const_iterator mapField;
	mapField = mapLocalFields.begin();

	while (mapField != mapLocalFields.end()) {
		cout << mapField->first << endl;
		mapField++;
	}
}