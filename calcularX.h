//
//  calcularX.h
//  Programa6
//
//  Created by Cristina Jimenez on 11/8/17.
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//

#ifndef calcularX_h
#define calcularX_h
#include <algorithm>
#include <math.h>
#include <iomanip>
#include "informacion.h"

const double pi = 3.14159265358979323846;
using namespace std;
//=p-CalcularX
//=b-56

class CalcularX{
private:
    Informacion info;
    double x;
    int dof;
    double p;
public:
    CalcularX(){
        info = *new Informacion();
        x = 0;
        dof = 1;
    }
    CalcularX(Informacion info, double x, int dof){
        this->info = info;
        this->x = x;
        this->dof = dof;
    }
    
    //SET
    void setX(double x){
        this->x = x;
    }
    void setDof(int dof){
        this->dof = dof;
    }
    
    void setP(double p){
        this->p = p;
    }
    //GET
    Informacion getInfo(){
        return info;
    }
    double getX(){
        return x;
    }
    int getDof(){
        return dof;
    }
    
    //METODOS DE ACCION
    
    //=i-
    //CALCULA LA FUNCION EN X
    double f(double x){
        
        double a;
        double b;
        double c;
        
        a = (pow(dof*pi,.5));
        b = tgamma(dof/2.0);
        c = pow((1+(pow(x, 2)/dof)), (-(dof+1)/2.0));
        
        return ((tgamma((dof+1)/2.0))/(a*b))*c;
    }
    
    //=i-
    //SE HACEN LOS CALCULOS SIMPSON ASI COMO SE MANDA A LLAMAR A LA FUNCION
    //PARA SER EVALUADA EN X
    void operaciones(){
        info.setW(x/info.getNum_Seg());
        
        int i = 1;
        double wAct = info.getW();
        double result = f(0) + f(x);
        
        while(i < info.getNum_Seg()){
            
            //EL CONTADOR ES PAR
            if(i % 2 == 0){
                result =  result + 2*f(wAct);
            }
            //EL CONTADOR NO ES PAR
            else{
                result =  result + 4*f(wAct);
            }
            i++;
            wAct = wAct+info.getW();
        }
        
        info.setP(result*info.getW()/3);
    }
    
    //=i-
    //METODO QUE DUPLICA LA CANTIDAD DE SEGMENTOS
    void operacionesX2(){
        info.setNum_Seg(info.getNum_Seg()*2);
        operaciones();
    }
    //=i-
    //PREPARA E IMPRIME LOS RESULTADOS DE LAS OPERACIONES
    void resultados(){
        printf("p = %.5f \n", p);
        printf("dof = %d \n", dof);
        printf("x = %.5f \n", x);
    }
    
};


#endif /* calcularX_h */


