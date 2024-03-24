#include <stdio.h>

int processoFilho()
{

    pid_t ramal = fork();

    if(ramal < FILHO)
    {
        // Falha na criação do ramal
        perror("Erro na criação do processo filho.");
        return -1;
    }
    else if(ramal == FILHO)
    {
        return processoFilho(); //TODO
    }

    close(tuboFilho[LEITURA]);  // Fecha o canal de leitura (STDIN_FILENO = 0)
                                // Vai-se tirar partido do aspeto de clonagem para receber a leitura do vetor
                                // Depois de ler o sv
    //contagem = vector_get_in_range();



    close(tuboFilho[ESCRITA]);   // Fecha o canal de escrita (STDOUT_FILENO = 1)




}
