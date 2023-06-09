#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
using namespace std;

void impresora(vector<vector<int>> dist){
    for(vector<int> v : dist){
        for(int i : v){
            cout <<i<<" ";
        }
        cout << endl;
        cout<<"-----------------"<<endl; 
    }

    // for(vector<int> v : demandas){
    //     for(int i : v){
    //         cout <<i<<" ";
    //     }
    //     cout << endl; 
    //     cout<<"-----------------"<<endl; 
    // }

    // for(int i : capacidades){
    //     cout << i << " "; 
    // }
    // cout << endl; 
    // cout<<"-----------------"<<endl; 
}


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

void heuristica_1(vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidades){
    //Le asignamos a un negocio el deposito que le quede mas cerca
    vector<vector<int>> asig;
    vector<int> capaux = capacidades;
    // ofstream asignaciones("Asignaciones.csv", ofstream::out);
    for(int j = 0; j < dist[0].size(); j++){
        int minimo = 99999;
        int depositoFinal;
        for(int i = 0; i < dist.size(); i++){
            if((capaux[i]-demandas[i][j] >= 0) && (dist[i][j] < minimo)){
                int minimo = dist[i][j];
                int depositoFinal = i;
            }
        }
        asig[depositoFinal].push_back(j);
        capaux[depositoFinal] -= demandas[depositoFinal][j];
    }

    impresora(asig);

    // for(int i = 0; i < dist.size(); i++){
    //     asignaciones << "Deposito " << i << ",";
    //     for(int j = 0; j < dist[0].size(); j++){
    //         asignaciones << asig[i][j] << ",";
    //     }
    // }
    // asignaciones.close();
}


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    vector<vector<int>> dist, demandas;
    vector<int> capacidades;
    lector(filename, dist, demandas, capacidades);
    
    heuristica_1(dist, demandas, capacidades);

    return 0;
}