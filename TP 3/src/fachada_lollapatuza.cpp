#include "fachada_lollapatuza.h"
#include "tipos.h"
diccPuestos convertirPuestos(const map<IdPuesto, aed2_Puesto> &infoPuestos, const set<Persona>& personas){
    diccPuestos puestos = diccPuestos();
    auto itPuestos = infoPuestos.begin();
    while(itPuestos != infoPuestos.end()){
        Stock stock = (itPuestos->second).stock;
        Menu menu = (itPuestos->second).menu;
        Promociones descuentos = (itPuestos->second).promociones;
        IdPuesto id = itPuestos->first;
        Puesto p = Puesto();
        p.setStock(stock);
        p.setMenu(menu);
        p.setDescuentos(descuentos);
        p.setPersonas(personas);
        puestos.insert({id, p});
        ++itPuestos;
    }
    return puestos;
}

FachadaLollapatuza::FachadaLollapatuza(const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos) :
    lolla(convertirPuestos(infoPuestos, personas), personas) {};

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    lolla.NuevaCompra(persona, idPuesto, producto, cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    lolla.HackearItem(producto, persona);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    return (lolla.GastoPersona)(persona);
}

Persona FachadaLollapatuza::mayorGastador() const {
    return lolla.MayorComprador();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   return lolla.MenorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return lolla.ObtenerPersonas();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    Nat stock = ((lolla.ObtenerPuestos())[idPuesto]).StockItem(producto);
    return stock;
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    Nat descuento = ((lolla.ObtenerPuestos())[idPuesto]).DescuentoDe(producto, cantidad);
    return descuento;
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    Gasto res = lolla.ObtenerPuestos().at(idPuesto).GastoPersona(persona);
    return res;
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    return lolla.ObtenerIdPuestos();
}