#include <iostream>

void punto_1(){
    // Declarar y asignar una variable entera (int)
    int num = 255;
    std::cout << "Valor de variable: " << num << std::endl;

    // Presentar en pantalla la dirección de memoria de esa variable.
    std::cout << "Direccion en memoria de variable:" << &num << std::endl;
    int * pnum = &num;

    // Modifique el valor de la variable indirectamente utilizando punteros
    *pnum = 510;

    // Presente nuevamente el valor de la variable y la dirección de memoria
    std::cout << "Nuevo valor de variable: " << num << " | Dir. de memoria: " << &num << std::endl;
    return;
}

void punto_2(){
    // Declarar un puntero a una variable
    int num = 242;
    int * pnum = &num;
    std::cout << "Valor de variable por puntero: " << *pnum << std::endl;

    // Utilizar el puntero para acceder y modificar el valor de la variable
    *pnum = 484;
    std::cout << "Nuevo valor de variable por puntero: " << num << std::endl;

    // Crear una referencia a la variable y utilizarla para modificar el valor
    int & refnum = num;
    refnum = 211;

    // Presentar las direcciones de memoria del puntero y la referencia
    std::cout << "Valor de variable por referencia: " << num << std::endl;
    std::cout << "Dir. de memoria de referencia: " << &pnum << std::endl;
    std::cout << "Dir. de memoria de referencia: " << &refnum << std::endl;
    return;
}

void punto_3(){
    // Declarar un array de números enteros (int)
    const int arrSize = 5;
    int nums[arrSize] = {11, 22, 33, 44, 55};

    std::cout << "Contenido del arreglo: ";
    for (int i = 0; i < arrSize; i++){
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    // Utilizar punteros para acceder a los elementos del array y modificar su contenido.
    int * pnumArr = nums;
    pnumArr[2] = 99;

    std::cout << "Contenido del arreglo post-modificacion: ";
    for (int i = 0; i < arrSize; i++){
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    // Presente la dirección de memoria del array y del puntero
    std::cout << "Dir. de memoria del array: " << &nums << std::endl;
    std::cout << "Dir. de memoria del puntero: " << &pnumArr << std::endl;
    return;
}

void punto_4(){
    // Cree una matriz de enteros dinámica de 2D, usando asignación dinámica de memoria con new
    int ** dynamic2DArray;
    int fil = 3; 
    int col = 4;
    
    dynamic2DArray = new int*[fil];
    for (int i = 0; i < fil; i++){
        dynamic2DArray[i] = new int[col];
    }

    // Llenar la matriz con datos
    int val = 1;
    for (int i = 0; i < fil; i++){
        for (int j = 0; j < col; j++){
            dynamic2DArray[i][j] = val++;
        }
    }
    std::cout << "Matriz dinamica:" << std::endl;
    for (int i = 0; i < fil; i++){
        for (int j = 0; j < col; j++){
            std::cout << dynamic2DArray[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Liberar la memoria con delete cuando haya terminado
    for (int i = 0; i < fil; i++){
        delete[] dynamic2DArray[i];        
    }
    delete[] dynamic2DArray;   
    return;
}

void extra(){ 
    // Presentar el stack, el heap y el code usando C++
    int stackVar;
    std::cout << "Dir. de stackVar: " << &stackVar << std::endl;
    int * heapMem = new int;
    std::cout << "Dir. de memoria asignada en el heap: " << heapMem << std::endl;
    std::cout << "Dir. de la funcion extra(): " << (void*)extra << std::endl;
    delete heapMem;
    return;
}

int main(){
    int option;
    std::cout << "Opcion (1): Correr codigo de Actividad 1" << std::endl;
    std::cout << "Opcion (2): Correr codigo de Actividad 2" << std::endl;
    std::cout << "Opcion (3): Correr codigo de Actividad 3" << std::endl;
    std::cout << "Opcion (4): Correr codigo de Actividad 4" << std::endl;
    std::cout << "Opcion (5): Correr codigo de Actividad Extra" << std::endl;
    std::cin >> option;

    if (option == 1){
        punto_1();
    } else if (option == 2){
        punto_2();
    } else if (option == 3){
        punto_3();
    } else if (option == 4){
        punto_4();
    } else if (option == 5){
        extra();
    }

    return 0;
}