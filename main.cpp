#include <iostream>
#include <cstdlib>
#include "Window.h"

void puntoMedioLinea(SDL_Renderer* render,int maximo);
void CircunferenciaSegundoOrden(SDL_Renderer* render,int maximo);
void Elipse(SDL_Renderer* render,int maximo);
void Parabola(SDL_Renderer* render,int maximo);
void pintar8Pixeles(SDL_Renderer*render, int x, int y);
using namespace std;

int main(int argc, char **argv) {
    int respuesta;
    int maximo=600;
    cout<<endl<<"Primer tarea de graficación<<endl";
    cout<<"Elija una opcion: "<<endl;
    cout<<"0) Linea"<<endl<<"1) Circunferencia por 2do Orden"<<endl<<"2) Elipse"<<endl<<"3) Parabola"<<endl<<"4) Hiperbole"<<endl;
    
    do{
        cout<<"Respuesta: ";
        cin>>respuesta;
    }while(respuesta<0 || respuesta >4);

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Event event;
        SDL_Window* window = NULL;
        SDL_Renderer* render = NULL;
        
        if (SDL_CreateWindowAndRenderer(maximo,maximo, 0, &window, &render) == 0) {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
            SDL_RenderClear(render);
            SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
            SDL_RenderClear(render);
            SDL_RenderPresent(render);
    
    /*
    SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
    SDL_RenderPresent(render);
    */
    
    switch(respuesta){
        case 0:
            puntoMedioLinea(render,maximo);
            break;
        case 1:
            CircunferenciaSegundoOrden(render,maximo);
            break;
        case 2:
            Elipse(render,maximo);
            break;
        case 3:
            Parabola(render,maximo);
            break;
        case 4:
            //Hiperbole(render,maximo);
            break;
        default:
            cout<<"Opcion Invalida"<<endl;
            break;
    }
            SDL_RenderPresent(render);
            while (1) {
                if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
                    break;
            }
            
            if (render) {
                SDL_DestroyRenderer(render);
            }
            if (window) {
                SDL_DestroyWindow(window);
            }
        }
    }
    
    SDL_Quit();
    return 0;
}

void puntoMedioLinea(SDL_Renderer* render,int maximo )
{
    int X1,Y1,X2,Y2;

    do{
        cout<<"Ingrese valor de X1: "; cin>>X1;
        cout<<"Ingrese valor de Y1: "; cin>>Y1;
        cout <<endl<<"Ingrese valor de X2: "; cin>>X2;
        cout<<"Ingrese valor de Y2: "; cin>>Y2;
    }while(X1>maximo || X2>maximo || Y1>maximo || Y2>maximo);

    
    
    int x = Y1, y = X1;
    
    int dx = X2 - X1;
    int dy = Y2 - Y1;
    
    // valor inicial para el parametro de decisión
    int d = 2 * (dy-dx);
    
    while (x < X2)
    {
        x++;
        
        // E se elige
        if (d <= 0)
            d += 2 *dy;
        
        // NE se elige
        else
        {
            d += 2 *(dy-dx);
            y++;
        }
        
        
        SDL_RenderDrawPoint(render, x+300, -y+300);
        SDL_RenderPresent(render);
        
        
    }
   
}

void CircunferenciaSegundoOrden(SDL_Renderer* render,int maximo)
{
    int r,d,dE,dSE;
    double X,Y;
    do{
        cout<<"Ingrese valor del radio: ";
        cin>>r;
    }while(r>maximo);
    
    d=1-r;
    dE=3;
    dSE=-2*r+5;
    
    X=0;
    Y=r;
    
    while(X<Y){
        X++;
        if(d<0){
            d +=dE;
            dE+=2;
            dSE+=2;
        }else{
            d+=dSE;
            dE+=2;
            dSE+=4;
            Y--;
        }
        pintar8Pixeles(render,X,Y);
        pintar8Pixeles(render,Y,X);


    }
    
}



void Elipse(SDL_Renderer* render,int maximo)
{
    //x1= radio de x, y1= radio de y
    int x1,y1;
    double x,y,d1,d2,dx,dy;
    

    do{
        cout<<"Ingrese valor de X1: ";
        cin>>x1;
        cout<<"Ingrese valor de Y1: ";
        cin>>y1;
    }while(x1>maximo and y1>maximo);
    
    x=0;
    y=y1;
    
    d1 = (y1 * y1) - (x1 * x1 * y1) +
    (0.25 * x1 * x1);
    
    
    
    dx = 2 * y1 * y1 * x;
    dy = 2 * x1 * x1 * y;
    while(dx<dy){
        
        pintar8Pixeles(render,(x),(y));
        
        if (d1 < 0)
        {
            x++;
            dx = dx + (2 * y1 * y1);
            d1 = d1 + dx + (y1 * y1);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * y1 * y1);
            dy = dy - (2 * x1 * x1);
            d1 = d1 + dx - dy + (y1 * y1);
        }
        
    }
    
    d2 = ((y1 * y1) * ((x + 0.5) * (x + 0.5))) +
    ((x1 * x1) * ((y - 1) * (y - 1))) -
    (x1 * x1 * y1 * y1);
    
    // Plotting points of region 2
    while (y >= 0)
    {
        
        // Print points based on 4-way symmetry
        pintar8Pixeles(render,(x),(y));
        
        
        // Checking and updating parameter
        // value based on algorithm
        if (d2 > 0)
        {
            y--;
            dy = dy - (2 * x1 * x1);
            d2 = d2 + (x1 * x1) - dy;
        }
        {
            y--;
            x++;
            dx = dx + (2 * y1 * y1);
            dy = dy - (2 * x1 * x1);
            d2 = d2 + dx - dy + (x1 * x1);
        }
    }
    
    
}
void Parabola(SDL_Renderer* render,int maximo)
{
    int x,y,d1,d2,p;
    y=0;
    x=0;
    do{
        cout<<"Ingrese valor de p: ";
        cin>>p;
    }while(p>maximo);
    
    d1=pow(x+1.0,2)-4*(p*y+0.5);
    //REGION I
    while(y < p && x<=maximo){
        x++;
        if(d1<=0){
            //Eliges este
            d1+=2*x-3;
        }else{
            //Eliges noreste
            d1+=2*x+3-4*p;
            y++;
        }
        pintar8Pixeles(render,x,y);
    }
    
    //REGION II
    
    d2=pow(x+0.5,2)-4*(p*(y+1.0));
    while(x<=maximo){
        y++;
        if(d2<=0){
            //Eliges noreste
            d2+=2*x-4*p+2;
            x++;
        }else{
            //Eliges norte
            d2+=-4*p;
        }
        
        pintar8Pixeles(render,x,y);
    }
    
}

void pintar8Pixeles(SDL_Renderer*render, int x, int y){
    SDL_RenderDrawPoint(render, x+300, -y+300);
    SDL_RenderDrawPoint(render, x+300, y+300);
    SDL_RenderDrawPoint(render, -x+300, -y+300);
    SDL_RenderDrawPoint(render, -x+300, y+300);
}
