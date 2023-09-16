#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>


using namespace std;
using ll = long long;


ll mod = 1e9 + 7;
ll mejor_descontento;
ll e; 
ll coeficientes;



//ordeno segun las multiplicaciones de la relacion menor-igual:
struct criterio {
    bool operator()(const std::pair<ll,ll> &left, const std::pair<ll,ll> &right) {
        return (((left.first % mod) * (right.second % mod)) <= ((right.first % mod) * (left.second % mod)));
    }
};

//l vector que es lista de los examenes, d acumulador de descontentos 
ll calcularDescontento(vector<pair<ll,ll>> &l){
    ll d = 0;
    sort(l.begin(), l.begin() + e, criterio()); //se ordena segun tiempo_i/coeficiente_i < tiempo_j/coeficiente_j
    for (int i = 0; i < e ; i++) {
        ll demora_examen_actual = l[i].first ; //demora que trae ese examen
        d += ((demora_examen_actual % mod) * (coeficientes %mod)) % mod; 
        coeficientes = ((coeficientes %mod) - (l[i].second % mod)) %mod;

        l[i].second = 0;
    }

    return (d % mod);
}

int main(){
    ll cantidad_casos;
    cin >> cantidad_casos;
    vector<pair<ll,ll>> l(1e7 +1, make_pair(0,0));
    for (int i = 0; i < cantidad_casos; i++) {
        mejor_descontento = std::numeric_limits<ll>::max();
        cin >> e;
        coeficientes = 0;
        //para cada estudiante, ingresamos su demora 
        for(int j = 0; j < e; j++){
            ll demora_e;
            cin >> demora_e;
            l[j].first = demora_e; 
            }
            //para cada estudiante, ingresamos su coeficiente
        for (int j = 0; j < e; j++){
            ll coeficiente_e;
            cin >> coeficiente_e;
            l[j].second = coeficiente_e;
            coeficientes += coeficiente_e;
        }


        cout << calcularDescontento(l) << endl; 

    }

    return 0;
}
