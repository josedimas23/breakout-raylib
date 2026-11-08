#include "Particula.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <assert.h>



using namespace std;

// constructor sin parametros.
// Suponemos un tamaño minimo del mundo
// y una velocidad máxima permitida

Particula::Particula() {
    x = rand() % MIN_DIM + 1;
    y = rand() % MIN_DIM + 1;

    dx = rand() % MAX_VEL + 1;
    dy = rand() % MAX_VEL + 1;
    radio = RADIO;
}

float Particula::distancia(const Particula & otra) const {
    float xx = otra.x - this->x;
    float yy = otra.y - this->y;

    return (sqrt(xx * xx + yy * yy));
}

bool Particula::colision(const Particula & otra) const {
    float d = this->distancia(otra);

    return (d < (this->radio + otra.radio));
}

float Particula::GetX() const {
    return (x);
}

float Particula::GetY() const {
    return (y);
}

float Particula::GetDX() const {
    return (dx);
}

float Particula::GetDY() const {
    return (dy);
}

float Particula::GetRadio() const {
    return (radio);
}

void Particula::SetXY(float _x, float _y) {
    x = _x;
    y = _y;
}

void Particula::SetDX(float _dx) {
    dx = _dx;
}

void Particula::SetDY(float _dy) {
    dy = _dy;
}

void Particula::ajustarPosicion(int ancho, int alto) {

    if (x >= ancho - radio)
        x = ancho - radio;
    else if (x <= radio)
        x = radio;


    if (y >= alto - radio)
        y = alto - radio;
    else if (y <= radio)
        y = radio;

}

void Particula::moverGrid(char dir, int ancho, int alto) {
    if (dir == 'U')
        y -= dy;

    if (dir == 'D')
        y += dy;

    if (dir == 'L')
        x -= dx;

    if (dir == 'R')
        x += dx;


    this->ajustarPosicion(ancho, alto);

}

void Particula::mover(int ancho, int alto) {
    x += dx;
    y += dy;
    this->ajustarPosicion(ancho, alto);
}

void Particula::rebotaBordes(int ancho, int alto) {

    if ((x >= (ancho - radio)) || (x <= radio))
        dx *= -1.0f;

    if ((y >= (alto - radio)) || (y <= radio))
        dy *= -1.0f;

}

void Particula::rotar(float posX, float posY, double rads) {
    float deltaX = x - posX;
    float deltaY = y - posY;

    x = posX + deltaX * cos(rads) - deltaY * sin(rads);
    y = posY + deltaX * sin(rads) + deltaY * cos(rads);

}

std::string Particula::toString() const {
    string s = "";
    s = "(x: " + to_string(x) + ", y: " + to_string(y) + ", ";
    s += " dx: " + to_string(dx) + ", dy: " + to_string(dy) + " R: " + to_string(radio) + ")";


    return s;
}

void Particula::intercambiaVelocidad(Particula & otra) {
    float aux_DX = otra.dx;
    float aux_DY = otra.dy;

    otra.dx = dx;
    otra.dy = dy;

    dx = aux_DX;
    dy = aux_DY;
    

}


//PARTE 2-----------------------------------------------------------------------

bool Particula::operator == (const Particula &objeto)const{
   
    bool resultado = false;
        
      if(this->distancia(objeto) < E){
        
        resultado = true;
        }

    return resultado;
    
}
//extra <<
ostream &operator << (ostream &flujo, const Particula &objeto){
    
    flujo << "X: " << objeto.GetX() << endl;
    
    flujo << "Y: " <<objeto.GetY() << endl;
    
    flujo << "DX: " << objeto.GetDX() << endl;
    
    flujo << "DY: " << objeto.GetDY() << endl;

    flujo << "RADIO: " << objeto.GetRadio() << endl;    
    
   return flujo;
   
    
}

 istream &operator>> (istream &flujo,  Particula &objeto){
    float x, y, radio, dx, dy;
    
    flujo >> x >> y >> dx >> dy >> radio;
    
    objeto = Particula(x, y, dx, dy, radio);
    
    return flujo;
    
 }