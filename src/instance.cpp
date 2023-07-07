#include "instance.h"

AssignmentInstance::AssignmentInstance(string filename){
    // Guardamos las distancias de los negocios a los depositos en una matriz
    this->distancias={};
    this->capacidades={};
    this->demandas={};
    this->valor_objetivo=0;
    this->correspondencia={};
    this->tiempo={0,0,0,0,0};

    
    ifstream file(filename);
    string mystring;
    file>>mystring;
    int m = stoi(mystring);
    file>>mystring;
    int n = stoi(mystring);
    for(int i = 0; i < m; i++){
        vector<double> aux;
        for(int j = 0; j < n; j++){
            file>>mystring;
            double x = stod(mystring);
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
    double d_max = 0;
    for(int i = 0; i<n;i++){ //calculo la distancia máxima entre un negocio y un depósito
        for( int j = 0; j <m; j++){
            d_max = max(d_max, distancias[j][i]);
        }
    }
    this->dist_max = d_max;
}


void AssignmentInstance::heuristica1(){
    auto begin = std::chrono::high_resolution_clock::now();
    for(int j = 0; j < this->distancias[0].size(); j++){ //iteramos por los negocios
        double minimo = 99999;
        int depositoFinal = -1;
        for(int i = 0; i < this->distancias.size(); i++){ //iteramos por los depósitos
            if((this->capacidades[i]-this->demandas[i][j] >= 0) && (this->distancias[i][j] < minimo)){ //vemos si el la demanda del negocio no supera la capacidad del deposito y si este es el deposito más cercano al negocio
                minimo = this->distancias[i][j];
                depositoFinal = i;
            }
        }
        if(depositoFinal!=-1){
            this->asignaciones[depositoFinal].push_back(j);//agregamos el negocio j a su depósito más cercano
            this->capacidades[depositoFinal] -= this->demandas[depositoFinal][j];//actualizamos la capacidad del deposito
            this->valor_objetivo+=this->distancias[depositoFinal][j];//actualizamos el valor objetivo
            this->correspondencia[j]=depositoFinal;
        }

    } 
     
    for(int i = 0; i<correspondencia.size();i++){//penalizo los negocios no asignados
        if(correspondencia[i]==-1){
            this->valor_objetivo += 3*this->dist_max;
        }
    }      
    crear_archivo("asignaciones_heuristicas_1_clase.txt");//generamos el output con las asignaciones
    cout<<this->valor_objetivo<<endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-begin);
    this->tiempo[0] = elapsed.count();

}

vector<int> AssignmentInstance::ordenamiento(vector<double> dist){
    //el objetivo de esta función auxiliar es por cada depósito ordenar los negocios según cuan cerca están de este
    //dist son las distancias de los negocios a un depósito x
    //observemos que el vector ordenado no contiene las distancias si no que los índices de los negocios
    vector<int> ordenado={0};
    for(int i=1;i<this->n;i++){ // iteramos por los negocios, ordenado por distancia  al depósito, de menor a mayor

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
    auto begin = std::chrono::high_resolution_clock::now();
    vector<int>dist_a_dep = {};
    vector<int>no_disponibles={};
    for(int i = 0; i<m; i++){//iteramos por los depositos
        dist_a_dep = ordenamiento(distancias[i]); //ordenamos por cercanía los negocios en relación al depósito i
        for(int j = 0; j<n; j++){//iteramos por los negocios
            if(this->capacidades[i]-this->demandas[i][dist_a_dep[j]] >= 0 && find(no_disponibles.begin(), no_disponibles.end(), dist_a_dep[j])==no_disponibles.end()){ //evalúo si el negocio tiene una demanda menor a la capacidad del deósito y si el negocio no ha sido asignado aún
                this->asignaciones[i].push_back(dist_a_dep[j]); //asigno el negocio al depósito i
                this->capacidades[i] -= this->demandas[i][dist_a_dep[j]]; //actualizo las capacidades
                this->correspondencia[dist_a_dep[j]] = i;
                this->valor_objetivo+=this->distancias[i][dist_a_dep[j]]; //actualizo el valor objetivo
                no_disponibles.push_back(dist_a_dep[j]); //marco como no disponible el negocio ya asignado
            }
        }
    }        
    for(int i = 0; i<correspondencia.size();i++){//penalizo los negocios no asignados
        if(correspondencia[i]==-1){
            this->valor_objetivo += 3*this->dist_max;
        }
    }      
    crear_archivo("asignaciones_heuristicas_2_clase.txt"); //generamos el output con las asignaciones
    cout<<this->valor_objetivo<<endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-begin);
    this->tiempo[1] = elapsed.count();
}


void AssignmentInstance::busqueda1(){
    // cout<<correspondencia.size()<<endl;
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0; i<this->n;i++){ //iteramos por los negocios
        int j=0;
        // Deberiamos tener en cuenta el caso que no esta en ningun deposito.
        while(j<m){//iteramos por los depósitos
            if(correspondencia[i]!=-1){ //si el negocio fue asignado a algun depósito
                if(j!=correspondencia[i] && this->distancias[j][i]<this->distancias[correspondencia[i]][i] && this->demandas[j][i]<this->capacidades[j]){//evalúo si la distancia es menor en el nuevo depósito y si la capacidad es suficiente
                    this->valor_objetivo-=(this->distancias[correspondencia[i]][i]-this->distancias[j][i]);//actualizamos el valor objetivo
                    this->capacidades[j]-=this->demandas[j][i];//actualizamos las capacidades
                    this->capacidades[correspondencia[i]]+=this->demandas[correspondencia[i]][i];//actualizamos las capacidades
                    this->asignaciones[correspondencia[i]].erase(find(asignaciones[correspondencia[i]].begin(), asignaciones[correspondencia[i]].end(), i));
                    this->asignaciones[j].push_back(i);
                    this->correspondencia[i]=j;
                    break;
                }
            }
            else if(correspondencia[i]==-1){
                if(capacidades[j]-demandas[j][i]>=0){
                    //CHEQUEAR SI EL CODIGO ENTRA ACÁ !!!
                    this->capacidades[j] -= demandas[j][i];//actualizo capacidades
                    this->valor_objetivo += distancias[j][i]; //actualizo valor objetivo
                    this->valor_objetivo -= 3*this->dist_max; //despenalizo
                    this->correspondencia[i] = j; // asigno
                    this->asignaciones[j].push_back(i);// asigno
                }
            }                
            j+=1;
        }
    }
    crear_archivo("asignaciones_heuristicas_2_busqueda_local.txt");
    cout<<this->valor_objetivo<<endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-begin);
    this->tiempo[2] = elapsed.count();
}


void AssignmentInstance::busqueda2(){
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0;i<this->n;i++){ //iteramos por los negocios
        for(int j=0;j<this->n;j++){ //iteramos por los negocios
            if(i!=j && this->correspondencia[i]!=this->correspondencia[j] ){
                if(condiciones_swap(i,j)){ //evaluamos si cumple las condiciones del swap
                    this->capacidades[this->correspondencia[i]] += this->demandas[this->correspondencia[i]][i]; //actualizamos capacidades
                    this->capacidades[this->correspondencia[i]] -= this->demandas[this->correspondencia[i]][j]; //actualizamos capacidades
                    this->capacidades[this->correspondencia[j]] += this->demandas[this->correspondencia[j]][j]; //actualizamos capacidades
                    this->capacidades[this->correspondencia[j]] -= this->demandas[this->correspondencia[j]][i]; //actualizamos capacidades
                    this->valor_objetivo-=(this->distancias[this->correspondencia[i]][i]+this->distancias[this->correspondencia[j]][j]- this->distancias[this->correspondencia[i]][j]-this->distancias[this->correspondencia[j]][i]);//actualizamos el valor objetivo
                    this->asignaciones[this->correspondencia[i]].push_back(j);
                    this->asignaciones[this->correspondencia[j]].push_back(i);
                    this->asignaciones[this->correspondencia[i]].erase(find(this->asignaciones[this->correspondencia[i]].begin(),this->asignaciones[this->correspondencia[i]].end(), i));
                    this->asignaciones[this->correspondencia[j]].erase(find(this->asignaciones[this->correspondencia[j]].begin(),this->asignaciones[this->correspondencia[j]].end(), j));
                    swap(this->correspondencia[i], this->correspondencia[j]);//realizamos el swap
                }
            }
        }
    }
    cout<<this->valor_objetivo<<endl;
    crear_archivo("asignaciones_heuristicas_1_busqueda_local.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-begin);
    this->tiempo[3] = elapsed.count();
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
    if(correspondencia[i]==-1 || correspondencia[j]==-1){return false;}//evaluamos que ambos negocios hayan sido asignados a algún depósito
    bool condicion1= (this->distancias[this->correspondencia[i]][i] + this->distancias[this->correspondencia[j]][j])> (this->distancias[this->correspondencia[i]][j] + this->distancias[this->correspondencia[j]][i]);//evaluamos que las distancias mejoren
    bool condicion2= this->demandas[this->correspondencia[i]][j]< this->capacidades[this->correspondencia[i]]+this->demandas[this->correspondencia[i]][i];//evaluamos que las capacidades permitan el swap
    bool condicion3= this->demandas[this->correspondencia[j]][i]< this->capacidades[this->correspondencia[j]]+this->demandas[this->correspondencia[j]][j];//evaluamos que las capacidades permitan el swap
    return condicion1 && condicion2 && condicion3;
}

void AssignmentInstance::metaheuristica(bool i){
    auto begin = std::chrono::high_resolution_clock::now();
    (i ? heuristica1():heuristica2());//utilizamos la heuristica indicada por parámetro
    bool mejora=true;
    double actual;
    while(mejora){
        actual=this->valor_objetivo;
        bool relocate=true;
        while(relocate){ //iteramos hasta llegar a un mínimo local del vecindario de relocate
            double reloc=this->valor_objetivo;
            busqueda1();//O(nm)
            cout<<"Reloc:"<<valor_objetivo<<endl;
            if(reloc==valor_objetivo){relocate=false;}//una vez que el valor objetivo no mejora, sabemos que estamos en un mínimo local, pasamos al próximo operador (swap)
        }
        bool swape=true;
        while(swape){//iteramos hasta llegar a un mínimo local del vecindario de swap
            double spe=this->valor_objetivo;
            busqueda2();//O(n^2)
            cout<<"Spe:"<<valor_objetivo<<endl;
            if(spe==valor_objetivo){swape=false;}//una vez que el valor objetivo no mejora, sabemos que estamos en un mínimo local, pasamos al próximo operador (relocate)
        }
        if (valor_objetivo==actual){//si ningun operador logró mejorar la solución, estamos en un mínimo para ambos, finaliza la búsqueda
            mejora=false;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end-begin);
    this->tiempo[4] = elapsed.count();
}

