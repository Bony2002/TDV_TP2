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
    crear_archivo("asignaciones_heuristicas_1_clase.txt");
    cout<<this->valor_objetivo<<endl;
}

void AssignmentInstance::heuristica2(){
        //Le asignamos a  el cada deposito loo negocios que le queden mas cerca
    vector<int>no_disponibles={};
    for(int j = 0; j < this->distancias.size(); j++){
        int suma = 0;
        //calculas la distancia promedio de cada deposito
        for(int i = 0; i<this->distancias[0].size(); i++){
            suma += this->distancias[j][i];
        }
        int prom = suma/this->distancias[0].size();
        for(int i = 0; i < this->distancias[0].size(); i++){
            //agregas el nogocio al deposito si esta mas cerca que el promedio
            if((this->capacidades[j]-this->demandas[j][i] >= 0) && (this->distancias[j][i] <= prom) && find(no_disponibles.begin(), no_disponibles.end(), i)==no_disponibles.end()){ 
                this->asignaciones[j].push_back(i);
                this->capacidades[j] -= this->demandas[j][i];
                no_disponibles.push_back(i);
                this->valor_objetivo+=this->distancias[j][i];
            }
        }
    }
    crear_archivo("asignaciones_heuristicas_2_clase.txt");
    cout<<this->valor_objetivo<<endl;

}

void AssignmentInstance::busqueda1(){
    for(int i=0; i<this->m;i++){
        int j=0;
        int flag;
        while(j<asignaciones[i].size()){
            flag=0;
            for(int d=0;d<this->m;d++){
                if(d!=i && this->distancias[d][this->asignaciones[i][j]]<this->distancias[i][this->asignaciones[i][j]] && this->demandas[d][asignaciones[i][j]]<this->capacidades[d] ){
                    this->valor_objetivo-=(this->distancias[i][this->asignaciones[i][j]]-this->distancias[d][this->asignaciones[i][j]]);
                    this->asignaciones[d].push_back(this->asignaciones[i][j]);
                    this->capacidades[d]-=this->demandas[d][this->asignaciones[i][j]];
                    this->capacidades[i]+=this->demandas[i][this->asignaciones[i][j]];
                    this->asignaciones[i].erase(this->asignaciones[i].begin()+j);
                    flag=1;
                    break;
                }
            }
            if(flag==0){j++;}
        }
    }
    crear_archivo("asignaciones_heuristicas_2_busqueda_local.txt");
    cout<<this->valor_objetivo<<endl;

}
void AssignmentInstance::busqueda2(){
    for(int i=0;i<this->n;i++){
        for(int j=0;j<this->n;j++){
            if(this->correspondencia[i]!=this->correspondencia[j]){
                if(condiciones_swap(i,j)){
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
    bool condicion1= (this->distancias[this->correspondencia[i]][i] + this->distancias[this->correspondencia[j]][j])> (this->distancias[this->correspondencia[i]][j] + this->distancias[this->correspondencia[j]][i]);
    bool condicion2= this->demandas[this->correspondencia[i]][j]< this->capacidades[this->correspondencia[i]]+this->demandas[this->correspondencia[i]][i];
    bool condicion3= this->demandas[this->correspondencia[j]][i]< this->capacidades[this->correspondencia[j]]+this->demandas[this->correspondencia[j]][j];
    return condicion1 && condicion2 && condicion3;
}
