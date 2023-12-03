#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

bool checkIfValid(const int& x, const int& y, const vector< vector<char> >& mat) {

	int lineSize = mat[x].size();
	int matSize = mat.size();


	for (int i = x - 1; i <= x + 1; ++i) {												// Comencem per la línia de sobre del digit que hem trobat
		if (i >= 0 && i < matSize) {													// Comprovem que no estiguem fora de la matriu

			for (int j = y - 1; j <= y + 1; ++j) {										// Comencem per l'esquerra del dígit que hem trobat

				if (j >= 0 && j < lineSize) {											// Comprovem que no estiguem fora de la matriu
					char actual = mat[i][j];											// Per simplicitat end guardem el char que anem a comprovar
					if (actual != '.' && ( actual < 48 || actual > 57)) return true;	// Si el char no es un '.' ni un dígit, aleshores hem trobat un símbol
				}

			}

		}
	}

	return false;
}

int getNumber(const int& i, const int& j, const vector<vector<char>>& mat) {
	int numIni = j;
	int valor = 0;
	while (numIni > 0 && mat[i][numIni - 1] >= 48 && mat[i][numIni - 1] <= 57) --numIni;
	while (numIni < mat[i].size() && mat[i][numIni] >= 48 && mat[i][numIni] <= 57) {
		valor = 10 * valor + mat[i][numIni] - 48;
		++numIni;
	}
	return valor;
}

int main()
{
	ifstream file;
	file.open("input.txt");
	string linia;
	char c;

	vector< vector<char> > mat;
	vector< pair<int, int> > posicions; // Les posicions dels gears
	int linies = 0;
	while (getline(file,linia)) {	// Primer creem i omplim la matriu de chars
		int columnes = 0;
		vector<char> liniaToChars;
		stringstream input(linia);
		while (input >> c) {
			if (c == '*') posicions.push_back(pair<int, int>(linies, columnes));	// PROBLEMA 2
			liniaToChars.push_back(c);
			++columnes;																// PROBLEMA 2
		}
		mat.push_back(liniaToChars);
		++linies;																	// PROBLEMA 2
	}
	
	int suma = 0;
		
	for (pair<int, int> pos : posicions) {
		vector<int> numeros;
		for (int i = pos.first - 1; i <= pos.first + 1; ++i) {	// Mirem al voltan del simbol de dalt a baix
			if (i >= 0 && i < mat.size()) {
				bool sameNumber = false;
				for (int j = pos.second - 1; j <= pos.second + 1; ++j) {	// Mirem al voltant del símbol d'esquerra a dreta
					if (j >= 0 && j < mat[i].size()) {

						if (mat[i][j] >= 48 && mat[i][j] <= 57) {
							if (not sameNumber) {							// Si abans no tenia cap digit ens guardem el numero
								sameNumber = true;							// Ens guardem que ja estem mirant el número per no mirarlo multiples cops
								numeros.push_back(getNumber(i, j, mat));	// Guardem el numero
							}
						}
						else sameNumber = false;							// Si no veiem un digit, actualitzem el flag
						
					}
				}
			}
		}
		if (numeros.size() == 2) suma += numeros.at(0) * numeros.at(1);
	}


	// PROBLEMA 1 INEFICIENT
	/*for (int i = 0; i < mat.size(); ++i) {	// Recorrem totes les files de la matriu
		
		bool isNumber = false;				// Aquest booleà ens dirà si els números que estem llegint son el primer o no
		bool isValid = false;
		int numero = 0;

		for (int j = 0; j < mat[i].size(); ++j) {	// Recorrem la fila anant char per char

			char actual = mat[i][j];				// Per fer menys accessos a la matriu

			if (isNumber) {							// Si el char anterior era un número, entrem aquí

				if (actual >= 48 && actual <= 57) {	// Si el char que estem mirant és un dígit, entrem aquí

					numero = numero * 10 + (actual - 48);				// Afegim el dígit al final del número
					if (!isValid) isValid = checkIfValid(i, j, mat);	// Si no hem pogut comprovar que sigui vàlid, ho comprovem
				
				}

				else {								// Si el char actual no és un número, entrem aquí
					if (isValid) suma += numero;	// Si es un numero que toca un símbol, el sumem
					numero = 0;						// Reiniciem el numero
					isNumber = false;				// Desactivem la flag que ens diu si estem mirant un número
					isValid = false;
				}

			}

			else {										// Si el dígit anterior no era un número, entrem aquí
				
				if (actual >= 48 && actual <= 57) {		// Comprovem si és un número
					isNumber = true;					// Activem el flag de que hem trobat un número
					numero = actual - 48;				// Guardem el valor
					isValid = checkIfValid(i, j, mat);	// Fem check de si es vàlid en el nostre problema
				}

			}
		
		}
		if (isValid) suma += numero;					// Si acabem la linia i tenim un número vàlid, el sumem
	}*/
	
	cout << suma;
}