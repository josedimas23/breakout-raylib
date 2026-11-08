#include "Pintar.h"

Rectangle rectangulo(const Particula &p, float ancho, float alto){
    return { p.GetX() - ancho / 2, p.GetY() - alto / 2, ancho, alto };
}

void pintarParticula(const Particula &p, Color c){
    DrawCircleV({ p.GetX(), p.GetY() }, p.GetRadio(), c);
}

void pintarLadrillo(const Particula &p, float ancho, float alto, Color c){
    Rectangle r = rectangulo(p, ancho, alto);
    DrawRectangleRec(r, c);
    DrawRectangleLinesEx(r, 2, Fade(BLACK, 0.25f));
}

void pintarConjunto(const ConjuntoParticulas &cp, float ancho, float alto, Color c){
    for(int i = 0; i < cp.GetUtiles(); i++){
        pintarLadrillo(cp.obtieneParticula(i), ancho, alto, c);
    }
}
