/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Pintar.h
 * Author: josedsc23
 *
 * Created on 23 de mayo de 2022, 18:05
*/

#ifndef PINTAR_H
#define PINTAR_H

#include <iostream>
#include "Particula.h"
#include "ConjuntoParticulas.h"
#include "raylib.h"


void pintarParticula( const Particula &p, Color c);

void pintarLadrillo( const Particula &p,int ancho, int alto, Color c);

void pintarConjunto( const ConjuntoParticulas &cp, Color c);





#endif /* PINTAR_H */

