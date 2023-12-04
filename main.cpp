#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include "ArbolConnect.cpp"
using namespace std;


void guardarEnCSV(const string& nombreArchivo, const string& datos){ //Metodo para guardar los datos de la partida en un archivo csv
    ofstream archivo(nombreArchivo, ios::app); 

    if (archivo.is_open()) {
        archivo<<datos<<"\n";
        archivo.close();
        cout<<"Datos guardados exitosamente en "<<nombreArchivo<<"\n";
    } else {
        cerr<<"Error al abrir el archivo "<<nombreArchivo<<"\n";
    }
}

void cargarPartidasDesdeCSV(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if(archivo.is_open()){
        string linea;
        while(getline(archivo, linea)){
            stringstream ss(linea);
            string columnaStr, ganador;
            getline(ss, columnaStr, ',');
            getline(ss, ganador, ',');

            // Convertir valores a tipos adecuados
            int columna = stoi(columnaStr);

            // Procesar la información como desees, por ejemplo, mostrar en la consola
            cout<<"Columna: "<< columna<< ", Ganador: "<<ganador<<"\n";
        }

        archivo.close();
    } else {
        cerr<<"Error al abrir el archivo "<<nombreArchivo<<"\n";
    }
}

int main(){
    char opcion;
    ArbolConnect juego;
    do {
        cout<<"---- Menu ----"<<endl;
        cout<<"1.Juego Nuevo"<<endl;
        cout<<"2.Cargar Partida"<<endl;
        cout<<"3.Salir del Sistema"<<endl;
        cout<<"Ingrese la opción deseada (1-3): ";
        cin>>opcion;
        switch(opcion){
            case '1': {
                char dificultad;
                cout<<"---- Modo de Dificultad ----"<<endl;
                cout<<"1.Facil"<<endl;
                cout<<"2.Intermedio"<<endl;
                cout<<"3.Dificil"<<endl;
                cout<<"Ingrese la opción de dificultad (1-3): ";
                cin>>dificultad;

                switch(dificultad){
                    case '1':
                        cout<<"Iniciando juego nuevo en modo Facil..."<<endl;
                        juego.jugar();
                        break;
                        break;

                    case '2':
                        cout<<"Iniciando juego nuevo en modo Intermedio..."<<endl;
                        juego.jugar();
                        break;

                    case '3':
                        cout<<"Iniciando juego nuevo en modo Dificil..."<<endl;
                        juego.jugar();
                        break;
                        break;

                    default:
                        cout<<"Opcion de dificultad no valida. Volviendo al menu principal."<<endl;
                        break;
                }
                break;
            }

            case '2':
                cout<<"Cargando partida..."<<endl;
                
                break;

            case '3':
                cout<<"Saliendo del sistema.Hasta luego!"<<endl;
                break;

            default:
                cout<<"Opcion no valida. Intentelo de nuevo."<<endl;
                break;
        }

    } while (opcion != '3');

    return 0;
}