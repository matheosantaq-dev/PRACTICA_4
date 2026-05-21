#include "Red.h"
#include <algorithm>
#include <queue>
#include <climits>
#include "iostream"
using namespace std;
char nombreNodo(int id){
    return 'A' + id;
}
//agregar enrutador
void Red::agregarEnrutador(int id){
    if(enrutadores.find(id) == enrutadores.end()){
        enrutadores[id] = new Enrutador(id);
    }
}

//obtener enrutador
Enrutador* Red::obtenerEnrutador(int id){
    if(enrutadores.find(id) != enrutadores.end()){
        return enrutadores[id];
    }
    return nullptr;
}
Red::~Red(){
    for(auto& par : enrutadores){
        delete par.second;
    }
}
//conectar enrutadores
void Red::conectar(int id1, int id2, int costo){

    Enrutador* a = obtenerEnrutador(id1);
    Enrutador* b = obtenerEnrutador(id2);

    // validar existencia
    if(!a || !b){
        cout << "Error: uno de los enrutadores no existe\n";
        return;
    }

    // evitar conectarse a sí mismo
    if(id1 == id2){
        cout << "Error: no se puede conectar un nodo consigo mismo\n";
        return;
    }
    if(costo < 0){
        cout << "Error: el costo no puede ser negativo\n";
        return;
    }
    // verificar si ya existe la conexión
    for(auto& vec : a->obtenerVecinos()){
        if(vec.first->obtenerId() == id2){
            cout << "La conexion entre "
                 << char('A'+id1)
                 << " y "
                 << char('A'+id2)
                 << " ya existe\n";
            return;
        }
    }

    //  crear conexión
    a->nuevoVecino(b, costo);
    b->nuevoVecino(a, costo);

    cout << "Conexion creada entre "
         << char('A'+id1)
         << " y "
         << char('A'+id2)
         << " con costo " << costo << endl;

    calcularTodasLasRutas();
}
void Red::ejecutarDijkstra(Enrutador* fuente){

    // reiniciar todos
    for(auto& par : enrutadores){
        par.second->reinicio();
    }

    previo.clear();

    fuente->setDistancia(0);

    priority_queue<pair<int, Enrutador*>> colaEnrut;
    colaEnrut.push({0, fuente});

    while(!colaEnrut.empty()){
        Enrutador* actual = colaEnrut.top().second;
        colaEnrut.pop();

        if(actual->getVisitado()) continue;
        actual->setVisitado(true);

        for(auto& veci : actual->obtenerVecinos()){
            Enrutador* sig = veci.first;
            int costo = veci.second;

            int nuevaDist = actual->getDistancia() + costo;

            if(nuevaDist < sig->getDistancia()){
                sig->setDistancia(nuevaDist);

                previo[sig->obtenerId()] = actual->obtenerId();

                colaEnrut.push({-nuevaDist, sig});
            }
        }
    }
    fuente->obtenerTabla().clear();
    // guardar resultados en la tabla del enrutador fuente
    for(auto& par : enrutadores){
        int idDestino = par.first;
        Enrutador* nodo = par.second;

        fuente->obtenerTabla()[idDestino] = nodo->getDistancia();
    }
}
void Red::calcularTodasLasRutas(){
    for(auto& par : enrutadores){
        ejecutarDijkstra(par.second);
    }
}
vector<int> Red::obtenerCamino(int origen, int destino){

    vector<int> camino;

    //si no existe
    if(enrutadores.find(origen) == enrutadores.end() ||
        enrutadores.find(destino) == enrutadores.end()){
        return camino;
    }

    //ejecutar dijkstra desde origen
    ejecutarDijkstra(enrutadores[origen]);

    int actual = destino;

    //si no hay camino
    if(enrutadores[destino]->getDistancia() == INT_MAX){
        return camino;
    }

    //reconstruir camino (hacia atrás)
    while(actual != origen){
        camino.push_back(actual);
        actual = previo[actual];
    }

    camino.push_back(origen);

    //invertir vector
    reverse(camino.begin(), camino.end());

    return camino;
}

void Red::eliminarConexion(int id1, int id2){

    Enrutador* a = obtenerEnrutador(id1);
    Enrutador* b = obtenerEnrutador(id2);

    //validar existencia
    if(!a || !b){
        cout << "Error: uno de los enrutadores no existe\n";
        return;
    }

    //evitar mismo nodo
    if(id1 == id2){
        cout << "Error: no se puede eliminar una conexion consigo mismo\n";
        return;
    }

    //verificar si existe la conexion
    bool existe = false;
    for(auto& vec : a->obtenerVecinos()){
        if(vec.first->obtenerId() == id2){
            existe = true;
            break;
        }
    }

    if(!existe){
        cout << "No existe conexion entre "
             << char('A'+id1) << " y "
             << char('A'+id2) << endl;
        return;
    }

    //eliminar en A
    auto& vecA = a->obtenerVecinos();
    vecA.erase(remove_if(vecA.begin(), vecA.end(),[id2](pair<Enrutador*, int> p){
        return p.first->obtenerId() == id2;
    }), vecA.end());

    //eliminar en B
    auto& vecB = b->obtenerVecinos();
    vecB.erase(remove_if(vecB.begin(), vecB.end(),
                         [id1](pair<Enrutador*, int> p){
                             return p.first->obtenerId() == id1;
                         }), vecB.end());

    cout << "Conexion eliminada entre "
         << char('A'+id1) << " y "
         << char('A'+id2) << endl;

    calcularTodasLasRutas();
}
void Red::eliminarEnrutador(int id){

    Enrutador* borrar = obtenerEnrutador(id);

    //validar existencia
    if(!borrar){
        cout << "Error: el enrutador no existe\n";
        return;
    }

    //quitar de vecinos
    for(auto& par : enrutadores){
        auto& vec = par.second->obtenerVecinos();

        vec.erase(remove_if(vec.begin(), vec.end(),
                            [id](pair<Enrutador*, int> p){
                                return p.first->obtenerId() == id;
                            }), vec.end());
    }

    //eliminar nodo
    delete enrutadores[id];
    enrutadores.erase(id);

    cout << "Enrutador "
         << char('A'+id)
         << " eliminado correctamente\n";

    calcularTodasLasRutas();
}

void Red::mostrarTopologia(){

    cout << "\n===== TOPOLOGIA DE LA RED =====\n";

    for(auto& par : enrutadores){
        int id = par.first;
        Enrutador* e = par.second;

        cout << "Desde " << nombreNodo(id) << " se puede ir a: ";

        for(auto& vec : e->obtenerVecinos()){
            cout << nombreNodo(vec.first->obtenerId())
            << " (costo " << vec.second << ")  ";
        }

        cout << endl;
    }

    cout << "================================\n";
}
void Red::mostrarRutasConCamino(){

    cout << "\n===== MEJORES RUTAS =====\n";

    for(auto& origen : enrutadores){

        int idOrigen = origen.first;

        for(auto& destino : enrutadores){

            int idDestino = destino.first;

            if(idOrigen == idDestino) continue;

            vector<int> camino = obtenerCamino(idOrigen, idDestino);

            if(camino.empty()){
                cout << "No existe camino desde "
                     << nombreNodo(idOrigen)
                     << " hasta "
                     << nombreNodo(idDestino) << endl;
            } else {

                cout << "La mejor ruta desde "
                     << nombreNodo(idOrigen)
                     << " hasta "
                     << nombreNodo(idDestino)
                     << " es: ";

                //imprimir camino
                for(size_t i = 0; i < camino.size(); i++){
                    cout << nombreNodo(camino[i]);

                    if(i < camino.size() - 1){
                        cout << " -> ";
                    }
                }

                int costo = obtenerEnrutador(idOrigen)->obtenerTabla()[idDestino];

                cout << " con un costo total de " << costo << endl;
            }
        }
    }

    cout << "===========================\n";
}
