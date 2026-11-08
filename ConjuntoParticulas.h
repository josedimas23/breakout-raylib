#ifndef CONJUNTOPARTICULAS_H
#define CONJUNTOPARTICULAS_H

#include <iostream>
#include "Particula.h"
#include <assert.h>

using namespace std;

const int TAM_BLOQUE=3;
        
class ConjuntoParticulas{
private:
    
    Particula *set;
    int capacidad;
    int utiles;
    Particula aux3;
    
    void liberar();
    Particula * reservar(int maximoGrado);
    
public:
    
    //constructor sin parametros
    ConjuntoParticulas();
    
    //constructor con parametros
     ConjuntoParticulas(int N){
         
     if(N > 0){
         
     this->capacidad = N;
     this->utiles = N;
     this->set = new Particula[capacidad]; 
         
     }
    };
    
    //constructor de copia
    ConjuntoParticulas(const ConjuntoParticulas & objeto) ;
    
    //destructor
    ~ConjuntoParticulas();
    
    int GetCapacidad() const;
    
    int GetUtiles() const;
    
    void agregaParticula(const Particula nueva);
    
    void borraParticula(int pos);
 
    Particula obtieneParticula(int pos) const;
    
    void reemplazaParticula(int pos,const Particula part2);
    
    void mover(int ancho, int alto);
    
    void rebotar(int ancho, int alto);
    
    void mostrarInfo();
    
    ConjuntoParticulas & operator = (const ConjuntoParticulas & objeto);
    
    Particula & operator[](int indice);
      
    const Particula & operator[](int indice) const;
    
    ConjuntoParticulas & operator+(const Particula &objeto);
    
    bool operator == (const ConjuntoParticulas &objeto) const;
    
    int distanciaPromedio(Particula p) const;
    
    bool  operator < (const ConjuntoParticulas & cp2);
    
    friend ostream& operator<<(ostream &flujo, const ConjuntoParticulas & objeto);
     
};

 #endif /* CONJUNTOPARTICULAS_H */   







