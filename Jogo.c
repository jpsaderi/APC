#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define VERMELHO "\033[31m"
#define VERDE "\033[32m"
#define AMARELO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define NEGRITO "\033[1m"
#define RESETCOLOR "\033[0m"

#define TRUE 1
#define FALSE 0

#ifndef _WIN32
#include <termios.h>
#include <fcntl.h>

int kbhit(){
	struct termios oldt, newt;
	int ch, oldf;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF){
		ungetc(ch,stdin);
		return 1;
	}
	return 0;
}

int getch(void) {
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#else
	#include <conio.h>
#endif





int Altura = 13 , Largura = 8;
char Mat[50][50];
int pos1, pos2, pos_x1, pos_x2, pos_y1, pos_y2;
int Pontuacao = 0;
int Perdeu = FALSE, Bloco_vertical = FALSE;

void Clear(){
	printf("\033c");
}

void Inicializar_matriz(){
	int i, j;
	for(i = 0; i < Altura; i++){
		for(j = 0; j < Largura; j++){
			if(j == 0 || j == Largura-1 || i == Altura-1){
				Mat[i][j] = '#';
			}
			else{
				Mat[i][j] = ' ';
			}
		}
	}
}


int Aleatorio_Letra(){
	int num;
	num = rand()%5;
	return num;
}
int Aleatorio_Posicao(){
	int num;
	num = (rand()%(Largura-3))+1;
	return num;
}

char EscolheLetra(){
	int cor = Aleatorio_Letra();
	switch(cor){
		case 0 : return 'A';
				 break;
		case 1 : return 'B';
				 break;
		case 2 : return 'C';
				 break;
		case 3 : return 'D';
				 break;
		case 4 : return 'E';
				 break;
		default : break;	
	}
}

void CriarLetras(){
	char letra1, letra2;
	letra1 = EscolheLetra();
	letra2 = EscolheLetra();

	pos1 = Aleatorio_Posicao();
	pos2 = pos1 +1;

	if(Mat[0][pos1] == ' ' && Mat[0][pos2] == ' '){
		Mat[0][pos1] = letra1;
		Mat[0][pos2] = letra2;
		pos_x1 = pos1;
		pos_x2 = pos2;
		pos_y1 = 0;
		pos_y2 = 0;	
	}
	else{
		Perdeu = TRUE;
	}
}

void TrocarLetras(){
	char aux;
	aux = Mat[pos_y1][pos_x1];
	Mat[pos_y1][pos_x1] = Mat[pos_y2][pos_x2];
	Mat[pos_y2][pos_x2] = aux;
}

void DescerLetras(){
	int i,j;
	int chegou_fim1 = FALSE, chegou_fim2 = FALSE;
	for(i = Altura-1;i >= 0;i--){
		for(j = 0;j < Largura-1;j++){
			if(Mat[i][j] >= 'A' && Mat[i][j] <= 'E'){
				if(Mat[i+1][j] == ' '){
					if(i == pos_y1){
						Mat[i+1][j] = Mat[i][j];
						Mat[i][j] = ' ';
						pos_y1++;
					}
					else{
						Mat[i+1][j] = Mat[i][j];
						Mat[i][j] = ' ';
						pos_y2++;
					}
				}
			}
			if(pos_y1 == i && Mat[pos_y1+1][pos_x1] != ' '){
				chegou_fim1 = TRUE;
			}
			if(pos_y2 == i && Mat[pos_y2+1][pos_x2] != ' '){
				chegou_fim2 = TRUE;
			}
		}
	}
	if(chegou_fim1 == TRUE && chegou_fim2 == TRUE){
		CriarLetras();
	}

}





// void MoverDireita(){
// 	if(Bloco_vertical == FALSE){
// 		if(Mat[pos_x1]po)
// 	}



// }




// Verificar_lados(char Vet[][], int pos_x1, int pos_y1, char letra){
// 	if(Vet[pos_x1][pos_y1] == letra){

// 		return Verificar_lados(Vet[][], pos_x1+1, pos_y1, letra);
// 	}


// }


void Imprimir_matriz(){
	int i, j;

	printf("%d\n", Pontuacao);
	for(i = 0; i < Altura; i++){
		for (j = 0; j < Largura; j++){
			if(Mat[i][j] == 'A'){
				printf(VERMELHO"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'B'){
				printf(VERDE"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'C'){
				printf(AMARELO"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'D'){
				printf(AZUL"%c "RESETCOLOR, Mat[i][j]);
			}
			else if(Mat[i][j] == 'E'){
				printf(MAGENTA"%c "RESETCOLOR, Mat[i][j]);
			}
			else{
				printf("%c ", Mat[i][j]);
			}
		}
		printf("\n");
	}
}



int main(){
	int letra1, letra2;
	srand(time(NULL));
	Inicializar_matriz();
	Imprimir_matriz();
	CriarLetras();
	while(Perdeu == FALSE){
		Clear();
		Imprimir_matriz();
		DescerLetras();
		usleep(250000);
	}


	return 0;
}