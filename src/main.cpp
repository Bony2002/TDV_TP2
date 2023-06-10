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

void heuristica_1(vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidades){
    //Le asignamos a un negocio el deposito que le quede mas cerca
    vector<vector<int>> asig(dist.size(), vector<int>(0, {}));
    for(int j = 0; j < dist[0].size(); j++){
        int minimo = 99999;
        int depositoFinal = 0;
        for(int i = 0; i < dist.size(); i++){
            if((capacidades[i]-demandas[i][j] >= 0) && (dist[i][j] < minimo)){
                minimo = dist[i][j];
                depositoFinal = i;
            }
        }
        asig[depositoFinal].push_back(j);
        capacidades[depositoFinal] -= demandas[depositoFinal][j];
    } 

    ofstream asignaciones("asignaciones_heuristica1.txt", std::ofstream::out);
    for(int i = 0; i < asig.size(); i++){
        for(int j = 0; j < asig[0].size(); j++){
            string w = to_string(asig[i][j]);
            asignaciones << w << " ";
        }
        asignaciones<<'\n';
    }
    asignaciones.close();
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
    
    heuristica_1(dist, demandas, capacidades);

    return 0;
}