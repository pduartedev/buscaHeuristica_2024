#pragma once

#include <iostream>

#include "solution.hpp"

using namespace std;

class Lista_tabu{

    public:

    Solution* tabu_list;
    int last;
    int tamanho;

    Lista_tabu(int tamanho1){
        this->tamanho = tamanho1;    
        this->tabu_list = new Solution[this->tamanho];
        last = -1;    
    }

    ~Lista_tabu(){
        delete[] this->tabu_list;
    }

    void add(Solution solution){

        
        //primeiro elemento adicionado na lista
        if(this->last == -1){
            this->last = 0;
            this->tabu_list[0] = solution;
            cout<<this->tabu_list[0].solucao[0].elementos.size();
        }
        else{
            if(this->last == this->tamanho - 1){
                this->tabu_list[0] = solution;
                this->last = 0;
            }
            else{
                this->tabu_list[last+1] = solution;
                this->last++;
            }
        }
                

    }  
};