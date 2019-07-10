#ifndef executionengine_h
#define executionengine_h

#include <string>
#include <queue>
#include <stack>

#include <iostream>
#include <cassert>
#include <queue>

#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <cstdlib>

#include "ArrayObject.h"
#include "BasicTypes.h"
#include "InstanceClass.h"

using namespace std;

class Operations;
typedef void (Operations::*funcaoGenericaPointeiro)();


/** @class Operations
 * @brief É responsável por realizar a execução do .class
 * @brief Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
  */
class Operations {
public:
    /**
     * @brief Obter a única instância da Execution Engine.
     * @return A instância da Execution Engine.
     */
    static Operations& getInstance() {
        static Operations instance;
        return instance;
    }
    
    /**
     * @brief Destrutor padrão.
     */
    ~Operations();
    
    /**
     * @brief Inicia a Execution Engine com a classe passada.
     *
     * Esse método irá iniciar execução através do método estático main.
     * @param
     */
    void executarMetodos(StaticClass *classRuntime);
    
    /**
     * @brief Verifica se o método informado existe na classe atual.
     * @param classRuntime A classe que a pesquisa irá ser realizada.
     * @param name O nome do método.
     * @param descriptor O descritor do método.
     * @return Retorna \c true caso o método exista, ou \c false caso contrário.
     */
    bool verificarMetodoExiste(StaticClass *classRuntime, string name, string descriptor);

    /**
     * @brief Popula os vetores de um multiarray
     * @param array Cada array que representa uma dimansão
     * @param value Referência à uma classe 
     * @param count Número de elementos em um array
     */
    void populateMultiarray(ArrayObject *array, ValueType value, stack<int> count);
    
private:
    /**
     * @brief Construtor padrão.
     */
    Operations();
    
    Operations(Operations const&); // não permitir implementação do construtor de cópia
    void operator=(Operations const&); // não permitir implementação do operador de igual
    
    /**
     * Armazena \c true se a última instrução foi um wide, e \c false caso contrário.
     */
    bool _isWide;
    
    /**
     * @brief Implementa a funcionalidade da instrução nop.
     */
    void   nop();
    
    /**
     * @brief Implementa a funcionalidade da instrução aconst_null.
     */
    void   aconst_null();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_m1.
     */
    void   iconst_m1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_0.
     */
    void   iconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_1.
     */
    void   iconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_2.
     */
    void   iconst_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_3.
     */
    void   iconst_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_4.
     */
    void   iconst_4();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_5.
     */
    void   iconst_5();
    
    /**
     * @brief Implementa a funcionalidade da instrução lconst_0.
     */
    void   lconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lconst_1.
     */
    void   lconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_0.
     */
    void   fconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_1.
     */
    void   fconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_2.
     */
    void   fconst_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dconst_0.
     */
    void   dconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dconst_1.
     */
    void   dconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução bipush.
     */
    void   bipush();
    
    /**
     * @brief Implementa a funcionalidade da instrução sipush.
     */
    void   sipush();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc.
     */
    void   ldc();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc_w.
     */
    void   ldc_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc2_w.
     */
    void   ldc2_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload.
     */
    void   iload();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload.
     */
    void   lload();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload.
     */
    void   fload();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload.
     */
    void   dload();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload.
     */
    void   aload();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_0.
     */
    void   iload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_1.
     */
    void   iload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_2.
     */
    void   iload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_3.
     */
    void   iload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_0.
     */
    void   lload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_1.
     */
    void   lload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_2.
     */
    void   lload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_3.
     */
    void   lload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_0.
     */
    void   fload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_1.
     */
    void   fload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_2.
     */
    void   fload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_3.
     */
    void   fload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_0.
     */
    void   dload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_1.
     */
    void   dload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_2.
     */
    void   dload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_3.
     */
    void   dload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_0.
     */
    void   aload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_1.
     */
    void   aload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_2.
     */
    void   aload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_3.
     */
    void   aload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iaload.
     */
    void   iaload();
    
    /**
     * @brief Implementa a funcionalidade da instrução laload.
     */
    void   laload();
    
    /**
     * @brief Implementa a funcionalidade da instrução faload.
     */
    void   faload();
    
    /**
     * @brief Implementa a funcionalidade da instrução daload.
     */
    void   daload();
    
    /**
     * @brief Implementa a funcionalidade da instrução aaload.
     */
    void   aaload();
    
    /**
     * @brief Implementa a funcionalidade da instrução baload.
     */
    void   baload();
    
    /**
     * @brief Implementa a funcionalidade da instrução caload.
     */
    void   caload();
    
    /**
     * @brief Implementa a funcionalidade da instrução saload.
     */
    void   saload();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore.
     */
    void   istore();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore.
     */
    void   lstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore.
     */
    void   fstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore.
     */
    void   dstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore.
     */
    void   astore();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_0.
     */
    void   istore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_1.
     */
    void   istore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_2.
     */
    void   istore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_3.
     */
    void   istore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_0.
     */
    void   lstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_1.
     */
    void   lstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_2.
     */
    void   lstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_3.
     */
    void   lstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_0.
     */
    void   fstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_1.
     */
    void   fstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_2.
     */
    void   fstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_3.
     */
    void   fstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_0.
     */
    void   dstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_1.
     */
    void   dstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_2.
     */
    void   dstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_3.
     */
    void   dstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_0.
     */
    void   astore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_1.
     */
    void   astore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_2.
     */
    void   astore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_3.
     */
    void   astore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iastore.
     */
    void   iastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução lastore.
     */
    void   lastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução fastore.
     */
    void   fastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução dastore.
     */
    void   dastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução aastore.
     */
    void   aastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução bastore.
     */
    void   bastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução castore.
     */
    void   castore();
    
    /**
     * @brief Implementa a funcionalidade da instrução sastore.
     */
    void   sastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução pop.
     */
    void   pop();
    
    /**
     * @brief Implementa a funcionalidade da instrução pop2.
     */
    void   pop2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup.
     */
    void   dup();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup_x1.
     */
    void   dup_x1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup_x2.
     */
    void   dup_x2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2.
     */
    void   dup2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2_x1.
     */
    void   dup2_x1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2_x2.
     */
    void   dup2_x2();
    
    /**
     * @brief Implementa a funcionalidade da instrução swap.
     */
    void   swap();
    
    /**
     * @brief Implementa a funcionalidade da instrução iadd.
     */
    void   iadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução ladd.
     */
    void   ladd();
    
    /**
     * @brief Implementa a funcionalidade da instrução fadd.
     */
    void   fadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução dadd.
     */
    void   dadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução isub.
     */
    void   isub();
    
    /**
     * @brief Implementa a funcionalidade da instrução lsub.
     */
    void   lsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução fsub.
     */
    void   fsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução dsub.
     */
    void   dsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução imul.
     */
    void   imul();
    
    /**
     * @brief Implementa a funcionalidade da instrução lmul.
     */
    void   lmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução fmul.
     */
    void   fmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução dmul.
     */
    void   dmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução idiv.
     */
    void   idiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldiv.
     */
    void   ldiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução fdiv.
     */
    void   fdiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução ddiv.
     */
    void   ddiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução irem.
     */
    void   irem();
    
    /**
     * @brief Implementa a funcionalidade da instrução lrem.
     */
    void   lrem();
    
    /**
     * @brief Implementa a funcionalidade da instrução frem.
     */
    void   frem();
    
    /**
     * @brief Implementa a funcionalidade da instrução drem.
     */
    void   drem();
    
    /**
     * @brief Implementa a funcionalidade da instrução ineg.
     */
    void   ineg();
    
    /**
     * @brief Implementa a funcionalidade da instrução lneg.
     */
    void   lneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução fneg.
     */
    void   fneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução dneg.
     */
    void   dneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução ishl.
     */
    void   ishl();
    
    /**
     * @brief Implementa a funcionalidade da instrução lshl.
     */
    void   lshl();
    
    /**
     * @brief Implementa a funcionalidade da instrução ishr.
     */
    void   ishr();
    
    /**
     * @brief Implementa a funcionalidade da instrução lshr.
     */
    void   lshr();
    
    /**
     * @brief Implementa a funcionalidade da instrução iushr.
     */
    void   iushr();
    
    /**
     * @brief Implementa a funcionalidade da instrução lushr.
     */
    void   lushr();
    
    /**
     * @brief Implementa a funcionalidade da instrução iand.
     */
    void   iand();
    
    /**
     * @brief Implementa a funcionalidade da instrução land.
     */
    void   land();
    
    /**
     * @brief Implementa a funcionalidade da instrução ior.
     */
    void   ior();
    
    /**
     * @brief Implementa a funcionalidade da instrução lor.
     */
    void   lor();
    
    /**
     * @brief Implementa a funcionalidade da instrução ixor.
     */
    void   ixor();
    
    /**
     * @brief Implementa a funcionalidade da instrução lxor.
     */
    void   lxor();
    
    /**
     * @brief Implementa a funcionalidade da instrução iinc.
     */
    void   iinc();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2l.
     */
    void   i2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2f.
     */
    void   i2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2d.
     */
    void   i2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2i.
     */
    void   l2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2f.
     */
    void   l2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2d.
     */
    void   l2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2i.
     */
    void   f2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2l.
     */
    void   f2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2d.
     */
    void   f2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2i.
     */
    void   d2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2l.
     */
    void   d2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2f.
     */
    void   d2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2b.
     */
    void   i2b();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2c.
     */
    void   i2c();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2s.
     */
    void   i2s();
    
    /**
     * @brief Implementa a funcionalidade da instrução lcmp.
     */
    void   lcmp();
    
    /**
     * @brief Implementa a funcionalidade da instrução fcmpl.
     */
    void   fcmpl();
    
    /**
     * @brief Implementa a funcionalidade da instrução fcmpg.
     */
    void   fcmpg();
    
    /**
     * @brief Implementa a funcionalidade da instrução dcmpl.
     */
    void   dcmpl();
    
    /**
     * @brief Implementa a funcionalidade da instrução dcmpg.
     */
    void   dcmpg();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifeq.
     */
    void   ifeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifne.
     */
    void   ifne();
    
    /**
     * @brief Implementa a funcionalidade da instrução iflt.
     */
    void   iflt();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifge.
     */
    void   ifge();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifgt.
     */
    void   ifgt();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifle.
     */
    void   ifle();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpeq.
     */
    void   if_icmpeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpne.
     */
    void   if_icmpne();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmplt.
     */
    void   if_icmplt();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpge.
     */
    void   if_icmpge();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpgt.
     */
    void   if_icmpgt();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmple.
     */
    void   if_icmple();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_acmpeq.
     */
    void   if_acmpeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_acmpne.
     */
    void   if_acmpne();
    
    /**
     * @brief Implementa a funcionalidade da instrução goto.
     */
    void   func_goto();
    
    /**
     * @brief Implementa a funcionalidade da instrução jsr.
     */
    void   jsr();
    
    /**
     * @brief Implementa a funcionalidade da instrução ret.
     */
    void   ret();
    
    /**
     * @brief Implementa a funcionalidade da instrução tableswitch.
     */
    void   tableswitch();
    
    /**
     * @brief Implementa a funcionalidade da instrução lookupswitch.
     */
    void   lookupswitch();
    
    /**
     * @brief Implementa a funcionalidade da instrução ireturn.
     */
    void   ireturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução lreturn.
     */
    void   lreturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução freturn.
     */
    void   freturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução dreturn.
     */
    void   dreturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução areturn.
     */
    void   areturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução return.
     */
    void   func_return();
    
    /**
     * @brief Implementa a funcionalidade da instrução getstatic.
     */
    void   getstatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução putstatic.
     */
    void   putstatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução getfield.
     */
    void   getfield();
    
    /**
     * @brief Implementa a funcionalidade da instrução putfield.
     */
    void   putfield();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokevirtual.
     */
    void   invokevirtual();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokespecial.
     */
    void   invokespecial();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokestatic.
     */
    void   invokestatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokeinterface.
     */
    void   invokeinterface();
    
    /**
     * @brief Implementa a funcionalidade da instrução new.
     */
    void   func_new();
    
    /**
     * @brief Implementa a funcionalidade da instrução newarray.
     */
    void   newarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução anewarray.
     */
    void   anewarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução arraylength.
     */
    void   arraylength();
    
    /**
     * @brief Implementa a funcionalidade da instrução athrow.
     */
    void   athrow();
    
    /**
     * @brief Implementa a funcionalidade da instrução checkcast.
     */
    void   checkcast();
    
    /**
     * @brief Implementa a funcionalidade da instrução instanceof.
     */
    void   instanceof();
    
    /**
     * @brief Implementa a funcionalidade da instrução monitorenter.
     */
    void   monitorenter();
    
    /**
     * @brief Implementa a funcionalidade da instrução monitorexit.
     */
    void   monitorexit();
    
    /**
     * @brief Implementa a funcionalidade da instrução wide.
     */
    void   wide();
    
    /**
     * @brief Implementa a funcionalidade da instrução multianewarray.
     */
    void   multianewarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifnull.
     */
    void   ifnull();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifnonnull.
     */
    void   ifnonnull();
    
    /**
     * @brief Implementa a funcionalidade da instrução goto_w.
     */
    void   goto_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução jsr_w.
     */
    void   jsr_w();
    
    /**
     * @brief Inicializa o vetor de ponteiros de funções.
     */
    void initInstructions();
    
    /**
     * O vetor de ponteiros de funções.
     */
    funcaoGenericaPointeiro funcaoGenerica[202];
};

#endif /* executionengine_h */
