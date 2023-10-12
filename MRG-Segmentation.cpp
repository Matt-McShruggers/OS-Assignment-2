#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

struct Proceso {
    int id;
    int size;
};

struct Segmento {
    int size;
    std::vector<Proceso> processes;
};

class SimulacionSegmentacion {
private:
    int memSize;
    std::vector<Segmento> segmentsOccupation;
public:
    SimulacionSegmentacion(int size){
        memSize = size;
        segmentsOccupation = {};
    }

    bool addSegment(int segmentSize){
        // Comprueba si la segmentacion es correcta
        int segmentMemTest = memSize;
        for (int i = 0; i < segmentsOccupation.size(); i++){
            segmentMemTest -= segmentsOccupation[i].size;
        }
        if (segmentMemTest < 0){
            std::cerr << "El segmento pide mas memoria de la que ya está disponible" << std::endl;
            return false;
        }

        // En caso correcto, se hace la creación normal del segmento
        Segmento s;
        s.size = segmentSize;
        s.processes = {};
        segmentsOccupation.push_back(s);
        return true;
    }

    bool addProcessAndAssignMemory(int PID, int pSize){
        Proceso p;
        p.id = PID;
        p.size = pSize;
        for (int i = 0; i < segmentsOccupation.size(); i++){
            if (segmentsOccupation[i].processes.empty() && p.size <= segmentsOccupation[i].size){
                segmentsOccupation[i].processes.push_back(p);
                return true;
            } else if (p.size <= segmentsOccupation[i].size) {
                int temporalSegSize = segmentsOccupation[i].size;
                for (int j = 0; j < segmentsOccupation[i].processes.size(); j++){
                    temporalSegSize -= segmentsOccupation[i].processes[j].size;
                }
                if (temporalSegSize <= 0) { 
                    continue; 
                } else if (temporalSegSize > 0 && temporalSegSize >= p.size){
                    segmentsOccupation[i].processes.push_back(p);
                    return true;
                }
            }
        }
        std::cerr << "El proceso no pudo ser asignado memoria" << std::endl;
        return false;
    }

    void liberarMemoria(int PID){
        for (int i = 0; i < segmentsOccupation.size(); i++){
            for (int j = 0; j < segmentsOccupation[i].processes.size(); j++){
                if (segmentsOccupation[i].processes[j].id == PID){
                    segmentsOccupation[i].processes.erase(segmentsOccupation[i].processes.begin()+j);
                    break;
                }
            }
        }
        return;
    }

    void imprimirEstadoMemoria(){
        std::cout << std::endl << "[ ESTADO DE LA MEMORIA SEGMENTADA: ]" << std::endl;
        for (int i = 0; i < segmentsOccupation.size(); i++){
            std::cout << "Segmento " << i << std::endl;
            std::cout << "Tamanio de memoria: " << segmentsOccupation[i].size << " | Procesos guardados: ";
            if (segmentsOccupation[i].processes.empty()){
                std::cout << std::endl << "  N/A" << std::endl << std::endl;
                continue;
            }
            for (int j = 0; j < segmentsOccupation[i].processes.size(); j++){
                std::cout << std::endl << "  ID de proceso: " << segmentsOccupation[i].processes[j].id << " | Tamanio de proceso: " << segmentsOccupation[i].processes[j].size;
            }
            std::cout << std::endl << std::endl;
        }
    }
};

int main(){
    std::cout << std::endl << "Creando memoria de 500 KB...";
    int memSize = 500;
    SimulacionSegmentacion simulador(memSize);

    std::cout << std::endl << "Adicionando 3 segmentos, S0 = 125 KB, S1 = 150 KB y S2 = 200 KB..." << std::endl;
    simulador.addSegment(125);
    simulador.addSegment(150);
    simulador.addSegment(200);

    simulador.imprimirEstadoMemoria();

    std::cout << std::endl << "Asignando 5 procesos a segmentos, P1 = 75 KB, P2 = 75 KB, P3 = 50 KB, P4 = 100 KB, P5 = 50 KB..." << std::endl;
    simulador.addProcessAndAssignMemory(1, 75);
    simulador.addProcessAndAssignMemory(2, 75);
    simulador.addProcessAndAssignMemory(3, 50);
    simulador.addProcessAndAssignMemory(4, 100);
    simulador.addProcessAndAssignMemory(5, 50);

    simulador.imprimirEstadoMemoria();

    std::cout << std::endl << "Liberando procesos 1, 3 y 5..." << std::endl;
    simulador.liberarMemoria(1);
    simulador.liberarMemoria(3);
    simulador.liberarMemoria(5);
    
    simulador.imprimirEstadoMemoria();
    return 0;
}