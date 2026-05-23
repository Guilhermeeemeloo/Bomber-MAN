/*
Trabalho Bomberman - M1 - Algorítmos e Programação II

Bernardo Prantz Pin
Samuel Pereira Eduardo Santana
Toni Eliezer Dos Santos
Guilherme Melo
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <locale.h>
#include <fstream>
#include <string>

// multiplataforma
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

using namespace std;

const unsigned maxInimigos = 10;

struct Jogador {
    int x;
    int y;
    bool vivo;
    int qtdMovimentos;
    int bombasUsadas;
    double pontuacao;
    int inimigosAbatidos;
};

struct pRanking {
    string nomeJogador;
    int pontosJogador;
    int tempoPartida;
};

struct Inimigo {
    int x;
    int y;
    bool vivo;
    int direcao;
    int passos;

};

struct Bomba {
    int x;
    int y;
    bool ativa;
    chrono::steady_clock::time_point tempoPlantada;
    bool explosaoAtiva;
    chrono::steady_clock::time_point tempoExplosao;
};

struct EstadoJogo {
    int mapa[19][25];
    bool rodando;
    bool vencedor;
    unsigned inimigosAtivos;
    chrono::steady_clock::time_point tempoInicio;
};

void enableANSI() {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
}

#ifndef _WIN32
int _kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif

double calculaPontuacao(Jogador& p1){
    double multiplicador = 2.0;
    if(p1.bombasUsadas > 3){
        multiplicador = 1.75;
    }else if(p1.bombasUsadas > 2){
        multiplicador = 1.5;
    }else if(p1.bombasUsadas > 1){
        multiplicador = 1.25;
    }

    return p1.pontuacao + (100 * multiplicador);


}

// procedimento para desenhar o mapa do jogo
void imprimeMapa(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade) {

	for(int i=0; i<19; i++) {
		for(int j=0; j<25; j++) {

			if(bomba.explosaoAtiva == true && jogo.mapa[i][j] != 1 && (i == bomba.x && j == bomba.y || i == bomba.x - 1 && j == bomba.y || i == bomba.x + 1 && j == bomba.y ||  i == bomba.x && j == bomba.y - 1 || i == bomba.x && j == bomba.y + 1)) {
				cout << "\033[103m💥\033[0m";

			}else if(i==p1.x && j==p1.y) {
				if(p1.vivo == true){
                    cout<< "\033[42m🧔\033[0m";
				}else{
                    cout<< "\033[42m🪦\033[0m";
				}

			}else if(bomba.ativa == true && i==bomba.x && j==bomba.y) {
				cout << "\033[42m💣\033[0m";

			}else{
				bool inimigoAqui = false;
				for(int k = 0; k < jogo.inimigosAtivos; k++) {
					if(inimigoAqui == false && inimigos[k].vivo == true && i == inimigos[k].x && j == inimigos[k].y) {
						inimigoAqui = true;
					}
				}

				if(inimigoAqui == true) {
					cout << "\033[42m👹";
				}else{
					switch (jogo.mapa[i][j]) {
					case 0:
						cout<< "\033[42m  \033[0m";
						break;
					case 1:
						cout<< "\033[47m  \033[0m";
						break;
					case 2:
						cout<< "\033[42m🧱\033[0m";
						break;
					}
				}
			}
		}
		cout<<"\n";
	}
	cout << "\033[33mDIFICULDADE: ";
	if(selDificuldade == 3){
        cout << "Dificil";
	}else if(selDificuldade == 2){
        cout << "Intermediario";
	}else{
        cout << "Facil";
	}


	auto tempoAtual = chrono::steady_clock::now();
	int tempoDecorrido = chrono::duration_cast<chrono::seconds>(tempoAtual - jogo.tempoInicio).count();

	int minutos = tempoDecorrido / 60;
	int segundos = tempoDecorrido % 60;

	cout << "\t\033[33m" << "TEMPO DE JOGO: ";

	if (minutos > 0) {
	    cout << minutos << "m ";
	    if (segundos < 10) cout << "0";
	}
	if (minutos <= 0) {
	    cout << "00m ";
	    if (segundos < 10) cout << "0";
	}
	cout << segundos << "s ";

	cout << "\n\033[36mMOVIMENTOS: " << p1.qtdMovimentos << " | INIMIGOS ABATIDOS: " << p1.inimigosAbatidos << "\nBOMBAS USADAS: " << p1.bombasUsadas << " | PONTOS: " << p1.pontuacao << "\033[0m";
	cout << "\033[J";
}

// procedimento para executar as acoes do jogador no mapa
void executaMovimentos(EstadoJogo& jogo, Jogador& p1, Bomba& bomba) {
	char tecla;

	if(p1.vivo == true){
        if ( _kbhit() ) {
            tecla = getch();
            switch(tecla)
            {
            case 72:
            case 'w':
                if(jogo.mapa[p1.x-1][p1.y] == 0) {
                    p1.x--;
                    p1.qtdMovimentos++;
                }
                break;
            case 80:
            case 's':
                if(jogo.mapa[p1.x+1][p1.y] == 0) {
                    p1.x++;
                    p1.qtdMovimentos++;
                }
                break;
            case 75:
            case 'a':
                if(jogo.mapa[p1.x][p1.y-1] == 0) {
                    p1.y--;
                    p1.qtdMovimentos++;
                }
                break;
            case 77:
            case 'd':
                if(jogo.mapa[p1.x][p1.y+1] == 0) {
                    p1.y++;
                    p1.qtdMovimentos++;
                }
                break;
            case 88:
            case 'x':
                if(bomba.ativa == false && bomba.explosaoAtiva == false) {
                    bomba.ativa = true;
                    bomba.x = p1.x;
                    bomba.y = p1.y;
                    p1.bombasUsadas++;
                    bomba.tempoPlantada = chrono::steady_clock::now();
                }
                break;

            }
        }
	}
}

// procedimento para movimentar os inimigos no mapa
void movimentaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Bomba& bomba) {
	for(int k = 0; k < jogo.inimigosAtivos; k++) {
		if(inimigos[k].vivo == true) {
            if(inimigos[k].passos == 0){
                inimigos[k].direcao = rand() %4;
                inimigos[k].passos = rand() %3 +1;

                continue;
            }
			switch(inimigos[k].direcao) {
			case 0:
				if(jogo.mapa[inimigos[k].x - 1][inimigos[k].y] == 0 && (bomba.ativa == false || (inimigos[k].x - 1 != bomba.x || inimigos[k].y != bomba.y))) {
					inimigos[k].x--;
					inimigos[k].passos--;
				} else {
				    inimigos[k].passos = 0;
					break;
				}
				break;
			case 1:
				if(jogo.mapa[inimigos[k].x + 1][inimigos[k].y] == 0 && (bomba.ativa == false || (inimigos[k].x + 1 != bomba.x || inimigos[k].y != bomba.y))) {
					inimigos[k].x++;
					inimigos[k].passos--;
				} else {
				    inimigos[k].passos = 0;
					break;
				}
				break;
			case 2:
				if(jogo.mapa[inimigos[k].x][inimigos[k].y -1] == 0 && (bomba.ativa == false || (inimigos[k].x != bomba.x || inimigos[k].y-1 != bomba.y))) {
					inimigos[k].y--;
					inimigos[k].passos--;
				} else {
				    inimigos[k].passos = 0 ;
					break;
				}
				break;
			case 3:
				if(jogo.mapa[inimigos[k].x][inimigos[k].y +1] == 0 && (bomba.ativa == false || (inimigos[k].x != bomba.x || inimigos[k].y+1 != bomba.y))) {
					inimigos[k].y++;
					inimigos[k].passos--;
				} else {
				    inimigos[k].passos = 0;
					break;
				}
				break;
			}
		}
	}
}
//procedimento para inicializar os inimigos no jogo
void inicializaInimigos(EstadoJogo& jogo, Inimigo inimigos[], Jogador p1){
    int sorteioLinha, sorteioColuna;

    for(int i = 0; i < jogo.inimigosAtivos; i++){
        bool areaLivre = false;
        inimigos[i].vivo = true;
        inimigos[i].direcao = 0;
        inimigos[i].passos = 0;
        do{
            sorteioLinha = rand() % 19;
            sorteioColuna = rand() %  25;

            if (jogo.mapa[sorteioLinha][sorteioColuna] == 0) {
                areaLivre = true;
                if((sorteioLinha == p1.x && sorteioColuna == p1.y) || (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +1) || (sorteioLinha == p1.x +2 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +2)){
				areaLivre = false;
                }
            }


            if(areaLivre == true) {
                inimigos[i].x = sorteioLinha;
                inimigos[i].y = sorteioColuna;
                }
        }while(areaLivre == false);
    }
}

// procedimento para escolher aleatoriamente a posicao das paredes frageis
void sorteiaFrageis(EstadoJogo& jogo, Jogador& p1){
    int cont = 0, sorteioLinha, sorteioColuna;
    bool areaLivre = false;

    while(cont < 50) {
		sorteioLinha = rand() % 19;
		sorteioColuna = rand() %  25;

		if (jogo.mapa[sorteioLinha][sorteioColuna] == 0) {
			areaLivre = true;

			if((sorteioLinha == p1.x && sorteioColuna == p1.y) || (sorteioLinha == p1.x +1 && sorteioColuna == p1.y) || (sorteioLinha == p1.x && sorteioColuna == p1.y +1))
				areaLivre = false;



                if(areaLivre == true) {
                    jogo.mapa[sorteioLinha][sorteioColuna] = 2;
                    cont++;
			}
		}
	}
}

// procedimento que conta o timer da bomba e ao desativa-la aplica seus efeitos
void detonaBomba(EstadoJogo& jogo, Bomba& bomba, Jogador& p1, Inimigo inimigos[]){

    if(bomba.ativa == true) {
			auto tempoAtual = chrono::steady_clock::now();
            auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoPlantada).count();

			if(duracao >= 3000) {
				bomba.ativa = false;

				if(jogo.mapa[bomba.x-1][bomba.y] == 2) jogo.mapa[bomba.x-1][bomba.y] = 0;
				if(jogo.mapa[bomba.x+1][bomba.y] == 2) jogo.mapa[bomba.x+1][bomba.y] = 0;
				if(jogo.mapa[bomba.x][bomba.y-1] == 2) jogo.mapa[bomba.x][bomba.y-1] = 0;
				if(jogo.mapa[bomba.x][bomba.y+1] == 2) jogo.mapa[bomba.x][bomba.y+1] = 0;

				for(int k = 0; k < jogo.inimigosAtivos; k++) {
					if(inimigos[k].vivo == true) {
						if(inimigos[k].x == bomba.x && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x - 1 && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x + 1 && inimigos[k].y == bomba.y || inimigos[k].x == bomba.x && inimigos[k].y == bomba.y - 1 || inimigos[k].x == bomba.x && inimigos[k].y == bomba.y + 1) {
							inimigos[k].vivo = false;
							p1.inimigosAbatidos++;
							p1.pontuacao = calculaPontuacao(p1);
						}
					}
				}

				bomba.explosaoAtiva = true;
				bomba.tempoExplosao = chrono::steady_clock::now();

				if(bomba.x == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x -1 == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x +1 == p1.x && bomba.y == p1.y) p1.vivo = false;
				if(bomba.x == p1.x && bomba.y -1 == p1.y) p1.vivo = false;
				if(bomba.x == p1.x && bomba.y +1 == p1.y) p1.vivo = false;
			}
		}

		if(bomba.explosaoAtiva == true) {
			auto tempoAtual = chrono::steady_clock::now();
            auto duracao = chrono::duration_cast<chrono::milliseconds>(tempoAtual - bomba.tempoExplosao).count();
			if(duracao >= 500) {
				bomba.explosaoAtiva = false;
			}
		}
}

// procedimento para verificar se as condicoes de vitoria ou derrota foram atingidas
void verificaFim(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[], unsigned selDificuldade){

    int inimigosMortos = 0;

        for(int k = 0; k < jogo.inimigosAtivos; k++){
            if((inimigos[k].vivo == true) && inimigos[k].x == p1.x && inimigos[k].y == p1.y){
                p1.vivo = false;
            }
            if(inimigos[k].vivo == false){
                inimigosMortos++;
            }
        }

        if(inimigosMortos == jogo.inimigosAtivos && bomba.explosaoAtiva == false){
            #ifdef _WIN32
                COORD coord;
                coord.X = 0;
                coord.Y = 0;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            #else
                cout << "\033[H";
            #endif
                jogo.vencedor = true;
                imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);
                auto inicioPausa = chrono::steady_clock::now();
                while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {

                }
                jogo.rodando = false;
        }

        if(p1.vivo == false && bomba.explosaoAtiva == false){
            #ifdef _WIN32
                COORD coord;
                coord.X = 0;
                coord.Y = 0;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            #else
                cout << "\033[H";
            #endif
                imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);
                auto inicioPausa = chrono::steady_clock::now();
                while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - inicioPausa).count() < 1000) {
                }
                jogo.rodando = false;
        }
}

void imprimeTelaInicial(){
    int matTelaInicial[19][25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                            };
    for(int i = 0; i < 19; i++){
            for(int j = 0; j < 25; j++){
                switch(matTelaInicial[i][j]){
                case 0: cout<< "  "; break;
                case 1: cout<< "\033[47m  \033[0m"; break;
                case 2: cout<< "\033[91m  \033[0m"; break;
                case 3: cout<< "  "; break;
                case 4: cout<< "  "; break;
                case 5: cout<< "  "; break;
                }
            }
            cout << "\n";
        }

}
// procedimento que desenha a tela final
void imprimeTelaFinal(bool vencedor){
    int matGameOver[19][25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,4,2,2,0,0,4,2,5,0,0,2,2,2,2,0,0,2,2,2,0,0,0,1,
                                1,0,2,0,0,0,0,2,0,2,0,0,2,4,0,2,0,0,2,3,0,0,0,0,1,
                                1,0,2,0,3,0,0,2,2,2,0,0,2,0,0,2,0,0,2,0,0,0,0,0,1,
                                1,0,4,2,2,0,0,2,0,2,0,0,2,0,0,2,0,0,2,2,2,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,2,2,2,0,0,2,0,0,2,0,0,2,2,2,0,0,2,2,0,0,0,0,1,
                                1,0,2,0,2,0,0,2,0,0,2,0,0,2,3,0,0,0,2,3,0,0,0,0,1,
                                1,0,2,0,2,0,0,4,3,3,5,0,0,2,0,0,0,0,2,4,5,0,0,0,1,
                                1,0,2,2,2,0,0,0,4,5,0,0,0,2,2,2,0,0,2,0,2,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                                };

    int matWin[19][25] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,0,2,0,0,2,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,2,2,0,2,0,0,0,1,
                        1,0,0,2,0,0,0,2,0,0,0,0,2,0,0,0,0,2,4,5,2,0,0,0,1,
                        1,0,0,2,3,2,3,2,0,0,0,0,2,0,0,0,0,2,0,2,2,0,0,0,1,
                        1,0,0,4,5,0,4,5,0,0,0,0,2,0,0,0,0,2,0,0,2,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
                        };

    if(vencedor == false){
        for(int i = 0; i < 19; i++){
            for(int j = 0; j < 25; j++){
                switch(matGameOver[i][j]){
                case 0: cout<< "\033[40m  \033[0m"; break;
                case 1: cout<< "\033[47m  \033[0m"; break;
                case 2: cout<< "\033[101m  \033[0m"; break;
                case 3: cout<< "\033[101m  \033[0m"; break;
                case 4: cout<< "\033[101m  \033[0m"; break;
                case 5: cout<< "\033[101m  \033[0m"; break;
                }
            }
            cout << "\n";
        }
    }else{
        for(int i = 0; i < 19; i++){
            for(int j = 0; j < 25; j++){
                switch(matWin[i][j]){
                case 0: cout<< "\033[40m  \033[0m"; break;
                case 1: cout<< "\033[47m  \033[0m"; break;
                case 2: cout<< "\033[44m  \033[0m"; break;
                case 3: cout<< "\033[44m  \033[0m"; break;
                case 4: cout<< "\033[44m  \033[0m"; break;
                case 5: cout<< "\033[44m  \033[0m"; break;
                }
            }
            cout << "\n";
        }
    }



}

void salvaRanking(Jogador p1, EstadoJogo jogo){

    auto tempoFinal = chrono::steady_clock::now();
    int tempoTotal = chrono::duration_cast<chrono::seconds>(tempoFinal - jogo.tempoInicio).count();
    string nomeJogador;
    cout << "\n\n\nDIGITE SEU PRIMEIRO NOME: ";
    cout << "\033[J";
    cin >> nomeJogador;

    ofstream arqRank;
    arqRank.open("ranking.txt", ios::app);
    if(arqRank.is_open()){
        arqRank << "\n" << nomeJogador << "\t" << tempoTotal << "\t" << p1.pontuacao << "\n";
        arqRank.close();
    }else{
        cout << "Erro ao salvar!!!" << endl;
    }

}

void resetaJogo(EstadoJogo& jogo, Jogador& p1, Bomba& bomba, Inimigo inimigos[]){
    cout << "\033[J";
    const int mapaBase[19][25] = {

        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };

    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 25; j++) {
            jogo.mapa[i][j] = mapaBase[i][j];
        }
    }

    jogo.rodando = true;
    jogo.vencedor = false;
    p1.vivo = true;
    p1.qtdMovimentos = 0;
    p1.bombasUsadas = 0;
    p1.pontuacao = 0;
    p1.inimigosAbatidos = 0;
    p1.x = 1;
    p1.y = 1;
    bomba.ativa = false;
    bomba.explosaoAtiva = false;
    bomba.tempoExplosao = chrono::steady_clock::now();
    bomba.tempoPlantada = chrono::steady_clock::now();
    bomba.x = 0;
    bomba.y = 0;



    sorteiaFrageis(jogo, p1);

    inicializaInimigos(jogo, inimigos, p1);

    jogo.tempoInicio = chrono::steady_clock::now();


}
int main() {
    system ("chcp 65001");
    #ifdef _WIN32
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);

        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
    #endif


	srand(time(NULL));
	enableANSI();

	EstadoJogo jogo;
    Jogador p1;
    Bomba bomba;
    Inimigo inimigos[maxInimigos];
    jogo.inimigosAtivos = 3;

    auto tempoInimigos = chrono::steady_clock::now();

    pRanking lista[100];
    pRanking temp;
    int totalJogadores;
    unsigned opcao;
    unsigned selDificuldade;
    char lido;
    ifstream arqRank;
    do{
        #ifdef _WIN32
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
                cout << "\033[H";
        #endif

            imprimeTelaInicial();
            cout << "\033[J";
            cout << "\n1- Jogar \n2- Selecionar dificuldade \n3- Info \n4- Ranking \n5- Fechar o Jogo" << endl;
            cin >> opcao;
            if(cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                opcao = 0;
            }

            switch(opcao){
                case 1:
                    resetaJogo(jogo, p1, bomba, inimigos);

                    while(jogo.rodando == true) {
                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif

                                imprimeMapa(jogo, p1, bomba, inimigos, selDificuldade);

                                executaMovimentos(jogo, p1, bomba);

                                auto tempoAtual_inimigos = chrono::steady_clock::now();
                                auto duracaoInimigos = chrono::duration_cast < chrono::milliseconds>(tempoAtual_inimigos - tempoInimigos).count();

                                if(duracaoInimigos >= 500) {
                                    movimentaInimigos(jogo, inimigos, bomba);
                                    tempoInimigos = chrono::steady_clock::now();
                                }

                                detonaBomba(jogo, bomba, p1, inimigos);

                                verificaFim(jogo, p1, bomba, inimigos, selDificuldade);

                    }
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif


                        imprimeTelaFinal(jogo.vencedor);
                        salvaRanking(p1, jogo);
                        cout << "PRESSIONE QUALQUER TECLA PARA VOLTAR A TELA INICIAL";


                        #ifdef _WIN32
                                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                                cout << "\033[H";
                        #endif
                        while(_kbhit()) {
                            getch();
                        }
                        cin.clear();
                        getch();
                        #ifdef _WIN32
                            system ("cls");
                        #else
                            system ("clear");
                        #endif
                        cout << "\033[2J\033[H";
                    break;

                case 2:

                    do{

                        #ifdef _WIN32
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                        #else
                            cout << "\033[H";
                        #endif

                        imprimeTelaInicial();
                        cout << "\033[J";


                        cout << "\nEscolha a dificuldade: \n1- Facil \n2- Intermediario \n3- Dificil\n";
                        cin >> selDificuldade;

                        if(cin.fail()) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            selDificuldade = 0;
                        }
                        if(selDificuldade == 1){
                            jogo.inimigosAtivos = 3;
                        }
                        if(selDificuldade == 2){
                            jogo.inimigosAtivos = 5;
                        }
                        if(selDificuldade == 3){
                            jogo.inimigosAtivos = 7;
                        }

                    }while(selDificuldade < 1 || selDificuldade > 3);
                    break;
                case 4:
                    #ifdef _WIN32
                        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    #else
                        cout << "\033[H";
                    #endif
                        imprimeTelaInicial();
                        cout << "\033[J";
                        cout << "\n\033[36m===\t RANKING\t  ===\033[0m\n\n";

                        arqRank.open("ranking.txt");
                        if(arqRank.is_open()){
                            totalJogadores = 0;

                            while(arqRank >> lista[totalJogadores].nomeJogador >> lista[totalJogadores].tempoPartida >> lista[totalJogadores].pontosJogador){
                                totalJogadores++;

                            }
                            arqRank.close();

                        }else{
                            cout << "Erro ao acessar o ranking!";
                        }
                        for(int i = 0; i < totalJogadores - 1; i++){
                            for(int j = 0; j < totalJogadores - i - 1; j++){
                                if(lista[j].pontosJogador < lista[j+1].pontosJogador){
                                    temp = lista[j];
                                    lista[j] = lista[j+1];
                                    lista[j+1] = temp;
                                }
                            }
                        }
                        for(int i = 0; i < totalJogadores; i++){
                            cout << lista[i].nomeJogador << "\t" << lista[i].tempoPartida << "\t" << lista[i].pontosJogador << endl;
                        }
                        cout << "\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU...";
                        while(_kbhit()) { getch(); }
                            cin.clear();
                            getch();
                        break;



            }
    }while(opcao != 5);

    cout << "\n\nOBRIGADO POR JOGAR!" << endl;

	return 0;
}
