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

/* 
//l vector de parciales, t tiempo acumulado, d descontento acumulado
void optimizarCorreciones(vector<pair<int,int>> & l ,int t, int d){
    int prueba2 = mejor_descontento;
    int largo_l = l.size();
    if (l.size() == 0) //no hay nada por corregir, ya termine
    {
        if (d < mejor_descontento)
        {
            mejor_descontento = d % (10^9+7); 
        }  
    }
    for (size_t i = 0; i < l.size(); i++) //para cada estudiante, considero corregir su examen
    {
        int demora_examen_actual = (l[i].first) % (10^9+7);
        t += demora_examen_actual;
        //int dint calcularDescontento(vector<pair<int,int>> &l,vector<pair<int,int>> &r, int t, int d){
    for (int i = 0; i < r.size() ; i++)
    {
        int posicion = r[i].second; //posicion del parcial que tiene peor ratio tiempo/coeficiente
        int demora_examen_actual = l[posicion].first; //demora que trae ese examen
        for (int j = 0; j < l.size(); j++)
        {   
            d += demora_examen_actual * l[j].second; 
        }
        l[posicion].first = 0;
    }
    return d;
}
escontento_estudiante = demora_examen_actual * l[i][1];
        //d+= descontento_estudiante;
        for (size_t j = i; j < l.size() ; j++) //sumo el descontento ocasionado por la espera del resto (que todavÃ­a no recibieron su examen)
        {
            d += (l[j].second * demora_examen_actual) % (10^9+7); 
        }
        //recursion: sigo corrigiendo teniendo en cuenta que acabo de corregir a este:
        pair<int,int> examen_actual = l[i];
        //caso en el que lo corregi:
        vector<pair<int,int>> l_anterior = l;   
        l.erase(l.begin() + i);
        optimizarCorreciones(l, t, d);
        //para el caso en el que no lo corregi, sigo haciendo backtracking: 
        l = l_anterior;
        //l[i-1] = examen_actual;

    }
    
}          
 */

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
    cout << "resultado es " << calcularDescontento(l, r, 0, 0) <<" "; 
    return 1;
}
