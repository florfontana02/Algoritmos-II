#ifndef SOLUCION_TIPOS_H
#define SOLUCION_TIPOS_H

#include <string>
#include <map>
#include <list>
#include <set>
#include <utility>

using namespace std;

using Persona = int;
using IdPuesto = int;
using Producto = int;
using Nat = unsigned int;
using Stock = map<Producto, Nat>;
using Promociones = map<Producto, map<Nat, Nat>>;
using Menu = map<Producto, Nat>;
using maxCant = Nat;
using minCant = Nat;
using Gasto = Nat;
using Descuentos = map<Producto, tuple<maxCant, minCant, map<Nat, Nat>>>;

struct personaYGasto{
    Persona persona;
    Gasto gasto;
    bool operator<(const personaYGasto pyg) const{
        return this->gasto>pyg.gasto or (this->gasto == pyg.gasto and this->persona < pyg.persona);
    }
    personaYGasto(Persona p, Gasto g) : persona(p), gasto(g) {};
};

struct aed2_Puesto {
    Stock stock;
    Promociones promociones;
    Menu menu;
};
typedef map<Producto, list<Nat>> diccProductoXcantidades;

#endif //SOLUCION_TIPOS_H
