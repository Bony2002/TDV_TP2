#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
#include <algorithm>
using namespace std;


class AssignmentInstance{

    public:
    AssignmentInstance(std::string filename);
    void heuristica1();
    void heuristica2();
    void busqueda1();
    void busqueda2();
    void metaheuristica();
    vector<int> ordenamiento(vector<int> distancias);
    void crear_archivo(string nombre);
    bool condiciones_swap(int i, int j);

    vector<int> correspondencia;
    vector<vector<int>> asignaciones;
    vector<vector<int>> distancias;
    vector<vector<int>> demandas;
    vector<int> capacidades;
    int n;
    int m;
    int valor_objetivo;
    bool resuelto;

};

#endif