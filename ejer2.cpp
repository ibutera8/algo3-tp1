#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

int mod = 1e9 + 7;
int mejor_descontento;


int calcularDescontento(vector<pair<int,int>> &l,vector<pair<float,int>> &r, int t, int d){
    for (int i = 0; i < r.size() ; i++) {
        int posicion = r[i].second; //posicion del parcial que tiene peor ratio tiempo/coeficiente
        int demora_examen_actual = l[posicion].first % mod; //demora que trae ese examen
        for (int j = 0; j < l.size(); j++) {   
            int descontento = (demora_examen_actual * l[j].second) % mod;
            int nuevo_descontento = (d + descontento) % mod;
            d = nuevo_descontento % mod;
        }

        l[posicion].second = 0;
    }

    return d;
}

struct criterio {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return (left.first > right.first) || (left.first == right.first && left.second > right.second);
    }
};

//toma el listado de parciales y devuelve un vector de tuplas de la forma <tiempo / coeficiente, posicion original>:
vector<pair<float,int>> obtener_Peores(vector<pair<int,int>> l){ 
    vector<pair<float,int>> res;
    for ( int i = 0; i < l.size(); i++)
    {
        float division = (float)l[i].second / (float)l[i].first;
        pair <float, int> examen;
        examen.first= division;
        examen.second= i;
        res.push_back(examen);

    }
    sort(res.begin(), res.end(), criterio());
    return res;
}

int main(){
    int cantidad_casos;
    cin >> cantidad_casos;
    for (int i = 0; i < cantidad_casos; i++) {
        mejor_descontento = std::numeric_limits<int>::max();
        int e;    
        cin >> e;
        vector<pair<int,int>> l(e, make_pair(0,0));
        //para cada estudiante, ingresame su demora 
        for(int j = 0; j < e; j++){
            int demora_e;
            cin >> demora_e;            
            l[j].first = demora_e; 
            }
            //para cada estudiante, ingresame su coeficiente
        for (int j = 0; j < e; j++){
            int coeficiente_e;
            cin >> coeficiente_e;
            l[j].second = coeficiente_e;
        } 
        vector<pair<float, int>> r = obtener_Peores(l);
        //optimizarCorreciones(l, 0,0);
        cout << calcularDescontento(l, r, 0, 0) << endl; 

    }
  
    return 0;
}