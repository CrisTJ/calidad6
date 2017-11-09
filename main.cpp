//
//  main.cpp
//  Proga3
//
//  Created by Cristina Jimenez on 10/18/17.
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//
#include "info.h"
#include "calcular.h"
#include "info2.h"
#include "calcular2.h"
#include <iostream>
#include <iomanip> //LIBRERIA PARA MANIPULACION DE DECIMALES
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
//=p-Main
//BASE DEL PROGRAMA 3
//=b-10
//BASE DEL PROGRAMA 5
//=b-48

//ESTA PARTE CREA LOS OBJETOS Y RECIBE LA INFORMACION DE PARTE DEL USUARIO
//PARA EJECUTAR LOS CALULOS.

//=i
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

using namespace std;
int main(int argc, const char * argv[]) {
    std::string s; //=b-
    std::cout<<"Por favor escriba el nombre del archivo: "<<std::endl;
    std::cin>> s;
    
    Calcular *calcular = new Calcular();
    calcular->meterInfo(s);
    calcular->calcula();
    calcular->imprimeResultados();

    
    return 0;
}
