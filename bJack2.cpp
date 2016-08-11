//#include <QCoreApplication>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <cstring>
//COPAS   = c
//ESPADAS = e
//OUROS   = o
//PAUS    = p

using namespace std;

string mao = "";

enum NAIPES {COPAS, ESPADAS, OUROS, PAUS};
enum CARTAS {C2, C3, C4, C5, C6, C7, C8, C9, C10, CJ , CQ, CK, CA};

int dinheiroJogador = 100;
int opcApost;

struct Cartas{
    NAIPES naipes;
    CARTAS cartas;
    int valor;
};

string nomearLetras(int carta){
    switch (carta){
        case 0:
            return "2";
        case 1:
            return "3";
        case 2:
            return "4";
        case 3:
            return "5";
        case 4:
            return "6";
        case 5:
            return "7";
        case 6:
            return "8";
        case 7:
            return "9";
        case 8:
            return "10";
        case 9:
            return "J";
        case 10:
            return "Q";
        case 11:
            return "K";
        case 12:
            return "A";
    }
    return "A";
}


void iniciaBaralho(vector <Cartas> &vCartas){
    for (int j=0; j<13; j++) {
        for (int i=0; i<4; i++) {
            int v;
            if (j > 8) {
                v = 10;
            }else{
                v = j+2;
            }
            Cartas carta = {((NAIPES)i),((CARTAS)j),v};
            vCartas.push_back(carta);
        }
    }
}


int pedirCarta(vector <Cartas> &vCartas, int total){
    int cartaRand = rand()%51;
    int valor = vCartas[cartaRand].valor;
    if (vCartas[cartaRand].cartas == CA) {
        if (total >= 12) {
            return 1;
        }
        return 11;
    }

    //mao += nomearLetras(vCartas[cartaRand].cartas) + " ";
    cout << mao;
    vCartas.erase(vCartas.begin()+cartaRand);
    return valor;
}

void imprimePlacar(int totalJog, int totalMes){
	cout << "Mesa:...................." << totalMes << endl;
    cout << "Voce:...................." << totalJog << endl;    
    cout << "R$  :...................." << dinheiroJogador << endl;
}

void menu(){
    cout << "MENU" << endl;
    cout << "1 - Pedir Carta" << endl;
    cout << "2 - Parar" << endl;
}

void aposta(){
    
    cout << "DINHEIRO: " << dinheiroJogador << endl;
    cout << "Digite o valor da aposta" << endl;
    cout << "-1 - Sair" << endl;
    cin >> opcApost;
	if (opcApost == -1){ exit(1);}
    dinheiroJogador-=opcApost;
}

int main()
{
    srand(time(NULL));
    vector <Cartas> cartasConjuto;

    int totalJogador = 0;
    int totalMesa = 0;

    int opcMenu;

    iniciaBaralho(cartasConjuto);    
    aposta();

    /****** INICIA JGGADA ******/

    totalJogador += pedirCarta(cartasConjuto,totalJogador);
    totalJogador += pedirCarta(cartasConjuto,totalJogador);
    totalMesa += pedirCarta(cartasConjuto,totalMesa);

    do{
    imprimePlacar(totalJogador, totalMesa);


    menu();
    
    cin >> opcMenu;

    switch (opcMenu) {
    case 1:
        totalJogador += pedirCarta(cartasConjuto,totalJogador);    
        if (totalJogador > 21)
        {
        	imprimePlacar(totalJogador, totalMesa);
        	cout << "VOCE PERDEU" << endl; exit(1);      
        }
        break;
    case 2:
        while(totalMesa <= 21){
        	totalMesa += pedirCarta(cartasConjuto,totalMesa);        	
        }
        if (totalMesa > totalJogador && totalMesa <= 21)
        	{cout << "VOCE PERDEU" << endl; exit(1);}
        else
        	{
        	dinheiroJogador += (opcApost*2); 
        	imprimePlacar(totalJogador, totalMesa);
        	cout << "VOCE GANHOU" << endl; exit(1);}
    	break;
    default:
        break;
    }

    }while(opcMenu == 1 || opcMenu == 2);

    return 0;
}

