#include "Exhibitor.h"
#include <inttypes.h>

/**
*  Fun��o que mostra informa��es na tela
* @param classe Ponteiro para o arquivo de classe a ser printado na tela
*/
void mostra_outras_informacoes(ClassFile *classe){
    char *nomeThisClass, *nomeSuperClass;
    int index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    nomeThisClass = informacao_nome(index, classe);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    nomeSuperClass = informacao_nome(index, classe);
    printf("\n");
    printf("===Informacoes Gerais====\n");
    printf("|Minor: %d\n", classe->minor_version);
    printf("|Major: %d\n", classe->major_version);
    printf("|Contador da Pool de Constantes: %d\n", classe->constant_pool_count);
    printf("|Flags de acesso: 0x%x\n", classe->access_flags);
    printf("|This.class: <%s>, |CP={%d}|\n", nomeThisClass, classe->this_class);
    printf("|Super.class: <%s>, |CP={%d}|\n", nomeSuperClass, classe->super_class);
    printf("|Contador de interfaces: %d\n", classe->interfaces_count);
    printf("|Contador de campos: %d\n", classe->fields_count);
    printf("|Contador de metodos: %d\n", classe->methods_count);
    printf("|Contador de atributos: %d\n", classe->attributes_count);
	printf("=========================\n");
}

/**
*   Fun��o para mostrar informa��es em um arquivo
*   @param classe   Ponteiro para o arquivo de classe a ser salvo no arquivo
*   @param file     Ponteiro para o arquivo a ser manipulado
*/
void mostra_outras_informacoes_arquivo(ClassFile *classe, FILE *file){
    char *nomeThisClass, *nomeSuperClass;
    int index = classe->constant_pool[classe->this_class - 1].info.Class.name_index - 1;
    nomeThisClass = informacao_nome(index, classe);
    index = classe->constant_pool[classe->super_class - 1].info.Class.name_index - 1;
    nomeSuperClass = informacao_nome(index, classe);
    fprintf(file, "\n===Informacoes Gerais====\n");
    fprintf(file, "|Minor: %d\n", classe->minor_version);
    fprintf(file, "|Major: %d\n", classe->major_version);
    fprintf(file, "|Contador da Pool de Constantes: %d\n", classe->constant_pool_count);
    fprintf(file, "|Flags de acesso: 0x%x\n", classe->access_flags);
    fprintf(file, "|This.class: <%s>, |CP={%d}|\n", nomeThisClass, classe->this_class);
    fprintf(file, "|Super.class: <%s>, |CP={%d}|\n", nomeSuperClass, classe->super_class);
    fprintf(file, "|Contador de interfaces: %d\n", classe->interfaces_count);
    fprintf(file, "|Contador de campos: %d\n", classe->fields_count);
    fprintf(file, "|Contador de metodos: %d\n", classe->methods_count);
    fprintf(file, "|Contador de atributos: %d\n", classe->attributes_count);
	fprintf(file, "=========================\n");
    fprintf(file, "\n");
    free(nomeThisClass);
    free(nomeSuperClass);
}


/**
*  Fun��o que exibe a pool de constantes
* @param classe Ponteiro para o arquivo de classe a ser printado na tela
*/
void mostra_poolDe_constantes(ClassFile *classe){
    u8 l;
    char *nome_ref = NULL, *nome_ref2 = NULL, *nome_ref3 = NULL;
    printf("\n");
	printf("\n============ INICIO IMPRESSAO ARQUIVO .class ============\n\n");
    printf("====constant-pool====\n");
    printf("contador da pool de constantes: %d\n", classe->constant_pool_count);
    int index = 0;
    float fvalue;
    double dvalue;
    for (int i = 0;  i < (classe->constant_pool_count - 1); i++){
		printf("\n~~~> ");
        switch (classe->constant_pool[i].tag){
        case CONSTANTClass:
            index = classe->constant_pool[i].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            printf("{%d} const_classe:\n", (i + 1));
            printf("nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Class.name_index);
            break;
        case CONSTANTFieldref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            printf("{%d} const_ref_campo:\n", (i + 1));
            printf("nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Fieldref.class_index);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            nome_ref = informacao_nome(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            nome_ref2 = informacao_nome(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            printf("Tipo e nome:  <%s%s>, |CP={%d}|\n", nome_ref, nome_ref2, classe->constant_pool[i].info.Fieldref.name_and_type_index);
            break;
        case CONSTANTMethodref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            printf("{%d} cont_ref_metodo:\n", (i + 1));
            printf("nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Methodref.class_index);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            nome_ref = informacao_nome(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            nome_ref2 = informacao_nome(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            printf("Tipo e nome: <%s%s>, |CP={%d}|\n", nome_ref, nome_ref2, classe->constant_pool[i].info.Methodref.name_and_type_index);
            break;
        case CONSTANTInterfaceMethodref:
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index - 1;
            nome_ref2 = informacao_nome(index, classe);
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index - 1;
            nome_ref3 = informacao_nome(index, classe);
            nome_ref2 = strcat(nome_ref2,nome_ref3);
            printf("{%d} const_interface_ref_metodo:\n", (i + 1));
            printf("nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.InterfaceMethodref.class_index);
            printf("Tipo e nome: <%s>, |CP={%d}|\n", nome_ref2, classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
            break;
        case CONSTANTString:
            index = classe->constant_pool[i].info.String.string_index - 1;
            nome_ref = informacao_nome(index, classe);
            printf("{%d} const_string:\n", (i + 1));
            printf("string: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.String.string_index);
            break;
        case CONSTANTInteger:
            printf("{%d} const_int: \n", (i + 1));
            printf("bytes: 0x%x\n", classe->constant_pool[i].info.Integer.bytes);
            printf("inteiro: %d\n", classe->constant_pool[i].info.Integer.bytes);
            break;
        case CONSTANTFloat:
			memcpy(&fvalue,&(classe->constant_pool[i].info.Float.bytes),sizeof(u4));
            printf("{%d} const_float:\n", (i + 1));
            printf("bytes: 0x%x\n", classe->constant_pool[i].info.Float.bytes);
            printf("float: %f\n", fvalue);
            break;
        case CONSTANTLong:
            l = (u8) classe->constant_pool[i].info.Long.high_bytes << 32;
            l = l | classe->constant_pool[i].info.Long.low_bytes;
            printf("{%d} const_long:\n", (i + 1));
            printf("high: 0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
            printf("low: t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
            printf("long: %lld\n", l);
            i++;
            printf("[%d] \n", (i + 1));
            break;
        case CONSTANTDouble:
            l = (u8) classe->constant_pool[i].info.Double.high_bytes << 32;
            l = l | classe->constant_pool[i].info.Double.low_bytes;
            memcpy(&dvalue,&l,sizeof(u8));
            printf("{%d} const_double :\n", (i + 1));
            printf("high: 0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
            printf("low: 0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
            printf("double: %f\n",dvalue);
            i++;
            printf("[%d] \n", (i + 1));
            break;
        case CONSTANTNameAndType:
            index = classe->constant_pool[i].info.NameAndType.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
            nome_ref2 = informacao_nome(index, classe);
            printf("{%d} const_tipo-nome:\n", (i + 1));
            printf("nome: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.NameAndType.name_index);
            printf("descritor: <%s>, |CP={%d}|\n", nome_ref2, classe->constant_pool[i].info.NameAndType.descriptor_index);
            break;


        case CONSTANTUtf8:
            printf("{%d} const_utf8:\n", (i + 1));
            printf("tamanho do vetor de bytes:%d\n", classe->constant_pool[i].info.Utf8.length);
            printf("tamanho da string: %d\n", classe->constant_pool[i].info.Utf8.length);
            printf("string: ");
            for (int j = 0; j < classe->constant_pool[i].info.Utf8.length; j++)
                printf("%c", classe->constant_pool[i].info.Utf8.bytes[j]);
            printf("\n");
            break;

        }
    }
    free(nome_ref);
    free(nome_ref2);
    free(nome_ref3);
    printf("\n");
}

/**
*   Fun��o para mostrar a pool de constantes em um arquivo
*   @param classe   Ponteiro para o arquivo de classe a ser salvo no arquivo
*   @param file     Ponteiro para o arquivo a ser manipulado
*/
void mostra_poolDe_constantes_arquivo(ClassFile *classe, FILE *file){
    u8 l;
    char *nome_ref = NULL, *nome_ref2 = NULL, *nome_ref3 = NULL;
	fprintf(file, "============ INICIO IMPRESSAO ARQUIVO .class ============\n\n");
    fprintf(file, "====constant-pool====\n");
    fprintf(file, "contador da pool de constantes: %d\n", classe->constant_pool_count);
    int index = 0;
    float fvalue;
    double dvalue;
    for (int i = 0;  i < (classe->constant_pool_count - 1); i++){
		fprintf(file, "\n~~~> ");
        switch (classe->constant_pool[i].tag){
        case CONSTANTClass:
            index = classe->constant_pool[i].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            fprintf(file, "{%d} const_classe:\n", (i + 1));
            fprintf(file, "nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Class.name_index);
            break;
        case CONSTANTFieldref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            fprintf(file, "{%d} const_ref_campo:\n", (i + 1));
            fprintf(file, "nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Fieldref.class_index);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            nome_ref = informacao_nome(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            nome_ref2 = informacao_nome(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            fprintf(file, "Tipo e nome:  <%s%s>, |CP={%d}|\n", nome_ref, nome_ref2, classe->constant_pool[i].info.Fieldref.name_and_type_index);
            break;
        case CONSTANTMethodref:
            index = classe->constant_pool[i].info.Fieldref.class_index - 1;
            index = classe->constant_pool[index].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            fprintf(file, "{%d} cont_ref_metodo:\n", (i + 1));
            fprintf(file, "nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.Methodref.class_index);
            index = classe->constant_pool[i].info.Fieldref.name_and_type_index - 1;
            nome_ref = informacao_nome(classe->constant_pool[index].info.NameAndType.name_index - 1, classe);
            nome_ref2 = informacao_nome(classe->constant_pool[index].info.NameAndType.descriptor_index - 1,
                                          classe);
            fprintf(file, "Tipo e nome: <%s%s>, |CP={%d}|\n", nome_ref, nome_ref2, classe->constant_pool[i].info.Methodref.name_and_type_index);
            break;
        case CONSTANTInterfaceMethodref:
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.class_index - 1].info.Class.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.name_index - 1;
            nome_ref2 = informacao_nome(index, classe);
            index = classe->constant_pool[classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index - 1].info.NameAndType.descriptor_index - 1;
            nome_ref3 = informacao_nome(index, classe);
            nome_ref2 = strcat(nome_ref2,nome_ref3);
            fprintf(file, "{%d} const_interface_ref_metodo:\n", (i + 1));
            fprintf(file, "nome da classe: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.InterfaceMethodref.class_index);
            fprintf(file, "Tipo e nome: <%s>, |CP={%d}|\n", nome_ref2, classe->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
            break;
        case CONSTANTString:
            index = classe->constant_pool[i].info.String.string_index - 1;
            nome_ref = informacao_nome(index, classe);
            fprintf(file, "{%d} const_string:\n", (i + 1));
            fprintf(file, "string: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.String.string_index);
            break;
        case CONSTANTInteger:
            fprintf(file, "{%d} const_int: \n", (i + 1));
            fprintf(file, "bytes: 0x%x\n", classe->constant_pool[i].info.Integer.bytes);
            fprintf(file, "inteiro: %d\n", classe->constant_pool[i].info.Integer.bytes);
            break;
        case CONSTANTFloat:
			memcpy(&fvalue,&(classe->constant_pool[i].info.Float.bytes),sizeof(u4));
            fprintf(file, "{%d} const_float:\n", (i + 1));
            fprintf(file, "bytes: 0x%x\n", classe->constant_pool[i].info.Float.bytes);
            fprintf(file, "float: %f\n", fvalue);
            break;
        case CONSTANTLong:
            l = (u8) classe->constant_pool[i].info.Long.high_bytes << 32;
            l = l | classe->constant_pool[i].info.Long.low_bytes;
            fprintf(file, "{%d} const_long:\n", (i + 1));
            fprintf(file, "high: 0x%x\n", classe->constant_pool[i].info.Long.high_bytes);
            fprintf(file, "low: t0x%x\n", classe->constant_pool[i].info.Long.low_bytes);
            fprintf(file, "long: %lld\n", l);
            i++;
            fprintf(file, "[%d] \n", (i + 1));
            break;
        case CONSTANTDouble:
            l = (u8) classe->constant_pool[i].info.Double.high_bytes << 32;
            l = l | classe->constant_pool[i].info.Double.low_bytes;
            memcpy(&dvalue,&l,sizeof(u8));
            fprintf(file, "{%d} const_double :\n", (i + 1));
            fprintf(file, "high: 0x%x\n", classe->constant_pool[i].info.Double.high_bytes);
            fprintf(file, "low: 0x%x\n", classe->constant_pool[i].info.Double.low_bytes);
            fprintf(file, "double: %f\n",dvalue);
            i++;
            fprintf(file, "[%d] \n", (i + 1));
            break;
        case CONSTANTNameAndType:
            index = classe->constant_pool[i].info.NameAndType.name_index - 1;
            nome_ref = informacao_nome(index, classe);
            index = classe->constant_pool[i].info.NameAndType.descriptor_index - 1;
            nome_ref2 = informacao_nome(index, classe);
            fprintf(file, "{%d} const_tipo-nome:\n", (i + 1));
            fprintf(file, "nome: <%s>, |CP={%d}|\n", nome_ref, classe->constant_pool[i].info.NameAndType.name_index);
            fprintf(file, "descritor: <%s>, |CP={%d}|\n", nome_ref2, classe->constant_pool[i].info.NameAndType.descriptor_index);
            break;
        case CONSTANTUtf8:
            fprintf(file, "{%d} const_utf8:\n", (i + 1));
            fprintf(file, "tamanho do vetor de bytes:%d\n", classe->constant_pool[i].info.Utf8.length);
            fprintf(file, "tamanho da string: %d\n", classe->constant_pool[i].info.Utf8.length);
            fprintf(file, "string: ");
            for (int j = 0; j < classe->constant_pool[i].info.Utf8.length; j++)
                fprintf(file, "%c", classe->constant_pool[i].info.Utf8.bytes[j]);
            fprintf(file, "\n");
            break;
        }
    }
    free(nome_ref);
    free(nome_ref2);
    free(nome_ref3);
    fprintf(file, "\n");
}

/**
*   Fun��o para mostrar um atributo espec�fico na tela
*   @param attributeInfo    Ponteiro para as informa��es do atributo
*   @param classe           Ponteiro para o arquivo de classe do atributo
*/
void mostra_atributo(attribute_info *attributeInfo, ClassFile *classe){
    char *nome_ref = NULL;
    u8 l;
    char *tipoAtributo = NULL;
    u2 index = attributeInfo->attribute_name_index - 1;
    int iterat;
    tipoAtributo = (char *) malloc((classe->constant_pool[index].info.Utf8.length+1) * sizeof(char));
    float fvalue;
    double dvalue;

    for (iterat = 0; iterat < classe->constant_pool[index].info.Utf8.length; iterat++) {
        printf("%c", classe->constant_pool[index].info.Utf8.bytes[iterat]);
        tipoAtributo[iterat] = classe->constant_pool[index].info.Utf8.bytes[iterat];
    }
    tipoAtributo[iterat] = '\0';
    index = attributeInfo->attribute_name_index - 1;
    nome_ref = informacao_nome(index,classe);
    printf("\n");
    printf("\tindex de nome: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->attribute_name_index);
    printf("\tcomprimento do atributo: %d\n", attributeInfo->attribute_length);
    free(nome_ref);
    if (attributeInfo->attribute_length > 0){
        if (!strcmp(tipoAtributo, "ConstantValue")){

            int i;
            u2 index1;
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
            switch (classe->constant_pool[index].tag){
            case CONSTANTLong:
                l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                printf("\nindex-Constant_val: <%ld>, |CP={%d}|", l, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTDouble:
                l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
				memcpy(&dvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u8));
                printf("\nindex-Constant_val: <%f>, |CP={%d}|", dvalue, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTFloat:
				memcpy(&fvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u4));
                printf("\nindex-Constant_val: <%f>, |CP={%d}|", fvalue, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTInteger:
                i = (int32_t)classe->constant_pool[index].info.Integer.bytes;
                printf("\nindex-Constant_val: <%d>, |CP={%d}|", i, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTString:
                index1 = classe->constant_pool[index].info.String.string_index - 1;
                nome_ref = informacao_nome(index1,classe);
                printf("\nindex-Constant_val: <%s>, |CP={%d}|", nome_ref, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code")){

		    printf("\t->Outros dados\n");
            printf("\tstack maximo: %d\n", attributeInfo->info.CodeAttribute.max_stack);
            printf("\tmaximo locals: %d\n", attributeInfo->info.CodeAttribute.max_locals);
            printf("\tcomprimento do codigo: %d\n", attributeInfo->info.CodeAttribute.code_length);
            printf("\tcodigo: \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++){
                Instrucao mapeamento[0xCA];
                mnemonicos(mapeamento);
                u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
                u2 instrIndex;
                int16_t offset;
                char *instrRef;
                printf("\t\t\t%d: %s\t", i, mapeamento[opcode].mnemonico);
                int j;
                double dvalue;
                switch(mapeamento[opcode].req_cp){
                    case REQ_METHODREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        instrRef = informacoes_metodo(instrIndex - 1, classe);
                        printf("<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_METHODREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = informacoes_metodo(instrIndex - 1, classe);
                        printf("<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_FIELDREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = informacoes_camporef(instrIndex - 1, classe);
                        printf("<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_JMPREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
                        printf("%d\t(%d)\t", (offset - 2) + i, offset);
                        break;
                    case REQ_LDCREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
                        printf("%d\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANTInteger:
                                printf("<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANTFloat:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                printf("<%f>\t", fvalue);
                                break;
                            case CONSTANTLong:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                printf("<%ld>\t", l);
                                break;
                            case CONSTANTDouble:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                printf("<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_LDCREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
                        printf("%d\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANTInteger:
                                printf("<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANTFloat:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                printf("<%f>\t", fvalue);
                                break;
                            case CONSTANTLong:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                printf("<%ld>\t", l);
                                break;
                            case CONSTANTDouble:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                printf("<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_ARRAYREF:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        printf("%d\t", instrIndex);
                        switch(instrIndex) {
                            case 0:
                                printf("(ref)\t");
                                break;
                            case 4:
                                printf("(boolean)\t");
                                break;
                            case 5:
                                printf("(char)\t");
                                break;
                            case 6:
                                printf("(float)\t");
                                break;
                            case 7:
                                printf("(double)\t");
                                break;
                            case 8:
                                printf("(byte)\t");
                                break;
                            case 9:
                                printf("(short)\t");
                                break;
                            case 10:
                                printf("(int)\t");
                                break;
                            case 11:
                                printf("(long)\t");
                                break;
                            default:
                                break;
                        }
                        break;
                    case REQ_IINCREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        printf("%d by %d\t", instrIndex1, instrIndex2);
                        break;
                    default:
                        for(j = 0; j < mapeamento[opcode].operandos; j++) {
                            printf("%d\t", attributeInfo->info.CodeAttribute.code[++i]);
                        }
                        break;
                }
                printf("\n");
            }
            printf("\n\texception (comprimento da tabela): %d\n", attributeInfo->info.CodeAttribute.exception_table_length);
            if(attributeInfo->info.CodeAttribute.exception_table_length > 0) {
                printf("\tinicia PC\tEnd PC\thandler PC\ttipo de catch\n");
                for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++){
                    printf("%d: %d\t", i, attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                    printf("%d\t", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                    printf("%d\t", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                    printf("%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
                }
            }
           	printf("\tnumero de atributos do codigo: %d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++){
               	printf("\t{%d} ", k);
                mostra_atributo(&(attributeInfo->info.CodeAttribute.attributes[k]), classe);
            }
        }
        else if (!strcmp(tipoAtributo, "exceptions")){
            printf("\tnumero de execoes: %d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++){
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                nome_ref = informacao_nome(index,classe);
                printf("\tindex de execoes: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.Exception.exception_index_table[i]);
                free(nome_ref);
            }
        }
        else if (!strcmp(tipoAtributo, "classes internas")){
            printf("\tnumero de classes: %d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++){
                free(nome_ref);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                nome_ref = informacao_nome(index,classe);
                printf("\t\tindice da classe interna: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                printf("\t\tindice da classe externa: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                printf("\t\tindice do nome interno: <%s>, |CP={%d}|\n",nome_ref, attributeInfo->info.InnerClasses.classes[i].inner_name_index);
                printf("\t\tflags de acesso da classe interna: %d\n",attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }else if (!strcmp(tipoAtributo, "SourceFile")){
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            nome_ref = informacao_nome(index,classe);
            printf("\tindex do arquivo de origem: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.Sourcefile.sourcefile_index);
            free(nome_ref);
        }else if (!strcmp(tipoAtributo, "LineNumberTable")){
            printf("\tNumero de linhas: %d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            if(attributeInfo->info.LineNumberTable.line_number_table_length > 0) {
                printf("\n\tinicia PC\tNumero da linha\n");
                for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++){
                   	printf("\t\t%d: %d", i, attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
                    printf("\t\t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                }
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable")){
            printf("\tcomprimento da tabela: %d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++){
                free(nome_ref);
                printf("\t\tinicia PC: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                printf("\t\tcomprimento: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                nome_ref = informacao_nome(index,classe);
                printf("\t\tindex de nome: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                printf("\t\tDescriptor Index: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index);
                printf("\t\tIndex: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }else{
            printf("\tdefault: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++){
                printf("\t%x", attributeInfo->info.Default.data[i]);
            }
            printf("\n");
        }
    }
    //free(nome_ref);
    //free(tipoAtributo);
}

/**
*   Fun��o para mostrar um atributo espec�fico e salvar em um arquivo
*   @param attributeInfo    Ponteiro para as informa��es do atributo
*   @param classe           Ponteiro para o arquivo de classe
*   @param file             Ponteiro para o arquivo a ser manipulado
*/
void mostra_atributo_arquivo(attribute_info *attributeInfo, ClassFile *classe, FILE *file){
    char *nome_ref = NULL;
    u8 l;
    char *tipoAtributo = NULL;
    u2 index = attributeInfo->attribute_name_index - 1;
    int iterat;
    tipoAtributo = (char *) malloc((classe->constant_pool[index].info.Utf8.length+1) * sizeof(char));
    float fvalue;
    double dvalue;

    for (iterat = 0; iterat < classe->constant_pool[index].info.Utf8.length; iterat++) {
        fprintf(file, "%c", classe->constant_pool[index].info.Utf8.bytes[iterat]);
        tipoAtributo[iterat] = classe->constant_pool[index].info.Utf8.bytes[iterat];
    }
    tipoAtributo[iterat] = '\0';
    index = attributeInfo->attribute_name_index - 1;
    nome_ref = informacao_nome(index,classe);
    fprintf(file, "\n");
    fprintf(file, "\tindex de nome: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->attribute_name_index);
    fprintf(file, "\tcomprimento do atributo: %d\n", attributeInfo->attribute_length);
    free(nome_ref);
    if (attributeInfo->attribute_length > 0){
        if (!strcmp(tipoAtributo, "ConstantValue")){

            int i;
            u2 index1;
            index = attributeInfo->info.ConstantValue.constantvalue_index - 1;
            switch (classe->constant_pool[index].tag){
            case CONSTANTLong:
                l = (u8)classe->constant_pool[index].info.Long.high_bytes<<32|classe->constant_pool[index].info.Long.low_bytes;
                fprintf(file, "\nindex-Constant_val: <%ld>, |CP={%d}|", l, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTDouble:
                l = (u8)classe->constant_pool[index].info.Double.high_bytes<<32|classe->constant_pool[index].info.Double.low_bytes;
				memcpy(&dvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u8));
                fprintf(file, "\nindex-Constant_val: <%f>, |CP={%d}|", dvalue, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTFloat:
				memcpy(&fvalue,&(classe->constant_pool[index].info.Float.bytes),sizeof(u4));
                fprintf(file, "\nindex-Constant_val: <%f>, |CP={%d}|", fvalue, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTInteger:
                i = (int32_t)classe->constant_pool[index].info.Integer.bytes;
                fprintf(file, "\nindex-Constant_val: <%d>, |CP={%d}|", i, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            case CONSTANTString:
                index1 = classe->constant_pool[index].info.String.string_index - 1;
                nome_ref = informacao_nome(index1,classe);
                fprintf(file, "\nindex-Constant_val: <%s>, |CP={%d}|", nome_ref, attributeInfo->info.ConstantValue.constantvalue_index);
                break;
            }
        }
        else if (!strcmp(tipoAtributo, "Code")){

		    fprintf(file, "\t->Outros dados\n");
            fprintf(file, "\tstack maximo: %d\n", attributeInfo->info.CodeAttribute.max_stack);
            fprintf(file, "\tmaximo locals: %d\n", attributeInfo->info.CodeAttribute.max_locals);
            fprintf(file, "\tcomprimento do codigo: %d\n", attributeInfo->info.CodeAttribute.code_length);
            fprintf(file, "\tcodigo: \n");
            for (int i = 0; i < attributeInfo->info.CodeAttribute.code_length; i++){
                Instrucao mapeamento[0xCA];
                mnemonicos(mapeamento);
                u1 opcode = attributeInfo->info.CodeAttribute.code[i], instrIndex1, instrIndex2;
                u2 instrIndex;
                int16_t offset;
                char *instrRef;
                fprintf(file, "\t\t\t%d: %s\t", i, mapeamento[opcode].mnemonico);
                int j;
                double dvalue;
                switch(mapeamento[opcode].req_cp){
                    case REQ_METHODREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        instrRef = informacoes_metodo(instrIndex - 1, classe);
                        fprintf(file, "<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_METHODREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = informacoes_metodo(instrIndex - 1, classe);
                        fprintf(file, "<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_FIELDREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << 8));
                        instrRef = informacoes_camporef(instrIndex - 1, classe);
                        fprintf(file, "<%s>, |CP={%d}|\t", instrRef, instrIndex);
                        break;
                    case REQ_JMPREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        offset = (int16_t) (instrIndex2 | (instrIndex1 << 8));
                        fprintf(file, "%d\t(%d)\t", (offset - 2) + i, offset);
                        break;
                    case REQ_LDCREF_1:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i] - 1;
                        fprintf(file, "%d\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANTInteger:
                                fprintf(file, "<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANTFloat:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                fprintf(file, "<%f>\t", fvalue);
                                break;
                            case CONSTANTLong:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                fprintf(file, "<%ld>\t", l);
                                break;
                            case CONSTANTDouble:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                fprintf(file, "<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_LDCREF_2:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex = (instrIndex2 | (instrIndex1 << sizeof(u1))) - 1;
                        fprintf(file, "%d\t", instrIndex + 1);
                        switch(classe->constant_pool[instrIndex].tag) {
                            case CONSTANTInteger:
                                fprintf(file, "<%d>\t", classe->constant_pool[instrIndex].info.Integer.bytes);
                                break;
                            case CONSTANTFloat:
                                memcpy(&fvalue, &(classe->constant_pool[instrIndex].info.Float.bytes), sizeof(u4));
                                fprintf(file, "<%f>\t", fvalue);
                                break;
                            case CONSTANTLong:
                                l = (u8) classe->constant_pool[instrIndex].info.Long.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Long.low_bytes;
                                fprintf(file, "<%ld>\t", l);
                                break;
                            case CONSTANTDouble:
                                l = (u8) classe->constant_pool[instrIndex].info.Double.high_bytes << 32;
                                l = l | classe->constant_pool[instrIndex].info.Double.low_bytes;
                                memcpy(&dvalue,&l,sizeof(u8));
                                fprintf(file, "<%f>\t", dvalue);
                                break;
                        }
                        break;
                    case REQ_ARRAYREF:
                        instrIndex = attributeInfo->info.CodeAttribute.code[++i];
                        fprintf(file, "%d\t", instrIndex);
                        switch(instrIndex) {
                            case 0:
                                fprintf(file, "(ref)\t");
                                break;
                            case 4:
                                fprintf(file, "(boolean)\t");
                                break;
                            case 5:
                                fprintf(file, "(char)\t");
                                break;
                            case 6:
                                fprintf(file, "(float)\t");
                                break;
                            case 7:
                                fprintf(file, "(double)\t");
                                break;
                            case 8:
                                fprintf(file, "(byte)\t");
                                break;
                            case 9:
                                fprintf(file, "(short)\t");
                                break;
                            case 10:
                                fprintf(file, "(int)\t");
                                break;
                            case 11:
                                fprintf(file, "(long)\t");
                                break;
                            default:
                                break;
                        }
                        break;
                    case REQ_IINCREF:
                        instrIndex1 = attributeInfo->info.CodeAttribute.code[++i];
                        instrIndex2 = attributeInfo->info.CodeAttribute.code[++i];
                        fprintf(file, "%d by %d\t", instrIndex1, instrIndex2);
                        break;
                    default:
                        for(j = 0; j < mapeamento[opcode].operandos; j++) {
                            fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.code[++i]);
                        }
                        break;
                }
                fprintf(file, "\n");
            }
            fprintf(file, "\n\texception (comprimento da tabela): %d\n", attributeInfo->info.CodeAttribute.exception_table_length);
            if(attributeInfo->info.CodeAttribute.exception_table_length > 0) {
                fprintf(file, "\tinicia PC\tEnd PC\thandler PC\ttipo de catch\n");
                for (int i = 0; i < attributeInfo->info.CodeAttribute.exception_table_length; i++){
                    fprintf(file, "%d: %d\t", i, attributeInfo->info.CodeAttribute.exception_table[i].start_pc);
                    fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.exception_table[i].end_pc);
                    fprintf(file, "%d\t", attributeInfo->info.CodeAttribute.exception_table[i].handler_pc);
                    fprintf(file, "%d\n", attributeInfo->info.CodeAttribute.exception_table[i].catch_type);
                }
            }
            fprintf(file, "\tnumero de atributos do codigo: %d\n", attributeInfo->info.CodeAttribute.attributes_count);
            for (int k = 0; k < attributeInfo->info.CodeAttribute.attributes_count; k++){
                fprintf(file, "\t{%d} ", k);
                mostra_atributo_arquivo(&(attributeInfo->info.CodeAttribute.attributes[k]), classe, file);
            }
        }
        else if (!strcmp(tipoAtributo, "exceptions")){
            fprintf(file, "\tnumero de execoes: %d\n", attributeInfo->info.Exception.number_of_exceptions);
            for (int i = 0; i < attributeInfo->info.Exception.number_of_exceptions; i++){
                index = attributeInfo->info.Exception.exception_index_table[i] - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\tindex de execoes: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.Exception.exception_index_table[i]);
                free(nome_ref);
            }
        }
        else if (!strcmp(tipoAtributo, "classes internas")){
            fprintf(file, "\tnumero de classes: %d\n", attributeInfo->info.InnerClasses.number_of_classes);
            for (int i = 0; i < attributeInfo->info.InnerClasses.number_of_classes; i++){
                free(nome_ref);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\t\tindice da classe interna: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.InnerClasses.classes[i].inner_class_info_index);
                index = attributeInfo->info.InnerClasses.classes[i].outer_class_info_index - 1;
                index = classe->constant_pool[index].info.Class.name_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\t\tindice da classe externa: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.InnerClasses.classes[i].outer_class_info_index);
                index = attributeInfo->info.InnerClasses.classes[i].inner_class_info_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\t\tindice do nome interno: <%s>, |CP={%d}|\n",nome_ref, attributeInfo->info.InnerClasses.classes[i].inner_name_index);
                fprintf(file, "\t\tflags de acesso da classe interna: %d\n",attributeInfo->info.InnerClasses.classes[i].inner_class_access_flags);
            }
        }else if (!strcmp(tipoAtributo, "SourceFile")){
            index = attributeInfo->info.Sourcefile.sourcefile_index - 1;
            nome_ref = informacao_nome(index,classe);
            fprintf(file, "\tindex do arquivo de origem: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.Sourcefile.sourcefile_index);
            free(nome_ref);
        }else if (!strcmp(tipoAtributo, "LineNumberTable")){
            fprintf(file, "\tNumero de linhas: %d\n", attributeInfo->info.LineNumberTable.line_number_table_length);
            if(attributeInfo->info.LineNumberTable.line_number_table_length > 0) {
                fprintf(file, "\n\tinicia PC\tNumero da linha\n");
                for (int i = 0; i < attributeInfo->info.LineNumberTable.line_number_table_length; i++){
                    fprintf(file, "\t\t%d: %d", i, attributeInfo->info.LineNumberTable.line_number_table[i].start_pc);
                    fprintf(file, "\t\t%d\n", attributeInfo->info.LineNumberTable.line_number_table[i].line_number);
                }
            }
        }
        else if (!strcmp(tipoAtributo, "LocalVariableTable")){
            fprintf(file, "\tcomprimento da tabela: %d\n", attributeInfo->info.LocalVariableTable.local_variable_table_length);
            for (int i = 0; i < attributeInfo->info.LocalVariableTable.local_variable_table_length; i++){
                free(nome_ref);
                fprintf(file, "\t\tinicia PC: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].start_pc);
                fprintf(file, "\t\tcomprimento: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].length);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index - 1;
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\t\tindex de nome: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.LocalVariableTable.local_variable_table[i].name_index);
                index = attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index - 1;
                free(nome_ref);
                nome_ref = informacao_nome(index,classe);
                fprintf(file, "\t\tDescriptor Index: <%s>, |CP={%d}|\n", nome_ref, attributeInfo->info.LocalVariableTable.local_variable_table[i].descriptor_index);
                fprintf(file, "\t\tIndex: %d\n",
                       attributeInfo->info.LocalVariableTable.local_variable_table[i].index);
            }
        }else{
            fprintf(file, "\tdefault: \t");
            for (int i = 0; i < attributeInfo->attribute_length; i++){
                fprintf(file, "\t%x", attributeInfo->info.Default.data[i]);
            }
            fprintf(file, "\n");
        }
    }
    //free(nome_ref);
    //free(tipoAtributo);
}

/**
*   Fun��o para mostrar um atributo espec�fico
*   @param classe   Ponteiro para o arquivo de classe a ser salvo no arquivo
*/
void mostra_atributos(ClassFile *classe){
    printf("\n");
    printf("\n");
    printf("========Atributos=========\n");
    printf("contador de atributos: %d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++){
		printf("\n~~~> ");
        printf("{%d} ", i);
        mostra_atributo(&(classe->attributes[i]), classe);
    }
}

void mostra_atributos_arquivo(ClassFile *classe, FILE *file){
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "========Atributos=========\n");
    fprintf(file, "contador de atributos: %d\n", classe->attributes_count);
    for (int i = 0; i < classe->attributes_count; i++){
		fprintf(file, "\n~~~> ");
        fprintf(file, "{%d} ", i);
        mostra_atributo_arquivo(&(classe->attributes[i]), classe, file);
    }
}

//campo

void mostra_campos(ClassFile *classe){
    printf("\n");
    printf("======Campos======\n");
    printf("contador de campos: %d\n", classe->fields_count);
    for (int i = 0; i < classe->fields_count; i++){
        int index = 0;
        char *nome_ref = NULL, *nome_ref2 = NULL;
		printf("\n~~~> ");
        printf("{%d} ", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        index = classe->fields[i].name_index - 1;
        nome_ref = informacao_nome(index, classe);
        index = classe->fields[i].descriptor_index - 1;
        nome_ref2 = informacao_nome(index, classe);
        printf("flags de acesso: %d\n", classe->fields[i].access_flags);
        printf("index de nome: <%s>, |CP={%d}|\n", nome_ref, classe->fields[i].name_index);
        printf("index de descritor: <%s>, |CP={%d}|\n", nome_ref2, classe->fields[i].descriptor_index);
        printf("numero de atributos: %d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++){
			printf("\n~~~> ");
            printf("{%d} ", j);
            for (int k = 0; k < classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                    1].info.Utf8.length; k++)
                printf("%c", classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                   1].info.Utf8.bytes[k]);
            printf("\n");
            mostra_atributo(&classe->fields[i].attributes[j], classe);
        }
    }
}

void mostra_campos_arquivo(ClassFile *classe, FILE *file){
    fprintf(file, "======Campos======\n");
    fprintf(file, "contador de campos: %d\n", classe->fields_count);
    for (int i = 0; i < classe->fields_count; i++){
        int index = 0;
        char *nome_ref = NULL, *nome_ref2 = NULL;
		fprintf(file, "\n~~~> ");
        fprintf(file, "{%d} ", i);
        for (int j = 0; j < classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->fields[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        index = classe->fields[i].name_index - 1;
        nome_ref = informacao_nome(index, classe);
        index = classe->fields[i].descriptor_index - 1;
        nome_ref2 = informacao_nome(index, classe);
        fprintf(file, "flags de acesso: %d\n", classe->fields[i].access_flags);
        fprintf(file, "index de nome: <%s>, |CP={%d}|\n", nome_ref, classe->fields[i].name_index);
        fprintf(file, "index do descritor: <%s>, |CP={%d}|\n", nome_ref2, classe->fields[i].descriptor_index);
        fprintf(file, "numero de atributos: %d\n", classe->fields[i].attributes_count);
        for (int j = 0; j < classe->fields[i].attributes_count; j++){
			fprintf(file, "\n~~~> ");
            fprintf(file, "{%d} ", j);
            for (int k = 0; k < classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index - 1].info.Utf8.length; k++)
                fprintf(file, "%c", classe->constant_pool[classe->fields[i].attributes[j].attribute_name_index -
                                                   1].info.Utf8.bytes[k]);
            fprintf(file, "\n");
            mostra_atributo_arquivo(&classe->fields[i].attributes[j], classe, file);
        }
        free(nome_ref);
        free(nome_ref2);
    }
}

void mostra_interface(cp_info val_cpinfo){
  switch (val_cpinfo.tag){
    case CONSTANTClass:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Class.tag);
      printf("Name index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.Class.name_index);
    break;
    case CONSTANTFieldref:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Fieldref.tag);
      printf("Class index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.Fieldref.class_index);
      printf("Name and type index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.Fieldref.name_and_type_index);
    break;
    case CONSTANTMethodref:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Methodref.tag);
      printf("Class index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.Methodref.class_index);
      printf("Name and type index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.Methodref.name_and_type_index);
    break;
    case CONSTANTInterfaceMethodref:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.InterfaceMethodref.tag);
      printf("Class index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.InterfaceMethodref.class_index);
      printf("Name and type index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.InterfaceMethodref.name_and_type_index);
    break;
    case CONSTANTString:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.String.tag);
      printf("String index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.String.string_index);
    break;
    case CONSTANTInteger:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Integer.tag);
      printf("Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Integer.bytes);
    break;
    case CONSTANTFloat:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Float.tag);
      printf("Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Float.bytes);
    break;
    case CONSTANTLong:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Long.tag);
      printf("High Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Long.high_bytes);
      printf("Low Bytes Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Long.low_bytes);
    break;
    case CONSTANTDouble:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Double.tag);
      printf("High Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Double.high_bytes);
      printf("Low Bytes Bytes: ");
      printf("%" PRIu32 "\n", val_cpinfo.info.Double.low_bytes);
    break;
    case CONSTANTNameAndType:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.NameAndType.tag);
      printf("Name index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.NameAndType.name_index);
      printf("Descriptor index: ");
      printf("%" PRIu16 "\n", val_cpinfo.info.NameAndType.descriptor_index);
    break;
    case CONSTANTUtf8:
      printf("Tag: ");
      printf("%" PRIu8 "\n", val_cpinfo.info.Utf8.tag);
      for(int i=0; i < val_cpinfo.info.Utf8.length; i++){
        uint8_t byte = val_cpinfo.info.Utf8.bytes[i];
        char c = byte;
        printf("%c", c);
      }
    break;
  }
}

void mostra_interface_arquivo(ClassFile *classe, FILE *file, cp_info val_cpinfo){
  switch (val_cpinfo.tag){
    case CONSTANTClass:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Class.tag);
      fprintf(file,"index nome: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.Class.name_index);
    break;
    case CONSTANTFieldref:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Fieldref.tag);
      fprintf(file,"index classe: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.Fieldref.class_index);
      fprintf(file,"index nome e tipo: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.Fieldref.name_and_type_index);
    break;
    case CONSTANTMethodref:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Methodref.tag);
      fprintf(file,"index classe: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.Methodref.class_index);
      fprintf(file,"index nome e tipo: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.Methodref.name_and_type_index);
    break;
    case CONSTANTInterfaceMethodref:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.InterfaceMethodref.tag);
      fprintf(file,"index classe: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.InterfaceMethodref.class_index);
      fprintf(file,"index nome e tipo: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.InterfaceMethodref.name_and_type_index);
    break;
    case CONSTANTString:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.String.tag);
      fprintf(file,"String index: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.String.string_index);
    break;
    case CONSTANTInteger:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Integer.tag);
      fprintf(file,"Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Integer.bytes);
    break;
    case CONSTANTFloat:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Float.tag);
      fprintf(file,"Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Float.bytes);
    break;
    case CONSTANTLong:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Long.tag);
      fprintf(file,"High Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Long.high_bytes);
      fprintf(file,"Low Bytes Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Long.low_bytes);
    break;
    case CONSTANTDouble:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Double.tag);
      fprintf(file,"High Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Double.high_bytes);
      fprintf(file,"Low Bytes Bytes: ");
      fprintf(file,"%" PRIu32 "\n", val_cpinfo.info.Double.low_bytes);
    break;
    case CONSTANTNameAndType:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.NameAndType.tag);
      fprintf(file,"Name index: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.NameAndType.name_index);
      fprintf(file,"Descriptor index: ");
      fprintf(file,"%" PRIu16 "\n", val_cpinfo.info.NameAndType.descriptor_index);
    break;
    case CONSTANTUtf8:
      fprintf(file,"Tag: ");
      fprintf(file,"%" PRIu8 "\n", val_cpinfo.info.Utf8.tag);
      for(int i=0; i < val_cpinfo.info.Utf8.length; i++){
        uint8_t byte = val_cpinfo.info.Utf8.bytes[i];
        char c = byte;
        fprintf(file,"%c", c);
      }
    break;
  }
}

void mostra_interfaces(ClassFile *classe){
    printf("\n");
    printf("\n");
    printf("====Interfaces====\n");
 	printf("numero de interfaces: %d\n", classe->interfaces_count);
    for (int i = 0; i < classe->interfaces_count; i++){
		printf("\n~~~> ");
        printf("{%d}: CP={", i);
        printf("%" PRIu16, classe->interfaces[i]);
		printf("}\n");
    }
	printf("\n");
}

void mostra_interfaces_arquivo(ClassFile * classe, FILE *file){
    fprintf(file, "\n");
    fprintf(file, "\n");
    fprintf(file, "====Interfaces====\n");
 	fprintf(file, "numero de interfaces: %d\n", classe->interfaces_count);
    for (int i = 0; i < classe->interfaces_count; i++){
		fprintf(file, "\n~~~> ");
        fprintf(file, "{%d}: CP={", i);
        fprintf(file, "%" PRIu16, classe->interfaces[i]);
		fprintf(file, "}\n");
    }
	fprintf(file, "\n");
}

void mostra_metodos(ClassFile *classe){
    printf("\n");
    printf("\n");
    printf("=======Metodos=========\n");
    printf("contador de metodos: %d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++){
        int index = 0;
        char *nome_ref = NULL;
		printf("\n~~~> ");
        printf("{%d} ", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            printf("%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        printf("\n");
        index = classe->methods[i].name_index - 1;
        nome_ref = informacao_nome(index,classe);
        printf("nome: <%s>, |CP={%d}|\n", nome_ref, classe->methods[i].name_index);
        index = classe->methods[i].descriptor_index - 1;
        nome_ref = informacao_nome(index,classe);
        printf("descritor: <%s>, |CP={%d}|\n", nome_ref, classe->methods[i].descriptor_index);
        printf("flags de acesso: 0x%x\n", classe->methods[i].access_flags);
        printf("contador dos atributos: %d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++){
			printf("\n~~~~~> ");
            printf("{{%d}} ", j);
            mostra_atributo(&(classe->methods[i].attributes[j]), classe);
        }
    }
}

void mostra_metodos_arquivo(ClassFile *classe, FILE *file){
    fprintf(file, "\n");
    fprintf(file, "=======Metodos=========\n");
    fprintf(file, "contador de metodos: \t%d\n", classe->methods_count);

    for (int i = 0; i < classe->methods_count; i++){
        int index = 0;
        char *nome_ref = NULL;
		fprintf(file, "\n~~~> ");
        fprintf(file, "{%d} ", i);
        for (int j = 0; j < classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.length; j++)
            fprintf(file, "%c", classe->constant_pool[classe->methods[i].name_index - 1].info.Utf8.bytes[j]);
        fprintf(file, "\n");
        index = classe->methods[i].name_index - 1;
        nome_ref = informacao_nome(index,classe);
        fprintf(file, "Nome: <%s>, |CP={%d}|\n", nome_ref, classe->methods[i].name_index);
        index = classe->methods[i].descriptor_index - 1;
        free(nome_ref);
        nome_ref = informacao_nome(index,classe);
        fprintf(file, "descritor: <%s>, |CP={%d}|\n", nome_ref, classe->methods[i].descriptor_index);
        fprintf(file, "flags de acesso: 0x%x\n", classe->methods[i].access_flags);
        fprintf(file, "contador de atributos: %d\n", classe->methods[i].attributes_count);
        for (int j = 0; j < classe->methods[i].attributes_count; j++){
			fprintf(file, "\n~~~~~> ");
            fprintf(file, "{{%d}} ", j);
            mostra_atributo_arquivo(&(classe->methods[i].attributes[j]), classe, file);
        }
        free(nome_ref);
    }
}

void mnemonicos(Instrucao *mapeamento){
    strcpy(mapeamento[0x00].mnemonico, "nop");
    mapeamento[0x00].operandos = 0;
    mapeamento[0x00].req_cp = 0;
    strcpy(mapeamento[0x01].mnemonico, "aconst_null");
    mapeamento[0x01].operandos = 0;
    mapeamento[0x01].req_cp = 0;
    strcpy(mapeamento[0x02].mnemonico, "iconst_m1");
    mapeamento[0x02].operandos = 0;
    mapeamento[0x02].req_cp = 0;
    strcpy(mapeamento[0x03].mnemonico, "iconst_0");
    mapeamento[0x03].operandos = 0;
    mapeamento[0x03].req_cp = 0;
    strcpy(mapeamento[0x04].mnemonico, "iconst_1");
    mapeamento[0x04].operandos = 0;
    mapeamento[0x04].req_cp = 0;
    strcpy(mapeamento[0x05].mnemonico, "iconst_2");
    mapeamento[0x05].operandos = 0;
    mapeamento[0x05].req_cp = 0;
    strcpy(mapeamento[0x06].mnemonico, "iconst_3");
    mapeamento[0x06].operandos = 0;
    mapeamento[0x06].req_cp = 0;
    strcpy(mapeamento[0x07].mnemonico, "iconst_4");
    mapeamento[0x07].operandos = 0;
    mapeamento[0x07].req_cp = 0;
    strcpy(mapeamento[0x08].mnemonico, "iconst_5");
    mapeamento[0x08].operandos = 0;
    mapeamento[0x08].req_cp = 0;
    strcpy(mapeamento[0x09].mnemonico, "lconst_0");
    mapeamento[0x09].operandos = 0;
    mapeamento[0x09].req_cp = 0;
    strcpy(mapeamento[0x0A].mnemonico, "lconst_1");
    mapeamento[0x0A].operandos = 0;
    mapeamento[0x0A].req_cp = 0;
    strcpy(mapeamento[0x0B].mnemonico, "fconst_0");
    mapeamento[0x0B].operandos = 0;
    mapeamento[0x0B].req_cp = 0;
    strcpy(mapeamento[0x0C].mnemonico, "fconst_1");
    mapeamento[0x0C].operandos = 0;
    mapeamento[0x0C].req_cp = 0;
    strcpy(mapeamento[0x0D].mnemonico, "fconst_2");
    mapeamento[0x0D].operandos = 0;
    mapeamento[0x0D].req_cp = 0;
    strcpy(mapeamento[0x0E].mnemonico, "dconst_0");
    mapeamento[0x0E].operandos = 0;
    mapeamento[0x0E].req_cp = 0;
    strcpy(mapeamento[0x0F].mnemonico, "dconst_1");
    mapeamento[0x0F].operandos = 0;
    mapeamento[0x0F].req_cp = 0;
    strcpy(mapeamento[0x10].mnemonico, "bipush");
    mapeamento[0x10].operandos = 1;
    mapeamento[0x10].req_cp = 0;
    strcpy(mapeamento[0x11].mnemonico, "sipush");
    mapeamento[0x11].operandos = 2;
    mapeamento[0x11].req_cp = 0;
    strcpy(mapeamento[0x12].mnemonico, "ldc");
    mapeamento[0x12].operandos = 1;
    mapeamento[0x12].req_cp = REQ_LDCREF_1;
    strcpy(mapeamento[0x13].mnemonico, "ldc_w");
    mapeamento[0x13].operandos = 2;
    mapeamento[0x13].req_cp = REQ_LDCREF_1;
    strcpy(mapeamento[0x14].mnemonico, "ldc2_w");
    mapeamento[0x14].operandos = 2;
    mapeamento[0x14].req_cp = REQ_LDCREF_2;
    strcpy(mapeamento[0x15].mnemonico, "iload");
    mapeamento[0x15].operandos = 1;
    mapeamento[0x15].req_cp = 0;
    strcpy(mapeamento[0x16].mnemonico, "lload");
    mapeamento[0x16].operandos = 1;
    mapeamento[0x16].req_cp = 0;
    strcpy(mapeamento[0x17].mnemonico, "fload");
    mapeamento[0x17].operandos = 1;
    mapeamento[0x17].req_cp = 0;
    strcpy(mapeamento[0x18].mnemonico, "dload");
    mapeamento[0x18].operandos = 1;
    mapeamento[0x18].req_cp = 0;
    strcpy(mapeamento[0x19].mnemonico, "aload");
    mapeamento[0x19].operandos = 1;
    mapeamento[0x19].req_cp = 0;
    strcpy(mapeamento[0x1A].mnemonico, "iload_0");
    mapeamento[0x1A].operandos = 0;
    mapeamento[0x1A].req_cp = 0;
    strcpy(mapeamento[0x1B].mnemonico, "iload_1");
    mapeamento[0x1B].operandos = 0;
    mapeamento[0x1B].req_cp = 0;
    strcpy(mapeamento[0x1C].mnemonico, "iload_2");
    mapeamento[0x1C].operandos = 0;
    mapeamento[0x1C].req_cp = 0;
    strcpy(mapeamento[0x1D].mnemonico, "iload_3");
    mapeamento[0x1D].operandos = 0;
    mapeamento[0x1D].req_cp = 0;
    strcpy(mapeamento[0x1E].mnemonico, "lload_0");
    mapeamento[0x1E].operandos = 0;
    mapeamento[0x1E].req_cp = 0;
    strcpy(mapeamento[0x1F].mnemonico, "lload_1");
    mapeamento[0x1F].operandos = 0;
    mapeamento[0x1F].req_cp = 0;
    strcpy(mapeamento[0x20].mnemonico, "lload_2");
    mapeamento[0x20].operandos = 0;
    mapeamento[0x20].req_cp = 0;
    strcpy(mapeamento[0x21].mnemonico, "lload_3");
    mapeamento[0x21].operandos = 0;
    mapeamento[0x21].req_cp = 0;
    strcpy(mapeamento[0x22].mnemonico, "fload_0");
    mapeamento[0x22].operandos = 0;
    mapeamento[0x22].req_cp = 0;
    strcpy(mapeamento[0x23].mnemonico, "fload_1");
    mapeamento[0x23].operandos = 0;
    mapeamento[0x23].req_cp = 0;
    strcpy(mapeamento[0x24].mnemonico, "fload_2");
    mapeamento[0x24].operandos = 0;
    mapeamento[0x24].req_cp = 0;
    strcpy(mapeamento[0x25].mnemonico, "fload_3");
    mapeamento[0x25].operandos = 0;
    mapeamento[0x25].req_cp = 0;
    strcpy(mapeamento[0x26].mnemonico, "dload_0");
    mapeamento[0x26].operandos = 0;
    mapeamento[0x26].req_cp = 0;
    strcpy(mapeamento[0x27].mnemonico, "dload_1");
    mapeamento[0x27].operandos = 0;
    mapeamento[0x27].req_cp = 0;
    strcpy(mapeamento[0x28].mnemonico, "dload_2");
    mapeamento[0x28].operandos = 0;
    mapeamento[0x28].req_cp = 0;
    strcpy(mapeamento[0x29].mnemonico, "dload_3");
    mapeamento[0x29].operandos = 0;
    mapeamento[0x29].req_cp = 0;
    strcpy(mapeamento[0x2A].mnemonico, "aload_0");
    mapeamento[0x2A].operandos = 0;
    mapeamento[0x2A].req_cp = 0;
    strcpy(mapeamento[0x2B].mnemonico, "aload_1");
    mapeamento[0x2B].operandos = 0;
    mapeamento[0x2B].req_cp = 0;
    strcpy(mapeamento[0x2C].mnemonico, "aload_2");
    mapeamento[0x2C].operandos = 0;
    mapeamento[0x2C].req_cp = 0;
    strcpy(mapeamento[0x2D].mnemonico, "aload_3");
    mapeamento[0x2D].operandos = 0;
    mapeamento[0x2D].req_cp = 0;
    strcpy(mapeamento[0x2E].mnemonico, "iaload");
    mapeamento[0x2E].operandos = 0;
    mapeamento[0x2E].req_cp = 0;
    strcpy(mapeamento[0x2F].mnemonico, "laload");
    mapeamento[0x2F].operandos = 0;
    mapeamento[0x2F].req_cp = 0;
    strcpy(mapeamento[0x30].mnemonico, "faload");
    mapeamento[0x30].operandos = 0;
    mapeamento[0x30].req_cp = 0;
    strcpy(mapeamento[0x31].mnemonico, "daload");
    mapeamento[0x31].operandos = 0;
    mapeamento[0x31].req_cp = 0;
    strcpy(mapeamento[0x32].mnemonico, "aaload");
    mapeamento[0x32].operandos = 0;
    mapeamento[0x32].req_cp = 0;
    strcpy(mapeamento[0x33].mnemonico, "baload");
    mapeamento[0x33].operandos = 0;
    mapeamento[0x33].req_cp = 0;
    strcpy(mapeamento[0x34].mnemonico, "caload");
    mapeamento[0x34].operandos = 0;
    mapeamento[0x34].req_cp = 0;
    strcpy(mapeamento[0x35].mnemonico, "saload");
    mapeamento[0x35].operandos = 0;
    mapeamento[0x35].req_cp = 0;
    strcpy(mapeamento[0x36].mnemonico, "istore");
    mapeamento[0x36].operandos = 1;
    mapeamento[0x36].req_cp = 0;
    strcpy(mapeamento[0x37].mnemonico, "lstore");
    mapeamento[0x37].operandos = 1;
    mapeamento[0x37].req_cp = 0;
    strcpy(mapeamento[0x38].mnemonico, "fstore");
    mapeamento[0x38].operandos = 1;
    mapeamento[0x38].req_cp = 0;
    strcpy(mapeamento[0x39].mnemonico, "dstore");
    mapeamento[0x39].operandos = 1;
    mapeamento[0x39].req_cp = 0;
    strcpy(mapeamento[0x3A].mnemonico, "astore");
    mapeamento[0x3A].operandos = 1;
    mapeamento[0x3A].req_cp = 0;
    strcpy(mapeamento[0x3B].mnemonico, "istore_0");
    mapeamento[0x3B].operandos = 0;
    mapeamento[0x3B].req_cp = 0;
    strcpy(mapeamento[0x3C].mnemonico, "istore_1");
    mapeamento[0x3C].operandos = 0;
    mapeamento[0x3C].req_cp = 0;
    strcpy(mapeamento[0x3D].mnemonico, "istore_2");
    mapeamento[0x3D].operandos = 0;
    mapeamento[0x3D].req_cp = 0;
    strcpy(mapeamento[0x3E].mnemonico, "istore_3");
    mapeamento[0x3E].operandos = 0;
    mapeamento[0x3E].req_cp = 0;
    strcpy(mapeamento[0x3F].mnemonico, "lstore_0");
    mapeamento[0x3F].operandos = 0;
    mapeamento[0x3F].req_cp = 0;
    strcpy(mapeamento[0x40].mnemonico, "lstore_1");
    mapeamento[0x40].operandos = 0;
    mapeamento[0x40].req_cp = 0;
    strcpy(mapeamento[0x41].mnemonico, "lstore_2");
    mapeamento[0x41].operandos = 0;
    mapeamento[0x41].req_cp = 0;
    strcpy(mapeamento[0x42].mnemonico, "lstore_3");
    mapeamento[0x42].operandos = 0;
    mapeamento[0x42].req_cp = 0;
    strcpy(mapeamento[0x43].mnemonico, "fstore_0");
    mapeamento[0x43].operandos = 0;
    mapeamento[0x43].req_cp = 0;
    strcpy(mapeamento[0x44].mnemonico, "fstore_1");
    mapeamento[0x44].operandos = 0;
    mapeamento[0x44].req_cp = 0;
    strcpy(mapeamento[0x45].mnemonico, "fstore_2");
    mapeamento[0x45].operandos = 0;
    mapeamento[0x45].req_cp = 0;
    strcpy(mapeamento[0x46].mnemonico, "fstore_3");
    mapeamento[0x46].operandos = 0;
    mapeamento[0x46].req_cp = 0;
    strcpy(mapeamento[0x47].mnemonico, "dstore_0");
    mapeamento[0x47].operandos = 0;
    mapeamento[0x47].req_cp = 0;
    strcpy(mapeamento[0x48].mnemonico, "dstore_1");
    mapeamento[0x48].operandos = 0;
    mapeamento[0x48].req_cp = 0;
    strcpy(mapeamento[0x49].mnemonico, "dstore_2");
    mapeamento[0x49].operandos = 0;
    mapeamento[0x49].req_cp = 0;
    strcpy(mapeamento[0x4A].mnemonico, "dstore_3");
    mapeamento[0x4A].operandos = 0;
    mapeamento[0x4A].req_cp = 0;
    strcpy(mapeamento[0x4B].mnemonico, "astore_0");
    mapeamento[0x4B].operandos = 0;
    mapeamento[0x4B].req_cp = 0;
    strcpy(mapeamento[0x4C].mnemonico, "astore_1");
    mapeamento[0x4C].operandos = 0;
    mapeamento[0x4C].req_cp = 0;
    strcpy(mapeamento[0x4D].mnemonico, "astore_2");
    mapeamento[0x4D].operandos = 0;
    mapeamento[0x4D].req_cp = 0;
    strcpy(mapeamento[0x4E].mnemonico, "astore_3");
    mapeamento[0x4E].operandos = 0;
    mapeamento[0x4E].req_cp = 0;
    strcpy(mapeamento[0x4F].mnemonico, "iastore");
    mapeamento[0x4F].operandos = 0;
    mapeamento[0x4F].req_cp = 0;
    strcpy(mapeamento[0x50].mnemonico, "lastore");
    mapeamento[0x50].operandos = 0;
    mapeamento[0x50].req_cp = 0;
    strcpy(mapeamento[0x51].mnemonico, "fastore");
    mapeamento[0x51].operandos = 0;
    mapeamento[0x51].req_cp = 0;
    strcpy(mapeamento[0x52].mnemonico, "dastore");
    mapeamento[0x52].operandos = 0;
    mapeamento[0x52].req_cp = 0;
    strcpy(mapeamento[0x53].mnemonico, "aastore");
    mapeamento[0x53].operandos = 0;
    mapeamento[0x53].req_cp = 0;
    strcpy(mapeamento[0x54].mnemonico, "bastore");
    mapeamento[0x54].operandos = 0;
    mapeamento[0x54].req_cp = 0;
    strcpy(mapeamento[0x55].mnemonico, "castore");
    mapeamento[0x55].operandos = 0;
    mapeamento[0x55].req_cp = 0;
    strcpy(mapeamento[0x56].mnemonico, "sastore");
    mapeamento[0x56].operandos = 0;
    mapeamento[0x56].req_cp = 0;
    strcpy(mapeamento[0x57].mnemonico, "pop");
    mapeamento[0x57].operandos = 0;
    mapeamento[0x57].req_cp = 0;
    strcpy(mapeamento[0x58].mnemonico, "pop2");
    mapeamento[0x58].operandos = 0;
    mapeamento[0x58].req_cp = 0;
    strcpy(mapeamento[0x59].mnemonico, "dup");
    mapeamento[0x59].operandos = 0;
    mapeamento[0x59].req_cp = 0;
    strcpy(mapeamento[0x5A].mnemonico, "dup_x1");
    mapeamento[0x5A].operandos = 0;
    mapeamento[0x5A].req_cp = 0;
    strcpy(mapeamento[0x5B].mnemonico, "dup_x2");
    mapeamento[0x5B].operandos = 0;
    mapeamento[0x5B].req_cp = 0;
    strcpy(mapeamento[0x5C].mnemonico, "dup2");
    mapeamento[0x5C].operandos = 0;
    mapeamento[0x5C].req_cp = 0;
    strcpy(mapeamento[0x5D].mnemonico, "dup2_x1");
    mapeamento[0x5D].operandos = 0;
    mapeamento[0x5D].req_cp = 0;
    strcpy(mapeamento[0x5E].mnemonico, "dup2_x2");
    mapeamento[0x5E].operandos = 0;
    mapeamento[0x5E].req_cp = 0;
    strcpy(mapeamento[0x5F].mnemonico, "swap");
    mapeamento[0x5F].operandos = 0;
    mapeamento[0x5F].req_cp = 0;
    strcpy(mapeamento[0x60].mnemonico, "iadd");
    mapeamento[0x60].operandos = 0;
    mapeamento[0x60].req_cp = 0;
    strcpy(mapeamento[0x61].mnemonico, "ladd");
    mapeamento[0x61].operandos = 0;
    mapeamento[0x61].req_cp = 0;
    strcpy(mapeamento[0x62].mnemonico, "fadd");
    mapeamento[0x62].operandos = 0;
    mapeamento[0x62].req_cp = 0;
    strcpy(mapeamento[0x63].mnemonico, "dadd");
    mapeamento[0x63].operandos = 0;
    mapeamento[0x63].req_cp = 0;
    strcpy(mapeamento[0x64].mnemonico, "isub");
    mapeamento[0x64].operandos = 0;
    mapeamento[0x64].req_cp = 0;
    strcpy(mapeamento[0x65].mnemonico, "lsub");
    mapeamento[0x65].operandos = 0;
    mapeamento[0x65].req_cp = 0;
    strcpy(mapeamento[0x66].mnemonico, "fsub");
    mapeamento[0x66].operandos = 0;
    mapeamento[0x66].req_cp = 0;
    strcpy(mapeamento[0x67].mnemonico, "dsub");
    mapeamento[0x67].operandos = 0;
    mapeamento[0x67].req_cp = 0;
    strcpy(mapeamento[0x68].mnemonico, "imul");
    mapeamento[0x68].operandos = 0;
    mapeamento[0x68].req_cp = 0;
    strcpy(mapeamento[0x69].mnemonico, "lmul");
    mapeamento[0x69].operandos = 0;
    mapeamento[0x69].req_cp = 0;
    strcpy(mapeamento[0x6A].mnemonico, "fmul");
    mapeamento[0x6A].operandos = 0;
    mapeamento[0x6A].req_cp = 0;
    strcpy(mapeamento[0x6B].mnemonico, "dmul");
    mapeamento[0x6B].operandos = 0;
    mapeamento[0x6B].req_cp = 0;
    strcpy(mapeamento[0x6C].mnemonico, "idiv");
    mapeamento[0x6C].operandos = 0;
    mapeamento[0x6C].req_cp = 0;
    strcpy(mapeamento[0x6D].mnemonico, "ldiv");
    mapeamento[0x6D].operandos = 0;
    mapeamento[0x6D].req_cp = 0;
    strcpy(mapeamento[0x6E].mnemonico, "fdiv");
    mapeamento[0x6E].operandos = 0;
    mapeamento[0x6E].req_cp = 0;
    strcpy(mapeamento[0x6F].mnemonico, "ddiv");
    mapeamento[0x6F].operandos = 0;
    mapeamento[0x6F].req_cp = 0;
    strcpy(mapeamento[0x70].mnemonico, "irem");
    mapeamento[0x70].operandos = 0;
    mapeamento[0x70].req_cp = 0;
    strcpy(mapeamento[0x71].mnemonico, "lrem");
    mapeamento[0x71].operandos = 0;
    mapeamento[0x71].req_cp = 0;
    strcpy(mapeamento[0x72].mnemonico, "frem");
    mapeamento[0x72].operandos = 0;
    mapeamento[0x72].req_cp = 0;
    strcpy(mapeamento[0x73].mnemonico, "drem");
    mapeamento[0x73].operandos = 0;
    mapeamento[0x73].req_cp = 0;
    strcpy(mapeamento[0x74].mnemonico, "ineg");
    mapeamento[0x74].operandos = 0;
    mapeamento[0x74].req_cp = 0;
    strcpy(mapeamento[0x75].mnemonico, "lneg");
    mapeamento[0x75].operandos = 0;
    mapeamento[0x75].req_cp = 0;
    strcpy(mapeamento[0x76].mnemonico, "fneg");
    mapeamento[0x76].operandos = 0;
    mapeamento[0x76].req_cp = 0;
    strcpy(mapeamento[0x77].mnemonico, "dneg");
    mapeamento[0x77].operandos = 0;
    mapeamento[0x77].req_cp = 0;
    strcpy(mapeamento[0x78].mnemonico, "ishl");
    mapeamento[0x78].operandos = 0;
    mapeamento[0x78].req_cp = 0;
    strcpy(mapeamento[0x79].mnemonico, "lshl");
    mapeamento[0x79].operandos = 0;
    mapeamento[0x79].req_cp = 0;
    strcpy(mapeamento[0x7A].mnemonico, "ishr");
    mapeamento[0x7A].operandos = 0;
    mapeamento[0x7A].req_cp = 0;
    strcpy(mapeamento[0x7B].mnemonico, "lshr");
    mapeamento[0x7B].operandos = 0;
    mapeamento[0x7B].req_cp = 0;
    strcpy(mapeamento[0x7C].mnemonico, "iushr");
    mapeamento[0x7C].operandos = 0;
    mapeamento[0x7C].req_cp = 0;
    strcpy(mapeamento[0x7D].mnemonico, "lushr");
    mapeamento[0x7D].operandos = 0;
    mapeamento[0x7D].req_cp = 0;
    strcpy(mapeamento[0x7E].mnemonico, "iand");
    mapeamento[0x7E].operandos = 0;
    mapeamento[0x7E].req_cp = 0;
    strcpy(mapeamento[0x7F].mnemonico, "land");
    mapeamento[0x7F].operandos = 0;
    mapeamento[0x7F].req_cp = 0;
    strcpy(mapeamento[0x80].mnemonico, "ior");
    mapeamento[0x80].operandos = 0;
    mapeamento[0x80].req_cp = 0;
    strcpy(mapeamento[0x81].mnemonico, "lor");
    mapeamento[0x81].operandos = 0;
    mapeamento[0x81].req_cp = 0;
    strcpy(mapeamento[0x82].mnemonico, "ixor");
    mapeamento[0x82].operandos = 0;
    mapeamento[0x82].req_cp = 0;
    strcpy(mapeamento[0x83].mnemonico, "lxor");
    mapeamento[0x83].operandos = 0;
    mapeamento[0x83].req_cp = 0;
    strcpy(mapeamento[0x84].mnemonico, "iinc");
    mapeamento[0x84].operandos = 2;
    mapeamento[0x84].req_cp = REQ_IINCREF;
    strcpy(mapeamento[0x85].mnemonico, "i2l");
    mapeamento[0x85].operandos = 0;
    mapeamento[0x85].req_cp = 0;
    strcpy(mapeamento[0x86].mnemonico, "i2f");
    mapeamento[0x86].operandos = 0;
    mapeamento[0x86].req_cp = 0;
    strcpy(mapeamento[0x87].mnemonico, "i2d");
    mapeamento[0x87].operandos = 0;
    mapeamento[0x87].req_cp = 0;
    strcpy(mapeamento[0x88].mnemonico, "l2i");
    mapeamento[0x88].operandos = 0;
    mapeamento[0x88].req_cp = 0;
    strcpy(mapeamento[0x89].mnemonico, "l2f");
    mapeamento[0x89].operandos = 0;
    mapeamento[0x89].req_cp = 0;
    strcpy(mapeamento[0x8A].mnemonico, "l2d");
    mapeamento[0x8A].operandos = 0;
    mapeamento[0x8A].req_cp = 0;
    strcpy(mapeamento[0x8B].mnemonico, "f2i");
    mapeamento[0x8B].operandos = 0;
    mapeamento[0x8B].req_cp = 0;
    strcpy(mapeamento[0x8C].mnemonico, "f2l");
    mapeamento[0x8C].operandos = 0;
    mapeamento[0x8C].req_cp = 0;
    strcpy(mapeamento[0x8D].mnemonico, "f2d");
    mapeamento[0x8D].operandos = 0;
    mapeamento[0x8D].req_cp = 0;
    strcpy(mapeamento[0x8E].mnemonico, "d2i");
    mapeamento[0x8E].operandos = 0;
    mapeamento[0x8E].req_cp = 0;
    strcpy(mapeamento[0x8F].mnemonico, "d2l");
    mapeamento[0x8F].operandos = 0;
    mapeamento[0x8F].req_cp = 0;
    strcpy(mapeamento[0x90].mnemonico, "d2f");
    mapeamento[0x90].operandos = 0;
    mapeamento[0x90].req_cp = 0;
    strcpy(mapeamento[0x91].mnemonico, "i2b");
    mapeamento[0x91].operandos = 0;
    mapeamento[0x91].req_cp = 0;
    strcpy(mapeamento[0x92].mnemonico, "i2c");
    mapeamento[0x92].operandos = 0;
    mapeamento[0x92].req_cp = 0;
    strcpy(mapeamento[0x93].mnemonico, "i2s");
    mapeamento[0x93].operandos = 0;
    mapeamento[0x93].req_cp = 0;
    strcpy(mapeamento[0x94].mnemonico, "lcmp");
    mapeamento[0x94].operandos = 0;
    mapeamento[0x94].req_cp = 0;
    strcpy(mapeamento[0x95].mnemonico, "fcmpl");
    mapeamento[0x95].operandos = 0;
    mapeamento[0x95].req_cp = 0;
    strcpy(mapeamento[0x96].mnemonico, "fcmpg");
    mapeamento[0x96].operandos = 0;
    mapeamento[0x96].req_cp = 0;
    strcpy(mapeamento[0x97].mnemonico, "dcmpl");
    mapeamento[0x97].operandos = 0;
    mapeamento[0x97].req_cp = 0;
    strcpy(mapeamento[0x98].mnemonico, "dcmpg");
    mapeamento[0x98].operandos = 0;
    mapeamento[0x98].req_cp = 0;
    strcpy(mapeamento[0x99].mnemonico, "ifeq");
    mapeamento[0x99].operandos = 2;
    mapeamento[0x99].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9A].mnemonico, "ifne");
    mapeamento[0x9A].operandos = 2;
    mapeamento[0x9A].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9B].mnemonico, "iflt");
    mapeamento[0x9B].operandos = 2;
    mapeamento[0x9B].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9C].mnemonico, "ifge");
    mapeamento[0x9C].operandos = 2;
    mapeamento[0x9C].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9D].mnemonico, "ifgt");
    mapeamento[0x9D].operandos = 2;
    mapeamento[0x9D].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9E].mnemonico, "ifle");
    mapeamento[0x9E].operandos = 2;
    mapeamento[0x9E].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0x9F].mnemonico, "if_icmpeq");
    mapeamento[0x9F].operandos = 2;
    mapeamento[0x9F].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA0].mnemonico, "if_icmpne");
    mapeamento[0xA0].operandos = 2;
    mapeamento[0xA0].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA1].mnemonico, "if_icmplt");
    mapeamento[0xA1].operandos = 2;
    mapeamento[0xA1].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA2].mnemonico, "if_icmpge");
    mapeamento[0xA2].operandos = 2;
    mapeamento[0xA2].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA3].mnemonico, "if_icmpgt");
    mapeamento[0xA3].operandos = 2;
    mapeamento[0xA3].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA4].mnemonico, "if_icmple");
    mapeamento[0xA4].operandos = 2;
    mapeamento[0xA4].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA5].mnemonico, "if_acmpeq");
    mapeamento[0xA5].operandos = 2;
    mapeamento[0xA5].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA6].mnemonico, "if_acmpne");
    mapeamento[0xA6].operandos = 2;
    mapeamento[0xA6].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA7].mnemonico, "goto");
    mapeamento[0xA7].operandos = 2;
    mapeamento[0xA7].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA8].mnemonico, "jsr");
    mapeamento[0xA8].operandos = 2;
    mapeamento[0xA8].req_cp = REQ_JMPREF;
    strcpy(mapeamento[0xA9].mnemonico, "ret");
    mapeamento[0xA9].operandos = 1;
    mapeamento[0xA9].req_cp = 0;
    strcpy(mapeamento[0xAA].mnemonico, "tableswitch");
    mapeamento[0xAA].operandos = 14;
    mapeamento[0xAA].req_cp = 0;
    strcpy(mapeamento[0xAB].mnemonico, "lookupswitch");
    mapeamento[0xAB].operandos = 10;
    mapeamento[0xAB].req_cp = 0;
    strcpy(mapeamento[0xAC].mnemonico, "ireturn");
    mapeamento[0xAC].operandos = 0;
    mapeamento[0xAC].req_cp = 0;
    strcpy(mapeamento[0xAD].mnemonico, "lreturn");
    mapeamento[0xAD].operandos = 0;
    mapeamento[0xAD].req_cp = 0;
    strcpy(mapeamento[0xAE].mnemonico, "freturn");
    mapeamento[0xAE].operandos = 0;
    mapeamento[0xAE].req_cp = 0;
    strcpy(mapeamento[0xAF].mnemonico, "dreturn");
    mapeamento[0xAF].operandos = 0;
    mapeamento[0xAF].req_cp = 0;
    strcpy(mapeamento[0xB0].mnemonico, "areturn");
    mapeamento[0xB0].operandos = 0;
    mapeamento[0xB0].req_cp = 0;
    strcpy(mapeamento[0xB1].mnemonico, "return");
    mapeamento[0xB1].operandos = 0;
    mapeamento[0xB1].req_cp = 0;
    strcpy(mapeamento[0xB2].mnemonico, "getstatic");
    mapeamento[0xB2].operandos = 2;
    mapeamento[0xB2].req_cp = REQ_FIELDREF;
    strcpy(mapeamento[0xB3].mnemonico, "putstatic");
    mapeamento[0xB3].operandos = 2;
    mapeamento[0xB3].req_cp = REQ_FIELDREF;
    strcpy(mapeamento[0xB4].mnemonico, "getfield");
    mapeamento[0xB4].operandos = 2;
    mapeamento[0xB4].req_cp = REQ_FIELDREF;
    strcpy(mapeamento[0xB5].mnemonico, "putfield");
    mapeamento[0xB5].operandos = 2;
    mapeamento[0xB5].req_cp = REQ_FIELDREF;
    strcpy(mapeamento[0xB6].mnemonico, "invokevirtual");
    mapeamento[0xB6].operandos = 2;
    mapeamento[0xB6].req_cp = REQ_METHODREF_2;
    strcpy(mapeamento[0xB7].mnemonico, "invokespecial");
    mapeamento[0xB7].operandos = 2;
    mapeamento[0xB7].req_cp = REQ_METHODREF_2;
    strcpy(mapeamento[0xB8].mnemonico, "invokestatic");
    mapeamento[0xB8].operandos = 2;
    mapeamento[0xB8].req_cp = REQ_METHODREF_2;
    strcpy(mapeamento[0xB9].mnemonico, "invokeinterface");
    mapeamento[0xB9].operandos = 4;
    mapeamento[0xB9].req_cp = REQ_METHODREF_2;
    strcpy(mapeamento[0xBB].mnemonico, "new");
    mapeamento[0xBB].operandos = 2;
    mapeamento[0xBA].req_cp = 0;
    strcpy(mapeamento[0xBC].mnemonico, "newarray");
    mapeamento[0xBC].operandos = 1;
    mapeamento[0xBC].req_cp = REQ_ARRAYREF;
    strcpy(mapeamento[0xBD].mnemonico, "anewarray");
    mapeamento[0xBD].operandos = 2;
    mapeamento[0xBD].req_cp = 0;
    strcpy(mapeamento[0xBE].mnemonico, "arraylength");
    mapeamento[0xBE].operandos = 0;
    mapeamento[0xBE].req_cp = 0;
    strcpy(mapeamento[0xBF].mnemonico, "athrow");
    mapeamento[0xBF].operandos = 0;
    mapeamento[0xBF].req_cp = 0;
    strcpy(mapeamento[0xC0].mnemonico, "check_cast");
    mapeamento[0xC0].operandos = 0;
    mapeamento[0xC0].req_cp = 0;
    strcpy(mapeamento[0xC1].mnemonico, "instance_of");
    mapeamento[0xC1].operandos = 0;
    mapeamento[0xC1].req_cp = 0;
    strcpy(mapeamento[0xC2].mnemonico, "monitor_enter");
    mapeamento[0xC2].operandos = 0;
    mapeamento[0xC2].req_cp = 0;
    strcpy(mapeamento[0xC3].mnemonico, "monitor_exit");
    mapeamento[0xC3].operandos = 0;
    mapeamento[0xC3].req_cp = 0;
    strcpy(mapeamento[0xC4].mnemonico, "wide");
    mapeamento[0xC4].operandos = 7;
    mapeamento[0xC4].req_cp = 0;
    strcpy(mapeamento[0xC5].mnemonico, "multianewarray");
    mapeamento[0xC5].operandos = 3;
    mapeamento[0xC5].req_cp = 0;
    strcpy(mapeamento[0xC6].mnemonico, "ifnull");
    mapeamento[0xC6].operandos = 2;
    mapeamento[0xC6].req_cp = 0;
    strcpy(mapeamento[0xC7].mnemonico, "ifnonnull");
    mapeamento[0xC7].operandos = 2;
    mapeamento[0xC7].req_cp = 0;
    strcpy(mapeamento[0xC8].mnemonico, "goto_w");
    mapeamento[0xC8].operandos = 4;
    mapeamento[0xC8].req_cp = 0;
    strcpy(mapeamento[0xC9].mnemonico, "jsr_w");
    mapeamento[0xC9].operandos = 4;
    mapeamento[0xC9].req_cp = 0;
}

char* informacao_nome(u2 index, ClassFile *classe){
    char *nome;
    int i;
    nome = (char *) malloc((classe->constant_pool[index].info.Utf8.length + 1) * sizeof(char));
    for (i = 0; i < classe->constant_pool[index].info.Utf8.length; i++){
        nome[i] = classe->constant_pool[index].info.Utf8.bytes[i];
    }
    nome[i] = '\0';
    return nome;
}

char* informacoes_metodo(u2 index, ClassFile *classe){
    char *class_name, *method_name, *nome;
    u2 class_index, name_and_type_index, method_index;

    class_index = classe->constant_pool[index].info.Methodref.class_index - 1;
    class_index = classe->constant_pool[class_index].info.Class.name_index - 1;
    name_and_type_index = classe->constant_pool[index].info.Methodref.name_and_type_index - 1;
    method_index = classe->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;
    class_name = informacao_nome(class_index, classe);
    method_name = informacao_nome(method_index, classe);
    nome = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));
    strcpy(nome, class_name);
    strcat(nome, ".");
    strcat(nome, method_name);

    free(class_name);
    free(method_name);

    return nome;
}

char* informacoes_camporef(u2 index, ClassFile *classe){
    char *class_name, *method_name, *nome;
    u2 class_index, name_and_type_index, method_index;

    class_index = classe->constant_pool[index].info.Fieldref.class_index - 1;
    class_index = classe->constant_pool[class_index].info.Class.name_index - 1;
    name_and_type_index = classe->constant_pool[index].info.Fieldref.name_and_type_index - 1;
    method_index = classe->constant_pool[name_and_type_index].info.NameAndType.name_index - 1;
    class_name = informacao_nome(class_index, classe);
    method_name = informacao_nome(method_index, classe);
    nome = (char *) malloc((strlen(class_name) + strlen(method_name) + 2) * sizeof(char));
    strcpy(nome, class_name);
    strcat(nome, ".");
    strcat(nome, method_name);

    free(class_name);
    free(method_name);

    return nome;
}