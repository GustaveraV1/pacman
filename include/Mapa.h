#ifndef MAPA_H
#define MAPA_H

#define TAMANHO 20

class Mapa {
	public:
		Mapa(const char *);
		void desenhar(void);
	private:
		int mapa[TAMANHO][TAMANHO];
		int pastilhas;
};

#endif
