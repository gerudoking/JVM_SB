#ifndef utils_h
#define utils_h

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "BasicTypes.h"
#include "LeitorExibidor.h"

using namespace std;

/** @class Utils
 * @brief  Representa classe utilitaria.
 */
class Utils {

public:
	/**
	 * Converte os dados de versão obtidos da struct classFile para a convenção encontrada em https://en.wikipedia.org/wiki/Java_class_file#General_layout
	 *
	 * J2SE 8 = 52
	 *
	 * J2SE 7 = 51
	 *
	 * J2SE 6.0 = 50
	 *
	 * J2SE 5.0 = 49
	 *
	 * JDK 1.4 = 48
	 *
	 * JDK 1.3 = 47
	 *
	 * JDK 1.2 = 46
	 *
	 * JDK 1.1 = 45
	 * @param *classFile Ponteiro para uma instância de struct \c ClassFile, que descreve toda a estrutura de um arquivo .class.
	 * @return O valor equivalente à versão lida em *classFile.
	 */
	static double verificarVersao(ClassFile *classFile);

	/**
	 * Verifica a igualdade entre uma string e o conteúdo de uma struct \c CONSTANT_Utf8_info.
	 * @param constant Estrutura do tipo \c CONSTANT_Utf8_info.
	 * @param *str String a se comparar.
	 * @return É retornado \c true caso a igualdade seja verdadeira, e \c false caso contrário.
	 */
	static bool compararUtf8String(CONSTANT_Utf8_info constant, const char *str);

	/**
	 * Imprime uma dada quantidade de tabs.
	 * @param out
	 * @param n Quantidade de tabs desejada.
	 */
	static void imprintTabs(FILE *out, uint8_t n);

	/**
	 * exibe uma dada quantidade de tabs.
	 * @param n Quantidade de tabs desejada.
	 */
	static void exibeTabs(uint8_t n);
	/**
	 * Converte dados do tipo stringstream para \c const \c char*.
	 * @param &ss Referência para um \c std::stringstream.
	 * @return O resultado da conversão, uma string terminada com NULL (i.e. \0).
	 */
	static const char* converterStreamToCString(const stringstream &ss);

	/**
	 * exibe uma dada quantidade de tabs.
	 * @param out
	 * @param n Quantidade de tabs desejada.
	 */
	void exibeTabs(FILE *out, uint8_t n);

	static double verificarVersaoClass(ClassFile *classFile);
	static bool verificarThisClass(string auxFilename, string auxClass);

};

#endif /* utils_h */
