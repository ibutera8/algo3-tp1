#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

bool existen_soluciones;
ll cantidad_soluciones;
vector<char> solucion;
vector<vector<int>> memo; 

vector<char> revisarSolucion(vector<char> &o, vector<char> &s) {
    for (int i = 0; i < o.size(); i++) {
        if (o[i] != s[i]) {
            s[i] = '?';
        }
    }
    return s;
}

bool calcularOperaciones(vector<ll> &l, vector<char> &o, int i, ll s) {
    bool res = false;
    if (i == l.size()) {
        if (s == 0) {
            if (!existen_soluciones) {
                existen_soluciones = true;
                solucion = o;
                return true;
            } else {
                solucion = revisarSolucion(o, solucion);
                cantidad_soluciones++;
                return true;
            }
        } else {
            return false;
        }
    }

    if (memo[i][s] != -1) {
        return memo[i][s];
    }

    vector<char> o_suma = o;
    vector<char> o_resta = o;
    o_suma[i] = '+';
    o_resta[i] = '-';
    //no sirve ninguno
    if (!calcularOperaciones(l, o_suma, i + 1, s - l[i]) && 
        !calcularOperaciones(l, o_resta, i + 1, s + l[i]))
    {
        memo[i][s] = 0;
        res =  false;
    }
    bool suma = calcularOperaciones(l, o_suma, i + 1, s - l[i]);
    bool resta = calcularOperaciones(l, o_resta, i + 1, s - l[i]);
    //sirven ambos
    if(calcularOperaciones(l, o_suma, i + 1, s - l[i]) &&
        calcularOperaciones(l, o_resta, i + 1, s - l[i]))
        {
         memo[i][s] = 1;
         res =  true;
        }
    //sirve solo suma     
    if(calcularOperaciones(l, o_suma, i + 1, s - l[i]) &&
        !calcularOperaciones(l, o_resta, i + 1, s - l[i]))
        {
         memo[i][s] = 1;
         res =  true;
        }   
    //sirve solo resta
    if(!calcularOperaciones(l, o_suma, i + 1, s - l[i]) &&
        calcularOperaciones(l, o_resta, i + 1, s - l[i]))
        {
         memo[i][s] = 1;
         res = true;
        }       
        
    return res;
}

int main() {
    existen_soluciones = false;
    cantidad_soluciones = 0;

    ll cantidad_tests;
    cin >> cantidad_tests;

    for (int t = 0; t < cantidad_tests; t++) {
        existen_soluciones = false;
        cantidad_soluciones = 0;

        ll gastos, saldo;
        cin >> gastos >> saldo;

        vector<ll> l;
        for (int i = 0; i < gastos; i++) {
            int gasto;
            cin >> gasto;
            l.push_back(gasto);
        }

        vector<char> o(l.size());
        ll largo_l = l.size();
        int saldos_posibles = 2000;
        memo.assign(l.size(), vector<int>(saldos_posibles, -1));

        calcularOperaciones(l, o, 0, saldo);

        vector<char> copia_res = solucion;
        for (int i = 0; i < solucion.size(); i++) {
            cout << solucion[i];
        }
        cout << endl;
    }

    return 0;
}
