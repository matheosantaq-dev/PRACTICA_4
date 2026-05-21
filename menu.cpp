#include <iostream>
#include <limits>
#include "menu.h"
using namespace std;

//menu principal
void iniciarMenu(Red& red){
    inicializarRed(red);
    red.mostrarTopologia();
    char opcion;

    do{
        cout << "\n--------------------------------------------------------------"
                "-----------"
             << endl
             << "MENU TOPOLOGIA" << endl
             << "1. Agregar enrutador" << endl
             << "2. Conectar enrutadores" << endl
             << "3. Eliminar conexion" << endl
             << "4. Eliminar enrutador" << endl
             << "5. Ver camino" << endl
             << "6. ver rutas completas" << endl
             << "7. ver topologia" << endl
             << "0. Salir" << endl
             << "--------------------------------------------------------------"
                "-----------"
             << endl
             << "Opcion: ";
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida\n";
            continue;
        }
        switch(opcion){
        case '1':{
            opcionAgregarEnrutador(red);
            break;}
        case '2':{
            opcionConectar(red);
            break;}
        case '3':{
            opcionEliminarConexion(red);
            break;}

        case '4':{
            opcionEliminarEnrutador(red);
            break;
        }
        case '5':{
            opcionVerCamino(red);
            break;
        }
        case '6':{
            red.mostrarRutasConCamino();
            break;
        }
        case '7':{
            red.mostrarTopologia();
            break;
        }
        case '0':{
            cout << "Saliendo...\n";
            break;}

        default:{
            cout << "Opcion invalida\n";
        }

        }

    } while(opcion != '0');
}

//agregar enrutador
void opcionAgregarEnrutador(Red& red){

    char nombre;

    cout << "\nIngrese el nombre del enrutador (A, B, C...): ";
    cin >> nombre;

    //validar que sea letra
    if(!isalpha(nombre)){
        cout << "Entrada invalida. Debe ser una letra.\n";
        return;
    }

    //convertir a mayuscula
    nombre = toupper(nombre);

    int id = nombre - 'A';

    //verificar si ya existe
    if(red.obtenerEnrutador(id) != nullptr){
        cout << "El enrutador " << nombre << " ya existe.\n";
        return;
    }

    red.agregarEnrutador(id);
    red.calcularTodasLasRutas();

    cout << "Enrutador " << nombre << " agregado correctamente.\n";
}

//conectar
void opcionConectar(Red& red){

    char a, b;
    int costo;

    cout << "Nodo 1 (A, B, C...): "; cin >> a;
    cout << "Nodo 2 (A, B, C...): "; cin >> b;
    cout << "Costo: "; cin >> costo;
    if(costo < 0){
        cout << "Error: el costo no puede ser negativo\n";
        return;
    }
    if(!isalpha(a) || !isalpha(b)){
        cout << "Entrada invalida\n";
        return;
    }

    a = toupper(a);
    b = toupper(b);

    int id1 = a - 'A';
    int id2 = b - 'A';

    red.conectar(id1, id2, costo);

}

void opcionEliminarConexion(Red& red){

    char a, b;

    cout << "Nodo 1 (A, B, C...): "; cin >> a;
    cout << "Nodo 2 (A, B, C...): "; cin >> b;

    if(!isalpha(a) || !isalpha(b)){
        cout << "Entrada invalida\n";
        return;
    }

    a = toupper(a);
    b = toupper(b);

    int id1 = a - 'A';
    int id2 = b - 'A';

    red.eliminarConexion(id1, id2);


}

//eliminar enrutador
void opcionEliminarEnrutador(Red& red){

    char nombre;

    cout << "Enrutador a eliminar (A, B, C...): ";
    cin >> nombre;

    if(!isalpha(nombre)){
        cout << "Entrada invalida\n";
        return;
    }

    nombre = toupper(nombre);

    int id = nombre - 'A';

    red.eliminarEnrutador(id);

}

//ver camino
void opcionVerCamino(Red& red){

    char origen, destino;

    cout << "Origen (A, B, C...): ";
    cin >> origen;

    cout << "Destino (A, B, C...): ";
    cin >> destino;

    if(!isalpha(origen) || !isalpha(destino)){
        cout << "Entrada invalida\n";
        return;
    }

    origen = toupper(origen);
    destino = toupper(destino);

    int idOrigen = origen - 'A';
    int idDestino = destino - 'A';

    vector<int> camino = red.obtenerCamino(idOrigen, idDestino);

    if(camino.empty()){
        cout << "No existe camino entre "
             << origen << " y " << destino << endl;
    } else {

        cout << "La mejor ruta desde "
             << origen << " hasta "
             << destino << " es: ";

        for(size_t i = 0; i < camino.size(); i++){
            cout << char('A' + camino[i]);

            if(i < camino.size() - 1){
                cout << " -> ";
            }
        }

        int costo = red.obtenerEnrutador(idOrigen)->obtenerTabla()[idDestino];

        cout << " con un costo de " << costo << endl;
    }
}
void inicializarRed(Red& red){
    if(red.obtenerEnrutador(0) != nullptr) return;
    //crear enrutadores
    red.agregarEnrutador(0); //A
    red.agregarEnrutador(1); //B
    red.agregarEnrutador(2); //C
    red.agregarEnrutador(3); //D

    //conexiones
    red.conectar(0,1,4);  //A-B
    red.conectar(0,3,5);  //A-D
    red.conectar(1,2,3);  //B-C
    red.conectar(2,3,2);  //C-D
    red.conectar(0,2,10); //A-C
    red.conectar(1,3,1);  //B-D

    red.calcularTodasLasRutas();
}
