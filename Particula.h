#ifndef PARTICULA_H
#define PARTICULA_H

#include <iostream>

using namespace std;


const int MAX_VEL = 5;
const int MIN_DIM = 600;
const float RADIO = 7.0;

const float E = 0.01;

class Particula {
private:
    float x, y, dx, dy;
    float radio;
    // Método privado para control de bordes. Mantiene la partícula en el rectángulo
    // (0,0) - (ancho, alto)  (sup izquierdo, inferior derecho)
    void ajustarPosicion(int ancho, int alto);

public:

    // crea una partícula con valores al azar en posicion y velocidad
    // 0 <= x, y < MIN_DIM
    // 0 <= dx, dx < MAX_VEL
    // radio fijo para la inicialización
    Particula();

    // constructor con parámetros
    Particula(float _x, float _y, float _dx, float _dy, float _r) : x(_x), y(_y), dx(_dx), dy(_dy), radio(_r) {
    };

    // Setters / Getters
    float GetX() const;
    float GetY() const;
    float GetDX()const;
    float GetDY()const;
    float GetRadio()const;

    void SetXY(float, float);
    void SetDX(float);
    void SetDY(float);

    // calcula distancia euclidea entre dos partículas
    float distancia(const Particula & otra) const;

    // detecta si dos partículas chocan
    // la distancia tiene que ser menor que la suma de sus radios
    bool colision(const Particula & otra) const;

    // controla si la partícula choca con los bordes
    // en ese caso, cambia el signo de la velocidad
    void rebotaBordes(int ancho, int alto);

    // cambia la posicion, sumándole la velocidad
    void mover(int ancho, int alto);

    // realiza un movimiento en una direccion dada
    // dir = {'U', 'D', 'L', 'R'} (arriba, abajo, izq, der)
    // recibe las dimensiones del mundo para evitar que la partícula
    // salga del mundo
    void moverGrid(char dir, int ancho, int alto);

    // rota la partícula sobre el punto (posX, posY) rads radianes
    // Si quiere transformar grados a radianes debe hacer
    // rads = grados * (M PI / 180.0). La constanteM_PI esta definida en cmath.
    void rotar(float posX, float posY, double rads);

    // transforma el contenido de la particula en un string
    std::string toString() const;

    // para simular el choque elástico entre dos partículas
    void intercambiaVelocidad(Particula & otra);

    bool operator == (const Particula &objeto) const;

    friend ostream& operator<<(ostream &flujo, const Particula & objeto);

    friend istream& operator>>(istream &flujo,  Particula & objeto);

};






#endif /* PARTICULA_H */
