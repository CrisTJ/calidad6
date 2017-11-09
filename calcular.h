//
//  calcular.h
//  Proga3
//
//  Created by Cristina Jimenez on 10/18/17.
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
#include "info2.h"
#include "calcular2.h"

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
    Par getPares(){
        return pares;
    }
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
    void sigCorre(Calcular2 calcular2){
        double sup = fabs(pares.getR())*sqrt(pares.getN()-2);;
        double inf = sqrt(1-(pow(pares.getR(), 2)));
        double x = sup/inf;
        
        calcular2.setX(x);
        calcular2.setDof(pares.getN()-2);
        
        double p = loopCalcP(calcular2);
        
        setSig(1 - 2.0 * p);
    }
    
    double loopCalcP(Calcular2 calcular2){
        
        calcular2.operaciones();
        double pAct = calcular2.getInfo().getP();
        double pAnt;
        do
        {
            pAnt = pAct;
            calcular2.operacionesX2();
            pAct = calcular2.getInfo().getP();
            
        } while(fabs(pAnt-pAct)>calcular2.getInfo().getE());
        
        return pAct;
    }
    
    //i
    //ESTE METODO CALCULA EL INTERVALO DE PREDICCION
    double intervaloPred(){
        //calculateX();
        vector<pair<double,double>> pairs = pares.getVector();
        //meter progrsma 5
        
        //Acabar programa 5
        double ran;
        double desv = 0.0;
        double b = 0;
        double t = calculateX();
        double a = 1/(pares.getN());
        double c = pow(pares.getXK() - pares.getxProm(),2);
        
        for( int i = 0; i< pares.getN(); i++){
             b += pow(pairs[i].first - pares.getxProm(),2);
            desv = pow(pairs[i].second - regreLinealB0() - (regreLinealB1()*pairs[i].first),2);
        }
        
        ran = t * sqrt(desv*(1/(pares.getN()-2))) * sqrt(1+a+(c/b));
        return ran;
    }
    
    double calculateX(){
        //Meter programa 5
        Calcular2 *calcular2 = new Calcular2();
        //=d-15
        double p = 0.35;
        calcular2->getInfo().setP(p);
        calcular2->setX(1.0);
        calcular2->setDof(pares.getN());
        double d = 0.5;
        bool dir = false;
        double pAux = loopCalcP(*calcular2);
        cout << calcular2->getInfo().getE() << endl;
        cout << pAux << endl;
        while(fabs(p-pAux)>calcular2->getInfo().getE()){
            if(pAux<p){
                calcular2->setX(calcular2->getX()+d);
                if(dir){
                    d = d/2;
                }
                dir = false;
            }
            else{
                calcular2->setX(calcular2->getX()-d);
                if(!dir){
                    d= d/2;
                }
                dir = true;
            }
            cout << calcular2->getX() << " " << pAux << endl;
            pAux = loopCalcP(*calcular2);
            
        }
        return calcular2->getX();
    }
    
    //=i
    //ESTE METODO CALCULA EL RANGO SUPERIOR
    void calcUPInt(){
        setLS(pares.getYK()+intervaloPred());
    }
    
    //=i
    //ESTE METODO CALCULA EL RANGO INFERIOR
    void calcLPInt(){
        if(pares.getYK()-intervaloPred() <= 0){
            setLI(0);
        }else{
            setLI(pares.getYK()-intervaloPred());
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
        setRan(intervaloPred());
        sigCorre(Calcular2());
        calcUPInt();
        calcLPInt();
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
        cout<< "sig = "<< setprecision(10) << fixed << getSig()      << endl;
        cout<< "ran = "<< setprecision(5) << fixed << getRan()      << endl;
        cout<< "LS = " << setprecision(5) << fixed << getLS()       << endl;
        cout<< "LI = " << setprecision(5) << fixed << getLI()       << endl;
    }
};

#endif /* calcular_h */
