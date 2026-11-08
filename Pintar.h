// Funciones de dibujo con raylib para partículas y ladrillos.

#ifndef PINTAR_H
#define PINTAR_H

#include "Particula.h"
#include "ConjuntoParticulas.h"
#include "raylib.h"

// Rectángulo de ancho x alto centrado en la posición de la partícula.
Rectangle rectangulo(const Particula &p, float ancho, float alto);

// Dibuja la partícula como un círculo centrado en su posición.
void pintarParticula(const Particula &p, Color c);

// Dibuja la partícula como un rectángulo centrado en su posición.
void pintarLadrillo(const Particula &p, float ancho, float alto, Color c);

// Dibuja todas las partículas del conjunto como ladrillos.
void pintarConjunto(const ConjuntoParticulas &cp, float ancho, float alto, Color c);

#endif /* PINTAR_H */
