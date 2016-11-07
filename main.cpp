#include <iostream>
#include "sha1.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <sstream>

using namespace std;

/* El especialista tecnologico del escuadron de John Connor  */
/* ha estado trabajando en debuggear el codigo de los T1000. */
/* Hasta ahora, solo hemos podido des-ensamblar la siguiente */
/* estructura, que forma parte de dicho codigo.              */
struct cap_t {
    string essid;
    int power;
    string hash;
};




/* Main function de nuestro trabajo. Muerte a los T1000!!!   */
/* Se puede ver que el codigo que nos enviaron en el main    */
/* solo sirve para testear un hash, y nosotros debemos       */
/* testear muchos, para poder encontrar las passwords!       */
/* Sientanse en la libertad de borrar lo que hay abajo y     */
/* reescribir lo que sea necesario para salvar a John Connor */
int main(int argc, char *argv[]) {

    ifstream myReadFile("/home/mnehmad/batcave/tallerT1000/src/text/spanish.dic");
    string line;
    vector<pair<string, string> > palabrasySusHashes;

    if (myReadFile.is_open()) {
        while (getline(myReadFile, line) && !myReadFile.eof()) {
            string palabraActual = line;
            string hashActual = sha1(palabraActual);
            pair<string, string> palabraYHash = make_pair(palabraActual, hashActual);
            palabrasySusHashes.push_back(palabraYHash);
//            cout << palabrasySusHashes[0].second;
        }
        myReadFile.close();
    }

    std::vector<cap_t> los_handshakes;

    ifstream handshakes("/home/mnehmad/batcave/tallerT1000/src/text/handshakes.lst");
    string line2;
    if (handshakes.is_open()) {
        while (getline(handshakes, line2, ';') && !handshakes.eof()) {
            istringstream hand_actual(line2);
            hand_actual.ignore(1);
            cap_t cap_actual;

            getline(hand_actual, cap_actual.essid, ',');
            string powerString;
            getline(hand_actual, powerString, ',');
            cap_actual.power = stoi(powerString);
            getline(hand_actual, cap_actual.hash, ']');

            los_handshakes.push_back(cap_actual);
        }
        myReadFile.close();
    }

    struct nombrePalabraHashYPower {
        string nombre;
        string palabra;
        string hash;
        int power;
    };

    std::vector<nombrePalabraHashYPower> chorizoDePasswords;

    unsigned long n = palabrasySusHashes.size();
    unsigned long m = los_handshakes.size();

    unsigned long i = 0;

    while (i < n) {
        unsigned long j = 0;

        while (j < m) {
            cap_t actual = los_handshakes[j];
            if (palabrasySusHashes[i].second == actual.hash) {
                nombrePalabraHashYPower chorizoActual;
                chorizoActual.nombre = actual.essid;
                chorizoActual.palabra = palabrasySusHashes[i].first;
                chorizoActual.hash = palabrasySusHashes[i].second;
                chorizoActual.power = actual.power;

                chorizoDePasswords.push_back(chorizoActual);
                cout << chorizoActual.nombre << ' ' << chorizoActual.palabra<< endl;
            }
            j++;
        }
        i++;
    }


    cap_t cap; // instancia vacia de captura
    int pow;
    string aux, aux2;

    cout << "Ingrese nombre de wifi: " << endl;
    cin >> aux;
    cout << "Ingrese power: " << endl;
    cin >> pow;
    cout << "Ingrese password a hashear: " << endl;
    cin >> aux2;
    cap.essid = aux;
    cap.power = pow;


    /*****     Aca ocurre la magia    *****/
    /* utilizando el codigo objeto sha1.o */
    /* podemos acceder a la funcion sha1  */
    /* que los T1000 utilizan para armar  */
    /* los hashes de sus WiFi             */
    cap.hash = sha1(aux2);
    /**************************************/

    // El problema es que la comparacion es a ojo, y de a un hash a la vez. Habra alguna forma de mejorar esto?
    cout << "El handshake resultante es: [" << cap.essid << ", " << cap.power << ", " << cap.hash << "]" << endl;

    /* Comunicado: John Connor en peligro! Bateria baja. ayud... <<EOF>> */
    return 0;
}
