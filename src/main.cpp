#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <typeinfo>
using namespace std;

void minimizacion_distancia(){
    ifstream file("instances/gap/gap_a/a05100.txt");
    string mystring;
    file >> mystring;
    cout<<mystring;
    return;
}




int main(int argc, char** argv) {
    std::string filename = "instances/gap/gap_a/a05100";
    std::cout << "Reading file " << filename << std::endl;

    vector<int>dist_1j = {};
    vector<int>dist_2j = {};
    ifstream file(filename);
    string mystring;
    file>>mystring;
    int m = stoi(mystring);
    cout<<m<<endl;
    file>>mystring;
    int n = stoi(mystring);
    cout<<n<<endl;

    int i = 0; //primer deposito
    while(i<100){
        file>>mystring;
        int x = stoi(mystring);
        dist_1j.push_back(x);
        i +=1;
    }
    for(int x : dist_1j){
        cout<<x<<endl;
    }
    cout<<'l'<<endl;

    int j = 0; //segundo deposito
    while(j<100){
        file>>mystring;
        int x = stoi(mystring);
        dist_2j.push_back(x);
        j +=1;
    }
    for(int x : dist_2j){
        cout<<x<<endl;
    }


    return 0;
}