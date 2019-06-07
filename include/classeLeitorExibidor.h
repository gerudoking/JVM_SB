/*!
 * \file classeLeitorExibidor.h
 * \brief Definição da ClasseLeitorExibidor
 */
#ifndef CLASSE_LEITOR
#define CLASSE_LEITOR

class LeitorExibidor;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string>
#include <fstream>
#include "classeTiposBasicos.h"
#include "constantPool.h"
#include "flags.h"
#include "fields.h"
#include "attributes.h"
#include "interfaces.h"
#include "methods.h"
#include "classeEstatica.h"
#include "classeInstancia.h"
#include "classeMethodArea.h"

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
 * @section DESCRIPTION
 *
 * A classe LeitorExibidor contém o necessário para ler o bytecode, exibilo e armazena-lo em memoria
 */
class LeitorExibidor {
public:
	/** @fn LeitorExibidor(char *in)
	 * Construtor de leitura
	 * @param in caminho do arquivo .class.
	 */
	LeitorExibidor(char *in);

	/** 
	 @fn LeitorExibidor(string in)
	 Construtor de leitura
	 @param in caminho do arquivo .class.
	 */
	LeitorExibidor(string in);

	/** @fn int inicializarArquivo()
	 @brief criar e inicializar arquivo
	 */
	int inicializarArquivo(char *argv[]);

	/** @fn void fecharArquivo()
	 @brief Fechar arquivo
	 */
	void fecharArquivo();

	/** @fn int carregar()
	 @brief Carrega todas as informações do class file
	 */
	int carregar();

	/** @fn bool imprimirInformacoesGerais()
	 @brief Imprime informações gerais do .class
	 */
	void imprimirInformacoesGerais();

	/** @fn bool gravarArquivoInformacoesGerais()
	 @brief Gravar informações gerais do .class em um arquivo
	 */
	void gravarArquivoInformacoesGerais();

	/** @fn bool exibir()
	 @brief Imprime todas as informações do .class
	 */
	bool exibir();

	/** @fn bool gravarArquivo()
	 @brief Gravar todas as informações do .class em um arquivo
	 */
	bool gravarArquivo();

	/** @fn bool validarExtensao ()
	 @brief Verifica se a extensão do arquivo é .class
	 */
	bool validarExtensao();

	/** @fn bool existeMain()
	 @brief Verifica se o .class possui função main
	 */
	bool existeMain();

	/** @fn method_info obterMain()
	 @brief Retorna o método main
	 */
	method_info obterMain();

	/** @fn bool existeClinit()
	 @brief Verifica se o .class tem o método <clinit>
	 */
	bool existeClinit();

	/** @fn method_info obterClinit()
	 @brief Retorna o método <clinit>
	 */
	method_info obterClinit();

	/** @fn bool verificarThisClass ()
	 @brief Verifica se a class definida é igual ao nome da classe sem extensões
	 */
	bool verificarThisClass();

	/** @fn int obterStatus()
	 @brief Retorna o status lido, informando para o método que chamou o que aconteceu
	 */
	int obterStatus();

	/** @fn cp_info *obterConstantPool()
	 @brief Retorna referencia a constant pool
	 */
	cp_info *obterConstantPool() const;

	/** @fn U2 obterTamanhoConstantPool()
	 @brief Retorna o valor do tamanho da constant pool
	 */
	U2 obterTamanhoConstantPool();

	/** @fn char *obterPath()
	 @brief Pega o caminho do arquivo .class
	 */
	char *obterPath();

	/** @fn method_info *obterMethods()
	 @brief Retorna todos os métodos
	 */
	method_info *obterMethods();

	/** @fn U2 obterMethodsCount()
	 @brief Retorna o numero de methods
	 */
	U2 obterMethodsCount();

	/** @fn U2 obterThis_class()
	 @brief Retorna um índice da constant pool que aponta para string com nome da class
	 */
	U2 obterThis_class();

	/** @fn U2 obterSuper_class()
	 @brief Retorna um índice da constant pool que aponta para string com nome da superclass
	 */
	U2 obterSuper_class();

	/** @fn U2 obterFieldsCount()
	 @brief Retorna número de fields
	 */
	U2 obterFieldsCount();

	/** @fn U2 obterFields()
	 @brief Retorna todos os fields
	 */
	field_info *obterFields();

	/** @fn U2 obterField()
	 @brief Retorna um field

	 @param nome do field desejado
	 */
	field_info *obterField(string nome);

	/** \fn U2 getMethod(ClasseInstancia* i, string name, string descriptor)
	 \brief Retorna o method info

	 \param name Nome do method desejado
	 \param descriptor Descritor do method desejado
	 */
	method_info* getMethod(string name, string descriptor);

	/** \fn U2 getClassThatHasSerachedMethod(string name, string descriptor)
	 \brief Retorna o ponteiro para o leitor do .class que contém o método encontrado em getMethod

	 \param name Nome do method desejado
	 \param descriptor Descritor do method desejado
	 */
	LeitorExibidor* getClassThatHasSerachedMethod(string name, string descriptor);

	/** @fn validacao(void)
	 * @brief Valida estrutura obrigatoria */
	int validacao(void);

private:
	/** @fn bool verificarMain()
	 @brief Encontro em qual method está a main
	 */
	bool verificarMain();

	/** @fn bool verificarClinit()
	 @brief Encontra em qual method esta a <clinit>, se existir
	 */
	bool verificarClinit();

	/** @fn string obterErro(int erro)
	 * @brief Retorna a string que contém uma mensagem de erro correspondente ao índice que recebe como parâmetro
	 * param erro Index that localizes the string that contains the error message
	 */
	string obterErro(int erro);

	int status, mainMethod, clinit;
	bool encontrouMain, encontrouClinit;
	char *fileName;
	U2 minVersion, majVersion, lengthCP;
	U2 this_class, super_class, interfacesCount, fieldsCount;
	U2 methodsCount, accessFlags, attributesCount;
	U2 *interfaces;
	cp_info *constantPool;
	field_info *fields;
	method_info *methods;
	attribute_info *attributes;
	FILE *arquivoClass;
	fstream arquivoSaida;
};

#endif
