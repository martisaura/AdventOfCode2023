// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin;
    fin.open("input.txt");
    if (!fin.is_open()) std::cout << "error" << endl;
    string lectura;
    int suma = 0;
    vector<string> numeros = { "zero","one","two","three","four","five","six","seven","eight","nine" }; //PER PROBLEMA 2
    vector<int> pos = { 0,0,0,0,0,0,0,0,0,0 };                                                          //PER PROBLEMA 2

    while (fin >> lectura) {
        int primer = -1, ultim=0;
        for (int i = 0; i < pos.size(); ++i) pos[i] = 0;
        for (char c : lectura) {
            int valor = c-48;
            if (valor >= 0 && valor <= 9) {
                if (primer == -1) primer = valor;
                ultim = valor;
            }

            //PROBLEMA 2
            for (int i = 0; i < 10; ++i) {
                if (numeros[i][pos[i]] == c) {
                    ++pos[i];
                    if (pos[i] == numeros[i].size()) {
                        if (primer == -1) primer = i;
                        ultim = i;
                    }
                }
                else {
                    if (numeros[i][0] == c) pos[i] = 1;
                    else pos[i] = 0;
                }
            }
            //FI PROBLEMA 2

        }
        suma += ((10 * primer) + ultim);
    }
    std::cout << suma << endl;
}