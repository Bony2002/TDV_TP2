#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
using namespace std;

void lector(string filename, vector<vector<int>> &dist, vector<vector<int>> &demandas, vector<int> &capacidades){
    // Guardamos las distancias de los negocios a los depositos en una matriz
    ifstream file(filename);
    string mystring;
    file>>mystring;
    int m = stoi(mystring);
    file>>mystring;
    int n = stoi(mystring);
    for(int i = 0; i < m; i++){
        vector<int> aux;
        for(int j = 0; j < n; j++){
            file>>mystring;
            int x = stoi(mystring);
            aux.push_back(x);
        }
        dist.push_back(aux);
    }

    //Guardamos las demandas de los negocios en una matriz
    for(int i = 0; i < m; i++){
        vector<int> aux;
        for(int j = 0; j <n; j++){
            file>>mystring;
            int y = stoi(mystring);
            aux.push_back(y);
        }
        demandas.push_back(aux);
    }

    //Guardamos las capacidades totales de los depositos
    for(int i = 0; i < m; i++){
        file>>mystring;
        int z = stoi(mystring);
        capacidades.push_back(z);
    }
}

void minimizacion_distancia(){
    return;
}

int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    vector<vector<int>> dist, demandas;
    vector<int> capacidades;
    lector(filename, dist, demandas, capacidades);
    for(vector<int> v : dist){
        for(int i : v){
            cout <<i<<" ";
        }
        cout << endl;
        cout<<"-----------------"<<endl; 
    }

    for(vector<int> v : demandas){
        for(int i : v){
            cout <<i<<" ";
        }
        cout << endl; 
        cout<<"-----------------"<<endl; 
    }

    for(int i : capacidades){
        cout << i << " "; 
    }
    cout << endl; 
    cout<<"-----------------"<<endl; 

    return 0;
}