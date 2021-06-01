#include <stdlib.h>


/*
  il labirinto:w(muro),u(cella sconosciuta, raggiungibile),e(explored)
  vengono salvate sia celle sia i muri tra le celle, quindi la dimensione(sizeof(maze))è nCaselle*2-1
*/
char** maze;
int* mot, sonar;
//posizione e direzione del robot nel labirinto(posizione assoluta)
int lato, dirA, xA , yA;
int pot1, pot2, check;
/*
  movimenti da fare per muoveri nella cella in direzione indice
  es: rot[1] sono i movimenti per girarsi a destra e andare avanti di una cella
  usato solo in calcPer
*/
int** rot;
void setup() {
  robot();
  mazeInit(200);
}
/*

  il file maze serve per salvare il labirinto e calcolare i movimenti da fare(parte logica)
  il file robot serve a comandare il robot, comunica con i pin della scheda

  nel loop si esegue questa serie di azioni:
  -lettura dei muri vicini e aggiornamento della tabella
  -controllo se ci sono quadrati di celle collegate e rimosione del bug
  -calcolo del percorso da seguire per la cella inesplorata più vicina
  -esecuzione dei movimenti e aggiornamento della posizione nella tabella

  info generali del progetto:
  coordinate relative del robot:0 davanti, 1 sinistra, 2 dietro, 3 destra
  coordinate assolute labirinto:0 nord/sopra(y=0, maze[0][]),1 est/destra(x=lato, maze[][lato]),
  2 sud/sotto(y=lato, maze[lato][]), 3 ovest/sinistra(x=0, maze[][0])
*/
void loop() {
  setAvanti(sAvanti());
  setDestra(sDestra());
  setDietro(sDietro());
  setSinistra(sSinistra());
  debugSquare();
  int* mov = percorso();
  if (mov != NULL) {
    for (int i = 0; i < sizeof(mov); i++) {
      switch (mov[i]) {
        case 0:
          avanti();
          tabAvanti();
          break;
        case 1:
          destra();
          tabDestra();
          break;
        case 3:
          sinistra();
          tabSinistra();
          break;
      }
    }
  }
}
