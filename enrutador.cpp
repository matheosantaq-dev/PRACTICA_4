#include "Enrutador.h"
#include <climits>

//constructor
Enrutador::Enrutador(int id){
    idEnrut = id;
    distancia = INT_MAX;
    visitado = false;
}

//agregar vecino
void Enrutador::nuevoVecino(Enrutador* vecino, int costo){
    vecinos.emplace_back(vecino, costo);
}

//reiniciar datos para dijkstra
void Enrutador::reinicio(){
    distancia = INT_MAX;
    visitado = false;
}

//getter id
int Enrutador::obtenerId(){
    return idEnrut;
}

//getter vecinos
vector<pair<Enrutador*, int>>& Enrutador::obtenerVecinos(){
    return vecinos;
}

//getter tabla de costos
map<int, int>& Enrutador::obtenerTabla(){
    return tablaCostos;
}



//get distancia
int Enrutador::getDistancia(){
    return distancia;
}
//get visitado
bool Enrutador::getVisitado(){
    return visitado;
}
//set visitado
void Enrutador::setVisitado(bool v){
    visitado = v;
}
//set distancia
void Enrutador::setDistancia(int d){
    distancia = d;
}
