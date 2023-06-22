#include "instance.h"

AssignmentInstance::AssignmentInstance(string filename){
        // Guardamos las distancias de los negocios a los depositos en una matriz
    this->distancias={};
    this->capacidades={};
    this->demandas={};
    this->valor_objetivo=0;
    this->resuelto=0;
    this->correspondencia={};

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
        this->distancias.push_back(aux);
    }

    //Guardamos las demandas de los negocios en una matriz
    for(int i = 0; i < m; i++){
        vector<int> aux;
        for(int j = 0; j <n; j++){
            file>>mystring;
            int y = stoi(mystring);
            aux.push_back(y);
        }
        this->demandas.push_back(aux);
    }

    //Guardamos las capacidades totales de los depositos
    for(int i = 0; i < m; i++){
        file>>mystring;
        int z = stoi(mystring);
        this->capacidades.push_back(z);
    }
    vector<vector<int>>aux(this->distancias.size(), vector<int>(0, {}));
    this->asignaciones=aux;
    this->m=distancias.size();
    this->n=distancias[0].size();
    vector<int> aux2(this->n,-1);
    this->correspondencia=aux2;
}


void AssignmentInstance::heuristica1(){

    for(int j = 0; j < this->distancias[0].size(); j++){
        int minimo = 99999;
        int depositoFinal = 0;
        for(int i = 0; i < this->distancias.size(); i++){
            if((this->capacidades[i]-this->demandas[i][j] >= 0) && (this->distancias[i][j] < minimo)){
                minimo = this->distancias[i][j];
                depositoFinal = i;
            }
        }
        this->asignaciones[depositoFinal].push_back(j);
        this->capacidades[depositoFinal] -= this->demandas[depositoFinal][j];
        this->valor_objetivo+=this->distancias[depositoFinal][j];
        this->correspondencia[j]=depositoFinal;
    } 
    for(int i = 0; i<correspondencia.size();i++){
        if(correspondencia[i]==-1){
            int d_max = 0;
            for( int j = 0; j <m; j++){
                d_max = max(d_max, distancias[j][i]);
            }
            this->valor_objetivo += 3*d_max;
        }
    }
    crear_archivo("asignaciones_heuristicas_1_clase.txt");
    cout<<this->valor_objetivo<<endl;
}

vector<int> AssignmentInstance::ordenamiento(vector<int> dist){
    vector<int> ordenado={dist[0]};
    for(int i=1;i<this->n;i++){

        for(int j=0;j<ordenado.size();j++){

            if(dist[i]<=dist[ordenado[j]]){

                ordenado.insert(ordenado.begin()+j,i);
                break;
            }
        }
        if(dist[i]>dist[ordenado[ordenado.size()-1]]){
            ordenado.push_back(i);
        }
    }
    return ordenado;
}

void AssignmentInstance::heuristica2(){
    //Le asignamos a  el cada deposito loo negocios que le queden mas cerca
    vector<int>dist_a_dep = {};
    vector<int>no_disponibles={};
    for(int i = 0; i<m; i++){
        dist_a_dep = ordenamiento(distancias[i]);
        for(int j = 0; j<n; j++){
            if(this->capacidades[i]-this->demandas[i][dist_a_dep[j]] >= 0 && find(no_disponibles.begin(), no_disponibles.end(), dist_a_dep[j])==no_disponibles.end()){ 
                this->asignaciones[i].push_back(dist_a_dep[j]);
                this->capacidades[i] -= this->demandas[i][dist_a_dep[j]];
                this->correspondencia[dist_a_dep[j]] = i;
                this->valor_objetivo+=this->distancias[i][dist_a_dep[j]];
                no_disponibles.push_back(dist_a_dep[j]);
            }
        }
    }
    for(int i = 0; i<correspondencia.size();i++){
        if(correspondencia[i]==-1){
            int d_max = 0;
            for( int j = 0; j <m; j++){
                d_max = max(d_max, distancias[j][i]);
            }
            this->valor_objetivo += 3*d_max;
        }
    }
    crear_archivo("asignaciones_heuristicas_2_clase.txt");
    cout<<this->valor_objetivo<<endl;
}

// void AssignmentInstance::busqueda1(){
//     for(int i=0; i<this->m;i++){
//         int j=0;
//         int flag;
//         while(j<asignaciones[i].size()){
//             flag=0;
//             for(int d=0;d<this->m;d++){
//                 if(d!=i && this->distancias[d][this->asignaciones[i][j]]<this->distancias[i][this->asignaciones[i][j]] && this->demandas[d][asignaciones[i][j]]<this->capacidades[d] ){
//                     this->valor_objetivo-=(this->distancias[i][this->asignaciones[i][j]]-this->distancias[d][this->asignaciones[i][j]]);
//                     this->asignaciones[d].push_back(this->asignaciones[i][j]);
//                     this->capacidades[d]-=this->demandas[d][this->asignaciones[i][j]];
//                     this->capacidades[i]+=this->demandas[i][this->asignaciones[i][j]];
//                     this->asignaciones[i].erase(this->asignaciones[i].begin()+j);
//                     flag=1;
//                     break;
//                 }
//             }
//             if(flag==0){j++;}
//         }
//     }
//     crear_archivo("asignaciones_heuristicas_2_busqueda_local.txt");
//     cout<<this->valor_objetivo<<endl;
// }


void AssignmentInstance::busqueda1(){
    // cout<<correspondencia.size()<<endl;
    for(int i=0; i<this->n;i++){
        int j=0;
        // Deberiamos tener en cuenta el caso que no esta en ningun deposito.
        if(correspondencia[i]!=-1){
            while(j<m){
                if(j!=correspondencia[i] && this->distancias[j][i]<this->distancias[correspondencia[i]][i] && this->demandas[j][i]<this->capacidades[j]){
                    this->valor_objetivo-=(this->distancias[correspondencia[i]][i]-this->distancias[j][i]);
                    this->capacidades[j]-=this->demandas[j][i];
                    // cout<<"B"<<endl;
                    this->capacidades[correspondencia[i]]+=this->demandas[correspondencia[i]][i];
                    // cout<<"C"<<endl;
                    this->asignaciones[correspondencia[i]].erase(find(asignaciones[correspondencia[i]].begin(), asignaciones[correspondencia[i]].end(), i));
                    // cout<<"D"<<endl;
                    this->asignaciones[j].push_back(i);
                    // cout<<"E"<<endl;
                    this->correspondencia[i]=j;
                    //cout<<"F"<<endl;
                    break;
                }
                j+=1;
            }
        }
    }
    crear_archivo("asignaciones_heuristicas_2_busqueda_local.txt");
    cout<<this->valor_objetivo<<endl;
}


void AssignmentInstance::busqueda2(){
    for(int i=0;i<this->n;i++){
        for(int j=0;j<this->n;j++){
            if(this->correspondencia[i]!=this->correspondencia[j]){
                // cout<<"lara hace pis"<<endl;
                if(condiciones_swap(i,j)){
                    // cout<<"lara hace caca"<<endl;
                    this->capacidades[this->correspondencia[i]] += this->demandas[this->correspondencia[i]][i];
                    this->capacidades[this->correspondencia[i]] -= this->demandas[this->correspondencia[i]][j];
                    this->capacidades[this->correspondencia[j]] += this->demandas[this->correspondencia[j]][j];
                    this->capacidades[this->correspondencia[j]] -= this->demandas[this->correspondencia[j]][i];
                    this->valor_objetivo-=(this->distancias[this->correspondencia[i]][i]+this->distancias[this->correspondencia[j]][j]- this->distancias[this->correspondencia[i]][j]-this->distancias[this->correspondencia[j]][i]);
                    this->asignaciones[this->correspondencia[i]].push_back(j);
                    this->asignaciones[this->correspondencia[j]].push_back(i);
                    this->asignaciones[this->correspondencia[i]].erase(find(this->asignaciones[this->correspondencia[i]].begin(),this->asignaciones[this->correspondencia[i]].end(), i));
                    this->asignaciones[this->correspondencia[j]].erase(find(this->asignaciones[this->correspondencia[j]].begin(),this->asignaciones[this->correspondencia[j]].end(), j));
                    swap(this->correspondencia[i], this->correspondencia[j]);
                }
            }
        }
    }
    cout<<this->valor_objetivo<<endl;
    crear_archivo("asignaciones_heuristicas_1_busqueda_local.txt");
}


void AssignmentInstance::crear_archivo(string nombre){
    ofstream archivo(nombre, std::ofstream::out);
    for(int i = 0; i < this->asignaciones.size(); i++){
        for(int j = 0; j < this->asignaciones[i].size(); j++){
            string w = to_string(this->asignaciones[i][j]);
            archivo << w << " ";
        }
        archivo<<'\n';
    }
    archivo.close();
    return;
}

bool AssignmentInstance::condiciones_swap(int i, int j){
    if(correspondencia[i]==-1 || correspondencia[j]==-1){return false;}
    bool condicion1= (this->distancias[this->correspondencia[i]][i] + this->distancias[this->correspondencia[j]][j])> (this->distancias[this->correspondencia[i]][j] + this->distancias[this->correspondencia[j]][i]);
    bool condicion2= this->demandas[this->correspondencia[i]][j]< this->capacidades[this->correspondencia[i]]+this->demandas[this->correspondencia[i]][i];
    bool condicion3= this->demandas[this->correspondencia[j]][i]< this->capacidades[this->correspondencia[j]]+this->demandas[this->correspondencia[j]][j];
    return condicion1 && condicion2 && condicion3;
}

void AssignmentInstance::metaheuristica(){
    heuristica2();
    bool mejora=true;
    int actual;
    while(mejora){
        actual=this->valor_objetivo;
        bool relocate=true;
        while(relocate){
            int reloc=this->valor_objetivo;
            busqueda1();
            cout<<"Reloc:"<<valor_objetivo<<endl;
            if(reloc==valor_objetivo){relocate=false;}
        }
        bool swape=true;
        while(swape){
            int spe=this->valor_objetivo;
            busqueda2();
            cout<<"Spe:"<<valor_objetivo<<endl;
            if(spe==valor_objetivo){swape=false;}
        }
        if (valor_objetivo==actual){mejora=false;}
    }

}

