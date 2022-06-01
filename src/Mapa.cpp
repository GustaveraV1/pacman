#include <iostream>
#include <fstream>
#include <string>

#include "Mapa.h"

Mapa::Mapa(const char *arquivo) {
	std::ifstream arquivo_leitura;
	arquivo_leitura.open(arquivo, std::ifstream::in);

	if (not arquivo_leitura.is_open()) {
		std::cerr << "nao foi possivel abrir o arquivo " << arquivo << "\n";
		std::exit(EXIT_FAILURE);
	}

	char c = arquivo_leitura.get();
	int i = 0, j = 0;
	while (arquivo_leitura.good()) {
		this->mapa[i][j] = c;
		c = arquivo_leitura.get();
	}
}

void Mapa::desenhar(void) {

}
