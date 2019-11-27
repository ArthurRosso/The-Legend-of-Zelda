#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>    // poll(), struct pollfd e POLLIN
#include <time.h>

#include "Structs/mundo.h"
#include "Structs/sala.h"
#include "Structs/jogador.h"
#include "Structs/inimigo.h"

// Atualiza uma instancia de mundo, se passando deltaTime segundos
void update (MUNDO *world, float deltaTime)
{
    int i;

    for (i=0; i < NRO_INIS; i++)
    {
        updateInimigo(world, &world->sala.inis[i], deltaTime);

        move_jogador(world);
    }

}
