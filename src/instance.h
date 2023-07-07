#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <chrono>
using namespace std;


class AssignmentInstance{

    public:
    AssignmentInstance(std::string filename);
    void heuristica1();
    void heuristica2();
    void busqueda1();
    void busqueda2();
    void metaheuristica(bool i);
    vector<int> ordenamiento(vector<double> distancias);
    void crear_archivo(string nombre);
    bool condiciones_swap(int i, int j);

    vector<int> correspondencia;
    vector<vector<int>> asignaciones;
    vector<vector<double>> distancias;
    vector<vector<int>> demandas;
    vector<int> capacidades;
    vector<int> tiempo;
    int n;
    int m;
    double valor_objetivo;
    double dist_max;

};

#endif