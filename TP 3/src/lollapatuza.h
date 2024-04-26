//
// Created by clinux01 on 16/06/23.
//

#ifndef TESTS_TP3_LOLLAPATUZA_H
#define TESTS_TP3_LOLLAPATUZA_H

#include "tipos.h"
#include "Puesto.h"
#include "tipos2.h"

using namespace std;

class lollapatuza {
public:
    lollapatuza(const diccPuestos& puestos, const set<Persona>& personas);

    void NuevaCompra(Persona per, IdPuesto pi, Producto i, Nat c);          //O(log P + log A + log I + log Cant)
    void HackearItem(Producto i, Persona per);                              //O(log A + log I)
    Gasto GastoPersona(Persona per) const;                                  //O(log A)
    Persona MayorComprador() const;                                         //O(1)
    IdPuesto MenorStock(Producto i) const;                                  //O(P * log I)
    const set<Persona>& ObtenerPersonas() const;                            //O(1)
    diccPuestos ObtenerPuestos() const;                                     //O(1)
    set<IdPuesto> ObtenerIdPuestos() const;                                 //O(1)

private:
    diccPersonaYGasto mayorGastoXPersonas;
    diccPersonaAitGasto infoPersonas;
    diccPuestos Puestos;
    diccHackeables puestosHackeables;
    set<Persona> idsPersonas;
    set<IdPuesto> idsPuestos;
};

#endif //TESTS_TP3_LOLLAPATUZA_H
