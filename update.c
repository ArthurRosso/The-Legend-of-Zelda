#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

// Atualiza uma instancia de mundo, se passando deltaTime segundos
void update (SALA *sala, float deltaTime)
{
    int i;

    for (i=0; i < NRO_INIS_MAX; i++)
    {
        updateInimigo(sala, &sala->inis[i], deltaTime);

        move_jogador(sala);
    }

}
