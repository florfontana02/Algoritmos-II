#include "tipos.h"
#include "Puesto.h"
#ifndef TP_LOLLA_TIPOS2_H
#define TP_LOLLA_TIPOS2_H
    typedef map<personaYGasto, Persona> diccPersonaYGasto;
    typedef map<IdPuesto, Puesto> diccPuestos;
    typedef map<IdPuesto, diccPuestos::iterator> diccPuestoXIt;
    typedef map<Producto, diccPuestoXIt> diccProdXPuestoIT;
    typedef map<Persona, diccProdXPuestoIT> diccHackeables;
    struct gastoXitPyG{
        Gasto gasto;
        diccPersonaYGasto::iterator it;
        gastoXitPyG(Gasto g, diccPersonaYGasto::iterator ite): gasto(g), it(ite) {};
    };
    typedef map<Persona, gastoXitPyG> diccPersonaAitGasto;
#endif //TP_LOLLA_TIPOS2_H
