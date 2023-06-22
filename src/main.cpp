#include "instance.h"
using namespace std;



// void lector(string filename, vector<vector<int>> &dist, vector<vector<int>> &demandas, vector<int> &capacidades){
//     // Guardamos las distancias de los negocios a los depositos en una matriz
//     ifstream file(filename);
//     string mystring;
//     file>>mystring;
//     int m = stoi(mystring);
//     file>>mystring;
//     int n = stoi(mystring);
//     for(int i = 0; i < m; i++){
//         vector<int> aux;
//         for(int j = 0; j < n; j++){
//             file>>mystring;
//             int x = stoi(mystring);
//             aux.push_back(x);
//         }
//         dist.push_back(aux);
//     }

//     //Guardamos las demandas de los negocios en una matriz
//     for(int i = 0; i < m; i++){
//         vector<int> aux;
//         for(int j = 0; j <n; j++){
//             file>>mystring;
//             int y = stoi(mystring);
//             aux.push_back(y);
//         }
//         demandas.push_back(aux);
//     }

//     //Guardamos las capacidades totales de los depositos
//     for(int i = 0; i < m; i++){
//         file>>mystring;
//         int z = stoi(mystring);
//         capacidades.push_back(z);
//     }

//     //imprimimos la información
//     cout<<"Distancias"<<endl;
//     for(vector<int> v : dist){
//         for(int i : v){
//             cout <<i<<" ";
//         }
//         cout << endl;
//         cout<<"-----------------"<<endl; 
//     }
//     cout<<"Demandas"<<endl;
//     for(vector<int> v : demandas){
//         for(int i : v){
//             cout <<i<<" ";
//         }
//         cout << endl; 
//         cout<<"-----------------"<<endl; 
//     }
//     cout<<"Capacidades"<<endl;
//     for(int i : capacidades){
//         cout << i << " "; 
//     }
//     cout << endl; 
//     cout<<"-----------------"<<endl; 
    
// }

// void heuristica_1(vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidades){
//     //Le asignamos a un negocio el deposito que le quede mas cerca
//     // HAY QUE HACER: Ordenar a los negocios de menor a mayor por la distancia que tengan con su deposito mas cercano
//     vector<vector<int>> asig(dist.size(), vector<int>(0, {}));
//     for(int j = 0; j < dist[0].size(); j++){
//         int minimo = 99999;
//         int depositoFinal = 0;
//         for(int i = 0; i < dist.size(); i++){
//             if((capacidades[i]-demandas[i][j] >= 0) && (dist[i][j] < minimo)){
//                 minimo = dist[i][j];
//                 depositoFinal = i;
//             }
//         }
//         asig[depositoFinal].push_back(j);
//         capacidades[depositoFinal] -= demandas[depositoFinal][j];
//     } 

//     ofstream asignaciones("asignaciones_heuristica1.txt", std::ofstream::out);
//     for(int i = 0; i < asig.size(); i++){
//         for(int j = 0; j < asig[i].size(); j++){
//             string w = to_string(asig[i][j]);
//             asignaciones << w << " ";
//         }
//         asignaciones<<'\n';
//     }
//     asignaciones.close();
//     return;
// }

// void heuristica_2(vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidades){
//     //Le asignamos a  el cada deposito loo negocios que le queden mas cerca
//     vector<vector<int>> asig(dist.size(), vector<int>(0, {}));
//     vector<int>no_disponibles={};
//     for(int j = 0; j < dist.size(); j++){
//         int suma = 0;
//         //calculas la distancia promedio de cada deposito
//         for(int i = 0; i<dist[0].size(); i++){
//             suma += dist[j][i];
//         }
//         int prom = suma/dist[0].size();
//         for(int i = 0; i < dist[0].size(); i++){
//             if((capacidades[j]-demandas[j][i] >= 0) && (dist[j][i] <= prom) && find(no_disponibles.begin(), no_disponibles.end(), i)==no_disponibles.end()){ //agregas el nogocio al deposito si esta mas cerca que el promedio
//                 asig[j].push_back(i);
//                 capacidades[j] -= demandas[j][i];
//                 no_disponibles.push_back(i);
//             }
//         }
//     }

//     ofstream asignaciones("asignaciones_heuristica2.txt", std::ofstream::out);
//     for(int i = 0; i < asig.size(); i++){
//         for(int j = 0; j < asig[i].size(); j++){
//             string w = to_string(asig[i][j]);
//             asignaciones << w << " ";
//         }
//         asignaciones<<'\n';
//     }
//     asignaciones.close();
//     return;
// }

// void heuristica_3(vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidades){
//     //Le asignamos a un negocio el deposito que le quede mas cerca
//     vector<vector<int>> asig(dist.size(), vector<int>(0, {}));
//     //La idea de este algoritmo es ordenar los negocios de mayor a menor por el promedio de la diferencia entre
//     // un deposito i y i-1, siendo el deposito 0 el deposito mas cerca y m el deposito mas lejos.

//     for(int j = 0; j < dist[0].size(); j++){
//         int minimo = 99999;
//         int depositoFinal = 0;
//         for(int i = 0; i < dist.size(); i++){
//             if((capacidades[i]-demandas[i][j] >= 0) && (dist[i][j] < minimo)){
//                 minimo = dist[i][j];
//                 depositoFinal = i;
//             }
//         }
//         asig[depositoFinal].push_back(j);
//         capacidades[depositoFinal] -= demandas[depositoFinal][j];
//     } 

//     ofstream asignaciones("asignaciones_heuristica3.txt", std::ofstream::out);
//     for(int i = 0; i < asig.size(); i++){
//         for(int j = 0; j < asig[i].size(); j++){
//             string w = to_string(asig[i][j]);
//             asignaciones << w << " ";
//         }
//         asignaciones<<'\n';
//     }
//     asignaciones.close();
//     return;
// }

// void busqueda_local_1(int obj,vector<vector<int>> asig , vector<vector<int>> dist, vector<vector<int>> demandas, vector<int> capacidad){


// }


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05200";
    std::cout << "Reading file " << filename << std::endl;

    // vector<vector<int>> dist, demandas;
    // vector<int> capacidades;
    // lector(filename, dist, demandas, capacidades);

    // heuristica_1(dist, demandas, capacidades);
    // heuristica_2(dist, demandas, capacidades);

    // AssignmentInstance instance (filename);
    // instance.heuristica1();
    // instance.busqueda2();

    // AssignmentInstance instance2 (filename);
    // instance2.heuristica2();
    // instance2.busqueda1();

    AssignmentInstance Instance3 (filename);
    Instance3.metaheuristica();
    return 0;
}