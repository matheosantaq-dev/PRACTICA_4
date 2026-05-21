#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <vector>
#include <map>
using namespace std;

class Enrutador {
private:
    int idEnrut; //identificador del enrutador

    //vecinos directos (enrutador, costo)
    vector<pair<Enrutador*, int>> vecinos;

    //tabla de costos (destino y costo minimo)
    map<int, int> tablaCostos;

    //variables auxiliares para dijkstra
    int distancia;
    bool visitado;

public:
    //constructor
    Enrutador(int id);

    //agregar vecino
    void nuevoVecino(Enrutador* vecino, int costo);

    //reiniciar datos para dijkstra
    void reinicio();

    //getters
    int obtenerId();
    vector<pair<Enrutador*, int>>& obtenerVecinos();
    map<int, int>& obtenerTabla();

    //setters
    void setDistancia(int d);
    int getDistancia();
    void setVisitado(bool v);
    bool getVisitado();
};

#endif
