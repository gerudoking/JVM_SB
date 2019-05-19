#include "Reader.h"

Reader::Reader(){
	
}

Reader::~Reader(){

}

u1 Reader::ReadU1(FILE *file)
{
    return (getc(file));
}

u2 Reader::ReadU2(FILE *file)
{
    return (getc(file) << 8 | getc(file));
}

u4 Reader::ReadU4(FILE *file)
{
	return (getc(file) << 24 | getc(file) << 16 | getc(file) << 8 | getc(file));
}

int Reader::InsertClass(char *fullFileName, ClassFile *jvm_class)
{
    char *filePath;
    FILE *fileClass;

	fileName = GetFileName(fullFileName);
    dicName = GetDirectory(fullFileName);

    if(root)
	{
        filePath = (char *) malloc((strlen(fullFileName) + 1) * sizeof(char));
        strcpy(filePath, fullFileName);
        strcpy(dicName, "ROOT");
    }
	else
	{
        filePath = (char *) malloc((strlen(dicName) + strlen(fileName) + 1) * sizeof(char));
        strcpy(filePath, dicName);
        strcat(filePath, fileName);
    }

    if(!(fileClass = fopen(filePath, "rb")))
	{
        char *filePathFallback = (char *) malloc((strlen(filePath) + 7) * sizeof(char));
        strcpy(filePathFallback, filePath);
        strcat(filePathFallback, ".class");
        if(!(fileClass = fopen(filePathFallback, "rb")))
		{
            printf("\nERROR: FILE \"%s\" DOES NOT EXIST IN \"%s\"\n", fileName, dicName);
            free(filePath);
            free(filePathFallback);
            return FILE_ERROR;
        }
        free(filePathFallback);
    }

//--- CHAMA INSERE_CABECALHO DO INSERIDOR.C PARA VERIFICAR SE A VERSÃO DO ARQUIVO.CLASS É COMPATÍVEL.

    switch(FillHeader(fileClass, jvm_class))
	{
    	case MAGIC_ERROR:
       		printf("\nERROR: INVALID MAGIC NUMBER\n");
       		fclose(fileClass);
        	free(filePath);
        	return MAGIC_ERROR;
		
    	case VERSION_ERROR:
       		printf("\nERROR: INVALID VERSION\n");
        	fclose(fileClass);
        	free(filePath);
        	return VERSION_ERROR;
		
    	default:
        	break;
    }

    FillConstantPool(fileClass, jvm_class);
    FillClassInfo(fileClass, jvm_class);
    FillInterface(fileClass, jvm_class);
    FillFields(fileClass, jvm_class);
    FillMethods(fileClass, jvm_class);
    FillAttributes(fileClass, jvm_class);

    if(CheckFileName(jvm_class, fileName) == MATCHING_ERROR)
	{
        printf("ERROR: FILE AND CLASS NAMES DON'T MATCH\n");
        fclose(fileClass);
        free(filePath);
        return MATCHING_ERROR;
    }

    fclose(fileClass);
    free(filePath);
    return SUCCESS;
}

char* Reader::GetDirectory(char *file)
{
    int size = strlen(file);
	int bars = 0;
	int i = 0;
    char *dicName = (char *) malloc((size + 1) * sizeof(char));

    for(int i = 0; i < size; i++) 
        if(file[i] == '/')
            bars++;
    
	i = 0;
    if(bars > 0)
	{
        root = 0;
        while(bars > 0)
		{
            dicName[i] = file[i];

            if(file[i] == '/')
                bars--;

            i++;
        }
        dicName[i] = '\0';
    }
    return dicName;
}

char* Reader::GetFileName(char *file)
{
    int dicSize = strlen(dicName);
    int totalSize = strlen(file) + dicSize;
    char *fileName = (char *) malloc((totalSize + 1) * sizeof(char));

    int j = 0;
    for(int i = dicSize; i < totalSize; i++)
	{
        fileName[j] = file[i];
        j++;
    }

    fileName[j] = '\0';
    return fileName;
}

int Reader::CheckFileName(ClassFile *jvm_class, char *name)
{
    char *temp, *nameThisClass;
    char c = name[0];
    int i = 0;
	int index = jvm_class->constant_pool[jvm_class->this_class - 1].info.Class.name_index - 1;

    temp = (char *) malloc(strlen(name) * sizeof(char));
    while(c != '.')
    {
        c = name[i];
        temp[i] = name[i];
        i++;
    }
    i++;
    temp[i] = '\0';
    //Descomentar a função abaixo quando uma correspondente for implementada
    //nameThisClass = informacao_nome(index, jvm_class);
    
	if(!strcmp(temp, nameThisClass))
    {
        free(temp);
        free(nameThisClass);
        return MATCHING_ERROR;
    }

    free(temp);
    free(nameThisClass);
    return SUCCESS;
}

int Reader::FillHeader(FILE *file, ClassFile *jvm_class)
{
    jvm_class->magic = ReadU4(file);
    jvm_class->minor_version = ReadU2(file);
    jvm_class->major_version = ReadU2(file);

    if (jvm_class->magic != MAGIC_NUMBER)
        return MAGIC_ERROR;
    
	if (jvm_class->minor_version > MAJOR_VERSION || jvm_class->major_version < MINOR_VERSION)
        return VERSION_ERROR;

    return SUCCESS;
}

void Reader::FillConstantPool(FILE *file, ClassFile *jvm_class)
{
    jvm_class->constant_pool_count = ReadU2(file);
    jvm_class->constant_pool = (CpInfo *) malloc(sizeof(CpInfo) * (jvm_class->constant_pool_count - 1));
    for(int i = 0;i < (jvm_class->constant_pool_count - 1); i++)
	{ 
        jvm_class->constant_pool[i].tag = ReadU1(file); 
        switch (jvm_class->constant_pool[i].tag){ 
        case CONSTANTClass:
            jvm_class->constant_pool[i].info.Class.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Class.name_index = ReadU2(file);
            break;
        case CONSTANTFieldref:
            jvm_class->constant_pool[i].info.Fieldref.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Fieldref.class_index = ReadU2(file);
            jvm_class->constant_pool[i].info.Fieldref.name_and_type_index = ReadU2(file);
            break;
        case CONSTANTMethodref:
            jvm_class->constant_pool[i].info.Methodref.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Methodref.class_index = ReadU2(file);
            jvm_class->constant_pool[i].info.Methodref.name_and_type_index = ReadU2(file);
            break;
        case CONSTANTInterfaceMethodref:
            jvm_class->constant_pool[i].info.InterfaceMethodref.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.InterfaceMethodref.class_index = ReadU2(file);
            jvm_class->constant_pool[i].info.InterfaceMethodref.name_and_type_index = ReadU2(file);
            break;
        case CONSTANTString:
            jvm_class->constant_pool[i].info.String.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.String.string_index = ReadU2(file);
            break;
        case CONSTANTInteger:
            jvm_class->constant_pool[i].info.Integer.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Integer.bytes = ReadU4(file);
            break;
        case CONSTANTFloat:
            jvm_class->constant_pool[i].info.Float.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Float.bytes = ReadU4(file);
            break;
        case CONSTANTLong:
            jvm_class->constant_pool[i].info.Long.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Long.high_bytes = ReadU4(file);
            jvm_class->constant_pool[i].info.Long.low_bytes = ReadU4(file);
            i++;
            break;
        case CONSTANTDouble:
            jvm_class->constant_pool[i].info.Double.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Double.high_bytes = ReadU4(file);
            jvm_class->constant_pool[i].info.Double.low_bytes = ReadU4(file);
            i++;
            break;
        case CONSTANTNameAndType:
            jvm_class->constant_pool[i].info.NameAndType.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.NameAndType.name_index = ReadU2(file);
            jvm_class->constant_pool[i].info.NameAndType.descriptor_index = ReadU2(file);
            break;
        case CONSTANTUtf8:
            jvm_class->constant_pool[i].info.Utf8.tag = jvm_class->constant_pool[i].tag;
            jvm_class->constant_pool[i].info.Utf8.length = ReadU2(file);
            jvm_class->constant_pool[i].info.Utf8.bytes = (u1 *) malloc(sizeof(u1) * jvm_class->constant_pool[i].info.Utf8.length);
            for (int j = 0; j < jvm_class->constant_pool[i].info.Utf8.length; j++)
                jvm_class->constant_pool[i].info.Utf8.bytes[j] = ReadU1(file);
            break;
        }
    }
}

void Reader::FillClassInfo(FILE *file, ClassFile *jvm_class)
{
    jvm_class->access_flags = ReadU2(file);
    jvm_class->this_class = ReadU2(file);
    jvm_class->super_class = ReadU2(file);
}

void Reader::FillInterface(FILE *file, ClassFile *jvm_class)
{
    jvm_class->interfaces_count = ReadU2(file);
    jvm_class->interfaces = (u2 *) malloc(jvm_class->interfaces_count * sizeof(u2));

    for (int i=0; i < jvm_class->interfaces_count; i++)
        jvm_class->interfaces[i] = ReadU2(file);
}

void Reader::FillFields(FILE *file, ClassFile *jvm_class)
{
    jvm_class->fields_count = ReadU2(file);
    jvm_class->fields = (field_info *) malloc(jvm_class->fields_count * sizeof(field_info));

    for (int i=0; i< jvm_class->fields_count; i++)
	{
        jvm_class->fields[i].access_flags = ReadU2(file);
        jvm_class->fields[i].name_index = ReadU2(file);
        jvm_class->fields[i].descriptor_index = ReadU2(file);
        jvm_class->fields[i].attributes_count = ReadU2(file);
        jvm_class->fields[i].attributes = (attribute_info *) malloc(jvm_class->fields[i].attributes_count * sizeof(attribute_info));
        for (int j = 0; j < jvm_class->fields[i].attributes_count; j++)
            FillAttribute(file, jvm_class, &(jvm_class->fields[i].attributes[j]));
    }
}

void Reader::FillMethods(FILE *file, ClassFile *jvm_class)
{
    jvm_class->methods_count = ReadU2(file);
    jvm_class->methods = (method_info *) malloc(jvm_class->methods_count * sizeof(method_info));

    for (int i = 0; i < jvm_class->methods_count; i++){
        jvm_class->methods[i].access_flags = ReadU2(file);
        jvm_class->methods[i].name_index = ReadU2(file);
        jvm_class->methods[i].descriptor_index = ReadU2(file);
        jvm_class->methods[i].attributes_count = ReadU2(file);
        jvm_class->methods[i].attributes = (attribute_info *) malloc(jvm_class->methods[i].attributes_count * sizeof(attribute_info));
        for (int j = 0; j < jvm_class->methods[i].attributes_count; j++)
            FillAttribute(file, jvm_class, &(jvm_class->methods[i].attributes[j]));
    }
}

void Reader::FillAttributes(FILE *file, ClassFile *jvm_class)
{
    jvm_class->attributes_count = ReadU2(file);
    jvm_class->attributes = (attribute_info *) malloc(jvm_class->attributes_count * sizeof(u2));
    for (int i = 0; i < jvm_class->attributes_count; i++)
        FillAttribute(file, jvm_class, &(jvm_class->attributes[i]));
}

void Reader::FillAttribute(FILE *file, ClassFile *jvm_class, attribute_info *attribute)
{
    char *attributeType;
    u4 attribute_length;

    attribute->attribute_name_index = ReadU2(file);
    attribute->attribute_length = ReadU4(file);
    attribute_length = attribute->attribute_length;
    u2 index = attribute->attribute_name_index - 1;
    attributeType = (char *) malloc((jvm_class->constant_pool[index].info.Utf8.length+1) * sizeof(char));
    for (int i = 0; i < jvm_class->constant_pool[index].info.Utf8.length; i++)
        attributeType[i] = jvm_class->constant_pool[index].info.Utf8.bytes[i];
	attributeType[jvm_class->constant_pool[index].info.Utf8.length] = '\0';

    if (!strcmp(attributeType, "ConstantValue"))
	{
        attribute->info.ConstantValue.constantvalue_index = ReadU2(file);
        attribute->tag = AT_TAG_Constantvalue;
    }
	else if (!strcmp(attributeType, "Code"))
	{
        u4 code_length;
        attribute->info.CodeAttribute.max_stack = ReadU2(file);
        attribute->info.CodeAttribute.max_locals = ReadU2(file);
        attribute->info.CodeAttribute.code_length = ReadU4(file);
        code_length = attribute->info.CodeAttribute.code_length;
        attribute->info.CodeAttribute.code = (u1 *) malloc(code_length * sizeof(u1));
        for (int i = 0; i < code_length; i++)
            attribute->info.CodeAttribute.code[i] = ReadU1(file);
        u2 exception_table_length;
        attribute->info.CodeAttribute.exception_table_length = ReadU2(file);
        exception_table_length = attribute->info.CodeAttribute.exception_table_length;
        attribute->info.CodeAttribute.exception_table = (struct exception_tab *) malloc(exception_table_length * sizeof(struct exception_tab));
        
        for (int i = 0; i < exception_table_length; i++)
        {
            attribute->info.CodeAttribute.exception_table[i].start_pc = ReadU2(file);
            attribute->info.CodeAttribute.exception_table[i].end_pc = ReadU2(file);
            attribute->info.CodeAttribute.exception_table[i].handler_pc = ReadU2(file);
            attribute->info.CodeAttribute.exception_table[i].catch_type = ReadU2(file);
        }

        u2 attributes_count;
        attribute->info.CodeAttribute.attributes_count = ReadU2(file);
        attributes_count = attribute->info.CodeAttribute.attributes_count;
        attribute->info.CodeAttribute.attributes = (attribute_info *) malloc(attributes_count * sizeof(attribute_info));
        for (int k = 0; k < attributes_count; k++)
            FillAttribute(file, jvm_class, attribute->info.CodeAttribute.attributes);
        attribute->tag = AT_TAG_Code;
    }
    else if (!strcmp(attributeType, "Exceptions"))
    {
        u2 number_of_exceptions;
        attribute->info.Exception.number_of_exceptions = ReadU2(file);
        number_of_exceptions = attribute->info.Exception.number_of_exceptions;
        attribute->info.Exception.exception_index_table = (u2 *) malloc(number_of_exceptions * sizeof(u2));
        for (int i = 0; i < number_of_exceptions; i++)
            attribute->info.Exception.exception_index_table[i] = ReadU2(file);
        attribute->tag = AT_TAG_Exception;
    }
    else if (!strcmp(attributeType, "InnerClasses"))
    {
        u2 number_of_classes;
        attribute->info.InnerClasses.number_of_classes = ReadU2(file);
        number_of_classes = attribute->info.InnerClasses.number_of_classes;
        attribute->info.InnerClasses.classes = (struct inner_classes *) malloc(number_of_classes * sizeof(struct inner_classes));
        
        for (int i = 0; i < number_of_classes; i++)
        {
            attribute->info.InnerClasses.classes[i].inner_class_info_index = ReadU2(file);
            attribute->info.InnerClasses.classes[i].outer_class_info_index = ReadU2(file);
            attribute->info.InnerClasses.classes[i].inner_name_index = ReadU2(file);
            attribute->info.InnerClasses.classes[i].inner_class_access_flags = ReadU2(file);
        }
        attribute->tag = AT_TAG_Innerclasses;
    }
    else if (!strcmp(attributeType, "SourceFile"))
    {
        attribute->info.Sourcefile.sourcefile_index = ReadU2(file);
        attribute->tag = AT_TAG_Sourcefile;
    }
    else if (!strcmp(attributeType, "LineNumberTable"))
    {
        attribute->info.LineNumberTable.line_number_table_length = ReadU2(file);
        u2 attribute_tamanho = attribute->info.LineNumberTable.line_number_table_length;
        attribute->info.LineNumberTable.line_number_table = (struct line_number_table *) malloc(attribute_tamanho * sizeof(struct line_number_table));
        
        for (int i = 0; i < attribute_tamanho; i++)
        {
            attribute->info.LineNumberTable.line_number_table[i].start_pc = ReadU2(file);
            attribute->info.LineNumberTable.line_number_table[i].line_number = ReadU2(file);
        }
        attribute->tag = AT_TAG_Linenumbertable;
    }
    else if (!strcmp(attributeType, "LocalVariableTable"))
    {
        u2 local_variable_table_length;
        attribute->info.LocalVariableTable.local_variable_table_length = ReadU2(file);
        local_variable_table_length = attribute->info.LocalVariableTable.local_variable_table_length;
        attribute->info.LocalVariableTable.local_variable_table = (struct local_variable *) malloc(
                    local_variable_table_length * sizeof(struct local_variable *));
        
        for (int i = 0; i < local_variable_table_length; i++)
        {
            attribute->info.LocalVariableTable.local_variable_table[i].start_pc = ReadU2(file);
            attribute->info.LocalVariableTable.local_variable_table[i].length = ReadU2(file);
            attribute->info.LocalVariableTable.local_variable_table[i].name_index = ReadU2(file);
            attribute->info.LocalVariableTable.local_variable_table[i].descriptor_index = ReadU2(file);
            attribute->info.LocalVariableTable.local_variable_table[i].index = ReadU2(file);
        }
        attribute->tag = AT_TAG_Localvariabletable;
    }
    else
    {
        attribute->info.Default.data = (u1 *) malloc(attribute_length * sizeof(u1));
        for (int i = 0; i < attribute_length; i++){
            attribute->info.Default.data[i] = ReadU1(file);
        }
        attribute->tag = AT_TAG_Default;
    }

    free(attributeType);
}