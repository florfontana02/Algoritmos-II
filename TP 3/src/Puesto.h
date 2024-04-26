#ifndef TESTS_TP3_PUESTO_H
#define TESTS_TP3_PUESTO_H

#include "tipos.h"

class Puesto {
public:
    Puesto();

    Nat StockItem(Producto) const;                          //O(log I)
    Nat PrecioItem(Producto) const;                         //O(log I)
    Nat DescuentoDe(Producto, Nat) const;                   //O(log I + log Cant)
    Nat GastoPersona(Persona) const;                        //O(log A)
    Nat nuevaVenta(Persona, Producto, Nat);                 //O(log A + log I + log Cant)
    Nat nuevaVentaSinDescuento(Persona, Producto, Nat);     //O(log A + log I + log Cant)
    Nat cantPrimerVenta(Producto prod, Persona per) const;  //O(log A + log I)
    bool tieneDescuento(Producto, Nat);                     //O(log I)
    void hackear(Producto i, Persona per);                  //O(log A + log I)
    void setStock(const Stock&);
    void setMenu(const Menu&);
    void setDescuentos(const Promociones&);
    void setPersonas(const set<Persona>&);
    bool noHayVentas(Producto, Persona) const;              //O(log A + log I)
private:
    Stock stock;
    Menu menu;
    Descuentos descuentos;
    map<Persona, diccProductoXcantidades> ventas;
    map<Persona, Nat> gastos;
    Nat vender(Persona per, Producto p, Nat cant);          //O(log A + log I + log Cant)
};

#endif //TESTS_TP3_PUESTO_H
