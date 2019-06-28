/*!
 * \file Attributes.cpp
 * \brief
 */

#include "Attributes.h"

T_exception_table* lerExceptionHandler(FILE* arquivoEntrada) {
	T_exception_table* tabelaException = (T_exception_table*) malloc(sizeof(T_exception_table));

	tabelaException->start_pc = lerU2(arquivoEntrada);
	tabelaException->end_pc = lerU2(arquivoEntrada);
	tabelaException->handler_pc = lerU2(arquivoEntrada);
	tabelaException->catch_type = lerU2(arquivoEntrada);

	return tabelaException;
}

T_info* lerAttributeInfo(FILE* arquivoEntrada, Cp_info *constantPool, unsigned short indice, unsigned short tamanho) {
	T_info* TabelaInfo = (T_info*) malloc(sizeof(T_info));

	string nome = capturarIndiceDeReferencia(constantPool, indice);

	if (nome == "ConstantValue") {
		TabelaInfo->constantValue.constantvalue_index = lerU2(arquivoEntrada);
	}

	else if (nome == "Code") {
		TabelaInfo->codeAttribute.max_stack = lerU2(arquivoEntrada);
		TabelaInfo->codeAttribute.max_locals = lerU2(arquivoEntrada);
		TabelaInfo->codeAttribute.code_length = lerU4(arquivoEntrada);

		unsigned char* list_code = (unsigned char*) malloc(sizeof(T_exception_table) * TabelaInfo->codeAttribute.code_length);

		for (int i = 0; (unsigned int) i < TabelaInfo->codeAttribute.code_length; i++) {
			list_code[i] = lerU1(arquivoEntrada);
		}
		TabelaInfo->codeAttribute.codigo = list_code;

		TabelaInfo->codeAttribute.exception_table_length = lerU2(arquivoEntrada);

		T_exception_table** table_of_exception = (T_exception_table**) malloc(
				sizeof(T_exception_table) * TabelaInfo->codeAttribute.exception_table_length);

		for (int i = 0; i < TabelaInfo->codeAttribute.exception_table_length; i++) {
			table_of_exception[i] = lerExceptionHandler(arquivoEntrada);
		}

		TabelaInfo->codeAttribute.exception_table = table_of_exception;

		TabelaInfo->codeAttribute.attribute_count = lerU2(arquivoEntrada);

		Attribute_info* attributes_infos = (Attribute_info*) malloc(sizeof(Attribute_info) * TabelaInfo->codeAttribute.attribute_count);

		for (int i = 0; i < TabelaInfo->codeAttribute.attribute_count; i++) {
			attributes_infos[i] = lerAttribute(arquivoEntrada, constantPool);
		}
		TabelaInfo->codeAttribute.attributes = attributes_infos;
	}

	else if (nome == "Exceptions") {
		TabelaInfo->exception.number_of_exceptions = lerU2(arquivoEntrada);

		unsigned short* exceptions = (unsigned short*) malloc(sizeof(unsigned short) * TabelaInfo->exception.number_of_exceptions);

		for (int i = 0; i < TabelaInfo->exception.number_of_exceptions; i++) {
			exceptions[i] = lerU2(arquivoEntrada);
		}
		TabelaInfo->exception.exception_index_table = exceptions;
	}

	else {
		for (int i = 0; i < tamanho; i++) {
			lerU1(arquivoEntrada);
		}
	}

	return TabelaInfo;
}

Attribute_info lerAttribute(FILE* arquivoEntrada, Cp_info *constantPool) {
	Attribute_info attribute;

	attribute.name_index = lerU2(arquivoEntrada);
	attribute.length = lerU4(arquivoEntrada);

	attribute.info = lerAttributeInfo(arquivoEntrada, constantPool, attribute.name_index, attribute.length);

	return attribute;
}

Attribute_info* lerTodosAttributes(FILE* arquivoEntrada, Cp_info *constantPool, int tamanho) {
	Attribute_info* attributes_reading = (Attribute_info*) malloc(sizeof(Attribute_info) * tamanho);

	int i;

	for (i = 0; i < tamanho; i++) {
		attributes_reading[i] = lerAttribute(arquivoEntrada, constantPool);
	}

	return attributes_reading;
}

void imprimirTodosAttributes(Attribute_info* attribute, Cp_info* constantPool, int tamanho) {
	int i;

	for (i = 0; i < tamanho; i++) {
		cout << "\tAtributo " << i << ": " << endl;
		imprimirAttribute(attribute[i], constantPool);
	}
}

void imprimirAttribute(Attribute_info attribute, Cp_info *constantPool) {
	string name_of_attribute = capturarIndiceDeReferencia(constantPool, attribute.name_index);

	cout << "\t\tNome: cp info #" << attribute.name_index << " " << name_of_attribute << endl;

	cout << "\t\tNúmero de Atributos: " << attribute.length << endl;

	if (name_of_attribute == "ConstantValue") {
		cout << "\t\tValor da Constante: " << attribute.info->constantValue.constantvalue_index << endl;
	}

	else if (name_of_attribute == "Code") {

		cout << "\t\tMisc: " << endl;
		cout << "\t\t\tMax Stack: " << attribute.info->codeAttribute.max_stack << endl;
		cout << "\t\t\tMax Locals: " << attribute.info->codeAttribute.max_locals << endl;
		cout << "\t\t\tCode Length: " << attribute.info->codeAttribute.code_length << endl;

		int var = 0;

		cout << "\t\tBytecode: " << endl;

		while ((unsigned int) var < attribute.info->codeAttribute.code_length) {
			cout << "\t\t\t" << var << "  " << obterMnemonico(attribute.info->codeAttribute.codigo[var]);
			obterParametrosOpcode(attribute.info->codeAttribute.codigo, &var);
			cout << endl;
		}

		cout << "\t\tException Table Length: " << attribute.info->codeAttribute.exception_table_length << endl;

		for (int var = 0; var < attribute.info->codeAttribute.exception_table_length; var++) {
			cout << "\t\tStart   PC: " << attribute.info->codeAttribute.exception_table[var]->start_pc << endl;
			cout << "\t\tEnd     PC: " << attribute.info->codeAttribute.exception_table[var]->end_pc << endl;
			cout << "\t\tHandler PC: " << attribute.info->codeAttribute.exception_table[var]->handler_pc << endl;
			cout << "\t\tCatch Type: " << attribute.info->codeAttribute.exception_table[var]->catch_type << endl;
		}

		cout << "\t\tNúmero de Atributos: " << attribute.info->codeAttribute.attribute_count << endl;

		for (int var = 0; var < attribute.info->codeAttribute.attribute_count; var++) {
			imprimirAttribute(attribute.info->codeAttribute.attributes[var], constantPool);
		}
	}

	else if (name_of_attribute == "Exceptions") {
		cout << "\t\tNúmero de Exceptions: " << attribute.info->exception.number_of_exceptions << endl;

		for (int var = 0; var < attribute.info->exception.number_of_exceptions; var++) {

			cout << "\t\tIndice Exception: " << attribute.info->exception.exception_index_table[var] << endl;
		}
	}
}

void gravarArquivoTodosAttributes(Attribute_info* attribute, Cp_info* constantPool, int tamanho, fstream &arquivoSaida) {
	int i;

	for (i = 0; i < tamanho; i++) {
		arquivoSaida << "\tAtributo " << i << ": " << endl;
		gravarArquivoAttribute(attribute[i], constantPool, arquivoSaida);
	}
}

void gravarArquivoAttribute(Attribute_info attribute, Cp_info *constantPool, fstream &arquivoSaida) {
	string name_of_attribute = capturarIndiceDeReferencia(constantPool, attribute.name_index);

	arquivoSaida << "\t\tNome: cp info #" << attribute.name_index << " " << name_of_attribute << endl;

	arquivoSaida << "\t\tNúmero de Atributos: " << attribute.length << endl;

	if (name_of_attribute == "ConstantValue") {
		arquivoSaida << "\t\tValor da Constante: " << attribute.info->constantValue.constantvalue_index << endl;
	}

	else if (name_of_attribute == "Code") {

		arquivoSaida << "\t\tMisc: " << endl;
		arquivoSaida << "\t\t\tMax Stack: " << attribute.info->codeAttribute.max_stack << endl;
		arquivoSaida << "\t\t\tMax Locals: " << attribute.info->codeAttribute.max_locals << endl;
		arquivoSaida << "\t\t\tCode Length: " << attribute.info->codeAttribute.code_length << endl;

		int var = 0;

		arquivoSaida << "\t\tBytecode: " << endl;

		while ((unsigned int) var < attribute.info->codeAttribute.code_length) {
			arquivoSaida << "\t\t\t" << var << "  " << obterMnemonico(attribute.info->codeAttribute.codigo[var]);
			gravaArquivoObterParametrosOpcode(attribute.info->codeAttribute.codigo, &var, arquivoSaida);
			arquivoSaida << endl;
		}

		arquivoSaida << "\t\tException Table Length: " << attribute.info->codeAttribute.exception_table_length << endl;

		for (int var = 0; var < attribute.info->codeAttribute.exception_table_length; var++) {
			arquivoSaida << "\t\tStart   PC: " << attribute.info->codeAttribute.exception_table[var]->start_pc << endl;
			arquivoSaida << "\t\tEnd     PC: " << attribute.info->codeAttribute.exception_table[var]->end_pc << endl;
			arquivoSaida << "\t\tHandler PC: " << attribute.info->codeAttribute.exception_table[var]->handler_pc << endl;
			arquivoSaida << "\t\tCatch Type: " << attribute.info->codeAttribute.exception_table[var]->catch_type << endl;
		}

		arquivoSaida << "\t\tNúmero de Atributos: " << attribute.info->codeAttribute.attribute_count << endl;

		for (int var = 0; var < attribute.info->codeAttribute.attribute_count; var++) {
			gravarArquivoAttribute(attribute.info->codeAttribute.attributes[var], constantPool, arquivoSaida);
		}
	}

	else if (name_of_attribute == "Exceptions") {
		arquivoSaida << "\t\tNúmero de Exceptions: " << attribute.info->exception.number_of_exceptions << endl;

		for (int var = 0; var < attribute.info->exception.number_of_exceptions; var++) {

			arquivoSaida << "\t\tIndice Exception: " << attribute.info->exception.exception_index_table[var] << endl;
		}
	}
}

string obterMnemonico(int opcode) {
	switch (opcode) {
	case (0x00):
		return "nop";

	case (0x01):
		return "aconst_null";

	case (0x02):
		return "iconst_m1";

	case (0x03):
		return "iconst_0";

	case (0x04):
		return "iconst_1";

	case (0x05):
		return "iconst_2";

	case (0x06):
		return "iconst_3";

	case (0x07):
		return "iconst_4";

	case (0x08):
		return "iconst_5";

	case (0x09):
		return "lconst_0";

	case (0x0a):
		return "lconst_1";

	case (0x0b):
		return "fconst_0";

	case (0x0c):
		return "fconst_1";

	case (0x0d):
		return "fconst_2";

	case (0x0e):
		return "dconst_0";

	case (0x0f):
		return "dconst_1";

	case (0x10):
		return "bipush";

	case (0x11):
		return "sipush";

	case (0x12):
		return "ldc";

	case (0x13):
		return "ldc_w";

	case (0x14):
		return "ldc2_w";

	case (0x15):
		return "iload";

	case (0x16):
		return "lload";

	case (0x17):
		return "fload";

	case (0x18):
		return "dload";

	case (0x19):
		return "aload";

	case (0x1a):
		return "iload_0";

	case (0x1b):
		return "iload_1";

	case (0x1c):
		return "iload_2";

	case (0x1d):
		return "iload_3";

	case (0x1e):
		return "lload_0";

	case (0x1f):
		return "lload_1";

	case (0x20):
		return "lload_2";

	case (0x21):
		return "lload_3";

	case (0x22):
		return "fload_0";

	case (0x23):
		return "fload_1";

	case (0x24):
		return "fload_2";

	case (0x25):
		return "fload_3";

	case (0x26):
		return "dload_0";

	case (0x27):
		return "dload_1";

	case (0x28):
		return "dload_2";

	case (0x29):
		return "dload_3";

	case (0x2a):
		return "aload_0";

	case (0x2b):
		return "aload_1";

	case (0x2c):
		return "aload_2";

	case (0x2d):
		return "aload_3";

	case (0x2e):
		return "iaload";

	case (0x2f):
		return "laload";

	case (0x30):
		return "faload";

	case (0x31):
		return "daload";

	case (0x32):
		return "aaload";

	case (0x33):
		return "baload";

	case (0x34):
		return "caload";

	case (0x35):
		return "saload";

	case (0x36):
		return "istore";

	case (0x37):
		return "lstore";

	case (0x38):
		return "fstore";

	case (0x39):
		return "dstore";

	case (0x3a):
		return "astore";

	case (0x3b):
		return "istore_0";

	case (0x3c):
		return "istore_1";

	case (0x3d):
		return "istore_2";

	case (0x3e):
		return "istore_3";

	case (0x3f):
		return "lstore_0";

	case (0x40):
		return "lstore_1";

	case (0x41):
		return "lstore_2";

	case (0x42):
		return "lstore_3";

	case (0x43):
		return "fstore_0";

	case (0x44):
		return "fstore_1";

	case (0x45):
		return "fstore_2";

	case (0x46):
		return "fstore_3";

	case (0x47):
		return "dstore_0";

	case (0x48):
		return "dstore_1";

	case (0x49):
		return "dstore_2";

	case (0x4a):
		return "dstore_3";

	case (0x4b):
		return "astore_0";

	case (0x4c):
		return "astore_1";

	case (0x4d):
		return "astore_2";

	case (0x4e):
		return "astore_3";

	case (0x4f):
		return "iastore";

	case (0x50):
		return "lastore";

	case (0x51):
		return "fastore";

	case (0x52):
		return "dastore";

	case (0x53):
		return "aastore";

	case (0x54):
		return "bastore";

	case (0x55):
		return "castore";

	case (0x56):
		return "sastore";

	case (0x57):
		return "pop";

	case (0x58):
		return "pop2";

	case (0x59):
		return "dup";

	case (0x5a):
		return "dup_x1";

	case (0x5b):
		return "dup_x2";

	case (0x5c):
		return "dup2";

	case (0x5d):
		return "dup2_x1";

	case (0x5e):
		return "dup2_x2";

	case (0x5f):
		return "swap";

	case (0x60):
		return "iadd";

	case (0x61):
		return "ladd";

	case (0x62):
		return "fadd";

	case (0x63):
		return "dadd";

	case (0x64):
		return "isub";

	case (0x65):
		return "lsub";

	case (0x66):
		return "fsub";

	case (0x67):
		return "dsub";

	case (0x68):
		return "imul";

	case (0x69):
		return "lmul";

	case (0x6a):
		return "fmul";

	case (0x6b):
		return "dmul";

	case (0x6c):
		return "idiv";

	case (0x6d):
		return "ldiv";

	case (0x6e):
		return "fdiv";

	case (0x6f):
		return "ddiv";

	case (0x70):
		return "irem";

	case (0x71):
		return "lrem";

	case (0x72):
		return "frem";

	case (0x73):
		return "drem";

	case (0x74):
		return "ineg";

	case (0x75):
		return "lneg";

	case (0x76):
		return "fneg";

	case (0x77):
		return "dneg";

	case (0x78):
		return "ishl";

	case (0x79):
		return "lshl";

	case (0x7a):
		return "ishr";

	case (0x7b):
		return "lshr";

	case (0x7c):
		return "iushr";

	case (0x7d):
		return "lushr";

	case (0x7e):
		return "iand";

	case (0x7f):
		return "land";

	case (0x80):
		return "ior";

	case (0x81):
		return "lor";

	case (0x82):
		return "ixor";

	case (0x83):
		return "lxor";

	case (0x84):
		return "iinc";

	case (0x85):
		return "i2l";

	case (0x86):
		return "i2f";

	case (0x87):
		return "i2d";

	case (0x88):
		return "l2i";

	case (0x89):
		return "l2f";

	case (0x8a):
		return "l2d";

	case (0x8b):
		return "f2i";

	case (0x8c):
		return "f2l";

	case (0x8d):
		return "f2d";

	case (0x8e):
		return "d2i";

	case (0x8f):
		return "d2l";

	case (0x90):
		return "d2f";

	case (0x91):
		return "i2b";

	case (0x92):
		return "i2c";

	case (0x93):
		return "i2s";

	case (0x94):
		return "lcmp";

	case (0x95):
		return "fcmpl";

	case (0x96):
		return "fcmpg";

	case (0x97):
		return "dcmpl";

	case (0x98):
		return "dcmpg";

	case (0x99):
		return "ifeq";

	case (0x9a):
		return "ifne";

	case (0x9b):
		return "iflt";

	case (0x9c):
		return "ifge";

	case (0x9d):
		return "ifgt";

	case (0x9e):
		return "ifle";

	case (0x9f):
		return "if_icmpeq";

	case (0xa0):
		return "if_icmpne";

	case (0xa1):
		return "if_icmplt";

	case (0xa2):
		return "if_icmpge";

	case (0xa3):
		return "if_icmpgt";

	case (0xa4):
		return "if_icmple";

	case (0xa5):
		return "if_acmpeq";

	case (0xa6):
		return "if_acmpne";

	case (0xa7):
		return "goto";

	case (0xa8):
		return "jsr";

	case (0xa9):
		return "ret";

	case (0xaa):
		return "tableswitch";

	case (0xab):
		return "lookupswitch";

	case (0xac):
		return "ireturn";

	case (0xad):
		return "lreturn";

	case (0xae):
		return "freturn";

	case (0xaf):
		return "dreturn";

	case (0xb0):
		return "areturn";

	case (0xb1):
		return "return";

	case (0xb2):
		return "getstatic";

	case (0xb3):
		return "putstatic";

	case (0xb4):
		return "getfield";

	case (0xb5):
		return "putfield";

	case (0xb6):
		return "invokevirtual";

	case (0xb7):
		return "invokespecial";

	case (0xb8):
		return "invokestatic";

	case (0xb9):
		return "invokeinterface";

	case (0xba):
		return "invokedynamic";

	case (0xbb):
		return "new";

	case (0xbc):
		return "newarray";

	case (0xbd):
		return "anewarray";

	case (0xbe):
		return "arraylength";

	case (0xbf):
		return "athrow";

	case (0xc0):
		return "checkcast";

	case (0xc1):
		return "instanceof";

	case (0xc2):
		return "monitorenter";

	case (0xc3):
		return "monitorexit";

	case (0xc4):
		return "wide";

	case (0xc5):
		return "multianewarray";

	case (0xc6):
		return "ifnull";

	case (0xc7):
		return "ifnonnull";

	case (0xc8):
		return "goto_w";

	case (0xc9):
		return "jsr_w";

	case (0xca):
		return "breakpoint";

	case (0xfe):
		return "impdep1";

	case (0xff):
		return "impdep2";

	default:
		return NULL;
	}
}

uint32_t obterValorNBytes(uint8_t numero, unsigned char* codigo, int* indice) {

	uint32_t valorNBytes = codigo[(*indice)++];

	for (int i = 1; i < numero; i++) {
		valorNBytes = (valorNBytes << 8) | codigo[(*indice)++];
	}

	return valorNBytes;
}

void obterParametrosOpcode(unsigned char* codigo, int* indice) {
	switch (codigo[(*indice)++]) {
	case (0x10): //"bipush";
	case (0x15): //"iload";
	case (0x16): //"lload";
	case (0x17): //"fload";
	case (0x18): //"dload";
	case (0x19): //"aload";
	case (0x36): //"istore";
	case (0x37): //"lstore";
	case (0x38): //"fstore";
	case (0x39): //"dstore";
	case (0x3a): //"astore";
	case (0xbc): //"newarray";
	case (0xa9): //"ret";

		cout << " " << obterValorNBytes(1, codigo, indice);

		break;
	case (0x11): //"sipush";
	case (0x99): //"ifeq";
	case (0x9a): //"ifne";
	case (0x9b): //"iflt";
	case (0x9c): //"ifge";
	case (0x9d): //"ifgt";
	case (0x9e): //"ifle";
	case (0x9f): //"if_icmpeq";
	case (0xa0): //"if_icmpne";
	case (0xa1): //"if_icmplt";
	case (0xa2): //"if_icmpge";
	case (0xa3): //"if_icmpgt";
	case (0xa4): //"if_icmple";
	case (0xa5): //"if_acmpeq";
	case (0xa6): //"if_acmpne";
	case (0xa7): //"goto";
	case (0xa8): //"jsr";
	case (0xbd): //"anewarray";
	case (0xc0): //"checkcast";
	case (0xc6): //"ifnull";
	case (0xc7): //"ifnonnull";
		cout << " " << obterValorNBytes(2, codigo, indice);
		break;
	case (0x12): //"ldc";
		cout << " #" << obterValorNBytes(1, codigo, indice);
		break;
	case (0x13): //"ldc_w";
	case (0x14): //"ldc2_w";
	case (0xb2): //"getstatic";
	case (0xb3): //"putstatic";
	case (0xb4): //"getfield";
	case (0xb5): //"putfield";
	case (0xbb): //"new";
	case (0xb6): //"invokevirtual";
	case (0xb7): //"invokespecial";
	case (0xb8): //"invokestatic";
	case (0xc1): //"instanceof";
		cout << " #" << obterValorNBytes(2, codigo, indice);
		break;
	case (0x84): //"iinc";
		cout << "#" << obterValorNBytes(1, codigo, indice);
		cout << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc5): //"multianewarray";
		cout << " " << obterValorNBytes(2, codigo, indice);
		cout << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc8): //"goto_w";
	case (0xc9): //"jsr_w";
		cout << " " << obterValorNBytes(4, codigo, indice);
		break;
	case (0xb9): //"invokeinterface";
	case (0xba): //"invokedynamic";
		cout << " #" << obterValorNBytes(2, codigo, indice);
		cout << " " << obterValorNBytes(1, codigo, indice);
		cout << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc4): //"wide";
		switch (codigo[(*indice)++]) {
		case (0x15): //"iload";
		case (0x16): //"lload";
		case (0x17): //"fload";
		case (0x18): //"dload";
		case (0x19): //"aload";
		case (0x36): //"istore";
		case (0x37): //"lstore";
		case (0x38): //"fstore";
		case (0x39): //"dstore";
		case (0x3a): //"astore";
		case (0xa9): //"ret";
			cout << " " << obterValorNBytes(2, codigo, indice);
			break;

		case (0x84): //"iinc";
			cout << " " << obterValorNBytes(2, codigo, indice);
			cout << " " << obterValorNBytes(2, codigo, indice);
			break;
		}
		break;
	case (0xaa): //"tableswitch";
	{
		if ((*indice) % 4 != 0) {
			(*indice) = *indice + (4 - (*indice % 4));
		}
		uint32_t defaultvalue = obterValorNBytes(4, codigo, indice);
		cout << " " << defaultvalue;

		uint32_t low = obterValorNBytes(4, codigo, indice);
		cout << " " << low;

		uint32_t high = obterValorNBytes(4, codigo, indice);
		cout << " " << high;

		for (int i = 0; (unsigned int) i < high - low + 1; i++) {
			cout << " " << obterValorNBytes(4, codigo, indice);
		}
	}
		break;

	case (0xab): //"lookupswitch";
	{
		if ((*indice) % 4 != 0) {
			(*indice) = *indice + (4 - (*indice % 4));
		}

		cout << " " << obterValorNBytes(4, codigo, indice);

		uint32_t npairs = obterValorNBytes(4, codigo, indice);
		cout << " " << npairs;

		for (int i = 0; (unsigned int) i < npairs; i++) {
			cout << " " << obterValorNBytes(4, codigo, indice);

			cout << " " << obterValorNBytes(4, codigo, indice);
		}
	}
		break;

	default:
		break;
	}
}

void gravaArquivoObterParametrosOpcode(unsigned char* codigo, int* indice, fstream & arquivoSaida) {
	switch (codigo[(*indice)++]) {
	case (0x10): //"bipush";
	case (0x15): //"iload";
	case (0x16): //"lload";
	case (0x17): //"fload";
	case (0x18): //"dload";
	case (0x19): //"aload";
	case (0x36): //"istore";
	case (0x37): //"lstore";
	case (0x38): //"fstore";
	case (0x39): //"dstore";
	case (0x3a): //"astore";
	case (0xbc): //"newarray";
	case (0xa9): //"ret";

		arquivoSaida << " " << obterValorNBytes(1, codigo, indice);

		break;
	case (0x11): //"sipush";
	case (0x99): //"ifeq";
	case (0x9a): //"ifne";
	case (0x9b): //"iflt";
	case (0x9c): //"ifge";
	case (0x9d): //"ifgt";
	case (0x9e): //"ifle";
	case (0x9f): //"if_icmpeq";
	case (0xa0): //"if_icmpne";
	case (0xa1): //"if_icmplt";
	case (0xa2): //"if_icmpge";
	case (0xa3): //"if_icmpgt";
	case (0xa4): //"if_icmple";
	case (0xa5): //"if_acmpeq";
	case (0xa6): //"if_acmpne";
	case (0xa7): //"goto";
	case (0xa8): //"jsr";
	case (0xbd): //"anewarray";
	case (0xc0): //"checkcast";
	case (0xc6): //"ifnull";
	case (0xc7): //"ifnonnull";
		arquivoSaida << " " << obterValorNBytes(2, codigo, indice);
		break;
	case (0x12): //"ldc";
		arquivoSaida << " #" << obterValorNBytes(1, codigo, indice);
		break;
	case (0x13): //"ldc_w";
	case (0x14): //"ldc2_w";
	case (0xb2): //"getstatic";
	case (0xb3): //"putstatic";
	case (0xb4): //"getfield";
	case (0xb5): //"putfield";
	case (0xbb): //"new";
	case (0xb6): //"invokevirtual";
	case (0xb7): //"invokespecial";
	case (0xb8): //"invokestatic";
	case (0xc1): //"instanceof";
		arquivoSaida << " #" << obterValorNBytes(2, codigo, indice);
		break;
	case (0x84): //"iinc";
		arquivoSaida << "#" << obterValorNBytes(1, codigo, indice);
		arquivoSaida << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc5): //"multianewarray";
		arquivoSaida << " " << obterValorNBytes(2, codigo, indice);
		arquivoSaida << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc8): //"goto_w";
	case (0xc9): //"jsr_w";
		arquivoSaida << " " << obterValorNBytes(4, codigo, indice);
		break;
	case (0xb9): //"invokeinterface";
	case (0xba): //"invokedynamic";
		arquivoSaida << " #" << obterValorNBytes(2, codigo, indice);
		arquivoSaida << " " << obterValorNBytes(1, codigo, indice);
		arquivoSaida << " " << obterValorNBytes(1, codigo, indice);
		break;
	case (0xc4): //"wide";
		switch (codigo[(*indice)++]) {
		case (0x15): //"iload";
		case (0x16): //"lload";
		case (0x17): //"fload";
		case (0x18): //"dload";
		case (0x19): //"aload";
		case (0x36): //"istore";
		case (0x37): //"lstore";
		case (0x38): //"fstore";
		case (0x39): //"dstore";
		case (0x3a): //"astore";
		case (0xa9): //"ret";
			arquivoSaida << " " << obterValorNBytes(2, codigo, indice);
			break;

		case (0x84): //"iinc";
			arquivoSaida << " " << obterValorNBytes(2, codigo, indice);
			arquivoSaida << " " << obterValorNBytes(2, codigo, indice);
			break;
		}
		break;
	case (0xaa): //"tableswitch";
	{
		if ((*indice) % 4 != 0) {
			(*indice) = *indice + (4 - (*indice % 4));
		}
		uint32_t defaultvalue = obterValorNBytes(4, codigo, indice);
		arquivoSaida << " " << defaultvalue;

		uint32_t low = obterValorNBytes(4, codigo, indice);
		arquivoSaida << " " << low;

		uint32_t high = obterValorNBytes(4, codigo, indice);
		arquivoSaida << " " << high;

		for (int i = 0; (unsigned int) i < high - low + 1; i++) {
			arquivoSaida << " " << obterValorNBytes(4, codigo, indice);
		}
	}
		break;

	case (0xab): //"lookupswitch";
	{
		if ((*indice) % 4 != 0) {
			(*indice) = *indice + (4 - (*indice % 4));
		}

		arquivoSaida << " " << obterValorNBytes(4, codigo, indice);

		uint32_t npairs = obterValorNBytes(4, codigo, indice);
		arquivoSaida << " " << npairs;

		for (int i = 0; (unsigned int) i < npairs; i++) {
			arquivoSaida << " " << obterValorNBytes(4, codigo, indice);

			arquivoSaida << " " << obterValorNBytes(4, codigo, indice);
		}
	}
		break;

	default:
		break;
	}
}

