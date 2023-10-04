#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;
using ll = long long;

//variables globales
ll inf = std::numeric_limits<int>::max();
vector<ll> solucion;
bool existen_soluciones;

ll costo(vector<ll> &puestos, vector<ll> &proveedurias){
    ll res = 0;
    for (int i = 0; i < puestos.size(); i++){
        //para cada i-esimo puesto
        ll minima_distancia = inf;
        for (int j = 0; j < proveedurias.size(); j++) {
            //busco la minima proveeduria mas cercana
            minima_distancia = min(minima_distancia, abs(puestos[i] - proveedurias[j]));
        }
        res += minima_distancia;
    }
    return res;
}

vector<ll> revisarSolucion(vector<ll> &puestos, vector<ll> &proveedurias){
    if (costo(puestos, solucion) < costo(puestos, proveedurias)) {
        return solucion;
    } else {
        return proveedurias;
    }
}


int costanera(vector<ll> &puestos, vector<ll> &proveedurias, int i, int k){
    int res = inf;
    if (k == 0 || i == puestos.size()) {
        if (existen_soluciones) {
            solucion = revisarSolucion(puestos, proveedurias);
        } else {
            solucion = proveedurias;
            existen_soluciones = true;
        }
        return costo(puestos, proveedurias); //Caso Base
    }
    
    //veo el minimo entre poner proveeduria en el puesto actual y no ponerlo:
    proveedurias.push_back(puestos[i]);
    int agregoProveeduriaEnPuestoI = costanera(puestos, proveedurias, i+1, k-1);
    proveedurias.pop_back();
    int noAgregoYSigo = costanera(puestos, proveedurias, i+1, k);
    res = min(agregoProveeduriaEnPuestoI, noAgregoYSigo);
    return res;
}


int main(){
    int cant_tests;
    cin >> cant_tests;
    for (int l = 1 ; l < cant_tests +1; l++) {
        existen_soluciones = false;
        int n, k;
        cin >> n >> k;
        vector<ll> puestos;
        vector<ll> proveedurias;
        //armo el vector de puestos
        for (int i = 0; i < n ; i++) {
            ll posicion_puesto;
            cin >> posicion_puesto;
            puestos.push_back(posicion_puesto);
        }
        int min_costo = costanera(puestos, proveedurias, 0, k);
        //imprimo el valor optimo
        cout << min_costo << endl;
        //imprimo la solucion optima
        for (int i = 0; i < solucion.size(); i++){
            cout << solucion[i] << " ";
        }
        cout << endl;
    }
}