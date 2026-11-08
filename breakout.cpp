#include "raylib.h"
#include "Particula.h"
#include "ConjuntoParticulas.h"
#include "Pintar.h"
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

// Ventana
const int screenWidth = 800;
const int screenHeight = 600;

// Pared de ladrillos: FILAS x COLUMNAS, centrada en horizontal
const int FILAS = 5;
const int COLUMNAS = 10;
const float LADRILLO_ANCHO = 64;
const float LADRILLO_ALTO = 22;
const float LADRILLO_HUECO = 8;
const float PARED_Y = 80;
const Color COLORES_FILA[FILAS] = { RED, ORANGE, GOLD, GREEN, SKYBLUE };

// Pala
const float PALA_ANCHO = 100;
const float PALA_ALTO = 14;
const float PALA_Y = 550;
const float PALA_VEL = 7;

// Bola
const float BOLA_RADIO = 8;
const float VEL_INICIAL = 4.5f;   // píxeles por fotograma
const float VEL_MAXIMA = 8.0f;
const float ACELERACION = 0.08f;  // aumento de velocidad por ladrillo roto
const float ANGULO_MAX = 60 * DEG2RAD; // rebote máximo respecto a la vertical

const int VIDAS = 3;

enum Estado { LISTO, JUGANDO, GANADO, PERDIDO };

char Direccion(){
    char dir = ' ';

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        dir = 'R';

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        dir = 'L';

    return dir;
}

void crearPared(ConjuntoParticulas pared[]){
    float anchoPared = COLUMNAS * LADRILLO_ANCHO + (COLUMNAS - 1) * LADRILLO_HUECO;
    float x0 = (screenWidth - anchoPared) / 2 + LADRILLO_ANCHO / 2;

    for(int i = 0; i < FILAS; i++){
        pared[i] = ConjuntoParticulas();
        float y = PARED_Y + i * (LADRILLO_ALTO + LADRILLO_HUECO);

        for(int j = 0; j < COLUMNAS; j++){
            float x = x0 + j * (LADRILLO_ANCHO + LADRILLO_HUECO);
            pared[i] + Particula(x, y, 0, 0, LADRILLO_ALTO / 2);
        }
    }
}

int ladrillosRestantes(const ConjuntoParticulas pared[]){
    int total = 0;
    for(int i = 0; i < FILAS; i++)
        total += pared[i].GetUtiles();
    return total;
}

float velocidad(const Particula &bola){
    return hypotf(bola.GetDX(), bola.GetDY());
}

// Fija la velocidad de la bola a partir de un ángulo medido desde la vertical
// (negativo = izquierda, positivo = derecha). La bola siempre sube.
void lanzarConAngulo(Particula &bola, float angulo, float vel){
    bola.SetDX(vel * sinf(angulo));
    bola.SetDY(-vel * cosf(angulo));
}

void colocarSobrePala(Particula &bola, const Particula &pala){
    bola.SetXY(pala.GetX(), PALA_Y - PALA_ALTO / 2 - BOLA_RADIO - 1);
    bola.SetDX(0);
    bola.SetDY(0);
}

void textoCentrado(const char *texto, int y, int tam, Color c){
    DrawText(texto, (screenWidth - MeasureText(texto, tam)) / 2, y, tam, c);
}

int main() {

    InitWindow(screenWidth, screenHeight, "Breakout");
    SetTargetFPS(60);

    ConjuntoParticulas pared[FILAS];

    // El radio de la pala es medio ancho: así ajustarPosicion la mantiene dentro de la ventana.
    Particula pala(screenWidth / 2.0f, PALA_Y, PALA_VEL, 0, PALA_ANCHO / 2);
    Particula bola(0, 0, 0, 0, BOLA_RADIO);

    Estado estado = LISTO;
    int vidas = VIDAS;
    int puntos = 0;

    crearPared(pared);
    colocarSobrePala(bola, pala);

    while (!WindowShouldClose()){

        // ---------- Actualizar ----------
        if (estado == GANADO || estado == PERDIDO){
            if (IsKeyPressed(KEY_R)){
                crearPared(pared);
                vidas = VIDAS;
                puntos = 0;
                pala.SetXY(screenWidth / 2.0f, PALA_Y);
                colocarSobrePala(bola, pala);
                estado = LISTO;
            }
        }
        else {
            pala.moverGrid(Direccion(), screenWidth, screenHeight);
        }

        if (estado == LISTO){
            colocarSobrePala(bola, pala);

            if (IsKeyPressed(KEY_SPACE)){
                // Ángulo aleatorio entre 20 y 50 grados, hacia la izquierda o la derecha
                float angulo = GetRandomValue(20, 50) * DEG2RAD;
                if (GetRandomValue(0, 1) == 0)
                    angulo = -angulo;
                lanzarConAngulo(bola, angulo, VEL_INICIAL);
                estado = JUGANDO;
            }
        }
        else if (estado == JUGANDO){
            float xAnterior = bola.GetX();

            bola.mover(screenWidth, screenHeight);

            // La bola ha llegado al fondo: se pierde una vida
            if (bola.GetY() >= screenHeight - BOLA_RADIO){
                vidas--;
                estado = (vidas > 0) ? LISTO : PERDIDO;
                colocarSobrePala(bola, pala);
            }
            else {
                bola.rebotaBordes(screenWidth, screenHeight);

                Vector2 centro = { bola.GetX(), bola.GetY() };

                // Pala: el punto de impacto decide el ángulo de salida
                Rectangle rPala = rectangulo(pala, PALA_ANCHO, PALA_ALTO);
                if (bola.GetDY() > 0 && CheckCollisionCircleRec(centro, BOLA_RADIO, rPala)){
                    float relativo = (bola.GetX() - pala.GetX()) / (PALA_ANCHO / 2);
                    relativo = clamp(relativo, -1.0f, 1.0f);
                    lanzarConAngulo(bola, relativo * ANGULO_MAX, velocidad(bola));
                    bola.SetXY(bola.GetX(), rPala.y - BOLA_RADIO);
                }

                // Ladrillos: como mucho uno por fotograma
                bool golpe = false;
                for(int i = FILAS - 1; i >= 0 && !golpe; i--){
                    for(int j = pared[i].GetUtiles() - 1; j >= 0 && !golpe; j--){
                        Rectangle r = rectangulo(pared[i].obtieneParticula(j), LADRILLO_ANCHO, LADRILLO_ALTO);

                        if (CheckCollisionCircleRec(centro, BOLA_RADIO, r)){
                            // Si venía desde arriba o abajo rebota en vertical; si no, en horizontal
                            if (xAnterior >= r.x && xAnterior <= r.x + r.width)
                                bola.SetDY(-bola.GetDY());
                            else
                                bola.SetDX(-bola.GetDX());

                            // Acelera un poco con cada ladrillo
                            float v = velocidad(bola);
                            float factor = min(v + ACELERACION, VEL_MAXIMA) / v;
                            bola.SetDX(bola.GetDX() * factor);
                            bola.SetDY(bola.GetDY() * factor);

                            pared[i].borraParticula(j);
                            puntos += (FILAS - i) * 10;   // las filas de arriba valen más
                            golpe = true;
                        }
                    }
                }

                if (ladrillosRestantes(pared) == 0)
                    estado = GANADO;
            }
        }

        // ---------- Dibujar ----------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for(int i = 0; i < FILAS; i++)
            pintarConjunto(pared[i], LADRILLO_ANCHO, LADRILLO_ALTO, COLORES_FILA[i]);

        pintarLadrillo(pala, PALA_ANCHO, PALA_ALTO, DARKGRAY);
        if (estado == LISTO || estado == JUGANDO)
            pintarParticula(bola, BLUE);

        DrawText(("Score: " + to_string(puntos)).c_str(), 16, 16, 20, DARKGRAY);
        string textoVidas = "Lives: " + to_string(vidas);
        DrawText(textoVidas.c_str(), screenWidth - 16 - MeasureText(textoVidas.c_str(), 20), 16, 20, DARKGRAY);

        if (estado == LISTO)
            textoCentrado("SPACE to launch  -  arrows to move  -  ESC to quit", 400, 20, GRAY);
        else if (estado == GANADO){
            textoCentrado("YOU WIN!", 330, 48, DARKGREEN);
            textoCentrado("Press R to play again", 390, 20, GRAY);
        }
        else if (estado == PERDIDO){
            textoCentrado("GAME OVER", 330, 48, MAROON);
            textoCentrado("Press R to play again", 390, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
