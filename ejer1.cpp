#include <iostream>
#include <vector>

using namespace std;

int caminoMinimo;
int caminoMaximo;
int inf = 121;
int n;
int m;
int i_0;
int j_0;

bool enRango(int i, int j){
    return (0 <= i && i < n && 0 <= j && j < m);
}

char deDondeVengo(vector<vector<pair<char, int>>> &tablero, int i, int j){
    char res;
    char signoDelCualVengo = tablero[i_0][j_0].first;
    int rotDelSignoDelQueVengo = tablero[i_0][j_0].second;

    //ahora estudio cada caso
    if (signoDelCualVengo == 'L'){
        if(rotDelSignoDelQueVengo % 4 == 0){ //o bien vengo del norte o bien vengo del oeste
            if (i_0 == i && j_0 == j-1) res = 'W';
            if (i_0 == i-1 && j_0 == j) res = 'N';
        } else if (rotDelSignoDelQueVengo % 4 == 1) { //o bien vengo del sur o bien vengo del oeste
            if (i_0 == i && j_0 == j-1) res = 'W';
            if (i_0 == i+1 && j_0 == j) res = 'S';
        } else if (rotDelSignoDelQueVengo % 4 == 2) { //o bien vengo del sur o bien vengo del este
            if (i_0 == i && j_0 == j+1) res = 'E';
            if (i_0 == i+1 && j_0 == j) res = 'S';
        } else {                                    //o bien vengo del norte o bien vengo del este
            if (i_0 == i && j_0 == j+1) res = 'E';
            if (i_0 == i-1 && j_0 == j) res = 'N';
        }
    } else if (signoDelCualVengo == 'I'){
        if(rotDelSignoDelQueVengo % 2 == 0){ //o bien vengo del norte o bien vengo del sur
            if (i_0 == i+1 && j_0 == j) res = 'S';
            if (i_0 == i-1 && j_0 == j) res = 'N';            
        } else {                           //o bien vengo del norte o bien vengo del sur
            if (i_0 == i && j_0 == j+1) res = 'E';
            if (i_0 == i && j_0 == j-1) res = 'W';
        }  
    } else { //signo del cual vengo e sun '+' entonces vengo si o si de ahi pues no hay rotaciones
        if (i_0 == i+1 && j_0 == j) res = 'S';
        if (i_0 == i-1 && j_0 == j) res = 'N';
        if (i_0 == i && j_0 == j+1) res = 'E';
        if (i_0 == i && j_0 == j-1) res = 'W';
    }

    return res;
}

bool senderos(vector<vector<pair<char, int>>> &tablero, int i, int j, int l){        
    bool res = false;

    //caso base: llegue a un final invalido
    if(tablero[i][j].first == *"?") return false;   //ya pase por esta casilla
    if(tablero[i][j].first == *"#") return false;  //me tope con un #
    if((i == 0 || i == n-1) && j == j_0 - 1) return false; //en las primera y ultima filas no puedo ir al oeste
    if((j == 0 || j == m-1) && i == i_0 - 1) return false; //en las primera y ultima columnas no puedo ir al norte
    

    //caso base: llegue al final del tablero
    if(i==n-1 && j==m-1) {
        caminoMaximo = max(l, caminoMaximo);
        caminoMinimo = min(l, caminoMinimo);
        return true;
    }


    //llamados recursivos
    char signoAnterior = tablero[i][j].first; 
    tablero[i][j].first = *"?";
    int rotacionAnterior = tablero[i][j].second;
    bool norte = false;
    bool sur = false;
    bool este = false; 
    bool oeste = false;
    int i0Anterior = i_0;
    int j0Anterior = j_0;

    //aca tengo que estudiar de que direccion estoy viniendo:
    char vengo;
    bool avanzoIgual = false;
    if(i_0 != -1 && j_0 != -1) vengo = deDondeVengo(tablero, i, j);
    if(i_0 == -1 && j_0 == -1) avanzoIgual = true;

    //avanzo en el arbol recursivo:
    i_0 = i;
    j_0 = j;

    if(signoAnterior == *"L"){
        for(int k = 0; k < 4; k++){
            if(tablero[i][j].second % 4 == 0 && vengo == *"N" || avanzoIgual){ //puedo moverme al este
                if(enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
            }
            if(tablero[i][j].second % 4 == 0 && vengo == *"E" || avanzoIgual) {  //puedo moverme al norte
                if(enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            }
            if(tablero[i][j].second % 4 == 1 && vengo == *"S" || avanzoIgual){ //puedo moverme al este
                if(enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
            }
            if(tablero[i][j].second % 4 == 1 && vengo == *"E" || avanzoIgual){ //puedo moverme al sur
                if(enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            }            
            if(tablero[i][j].second % 4 == 2 && vengo == *"W" || avanzoIgual){ //puedo moverme al sur
                if(enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            } 
            if(tablero[i][j].second % 4 == 2 && vengo == *"S" || avanzoIgual){ //puedo moverme al oeste
                if(enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
            }
            if(tablero[i][j].second % 4 == 3 && vengo == *"W" || avanzoIgual){ //puedo moverme al norte
                if(enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            }
            if(tablero[i][j].second % 4 == 3 && vengo == *"N" || avanzoIgual){ //puedo moverme al oeste
                if(enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"I") {
        for(int k = 0; k < 2; k++){ 
            if(tablero[i][j].second % 2 == 0 && vengo == *"N" || avanzoIgual){ //puedo moverme al sur
                if(enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            } 
            if(tablero[i][j].second % 2 == 0 && vengo == *"S" || avanzoIgual){ //puedo moverme al norte
                if(enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            }
            if(tablero[i][j].second % 2 == 1 && vengo == *"W" || avanzoIgual){ //puedo moverme al este
                if(enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
            }
            if(tablero[i][j].second % 2 == 1 && vengo == *"E" || avanzoIgual){ //puedo moverme al oeste
                if(enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
            }
            //aplico la rotacion para que avance en el proximo llamado:
            tablero[i][j].second++;
        }
    } else if (signoAnterior == *"+") {//en este caso es indistinto rotar, pero tengo que verificar de donde vengo
        if(vengo == *"N" || avanzoIgual){ //avanzo hacia S;E;W;
            if (enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            if (enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
            if (enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
        }
        if(vengo == *"E" || avanzoIgual){ //avanzo N;S;W
            if (enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            if (enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            if (enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
        }
        if(vengo == *"S" || avanzoIgual){ //avanzo N;E;W
            if (enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
            if (enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            if (enRango(i, j-1) && tablero[i][j-1].first != *"?") oeste = senderos(tablero, i, j-1, l+1);
        }
        if(vengo == *"W" || avanzoIgual){ //avanzo N;S;E
            if (enRango(i+1, j) && tablero[i+1][j].first != *"?") sur = senderos(tablero, i+1, j, l+1);
            if (enRango(i-1, j) && tablero[i-1][j].first != *"?") norte = senderos(tablero, i-1, j, l+1);
            if (enRango(i, j+1) && tablero[i][j+1].first != *"?") este = senderos(tablero, i, j+1, l+1);
        }
    }

    res = res || norte || este || sur || oeste;

    //backtracking
    tablero[i][j].first = signoAnterior;
    tablero[i][j].second = rotacionAnterior;
    i_0 = i0Anterior;
    j_0 = j0Anterior;
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
        i_0 = -1;
        j_0 = -1;
        if (senderos(tablero, 0, 0, 0)){
            cout << "POSIBLE " << caminoMinimo << " " << caminoMaximo;
        } else {
            cout << "IMPOSIBLE";
        }
        cout << endl;

    }    
        return 0;
}
