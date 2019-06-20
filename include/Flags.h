/** @file Flags.h
 * @brief ClassFlags (public, final, super, interface and abstract)
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <iostream>
#include <fstream>

#include "BasicTypes.h"

using namespace std;

const string flagNames[] = { "ACC_PUBLIC", "ACC_FINAL", "ACC_SUPER", "ACC_INTERFACE", "ACC_ABSTRACT" };

/** @fn void imprimirFlags (U2 accessFlags)
 * @brief Função que mostra as flags de acesso para os usuários
 * @param accessFlags Valor hexadecimal das flags
 */
void imprimirFlags(U2 accessFlags);

/** @fn void gravarArquivoFlags (U2 accessFlags, fstream &arquivoSaida)
 * @brief Função que gravar as flags de acesso em um arquivo
 * @param accessFlags Valor hexadecimal das flags
 * @param arquivoSaida arquivo gravado
 */
void gravarArquivoFlags(U2 accessFlags, fstream &arquivoSaida);

#endif
