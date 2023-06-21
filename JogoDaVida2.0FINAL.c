#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void printGrid(int** grid, int ROWS, int COLS) { //Funçao Imprime matriz padrao 
    for (int i = 0; i < ROWS; i++) {             //Inicializa matriz em I e J 
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                printf("[\033[34m%c\033[0m]", 254); // Fomarta o print com quadrados azuis 
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }
}

int countNeighbours(int ROWS, int COLS, int row, int col, int** grid) {      //Funcao conta vizinhos 
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;                                           //Verifica a fronteiras da matriz 
            int newCol = col + j;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                count += grid[newRow][newCol];
            }
        }
    }
    count -= grid[row][col];
    return count;
}

void updateGrid(int ROWS, int COLS, int** grid) {                        //Atualiza a matriz com as regras do jogo 
    int** newGrid = (int**)malloc(ROWS * sizeof(int*));                    //Aloca dinamicamene a matriz nova 
    for (int i = 0; i < ROWS; i++) {
        newGrid[i] = (int*)malloc(COLS * sizeof(int));
        for (int j = 0; j < COLS; j++) {
            int neighbours = countNeighbours(ROWS, COLS, i, j, grid);
            if (grid[i][j] == 1 && (neighbours < 2 || neighbours > 3)) {     //Aplica a regra do jogo 
                newGrid[i][j] = 0;
            } else if (grid[i][j] == 0 && neighbours == 3) {
                newGrid[i][j] = 1;
            } else {
                newGrid[i][j] = grid[i][j];
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = newGrid[i][j];
        }
        free(newGrid[i]);                                                           //Libera a nova matriz 
    }
    free(newGrid);
}

int main() {
    char nomearq[100];            //Define as variaveis 
    char linhaArq[100];
    int linhas, colunas, **p, i, j;
    int cont = 0;
    int generations = 0;
    int** grid;


    printf("Qual arquivo voce quer? \n");  //Le o arquivo escolhido  
    scanf("%s", &nomearq);
    printf("Quantas geracoes voce quer? \n");  //Le a quantidade de gerações 
    scanf("%d", &generations);
 
    FILE* f; 

    f=fopen(nomearq, "r");                  //Leitura do arquivo 

    if (f == NULL) {
        printf("Erro\n");      //retorna erra caso a leitura n funcione 
        system("pause");                    
        exit(1);
    } else {
        linhas = atoi(fgets(linhaArq, 100, f)); //Pega o valor de das linhas e transforma em int
        colunas = atoi(fgets(linhaArq, 100, f));
 
        grid = (int**)malloc(linhas * sizeof(int*));      //Aloca a matriz dinamicamente 
        for (i = 0; i < linhas; i++) {
            grid[i] = (int*)calloc(colunas, sizeof(int));
        }

        i = 0;
        while (!feof(f)) {
            fgets(linhaArq, 100, f);
            for (j = 0; j < colunas; j++) {
                if (linhaArq[j] == '1') {
                    grid[i][j] = 1;
                }
            }
            i++;
        }
        fclose(f);
    }

    while (cont != generations) {                //loop para dar dinamicidade do jogo 
        system("cls");
        printGrid(grid, linhas, colunas);
        updateGrid(linhas, colunas, grid);
        cont++;
        printf("Contador de geracoes: %d\n", cont);
        Sleep(100);
    }

    for (i = 0; i < linhas; i++) {          //Libera as linhas 
        free(grid[i]);
    }
    free(grid);

    system("pause");
    return 0;
}
