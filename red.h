#ifndef RED_H
#define RED_H

#include <vector>
#include <map>
#include "Enrutador.h"
using namespace std;

class Red {
private:
    //conjunto de enrutadores (id del enrutador)
    map<int, Enrutador*> enrutadores;
    map<int, int> previo; // destino  nodo anterior
public:
    //gestion de enrutadores
    void agregarEnrutador(int id);
    void eliminarEnrutador(int id);
    ~Red();
    //gestion de conexiones
    void conectar(int id1, int id2, int costo);
    void eliminarConexion(int id1, int id2);

    //algoritmo de rutas
    void ejecutarDijkstra(Enrutador* origen);
    void calcularTodasLasRutas();

    //consultas
    Enrutador* obtenerEnrutador(int id);

    //camino entre dos nodos
    vector<int> obtenerCamino(int origen, int destino);
    void mostrarRutasConCamino();
    void mostrarTopologia();
};

#endif
