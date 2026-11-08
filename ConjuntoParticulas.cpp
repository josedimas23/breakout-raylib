#include "ConjuntoParticulas.h"
#include "Particula.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <assert.h>



using namespace std;

void ConjuntoParticulas::liberar(){

    if(set != 0)
        delete [] set;
    set = 0;
}

Particula * ConjuntoParticulas::reservar(int maximoGrado){

  liberar();
  Particula * espacio = new Particula[maximoGrado];

  return espacio;

}

//constructor sin parametros
ConjuntoParticulas::ConjuntoParticulas(){
    this->capacidad = 0;
    this->utiles = 0;
    this->set = new Particula[capacidad];
}

//constructor copia

ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas & objeto) {

    capacidad = objeto.capacidad;

    utiles = objeto.utiles;

    set = new Particula[capacidad];



    for(int i = 0; i < utiles; i++){

        set[i] = objeto.set[i];
    }

}

//destructor
ConjuntoParticulas::~ConjuntoParticulas(){
    liberar();
}
//gets
int ConjuntoParticulas::GetUtiles() const {
    return utiles;
}

int ConjuntoParticulas::GetCapacidad() const {
    return capacidad;
}

//agregaParticula: agrega una partı́cula al conjunto
void ConjuntoParticulas::agregaParticula(const Particula nueva){

    if(capacidad == utiles){

        capacidad += TAM_BLOQUE; //redimensionar
        Particula *set2 = new Particula[capacidad];

        for(int i = 0;i < utiles; i++){

            set2[i]=set[i];    // ajustando el tamaño del nuevo set2 con el anterior

        }
        liberar();
        set = set2;

    }
    set[utiles] = nueva;
    utiles++;
}

//borraParticula
void ConjuntoParticulas::borraParticula(int pos){

    for(int i = pos; i < utiles - 1; i++){

        set[i] = set[i+1];
    }
    utiles--;

    if((capacidad - utiles) >TAM_BLOQUE){

        capacidad = GetCapacidad() - TAM_BLOQUE;

        Particula *set3 = new Particula[capacidad];
        for(int i = 0;i < utiles; i++){

            set3[i]=set[i];    // ajustando el tamaño del nuevo set2 con el anterior

        }
        liberar();

        set = set3;
    }
}

//obtieneParticula: devuelve la partı́cula de una posición dada
//con refencia si la puedes modificar en forma de copia
Particula ConjuntoParticulas::obtieneParticula(int pos) const{
    assert(pos >= 0 && pos < utiles);
    return set[pos];
}

//reemplazaParticula: reemplaza la partı́cula de una posición dada con otra.
void ConjuntoParticulas::reemplazaParticula(int pos,const Particula part2){

    if(pos >= 0 && pos < utiles)
        set[pos] = part2;
}

//moverParticulas: recibe como parámetros los valores de ancho y alto en los que las partı́culas se pueden mover.
void ConjuntoParticulas::mover(int ancho, int alto){

    for(int i = 0; i < utiles; i++){

        set[i].mover(ancho, alto);

    }

}

/*rebotar: recibe como parámetros los valores de ancho y alto
en los que las partı́culas se pueden mover. Luego, aplica a cada
partı́cula el método rebotaBordes.
*/
void ConjuntoParticulas::rebotar(int ancho, int alto){

    for(int i = 0; i < utiles; i++){

        set[i].rebotaBordes(ancho, alto);

    }
}
/*mostrarInfo: muestra por pantalla los valores de capacidad
y utiles, y luego los datos de cada partı́cula */
void ConjuntoParticulas::mostrarInfo(){

    cout << "Utiles: "<< GetUtiles() << " ";
    cout << "Capacidad:" << GetCapacidad();

    for(int i = 0; i < utiles; i++){
        cout << set[i].toString() << endl;

    }
}

//parte 2--------------- arriba he declarado el de constructor copia------------

ConjuntoParticulas &ConjuntoParticulas::operator =(const ConjuntoParticulas & objeto){

    liberar();

    capacidad = objeto.capacidad;
    utiles = objeto.utiles;

    set = reservar(objeto.GetCapacidad());

    for(int i = 0; i < utiles; i++){

        set[i] = objeto.set[i];
    }

    return *this;
}

ostream& operator<<(ostream &flujo, const ConjuntoParticulas & objeto){

    flujo << objeto.GetCapacidad()<< endl;
    flujo << objeto.GetUtiles() <<endl;



    for(int i = 0; i < objeto.GetUtiles(); i++){

        flujo << objeto.obtieneParticula(i).toString() ;
    }

    return flujo;
}

Particula & ConjuntoParticulas::operator[](int indice){

    assert(indice >= 0);
    if(indice > capacidad){

        cout << "error" << endl;

    }
    return set[indice];

}

const Particula & ConjuntoParticulas::operator[](int indice) const{

    assert(indice >= 0);
    if(indice > capacidad){

        cout << "error" << endl;

    }
    return set[indice];

}

ConjuntoParticulas& ConjuntoParticulas::operator+(const Particula &objeto){

    agregaParticula(objeto);

    return *this;

}

bool ConjuntoParticulas::operator == (const ConjuntoParticulas &objeto)const{

    bool resultado = false;

        if(utiles == objeto.utiles){

            int cont = 0;

            for(int i = 0; i < utiles; i++){


                for(int j = 0; j < utiles; j++){

                    if(set[i] == objeto.set[j]){

                        cont++;
                        j = utiles;
                    }
                }

            }
            if(cont == utiles){

                resultado = true;
            }
        }

    return resultado;

}

int ConjuntoParticulas::distanciaPromedio(Particula p) const{

    int distan = 0;

    for(int i = 0; i < utiles; i++){

        distan += (*this)[i].distancia(p);
    }

    distan = distan / utiles;

    return distan;

}

bool ConjuntoParticulas::operator < (const ConjuntoParticulas & cp2){

    bool menor = false;

    Particula cp(0, 0, 0, 0, 0);
    if(distanciaPromedio(cp) < cp2.distanciaPromedio(cp)){

        menor = true;
    }

    return menor;
}
