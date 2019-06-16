/*!
 * \file Instance.h
 * \brief Definição da Instance
 */
#ifndef INSTANCE_H
#define INSTANCE_H

class Instance;

#include "classeLeitorExibidor.h"
#include "StaticClass.h"
#include "OperandsStack.h"
#include "Heap.h"
#include <map>

using namespace std;

/** @class Instance
 * @brief Class instantiation.
 * @brief Lida com operações que lidam com uma instância da classe
 */
class Instance {
private:
	map<string, TypedElement*> mapLocalFields;
	StaticClass *staticClass;

public:
	/** @fn Instance(StaticClass* c)
	 * @brief Lida com operações que manipulam a instância da classe
	 * @param StaticClass Referência para a StaticClass
	 */
	Instance(StaticClass *staticClass);

	/** @fn StaticClass *getStatic()
	 * @brief Retorna referência para a classe estatica.
	 */
	StaticClass *obterStaticClass();

	/** @fn typedElement getField(string field)
	 * @brief Retorna field instanciado
	 * @param field do field.
	 * @return struct typedElement que contém informações sobre nome do tipo e valor
	 */
	TypedElement obterField(string field);

	/** @fn bool setField(string s, typedElement e)
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
