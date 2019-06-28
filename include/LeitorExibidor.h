#ifndef LEITOREXIBIDOR_H_
#define LEITOREXIBIDOR_H_

#include "ClassFile.h"

/**
 * @class LeitorExibidor
 * A classe LeitorExibidor contém o necessário para ler o bytecode, exibilo e armazena-lo em memoria
 */
class LeitorExibidor {

public:
	ClassFile *classFile;

	/**
	 @fn LeitorExibidor(ClassFile *pClass)
	 @brief Construtor que configura um objeto da classe LeitorExibidor com o nome do arquivo passado.
	 @param pClass ponteiro da class.
	 */
	LeitorExibidor(ClassFile *pClass);

	/**
	 @fn LeitorExibidor()
	 @brief Construtor padrao
	 */
	LeitorExibidor();

};

#endif
