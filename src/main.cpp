#include "instance.h"
using namespace std;

void generadorCSV(string filename, vector<string> directorio){
        
        std::fstream fout;
        fout.open(filename, ios::out);
        fout<<"Dataset,Valor Objetivo Heruistica 1,Valor Objetivo Heuristica 2,Valor Objetivo Heuristica 1 + Busqueda Local 1,Valor Objetivo Heuristica 1 + Busqueda Local 2,Valor Objetivo Heuristica 2 + Busqueda Local 1,Valor Objetivo Heuristica 2 + Busqueda Local 2,Metaheuristica1,Metaheuristica2\n";
        for(string i : directorio){
            AssignmentInstance Instance1(i);
            Instance1.heuristica1();
            double heur1 = Instance1.valor_objetivo;
            Instance1.busqueda1();
            double heur1busq1 = Instance1.valor_objetivo; 
            
            AssignmentInstance Instance2(i);
            Instance2.heuristica1();
            Instance2.busqueda2();
            double heur1busq2 = Instance2.valor_objetivo; 

            AssignmentInstance Instance3(i);
            Instance3.heuristica2();
            double heur2 = Instance3.valor_objetivo;
            Instance3.busqueda1();
            double heur2busq1 = Instance3.valor_objetivo; 

            AssignmentInstance Instance4(i);
            Instance4.heuristica2();
            Instance4.busqueda2();
            double heur2busq2 = Instance4.valor_objetivo; 

            AssignmentInstance Instance5(i);
            Instance5.metaheuristica(true);
            double meta1 = Instance5.valor_objetivo;


            AssignmentInstance Instance6(i);
            Instance6.metaheuristica(false);
            double meta2 = Instance6.valor_objetivo;

            fout << i <<","<< heur1 <<","<< heur2 <<","<< heur1busq1 <<","<< heur1busq2 <<","<< heur2busq1 <<","<< heur2busq2 <<","<< meta1 <<","<<meta2<<"\n";
        }
        fout.close();
    }


int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;
    std::vector<string> directorioA ={"instances/gap/gap_a/a05100","instances/gap/gap_a/a05200","instances/gap/gap_a/a10100","instances/gap/gap_a/a10100","instances/gap/gap_a/a20100","instances/gap/gap_a/a20200"};
    std::string archivoA="ExperimentacionGapA";
    std::vector<string> directorioB ={"instances/gap/gap_b/b05100","instances/gap/gap_b/b05200","instances/gap/gap_b/b10100","instances/gap/gap_b/b10100","instances/gap/gap_b/b20100","instances/gap/gap_b/b20200"};
    std::string archivoB="ExperimentacionGapB";
    std::vector<string> directorioE ={"instances/gap/gap_e/e05100","instances/gap/gap_e/e05200","instances/gap/gap_e/e10100","instances/gap/gap_e/e10200","instances/gap/gap_e/e10400","instances/gap/gap_e/e15900","instances/gap/gap_e/e20100","instances/gap/gap_e/e20200","instances/gap/gap_e/e20400","instances/gap/gap_e/e30900","instances/gap/gap_e/e40400","instances/gap/gap_e/e60900","instances/gap/gap_e/e201600","instances/gap/gap_e/e401600","instances/gap/gap_e/e801600"};
    std::string archivoE="ExperimentacionGapE";
    std::vector<string> directorioReal ={"instances/real/real_instance"};
    std::string archivoReal="ExperimentacionReal";
    
    

    // AssignmentInstance Instance (filename);
    // Instance.metaheuristica();
    // cout<<Instance.valor_objetivo<<endl;

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

    std::string realfile = "instances/real/real_instance";
    std::cout << "Reading file " << realfile << std::endl;

    AssignmentInstance Instance3 (realfile);
    Instance3.metaheuristica(true);
    cout<<Instance3.valor_objetivo<<endl;

    AssignmentInstance Instance4 (realfile);
    Instance4.metaheuristica(false);
    cout<<Instance4.valor_objetivo<<endl;
    generadorCSV(archivoA,directorioA);
    generadorCSV(archivoB,directorioB);
    generadorCSV(archivoE,directorioE);
    
    return 0;

}

