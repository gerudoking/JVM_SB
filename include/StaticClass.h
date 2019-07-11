#ifndef classruntime_h
#define classruntime_h

#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

#include "LeitorExibidor.h"
#include "ClassFile.h"

using namespace std;

/** @class StaticClass
 * @brief  Representação de uma classe carregada durante o runtime. O seu limite é dado por \c FRAME_MAX_SIZE
 */
class StaticClass {

public:
	/**
	 * @brief Construtor padrão.
	 * @param classFile A \c ClassFile correspondente à classe.
	 */
	StaticClass(ClassFile *classFile);

	/**
	 * @brief Destrutor padrão.
	 */
	ClassFile* getClassFile();

	/**
	 * @brief Insere um valor no field estático informado.
	 * @param value O valor que será inserido.
	 * @param fieldName O nome do field estático.
	 */
	void putValueIntoField(Value value, string fieldName);

	/**
	 * @brief Obtém o valor de um field estático.
	 * @param fieldName O valor do field que será obtido.
	 * @return Retorna o valor correspondente ao field estático.
	 */
	Value getValueFromField(string fieldName);

	/**
	 * @brief Verifica se o field informado existe.
	 * @param fieldName O nome do field que será verificado a existência.
	 * @return Retorna \c true caso o field exista, e \c false caso contrário.
	 */
	bool fieldExists(string fieldName);

	/**
	 * @brief formata arquivo saida  se o field informado existe.
	 * @param argv O nome arquivo
	 * @return Retorna nome  arquivo.
	 */
	string inicializarArquivo(char *argv[]);

private:
	/**
	 * A \c ClassFile correspondente à classe.
	 */
	ClassFile *_classFile;

	/**
	 * Os fields estáticos da classe.
	 */
	map<string, Value> _staticFields;

};

#endif /* classruntime_h */
