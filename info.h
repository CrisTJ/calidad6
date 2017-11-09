//
//  info.h
//  Proga3
//
//  Created by Cristina Jimenez on 10/18/17.
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//

#ifndef info_h
#define info_h
#include <iostream>
#include <iomanip> //LIBRERIA PARA MANIPULACION DE DECIMALES
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>

using namespace std;
//=p-Par
//=b-114
//ESTA CLASE DESCRIBE EL OBJETO DE PAR Y CONTIENE TODA LA INFORMACION
//NECESARIA PARA REALIZAR LOS CALCULOS 
class Par
{
private:
    double N;
    double XK;
    double r;
    double r2;
    double b0;
    double b1;
    double YK;
    double xProm;
    double yProm;
    double sumaXs;
    double sumaYs;
    double sumaXsCuad;
    double sumaYsCuad;
    double sumaMultXY;
    vector<pair<double, double>> vecPares;
    
public:
    Par(){
        this->N = 0;
        this->XK = 0;
        this->r= 0;
        this->r2 = 0;
        this->b0 = 0;
        this->b1 = 0;
        this->YK = 0;
        this->xProm = 0;
        this->yProm = 0;
        this->sumaXs = 0;
        this->sumaYs = 0;
        this->sumaXsCuad = 0;
        this->sumaYsCuad = 0;
        this->sumaMultXY = 0;
        
    }
    Par(double N, double XK, double r, double r2, double b0, double b1, double YK, double xProm, double yProm, double sumaXs, double sumaYs,double sumaXsCuad, double sumaYsCuad, double sumaMultXY){
        this->N = N;
        this->XK = XK;
        this->r= r;
        this->r2 = r2;
        this->b0 = b0;
        this->b1 = b1;
        this->YK = YK;
        this->xProm = xProm;
        this->yProm = yProm;
        this->sumaXs = sumaXs;
        this->sumaYs = sumaYs;
        this->sumaXsCuad = sumaXsCuad;
        this->sumaYsCuad = sumaYsCuad;
        this->sumaMultXY = sumaMultXY;
    }
    
    //SETs
    void addxy(double x, double y){
        addN();
        SumaXs(x);
        setSumaYs(y);
        setSumaXsCuad(x);
        setSumaYsCuad(y);
        setSumaMultXY(x, y);
        vecPares.push_back(make_pair(x, y));
        
    }
    void setpromedios(){
        setxProm();
        setyProm();
    }
    void addN(){
        this->N += 1;
    }
    void setXK(double XK){
        this->XK = XK;
    }
    void setR(double r){
        this->r= r;
    }
    void setR2(double r2){
        this->r2 = r2;
    }
    void setb0(double b0){
        this->b0 = b0;
    }
    void setb1(double b1){
        this->b1 = b1;
    }
    void setYK(double YK){
        this->YK = YK;
    }
    void setxProm(){
        this->xProm = getSumaXs()/getN();
    }
    void setyProm(){
        this->yProm = getSumaYs()/getN();
    }
    void SumaXs(double sumaXs){
        this->sumaXs += sumaXs;
    }
    void setSumaYs(double sumaYs){
        this->sumaYs += sumaYs;
    }
    void setSumaXsCuad(double sumaXsCuad){
        this->sumaXsCuad += sumaXsCuad*sumaXsCuad;
    }
    void setSumaYsCuad(double sumaYsCuad){
        this->sumaYsCuad += sumaYsCuad*sumaYsCuad;
    }
    void setSumaMultXY(double x, double y){
        this->sumaMultXY += x*y;
    }
    //GETS
    double getN(){
        return N;
    }
    double getXK(){
        return XK;
    }
    double getR(){
        return r;
    }
    double getR2(){
        return r2;
    }
    double getb0(){
        return b0;
    }
    double getb1(){
        return b1;
    }
    double getYK(){
        return YK;
    }
    double getxProm(){
        return xProm;
    }
    double getyProm(){
        return yProm;
    }
    double getSumaXs(){
        return sumaXs;
    }
    double getSumaYs(){
        return sumaYs;
    }
    double getSumaXsCuad(){
        return sumaXsCuad;
    }
    double getSumaYsCuad(){
        return sumaYsCuad;
    }
    double getSumaMultXY(){
        return sumaMultXY;
    }
    vector<pair<double,double>>getVector(){
        return vecPares; 
    }
};



#endif /* info_h */
