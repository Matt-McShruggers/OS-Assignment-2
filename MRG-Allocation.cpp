#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

// HEADS UP: Debido a como se trabajarán los vectores de memoria, este código solo
//           habilitará disponibilidad para 1 proceso por cada particion de memoria.

class MemoryManagement {
private:
    // Tamaño total de la memoria 
    int memSize;
    // Vector que maneja la ocupación de las particiones 
    // Ejemplo: {-1, -1, [numero de PID], -1}
    std::vector<int> memory;
    // Vector que maneja las particiones y el tamaño de memoria de cada una 
    // Ejemplo: {100, 200, 300 (Condición: [tamaño del numero de PID] < 300), 400}
    std::vector<int> partitions;
    
public:
    // Inicializar la memoria con valores negativos (-1) para indicar que está vacía
    MemoryManagement(int size) {
        memSize = size;
        memory.resize(size);
        fill(memory.begin(), memory.end(), -1);
    }
    
    // Para la segunda línea del .txt. Las particiones en las que va a estar la memoria
    void customMemSize(int mSize) {
        memory.resize(mSize);
        return;
    }
    
    // Para la tercera línea del .txt. Asignar cuanta memoria va a tener cada particion
    void distributeMemSize(std::vector<int> sizeDistribution) {
        partitions = sizeDistribution;
        return;
    }
    
    // Implementación del algoritmo First-Fit para asignar memoria
    bool memAllocFirstFit(int processID, int size) {
        // Si no hay tamaño de memoria suficiente para otorgarle al proceso, cancelar operación
        if (memSize < size){
            std::cout << "Error: El proceso requiere mas memoria de la que hay en total" << std::endl;
            return false;
        } 
        // Buscar un espacio en el arreglo de memorias que pueda almacenar el proceso
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i] == -1 && size <= partitions[i]) {
                memory[i] = processID;
                return true;
            }
        }
        // ¿No se encontró este espacio?
        std::cout << "Error: La memoria está llena";
        return false;
    }
    
    bool memAllocBestFit(int processID, int size) {
        // Si no hay tamaño de memoria suficiente para otorgarle al proceso, cancelar operación
        if (memSize < size){
            std::cout << "Error: El proceso requiere mas memoria de la que hay en total" << std::endl;
            return false;
        } 
        // Hacer la comparativa de la mejor particion asignable y luego asignar el proceso a ese bloque (Si existe)
        int bestFitCandidate = -1;
        int bestSubtractionThusFar = this->memSize;
        for (int i = 0; i < memory.size(); i++){
            int subtractionResult = partitions[i] - size;
            if (memory[i] == -1 && subtractionResult >= 0 && subtractionResult < bestSubtractionThusFar){
                bestFitCandidate = i;
                bestSubtractionThusFar = subtractionResult;
            }
        }
        // ¿No se obtuvo un candidato? (Memoria llena/No hay suficiente espacio)
        if (bestFitCandidate == -1){
            std::cout << "Error: No hay particiones disponibles para el proceso" << std::endl;
            return false;
        }
        // Si se obtuvo un candidato, se direcciona directamente
        memory[bestFitCandidate] = processID;
        return true;
    }
    
    bool memAllocWorstFit(int processID, int size) {
        // Si no hay tamaño de memoria suficiente para otorgarle al proceso, cancelar operación
        if (memSize < size){
            std::cout << "Error: El proceso requiere mas memoria de la que hay en total" << std::endl;
            return false;
        } 
        // Hacer la comparativa de la mejor particion asignable y luego asignar el proceso a ese bloque (Si existe)
        int worstFitCandidate = -1;
        int worstSubtractionThusFar = 0;
        for (int i = 0; i < memory.size(); i++){
            int subtractionResult = partitions[i] - size;
            if (memory[i] == -1 && subtractionResult >= 0 && subtractionResult > worstSubtractionThusFar){
                worstFitCandidate = i;
                worstSubtractionThusFar = subtractionResult;
            }
        }
        // ¿No se obtuvo un candidato? (Memoria llena/No hay suficiente espacio)
        if (worstFitCandidate == -1){
            std::cout << "Error: No hay particiones disponibles para el proceso" << std::endl;
            return false;
        }
        // Si se obtuvo un candidato, se direcciona directamente
        memory[worstFitCandidate] = processID;
        return true;
    }
    
    bool freeMem(int processID) {
        for (int i = 0; i < memory.size(); i++){
            if (memory[i] == processID) {
                // Liberar el bloque de memoria
                memory[i] = -1; 
                return true;
            }
        }
        std::cout << "Error: No se encontró el proceso pedido en la memoria" << std::endl;
        return false;
    }
    
    void memoryStatus() {
        std::cout << "Estado de la memoria: \n";
        for (int i = 0; i < memory.size(); i++){
            std::cout << "ID de proceso: " << memory[i] << "| Tamano total: " << partitions[i] << "\n";
        }
        std::cout << std::endl;
        return;
    }
};

class Reader {
private:
    std::vector<std::string> inputFileVector;

public:
    Reader() {
        inputFileVector = {};
    }

    // Para líneas en la que se especifican varios datos separados por comas y espacios
    std::vector<std::string> splitString(std::string distributedSizes){
        std::stringstream sstr(distributedSizes);
        std::vector<std::string> v;
        while (sstr.good()){
            std::string substr;
            getline(sstr, substr, ',');
            if (substr[0] == ' ') substr.erase(0, 1);
            v.push_back(substr);
        }
        return v;
    }

    // Lee el archivo de entrada, almacena la info importantes en un vector, y guarda este vector en privado
    void executeFileReading(){
        std::ifstream inputFile;
        inputFile.open("malloc-input.txt");
        if (!inputFile.is_open()) {
            std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
            return;
        }

        /*std::ofstream outputFile;
        outputFile.open("malloc-output.txt");
        if (!outputFile.is_open()) {
            std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
            return;
        }*/

        std::vector<std::string> inputFileContent;
        std::string line;
        int currentLine = 0;
        while (std::getline(inputFile, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            inputFileContent.push_back(line);
        }
        
        /*for (int i = 0; i < inputFileContent.size(); i++){
            std::cout << inputFileContent[i] << std::endl;
        }*/
    
        inputFile.close();
        // outputFile.close();
        inputFileVector = inputFileContent;
        return;
    }

    void executeAllocation(){
        int sizeOfMem = std::stoi(inputFileVector[0]);
        int numOfSegments = std::stoi(inputFileVector[1]);
        std::vector<int> segments = {};
        std::vector<std::string> thirdLine = this->splitString(inputFileVector[2]);
        for (int i = 0; i < thirdLine.size(); i++){
            segments.push_back = std::stoi(thirdLine[i]);
        }
        int algorithmType = std::stoi(inputFileVector[3]); // 1 = FirstFit, 2 = BestFit, 3 = WorstFit

        MemoryManagement manager(sizeOfMem);
        manager.customMemSize(numOfSegments);
        manager.distributeMemSize(segments);
        std::vector<std::string> consequentLines = {};
        int jobID;
        int jobMem;
        for (int j = 4; j < inputFileVector.size(); j++ ){
            consequentLines = this->splitString(inputFileVector[j]);
            jobID = std::stoi(consequentLines[0]);
            jobMem = std::stoi(consequentLines[1]);
            if (algorithmType == 1) {
                if (manager.memAllocFirstFit(jobID, jobMem)) {
                    std::cout << "Proceso alojado en memoria exitosamente." << std::endl;
                } else {
                    std::cout << "El alojamiento del proceso en memoria falló." << std::endl;
                }
            } else if (algorithmType == 2) {
                if (manager.memAllocBestFit(jobID, jobMem)) {
                    std::cout << "Proceso alojado en memoria exitosamente." << std::endl;
                } else {
                    std::cout << "El alojamiento del proceso en memoria falló." << std::endl;
                }
            } else if (algorithmType == 3) {
                if (manager.memAllocWorstFit(jobID, jobMem)) {
                    std::cout << "Proceso alojado en memoria exitosamente." << std::endl;
                } else {
                    std::cout << "El alojamiento del proceso en memoria falló." << std::endl;
                }
            }
        }
        return 0;
    }
};

void testingMemoryManagementClass() {
    int memSize = 100;
    std::vector<int> testing = {10, 50, 20, 20};
    MemoryManagement manager(memSize);
    
    manager.customMemSize(4);
    manager.distributeMemSize(testing);
    
    // Debería asignarse al primer segmento de memoria
    if (manager.memAllocFirstFit(1, 10)) {
        std::cout << "Asignado proceso 1 de size 10 usando First Fit" << std::endl;
    } else {
        std::cout << "No se pudo asignar memoria para el proceso 1" << std::endl;
    }
    
    manager.memoryStatus();
    
    manager.freeMem(1);
    std::cout << "Proceso 1 liberado" << std::endl;
    
    manager.memoryStatus();

    // Debería asignarse al tercer segmento de memoria
    if (manager.memAllocBestFit(2, 20)) {
        std::cout << "Asignado proceso 2 de size 20 usando Best Fit" << std::endl;
    } else {
        std::cout << "No se pudo asignar memoria para el proceso 2" << std::endl;
    }

    // Debería asignarse al segundo segmento de memoria
    if (manager.memAllocWorstFit(3, 15)) {
        std::cout << "Asignado proceso 2 de size 15 usando Worst Fit" << std::endl;
    } else {
        std::cout << "No se pudo asignar memoria para el proceso 3" << std::endl;
    }

    manager.memoryStatus();

    manager.freeMem(2);
    std::cout << "Proceso 2 liberado" << std::endl;

    // No debería asignarse a algun segmento de memoria
    if (manager.memAllocFirstFit(4, 25)) {
        std::cout << "Asignado proceso 4 de size 25 usando Worst Fit" << std::endl;
    } else {
        std::cout << "No se pudo asignar memoria para el proceso 4" << std::endl;
    }

    // Debería asignarse al primer segmento de memoria
    if (manager.memAllocFirstFit(5, 5)) {
        std::cout << "Asignado proceso 5 de size 5 usando First Fit" << std::endl;
    } else {
        std::cout << "No se pudo asignar memoria para el proceso 3" << std::endl;
    }
    return;

    manager.memoryStatus();

    manager.freeMem(3);
    std::cout << "Proceso 3 liberado" << std::endl;

    manager.freeMem(5);
    std::cout << "Proceso 5 liberado" << std::endl;
}

void testingReaderClass() {
    Reader r;
    r.executeFileReading();
    r.executeAllocation();
    return;
}

int main() {
    int option;
    std::cout << "Opcion (1): Correr una función para probar la clase memoryManagement" << std::endl;
    std::cout << "Opcion (2): Hacer lectura desde un archivo de entrada y recibir la salida por pantalla" << std::endl;
    std::cin >> option;

    if (option == 1){
        testingMemoryManagementClass();
    } else if (option == 2){
        testingReaderClass();
    }

    return 0;
}