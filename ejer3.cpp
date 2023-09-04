#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

bool existen_soluciones;
int cantidad_soluciones;
vector<vector<char>> soluciones;
vector<char> solucion;

vector<char> revisarSolucion(vector<char> &o , vector<char> &s){
    for (int i = 0; i < o.size(); i++)
    {   
        if (o[i] != s[i])
        {
            s[i]= *"?";
        }
    }
    return s;
}

void calcularOperaciones(vector<int> &l, vector<char> &o, int i, int s){
    // vector<char> copia_solucion = solucion;
    if (i==l.size())
    {
        if(s == 0){
            if (existen_soluciones==false){ //se registra la primera solucion
                existen_soluciones = true;
                solucion = o;
                //copia_solucion = solucion;
                return;
            }
            else{
                solucion = revisarSolucion(o, solucion);
                cantidad_soluciones++;
                return;
            }

    }
    else{
        return;
    }
    }

     //pruebo la suma: 
        o[i] = *"+";
        calcularOperaciones(l,o,i+1,s - l[i]);
        o[i] = *"-";
        calcularOperaciones(l,o,i+1,s + l[i]);
        return;
}



int main(){
    existen_soluciones= false;
    cantidad_soluciones = 0;
    //vector<char> solucion;
    //se ingresan los valores 
    int gastos,saldo;
    cin >> gastos;
    cin >> saldo;
    vector<int> l;
    for (int i = 0; i < gastos; i++)
    {
        int gasto;
        cin >> gasto;
        l.push_back(gasto);

    }
    vector<char> o(l.size());
    int largo_l = l.size();

    calcularOperaciones(l,o,0,saldo);
    //imprimo el resultado:
    vector<char> copia_res = solucion;
    for (int i = 0; i < solucion.size(); i++)
    {
        cout << solucion[i];
    }
    cout << endl;

    return 1;
}