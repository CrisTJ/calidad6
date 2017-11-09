//
//  calcular.h
//  Progama 6
//
//  Created by Cristina Jimenez on 11/07/17.
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//

#ifndef calcular_h
#define calcular_h
#include <iostream>
#include <iomanip> //LIBRERIA PARA MANIPULACION DE DECIMALES
#include <math.h>
#include <fstream>
#include <vector>
#include <stdio.h>// scanf
#include <string.h>
#include <string>
#include "info.h"
#include "calcularX.h"

using namespace std;

//ESTA PARTE SE DEDICA A CALCULAR LOS RESULTADOS
//=p-Calcular
//=b-66
class Calcular{
private:
    Par pares;
    double sig;
    double ran;
    double LS;
    double LI;
    
public:
    Calcular(){
        pares = Par();
        sig = 0;
        ran = 0;
        LS = 0;
        LI = 0;

    }
    Calcular(Par pares){
        this->pares = pares;
        sig = 0;
        ran = 0;
        LS = 0;
        LI = 0;
    }
    //GETS
    double getSig(){
        return sig;
    }
    double getRan(){
        return ran;
    }
    double getLS(){
        return LS;
    }
    double getLI(){
        return LI;
    }
    //SETS
    void setSig(double sig){
        this->sig = sig;
    }
    void setRan(double ran){
        this->ran = ran;
    }
    void setLS(double LS){
        this->LS = LS;
    }
    void setLI(double LI){
        this->LI = LI;
    }
    
    //METODOS DE ACCION
    void meterInfo(string archivo){//STRING S ES EL NOMBRE DEL ARCHIVO QUE VA A ANALIZAR
        ifstream file;
        file.open(archivo);//SE ABRE EL ARCHIVO
        string linea;
        bool isXK = true;//SE UTILIZA PARA CHECAR LA PRIMERA LINEA QUE ES LA QUE CONTIENE LA VARIABLE XK
        
        if(file.is_open()){//SI EL ARCHIVO SE ABRIO, ENTONCES:
            while(getline(file,archivo)){//MIENTRAS QUE EL ARCHIVO TENGA LINEAS DE INFORMACION
                if(isXK){
                    double xk = stoi(archivo);
                    pares.setXK(xk);
                    isXK=false;
                }else{
                    double a,b;
                    replace(archivo.begin(), archivo.end(), ',', ' ');
                    char tab2[1024];
                    strcpy(tab2, archivo.c_str());
                    sscanf (tab2,"%lf %lf",&a,&b);
                    pares.addxy(a,b);
                }
            }
        }
        else{
            cout<< "Favor de introducir un nombre de archivo valido!"<<endl;
        }
        pares.setpromedios();
        file.close();//SE CIERRA EL ARCHIVO
    }
    //=i
    //ESTE METODO CALCULA LOS COEFICIENTES DE CORRELACION
    double coefCorrelacion(){
        double n = pares.getN();
        double sup = (n*pares.getSumaMultXY()) - (pares.getSumaXs()*pares.getSumaYs());

        double a = n*pares.getSumaXsCuad();
        double b = n*pares.getSumaYsCuad();
        double c = pow(pares.getSumaYs(),2);
        double d = pow(pares.getSumaXs(),2);
        double inf = sqrt((a-d)*(b-c));
        if(inf<=0){
            return 0;
        }
        else return sup/inf;
    }

    //=i
    //ESTE METODO CALCULA LA B1
    double regreLinealB1(){
        double n = pares.getN();
        double a = pares.getSumaMultXY() - (n*pares.getxProm()*pares.getyProm());
        double b = pares.getSumaXsCuad() - (n*pares.getxProm()*pares.getxProm());

        return a/b;
    }
    //=i
    //ESTE METODO CALCULA LA REGRESION LINEAL EN BASE A B1
    double regreLinealB0(){
        return pares.getyProm() - pares.getb1() * pares.getxProm();
    }
    
    //=i
    //ESTE METODO CALCULA UNA PREDICCION MEJORADA
    double predMejorada(){
        return regreLinealB0() + (regreLinealB1()*pares.getXK());
    }
    
    //i
    //ESTE METODO CALCULA LA SIGNIFICANCIA DE UNA CORRELACION
    double sigCorre(){

        double sup;
        double inf;
        
        sup = fabs(pares.getR())*sqrt(pares.getN()-2);
        inf = sqrt(1-(pow(pares.getR(), 2)));
        setSig(sup/inf);
        return getSig();
    }
    //i
    //ESTE METODO CALCULA EL INTERVALO DE PREDICCION
    double intervaloPred(){
        double ran;
        return ran;
    }
    //i
    //CALCULA LA VARIABLE P
    double p(){
        double x = abs(pares.getR()) * sqrt((pares.getN() - 2)) / sqrt(1 - pares.getR() * pares.getR());
        int dof = pares.getN() - 2;
        double p;
        double aux;
        double error = 0.0000001;
        
        CalcularX *calcularX = new CalcularX();
        calcularX->setX(x);
        calcularX->setDof(dof);
        calcularX->operaciones();
        
        do{
            aux = p;
            calcularX->operacionesX2();
            p = calcularX->getX();
        }while(fabs(aux - p) > error);
        
        return calcularX->getX();
    }
    
    double loopCalcP(CalcularX calcularX){
        
        calcularX.operaciones();
        double pAct = calcularX.getInfo().getP();
        double pAnt;
        do
        {
            pAnt = pAct;
            calcularX.operacionesX2();
            pAct = calcularX.getInfo().getP();
            
        } while(fabs(pAnt-pAct)>calcularX.getInfo().getE());
        
        return pAct;
    }
    //=i
    //ESTE METODO CALCULA t(0.35, dof) QUE ES EL VALOR DE X PARA UNA DISTRIBUCION T CON N-2 GRADOS DE LIBERTAD
    double t(CalcularX calcularX){

        int dof = calcularX.getDof();
        calcularX.getInfo().setP(.35);
        calcularX.setX(1.0);
        calcularX.setDof(dof);
        double d = 0.5;
        bool dir = false;
        double pAux = loopCalcP(calcularX);
        double p = .35;
        
        while(fabs(p-pAux)>calcularX.getInfo().getE()){
            if(pAux<p){
                calcularX.setX(calcularX.getX()+d);
                if(dir){
                    d = d/2;
                }
                dir = false;
            }
            else{
                calcularX.setX(calcularX.getX()-d);
                if(!dir){
                    d= d/2;
                }
                dir = true;
            }
            
            pAux = loopCalcP(calcularX);
        }
        
    }
    // ESTE METODO CALCULA LA SIGNIFICANCIA
    //=i
    void Sig()
    {
        sig = 1 - (2 * p());
    }
    
    // ESTE METODO CALCULA EL LIMITE SUPERIOR
    //=i
    void calcLS()
    {
        LS = pares.getInfo().getYK + ran;
    }
    
    // ESTE METODO CALCULA EL LIMITE INFERIOR
    //=i
    void  calcLI()
    {
        LI = calcular.getyk() - ran;
        
        if(LI < 0){
            LI = 0.0;
        }
    }
    
    //=i
    //ESTE METODO MANDA LLAMAR TODOS LOS METODOS QUE CALCULAN LOS RESULTADOS
    void calcula(){
        pares.setb1(regreLinealB1());
        pares.setb0(regreLinealB0());
        pares.setR(coefCorrelacion());
        double aux = pow(pares.getR(),2);
        pares.setR2(aux);
        pares.setYK(predMejorada());
    }
    //=i
    //ESTE METODO IMPRIME EN CONSOLA LOS RESULTADOS DE LOS CALCULOS 
    void imprimeResultados(){
        
        cout<< "N = "  << pares.getN() << endl;
        cout<< "xk = " << pares.getXK() << endl;
        cout<< "r = "  << setprecision(5) << fixed << pares.getR()  << endl;
        cout<< "r2 = " << setprecision(5) << fixed << pares.getR2() << endl;
        cout<< "b0 = " << setprecision(5) << fixed << pares.getb0() << endl;
        cout<< "b1 = " << setprecision(5) << fixed << pares.getb1() << endl;
        cout<< "yk = " << setprecision(5) << fixed << pares.getYK() << endl;
        cout<< "sig = "<< setprecision(5) << fixed << sigCorre()    << endl;
        //cout<< "ran = "<< setprecision(5) << fixed << << endl;
        //cout<< "LS = "<< setprecision(5) << fixed << << endl;
        //cout<< "LI = "<< setprecision(5) << fixed << << endl;
    }
};

#endif /* calcular_h */
