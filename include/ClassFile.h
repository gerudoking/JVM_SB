/** @file ClassFile.h
 * @brief Definição da ClassFile
 */

#ifndef CLASSFILE
#define CLASSFILE

class ClassFile;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include "BasicTypes.h"
#include "ConstantPool.h"
#include "Flags.h"
#include "Fields.h"
#include "Attributes.h"
#include "Interfaces.h"
#include "Methods.h"
#include "StaticClass.h"
#include "InstanceClass.h"
#include "MethodArea.h"

using namespace std;

/**
 * MACROS para os possíves erros encontrados
 * 
 */
#define MISSING_ARGUMENT 1
#define CANT_OPEN 2
#define INVALID_FILE 3
#define UNKNOWN_TYPE 4
#define INVALID_NAME 5
#define INVALID_EXTENSION 6
#define MISSING_MAIN 7
#define MISSING_CLINIT 8

/**
 * @class ClassFile
 * @section DESCRIPTION
 * A classe ClassFile contém os bytecodes armazenados em memoria
 */
class ClassFile {
public:
	/** @fn ClassFile(char *in)
	 * @brief Construtor que configura um objeto da classe ClassFile com o nome do arquivo passado.
	 * @param in caminho do arquivo .class.
	 */
	ClassFile(char *in);

	/** 
	 @fn ClassFile(string in)
	 @brief Construtor que configura um objeto da classe ClassFile com o nome do arquivo passado.
	 @param in caminho do arquivo .class.
	 */
	ClassFile(string in);

	/** @fn int inicializarArquivo()
	 @brief criar e inicializar arquivo
	 */
	int inicializarArquivo(char *argv[]);

	/** @fn void fecharArquivo()
	 @brief Fechar arquivo
	 */
	void fecharArquivo();

	/** @fn int carregar()
	 * @brief Carrega o class file na classe
	 * @return variavel status que indica se houve erro no programa
	 */
	int carregar();

	/** @fn bool imprimirInformacoesGerais()
	 @brief Imprime informações gerais do .class
	 @return variavel status que indica se houve erro no programa
	 */
	void imprimirInformacoesGerais();

	/** @fn bool gravarArquivoInformacoesGerais()
	 @brief Gravar informações gerais do .class em um arquivo
	 @return variavel status que indica se houve erro no programa
	 */
	void gravarArquivoInformacoesGerais();

	/** @fn bool exibir()
	 * @brief Imprime todas as informações do .class
	 * @return true ou false dependendo se a variavel status indicar que houve erro na leitura
	 */
	bool exibir();

	/** @fn bool gravarArquivo()
	 @brief Gravar todas as informações do .class em um arquivo
	 @return true ou false dependendo se a variavel status indicar que houve erro na leitura
	 */
	bool gravarArquivo();

	/** @fn bool validarExtensao ()
	 @brief Verifica se a extensão do arquivo é .class
	 @return booleano que indica se existe o .class
	 */
	bool validarExtensao();

	/** @fn bool existeMain()
	 @brief Verifica se o .class possui função main
	 @return booleano que indica se existe o metodo main
	 */
	bool existeMain();

	/** @fn method_info obterMain()
	 @brief Retorna o método main
	 @return struct method_info contendo informações sobre o método
	 */
	Method_info obterMain();

	/** @fn bool existeClinit()
	 @brief Verifica se o .class tem o método clinit
	 @return booleano que indica se existe o metodo clinit
	 */
	bool existeClinit();

	/** @fn method_info obterClinit()
	 @brief Retorna o método clinit
	 @return struct method_info contendo informações sobre o método
	 */
	Method_info obterClinit();

	/** @fn bool verificarThisClass ()
	 @brief Verifica se a class definida é igual ao nome da classe sem extensões
	 @return booleano indicando se a .class está correta
	 */
	bool verificarThisClass();

	/** @fn int obterStatus()
	 @brief Retorna o status lido, informando para o método que chamou o que aconteceu
	 @return status
	 */
	int obterStatus();

	/** @fn cp_info *obterConstantPool()
	 @brief Retorna referencia a constant pool
	 @return Retorna a array com a constant pool
	 */
	Cp_info *obterConstantPool() const;

	/** @fn U2 obterTamanhoConstantPool()
	 @brief Retorna o valor do tamanho da constant pool
	 @return Retorna a array com a constant pool
	 */
	U2 obterTamanhoConstantPool();

	/** @fn char *obterPath()
	 @brief Pega o caminho do arquivo .class
	 @return Retorna a string com o caminho total do arquivo
	 */
	char *obterPath();

	/** @fn method_info *obterMethods()
	 * @brief Retorna todos os métodos
	 * @return array do tipo method_info
	 */
	Method_info *obterMethods();

	/** @fn U2 obterMethodsCount()
	 * @brief Retorna o numero de Methods
	 * @return uint16_t indicando o numero de metodos
	 */
	U2 obterMethodsCount();

	/** @fn U2 obterThis_class()
	 * @brief Retorna um índice da constant pool que aponta para string com nome da class
	 * @return uint16_t this_class
	 */
	U2 obterThis_class();

	/** @fn U2 obterSuper_class()
	 * @brief Retorna um índice da constant pool que aponta para string com nome da superclass
	 * @return uint16_t super_class
	 */
	U2 obterSuper_class();

	/** @fn U2 obterFieldsCount()
	 * @brief Retorna número de fields
	 * @return uint16_t indicando o numero de fields
	 */
	U2 obterFieldsCount();

	/** @fn field_info obterFields()
	 * @brief Retorna a array com as fields lidas
	 * @return a array da struct field_info
	 */
	Field_info *obterFields();

	/** @fn field_info *obterField(string nome)
	 * @brief Retorna um field
	 * @param nome do field desejado que deseja retornar
	 * @return struct field_info com a informação da field passada no parâmetro
	 */
	Field_info *obterField(string nome);

	/** @fn method_info* obterMethod(string nome, string descriptor)
	 * @param nome Nome do method desejado
	 * @param descriptor Descritor do method desejado
	 */
	Method_info* obterMethod(string nome, string descriptor);

	/** @fn ClassFile* obterClassThatHasSerachedMethod(string nome, string descriptor)
	 * @brief Retorna o ponteiro para o leitor do .class que contém o método encontrado em getMethod
	 * @param nome Nome do method desejado
	 * @param descriptor Descritor do method desejado
	 * @return classe ClassFile
	 */
	ClassFile* obterClassThatHasSerachedMethod(string nome, string descriptor);

	/** @fn validacao(void)
	 * @brief Valida estrutura obrigatoria */
	int validacao(void);

	/**	@fn int verficarVersaoClass(ClassFile *classFile)
	 * Converte os dados de versão obtidos da struct classFile para a convenção encontrada em https://en.wikipedia.org/wiki/Java_class_file#General_layout
	 *
	 * Não Tratados
	 * Java SE 14 = 58
	 * Java SE 13 = 57
	 * Java SE 12 = 56
	 * Java SE 11 = 55
	 * Java SE 10 = 54
	 * Java SE 9 = 53
	 *
	 * Tratados
	 * J2SE 8 = 52
	 * J2SE 7 = 51
	 * J2SE 6.0 = 50
	 * J2SE 5.0 = 49
	 * JDK 1.4 = 48
	 * JDK 1.3 = 47
	 * JDK 1.2 = 46
	 * JDK 1.1 = 45
	 * @return O valor equivalente à versão lida em *classFile.
	 */
	int verificarVersaoClass();

	/** @fn bool validarVersaoClass(uint16_t major)
	 * Verifica a validade da versão de uma estrutura ClassFile; devendo esta ser igual ou anterior à versão explicitada em major.
	 * O campo major_version da estrutura ClassFile é usado nessa avaliação.
	 * @param major Versão a se comparar.
	 * @return Verdadeiro de a versão é no máximo major ou Falso caso contrário
	 */
	bool validarVersaoClass(uint16_t major);

private:
	/** @fn bool verificarMain()
	 @brief Encontro em qual method está a main
	 @return booleano que indica se existe o metodo main
	 */
	bool verificarMain();

	/** @fn bool verificarClinit()
	 @brief Encontra em qual method esta a clinit, se existir
	 @return booleano que indica se existe o metodo clinit
	 */
	bool verificarClinit();

	/** @fn string obterErro(int erro)
	 * @brief Retorna a string que contém uma mensagem de erro correspondente ao índice que recebe como parâmetro
	 * @param erro MACRO com o erro que foi encontrado
	 * @return string contendo informação sobre o tipo de erro encontrado
	 */
	string obterErro(int erro);

	int status, mainMethod, clinit;
	bool encontrouMain, encontrouClinit;
	char *fileName;
	U2 minVersion, majVersion, lengthCP;
	U2 this_class, super_class, interfacesCount, fieldsCount;
	U2 methodsCount, accessFlags, attributesCount;
	U2 *interfaces;
	Cp_info *constantPool;
	Field_info *fields;
	Method_info *methods;
	Attribute_info *attributes;
	FILE *arquivoClass;
	fstream arquivoSaida;
};

#endif
