#include "lollapatuza.h"
#include "tipos.h"
#include "Puesto.h"
#include "tipos2.h"

diccPuestos lollapatuza::ObtenerPuestos() const {
    return Puestos;  //O(1)
}

const set<Persona>& lollapatuza::ObtenerPersonas() const {
    return idsPersonas;   //O(1)
}

Persona lollapatuza::MayorComprador() const {
    auto it = mayorGastoXPersonas.begin();   //O(1)
    return (it->second);      //O(1)
}

Gasto lollapatuza::GastoPersona(Persona per) const {
    Gasto res = (infoPersonas.at(per)).gasto;   //O(log A)
    return res;
}

IdPuesto lollapatuza::MenorStock(Producto i) const {      //O(P * log I)
    auto it = Puestos.begin();   //O(1)
    IdPuesto candidato = it->first;            //O(1)
    Nat menor = (it->second).StockItem(i);     //O(log I)
    while(it != Puestos.end()){                   //P * O(log I) = O(P * log I)
        Nat stock = (it->second).StockItem(i);    //O(log I)
        if (stock < menor){                       //O(1)
            candidato = it->first;                //O(1)
            menor = stock;                        //O(1)
        }
        it++;                                   //O(1)
    }
    return candidato;
}

void lollapatuza::NuevaCompra(Persona per, IdPuesto p, Producto i, Nat c) {  //O(log P + log A + log I + log Cant)
    Nat descuento = Puestos[p].DescuentoDe(i, c);                                   //O(log P + log I + log Cant)
    Nat gasto;
    if (descuento == 0){
        if (puestosHackeables[per].find(i) == puestosHackeables[per].end()){    //O(log A + log I)
            puestosHackeables[per].insert({i,diccPuestoXIt()});           //O(log A + log I)
        }
        auto itPuesto = Puestos.find(p);                            //O(log P)
        puestosHackeables[per][i].insert({p, itPuesto});                //O(log A + log I + log P)
        gasto = Puestos[p].nuevaVentaSinDescuento(per, i, c);                   //O(log P + log A + log I + log Cant)
    } else {
        gasto = Puestos[p].nuevaVenta(per, i, c);                               //O(log P + log A + log I + log Cant)
    }
    Nat gastoTotal = infoPersonas.at(per).gasto + gasto;                    //O(log A)
    mayorGastoXPersonas.erase(infoPersonas.at(per).it);             //O(log A)
    personaYGasto pyg = {per, gastoTotal};
    mayorGastoXPersonas[pyg] = per;                                         //O(log A)
    auto it = mayorGastoXPersonas.find(pyg);                  //O(log A)
    infoPersonas.at(per) = (gastoXitPyG){gastoTotal, it};        //O(log A)
}

void lollapatuza::HackearItem(Producto i, Persona per) {  //O(log A + log I)
    auto hackeando1 = ((puestosHackeables[per])[i]).begin();    //O(log A + log I)
    Puesto &hackeando = (hackeando1->second)->second;
    hackeando.hackear(i, per);                                           //O(log I + log A)
    if (hackeando.noHayVentas(i, per) or hackeando.tieneDescuento(i, hackeando.cantPrimerVenta(i, per))){  //O(log A + log I)
        puestosHackeables[per][i].erase(hackeando1);            //O(log A + log I)
    }
    Nat gastoActualizado = infoPersonas.at(per).gasto - hackeando.PrecioItem(i);   //O(log A + log I)
    mayorGastoXPersonas.erase(infoPersonas.at(per).it);                     //O(log A)
    personaYGasto pyg(per, gastoActualizado);
    auto it = mayorGastoXPersonas.insert({pyg, per}).first;     //O(log A)
    gastoXitPyG gastoIt(gastoActualizado, it);
    infoPersonas.at(per) = gastoIt;                     //O(log A)
}

set<IdPuesto> lollapatuza::ObtenerIdPuestos() const {
    return idsPuestos;   //O(1)
}

lollapatuza::lollapatuza(const diccPuestos& puestos, const set<Persona>& personas) {
    auto itP = personas.begin();
    mayorGastoXPersonas = map<personaYGasto, Persona>();
    infoPersonas = map<Persona, gastoXitPyG>();
    puestosHackeables = map<Persona, map<Producto, map<IdPuesto, diccPuestos::iterator>>>();
    while (itP != personas.end()){
        auto it = mayorGastoXPersonas.insert({personaYGasto(*itP,0),*itP}).first;
        infoPersonas.insert({*itP,gastoXitPyG(0, it)});
        puestosHackeables.insert({*itP, diccProdXPuestoIT()});
        idsPersonas.insert(*itP);
        itP++;
    }
    for (pair<IdPuesto, Puesto> p : puestos) {
        this->Puestos.insert({p.first, p.second});
        idsPuestos.insert(p.first);
    }
}
