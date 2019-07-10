#ifndef object_h
#define object_h

#include "BasicTypes.h"


/** @class Object
 * @brief n classe utilizada para todos elementos que se caracterizam como objetos, como: instância de classe e arrays.
  */
class Object { // @suppress("Class has a virtual method and non-virtual destructor")
public:
    /**
     * @brief Método utilizado para declaração do tipo de objeto.
     * @return O tipo de objeto.
     */
    virtual ObjectType objectType() = 0;
};

#endif // object_h
