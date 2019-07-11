#ifndef classinstance_h
#define classinstance_h

#include "Object.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

#include "BasicTypes.h"
#include "StaticClass.h"

using namespace std;

/**  @class InstanceClass
 * @brief  Lida com operações que lidam com uma instância da classe
 */
class InstanceClass: public Object {

public:
	/**
	 * @brief Construtor padrão.
	 * @param classRuntime A classe correspondente ao objeto.
	 */
	InstanceClass(StaticClass *classRuntime);

	/**
	 * @brief Destrutor padrão.
	 */
	~InstanceClass(); // @suppress("Class has a virtual method and non-virtual destructor")

	/**
	 * @brief Método utilizado para declaração do tipo de objeto.
	 * @return O tipo de objeto.
	 */
	ObjectType objectType();

	/**
	 * @brief Obtém a classe correspondente ao objeto.
	 * @return Retorna a classe do objeto.
	 */
	StaticClass* getClassRuntime();

	/**
	 * @brief Adiciona um valor no field de índice informado.
	 *
	 * Caso o índice do field (i.e. não exista na CP da classe atual seja inválido), um erro será emitido.
	 * @param value O valor que será inserido no field.
	 * @param fieldName O nome do field que será alterado.
	 */
	void putValueIntoField(Value value, string fieldName);

	/**
	 * @brief Obtém o valor contido em um field informado.
	 *
	 * Caso o nome do field seja inválido, um erro será emitido.
	 * @param fieldName O índice do field.
	 * @return O valor correspondente ao field.
	 */
	Value getValueFromField(string fieldName);

	/**
	 * @brief Verifica se existe um field com o nome dado.
	 * @param fieldName O nome do field.
	 * @return Retorna \c true caso o field existir, e \c false caso contrário.
	 */
	bool fieldExists(string fieldName);

private:
	/**
	 * Armazena a classe correspondente ao objeto.
	 */
	StaticClass *_classRuntime;

	/**
	 * Armazena os fields do objeto (de instância).
	 */
	map<string, Value> _fields;

};

#endif /* classinstance_h */
