#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <cmath>
using namespace std;

int main()
{
	map<string, int> maxColors;							//Guardem el maxim de cubs d'un mateix color en un mapa
	maxColors.insert( pair<string,int>("red", 12) );	
	maxColors.insert(pair<string, int>("green", 13));
	maxColors.insert(pair<string, int>("blue", 14));

	// PROBLEMA 2
	map<string,int> minColors;							//El m�nim sempre ser� 0, en cas que no s'agafi cap d'aquell color
	minColors.insert(pair<string, int>("red", 0));
	minColors.insert(pair<string, int>("green", 0));
	minColors.insert(pair<string, int>("blue", 0));
	//Fi estructura del problema 2

	ifstream file;
	file.open("input.txt");
	if (!file.is_open()) std::cout << "error" << endl;
	string input;
	int suma = 0;
	while (getline(file,input)) { // Llegim la linia
		stringstream linia(input);	// Guardem la linia al stringstream per poder llegir els valors
		string lectura;	
		linia >> lectura;	// Llegim "Game"
		linia >> lectura;	// Llegim el numero seguit de ':'. //Realment ningu ens assegura que les partides tingui ID consecutiu o ordenat
		lectura.erase(lectura.size() - 1);	// Treiem els dos punts (':') del final del numero
		int partida = stoi(lectura);		// Guardem el numero
		int quantitat;
		bool validGame = true;				// Ens dir� si la partida es possible
		linia >> quantitat;					// Llegim quants cubs ha tret
		linia >> lectura;					// Llegim de quin color son els cubs
		char comp = lectura[lectura.size() - 1];	// Guardem l'ultim char per saber si queden mes cubs despr�s	

		while (validGame && (comp == ',' || comp == ';')) {		// Mirem si es l'�ltim cub
			lectura.erase(lectura.size() - 1);					// Treiem el signe de puntuaci�
			//validGame = ( quantitat <= maxColors.at(lectura) );	// comprovem si es una soluci� v�lida -> problema 1
			
			minColors.at(lectura) = max(minColors.at(lectura), quantitat);	// Per al problema 2. Actualitzem el m�nim de cubs necessaris del color al 
																			// m�xim de cubs d'aquell color que hem tret
			
			linia >> quantitat >> lectura;						// Llegim la seguent parella quantitat-color
			comp = lectura[lectura.size() - 1];					// Actualitzem l'ultim char per saber si despr�s en quedaran m�s
		}
																			// No cal treure l'�ltim char de lectura degut a que l'acc�s al mapa nom�s el fem
																			// si l'�ltim char no es un signe de puntuaci�
		if (validGame) { 
			//validGame = (quantitat <= maxColors.at(lectura));				// Comparaci� per l'�ltim cas, ja que no entrem al while -> problema 1
			minColors.at(lectura) = max(minColors.at(lectura), quantitat);	
		}
		
		//PROBLEMA 1
		// if (validGame) suma += partida; // Al problema 1 estem sumant el id de la partida

		//PROBLEMA 2
		if (validGame) suma += ( minColors.at("red") * minColors.at("green") * minColors.at("blue") );	// En el problema 2, sumem la multiplicaci� del m�nim
																										// de cubs de cada color.
																										// Si els colors no fossin fixos, es podria fer
																										// 
																										// int sum = 1;
																										// for(pair<string,int>& val : minColors) sum *= val.second;
																										// suma += sum;
																										// 
																										// (El codi est� fet en un moment i potser no funciona tal com
																										// est� ara i s'hauria de canviar lleugerament)
																										

		//Reiniciem el m�nim de cubs de cada color
		minColors.at("red") = 0;
		minColors.at("green") = 0;
		minColors.at("blue") = 0;
	}
	std::cout << suma << endl;
}

