/*!
 * \file InstanceClass.h
 * \brief Definição da Classe Instance
 */
#ifndef INSTANCE_H
#define INSTANCE_H

class InstanceClass;

#include "ClassFile.h"
#include "StaticClass.h"
#include "OperandsStack.h"
#include "Heap.h"
#include <map>

using namespace std;

/** @class InstanceClass
 * @brief Class instantiation.
 * @brief Lida com operações que lidam com uma instância da classe
 */
class InstanceClass {
private:
	map<string, TypedElement*> mapLocalFields;
	StaticClass *staticClass;

public:
	/** @fn InstanceClass(StaticClass* staticClass)
	 * @brief Lida com operações que manipulam a instância da classe
	 * @param staticClass Referência para a StaticClass
	 */
	InstanceClass(StaticClass* staticClass);

	/** @fn StaticClass *obterStaticClass()
	 * @brief Retorna referência para a classe estatica.
	 */
	StaticClass *obterStaticClass();

	/** @fn typedElement obterField(string field)
	 * @brief Retorna field instanciado
	 * @param field do field.
	 * @return struct typedElement que contém informações sobre nome do tipo e valor
	 */
	TypedElement obterField(string field);

	/** @fn bool atualizarField(string s, typedElement e)
	 * @brief Defina um valor para um field da Instance
	 * @param field nome do field
	 * @param typedElement novo tipo que será atribuido ao field
	 * @return booleano indicado se o field foi definido
	 */
	bool atualizarField(string field, TypedElement typedElement);

	/** @fn bool atualizarFieldFinals(string field, TypedElement typedElement)
	 * @brief Define Field como final
	 * @param field nome do field desejado
	 * @param typedElement tipo para o field
	 * @return booleano que indica se o field foi setado com o novo tipo ou não
	 */
	bool atualizarFieldFinals(string field, TypedElement typedElement);

	/** @fn void imprimirInstance()
	 * @brief Mostra todas as classes instanciadas
	 */
	void imprimirInstance();

};

#endif