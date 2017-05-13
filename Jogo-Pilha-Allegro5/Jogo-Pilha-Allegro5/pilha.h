#pragma once

#define TAMANHO 4

class Pilha
{
private:
	int topo;
	int marcador[TAMANHO];
public:
	Pilha();
	bool Vazia();
	bool Cheia();
	void Empilha(int valor, bool &deuCerto);
	void Desempilha(int &valor, bool &deuCerto);
	bool IgualPilha(Pilha p1, Pilha p2);
	~Pilha();
};

Pilha::Pilha() {
	topo = -1;
}

bool Pilha::Vazia() {
	if (topo == -1)
		return true;
	else return false;
}

bool Pilha::Cheia() {
	if (topo == (TAMANHO - 1))
		return true;
	else return false;
}

void Pilha::Empilha(int valor, bool &deuCerto) {
	if (Cheia())
		deuCerto = false;
	else {
		deuCerto = true;
		topo += 1;
		marcador[topo] = valor;
	}
}

void Pilha::Desempilha(int &valor, bool &deuCerto) {
	if (Vazia())
		deuCerto = false;
	else {
		deuCerto = true;
		valor = marcador[topo];
		topo -= 1;
	}
}

bool Pilha::IgualPilha(Pilha p1, Pilha p2)
{
	bool flag1, flag2, auxStatus;
	int elemento1, elemento2;
	Pilha pilhaAux1, pilhaAux2;

	auxStatus = true;

	while ((p1.Vazia() == false) && (p2.Vazia() == false)) {
		p1.Desempilha(elemento1, flag1);
		p2.Desempilha(elemento2, flag2);
		if (flag1 == true)
			pilhaAux1.Empilha(elemento1, flag1);
		if (flag2 == true)
			pilhaAux2.Empilha(elemento2, flag2);
		if ((flag1 == true) && (flag2 == false))
			auxStatus = false;
		if ((flag1 == false) && (flag2 == true))
			auxStatus = false;
		if ((flag1 == true) && (flag2 == true)) {
			if (elemento1 != elemento2)
				auxStatus = false;
		}
	}
	while (pilhaAux1.Vazia() == false) {
		pilhaAux1.Desempilha(elemento1, flag1);
		p1.Empilha(elemento1, flag1);
	}
	while (pilhaAux2.Vazia() == false) {
		pilhaAux2.Desempilha(elemento2, flag2);
		p2.Empilha(elemento2, flag2);
	}
	if (auxStatus == true)
		return true;
	else
		return false;
}

Pilha::~Pilha() {

}

void imprimePilha(Pilha p1)
{
	int valor;
	Pilha pAux;
	bool flag1;
	while (p1.Vazia() == false) {
		p1.Desempilha(valor, flag1);
		if (flag1 == true) {
			pAux.Empilha(valor, flag1);
		}
	}
	while (pAux.Vazia() == false) {
		pAux.Desempilha(valor, flag1);
		if (flag1 == true) {
			cout << valor << endl;
			p1.Empilha(valor, flag1);
		}
	}
}