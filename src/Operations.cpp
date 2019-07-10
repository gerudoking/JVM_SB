#include "Operations.h"

#include "Frame.h"
#include "ArrayObject.h"
#include "ClassVisao.h"
#include "MethodArea.h"
#include "Stringobject.h"
#include "PilhaJVM.h"
#include "StaticClass.h"

Operations::Operations() : _isWide(false) {
    initInstructions();
}

Operations::~Operations() {

}

void Operations::executarMetodos(StaticClass *classRuntime) {
    PilhaJVM &pilhaJVM = PilhaJVM::getInstance();

    vector<Value> arguments;
    Value commandLineArgs;
    commandLineArgs.type = ValueType::REFERENCE;
    commandLineArgs.data.object = new ArrayObject(ValueType::REFERENCE);
    arguments.push_back(commandLineArgs);

    pilhaJVM.addFrame(new Frame(classRuntime, "main", "([Ljava/lang/String;)V", arguments));

    if (verificarMetodoExiste(classRuntime, "<clinit>", "()V")) {
        pilhaJVM.addFrame(new Frame(classRuntime, "<clinit>", "()V", arguments));
    }

    while (pilhaJVM.size() > 0) {
        Frame *topFrame = pilhaJVM.getTopFrame();
        u1 *code = topFrame->getCode(topFrame->pc);
        (*this.*funcaoGenerica[code[0]])();
    }
}

bool Operations::verificarMetodoExiste(StaticClass *classRuntime, string name, string descriptor) {
    ClassFile *classFile = classRuntime->getClassFile();

    bool found = false;
    method_info method;
    for (int i = 0; i < classFile->methods_count; i++) {
        method = classFile->methods[i];
        string methodName = getFormattedConstant(classFile->constant_pool, method.name_index);
        string methodDesc = getFormattedConstant(classFile->constant_pool, method.descriptor_index);

        if (methodName == name && methodDesc == descriptor) {
            found = true;
            break;
        }
    }

    return found;
}

void Operations::populateMultiarray(ArrayObject *array, ValueType valueType, stack<int> count) {
    int currCount = count.top();
    count.pop();
    
    ValueType arrayType = (count.size() > 1) ? ValueType::REFERENCE : valueType;
    
    if (count.size() == 0) {
        for (int i = 0; i < currCount; i++) {
            Value subarrayValue;
            subarrayValue.type = valueType;
            subarrayValue.printType = valueType;
            subarrayValue.data.longValue = 0;
            array->pushValue(subarrayValue);
        }
    } else {
        for (int i = 0; i < currCount; i++) {
            ArrayObject *subarray = new ArrayObject(arrayType);
            populateMultiarray(subarray, valueType, count);
            
            Value subarrayValue;
            subarrayValue.type = ValueType::REFERENCE;
            subarrayValue.data.object = subarray;
            array->pushValue(subarrayValue);
        }
    }
}

void Operations::nop() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    topFrame->pc += 1;
}

void Operations::aconst_null() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.type = ValueType::REFERENCE;
    value.data.object = NULL;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_m1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = -1;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 0;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 1;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 2;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 3;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_4() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 4;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iconst_5() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.printType = ValueType::INT;
    value.type = ValueType::INT;
    value.data.intValue = 5;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lconst_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value padding;
    padding.type = ValueType::PADDING;

    Value value;
    value.type = ValueType::LONG;
    value.data.longValue = 0;

    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lconst_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value padding;
    padding.type = ValueType::PADDING;

    Value value;
    value.type = ValueType::LONG;
    value.data.longValue = 1;

    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fconst_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.type = ValueType::FLOAT;
    value.data.floatValue = 0;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fconst_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.type = ValueType::FLOAT;
    value.data.floatValue = 1;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fconst_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;
    value.type = ValueType::FLOAT;
    value.data.floatValue = 2;

    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dconst_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value padding;
    padding.type = ValueType::PADDING;

    Value value;
    value.type = ValueType::DOUBLE;
    value.data.doubleValue = 0;

    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dconst_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value padding;
    padding.type = ValueType::PADDING;

    Value value;
    value.type = ValueType::DOUBLE;
    value.data.doubleValue = 1;

    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::bipush() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte = code[1];

    Value value;
    value.printType = ValueType::BYTE;
    value.type = ValueType::INT;
    value.data.intValue = (int32_t) (int8_t) byte; // convertendo para inteiro e estendendo o sinal

    topFrame->empilharOperandStack(value);

    topFrame->pc += 2;
}

void Operations::sipush() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t shortValue = (byte1 << 8) | byte2;
    Value value;
    value.printType = ValueType::SHORT;
    value.type = ValueType::INT;
    value.data.intValue = (int32_t) (int16_t) shortValue; // convertendo para inteiro e estendendo o sinal

    topFrame->empilharOperandStack(value);

    topFrame->pc += 3;
}

void Operations::ldc() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 index = code[1];
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    cp_info entry = constantPool[index-1];

    Value value;
    
    if (entry.tag == CONSTANT_String) {
        cp_info utf8Entry = constantPool[entry.info.string_info.string_index-1];
        assert(utf8Entry.tag == CONSTANT_Utf8);
        
        u1* bytes = utf8Entry.info.utf8_info.bytes;
        char utf8String[utf8Entry.info.utf8_info.length+1];
        int i;
        for (i = 0; i < utf8Entry.info.utf8_info.length; i++) {
            utf8String[i] = bytes[i];
        }
        utf8String[i] = '\0';
        
        value.type = ValueType::REFERENCE;
        value.data.object = new StringObject(utf8String);
    } else if (entry.tag == CONSTANT_Integer) {
        value.printType = ValueType::INT;
        value.type = ValueType::INT;
        value.data.intValue = (int32_t) entry.info.integer_info.bytes;
    } else if (entry.tag == CONSTANT_Float) {
        u4 floatBytes = entry.info.float_info.bytes;
        int s = ((floatBytes >> 31) == 0) ? 1 : -1;
        int e = ((floatBytes >> 23) & 0xff);
        int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;
        
        float number = s*m*pow(2, e-150);
        value.type = ValueType::FLOAT;
        value.data.floatValue = number;
    } else {
        cerr << "ldc tentando acessar um elemento da CP invalido: " << entry.tag << endl;
        exit(1);
    }
    
    topFrame->empilharOperandStack(value);
    topFrame->pc += 2;
}

void Operations::ldc_w() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 index = (byte1 << 8) | byte2;
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    cp_info entry = constantPool[index-1];
    
    Value value;
    
    if (entry.tag == CONSTANT_String) {
        cp_info utf8Entry = constantPool[entry.info.string_info.string_index-1];
        assert(utf8Entry.tag == CONSTANT_Utf8);
        
        u1* bytes = utf8Entry.info.utf8_info.bytes;
        char utf8String[utf8Entry.info.utf8_info.length+1];
        int i;
        for (i = 0; i < utf8Entry.info.utf8_info.length; i++) {
            utf8String[i] = bytes[i];
        }
        utf8String[i] = '\0';
        
        value.type = ValueType::REFERENCE;
        value.data.object = new StringObject(utf8String);
    } else if (entry.tag == CONSTANT_Integer) {
        value.printType = ValueType::INT;
        value.type = ValueType::INT;
        value.data.intValue = entry.info.integer_info.bytes;
    } else if (entry.tag == CONSTANT_Float) {
        u4 floatBytes = entry.info.float_info.bytes;
        int s = ((floatBytes >> 31) == 0) ? 1 : -1;
        int e = ((floatBytes >> 23) & 0xff);
        int m = (e == 0) ? (floatBytes & 0x7fffff) << 1 : (floatBytes & 0x7fffff) | 0x800000;
        
        float number = s*m*pow(2, e-150);
        value.type = ValueType::FLOAT;
        value.data.floatValue = number;
    } else {
        cerr << "ldc_w tentando acessar um elemento da CP invalido: " << entry.tag << endl;
        exit(1);
    }
    
    topFrame->empilharOperandStack(value);
    topFrame->pc += 3;
}

void Operations::ldc2_w() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u2 index = (byte1 << 8) | byte2;
    
    cp_info *classFile = *(topFrame->obterConstantPool());
    cp_info entry = classFile[index-1];
    
    Value value;
    
    if (entry.tag == CONSTANT_Long) {
        u4 highBytes = entry.info.long_info.high_bytes;
        u4 lowBytes = entry.info.long_info.low_bytes;
        
        int64_t longNumber = ((int64_t) highBytes << 32) + lowBytes;
        value.type = ValueType::LONG;
        value.data.longValue = longNumber;
        
        Value padding;
        padding.type = ValueType::PADDING;
        
        topFrame->empilharOperandStack(padding);
    } else if (entry.tag == CONSTANT_Double) {
        u4 highBytes = entry.info.double_info.high_bytes;
        u4 lowBytes = entry.info.double_info.low_bytes;
        
        int64_t longNumber = ((int64_t) highBytes << 32) + lowBytes;
        
        int32_t s = ((longNumber >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((longNumber >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (longNumber & 0xfffffffffffffL) << 1 : (longNumber & 0xfffffffffffffL) | 0x10000000000000L;
        
        double doubleNumber = s*m*pow(2, e-1075);
        value.type = ValueType::DOUBLE;
        value.data.doubleValue = doubleNumber;
        
        Value padding;
        padding.type = ValueType::PADDING;
        
        topFrame->empilharOperandStack(padding);
    } else {
        cerr << "ldc2_w tentando acessar um elemento da CP invalido: " << entry.tag << endl;
        exit(1);
    }
    
    topFrame->empilharOperandStack(value);
    topFrame->pc += 3;
}

// Pode ser modificado pelo wide
void Operations::iload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	}
	else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::INT);

	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void Operations::lload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	}
	else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));

	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::LONG);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void Operations::fload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	}
	else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::FLOAT);
	topFrame->empilharOperandStack(value);

}

// Pode ser modificado pelo wide
void Operations::dload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	}
	else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));

	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::DOUBLE);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);
	topFrame->empilharOperandStack(value);
}

// Pode ser modificado pelo wide
void Operations::aload() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	}
	else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);
	assert(value.type == ValueType::REFERENCE);
	topFrame->empilharOperandStack(value);
}

void Operations::iload_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(0);
    assert(value.type == ValueType::INT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iload_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::INT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iload_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::INT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iload_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::INT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lload_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(0);
    assert(value.type == ValueType::LONG);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lload_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::LONG);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lload_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::LONG);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::lload_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(4);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::LONG);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fload_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(0);
    assert(value.type == ValueType::FLOAT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fload_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::FLOAT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fload_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::FLOAT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::fload_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::FLOAT);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dload_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(0);
    assert(value.type == ValueType::DOUBLE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dload_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::DOUBLE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dload_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::DOUBLE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dload_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value;

    value = topFrame->obterLocalVariableValue(4);
    assert(value.type == ValueType::PADDING);
    topFrame->empilharOperandStack(value);

    value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::DOUBLE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::aload_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(0);
    assert(value.type == ValueType::REFERENCE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::aload_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(1);
    assert(value.type == ValueType::REFERENCE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::aload_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(2);
    assert(value.type == ValueType::REFERENCE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::aload_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->obterLocalVariableValue(3);
    assert(value.type == ValueType::REFERENCE);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::iaload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >(signed) array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->empilharOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Operations::laload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if ((signed)index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value padding;
    padding.type = ValueType::PADDING;
    
    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Operations::faload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->empilharOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Operations::daload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >(signed) array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value padding;
    padding.type = ValueType::PADDING;
    
    topFrame->empilharOperandStack(padding);
    topFrame->empilharOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Operations::aaload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    topFrame->empilharOperandStack(array->getValue(index.data.intValue));
    topFrame->pc += 1;
}

void Operations::baload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value value = array->getValue(index.data.intValue);
    assert(value.type == ValueType::BOOLEAN || value.type == ValueType::BYTE);
    
    if (value.type == ValueType::BOOLEAN) {
        value.data.intValue = (uint32_t) value.data.booleanValue;
        value.printType = ValueType::BOOLEAN;
    } else {
        value.data.intValue = (int32_t) value.data.byteValue;
        value.printType = ValueType::BYTE;
    }
    value.type = ValueType::INT;

    topFrame->empilharOperandStack(value);
    topFrame->pc += 1;
}

void Operations::caload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >(signed) array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    Value charValue = array->getValue(index.data.intValue);
    charValue.data.intValue = (uint32_t) charValue.data.charValue;
    charValue.printType = ValueType::CHAR;
    charValue.type = ValueType::INT;
    
    topFrame->empilharOperandStack(charValue);
    topFrame->pc += 1;
}

void Operations::saload() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }
    
    Value shortValue = array->getValue(index.data.intValue);
    shortValue.data.intValue = (int32_t) shortValue.data.shortValue;
    shortValue.printType = ValueType::SHORT;
    shortValue.type = ValueType::INT;
    
    topFrame->empilharOperandStack(shortValue);
    topFrame->pc += 1;
}

// Pode ser modificado pelo wide
void Operations::istore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

// Pode ser modificado pelo wide
void Operations::lstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::LONG);
	topFrame->desempilhaOperandStack(); //padding

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->trocaLocalVariable(value, index);
	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->trocaLocalVariable(padding, index + 1);
}

// Pode ser modificado pelo wide
void Operations::fstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::FLOAT);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

// Pode ser modificado pelo wide
void Operations::dstore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::DOUBLE);
	topFrame->desempilhaOperandStack(); //padding

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > (index + 1)));
	topFrame->trocaLocalVariable(value, index);
	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->trocaLocalVariable(padding, index + 1);
}

// Pode ser modificado pelo wide
void Operations::astore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::REFERENCE);

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; //índice do vetor de variáveis locais
	int16_t index = (int16_t)byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
		topFrame->pc += 3;
		_isWide = false;
	} else {
		topFrame->pc += 2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	topFrame->trocaLocalVariable(value, index);
}

void Operations::istore_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    topFrame->trocaLocalVariable(value, 0);

    topFrame->pc += 1;
}

void Operations::istore_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    topFrame->trocaLocalVariable(value, 1);

    topFrame->pc += 1;
}

void Operations::istore_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    topFrame->trocaLocalVariable(value, 2);

    topFrame->pc += 1;
}

void Operations::istore_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    topFrame->trocaLocalVariable(value, 3);

    topFrame->pc += 1;
}

void Operations::lstore_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::LONG);
    topFrame->trocaLocalVariable(value, 0);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 1);

    topFrame->pc += 1;
}

void Operations::lstore_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::LONG);
    topFrame->trocaLocalVariable(value, 1);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 2);

    topFrame->pc += 1;
}

void Operations::lstore_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::LONG);
    topFrame->trocaLocalVariable(value, 2);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 3);

    topFrame->pc += 1;
}

void Operations::lstore_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::LONG);
    topFrame->trocaLocalVariable(value, 3);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 4);

    topFrame->pc += 1;
}

void Operations::fstore_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::FLOAT);
    topFrame->trocaLocalVariable(value, 0);

    topFrame->pc += 1;
}

void Operations::fstore_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::FLOAT);
    topFrame->trocaLocalVariable(value, 1);

    topFrame->pc += 1;
}

void Operations::fstore_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::FLOAT);
    topFrame->trocaLocalVariable(value, 2);

    topFrame->pc += 1;
}

void Operations::fstore_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::FLOAT);
    topFrame->trocaLocalVariable(value, 3);

    topFrame->pc += 1;
}

void Operations::dstore_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::DOUBLE);
    topFrame->trocaLocalVariable(value, 0);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 1);

    topFrame->pc += 1;
}

void Operations::dstore_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::DOUBLE);
    topFrame->trocaLocalVariable(value, 1);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 2);

    topFrame->pc += 1;
}

void Operations::dstore_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::DOUBLE);
    topFrame->trocaLocalVariable(value, 2);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 3);

    topFrame->pc += 1;
}

void Operations::dstore_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::DOUBLE);
    topFrame->trocaLocalVariable(value, 3);

    value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::PADDING);
    topFrame->trocaLocalVariable(value, 4);

    topFrame->pc += 1;
}

void Operations::astore_0() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::REFERENCE);
    topFrame->trocaLocalVariable(value, 0);

    topFrame->pc += 1;
}

void Operations::astore_1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::REFERENCE);
    topFrame->trocaLocalVariable(value, 1);

    topFrame->pc += 1;
}

void Operations::astore_2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::REFERENCE);
    topFrame->trocaLocalVariable(value, 2);

    topFrame->pc += 1;
}

void Operations::astore_3() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::REFERENCE);
    topFrame->trocaLocalVariable(value, 3);

    topFrame->pc += 1;
}

void Operations::iastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >= (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    value.printType = ValueType::INT;
    
    assert(value.type == array->arrayContentType());
    array->changeValueAt(index.data.intValue, value);
    
    topFrame->pc += 1;
}

void Operations::lastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::LONG);
    Value padding = topFrame->desempilhaOperandStack();
    assert(padding.type == ValueType::PADDING);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >= (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    assert(value.type == array->arrayContentType());
    array->changeValueAt(index.data.intValue, value);

    topFrame->pc += 1;
}

void Operations::fastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::FLOAT);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >= (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    assert(value.type == array->arrayContentType());
    array->changeValueAt(index.data.intValue, value);
	
    topFrame->pc += 1;
}

void Operations::dastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::DOUBLE);
    Value padding = topFrame->desempilhaOperandStack();
    assert(padding.type == ValueType::PADDING);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >=(signed) array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    assert(value.type == array->arrayContentType());
    array->changeValueAt(index.data.intValue, value);
	
    topFrame->pc += 1;
}

void Operations::aastore() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

	Value value = topFrame->desempilhaOperandStack(); // Valor armazenado no index do array
	assert(value.type == ValueType::REFERENCE);
    Value index = topFrame->desempilhaOperandStack(); // Index do arary
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack(); // Referência ao array
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue >= (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

	array->changeValueAt(index.data.intValue, value);
    
    topFrame->pc += 1;
}

void Operations::bastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;
    assert(array->arrayContentType() == ValueType::BOOLEAN || array->arrayContentType() == ValueType::BYTE);

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    if (array->arrayContentType() == ValueType::BOOLEAN) {
        value.data.booleanValue = (value.data.intValue != 0) ? true : false;
        value.type = ValueType::BOOLEAN;
        value.printType = ValueType::BOOLEAN;
    } else {
        value.data.byteValue = (uint8_t) value.data.intValue;
        value.type = ValueType::BYTE;
        value.printType = ValueType::BYTE;
    }
    
    array->changeValueAt(index.data.intValue, value);
	
    topFrame->pc += 1;
}

void Operations::castore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    value.data.charValue = (uint8_t) value.data.intValue;
    value.printType = ValueType::CHAR;
    value.type = ValueType::CHAR;
    array->changeValueAt(index.data.intValue, value);
	
    topFrame->pc += 1;
}

void Operations::sastore() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
	ArrayObject *array;

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    Value index = topFrame->desempilhaOperandStack();
    assert(index.type == ValueType::INT);
    Value arrayref = topFrame->desempilhaOperandStack();
    assert(arrayref.type == ValueType::REFERENCE);
    assert((arrayref.data.object)->objectType() == ObjectType::ARRAY);

    array = (ArrayObject *) arrayref.data.object;

    if (array == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    if (index.data.intValue > (signed)array->getSize() || index.data.intValue < 0) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(2);
    }

    value.data.shortValue = (int16_t) value.data.intValue;
    value.printType = ValueType::SHORT;
    value.type = ValueType::SHORT;
    array->changeValueAt(index.data.intValue, value);
	
    topFrame->pc += 1;
}

void Operations::pop() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    Value value = topFrame->desempilhaOperandStack();
    assert(value.type != ValueType::LONG);
    assert(value.type != ValueType::DOUBLE);

    topFrame->pc += 1;
}

void Operations::pop2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    topFrame->desempilhaOperandStack();
    topFrame->desempilhaOperandStack();

    topFrame->pc += 1;
}

void Operations::dup() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value = topFrame->desempilhaOperandStack();
    assert(value.type != ValueType::LONG);
    assert(value.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value);
    topFrame->empilharOperandStack(value);

    topFrame->pc += 1;
}

void Operations::dup_x1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    Value value_2 = topFrame->desempilhaOperandStack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::dup_x2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_3 = topFrame->desempilhaOperandStack();

    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    assert(value_3.type != ValueType::LONG);
    assert(value_3.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_3);
    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::dup2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    Value value_2 = topFrame->desempilhaOperandStack();
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::dup2_x1() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_3 = topFrame->desempilhaOperandStack();

    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    assert(value_3.type != ValueType::LONG);
    assert(value_3.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_3);
    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::dup2_x2() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_3 = topFrame->desempilhaOperandStack();
    Value value_4 = topFrame->desempilhaOperandStack();

    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);
    assert(value_4.type != ValueType::LONG);
    assert(value_4.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_4);
    topFrame->empilharOperandStack(value_3);
    topFrame->empilharOperandStack(value_2);
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::swap() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    Value value_2 = topFrame->desempilhaOperandStack();

    assert(value_1.type != ValueType::LONG);
    assert(value_1.type != ValueType::DOUBLE);
    assert(value_2.type != ValueType::LONG);
    assert(value_2.type != ValueType::DOUBLE);

    topFrame->empilharOperandStack(value_1);
    topFrame->empilharOperandStack(value_2);

    topFrame->pc += 1;
}

void Operations::iadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

	value_1.data.intValue = value_1.data.intValue + (value_2.data.intValue);
    value_1.printType = ValueType::INT;
    
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::ladd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); //padding
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = value_1.data.longValue + (value_2.data.longValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::fadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);

	value_1.data.floatValue = value_1.data.floatValue + (value_2.data.floatValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::dadd() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);

	value_1.data.doubleValue = value_1.data.doubleValue + (value_2.data.doubleValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::isub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue - (value_2.data.intValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = value_1.data.longValue - (value_2.data.longValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::fsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);

	value_1.data.floatValue = value_1.data.floatValue - (value_2.data.floatValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::dsub() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);

	value_1.data.doubleValue = value_1.data.doubleValue - (value_2.data.doubleValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::imul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue * (value_2.data.intValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = value_1.data.longValue * (value_2.data.longValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::fmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);

	value_1.data.floatValue = value_1.data.floatValue * (value_2.data.floatValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::dmul() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);

	value_1.data.doubleValue = value_1.data.doubleValue * (value_2.data.doubleValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::idiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);
	if (value_2.data.intValue == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue / (value_2.data.intValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::ldiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);
	if (value_2.data.longValue == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}

	value_1.data.longValue = value_1.data.longValue / (value_2.data.longValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::fdiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);
	if (value_2.data.floatValue == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}
	value_1.data.floatValue = value_1.data.floatValue / (value_2.data.floatValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::ddiv() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);
	if (value_2.data.doubleValue == 0) {
		cerr << "ArithmeticException" << endl;
		exit(2);
	}
	value_1.data.doubleValue = value_1.data.doubleValue / (value_2.data.doubleValue);
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::irem() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();

    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);
	if (value_2.data.intValue == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	
    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue - (value_1.data.intValue / value_2.data.intValue)*value_2.data.intValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::lrem() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    assert(value_2.type == ValueType::LONG);
    assert(value_1.type == ValueType::LONG);
	if (value_2.data.longValue == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.longValue = value_1.data.longValue - (value_1.data.longValue / value_2.data.longValue)*value_2.data.longValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::frem() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();

    assert(value_2.type == ValueType::FLOAT);
    assert(value_1.type == ValueType::FLOAT);
	if (value_2.data.floatValue == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.floatValue = value_1.data.floatValue - ((uint32_t)(value_1.data.floatValue / value_2.data.floatValue))*value_2.data.floatValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::drem() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    topFrame->desempilhaOperandStack(); // PADDING
    Value value_1 = topFrame->desempilhaOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    assert(value_2.type == ValueType::DOUBLE);
    assert(value_1.type == ValueType::DOUBLE);
	if (value_2.data.doubleValue == 0) {
		cerr << "ArithmeticException" << endl;
        exit(2);
	}
	// value_1 negativo implica em resultado negativo
	value_1.data.doubleValue = value_1.data.doubleValue - ((uint64_t)(value_1.data.doubleValue / value_2.data.doubleValue))*value_2.data.doubleValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::ineg() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = -value_1.data.intValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::lneg() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = -value_1.data.longValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::fneg() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_1.type == ValueType::FLOAT);

	value_1.data.floatValue = -value_1.data.floatValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::dneg() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

	// Não precisa tirar o padding
    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_1.type == ValueType::DOUBLE);

	value_1.data.doubleValue = -value_1.data.doubleValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::ishl() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);

	// value_2 armazena seus 5 primeiros bits
	value_2.data.intValue = 0x1f & value_2.data.intValue;
	value_1.data.intValue = value_1.data.intValue << value_2.data.intValue;
    value_1.printType = ValueType::INT;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::lshl() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::LONG);

    value_2.data.longValue = 0x3f & value_2.data.longValue;
    value_1.data.longValue = (value_1.data.longValue) << value_2.data.intValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::ishr() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();
    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::INT);

	// value_2 armazena seus 5 primeiros bits
	value_2.data.intValue = 0x1f & value_2.data.intValue;
	value_1.data.intValue = value_1.data.intValue >> value_2.data.intValue;
    value_1.printType = ValueType::INT;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::lshr() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();

    Value value_2 = topFrame->desempilhaOperandStack();
    Value value_1 = topFrame->desempilhaOperandStack();
    // Sobra um padding na pilha que ficará abaixo do resultado

    assert(value_2.type == ValueType::INT);
    assert(value_1.type == ValueType::LONG);

	// value_2 armazena seus 6 primeiros bits
	value_2.data.longValue = 0x3f & value_2.data.longValue;
	value_1.data.longValue = value_1.data.longValue >> value_2.data.longValue;
    topFrame->empilharOperandStack(value_1);

    topFrame->pc += 1;
}

void Operations::iushr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

	value_2.data.intValue = 0x1f & value_2.data.intValue;
	value_1.data.intValue = value_1.data.intValue >> value_2.data.intValue;
	if (value_1.data.intValue < 0) {
		value_1.data.intValue = value_1.data.intValue + (2<<~(value_2.data.intValue));
	}
    value_1.printType = ValueType::INT;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lushr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::LONG);

	value_2.data.intValue = 0x3f & value_2.data.intValue;
	value_1.data.longValue = value_1.data.longValue >> value_2.data.intValue;
	if (value_1.data.longValue < 0) {
		value_1.data.longValue = value_1.data.longValue + ((int64_t)2 << ~(value_2.data.intValue));
	}
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::iand() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue & value_2.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::land() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); // PADDING
	Value value_1 = topFrame->desempilhaOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	// value_2 armazena seus 6 primeiros bits
	value_1.data.longValue = value_1.data.longValue & value_2.data.longValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::ior() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue | value_2.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); // PADDING
	Value value_1 = topFrame->desempilhaOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = value_1.data.longValue | value_2.data.longValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::ixor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_2.type == ValueType::INT);
	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::INT;
	value_1.data.intValue = value_1.data.intValue ^ value_2.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lxor() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); // PADDING
	Value value_1 = topFrame->desempilhaOperandStack();
	// Sobra um padding na pilha que ficará abaixo do resultado

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	value_1.data.longValue = value_1.data.longValue ^ value_2.data.longValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::iinc() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1 *code = topFrame->getCode(topFrame->pc);
    
    u2 index = 0;
    if (_isWide) {
        index = (code[1] << 8) | code[2];
    } else {
        index += code[1];
    }
    
    Value localVariable = topFrame->obterLocalVariableValue(index);
    assert(localVariable.type == ValueType::INT);
    
    int32_t inc;
    if (_isWide) {
        uint16_t constant = (code[3] << 8) | code[4];
        inc = (int32_t) (int16_t) constant;
    } else {
        inc = (int32_t) (int8_t) code[2];
    }
    
    localVariable.data.intValue += inc;
    topFrame->trocaLocalVariable(localVariable, index);
    
    topFrame->pc += _isWide ? 5 : 3;
    _isWide = false;
}

void Operations::i2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);

	Value padding;
	padding.type = ValueType::PADDING;

	topFrame->empilharOperandStack(padding);

    value_1.data.longValue = (int64_t) value_1.data.intValue;
	value_1.type = ValueType::LONG;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::i2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);

	value_1.type = ValueType::FLOAT;
	value_1.data.floatValue = (float) value_1.data.intValue;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::i2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->empilharOperandStack(padding);

	value_1.type = ValueType::DOUBLE;
	value_1.data.doubleValue = (double) value_1.data.intValue;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::l2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); //padding

	assert(value_1.type == ValueType::LONG);

    value_1.data.intValue = (int32_t) value_1.data.intValue;
    value_1.printType = ValueType::INT;
	value_1.type = ValueType::INT;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::l2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); //padding

	assert(value_1.type == ValueType::LONG);

	value_1.type = ValueType::FLOAT;
	value_1.data.floatValue = (float) value_1.data.longValue;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::l2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	//manter padding na pilha de operandos

	assert(value_1.type == ValueType::LONG);

	value_1.type = ValueType::DOUBLE;
	value_1.data.doubleValue = (double) value_1.data.longValue;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::f2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::FLOAT);

    value_1.printType = ValueType::INT;
	value_1.type = ValueType::INT;
	value_1.data.intValue = (int32_t) value_1.data.floatValue;

	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::f2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::FLOAT);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->empilharOperandStack(padding);

	value_1.type = ValueType::LONG;
	value_1.data.longValue = (uint64_t) value_1.data.floatValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::f2d() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::FLOAT);

	Value padding;
	padding.type = ValueType::PADDING;
	topFrame->empilharOperandStack(padding);

	value_1.type = ValueType::DOUBLE;
	value_1.data.doubleValue = (double) value_1.data.floatValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::d2i() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); //padding

	assert(value_1.type == ValueType::DOUBLE);

    value_1.printType = ValueType::INT;
	value_1.type = ValueType::INT;
	value_1.data.intValue = (int32_t) value_1.data.doubleValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::d2l() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	//manter padding na pilha de operandos

	assert(value_1.type == ValueType::DOUBLE);

	value_1.type = ValueType::LONG;
	value_1.data.longValue = (int64_t) value_1.data.doubleValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::d2f() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack(); //padding

	assert(value_1.type == ValueType::DOUBLE);

	value_1.type = ValueType::FLOAT;
	value_1.data.floatValue = (float) value_1.data.doubleValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::i2b() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);
    
    value_1.printType = ValueType::BYTE;
    
    value_1.data.intValue = (int32_t) (int8_t) value_1.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::i2c() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::CHAR;
    
    value_1.data.charValue = (uint32_t) (uint8_t) value_1.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::i2s() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_1 = topFrame->desempilhaOperandStack();

	assert(value_1.type == ValueType::INT);

    value_1.printType = ValueType::SHORT;
    
    value_1.data.intValue = (int32_t) (int16_t) value_1.data.intValue;
	topFrame->empilharOperandStack(value_1);

	topFrame->pc += 1;
}

void Operations::lcmp() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value resultado;
    resultado.printType = ValueType::INT;
	resultado.type = ValueType::INT;

	assert(value_2.type == ValueType::LONG);
	assert(value_1.type == ValueType::LONG);

	if (value_1.data.longValue > value_2.data.longValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.longValue == value_2.data.longValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void Operations::fcmpl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();
	Value resultado;
    resultado.printType = ValueType::INT;
	resultado.type = ValueType::INT;

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);

	if (isnan(value_1.data.floatValue) || isnan(value_2.data.floatValue)) {
		resultado.data.intValue = -1;
	} else if (value_1.data.floatValue > value_2.data.floatValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue == value_2.data.floatValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void Operations::fcmpg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();
	Value resultado;
    resultado.printType = ValueType::INT;
	resultado.type = ValueType::INT;

	assert(value_2.type == ValueType::FLOAT);
	assert(value_1.type == ValueType::FLOAT);

	if (isnan(value_1.data.floatValue) || isnan(value_2.data.floatValue)) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue > value_2.data.floatValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.floatValue == value_2.data.floatValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void Operations::dcmpl() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value resultado;
    resultado.printType = ValueType::INT;
	resultado.type = ValueType::INT;

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);

	if (isnan(value_1.data.doubleValue) || isnan(value_2.data.doubleValue)) {
		resultado.data.intValue = -1;
	} else if (value_1.data.doubleValue > value_2.data.doubleValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue == value_2.data.doubleValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void Operations::dcmpg() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value_2 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value value_1 = topFrame->desempilhaOperandStack();
	topFrame->desempilhaOperandStack();
	Value resultado;
    resultado.printType = ValueType::INT;
	resultado.type = ValueType::INT;

	assert(value_2.type == ValueType::DOUBLE);
	assert(value_1.type == ValueType::DOUBLE);

	if (isnan(value_1.data.doubleValue) || isnan(value_2.data.doubleValue)) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue > value_2.data.doubleValue) {
		resultado.data.intValue = 1;
	} else if (value_1.data.doubleValue == value_2.data.doubleValue) {
		resultado.data.intValue = 0;
	} else {
		resultado.data.intValue = -1;
	}

	topFrame->empilharOperandStack(resultado);

	topFrame->pc += 1;
}

void Operations::ifeq() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value value = topFrame->desempilhaOperandStack();
    assert(value.type == ValueType::INT);
    
    if (value.data.intValue == 0) {
        u1 *code = topFrame->getCode(topFrame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branchOffset = (byte1 << 8) | byte2;
        topFrame->pc += branchOffset;
    } else {
        topFrame->pc += 3;
    }
}

void Operations::ifne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	
	if (value.data.intValue != 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::iflt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	
	if (value.data.intValue < 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::ifge() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	
	if (value.data.intValue >= 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::ifgt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	
	if (value.data.intValue > 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::ifle() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value = topFrame->desempilhaOperandStack();
	assert(value.type == ValueType::INT);
	
	if (value.data.intValue <= 0) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmpeq() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue == value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmpne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue != value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
	} else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmplt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue < value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmpge() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue >= value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmpgt() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue > value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_icmple() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::INT);
	assert(value2.type == ValueType::INT);
	
	if (value1.data.intValue <= value2.data.intValue) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_acmpeq() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::REFERENCE);
	assert(value2.type == ValueType::REFERENCE);
	
	if (value1.data.object == value2.data.object) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::if_acmpne() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	Value value2 = topFrame->desempilhaOperandStack();
	Value value1 = topFrame->desempilhaOperandStack();
	assert(value1.type == ValueType::REFERENCE);
	assert(value2.type == ValueType::REFERENCE);

	if (value1.data.object != value2.data.object) {
		u1 *code = topFrame->getCode(topFrame->pc);
		u1 byte1 = code[1];
		u1 byte2 = code[2];
		int16_t branchOffset = (byte1 << 8) | byte2;
		topFrame->pc += branchOffset;
    } else {
		topFrame->pc += 3;
    }
}

void Operations::func_goto() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	topFrame->pc += branchOffset;
}

void Operations::jsr() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();
	
	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	int16_t branchOffset = (byte1 << 8) | byte2;
	
	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 3; 
	topFrame->empilharOperandStack(returnAddr);
	
	topFrame->pc += branchOffset;
}

// Pode ser modificado pelo wide
void Operations::ret() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1]; // índice do vetor de variáveis locais
	uint16_t index = (uint16_t) byte1;

	if (_isWide) {
		u1 byte2 = code[2];
		index = (byte1 << 8) | byte2;
	}

	assert(((int16_t)(topFrame->sizeLocalVariables()) > index));
	Value value = topFrame->obterLocalVariableValue(index);

	assert(value.type == ValueType::RETURN_ADDR);
	topFrame->trocaLocalVariable(value, index);

	topFrame->pc = value.data.returnAddress;
	_isWide = false;
}

void Operations::tableswitch() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1* code = topFrame->getCode(topFrame->pc);
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    
    u1 lowbyte1 = code[padding + 5];
    u1 lowbyte2 = code[padding + 6];
    u1 lowbyte3 = code[padding + 7];
    u1 lowbyte4 = code[padding + 8];
    uint32_t lowbytes = (lowbyte1 << 24) | (lowbyte2 << 16) | (lowbyte3 << 8) | lowbyte4;
    
    u1 highbyte1 = code[padding + 9];
    u1 highbyte2 = code[padding + 10];
    u1 highbyte3 = code[padding + 11];
    u1 highbyte4 = code[padding + 12];
    uint32_t highbytes = (highbyte1 << 24) | (highbyte2 << 16) | (highbyte3 << 8) | highbyte4;
    
    Value keyValue = topFrame->desempilhaOperandStack();
    assert(keyValue.type == ValueType::INT);
    int32_t key = keyValue.data.intValue;
    
    uint32_t i;
    uint32_t baseIndex = padding + 13;
    int32_t offsets = highbytes - lowbytes + 1;
    bool matched = false;
    for (i = 0; i < (unsigned)offsets; i++) {
        if ((unsigned)key == (unsigned)lowbytes) {
            int32_t offset = (code[baseIndex] << 24) | (code[baseIndex+1] << 16) | (code[baseIndex+2] << 8) | code[baseIndex+3];
            topFrame->pc += offset;
            matched = true;
            break;
        }
        lowbytes++;
        baseIndex += 4;
    }
    
    if (!matched) {
        topFrame->pc += defaultBytes; // salto default
    }
}

void Operations::lookupswitch() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    u1* code = topFrame->getCode(topFrame->pc);
    u1 padding = 4 - (topFrame->pc + 1) % 4;
    padding = (padding == 4) ? 0 : padding;
    
    u1 defaultbyte1 = code[padding + 1];
    u1 defaultbyte2 = code[padding + 2];
    u1 defaultbyte3 = code[padding + 3];
    u1 defaultbyte4 = code[padding + 4];
    int32_t defaultBytes = (defaultbyte1 << 24) | (defaultbyte2 << 16) | (defaultbyte3 << 8) | defaultbyte4;
    
    u1 npairs1 = code[padding + 5];
    u1 npairs2 = code[padding + 6];
    u1 npairs3 = code[padding + 7];
    u1 npairs4 = code[padding + 8];
    uint32_t npairs = (npairs1 << 24) | (npairs2 << 16) | (npairs3 << 8) | npairs4;

    Value keyValue = topFrame->desempilhaOperandStack();
    assert(keyValue.type == ValueType::INT);
    int32_t key = keyValue.data.intValue;
    
    uint32_t i;
    uint32_t baseIndex = padding + 9;
    bool matched = false;
    for (i = 0; i < npairs; i++) {
        int32_t match = (code[baseIndex] << 24) | (code[baseIndex+1] << 16) | (code[baseIndex+2] << 8) | code[baseIndex+3];
        
        if (key == match) {
            int32_t offset = (code[baseIndex+4] << 24) | (code[baseIndex+5] << 16) | (code[baseIndex+6] << 8) | code[baseIndex+7];
            topFrame->pc += offset;
            matched = true;
            break;
        }
        baseIndex += 8;
    }
    
    if (!matched) {
        topFrame->pc += defaultBytes; // salto default
    }
}

void Operations::ireturn() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value returnValue = topFrame->desempilhaOperandStack();
    assert(returnValue.type == ValueType::INT);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->empilharOperandStack(returnValue);
}

void Operations::lreturn() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value returnValue = topFrame->desempilhaOperandStack();
    assert(returnValue.type == ValueType::LONG);
    assert(topFrame->desempilhaOperandStack().type == ValueType::PADDING); // o debaixo precisa ser padding
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    Value padding;
    padding.type = ValueType::PADDING;
    newTopFrame->empilharOperandStack(padding);
    newTopFrame->empilharOperandStack(returnValue);
}

void Operations::freturn() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value returnValue = topFrame->desempilhaOperandStack();
    assert(returnValue.type == ValueType::FLOAT);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->empilharOperandStack(returnValue);
}

void Operations::dreturn() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value returnValue = topFrame->desempilhaOperandStack();
    assert(returnValue.type == ValueType::DOUBLE);
    assert(topFrame->desempilhaOperandStack().type == ValueType::PADDING); // o debaixo precisa ser padding
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    
    Value padding;
    padding.type = ValueType::PADDING;
    newTopFrame->empilharOperandStack(padding);
    newTopFrame->empilharOperandStack(returnValue);
}

void Operations::areturn() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value returnValue = topFrame->desempilhaOperandStack();
    assert(returnValue.type == ValueType::REFERENCE);
    
    stackFrame.destroyTopFrame();
    
    Frame *newTopFrame = stackFrame.getTopFrame();
    newTopFrame->empilharOperandStack(returnValue);
}

void Operations::func_return() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    stackFrame.destroyTopFrame();
}

void Operations::getstatic() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    // caso especial
    if (className == "java/lang/System" && fieldDescriptor == "Ljava/io/PrintStream;" ) {
        topFrame->pc += 3;
        return;
    }
    // fim do caso especial
    
    MethodArea &methodArea = MethodArea::getInstance();
    StaticClass *classRuntime = methodArea.carregarClassNamed(className);

    while (classRuntime != NULL) {
        if (classRuntime->fieldExists(fieldName) == false) {
            if (classRuntime->getClassFile()->super_class == 0) {
                classRuntime = NULL;
            } else {
                string superClassName = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->super_class);
                classRuntime = methodArea.carregarClassNamed(superClassName);
            }
        } else {
            break;
        }
    }

    if (classRuntime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (stackFrame.getTopFrame() != topFrame) return;
    
    Value staticValue = classRuntime->getValueFromField(fieldName);
    switch (staticValue.type) {
        case ValueType::BOOLEAN:
            staticValue.type = ValueType::INT;
            staticValue.printType = ValueType::BOOLEAN;
            break;
        case ValueType::BYTE:
            staticValue.type = ValueType::INT;
            staticValue.printType = ValueType::BYTE;
            break;
        case ValueType::SHORT:
            staticValue.type = ValueType::INT;
            staticValue.printType = ValueType::SHORT;
            break;
        case ValueType::INT:
            staticValue.type = ValueType::INT;
            staticValue.printType = ValueType::INT;
            break;
        default:
            break;
    }
    
    if (staticValue.type == ValueType::DOUBLE || staticValue.type == ValueType::LONG) {
        Value paddingValue;
        paddingValue.type = ValueType::PADDING;
        topFrame->empilharOperandStack(paddingValue);
    }

    topFrame->empilharOperandStack(staticValue);

    topFrame->pc += 3;
}

void Operations::putstatic() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    MethodArea &methodArea = MethodArea::getInstance();
    StaticClass *classRuntime = methodArea.carregarClassNamed(className);

    while (classRuntime != NULL) {
        if (classRuntime->fieldExists(fieldName) == false) {
            if (classRuntime->getClassFile()->super_class == 0) {
                classRuntime = NULL;
            } else {
                string superClassName = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->super_class);
                classRuntime = methodArea.carregarClassNamed(superClassName);
            }
        } else {
            break;
        }
    }

    if (classRuntime == NULL) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
    if (stackFrame.getTopFrame() != topFrame) return;
    
    Value topValue = topFrame->desempilhaOperandStack();
    if (topValue.type == ValueType::DOUBLE || topValue.type == ValueType::LONG) {
        topFrame->desempilhaOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                topValue.type = ValueType::BYTE;
                topValue.printType = ValueType::BYTE;
                break;
            case 'C':
                topValue.type = ValueType::CHAR;
                topValue.type = ValueType::CHAR;
                break;
            case 'S':
                topValue.type = ValueType::SHORT;
                topValue.type = ValueType::SHORT;
                break;
            case 'Z':
                topValue.type = ValueType::BOOLEAN;
                topValue.type = ValueType::BOOLEAN;
                break;
        }
    }

    classRuntime->putValueIntoField(topValue, fieldName);

    topFrame->pc += 3;
}

void Operations::getfield() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    Value objectValue = topFrame->desempilhaOperandStack();
    assert(objectValue.type == ValueType::REFERENCE);
    Object *object = objectValue.data.object;
    assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    InstanceClass *classInstance = (InstanceClass *) object;

    if (!classInstance->fieldExists(fieldName)) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }

    Value fieldValue = classInstance->getValueFromField(fieldName);
    switch (fieldValue.type) {
        case ValueType::BOOLEAN:
            fieldValue.type = ValueType::INT;
            fieldValue.printType = ValueType::BOOLEAN;
            break;
        case ValueType::BYTE:
            fieldValue.type = ValueType::INT;
            fieldValue.printType = ValueType::BYTE;
            break;
        case ValueType::SHORT:
            fieldValue.type = ValueType::INT;
            fieldValue.printType = ValueType::SHORT;
            break;
        case ValueType::INT:
            fieldValue.type = ValueType::INT;
            fieldValue.printType = ValueType::INT;
            break;
        default:
            break;
    }
    
    if (fieldValue.type == ValueType::DOUBLE || fieldValue.type == ValueType::LONG) {
        Value paddingValue;
        paddingValue.type = ValueType::PADDING;
        topFrame->empilharOperandStack(paddingValue);
    }

    topFrame->empilharOperandStack(fieldValue);

    topFrame->pc += 3;
}

void Operations::putfield() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t fieldIndex = (byte1 << 8) | byte2;
    cp_info fieldCP = constantPool[fieldIndex-1];
    assert(fieldCP.tag == CONSTANT_Fieldref); // precisa ser um fieldRef

    CONSTANT_Fieldref_info fieldRef = fieldCP.info.fieldref_info;

    string className = getFormattedConstant(constantPool, fieldRef.class_index);

    cp_info nameAndTypeCP = constantPool[fieldRef.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info fieldNameAndType = nameAndTypeCP.info.nameAndType_info;

    string fieldName = getFormattedConstant(constantPool, fieldNameAndType.name_index);
    string fieldDescriptor = getFormattedConstant(constantPool, fieldNameAndType.descriptor_index);

    Value valueToBeInserted = topFrame->desempilhaOperandStack();
    if (valueToBeInserted.type == ValueType::DOUBLE || valueToBeInserted.type == ValueType::LONG) {
        topFrame->desempilhaOperandStack(); // removendo padding
    } else {
        switch (fieldDescriptor[0]) {
            case 'B':
                valueToBeInserted.type = ValueType::BYTE;
                valueToBeInserted.printType = ValueType::BYTE;
                break;
            case 'C':
                valueToBeInserted.type = ValueType::CHAR;
                valueToBeInserted.printType = ValueType::CHAR;
                break;
            case 'S':
                valueToBeInserted.type = ValueType::SHORT;
                valueToBeInserted.printType = ValueType::SHORT;
                break;
            case 'Z':
                valueToBeInserted.type = ValueType::BOOLEAN;
                valueToBeInserted.printType = ValueType::BOOLEAN;
                break;
        }
    }

    Value objectValue = topFrame->desempilhaOperandStack();
    assert(objectValue.type == ValueType::REFERENCE);
    Object *object = objectValue.data.object;
    assert(object->objectType() == ObjectType::CLASS_INSTANCE);
    InstanceClass *classInstance = (InstanceClass *) object;

    classInstance->putValueIntoField(valueToBeInserted, fieldName);

    topFrame->pc += 3;
}

void Operations::invokevirtual() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className.find("java/") != string::npos) {
        // simulando println ou print
        if (className == "java/io/PrintStream" && (methodName == "print" || methodName == "println")) {
            if (methodDescriptor != "()V") {
                Value printValue = topFrame->desempilhaOperandStack();

                if (printValue.type == ValueType::INT) {
                    switch (printValue.printType) {
                        case ValueType::BOOLEAN:
                            printf("%s", printValue.data.booleanValue == 0 ? "false" : "true");
                            break;
                        case ValueType::BYTE:
                            printf("%d", printValue.data.byteValue);
                            break;
                        case ValueType::CHAR:
                            printf("%c", printValue.data.charValue);
                            break;
                        case ValueType::SHORT:
                            printf("%d", printValue.data.shortValue);
                            break;
                        default:
                            printf("%d", printValue.data.intValue);
                            break;
                    }
                } else {
                    switch (printValue.type) {
                        case ValueType::DOUBLE:
                            topFrame->desempilhaOperandStack(); // removendo padding
                            printf("%f", printValue.data.doubleValue);
                            break;
                        case ValueType::FLOAT:
                            printf("%f", printValue.data.floatValue);
                            break;
                        case ValueType::LONG:
                            topFrame->desempilhaOperandStack(); // removendo padding
                            printf("%lld", (long long) printValue.data.longValue);

                            break;
                        case ValueType::REFERENCE:
                            assert(printValue.data.object->objectType() == ObjectType::STRING_INSTANCE);
                            printf("%s", ((StringObject *) printValue.data.object)->getString().c_str());
                            break;
                        case ValueType::BOOLEAN:
                            printf("%s", printValue.data.booleanValue == 0 ? "false" : "true");
                            break;
                        case ValueType::BYTE:
                            printf("%d", printValue.data.byteValue);
                            break;
                        case ValueType::CHAR:
                            printf("%c", printValue.data.charValue);
                            break;
                        case ValueType::SHORT:
                            printf("%d", printValue.data.shortValue);
                            break;
                        default:
                            cerr << "Tentando printar tipo de dado invalido: " << printValue.type << endl;
                            exit(1);
                            break;
                    }
                }
            }

            if (methodName == "println") printf("\n");
        } else if (className == "java/lang/String" && methodName == "equals") {
            Value strValue1 = topFrame->desempilhaOperandStack();
            Value strValue2 = topFrame->desempilhaOperandStack();
            assert(strValue1.type == ValueType::REFERENCE);
            assert(strValue2.type == ValueType::REFERENCE);
            assert(strValue1.data.object->objectType() == ObjectType::STRING_INSTANCE);
            assert(strValue2.data.object->objectType() == ObjectType::STRING_INSTANCE);
            
            StringObject *str1 = (StringObject*) strValue1.data.object;
            StringObject *str2 = (StringObject*) strValue2.data.object;
            
            Value result;
            result.printType = ValueType::INT;
            result.type = ValueType::INT;
            if (str1->getString() == str2->getString()) {
                result.data.intValue = 1;
            } else {
                result.data.intValue = 0;
            }
            topFrame->empilharOperandStack(result);
        } else if (className == "java/lang/String" && methodName == "length") {	
            Value strValue = topFrame->desempilhaOperandStack();
            assert(strValue.type == ValueType::REFERENCE);		
            assert(strValue.data.object->objectType() == ObjectType::STRING_INSTANCE);		
                    
            StringObject *str = (StringObject*) strValue.data.object;		
                    
            Value result;
            result.printType = ValueType::INT;
            result.type = ValueType::INT;		
            result.data.intValue = (str->getString()).size();		
            topFrame->empilharOperandStack(result);
        } else {
            cerr << "Tentando invocar metodo de instancia invalido: " << methodName << endl;
            exit(1);
        }
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->desempilhaOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->desempilhaOperandStack();
        assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        InstanceClass *instance = (InstanceClass *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        StaticClass *classRuntime = methodArea.carregarClassNamed(className);
        
        Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Operations::invokespecial() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);
    
    // casos especiais
    if ((className == "java/lang/Object" || className == "java/lang/String") && methodName == "<init>") {
        if (className == "java/lang/String") {
            topFrame->desempilhaOperandStack();
        }
        
        topFrame->pc += 3;
        return;
    }
    // fim dos casos especiais
    
    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo especial invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->desempilhaOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->desempilhaOperandStack();
        assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        InstanceClass *instance = (InstanceClass *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        StaticClass *classRuntime = methodArea.carregarClassNamed(className);
        
        Frame *newFrame = new Frame(instance, classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Operations::invokestatic() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    assert(methodCP.tag == CONSTANT_Methodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className == "java/lang/Object" && methodName == "registerNatives") {
        topFrame->pc += 3;
        return;
    }
    
    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo estatico invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->desempilhaOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        MethodArea &methodArea = MethodArea::getInstance();
        StaticClass *classRuntime = methodArea.carregarClassNamed(className);
        Frame *newFrame = new Frame(classRuntime, methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 3;
}

void Operations::invokeinterface() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    stack<Value> operandStackBackup = topFrame->backupOperandStack();
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t methodIndex = (byte1 << 8) | byte2;
    cp_info methodCP = constantPool[methodIndex-1];
    assert(methodCP.tag == CONSTANT_Methodref || methodCP.tag == CONSTANT_InterfaceMethodref); // precisa referenciar um método

    CONSTANT_Methodref_info methodInfo = methodCP.info.methodref_info;

    string className = getFormattedConstant(constantPool, methodInfo.class_index);

    cp_info nameAndTypeCP = constantPool[methodInfo.name_and_type_index-1];
    assert(nameAndTypeCP.tag == CONSTANT_NameAndType); // precisa ser um nameAndType

    CONSTANT_NameAndType_info methodNameAndType = nameAndTypeCP.info.nameAndType_info;

    string methodName = getFormattedConstant(constantPool, methodNameAndType.name_index);
    string methodDescriptor = getFormattedConstant(constantPool, methodNameAndType.descriptor_index);

    if (className.find("java/") != string::npos) {
        cerr << "Tentando invocar metodo de interface invalido: " << methodName << endl;
        exit(1);
    } else {
        uint16_t nargs = 0; // numero de argumentos contidos na pilha de operandos
        uint16_t i = 1; // pulando o primeiro '('
        while (methodDescriptor[i] != ')') {
            char baseType = methodDescriptor[i];
            if (baseType == 'D' || baseType == 'J') {
                nargs += 2;
            } else if (baseType == 'L') {
                nargs++;
                while (methodDescriptor[++i] != ';');
            } else if (baseType == '[') {
                nargs++;
                while (methodDescriptor[++i] == '[');
                if (methodDescriptor[i] == 'L') while (methodDescriptor[++i] != ';');
            } else {
                nargs++;
            }
            i++;
        }

        vector<Value> args;
        for (int i = 0; i < nargs; i++) {
            Value value = topFrame->desempilhaOperandStack();
            if (value.type == ValueType::PADDING) {
                args.insert(args.begin() + 1, value); // adicionando o padding após o valor double/long.
            } else {
                args.insert(args.begin(), value);
            }
        }

        Value objectValue = topFrame->desempilhaOperandStack();
        assert(objectValue.type == ValueType::REFERENCE); // necessita ser uma referência para objeto
        args.insert(args.begin(), objectValue);

        Object *object = objectValue.data.object;
        assert(object->objectType() == ObjectType::CLASS_INSTANCE); // objeto precisa ser uma instância
        InstanceClass *instance = (InstanceClass *) object;

        MethodArea &methodArea = MethodArea::getInstance();
        methodArea.carregarClassNamed(className); // carregando a interface (caso ainda não foi carregada).
        
        Frame *newFrame = new Frame(instance, instance->getClassRuntime(), methodName, methodDescriptor, args);

        // se a stack frame mudou, é porque teve <clinit> adicionado, então terminar a execução da instrução para eles serem executados.
        if (stackFrame.getTopFrame() != topFrame) {
            topFrame->setOperandStackFromBackup(operandStackBackup);
            delete newFrame;
            return;
        }

        stackFrame.addFrame(newFrame);
    }

    topFrame->pc += 5;
}

void Operations::func_new() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();     
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);

    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t classIndex = (byte1 << 8) | byte2;
    cp_info classCP = constantPool[classIndex-1];
    assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
    string className = getFormattedConstant(constantPool, classInfo.name_index);

    Object *object;
    if (className == "java/lang/String") {
        object = new StringObject();
    } else {
        MethodArea &methodArea = MethodArea::getInstance();
        StaticClass *classRuntime = methodArea.carregarClassNamed(className);
        object = new InstanceClass(classRuntime); // Cria instancia da classe e coloca na heap
    }
    
    // Armazena referência na pilha
    Value objectref;
    objectref.data.object = object;
    objectref.type = ValueType::REFERENCE;
    topFrame->empilharOperandStack(objectref);
    
    topFrame->pc += 3;
}

void Operations::newarray() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value count = topFrame->desempilhaOperandStack(); // Número de elementos no array
    assert(count.type == ValueType::INT);
    
    if (count.data.intValue < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    Value padding;
    ArrayObject *array; // array que será criado
    Value value; // elemento que irá popular o array
    value.data.longValue = 0; // inicializando Value com 0s
    

    padding.type = ValueType::PADDING;
    
    u1 *code = topFrame->getCode(topFrame->pc);
    switch (code[1]) { // argumento representa tipo do array
        case 4:
            array = new ArrayObject(ValueType::BOOLEAN);
            value.type = ValueType::BOOLEAN;
            value.printType = ValueType::BOOLEAN;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 5:
            array = new ArrayObject(ValueType::CHAR);
            value.type = ValueType::CHAR;
            value.printType = ValueType::CHAR;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 6:
            array = new ArrayObject(ValueType::FLOAT);
            value.type = ValueType::FLOAT;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 7:
            array = new ArrayObject(ValueType::DOUBLE);
            value.type = ValueType::DOUBLE;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 8:
            array = new ArrayObject(ValueType::BYTE);
            value.type = ValueType::BYTE;
            value.printType = ValueType::BYTE;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 9:
            array = new ArrayObject(ValueType::SHORT);
            value.type = ValueType::SHORT;
            value.printType = ValueType::SHORT;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 10:
            array = new ArrayObject(ValueType::INT);
            value.type = ValueType::INT;
            value.printType = ValueType::INT;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
        case 11:
            array = new ArrayObject(ValueType::LONG);
            value.type = ValueType::LONG;
            for (int i = 0; i < count.data.intValue; i++) {
                array->pushValue(value);
            }
            break;
    }
    
    Value arrayref; // Referencia pro array na pilha de operandos
    arrayref.type = ValueType::REFERENCE;
    arrayref.data.object = array;
    
    topFrame->empilharOperandStack(arrayref);
    topFrame->pc += 2;
}

void Operations::anewarray() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value count = topFrame->desempilhaOperandStack(); // Número de elementos no array
    assert(count.type == ValueType::INT);
    if (count.data.intValue < 0) {
        cerr << "NegativeArraySizeException" << endl;
        exit(1);
    }
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];

    uint16_t classIndex = (byte1 << 8) | byte2; // Índice na pool de constantes
    cp_info classCP = constantPool[classIndex-1];
    assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info; // Formata nome da classe
    string className = getFormattedConstant(constantPool, classInfo.name_index);

    if (className != "java/lang/String") {
        int i = 0;
        while (className[i] == '[') i++;
        if (className[i] == 'L') {
            MethodArea &methodArea = MethodArea::getInstance();
            methodArea.carregarClassNamed(className.substr(i+1, className.size()-i-2)); // carrega a classe de referência (se ainda não foi).
        }
    }

    // criando objeto da classe instanciada
    Value objectref;
    objectref.type = ValueType::REFERENCE;
    objectref.data.object = new ArrayObject(ValueType::REFERENCE);
    
    // populando array com NULL
    Value nullValue;
    nullValue.type = ValueType::REFERENCE;
    nullValue.data.object = NULL;
    for (int i = 0; i < count.data.intValue; i++) {
        ((ArrayObject *) objectref.data.object)->pushValue(nullValue);
    }

    topFrame->empilharOperandStack(objectref);
    
    topFrame->pc += 3;
}

void Operations::arraylength() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value arrayref = topFrame->desempilhaOperandStack();  
    assert(arrayref.type == ValueType::REFERENCE);
    if (arrayref.data.object == NULL) {
        cerr << "NullPointerException" << endl;
        exit(1);
    }
    
    Value length;
    length.type = ValueType::INT;
    length.data.intValue = ((ArrayObject *) arrayref.data.object)->getSize();
    
    topFrame->empilharOperandStack(length);
    topFrame->pc += 1 ;
}

void Operations::athrow() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    topFrame->pc += 1;
}

void Operations::checkcast() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    MethodArea &methodArea = MethodArea::getInstance();
    
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    cp_info *constantPool = *(topFrame->obterConstantPool());
    cp_info cpElement = constantPool[cpIndex-1];
    assert(cpElement.tag == CONSTANT_Class);
    string className = getFormattedConstant(constantPool, cpIndex);
    
    Value objectrefValue = topFrame->desempilhaOperandStack();
    assert(objectrefValue.type == ValueType::REFERENCE);
    
    Value resultValue;
    resultValue.type = ValueType::INT;
    
    if (objectrefValue.data.object == NULL) {
        cerr << "ClassCastException" << endl;
        exit(1);
    } else {
        Object *obj = objectrefValue.data.object;
        
        if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
        	InstanceClass *classInstance = (InstanceClass *) obj;
            StaticClass *classRuntime = classInstance->getClassRuntime();
            
            bool found = false;
            while (!found) {
                ClassFile *classFile = classRuntime->getClassFile();
                string currClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                
                if (currClassName == className) {
                    found = true;
                } else {
                    if (classFile->super_class == 0) {
                        break;
                    } else {
                        string superClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                        classRuntime = methodArea.carregarClassNamed(superClassName);
                    }
                }
            }
            
            resultValue.data.intValue = found ? 1 : 0;
        } else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
            resultValue.data.intValue = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.intValue = 1;
            } else {
                resultValue.data.intValue = 0;
            }
        }
    }
    
    topFrame->empilharOperandStack(resultValue);
    
    topFrame->pc += 3;
}

void Operations::instanceof() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    MethodArea &methodArea = MethodArea::getInstance();

    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    
    u2 cpIndex = (byte1 << 8) | byte2;
    cp_info *constantPool = *(topFrame->obterConstantPool());
    cp_info cpElement = constantPool[cpIndex-1];
    assert(cpElement.tag == CONSTANT_Class);
    string className = getFormattedConstant(constantPool, cpIndex);
    
    Value objectrefValue = topFrame->desempilhaOperandStack();
    assert(objectrefValue.type == ValueType::REFERENCE);
    
    Value resultValue;
    resultValue.type = ValueType::INT;

    if (objectrefValue.data.object == NULL) {
        resultValue.data.intValue = 0;
    } else {
        Object *obj = objectrefValue.data.object;
        
        if (obj->objectType() == ObjectType::CLASS_INSTANCE) {
            InstanceClass *classInstance = (InstanceClass *) obj;
            StaticClass *classRuntime = classInstance->getClassRuntime();
            
            bool found = false;
            while (!found) {
                ClassFile *classFile = classRuntime->getClassFile();
                string currClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                
                if (currClassName == className) {
                    found = true;
                } else {
                    if (classFile->super_class == 0) {
                        break;
                    } else {
                        string superClassName = getFormattedConstant(classFile->constant_pool, classFile->this_class);
                        classRuntime = methodArea.carregarClassNamed(superClassName);
                    }
                }
            }
            
            resultValue.data.intValue = found ? 1 : 0;
        } else if (obj->objectType() == ObjectType::STRING_INSTANCE) {
            resultValue.data.intValue = (className == "java/lang/String" || className == "java/lang/Object") ? 1 : 0;
        } else {
            if (className == "java/lang/Object") {
                resultValue.data.intValue = 1;
            } else {
                resultValue.data.intValue = 0;
            }
        }
    }
    
    topFrame->empilharOperandStack(resultValue);
    
    topFrame->pc += 3;
}

void Operations::monitorenter() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    topFrame->pc += 1;
}

void Operations::monitorexit() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    topFrame->pc += 1;
}

void Operations::wide() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();
	_isWide = true;
	topFrame->pc += 1;
}

void Operations::multianewarray() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();       
    Frame *topFrame = stackFrame.getTopFrame();
    
    cp_info *constantPool = *(topFrame->obterConstantPool());
    u1 *code = topFrame->getCode(topFrame->pc);
    u1 byte1 = code[1];
    u1 byte2 = code[2];
    u1 dimensions = code[3];
    assert(dimensions >= 1);

    uint16_t classIndex = (byte1 << 8) | byte2;
    cp_info classCP = constantPool[classIndex-1];
    assert(classCP.tag == CONSTANT_Class);
    
    CONSTANT_Class_info classInfo = classCP.info.class_info;
    string className = getFormattedConstant(constantPool, classInfo.name_index);
    
    // obter o tipo dentro de className:
    ValueType valueType;
    int i = 0;
    while (className[i] == '[') i++;
    
    string multiArrayType = className.substr(i+1, className.size()-i-2); // em caso de ser uma referência (e.g. [[[Ljava/lang/String;)
    
    switch (className[i]) {
        case 'L':
            if (multiArrayType != "java/lang/String") {
                MethodArea &methodArea = MethodArea::getInstance();
                methodArea.carregarClassNamed(multiArrayType); // verifica se existe classe com esse nome
            }
            valueType = ValueType::REFERENCE;
            break;
        case 'B':
            valueType = ValueType::BYTE;
            break;
        case 'C':
            valueType = ValueType::CHAR;
            break;
        case 'D':
            valueType = ValueType::DOUBLE;
            break;
        case 'F':
            valueType = ValueType::FLOAT;
            break;
        case 'I':
            valueType = ValueType::INT;
            break;
        case 'J':
            valueType = ValueType::LONG;
            break;
        case 'S':
            valueType = ValueType::SHORT;
            break;
        case 'Z':
            valueType = ValueType::BOOLEAN;
            break;
        default:
            cerr << "Descritor invalido em multianewarray" << endl;
            exit(1);
    }
    
    stack<int> count;
    for (int i = 0; i < dimensions; i++) {
        Value dimLength = topFrame->desempilhaOperandStack();
        assert(dimLength.type == ValueType::INT);
        count.push(dimLength.data.intValue);
    }
    
    ArrayObject *array = new ArrayObject((dimensions > 1) ? ValueType::REFERENCE : valueType);
    populateMultiarray(array, valueType, count);
    
    Value arrayValue;
    arrayValue.type = ValueType::REFERENCE;
    arrayValue.data.object = array;
    
    topFrame->empilharOperandStack(arrayValue);
    
    topFrame->pc += 4;
}

void Operations::ifnull() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value referenceValue = topFrame->desempilhaOperandStack();
    assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object == NULL) {
        u1 *code = topFrame->getCode(topFrame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}

void Operations::ifnonnull() {
    PilhaJVM &stackFrame = PilhaJVM::getInstance();
    Frame *topFrame = stackFrame.getTopFrame();
    
    Value referenceValue = topFrame->desempilhaOperandStack();
    assert(referenceValue.type == ValueType::REFERENCE);
    
    if (referenceValue.data.object != NULL) {
        u1 *code = topFrame->getCode(topFrame->pc);
        u1 byte1 = code[1];
        u1 byte2 = code[2];
        int16_t branch =  (byte1 << 8) | byte2;
        topFrame->pc += branch;
    } else {
        topFrame->pc += 3;
    }
}

void Operations::goto_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u1 byte3 = code[3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topFrame->pc += branchOffset;

}

void Operations::jsr_w() {
	PilhaJVM &stackFrame = PilhaJVM::getInstance();
	Frame *topFrame = stackFrame.getTopFrame();

	u1 *code = topFrame->getCode(topFrame->pc);
	u1 byte1 = code[1];
	u1 byte2 = code[2];
	u1 byte3 = code[3];
	u1 byte4 = code[4];
	int32_t branchOffset = (byte1 << 24) | (byte2 << 16) | (byte3 << 8)| byte4;

	Value returnAddr;
	returnAddr.type = ValueType::RETURN_ADDR;
	returnAddr.data.returnAddress = topFrame->pc + 5;
	topFrame->empilharOperandStack(returnAddr);

	topFrame->pc += branchOffset;
	assert((int32_t)topFrame->pc < (int32_t)topFrame->sizeCode());
}

void Operations::initInstructions() {
    funcaoGenerica[0x00] = &Operations::nop;
    funcaoGenerica[0x01] = &Operations::aconst_null;
    funcaoGenerica[0x02] = &Operations::iconst_m1;
    funcaoGenerica[0x03] = &Operations::iconst_0;
    funcaoGenerica[0x04] = &Operations::iconst_1;
    funcaoGenerica[0x05] = &Operations::iconst_2;
    funcaoGenerica[0x06] = &Operations::iconst_3;
    funcaoGenerica[0x07] = &Operations::iconst_4;
    funcaoGenerica[0x08] = &Operations::iconst_5;
    funcaoGenerica[0x09] = &Operations::lconst_0;
    funcaoGenerica[0x0a] = &Operations::lconst_1;
    funcaoGenerica[0x0b] = &Operations::fconst_0;
    funcaoGenerica[0x0c] = &Operations::fconst_1;
    funcaoGenerica[0x0d] = &Operations::fconst_2;
    funcaoGenerica[0x0e] = &Operations::dconst_0;
    funcaoGenerica[0x0f] = &Operations::dconst_1;
    funcaoGenerica[0x10] = &Operations::bipush;
    funcaoGenerica[0x11] = &Operations::sipush;
    funcaoGenerica[0x12] = &Operations::ldc;
    funcaoGenerica[0x13] = &Operations::ldc_w;
    funcaoGenerica[0x14] = &Operations::ldc2_w;
    funcaoGenerica[0x15] = &Operations::iload;
    funcaoGenerica[0x16] = &Operations::lload;
    funcaoGenerica[0x17] = &Operations::fload;
    funcaoGenerica[0x18] = &Operations::dload;
    funcaoGenerica[0x19] = &Operations::aload;
    funcaoGenerica[0x1a] = &Operations::iload_0;
    funcaoGenerica[0x1b] = &Operations::iload_1;
    funcaoGenerica[0x1c] = &Operations::iload_2;
    funcaoGenerica[0x1d] = &Operations::iload_3;
    funcaoGenerica[0x1e] = &Operations::lload_0;
    funcaoGenerica[0x1f] = &Operations::lload_1;
    funcaoGenerica[0x20] = &Operations::lload_2;
    funcaoGenerica[0x21] = &Operations::lload_3;
    funcaoGenerica[0x22] = &Operations::fload_0;
    funcaoGenerica[0x23] = &Operations::fload_1;
    funcaoGenerica[0x24] = &Operations::fload_2;
    funcaoGenerica[0x25] = &Operations::fload_3;
    funcaoGenerica[0x26] = &Operations::dload_0;
    funcaoGenerica[0x27] = &Operations::dload_1;
    funcaoGenerica[0x28] = &Operations::dload_2;
    funcaoGenerica[0x29] = &Operations::dload_3;
    funcaoGenerica[0x2a] = &Operations::aload_0;
    funcaoGenerica[0x2b] = &Operations::aload_1;
    funcaoGenerica[0x2c] = &Operations::aload_2;
    funcaoGenerica[0x2d] = &Operations::aload_3;
    funcaoGenerica[0x2e] = &Operations::iaload;
    funcaoGenerica[0x2f] = &Operations::laload;
    funcaoGenerica[0x30] = &Operations::faload;
    funcaoGenerica[0x31] = &Operations::daload;
    funcaoGenerica[0x32] = &Operations::aaload;
    funcaoGenerica[0x33] = &Operations::baload;
    funcaoGenerica[0x34] = &Operations::caload;
    funcaoGenerica[0x35] = &Operations::saload;
    funcaoGenerica[0x36] = &Operations::istore;
    funcaoGenerica[0x37] = &Operations::lstore;
    funcaoGenerica[0x38] = &Operations::fstore;
    funcaoGenerica[0x39] = &Operations::dstore;
    funcaoGenerica[0x3a] = &Operations::astore;
    funcaoGenerica[0x3b] = &Operations::istore_0;
    funcaoGenerica[0x3c] = &Operations::istore_1;
    funcaoGenerica[0x3d] = &Operations::istore_2;
    funcaoGenerica[0x3e] = &Operations::istore_3;
    funcaoGenerica[0x3f] = &Operations::lstore_0;
    funcaoGenerica[0x40] = &Operations::lstore_1;
    funcaoGenerica[0x41] = &Operations::lstore_2;
    funcaoGenerica[0x42] = &Operations::lstore_3;
    funcaoGenerica[0x43] = &Operations::fstore_0;
    funcaoGenerica[0x44] = &Operations::fstore_1;
    funcaoGenerica[0x45] = &Operations::fstore_2;
    funcaoGenerica[0x46] = &Operations::fstore_3;
    funcaoGenerica[0x47] = &Operations::dstore_0;
    funcaoGenerica[0x48] = &Operations::dstore_1;
    funcaoGenerica[0x49] = &Operations::dstore_2;
    funcaoGenerica[0x4a] = &Operations::dstore_3;
    funcaoGenerica[0x4b] = &Operations::astore_0;
    funcaoGenerica[0x4c] = &Operations::astore_1;
    funcaoGenerica[0x4d] = &Operations::astore_2;
    funcaoGenerica[0x4e] = &Operations::astore_3;
    funcaoGenerica[0x4f] = &Operations::iastore;
    funcaoGenerica[0x50] = &Operations::lastore;
    funcaoGenerica[0x51] = &Operations::fastore;
    funcaoGenerica[0x52] = &Operations::dastore;
    funcaoGenerica[0x53] = &Operations::aastore;
    funcaoGenerica[0x54] = &Operations::bastore;
    funcaoGenerica[0x55] = &Operations::castore;
    funcaoGenerica[0x56] = &Operations::sastore;
    funcaoGenerica[0x57] = &Operations::pop;
    funcaoGenerica[0x58] = &Operations::pop2;
    funcaoGenerica[0x59] = &Operations::dup;
    funcaoGenerica[0x5a] = &Operations::dup2_x1;
    funcaoGenerica[0x5b] = &Operations::dup2_x2;
    funcaoGenerica[0x5c] = &Operations::dup2;
    funcaoGenerica[0x5d] = &Operations::dup2_x1;
    funcaoGenerica[0x5e] = &Operations::dup2_x2;
    funcaoGenerica[0x5f] = &Operations::swap;
    funcaoGenerica[0x60] = &Operations::iadd;
    funcaoGenerica[0x61] = &Operations::ladd;
    funcaoGenerica[0x62] = &Operations::fadd;
    funcaoGenerica[0x63] = &Operations::dadd;
    funcaoGenerica[0x64] = &Operations::isub;
    funcaoGenerica[0x65] = &Operations::lsub;
    funcaoGenerica[0x66] = &Operations::fsub;
    funcaoGenerica[0x67] = &Operations::dsub;
    funcaoGenerica[0x68] = &Operations::imul;
    funcaoGenerica[0x69] = &Operations::lmul;
    funcaoGenerica[0x6a] = &Operations::fmul;
    funcaoGenerica[0x6b] = &Operations::dmul;
    funcaoGenerica[0x6c] = &Operations::idiv;
    funcaoGenerica[0x6d] = &Operations::ldiv;
    funcaoGenerica[0x6e] = &Operations::fdiv;
    funcaoGenerica[0x6f] = &Operations::ddiv;
    funcaoGenerica[0x70] = &Operations::irem;
    funcaoGenerica[0x71] = &Operations::lrem;
    funcaoGenerica[0x72] = &Operations::frem;
    funcaoGenerica[0x73] = &Operations::drem;
    funcaoGenerica[0x74] = &Operations::ineg;
    funcaoGenerica[0x75] = &Operations::lneg;
    funcaoGenerica[0x76] = &Operations::fneg;
    funcaoGenerica[0x77] = &Operations::dneg;
    funcaoGenerica[0x78] = &Operations::ishl;
    funcaoGenerica[0x79] = &Operations::lshl;
    funcaoGenerica[0x7a] = &Operations::ishr;
    funcaoGenerica[0x7b] = &Operations::lshr;
    funcaoGenerica[0x7c] = &Operations::iushr;
    funcaoGenerica[0x7d] = &Operations::lushr;
    funcaoGenerica[0x7e] = &Operations::iand;
    funcaoGenerica[0x7f] = &Operations::land;
    funcaoGenerica[0x80] = &Operations::ior;
    funcaoGenerica[0x81] = &Operations::lor;
    funcaoGenerica[0x82] = &Operations::ixor;
    funcaoGenerica[0x83] = &Operations::lxor;
    funcaoGenerica[0x84] = &Operations::iinc;
    funcaoGenerica[0x85] = &Operations::i2l;
    funcaoGenerica[0x86] = &Operations::i2f;
    funcaoGenerica[0x87] = &Operations::i2d;
    funcaoGenerica[0x88] = &Operations::l2i;
    funcaoGenerica[0x89] = &Operations::l2f;
    funcaoGenerica[0x8a] = &Operations::l2d;
    funcaoGenerica[0x8b] = &Operations::f2i;
    funcaoGenerica[0x8c] = &Operations::f2l;
    funcaoGenerica[0x8d] = &Operations::f2d;
    funcaoGenerica[0x8e] = &Operations::d2i;
    funcaoGenerica[0x8f] = &Operations::d2l;
    funcaoGenerica[0x90] = &Operations::d2f;
    funcaoGenerica[0x91] = &Operations::i2b;
    funcaoGenerica[0x92] = &Operations::i2c;
    funcaoGenerica[0x93] = &Operations::i2s;
    funcaoGenerica[0x94] = &Operations::lcmp;
    funcaoGenerica[0x95] = &Operations::fcmpl;
    funcaoGenerica[0x96] = &Operations::fcmpg;
    funcaoGenerica[0x97] = &Operations::dcmpl;
    funcaoGenerica[0x98] = &Operations::dcmpg;
    funcaoGenerica[0x99] = &Operations::ifeq;
    funcaoGenerica[0x9a] = &Operations::ifne;
    funcaoGenerica[0x9b] = &Operations::iflt;
    funcaoGenerica[0x9c] = &Operations::ifge;
    funcaoGenerica[0x9d] = &Operations::ifgt;
    funcaoGenerica[0x9e] = &Operations::ifle;
    funcaoGenerica[0x9f] = &Operations::if_icmpeq;
    funcaoGenerica[0xa0] = &Operations::if_icmpne;
    funcaoGenerica[0xa1] = &Operations::if_icmplt;
    funcaoGenerica[0xa2] = &Operations::if_icmpge;
    funcaoGenerica[0xa3] = &Operations::if_icmpgt;
    funcaoGenerica[0xa4] = &Operations::if_icmple;
    funcaoGenerica[0xa5] = &Operations::if_acmpeq;
    funcaoGenerica[0xa6] = &Operations::if_acmpne;
    funcaoGenerica[0xa7] = &Operations::func_goto;
    funcaoGenerica[0xa8] = &Operations::jsr;
    funcaoGenerica[0xa9] = &Operations::ret;
    funcaoGenerica[0xaa] = &Operations::tableswitch;
    funcaoGenerica[0xab] = &Operations::lookupswitch;
    funcaoGenerica[0xac] = &Operations::ireturn;
    funcaoGenerica[0xad] = &Operations::lreturn;
    funcaoGenerica[0xae] = &Operations::freturn;
    funcaoGenerica[0xaf] = &Operations::dreturn;
    funcaoGenerica[0xb0] = &Operations::areturn;
    funcaoGenerica[0xb1] = &Operations::func_return;
    funcaoGenerica[0xb2] = &Operations::getstatic;
    funcaoGenerica[0xb3] = &Operations::putstatic;
    funcaoGenerica[0xb4] = &Operations::getfield;
    funcaoGenerica[0xb5] = &Operations::putfield;
    funcaoGenerica[0xb6] = &Operations::invokevirtual;
    funcaoGenerica[0xb7] = &Operations::invokespecial;
    funcaoGenerica[0xb8] = &Operations::invokestatic;
    funcaoGenerica[0xb9] = &Operations::invokeinterface;
    funcaoGenerica[0xbb] = &Operations::func_new;
    funcaoGenerica[0xbc] = &Operations::newarray;
    funcaoGenerica[0xbd] = &Operations::anewarray;
    funcaoGenerica[0xbe] = &Operations::arraylength;
    funcaoGenerica[0xbf] = &Operations::athrow;
    funcaoGenerica[0xc0] = &Operations::checkcast;
    funcaoGenerica[0xc1] = &Operations::instanceof;
    funcaoGenerica[0xc2] = &Operations::monitorenter;
    funcaoGenerica[0xc3] = &Operations::monitorexit;
    funcaoGenerica[0xc4] = &Operations::wide;
    funcaoGenerica[0xc5] = &Operations::multianewarray;
    funcaoGenerica[0xc6] = &Operations::ifnull;
    funcaoGenerica[0xc7] = &Operations::ifnonnull;
    funcaoGenerica[0xc8] = &Operations::goto_w;
    funcaoGenerica[0xc9] = &Operations::jsr_w;
}
