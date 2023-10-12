#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

struct Pagina {
    int idProceso;
};

struct Proceso {
    int id;
    int size;
    std::vector<int> assignedPages;
};

class SimulacionPaginacion {
private:
    int memSize;
    int pageSize;
    std::vector<Pagina> pagedMemory;
    std::vector<Proceso> processes;
public:
    SimulacionPaginacion(int size, int pagSize){
        memSize = size;
        pageSize = pagSize;
        int numOfPages = memSize/pageSize;
        pagedMemory.resize(numOfPages, {-1});
    }

    bool asignarMemoria(int processID, int size){
        Proceso p;
        p.id = processID;
        p.size = size;
        if (p.size > pageSize){
            float pageSizeCopy = static_cast<float>(pageSize);
            float processSizeCopy = static_cast<float>(p.size);
            double pagesRequired = std::ceil(processSizeCopy/pageSizeCopy);
            for (int i = 0; i < pagedMemory.size(); i++){
                if (pagesRequired == 0) break;
                if (pagedMemory[i].idProceso == -1){
                    pagedMemory[i].idProceso = p.id;
                    p.assignedPages.push_back(i);
                    pagesRequired--;
                }
            }
            if (pagesRequired > 0) {
                std::cerr << "No hay suficientes paginas para asignarle memoria a este proceso." << std::endl;
                return false;
            } 
        } else {
            for (int j = 0; j < pagedMemory.size(); j++){
                if (pagedMemory[j].idProceso == -1){
                    pagedMemory[j].idProceso = p.id;
                    p.assignedPages.push_back(j);
                    processes.push_back(p);
                    return true;
                }
            }
            std::cerr << "No hay paginas disponibles para asignarle memoria a este proceso." << std::endl;
            return false;
        }
        processes.push_back(p);
        return true;
    }

    void liberarMemoria(int processID){
        for (int i = 0; i < pagedMemory.size(); i++){
            if (pagedMemory[i].idProceso == processID){
                pagedMemory[i].idProceso = -1;
            }
        }
        for (int j = 0; j < processes.size(); j++){
            if (processes[j].id == processID){
                processes.erase(processes.begin()+j);
                break;
            }
        }
        return;
    }

    void imprimirEstadoMemoria(){
        std::cout << std::endl << "[ Estado de la memoria paginada: ]" << std::endl;
        for (int i = 0; i < pagedMemory.size(); i++){
            std::cout << pagedMemory[i].idProceso << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Procesos en memoria:" << std::endl;
        for (int j = 0; j < processes.size(); j++){
            std::cout << "ID de Proceso: " << processes[j].id << " | Tamanio: " << processes[j].size << " | Paginas: ";
            for (int page : processes[j].assignedPages){
                std::cout << page << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main(){
    std::cout << std::endl << "Creando memoria de 120 KB con paginas de 20 KB...";
    int memSize = 120;
    int pageSize = 20;
    SimulacionPaginacion simulador(memSize, pageSize);

    std::cout << std::endl << "Asignandole memoria a 3 procesos, P1 = 30, P2 = 40 y P3 = 15 KBs..." << std::endl;
    simulador.asignarMemoria(1, 30);
    simulador.asignarMemoria(2, 40);
    simulador.asignarMemoria(3, 15);

    simulador.imprimirEstadoMemoria();

    std::cout << std::endl << "Liberando los procesos P1 y P2" << std::endl;
    simulador.liberarMemoria(1);
    simulador.liberarMemoria(2);

    std::cout << std::endl << "Asignandole memoria a 2 procesos, P4 = 75 y P5 = 20 KBs..." << std::endl;
    simulador.asignarMemoria(4, 75);
    simulador.asignarMemoria(5, 20);

    simulador.imprimirEstadoMemoria();
    return 0;
}