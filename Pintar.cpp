
#include "ConjuntoParticulas.h"
#include "Particula.h"
#include "ConjuntoParticulas.h"
#include <cmath>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include "raylib.h"


using namespace std;

void pintarParticula( const Particula &p, Color c){
    
    int rad = p.GetRadio();
    
    DrawCircle(p.GetX() - rad, p.GetY() - rad, p.GetRadio(), c);
    
}

void pintarLadrillo( const Particula &p,int ancho, int alto, Color c){
    
    DrawRectangle(p.GetX()-25, p.GetY()-10, ancho, alto, c);
    //void DrawRectangle(int posX, int posY, int ancho, int alto, Color color);
    
}

void pintarConjunto( const ConjuntoParticulas &cp, Color c){
    
    int N = cp.GetUtiles();
    
    for(int i = 0; i < N; i++){
            
        pintarLadrillo(cp.obtieneParticula(i),60 , 20,  c);

    }
}





 