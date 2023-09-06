#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int caminoMinimo; 
int caminoMaximo;
int largoActual;
int pasosTotales;



bool senderos(vector<vector<pair<char, int>>> &tablero, int i, int j){
    int n = tablero.size();
    int m = tablero[0].size();
    bool res = false;
    
    if(largoActual == 16 || caminoMaximo == 16 || caminoMinimo == 16){
        cout << i << " " << j << endl;
    }
    //caso base: llegue a un final invalido (x/ej un costado del tablero o un #)
    if((i==n && j!=m) || (i!=n && j==m)) return false;
    if(i < 0 || j < 0) return false;
    if(tablero[i][j].first == *"#") return false;
    if (pasosTotales > n*m) return false;

    //caso base: llegue al final del tablero
    if(i==n-1 && j==m-1) {
        caminoMaximo = max(caminoMaximo, largoActual);
        caminoMinimo = min(caminoMinimo, largoActual);
        return true;
    }
    
    //llamados recursivos
    // HAY QUE REESCBRIBIR LOS LLAMADOS RECURSIVOS
    int largoViejo = largoActual;
    largoActual++;
    pasosTotales++;
    //char signoAnterior = tablero[i][j].first; 
    //tablero[i][j].first = *"#";
    if(tablero[i][j].first == *"L"){
        int rotVieja = tablero[i][j].second;
        for(int k = 0; k < 4; k++){
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
            if(tablero[i][j].second % 4 == 0){
                //puedo moverme al N o E
                res = res || (senderos(tablero, i, j+1) || senderos(tablero, i-1, j));
            } else if(tablero[i][j].second % 4 == 1){
                //puedo moverme al S o E
                res = res || (senderos(tablero, i+1, j) || senderos(tablero, i, j+1));
            } else if(tablero[i][j].second % 4 == 2){
                //puedo moverme al O o S
                res = res || (senderos(tablero, i, j-1) || senderos(tablero, i+1, j));
            } else if(tablero[i][j].second % 4 == 3){
                //puedo moverme al O o N
                res = res || (senderos(tablero, i, j-1) || senderos(tablero, i-1, j));
            }
        }
        //backtracking
        //tablero[i][j].first = signoAnterior;
        tablero[i][j].second = rotVieja;

    } else if (tablero[i][j].first == *"I") {
        int rotVieja = tablero[i][j].second;
        //char signoAnterior = tablero[i][j].first; 
        //tablero[i][j].first = *"#";
        for(int k = 0; k < 2; k++){
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
            if(tablero[i][j].second % 2 == 0){
                //puedo moverme al N o S
                res = res || (senderos(tablero, i+1, j) || senderos(tablero, i-1, j));
            } else if(tablero[i][j].second % 2 == 1){
                //puedo moverme al O o E
                res = res || (senderos(tablero, i, j-1) || senderos(tablero, i, j+1));
            }
        }
        //backtracking
        //tablero[i][j].first = signoAnterior;
        tablero[i][j].second = rotVieja;

    } else if (tablero[i][j].first == *"+") {
        //en este caso es indistinto rotar
        //char signoAnterior = tablero[i][j].first; 
        //tablero[i][j].first = *"#";
        res = res || ((senderos(tablero, i+1, j) || senderos(tablero, i-1, j)) || (senderos(tablero, i, j-1) || senderos(tablero, i, j+1)));
        //tablero[i][j].first = signoAnterior;
    }

    //backtracking
    largoActual = largoViejo;
    pasosTotales--;
    return res;

}

int main(){
    int cant_tests;
    cin >> cant_tests;
    for (int k = 0; k < cant_tests; k++){
        caminoMinimo = std::numeric_limits<int>::max(); 
        caminoMaximo = 0;
        largoActual = 0;
        pasosTotales = 0;
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

        if (senderos(tablero, 0,0)){
            cout << "POSIBLE " << caminoMinimo << " " << caminoMaximo;
        } else {
            cout << "IMPOSIBLE";
        }
        cout << endl;

    }    
        return 0;
}
