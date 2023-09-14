#include <iostream>
#include <vector>

using namespace std;

int caminoMinimo; 
int caminoMaximo;
int inf = 121;
int n;
int m;
int io;
int jo;

bool enRango(int i, int j){
    return (0 <= i && i < n && 0 <= j && j < m);
}

bool senderos(vector<vector<pair<char, int>>> &tablero, int i, int j, int l){    
    if (l == 6) {
        int caca = 0;
    }
    
    bool res = false;

    //caso base: llegue a un final invalido
    if(tablero[i][j].first == *"#") return false;  //me tope con un #
    if((i == 0 || i == n-1) && j == jo - 1) return false; //en las primera y ultima filas no puedo ir al oeste
    if((j == 0 || j == m-1) && i == io - 1) return false; //en las primera y ultima columnas no puedo ir al norte
    

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
    char signoAnterior = tablero[i][j].first; 
    tablero[i][j].first = *"#";
    int rotacionAnterior = tablero[i][j].second;
    bool norte = false;
    bool sur = false;
    bool este = false; 
    bool oeste = false;
    int ioAnterior = io;
    int joAnterior = jo;
    io = i;
    jo = j;
    if(signoAnterior == *"L"){
        for(int k = 0; k < 4; k++){
            if(tablero[i][j].second % 4 == 0){
                //puedo moverme al N o E
                if (enRango(i-1, j) && tablero[i-1][j].first != *"#") norte = senderos(tablero, i-1, j, l+1);
                if (enRango(i, j+1) && tablero[i][j+1].first != *"#") este = senderos(tablero, i, j+1, l+1);
                res = res || norte || este;
            } else if(tablero[i][j].second % 4 == 1){
                //puedo moverme al S o E
                if (enRango(i+1, j) && tablero[i+1][j].first != *"#") sur = senderos(tablero, i+1, j, l+1);
                if (enRango(i, j+1) && tablero[i][j+1].first != *"#") este = senderos(tablero, i, j+1, l+1);
                res = res || sur || este;
            } else if(tablero[i][j].second % 4 == 2){
                //puedo moverme al O o S
                if (enRango(i+1, j) && tablero[i+1][j].first != *"#") sur = senderos(tablero, i+1, j, l+1);
                if (enRango(i, j-1) && tablero[i][j-1].first != *"#") oeste = senderos(tablero, i, j-1, l+1);
                res = res || sur || oeste; 
            } else if(tablero[i][j].second % 4 == 3){
                //puedo moverme al O o N
                if (enRango(i-1, j) && tablero[i-1][j].first != *"#") norte = senderos(tablero, i-1, j, l+1);
                if (enRango(i, j-1) && tablero[i][j-1].first != *"#") oeste = senderos(tablero, i, j-1, l+1);
                res = res || norte || oeste;
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"I") {
        for(int k = 0; k < 2; k++){ 
            if(tablero[i][j].second % 2 == 0){
                //puedo moverme al N o S
                if (enRango(i-1, j) && tablero[i-1][j].first != *"#") norte = senderos(tablero, i-1, j, l+1);
                if (enRango(i+1, j) && tablero[i+1][j].first != *"#") sur = senderos(tablero, i+1, j, l+1);
                res = res || norte || sur;
            } else if(tablero[i][j].second % 2 == 1){
                //puedo moverme al O o E
                if (enRango(i, j+1) && tablero[i][j+1].first != *"#") este = senderos(tablero, i, j+1, l+1);
                if (enRango(i, j-1) && tablero[i][j-1].first != *"#") oeste = senderos(tablero, i, j-1, l+1);
                res = res || este || oeste;
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"+") {
        //en este caso es indistinto rotar
        if (enRango(i-1, j) && tablero[i-1][j].first != *"#") norte = senderos(tablero, i-1, j, l+1);
        if (enRango(i+1, j) && tablero[i+1][j].first != *"#") sur = senderos(tablero, i+1, j, l+1);
        if (enRango(i, j+1) && tablero[i][j+1].first != *"#") este = senderos(tablero, i, j+1, l+1);
        if (enRango(i, j-1) && tablero[i][j-1].first != *"#") oeste = senderos(tablero, i, j-1, l+1);
        res = res || sur || norte || este || oeste;
    }

    //backtracking
    tablero[i][j].first = signoAnterior;
    tablero[i][j].second = rotacionAnterior;
    io = ioAnterior;
    jo = joAnterior;
    return res;

}

int main(){
    int cant_tests;
    cin >> cant_tests;
    for (int k = 0; k < cant_tests; k++){
        caminoMinimo = inf; 
        caminoMaximo = 0;
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
        n = tablero.size();
        m = tablero[0].size();
        io = -1;
        jo = -1;
        if (senderos(tablero, 0, 0, 0)){
            cout << "POSIBLE " << caminoMinimo << " " << caminoMaximo;
        } else {
            cout << "IMPOSIBLE";
        }
        cout << endl;

    }    
        return 0;
}
