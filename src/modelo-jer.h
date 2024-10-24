#include "grafo-escena.h"

class C: public NodoGrafoEscena
{
    protected:
        glm::mat4 * matriz_rotacion = nullptr;

    public:
        C(const float angle);

        virtual unsigned leerNumParametros() const;
        virtual void actualizarEstadoParametro(const unsigned iParam, const float tSec);

};