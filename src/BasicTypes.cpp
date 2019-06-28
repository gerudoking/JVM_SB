/*!
 * \file BasicTypes.cpp
 * \brief
 */

#include "BasicTypes.h"

U2 lerU2(FILE *arquivoClass) {
	unsigned short u2 = 0;
	unsigned char aux;

	fread(&u2, 1, 1, arquivoClass);
	fread(&aux, 1, 1, arquivoClass);

	u2 <<= 8;
	u2 |= aux;

	return u2;
}

U1 lerU1(FILE *arquivoClass) {
	unsigned char u1;

	fread(&u1, 1, 1, arquivoClass);

	return u1;
}

U1 * lerUTF8(FILE* arquivoClass, int tamanho) {

	vector<unsigned char> *vectorUTF8 = new vector<unsigned char>(tamanho);

	for (int i = 0; i < tamanho; i++) {
		vectorUTF8->at(i) = lerU1(arquivoClass);
	}

	return (U1*) vectorUTF8;
}

U4 lerU4(FILE *arquivoClass) {
	unsigned int u4 = 0;
	unsigned char aux;

	for (int i = 0; i < 4; i++) {
		u4 <<= 8;
		fread(&aux, 1, 1, arquivoClass);
		u4 |= aux;
	}

	return u4;
}

string obterUTF8(unsigned char * s, int tamanho) {
	vector<unsigned char> *vectorUtf8 = (vector<unsigned char> *) s;
	string utf8 = "";
	tamanho = vectorUtf8->size();
	int i = 0;

	while (i < tamanho) {
		if (!(vectorUtf8->at(i) & 0x80)) { //utf8 only with 1 bit
			utf8.push_back(vectorUtf8->at(i));
		} else {
			unsigned short auxCurrent;
			if (!(vectorUtf8->at(i + 1) & 0x20)) { //utf8 of 2 bytes
				auxCurrent = ((vectorUtf8->at(i) & 0x1f) << 6) + (vectorUtf8->at(i + 1) & 0x3f);
			} else { //utf8 of 3 bytes
				auxCurrent = ((vectorUtf8->at(i) & 0xf) << 12) + ((vectorUtf8->at(i + 1) & 0x3f) << 6) + (vectorUtf8->at(i + 2) & 0x3f);
				i++;
			}
			i++;
			utf8.push_back(auxCurrent);
		}
		i++;
	}

	return utf8;
}

string converter_double_to_string(double d) {
	stringstream valor;
	switch (verificarDouble(d)) {
	case 0:
		valor << d;
		break;
	case 1:
		valor << "+Inf";
		break;
	case 2:
		valor << "-Inf";
		break;
	case 3:
		valor << "NaN";
		break;
	}

	return valor.str();
}

//return 1 for +infinity, 2 for -inifity, 3 for NaN e 0 for number inside bound
int verificarFloat(float f) {
	int valor = 0;
	Element element;
	element.f = f;

	if ((element.i >= 0x7f800001 && element.i <= 0x7fffffff) || (element.i >= 0xff800001 && element.i <= 0xffffffff)) {
		valor = 3;
	} else if (element.i == 0x7f800000) {
		valor = 1;
	} else if (element.i == 0xff800000) {
		valor = 2;
	}

	return valor;
}

//return 1 for +infinity, 2 for -inifity, 3 for NaN e 0 for number inside bound
int verificarDouble(double d) {
	int valor = 0;
	Element element;
	element.d = d;

	if ((element.l >= 0x7ff0000000000001L && element.l <= 0x7ffffffffffffL)
			|| (element.l >= 0xfff0000000000001L && element.l <= 0xffffffffffffffffL)) {
		valor = 3;
	} else if (element.l == 0x7ff0000000000000L) {
		valor = 1;
	} else if (element.l == 0xfff0000000000000L) {
		valor = 2;
	}

	return valor;
}

string converter_float_to_string(float f) {
	stringstream valor;
	switch (verificarFloat(f)) {
	case 0:
		valor << f;
		break;
	case 1:
		valor << "+Inf";
		break;
	case 2:
		valor << "-Inf";
		break;
	case 3:
		valor << "NaN";
		break;
	}

	return valor.str();
}

long converter_u4_to_long(ClassLoaderType classLoaderTypeMaior, ClassLoaderType classLoaderTypeMenor) {
	int64_t valor;

	valor = (((int64_t) classLoaderTypeMaior.u4) << 32) | classLoaderTypeMenor.u4;

	return valor;
}

double converter_u4_to_double(ClassLoaderType high, ClassLoaderType low) {
	double valor;
	uint64_t checkBoundaries = converter_u4_to_long(high, low);

	if (checkBoundaries == 0x7ff0000000000000L) {
		//return infinity??
	} else if (checkBoundaries == 0xfff0000000000000L) {
		//return negative infinity??
	} else if ((checkBoundaries >= 0x7ff0000000000001L) && (checkBoundaries <= 0x7ffffffffffffL)) {
		//return NaN??
	} else if ((checkBoundaries >= 0xfff0000000000001L) && (checkBoundaries <= 0xffffffffffffffffL)) {
		//return NaN??
	} else {
		int64_t s = ((checkBoundaries >> 63) == 0) ? 1 : -1;
		int64_t e = ((checkBoundaries >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (checkBoundaries & 0xfffffffffffffL) << 1 : (checkBoundaries & 0xfffffffffffffL) | 0x10000000000000L;

		valor = s * m * pow(2, (e - 1075));
	}

	return valor;
}

float converter_u4_to_float(ClassLoaderType classLoaderType) {
	float valor;

	int s = ((classLoaderType.u4 >> 31) == 0) ? 1 : -1;
	int e = ((classLoaderType.u4 >> 23) & 0xff);
	int m = (e == 0) ? (classLoaderType.u4 & 0x7fffff) << 1 : (classLoaderType.u4 & 0x7fffff) | 0x800000;

	valor = s * m * pow(2, (e - 150));

	return valor;
}

