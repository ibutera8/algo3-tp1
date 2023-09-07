#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int caminoMinimo; 
int caminoMaximo;
int inf = std::numeric_limits<int>::max();
//int largoActual;
//int pasosTotales;



bool senderos(vector<vector<pair<char, int>>> &tablero, int i, int j, int l){    
    if(l == 12 && i == 3 && j == 3) cout << "ACAAAAAAA" << caminoMaximo << endl;
    
    int n = tablero.size();
    int m = tablero[0].size();
    bool res = false;

    //caso base: llegue a un final invalido (x/ej un costado del tablero o un #)
    if((i>=n && j<m) || (i<n && j>=m)) return false;
    if(i < 0 || j < 0) return false;
    if (l > n*m) return false;
    if(tablero[i][j].first == *"#") return false;

    //caso base: llegue al final del tablero
    if(i==n-1 && j==m-1) {
        if (l < caminoMinimo) {
            caminoMinimo = l;
        }
        if (l > caminoMaximo) {
            caminoMaximo = l;
        }
        return true;
    }
    //llamados recursivos
    //largoActual++;
    char signoAnterior = tablero[i][j].first; 
    tablero[i][j].first = *"#";
    int rotacionAnterior = tablero[i][j].second;
    bool norte, sur, este, oeste;
    if(signoAnterior == *"L"){
        for(int k = 0; k < 4; k++){
            if(tablero[i][j].second % 4 == 0){
                //puedo moverme al N o E
                norte = senderos(tablero, i-1, j, l+1);
                este = senderos(tablero, i, j+1, l+1);
                res = res || norte || este;
            } else if(tablero[i][j].second % 4 == 1){
                //puedo moverme al S o E
                sur = senderos(tablero, i+1, j, l+1);
                este = senderos(tablero, i, j+1, l+1);
                res = res || sur || este;
            } else if(tablero[i][j].second % 4 == 2){
                //puedo moverme al O o S
                sur = senderos(tablero, i+1, j, l+1);
                oeste = senderos(tablero, i, j-1, l+1);
                res = res || sur || oeste; 
            } else if(tablero[i][j].second % 4 == 3){
                //puedo moverme al O o N
                norte = senderos(tablero, i-1, j, l+1);
                oeste = senderos(tablero, i, j-1, l+1);
                res = res || norte || oeste;
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"I") {
        for(int k = 0; k < 2; k++){ 
            if(tablero[i][j].second % 2 == 0){
                //puedo moverme al N o S
                norte = senderos(tablero, i+1, j, l+1);
                sur = senderos(tablero, i-1, j, l+1);
                res = res || norte || sur;
            } else if(tablero[i][j].second % 2 == 1){
                //puedo moverme al O o E
                este = senderos(tablero, i, j+1, l+1);
                oeste = senderos(tablero, i, j-1, l+1);
                res = res || este || oeste;
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"+") {
        //en este caso es indistinto rotar
        sur = senderos(tablero, i+1, j, l+1);
        norte = senderos(tablero, i-1, j, l+1);
        este = senderos(tablero, i, j+1, l+1);
        oeste = senderos(tablero, i, j-1, l+1);
        res = res || sur || norte || este || oeste;
    }

    //backtracking
    tablero[i][j].first = signoAnterior;
    tablero[i][j].second = rotacionAnterior;
    //largoActual--;
    return res;

}

int main(){
    int cant_tests;
    cin >> cant_tests;
    for (int k = 0; k < cant_tests; k++){
        caminoMinimo = inf; 
        caminoMaximo = -inf;
        //largoActual = 0;
        int filas, columnas;
        cin >> filas;
        cin >> columnas;
        vector<vector<pair<char, int>>> tablero(filas, vector<pair<char, int>>(columnas));
        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                char signo;
                cin >> signo;
                tablero[i][j] = make_pair(signo, 0);
            }
        }

        if (senderos(tablero, 0, 0, 0)){
            cout << "POSIBLE " << caminoMinimo << " " << caminoMaximo;
        } else {
            cout << "IMPOSIBLE";
        }
        cout << endl;

    }    
        return 0;
}
