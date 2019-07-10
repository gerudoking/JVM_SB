
#include "MethodArea.h"

#include "ClassVisao.h" // talvez retirar isso e colocar a getFormattedConstant() na Util.
#include "LeitorExibidor.h"
#include "Operations.h"
#include "PilhaJVM.h"

MethodArea::MethodArea() {
    
}

MethodArea::~MethodArea() {
    
}

StaticClass* MethodArea::carregarClassNamed(const string &className) {
    // se a classe já tiver sido carregada, retorna-la
    if (_classes.count(className) > 0) {
        return getClassNamed(className);
    }
    
    string classNameStr(className);
    string classLocation("");
    string classFormat(".class");
    
    if (classNameStr.size() < classFormat.size() || classNameStr.compare(classNameStr.size() - classFormat.size(), classFormat.size(), classFormat) != 0) {
        classNameStr = classLocation + classNameStr + classFormat; // concatena com ".class"
    }

    FILE *fp = fopen(classNameStr.c_str(), "rb");
    if (fp == NULL) {
        cerr << "NoClassDefFoundError: " << classNameStr << endl;
        exit(1);
    }
    
    LeitorExibidor &classLoader = LeitorExibidor::getInstance();
    ClassFile *classFile = classLoader.readClassFile(fp);
    StaticClass *classRuntime = new StaticClass(classFile);
    addClass(classRuntime);
    fclose(fp);
    
    // adicionando <clinit> da classe (se existir) na stack frame.
    Operations &operations = Operations::getInstance();
    bool existsClinit = operations.verificarMetodoExiste(classRuntime, "<clinit>", "()V");
    if (existsClinit) {
        PilhaJVM &stackFrame = PilhaJVM::getInstance();
        Frame *newFrame = new Frame(classRuntime, "<clinit>", "()V");
        stackFrame.addFrame(newFrame);
    }
    
    return classRuntime;
}

StaticClass* MethodArea::getClassNamed(const string &className) {
    map<string, StaticClass*>::iterator it = _classes.find(className);
    
    if (it == _classes.end()) {
        return NULL;
    }
    
    return it->second;
}

bool MethodArea::addClass(StaticClass *classRuntime) {
    ClassFile *classFile = classRuntime->getClassFile();
    
    const char *key = getFormattedConstant(classFile->constant_pool, classFile->this_class);
    
    if (_classes.count(key) > 0) {
        return false;
    }
    
    _classes[key] = classRuntime;
    return true;
}
