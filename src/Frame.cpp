#include "Frame.h"

#include "ClassVisao.h"
#include "MethodArea.h"
#include "Utils.h"

Frame::Frame(InstanceClass *object, StaticClass *classRuntime, string methodName, string methodDescriptor, vector<Value> arguments) :
		pc(0), _object(object) {

	for (int i = 0; i < (signed) arguments.size(); i++) {
		_localVariables[i] = arguments[i];
	}

	method_info *method = obterMethodNamed(classRuntime, methodName, methodDescriptor);
	assert(method != NULL);
	_method = *method;
	assert((_method.access_flags & 0x0008) == 0); // o método não pode ser estático

	encontrarAttributes();
}

Frame::Frame(StaticClass *classRuntime, string methodName, string methodDescriptor, vector<Value> arguments) :
		pc(0), _object(NULL) {

	for (int i = 0; i < (signed) arguments.size(); i++) {
		_localVariables[i] = arguments[i];
	}

	method_info *method = obterMethodNamed(classRuntime, methodName, methodDescriptor);
	assert(method != NULL);
	_method = *method;
	assert((_method.access_flags & 0x0008) != 0); // o método precisa ser estático

	encontrarAttributes();
}

Frame::~Frame() {

}

cp_info** Frame::obterConstantPool() {
	return &(_classRuntime->getClassFile()->constant_pool);
}

Value Frame::obterLocalVariableValue(uint32_t index) {
	if (index >= _codeAttribute->max_locals) {
		cerr << "Tentando acessar variavel local inexistente" << endl;
		exit(1);
	}

	return _localVariables[index];
}

void Frame::trocaLocalVariable(Value variableValue, uint32_t index) {
	if (index >= _codeAttribute->max_locals) {
		cerr << "Tentando alterar variavel local inexistente" << endl;
		exit(1);
	}

//    if (_localVariables.count(index) > 0 && variableValue.type != _localVariables[index].type) {
//        cerr << "Tentando alterar variavel local com outro tipo" << endl;
//        exit(1);
//    }

	_localVariables[index] = variableValue;
}

void Frame::empilharOperandStack(Value operand) {
	_operandStack.push(operand);
}

Value Frame::desempilhaOperandStack() {
	if (_operandStack.size() == 0) {
		cerr << "IndexOutOfBoundsException" << endl;
		exit(1);
	}

	Value top = _operandStack.top();

	_operandStack.pop();
	return top;
}

stack<Value> Frame::backupOperandStack() {
	return _operandStack;
}

void Frame::setOperandStackFromBackup(stack<Value> backup) {
	_operandStack = backup;
}

u1* Frame::getCode(uint32_t address) {
	return _codeAttribute->code + address;
}

method_info* Frame::obterMethodNamed(StaticClass *classRuntime, string name, string descriptor) {
	MethodArea &methodArea = MethodArea::getInstance();

	StaticClass *currClass = classRuntime;
	method_info *method;

	while (currClass != NULL) {
		ClassFile *classFile = currClass->getClassFile();

		for (int i = 0; i < classFile->methods_count; i++) {
			method = &(classFile->methods[i]);
			string methodName = getFormattedConstant(classFile->constant_pool, method->name_index);
			string methodDesc = getFormattedConstant(classFile->constant_pool, method->descriptor_index);

			if (methodName == name && methodDesc == descriptor) {
				_classRuntime = currClass;
				return method;
			}
		}

		// procurando o método nas super classes.
		if (classFile->super_class == 0) {
			currClass = NULL;
		} else {
			string superClassName = getFormattedConstant(classFile->constant_pool, classFile->super_class);
			currClass = methodArea.carregarClassNamed(superClassName);
		}
	}

	return NULL;
}

void Frame::encontrarAttributes() {
	cp_info *constantPool = *obterConstantPool();

	_codeAttribute = NULL;
	_exceptionsAttribute = NULL;

	for (int i = 0; i < _method.attributes_count; i++) {
		attribute_info *attr = &(_method.attributes[i]);
		CONSTANT_Utf8_info attrName = constantPool[attr->attribute_name_index - 1].info.utf8_info;

		if (Utils::compararUtf8String(attrName, "Code")) {
			_codeAttribute = &(attr->info.code_info);
			if (_exceptionsAttribute != NULL)
				break;
		} else if (Utils::compararUtf8String(attrName, "Exceptions")) {
			_exceptionsAttribute = &(attr->info.exceptions_info);
			if (_codeAttribute != NULL)
				break;
		}
	}
}

u2 Frame::sizeLocalVariables() {
	return _codeAttribute->max_locals;
}

u4 Frame::sizeCode() {
	return _codeAttribute->code_length;
}
