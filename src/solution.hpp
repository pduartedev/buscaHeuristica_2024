#pragma once

#include <iostream>
#include <algorithm>

#include "instance.hpp"
#include "pair.hpp"
#include "grupo.hpp"
#include "lista_elementos.hpp"
#include "funcoes.hpp"

using namespace std;
class Solution
{
public:
    Instance instance;
    double resultado;
    vector<Grupo> solucao;
    vector<Solution> vizinhos;    

    Solution()
    {
        // cout << "SOLUTION INICIADA";
    }
    Solution(Instance instance)
    {
        this->instance = instance;
    }

    // distribui os elementos aleatoriamente para ter um resultado ruim para comparar com a heurística
    vector<Grupo> calcular_resultado_ruim()
    {
        Funcoes funcoes;
        vector<int> elementos;
        vector<Grupo> grupos;

        elementos = funcoes.get_elementos(instance.arr_Pair);
        grupos = funcoes.get_grupos(instance);

        while (elementos.size() > 0)
        {
            for (int i = 0; i < instance.quant_Grup; i++)
            {
                if (grupos[i].elementos.size() < grupos[i].tam_minimo)
                {
                    grupos[i].elementos.push_back(elementos[elementos.size() - 1]);
                    elementos.pop_back();
                }
            }
            for (int i = 0; i < instance.quant_Grup; i++)
            {
                if (elementos.size() == 0)
                {
                    break;
                }
                if (grupos[i].elementos.size() < grupos[i].tam_maximo)
                {
                    grupos[i].elementos.push_back(elementos[elementos.size() - 1]);
                    elementos.pop_back();
                }
            }
        }

        return grupos;
    }
    

    vector<Grupo> calcular_resultado()
    {
        Funcoes funcoes;

        vector<int> elementos = funcoes.get_elementos(instance.arr_Pair);
        vector<Grupo> grupos = funcoes.get_grupos(instance);

        // nessa etapa garantimos que todos os tamanhos mínimos foram preenchidos
        bool while1 = true;
        while (while1)
        {
            while1 = false;
            for (int i = 0; i < grupos.size(); i++)
            {
                if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                {
                    funcoes.alocar_elemento(grupos[i], elementos, elementos.back());
                    while1 = true;
                }
            }
        }

        // adiciona os elementos restantes nas melhores posições
        while (elementos.size() > 0)
        {
            int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
            funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
        }

        return grupos;
    }

    vector<Grupo> calcular_resultado2()
    {
        Funcoes funcoes;
        vector<int> elementos = funcoes.get_elementos(instance.arr_Pair);
        vector<Grupo> grupos = funcoes.get_grupos(instance);

        int space = 0;
        for (int i = 0; i < grupos.size(); i++)
        {
            space += grupos[i].tam_minimo;
        }

        bool while1 = true;
        bool primeira_vez_no_while = true;

        while (while1)
        {
            while1 = false;

            if (space == elementos.size() or primeira_vez_no_while)
            {
                primeira_vez_no_while = false;
                for (int i = 0; i < grupos.size(); i++)
                {
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        funcoes.alocar_elemento(grupos[i], elementos, elementos.back());
                        space -= 1;
                        while1 = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < grupos.size(); i++)
                {
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        while1 = true;
                    }
                }

                int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
                funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());

                if (grupos[grupos[position].i].get_quantidade_elementos() <= grupos[grupos[position].i].tam_minimo)
                {
                    space -= 1;
                }
            }
        }

        while (elementos.size() > 0)
        {
            int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
            funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
        }

        return grupos;
    }

    vector<Grupo> calcular_resultado3()
    {
        Funcoes funcoes;
        vector<int> elementos = funcoes.get_elementos(instance.arr_Pair);
        vector<Grupo> grupos = funcoes.get_grupos(instance);
        int space = 0;

        for (int i = 0; i < grupos.size(); i++)
        {
            space += grupos[i].tam_minimo;
        }

        // nessa etapa garantimos que todos os tamanhos mínimos foram preenchidos
        bool while1 = true;

        while (while1)
        {
            while1 = false;

            // se espaço é igual a quantidade restante de elementos, então
            // necessariamente precisamos alocar elementos em grupos
            // que ainda não tiveram o tamanho mínimo preenchido
            if (space == elementos.size())
            {
                // cout<<"caso 1"<<endl;
                for (int i = 0; i < grupos.size(); i++)
                {
                    // se ainda tem grupos sem tamanho mínimo preenchido continuamos no while
                    // e adicionamos um elemento no grupo que não tem o
                    // tamanho mínimo preenchido
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        funcoes.alocar_elemento(grupos[i], elementos, elementos.back());
                        space -= 1;
                        while1 = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < grupos.size(); i++)
                {
                    // se ainda tem grupos sem tamanho mínimo preenchido continuamos no while
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        while1 = true;
                    }
                }

                int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
                funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
                if (grupos[grupos[position].i].get_quantidade_elementos() <= grupos[grupos[position].i].tam_minimo)
                {
                    space -= 1;
                }
            }
        }

        // adiciona os elementos restantes nas melhores posições
        while (elementos.size() > 0)
        {
            int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
            funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
        }

        return grupos;
    }

    vector<Grupo> calcular_resultado4()
    {
        Funcoes funcoes;
        vector<int> elementos = funcoes.get_elementos(instance.arr_Pair);
        vector<Grupo> grupos = funcoes.get_grupos(instance);

        int space = 0;
        for (int i = 0; i < grupos.size(); i++)
        {
            space += grupos[i].tam_minimo;
        }

        // nessa etapa garantimos que todos os tamanhos mínimos foram preenchidos
        bool while1 = true;
        bool primeira_vez_no_while = true;

        while (while1)
        {
            while1 = false;

            // se espaço é igual a quantidade restante de elementos, então
            // necessariamente precisamos alocar elementos em grupos
            // que ainda não tiveram o tamanho mínimo preenchido
            if (space == elementos.size() or primeira_vez_no_while)
            {
                if (primeira_vez_no_while)
                {
                    for (int i = 0; i < grupos.size(); i++)
                    {
                        // se ainda tem grupos sem tamanho mínimo preenchido continuamos no while
                        if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                        {
                            funcoes.alocar_elemento(grupos[i], elementos, elementos.back());
                            space -= 1;
                            while1 = true;
                        }
                    }
                }

                primeira_vez_no_while = false;

                for (int i = 0; i < grupos.size(); i++)
                {
                    // se ainda tem grupos sem tamanho mínimo preenchido continuamos no while
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        int position = funcoes.get_best_group2(grupos, elementos.back(), instance.arr_Pair);
                        funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
                        space -= 1;
                        while1 = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < grupos.size(); i++)
                {
                    // se ainda tem grupos sem tamanho mínimo preenchido continuamos no while
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        while1 = true;
                    }
                }

                int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
                funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());

                if (grupos[grupos[position].i].get_quantidade_elementos() <= grupos[grupos[position].i].tam_minimo)
                {
                    space -= 1;
                }
            }
        }

        // adiciona os elementos restantes nas melhores posições
        while (elementos.size() > 0)
        {
            int position = funcoes.get_best_group(grupos, elementos.back(), instance.arr_Pair);
            funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
        }

        return grupos;
    }

    // ESSE É A FUNÇÃO USADA NO TRABALHO, COM A  HEURÍSTICA
    vector<Grupo> calcular_resultado5()
    {
        Funcoes funcoes;
        vector<int> elementos = funcoes.get_elementos(instance.arr_Pair);
        vector<Grupo> grupos = funcoes.get_grupos(instance);
        int space = 0;

        for (int i = 0; i < grupos.size(); i++)
        {
            space += grupos[i].tam_minimo;
        }

        bool while1 = true;
        bool primeira_vez_no_while = true;

        while (while1)
        {
            while1 = false;

            if (space == elementos.size() or primeira_vez_no_while)
            {
                if (primeira_vez_no_while)
                {
                    for (int i = 0; i < grupos.size(); i++)
                    {
                        if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                        {
                            funcoes.alocar_elemento(grupos[i], elementos, elementos.back());
                            space -= 1;
                            while1 = true;
                        }
                    }
                }

                primeira_vez_no_while = false;

                for (int i = 0; i < grupos.size(); i++)
                {
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        int position = funcoes.get_best_group3(grupos, elementos.back(), instance.arr_Pair);
                        funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
                        space -= 1;
                        while1 = true;
                    }
                }
            }
            else
            {
                for (int i = 0; i < grupos.size(); i++)
                {
                    if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
                    {
                        while1 = true;
                    }
                }

                int position = funcoes.get_best_group3(grupos, elementos.back(), instance.arr_Pair);
                funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
                if (grupos[grupos[position].i].get_quantidade_elementos() <= grupos[grupos[position].i].tam_minimo)
                {
                    space -= 1;
                }
            }
        }

        while (elementos.size() > 0)
        {
            int position = funcoes.get_best_group3(grupos, elementos.back(), instance.arr_Pair);
            funcoes.alocar_elemento(grupos[grupos[position].i], elementos, elementos.back());
        }

        this->solucao = grupos;

        return grupos;
    }

    double limite_superior()
    {
        int tamanho = instance.arr_Pair.size();
        double total = 0.0;
        vector<Pair> distances = instance.arr_Pair;

        for (int i = 0; i < tamanho; i++)
        {

            total += distances[i].get_distance_Element();
        }
        return total;
    }

    double limite_superior2()
    {
        Funcoes funcoes;
        vector<Grupo> grupos = funcoes.get_grupos(instance);
        int quantidade_elementos = instance.quant_Elem;
        vector<Grupo> grupos_ordenados_por_tamanho_minimo = grupos;
        funcoes.ordenar_tam_minimo(grupos_ordenados_por_tamanho_minimo);
        vector<Grupo> grupos_ordenados_por_tamanho_maximo = grupos;
        funcoes.ordenar_tam_maximo(grupos_ordenados_por_tamanho_maximo);

        for (int i = 0; i < grupos.size(); i++)
        {
            grupos_ordenados_por_tamanho_minimo[i].tam_maximo = grupos_ordenados_por_tamanho_maximo[i].tam_maximo;
        }

        for (int i = 0; i < grupos.size(); i++)
        {
            grupos[i].i = grupos[i].tam_minimo;
            quantidade_elementos -= grupos[i].i;
        }

        for (int i = grupos_ordenados_por_tamanho_minimo.size() - 1; i >= 0; i--)
        {

            while (grupos_ordenados_por_tamanho_minimo[i].i < grupos_ordenados_por_tamanho_minimo[i].tam_maximo and quantidade_elementos > 0)
            {
                grupos_ordenados_por_tamanho_minimo[i].i += 1;
                quantidade_elementos -= 1;
            }
        }

        int quantidade_pares = 0;

        for (int i = 0; i < grupos_ordenados_por_tamanho_minimo.size(); i++)
        {
            quantidade_pares += funcoes.quantidade_pares(grupos_ordenados_por_tamanho_minimo[i].i);
        }

        vector<Pair> distancias_ordenadas = instance.arr_Pair;
        funcoes.ordenar_distancias(distancias_ordenadas);
        double total = 0.0;
        int i2 = distancias_ordenadas.size() - 1;

        for (int i = quantidade_pares - 1; i >= 0; i--)
        {
            total += (double)distancias_ordenadas[i2].get_distance_Element();
            i2 -= 1;
        }

        return total;
    }

    /////////////////////////////////////////
    // funções para vizinhança///////////////
    /////////////////////////////////////////


    /////////////////////////////////////////
    /////////////////////////////////////////
    /////////////////////////////////////////
    //primeira vizinhança////////////////////   
    /////////////////////////////////////////

    /*
    void atribuir_ponto_elemento(int i, int i2)
    {
    }

    void atribuir_pontos()
    {
        // quanto maior a pontuação, mais o elemento está bem naquele grupo
        for (int i = 0; i < this->solucao.size(); i++)
        {
            for (int i2 = 0; i < this->solucao[i].elementos.size(); i++)
            {
                atribuir_ponto_elemento(i, i2);
            }
        }
    }

    */

    void get_todos_vizinhos()
    {          
        Funcoes funcoes;
        vector<Solution> vizinhos;
        vector<Grupo> solucao_atual = this->solucao;

        // fazer para todos os pares de grupos
        for (int i = 0; i < solucao_atual.size() - 1; i++)
        {
            for (int i2 = i + 1; i2 < solucao_atual.size(); i2++)
            {
                // cout<<i<<", "<<i2 <<endl;
                // para cada par de grupos nós trocamos o primeiro elemento
                // de um grupo com o primeiro elemento de outro
                // e adicionamos o resultado no array de vizinhos
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos.push_back(solucao1);
                vizinhos.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos.back().vizinhos = {};
                vizinhos.back().vizinhos.push_back(*this);

                // restauramos a solução atual
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);
            }
        }

        /*
        //testa troca de elementos
        funcoes.trocaElementos(solucao_atual[0],solucao_atual[1],0,0);

        //passa a solução com elementos trocados para o vizinho
        Solution solucao1;
        solucao1.instance = this->instance;
        vizinhos.push_back(solucao1);
        vizinhos.back().solucao = solucao_atual;

        */

        // agora o primeiro vizinho tem a solução com o primeiro elemento do grupo 1 trocado com o primeiro elemento
        // do grupo 2

        this->vizinhos = vizinhos;
    }
   
    // geramos a lista de vizinhos antes de usar as funções tem_maior_vizinho e maior_vizinho
    // melhor melhora
    // retorna índice do melhor vizinho
    int maior_vizinho()
    {
        Funcoes funcoes;
        int index_resultado = 0;
        vector<Solution> lista_vizinhos = this->vizinhos;

        if (lista_vizinhos.empty())
        {
            cout << "Não há vizinhos na lista de vizinhos" << endl;
        }
        else
        {
            double resultado = -1;
            double auxiliar;
            for (int i = 0; i < lista_vizinhos.size(); i++)
            {
                auxiliar = funcoes.get_total(lista_vizinhos[i].solucao, lista_vizinhos[i].instance.arr_Pair);

                // se a solução é melhor que a melhor solução até o momento
                if (auxiliar > resultado)
                {
                    resultado = auxiliar;
                    // salvamos o índice do melhor vizinho até o momento
                    index_resultado = i;
                }
            }
        }

        return index_resultado;
    }

    // checa se algum vizinho é melhor que o resultado atual
    // tem que gerar os vizinhos antes
    int tem_maior_vizinho()
    {
        Funcoes funcoes;
        int index = -1;
        int auxiliar = maior_vizinho();
        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_vizinho = funcoes.get_total(this->vizinhos[auxiliar].solucao, this->instance.arr_Pair);

        // se o resultado atual for maior que o vizinho, retonamos -1
        if (resultado_atual > resultado_vizinho)
        {
            index = -1;
        }
        else
        {
            index = auxiliar;
        }

        // retorna -1 se a solução atual é melhor, ou o índice do vizinho se algum vizinho for melhor
        return index;
    }

    int get_primeira_melhora()
    {
        Funcoes funcoes;
        vector<Solution> vizinhos;
        vector<Grupo> solucao_atual = this->solucao;
        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_vizinho;
        resultado_vizinho = -1;
        int index = -1;
        int i = 0;
        int i2 = 0;

        while (resultado_atual > resultado_vizinho and i < solucao_atual.size() - 1)
        {
            i2 = i + 1;
            while (resultado_atual > resultado_vizinho and i2 < solucao_atual.size())
            {
                // vizinhos.push_back(*this);
                // resultado_vizinho+=10000;
                // cout<<"a"<<endl;

                // troca elementos de dois grupos da solução
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos.push_back(solucao1);
                vizinhos.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos.back().vizinhos = {};
                vizinhos.back().vizinhos.push_back(*this);

                // restauramos a solução atual
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);

                // atualiza o valor do vizinho, para parar quando for maior que o atual
                resultado_vizinho = funcoes.get_total(vizinhos.back().solucao, this->instance.arr_Pair);

                i2++;
            }

            i++;
        }

        this->vizinhos = vizinhos;

        /*
        //se nenhum vizinho é melhor que a solução atual
        if(resultado_vizinho < resultado_atual){
            return -1;
        }

        else{
            return this->vizinhos.back();
        }
        */

        if (resultado_vizinho > resultado_atual)
        {
            index = vizinhos.size() - 1;
        }

        return index;
    }

    int get_melhor_melhora()
    {           
        
        /*
        get_todos_vizinhos();               

        int index = tem_maior_vizinho();
        */
        int index = -1;
        
        Funcoes funcoes;
        Solution vizinho_atual;
        Solution vizinho_melhor;

        vector<Solution> vizinhos2;

        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_melhor = resultado_atual;

        vector<Grupo> solucao_atual = this->solucao;

        // fazer para todos os pares de grupos
        for (int i = 0; i < solucao_atual.size() - 1; i++)
        {
            for (int i2 = i + 1; i2 < solucao_atual.size(); i2++)
            {
                // cout<<i<<", "<<i2 <<endl;
                // para cada par de grupos nós trocamos o primeiro elemento
                // de um grupo com o primeiro elemento de outro
                // e adicionamos o resultado no array de vizinhos
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos2.push_back(solucao1);
                vizinhos2.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos2.back().vizinhos = {};
                vizinhos2.back().vizinhos.push_back(*this);

                // restauramos a solução atual
                funcoes.trocaElementos(solucao_atual[i], solucao_atual[i2], 0, 0);


                //mantemos apenas o vizinho melhor e o atual
                vizinho_atual = vizinhos2.back();

                //removemos o vizinho da lista de vizinhos para não gastar memória
                vizinhos2.pop_back();

                resultado_atual = funcoes.get_total(vizinho_atual.solucao, this->instance.arr_Pair);

                if(resultado_atual> resultado_melhor){
                    resultado_melhor = resultado_atual;
                    vizinho_melhor = vizinho_atual;
                    index = 0;
                }
            }
        }

        this->vizinhos.push_back(vizinho_melhor);

        return index;
    }


















































    /////////////////////////////////////////
    /////////////////////////////////////////
    /////////////////////////////////////////
    //segunda vizinhança/////////////////////    
    /////////////////////////////////////////

    
    void get_todos_vizinhos2()
    {          
        Funcoes funcoes;
        vector<Solution> vizinhos;
        vector<Grupo> solucao_atual = this->solucao;

        // fazer para todos os pares de grupos
        for (int i = 0; i < solucao_atual.size() - 1; i++)
        {
            for (int i2 = i + 1; i2 < solucao_atual.size(); i2++)
            {
                // cout<<i<<", "<<i2 <<endl;
                // para cada par de grupos nós trocamos o primeiro elemento
                // de um grupo com o primeiro elemento de outro
                // e adicionamos o resultado no array de vizinhos
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos.push_back(solucao1);
                vizinhos.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos.back().vizinhos = {};
                vizinhos.back().vizinhos.push_back(*this);

                // restauramos a solução atual
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);
            }
        }

        /*
        //testa troca de elementos
        funcoes.trocaElementos(solucao_atual[0],solucao_atual[1],0,0);

        //passa a solução com elementos trocados para o vizinho
        Solution solucao1;
        solucao1.instance = this->instance;
        vizinhos.push_back(solucao1);
        vizinhos.back().solucao = solucao_atual;

        */

        // agora o primeiro vizinho tem a solução com o primeiro elemento do grupo 1 trocado com o primeiro elemento
        // do grupo 2

        this->vizinhos = vizinhos;
    }
   
    // geramos a lista de vizinhos antes de usar as funções tem_maior_vizinho e maior_vizinho
    // melhor melhora
    // retorna índice do melhor vizinho
    int maior_vizinho2()
    {
        Funcoes funcoes;
        int index_resultado = 0;
        vector<Solution> lista_vizinhos = this->vizinhos;

        if (lista_vizinhos.empty())
        {
            cout << "Não há vizinhos na lista de vizinhos" << endl;
        }
        else
        {
            double resultado = -1;
            double auxiliar;
            for (int i = 0; i < lista_vizinhos.size(); i++)
            {
                auxiliar = funcoes.get_total(lista_vizinhos[i].solucao, lista_vizinhos[i].instance.arr_Pair);

                // se a solução é melhor que a melhor solução até o momento
                if (auxiliar > resultado)
                {
                    resultado = auxiliar;
                    // salvamos o índice do melhor vizinho até o momento
                    index_resultado = i;
                }
            }
        }

        return index_resultado;
    }

    // checa se algum vizinho é melhor que o resultado atual
    // tem que gerar os vizinhos antes
    int tem_maior_vizinho2()
    {
        Funcoes funcoes;
        int index = -1;
        int auxiliar = maior_vizinho();
        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_vizinho = funcoes.get_total(this->vizinhos[auxiliar].solucao, this->instance.arr_Pair);

        // se o resultado atual for maior que o vizinho, retonamos -1
        if (resultado_atual > resultado_vizinho)
        {
            index = -1;
        }
        else
        {
            index = auxiliar;
        }

        // retorna -1 se a solução atual é melhor, ou o índice do vizinho se algum vizinho for melhor
        return index;
    }

    int get_primeira_melhora2()
    {
        Funcoes funcoes;
        vector<Solution> vizinhos;
        vector<Grupo> solucao_atual = this->solucao;
        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_vizinho;
        resultado_vizinho = -1;
        int index = -1;
        int i = 0;
        int i2 = 0;

        while (resultado_atual > resultado_vizinho and i < solucao_atual.size() - 1)
        {
            i2 = i + 1;
            while (resultado_atual > resultado_vizinho and i2 < solucao_atual.size())
            {
                // vizinhos.push_back(*this);
                // resultado_vizinho+=10000;
                // cout<<"a"<<endl;

                // troca elementos de dois grupos da solução
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos.push_back(solucao1);
                vizinhos.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos.back().vizinhos = {};
                vizinhos.back().vizinhos.push_back(*this);

                // restauramos a solução atual
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                // atualiza o valor do vizinho, para parar quando for maior que o atual
                resultado_vizinho = funcoes.get_total(vizinhos.back().solucao, this->instance.arr_Pair);

                i2++;
            }

            i++;
        }

        this->vizinhos = vizinhos;

        /*
        //se nenhum vizinho é melhor que a solução atual
        if(resultado_vizinho < resultado_atual){
            return -1;
        }

        else{
            return this->vizinhos.back();
        }
        */

        if (resultado_vizinho > resultado_atual)
        {
            index = vizinhos.size() - 1;
        }

        return index;
    }

    int get_melhor_melhora2()
    {
        int index = -1;
        
        Funcoes funcoes;
        Solution vizinho_atual;
        Solution vizinho_melhor;

        vector<Solution> vizinhos2;

        double resultado_atual = funcoes.get_total(this->solucao, this->instance.arr_Pair);
        double resultado_melhor = resultado_atual;

        vector<Grupo> solucao_atual = this->solucao;

        for (int i = 0; i < solucao_atual.size() - 1; i++)
        {
            for (int i2 = i + 1; i2 < solucao_atual.size(); i2++)
            {
                Funcoes funcoes_local;
                funcoes_local.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                Solution solucao1;
                solucao1.instance = this->instance;
                vizinhos2.push_back(solucao1);
                vizinhos2.back().solucao = solucao_atual;
                vizinhos2.back().vizinhos = {};
                vizinhos2.back().vizinhos.push_back(*this);

                funcoes_local.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                vizinho_atual = vizinhos2.back();
                vizinhos2.pop_back();

                resultado_atual = funcoes_local.get_total(vizinho_atual.solucao, this->instance.arr_Pair);

                if (resultado_atual > resultado_melhor)
                {
                    resultado_melhor = resultado_atual;
                    vizinho_melhor = vizinho_atual;
                    index = 0;
                }
            }
        }

        this->vizinhos.push_back(vizinho_melhor);

        return index;
    }

};
