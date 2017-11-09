//
//  info.h
//  Programa5
//
//  Created by Cristina Jimenez on 10/30/17.
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//
//ESTA PARTE ES DONDE SE GUARDA TODA LA INFORMACION DEL CASO QUE VA A SER MANIPULADO


#ifndef info_h
#define info_h
//=p-Info
//=b-35


class Informacion{
private:
    int num_Seg;
    double dW;
    double dE;
    double dP;
    
public:
    //CONSTRUCTOR DE LA CLASE VACIA
    Informacion(){
        num_Seg = 10;
        dW = 0;
        dE = 0.00000001;//=m-
        dP = 0;
    }
    //CONSTRUCTOS DE LA CLASE CON PARAMETROS
    Informacion(int num_Seg, double dW, double dE, double dP){
        this->num_Seg = num_Seg;
        this->dW = dW;
        this->dE = dE;
        this->dP = dP;
    }
    
    //SET
    void setNum_Seg(int num_Seg){
        this->num_Seg = num_Seg;
    }
    void setW(double dW){
        this->dW = dW;
    }
    void setE(double dE){
        this->dE = dE;
    }
    void setP(double dP){
        this->dP = dP;
    }
    //GET
    int getNum_Seg(){
        return num_Seg;
    }
    double getW(){
        return dW;
    }
    double getE(){
        return dE;
    }
    double getP(){
        return dP;
    }
};


#endif /* info_h */

