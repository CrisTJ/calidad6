//
//  main.cpp
//  Programa 6
//
//  Created by Cristina Jimenez on 11/07/17
//  Copyright © 2017 Cristina Jimenez. All rights reserved.
//
#include "info.h"
#include "calcular.h"
#include <iostream>
#include <iomanip> //LIBRERIA PARA MANIPULACION DE DECIMALES
#include <math.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
//=p-Main
//=b-10
//ESTA PARTE CREA LOS OBJETOS Y RECIBE LA INFORMACION DE PARTE DEL USUARIO
//PARA EJECUTAR LOS CALULOS. 

using namespace std;
int main(int argc, const char * argv[]) {
    std::string s; 
    std::cout<<"Por favor escriba el nombre del archivo: "<<std::endl;
    std::cin>> s;
    
    Calcular *calcular = new Calcular();
    calcular->meterInfo(s);
    calcular->calcula();
    calcular->imprimeResultados();
    
    return 0;
}
