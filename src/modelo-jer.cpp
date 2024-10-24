#include "modelo-jer.h"

using namespace glm;

C::C(const float angle)
{
    unsigned ind1 = agregar(rotate(angle, vec3(0.0, 1.0, 0.0)));
    agregar(new MallaPiramide());

    matriz_rotacion = leerPtrMatriz(ind1);

}

unsigned C::leerNumParametros() const
{
    return 1;
}

void C::actualizarEstadoParametro(const unsigned iParam, const float tSec)
{   
    assert(iParam < leerNumParametros());
    *matriz_rotacion = rotate(2.0f*tSec, vec3(0.0, 1.0, 0.0));

}