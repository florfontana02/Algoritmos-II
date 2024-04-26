#include "Puesto.h"
#include "tipos.h"


Nat Puesto::PrecioItem(Producto p) const {
    return menu.at(p);    //O(log I)
}

Nat Puesto::StockItem(Producto p) const {
    return stock.at(p);     //O(log I)
}

Nat Puesto::DescuentoDe(Producto p, Nat cant) const {           //O(log I + log Cant)
    if (descuentos.find(p) == descuentos.end()) return 0;    //O(log I)
    Nat maxCant = get<0>(descuentos.at(p));               //O(log I)
    Nat minCant = get<1>(descuentos.at(p));               //O(log I)
    if(cant > maxCant){
        return (get<2>(descuentos.at(p))).at(maxCant);   //O(log I + log Cant)
    }
    if(cant < minCant){
        return 0;
    }
    return (get<2>(descuentos.at(p))).at(cant);         //O(log I + log Cant)
}

Nat Puesto::GastoPersona(Persona per) const {
    return gastos.at(per);          //O(log A)
}

Nat Puesto::nuevaVenta(Persona per, Producto p, Nat cant){    //O(log A + log I + log Cant)
    diccProductoXcantidades &venta = ventas[per];         //O(log A)
    auto itProd = venta.find(p);             //O(log I)
    if (itProd == venta.end())
        venta.insert({p, list<Nat>()});          //O(log I)
    venta.at(p).push_back(cant);                    //O(log I)
    return vender(per, p, cant);                           //O(log A + log I + log Cant)
}

Nat Puesto::nuevaVentaSinDescuento(Persona per, Producto p, Nat cant) {   //O(log A + log I + log Cant)
    diccProductoXcantidades &venta = ventas[per];    //O(log A)
    auto itProd = venta.find(p);       //O(log I)
    if (itProd == venta.end())
        venta.insert({p, list<Nat>()});    //O(log I)
    venta.at(p).push_front(cant);             //O(log I)
    return vender(per, p, cant);                     //O(log A + log I + log Cant)
}
Nat Puesto::cantPrimerVenta(Producto prod, Persona per) const {
    return ventas.at(per).at(prod).front();     //O(log A + log I)
}
bool Puesto::noHayVentas(Producto prod, Persona per) const {   //O(log A + log I)
    const diccProductoXcantidades &ventasPer = ventas.at(per);    //O(log A)
    return ventasPer.find(prod) == ventasPer.end();           //O(log I)
}
void Puesto::hackear(Producto i, Persona per) {   //O(log A + log I)
    stock[i]++;                            //O(log I)
    ventas[per][i].front()--;              //O(log A + log I)
    if (cantPrimerVenta(i, per)==0){  //O(log A + log I)
        ventas[per].erase(i);           //O(log A)
    }
    gastos[per] -= PrecioItem(i);      //O(log A + log I)
}

void Puesto::setStock(const Stock &s) {
    stock = s;
}

void Puesto::setMenu(const Menu &m) {
    menu = m;
}

void Puesto::setDescuentos(const Promociones &promos) {
    for(const auto & it : promos){
        auto itCant = (it.second).begin();
        Nat min = itCant->first;
        map<Nat, Nat> descuentosCompletos;
        auto itUltimo = --((it.second).end());
        while(itCant != itUltimo){
            Nat cantActual = itCant->first;
            Nat cantSiguiente = (++itCant)->first;
            itCant--;
            while(cantActual < cantSiguiente){
                descuentosCompletos[cantActual] = itCant->second;
                cantActual++;
            }
            ++itCant;
        }
        Nat max = itCant->first;
        descuentosCompletos[itCant->first] = itCant->second;
        descuentos[it.first] = {max, min, descuentosCompletos};
    }
}

Puesto::Puesto() {
    stock = Stock();
    menu = Menu();
    descuentos = Descuentos();
    ventas = map<Persona, diccProductoXcantidades>();
    gastos = map<Persona, Nat>();
}

Nat Puesto::vender(Persona per, Producto p, Nat cant) {   //O(log A + log I + log Cant)
    stock.at(p) -= cant;           //O(log I)
    Nat descuento = DescuentoDe(p, cant);      //O(log I + log Cant)
    Nat precio = PrecioItem(p);              //O(log I)
    Nat gasto = cant * ((precio * (100-descuento))/100);
    gastos.at(per) += gasto;    //O(log A)
    return gasto;
}

void Puesto::setPersonas(const set<Persona> &personas) {
    for (Persona p : personas){
        ventas.insert({p,diccProductoXcantidades()});
        gastos.insert({p, 0});
    }
}

bool Puesto::tieneDescuento(Producto prod, Nat cant) {  //O(log I)
    if (descuentos.find(prod) == descuentos.end()) return false;
    return (cant >= get<1>(descuentos[prod]));
}
