#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "grupo.hpp"
#include "pair.hpp"
#include "lista_elementos.hpp"
#include "instance.hpp"

using namespace std;

bool operator<(Pair const &a, Pair const &b)
{
    return a.distance_Element < b.distance_Element;
}
bool comparar_distancias(Pair &a, Pair &b)
{
    return a.distance_Element < b.distance_Element;
}
bool comparar_tam_maximo(Grupo grupo1, Grupo grupo2)
{
    return grupo1.tam_maximo < grupo2.tam_maximo;
}
bool comparar_tam_minimo(Grupo grupo1, Grupo grupo2)
{
    return grupo1.tam_minimo < grupo2.tam_minimo;
}

// Classe com funções auxiliares
class Funcoes
{
public:


    int quantidade_pares(int a)const {
        return a*(a-1)/2;
    }

    void ordenar_distancias(vector<Pair> &distances) const
    {
        std::sort(distances.begin(), distances.end(), comparar_distancias);
    }

    void ordenar_tam_maximo(vector<Grupo> &grupos) const
    {
        std::sort(grupos.begin(), grupos.end(), comparar_tam_maximo);
    }

    void ordenar_tam_minimo(vector<Grupo> &grupos) const
    {
        std::sort(grupos.begin(), grupos.end(), comparar_tam_minimo);
    }

    double media(vector<Pair> &distances) const
    {
        double soma = 0.0;
        for (long long unsigned int i = 0; i < distances.size(); i++)
        {
            soma += distances[i].distance_Element;
        }
        double resultado = soma / (double)distances.size();

        return resultado;
    }

    // adicionamos um elemento em um grupo
    // não confere se grupo está cheio
    void alocar_elemento(Grupo &grupo, vector<int> &elementos, int i) const
    {
        if (grupo.get_quantidade_elementos() == grupo.tam_maximo)
        {
            cout << "ERRO!!!!! TENTOU ADICIONAR ELEMENTO EM UM GRUPO CHEIO!!" << endl;
        }

        // grupo.quantidade_elementos+=1;
        grupo.elementos.push_back(elementos[i]);

        elementos.erase(elementos.begin() + i);
    }

    // usa a classe Lista_elementos
    void alocar_elemento2(Grupo &grupo, Lista_elementos &lista_elementos, int elemento) const
    {

        if (grupo.get_quantidade_elementos() == grupo.tam_maximo)
        {
            cout << "ERRO!!!!! TENTOU ADICIONAR ELEMENTO EM UM GRUPO CHEIO!!" << endl;
            cout << "elemento: " << elemento << endl;
        }

        if (lista_elementos.elementos[elemento] == true)
        {
            lista_elementos.remove(elemento);
            grupo.elementos.push_back(elemento);
        }
        else
        {
            cout << "elemento já alocado para algum grupo." << endl;
        }
    }

    // quando alocamos um elemento em um grupo precisamos ter certeza de que
    // ainda poderemos preencher o mínimo de elementos de todos os grupos.
    int alocar_elemento3(Grupo &grupo, Lista_elementos &lista_elementos, vector<int> elementos, int elemento, int &quantidade_elementos_minimos) const
    {

        cout << elemento << endl;
        if (grupo.get_quantidade_elementos() == grupo.tam_maximo)
        {
            cout << "ERRO!!!!! TENTOU ADICIONAR ELEMENTO EM UM GRUPO CHEIO!!" << endl;
        }
        if (lista_elementos.elementos[elemento] == false)
        {
            cout << "ELEMENTO JÁ FOI REMOVIDO!!!!!!!!!!!!" << endl;
            cout << "elemento: " << elemento << endl;
        }
        else
        {
            // removemos o elemento da lista_elementos
            lista_elementos.remove(elemento);

            // se o elemento estiver no final do vector<elementos> podemos
            // atualizar o vector<elementos> sem riscos
            if (elemento = elementos.back())
            {
                elementos.pop_back();
            }

            // coloca o elemento no grupo
            grupo.elementos.push_back(elemento);
            grupo.elementos.push_back(elemento);
            grupo.elementos.push_back(elemento);
            cout << "elemento do final: " << grupo.elementos.back() << endl;

            if (grupo.elementos.size() <= grupo.tam_minimo)
            {
                quantidade_elementos_minimos = quantidade_elementos_minimos - 1;
            }

            // com a classe lista_elementos nós podemos "remover" elementos
            // do nosso vector<elementos> enquanto os mantemos no vector.
            // Para isso, basta atualizarmos o tamanho de lista_elementos sempre
            // que mudamos o tamanho do vector (o remove faz isso),
            // e verificar se o elemento está
            // presente em lista elementos antes de removê-lo de vector.
            // também precisamos remover o elemento da lista elementos se
            // o removermos do vector<elementos>
        }

        return quantidade_elementos_minimos;
    }

    vector<int> get_elementos(vector<Pair> distances) const
    {
        vector<int> elementos;
        int tamanho;
        tamanho = distances[distances.size() - 1].second_Element + 1;
        for (int i = 0; i < tamanho; i++)
        {
            elementos.push_back(i);
        }
        return elementos;
    }

    vector<Grupo> get_grupos(const Instance& instance) const
    {

        vector<Grupo> grupos;

        for (int i = 0; i < instance.quant_Grup; i++)
        {
            Grupo grupo;
            grupo.i = i;
            grupo.tam_maximo = instance.arr_Tam_Max_Grup[i];
            grupo.tam_minimo = instance.arr_Tam_Min_Grup[i];
            grupos.push_back(grupo);
        }

        return grupos;
    }

    void imprimir_grupos(vector<Grupo> grupos) const
    {
        for (int i = 0; i < grupos.size(); i++)
        {
            cout << endl;
            cout << "grupo " << grupos[i].i << endl;
            grupos[i].imprimir();

            if (grupos[i].get_quantidade_elementos() == 0)
            {
                cout << "grupo sem elementos" << endl;
            }

            cout << endl;
        }
    }

    Pair get_pair(int elemento1, int elemento2, vector<Pair> &pares, int quantidade) const
    {
        elemento1 += 1;
        elemento2 += 1;

        int maior = elemento1;
        int menor = elemento2;
        if (elemento2 > elemento1)
        {
            maior = elemento2;
            menor = elemento1;
        }

        int position = (quantidade * (quantidade - 1) / 2) - (quantidade - menor) * (quantidade - menor - 1) / 2;

        position -= 1;

        while (pares[position].second_Element >= maior)
        {
            position -= 1;
        }

        return pares[position];
    }

    double get_total_grupo(Grupo grupo, vector<Pair> distances) const
    {

        int quantidade = grupo.elementos.size();
        double total = 0;
        Pair par;
        int quantidade_elementos;

        for (int i = 0; i < quantidade - 1; i++)
        {
            for (int i2 = i + 1; i2 < quantidade; i2++)
            {
                quantidade_elementos = distances[distances.size() - 1].second_Element + 1;
                par = get_pair(grupo.elementos[i], grupo.elementos[i2], distances, quantidade_elementos);
                total = total + (double)par.distance_Element;
            }
        }
        return total;
    }

    double get_total(vector<Grupo> grupos, const vector<Pair>& distances) const
    {
        double total = 0;
        double a;
        for (int i = 0; i < grupos.size(); i++)
        {
            a = get_total_grupo(grupos[i], distances);
            total += a;
        }

        return total;
    }

    // ATENÇÃO. não força a inserção em grupo que ainda não tem o tamanho mínimo cheio
    int get_best_group(vector<Grupo> grupos, int elemento, vector<Pair> distances) const
    {

        // criamos um array resultados com quantidade de grupos tamanho
        // cada posição do array contém um inteiro
        // para cada grupo compara a distância do elemento com x elementos do grupo
        // calcula a média
        // salva o resultado no array resultados
        // retornar o índice da posição que tem o maior valor

        // atenção! grupos ordenados não tem correspondência de índices com grupos desordenados
        // usar o atributo i da classe Grupo para resolver o problema

        // esse array contém, para cada grupo, um valor representando o quão vantajoso é colocar o elemento nesse grupo
        double *resultados = new double[grupos.size()];

        bool todos_grupos_cheios = true;

        // aqui fica o maior valor do array resultados
        int maior;
        // aqui fica a posição desse valor no array resultados, indicando qual o grupo
        int maior_position;

        int quantidade_elementos;
        quantidade_elementos = distances[distances.size() - 1].second_Element + 1;

        Pair par;

        // grupos se refere aos grupos disponíveis para alocar elementos. Não ao total de grupos
        // percorremos cada grupo, atribuindo um valor para a posição correspondente no vetor no final
        for (int i = 0; i < grupos.size(); i++)
        {

            resultados[i] = 0;

            if (grupos[i].get_quantidade_elementos() > 0)
            {

                for (int i2 = 0; i2 < grupos[i].get_quantidade_elementos(); i2++)
                {

                    par = get_pair(elemento, grupos[i].elementos[i2], distances, quantidade_elementos);
                    resultados[i] += (double)par.get_distance_Element();
                }

                resultados[i] = resultados[i] / (double)grupos[i].get_quantidade_elementos();
            }

            if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
            {
                resultados[i] = resultados[i] * 2;
            }

            if (grupos[i].get_quantidade_elementos() == grupos[i].tam_maximo)
            {
                resultados[i] = -10;
            }

            else
            {
                todos_grupos_cheios = false;
            }
        }

        // podemos adicionar um elemento em um grupo vazio, mas não em um grupo cheio
        maior = -5;
        for (int i = 0; i < grupos.size(); i++)
        {
            if (resultados[i] > maior)
            {
                maior = resultados[i];
                maior_position = i;
            }
        }

        if (todos_grupos_cheios)
        {
            cout << endl
                 << endl;
            cout << "ERRO!! NÃO HÁ ESPAÇO" << endl;
            cout << endl
                 << endl;
        }

        delete resultados;

        return grupos[maior_position].i;
    }

    // para inserir em grupos que ainda não preencheram o tamanho mínimo
    int get_best_group2(vector<Grupo> grupos, int elemento, vector<Pair> distances) const
    {

        // criamos um array resultados com quantidade de grupos tamanho
        // cada posição do array contém um inteiro
        // para cada grupo compara a distância do elemento com x elementos do grupo
        // calcula a média
        // salva o resultado no array resultados
        // retornar o índice da posição que tem o maior valor

        // atenção! grupos ordenados não tem correspondência de índices com grupos desordenados
        // usar o atributo i da classe Grupo para resolver o problema

        // esse array contém, para cada grupo, um valor representando o quão vantajoso é colocar o elemento nesse grupo
        double *resultados = new double[grupos.size()];

        bool todos_grupos_cheios = true;

        // aqui fica o maior valor do array resultados
        int maior;
        // aqui fica a posição desse valor no array resultados, indicando qual o grupo
        int maior_position;

        int quantidade_elementos;
        quantidade_elementos = distances[distances.size() - 1].second_Element + 1;

        Pair par;

        // grupos se refere aos grupos disponíveis para alocar elementos. Não ao total de grupos
        // percorremos cada grupo, atribuindo um valor para a posição correspondente no vetor no final
        for (int i = 0; i < grupos.size(); i++)
        {

            resultados[i] = 0;

            if (grupos[i].get_quantidade_elementos() > 0)
            {

                for (int i2 = 0; i2 < grupos[i].get_quantidade_elementos(); i2++)
                {

                    par = get_pair(elemento, grupos[i].elementos[i2], distances, quantidade_elementos);
                    resultados[i] += (double)par.get_distance_Element();
                }

                resultados[i] = resultados[i] / (double)grupos[i].get_quantidade_elementos();
            }

            if (grupos[i].get_quantidade_elementos() >= grupos[i].tam_minimo)
            {
                resultados[i] = -10;
            }

            if (grupos[i].get_quantidade_elementos() == grupos[i].tam_maximo)
            {
                resultados[i] = -20;
            }

            else
            {
                todos_grupos_cheios = false;
            }
        }

        // podemos adicionar um elemento em um grupo vazio, mas não em um grupo cheio
        maior = -5;
        for (int i = 0; i < grupos.size(); i++)
        {
            if (resultados[i] > maior)
            {
                maior = resultados[i];
                maior_position = i;
            }
        }

        if (todos_grupos_cheios)
        {
            cout << endl
                 << endl;
            cout << "ERRO!! NÃO HÁ ESPAÇO" << endl;
            cout << endl
                 << endl;
        }

        delete resultados;

        return grupos[maior_position].i;
    }

    // igual o get_best_group, mas aumenta o valor para um grupo proporcionalmente
    // ao tamanho máximo do grupo
    int get_best_group3(vector<Grupo> grupos, int elemento,vector<Pair> distances) const
    {

        // criamos um array resultados com quantidade de grupos tamanho
        // cada posição do array contém um inteiro
        // para cada grupo compara a distância do elemento com x elementos do grupo
        // calcula a média
        // salva o resultado no array resultados
        // retornar o índice da posição que tem o maior valor

        // atenção! grupos ordenados não tem correspondência de índices com grupos desordenados
        // usar o atributo i da classe Grupo para resolver o problema

        // esse array contém, para cada grupo, um valor representando o quão vantajoso é colocar o elemento nesse grupo
        double *resultados = new double[grupos.size()];

        bool todos_grupos_cheios = true;

        // aqui fica o maior valor do array resultados
        int maior;
        // aqui fica a posição desse valor no array resultados, indicando qual o grupo
        int maior_position;

        int quantidade_elementos;
        quantidade_elementos = distances[distances.size() - 1].second_Element + 1;

        Pair par;

        // grupos se refere aos grupos disponíveis para alocar elementos. Não ao total de grupos
        // percorremos cada grupo, atribuindo um valor para a posição correspondente no vetor no final
        for (int i = 0; i < grupos.size(); i++)
        {

            resultados[i] = 0;

            if (grupos[i].get_quantidade_elementos() > 0)
            {

                for (int i2 = 0; i2 < grupos[i].get_quantidade_elementos(); i2++)
                {

                    par = get_pair(elemento, grupos[i].elementos[i2], distances, quantidade_elementos);
                    resultados[i] += (double)par.get_distance_Element();
                }

                resultados[i] = resultados[i] / (double)grupos[i].get_quantidade_elementos();
            }

            resultados[i] = resultados[i] * ((double)(1.0 + (double)(((double)grupos[i].tam_maximo) / ((double)quantidade_elementos / 10.0))));

            if (grupos[i].get_quantidade_elementos() < grupos[i].tam_minimo)
            {
                resultados[i] = resultados[i] * 2;
            }

            if (grupos[i].get_quantidade_elementos() == grupos[i].tam_maximo)
            {
                resultados[i] = -10;
            }

            else
            {
                todos_grupos_cheios = false;
            }
        }

        // podemos adicionar um elemento em um grupo vazio, mas não em um grupo cheio
        maior = -5;
        for (int i = 0; i < grupos.size(); i++)
        {
            if (resultados[i] > maior)
            {
                maior = resultados[i];
                maior_position = i;
            }
        }

        if (todos_grupos_cheios)
        {
            cout << endl
                 << endl;
            cout << "ERRO!! NÃO HÁ ESPAÇO" << endl;
            cout << endl
                 << endl;
        }

        delete resultados;

        return grupos[maior_position].i;
    }


    void trocaElementos(Grupo& grupo1, Grupo& grupo2, int elementoGrupo1index, int elementoGrupo2index)const {

        int auxiliar = grupo1.elementos[elementoGrupo1index];  
         

        grupo1.elementos[elementoGrupo1index] = grupo2.elementos[elementoGrupo2index];
        grupo2.elementos[elementoGrupo2index] = auxiliar;

    }    

    void trocaElementos2(Grupo& grupo1, Grupo& grupo2) const{




    }


};
