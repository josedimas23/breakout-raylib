#include "raylib.h"
#include "Particula.h"
#include "ConjuntoParticulas.h"
#include "Pintar.h"
#include <cstdlib>
#include <cmath>
#include <assert.h>
#include <iostream>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
const float DESP = 4.0;

    char Direccion(){
    char dir = ' ';
    
        if (IsKeyDown(KEY_RIGHT))
            dir = 'R';
    
        if (IsKeyDown(KEY_LEFT))
            dir = 'L';

        return dir;
    }


int main(int argc, char* argv[]) {
    
    
    InitWindow(screenWidth, screenHeight, "Modulo de prueba");
    int  N = 5;
    float ladrilloX = 100;
    float ladrilloY = 55;
    
    //ConjuntoParticulas gas(N);
    
    ConjuntoParticulas pared[N];
    
    for(int i = 0; i < 5; i++){
        
        for(int j = 0; j < 10; j++){
            
            Particula rectangulo(ladrilloX, ladrilloY, 0, 0, 10);
          
            pared[i] + rectangulo;
            
            ladrilloX += 70;  //separacion de x
        }
        ladrilloX = 100;  
        ladrilloY += 35;  //separacion de y
    }
    
    Particula bola(screenWidth / 2.0, screenHeight / 2.0, -4.5, -4.5, 8);
    Particula tabla(300 , 550 , 6.5, 5.7, 7);
    
    char dir;
    int cont =0;          // matriz es de 5x10 = 50 
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
             
       
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        dir = Direccion();
        
            
        tabla.moverGrid(dir, screenWidth, screenHeight);
         
        //gas.mover(screenWidth, screenHeight);
        //gas.rebotar(screenWidth, screenHeight);
         
        bola.mover(screenWidth, screenHeight);
        bola.rebotaBordes(screenWidth, screenHeight);


        for(int i = 4; i >= 0; i--){
            
            for(int j = pared[i].GetUtiles()-1; j > 0;j-- ){
                
                if(bola.colision(pared[i].obtieneParticula(j))){
                
                    pared[i].borraParticula(j);
                    bola.SetDY(bola.GetDY() * -1);
          
                    
                }
            }
        }

        //pintarConjunto(gas, RED);
        for(int i = 0; i < 5; i++){
                
            pintarConjunto(pared[i], GREEN);
                       
        }          
        
        pintarParticula(bola, BLUE);
        
        pintarLadrillo(tabla,45, 20, BLACK);
            
        DrawText("ESC para salir", 10, 10, 20, BLACK);
        
                
        if(bola.colision(tabla)){
                
            bola.SetDY(bola.GetDY() * -1);
        }
        
        
        if(bola.GetY() >= 590){
            
            EndDrawing();
            CloseWindow();
            
        }
        
        
        //        matriz 5X10
        if(pared[4].GetUtiles() == 0){
            cont++;
        }
        if(pared[3].GetUtiles() == 0){
            cont++;
        }        
        if(pared[2].GetUtiles() == 0){
            cont++;
        }        
        if(pared[1].GetUtiles() == 0){
            cont++;
        }
        if(pared[0].GetUtiles() == 0){
            cont++;
        }
        
        
        if( cont == 5){
            
            EndDrawing();
            CloseWindow();
        }
        
        EndDrawing();
  
    }
    
    CloseWindow(); 
    
    return 0;

}

