#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
using ll = long long; //abrevio el nombre de la variable

bool existen_soluciones;
long long cantidad_soluciones;
vector<vector<char>> soluciones;
vector<char> solucion;
vector<pair<ll,ll>> dp;


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

void calcularOperaciones(vector<ll> &l, vector<char> &o, int i, int s){
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
    ll gastos,saldo, cantidad_tests;
    cin >> cantidad_tests;
    for (int t = 0; t < cantidad_tests; t++)
    {
        existen_soluciones= false;
        cantidad_soluciones = 0;
        cin >> gastos;
        cin >> saldo;
        dp = vector<pair<ll,ll>>(gastos, make_pair(-1,-1));
        vector<ll> l;
    
        for (int i = 0; i < gastos; i++)
        {
            int gasto;
            cin >> gasto;
            l.push_back(gasto);

        }
        vector<char> o(l.size());
        ll largo_l = l.size();

        calcularOperaciones(l,o,0,saldo);
        //imprimo el resultado:
        vector<char> copia_res = solucion;
        for (int i = 0; i < solucion.size(); i++)
        {
            cout << solucion[i];
        }
    cout << endl;
    }

    return 0;
}




















/*#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
using ll = long long; //abrevio el nombre de la variable

bool existen_soluciones;
long long cantidad_soluciones;
vector<vector<char>> soluciones;
vector<char> solucion;
vector<pair<ll,ll>> dp;

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

void calcularOperaciones(vector<ll> &l, vector<char> &o, ll i, ll s){
    // vector<char> copia_solucion = solucion;
    if (i==l.size())
    {
        if(s == 0){
            if (existen_soluciones==false){ //se registra la primera solucion
                existen_soluciones = true;
                solucion = o;
                for (int z = 0; z < o.size(); z++)
                {
                     if (o[z] == *"+") //sirvio la suma
                    {
                        dp[i].second = 1;
                        dp[i].first = 0; 
                    }
                    else{             //sirvio la resta
                         dp[i].first = 1; 
                         dp[i].second = 0;
                        }
                    }
            }
            else{
                solucion = revisarSolucion(o, solucion);
                cantidad_soluciones++;
                return;
            }
        
        }
        
        else{  //no llega a buen resultado
        return;

        }
    }
     //pruebo la suma: 
        vector<pair<ll,ll>> copia_dp = dp;
        if(dp[i].second == -1){  //si no 
        o[i] = *"+";
        calcularOperaciones(l,o,i+1,s - l[i]);
        }
        if(dp[i].first ==-1){
        o[i] = *"-";
        calcularOperaciones(l,o,i+1,s + l[i]);
        }
        return;
}
//nos ahorraria operaciones tener una funcion recursiva que sea del tipo dp(ignoado, i, sumar)
//que nos dice si a artir de un determinado indice podemos sumar n o no con los siguientes indices 
//utilizando dicha operacion. Por ejemplo memo[i][j] nos diria si es posile llegar a j (que ya tiene restado a i)
//habiendo hecho la operacion i 


int main(){
    existen_soluciones= false;
    cantidad_soluciones = 0;
    //vector<char> solucion;
    //se ingresan los valores 
    ll cantidad_tests;
    cin >> cantidad_tests;
    ll gastos,saldo;
    
    for (int t = 0; t < cantidad_tests; t++)
    {
        existen_soluciones= false;
        cantidad_soluciones = 0;
        cin >> gastos;
        cin >> saldo;
        dp = vector<pair<ll,ll>>(gastos, make_pair(-1,-1));
        vector<ll> l;
    
        for (int i = 0; i < gastos; i++)
        {
            int gasto;
            cin >> gasto;
            l.push_back(gasto);

        }
        vector<char> o(l.size());
        ll largo_l = l.size();

        calcularOperaciones(l,o,0,saldo);
        //imprimo el resultado:
        vector<char> copia_res = solucion;
        for (int i = 0; i < solucion.size(); i++)
        {
            cout << solucion[i];
        }
    cout << endl;
    }

    return 1;
}*/
