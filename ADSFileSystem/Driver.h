#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;

#define SB_TAM_BLOCO_FISICO 512
#define SB_TAM_BLOCO_LOGICO 4096

int LeiaBlocoFisico(int id, byte * buffer);

int EscrevaBlocoFisico(int id, byte * buffer);
