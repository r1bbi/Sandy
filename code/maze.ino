#include <stdlib.h>

//la tabella e il robot vengono inizializzate
void mazeInit(int l) {
  lato =l;
  dirA=0;
  maze = new char*[lato];
  for (int i = 0; i < sizeC(maze); i++)
    maze[i] = new char[lato];
  xA = (int)(lato / 2);
  yA = (int)(lato / 2);
  //assegnazione di rot
  rot=new int*[4];
  rot[0]=new int[1]{0};
  rot[1]=new int[2]{1,0};
  rot[2]=new int[3]{1,1,0};
  rot[3]=new int[2]{3,0};
}
//settaggio muri davanti, se non c'è un muro la cella dopo diventa 'u'
void setAvanti(bool wall) {
  //la maggior parte dei calcoli serve a calcolare la posizione delle celle e della direzione assoluta del muro guradato
  maze[yCalc(dirA, 1, xA)][xCalc(dirA, 1, yA)] = wall ? 'w' : 'f';
  if (!wall && cell(xA, yA, dirA, 2) != 'e')
    maze[yCalc(dirA, 2, yA)][xCalc(dirA, 2, xA)] = 'u';
}
void setDestra(bool wall) {
  maze[yCalc((dirA + 1) % 4, 1, yA)][xCalc((dirA + 1) % 4, 1, xA)] = wall ? 'w' : 'f';
  if (!wall && cell(xA, yA, (dirA + 1) % 4, 2) != 'e')
    maze[yCalc((dirA + 1) % (dirA + 1) % 4, 2, yA)][xCalc(0, 2, xA)] = 'u';
}
void setDietro(bool wall) {
  maze[yCalc((dirA + 2) % 4, 1, yA)][xCalc((dirA + 2) % 4, 1, xA)] = wall ? 'w' : 'f';
  if (!wall && cell(xA, yA, (dirA + 2) % 4, 2) != 'e')
    maze[yCalc((dirA + 2) % 4, 2, yA)][xCalc((dirA + 2) % 4, 2, xA)] = 'u';
}
void setSinistra(bool wall) {
  maze[yCalc((dirA + 3) % 4, 1, yA)][xCalc((dirA + 3) % 4, 1, xA)] = wall ? 'w' : 'f';
  if (!wall && cell(xA, yA, (dirA + 3) % 4, 2) != 'e')
    maze[yCalc((dirA + 3) % 4, 2, yA)][xCalc((dirA + 3) % 4, 2, xA)] = 'u';
}
//calcolo del numero di cella spostandosi di 'mov' in direzione 'dir', da 'x'
int xCalc(int dir, int mov, int x) {
  switch (dir) {
    case 1:
      return x + mov;
      break;
    case 3:
      return x - mov;
      break;
    default:
      return x;
  }
}
//uguale a xCalc, solo per le y
int yCalc(int dir, int mov, int y) {
  switch (dir) {
    case 0:
      return y + mov;
      break;
    case 2:
      return y - mov;
      break;
    default:
      return y;
  }
}
//ritorna il contenuto di una cella spostandosi da x e y di mov in direzione dir
char cell(int x, int y, int dir, int mov) {
  return maze[yCalc(dir, mov, y)][xCalc(dir, mov, x)];
}
//controlla se ci sono celle 'u' vicine e ritorna il percorso per una di quelle,
//se non ci sono procede al calcolo del percorso per la più vicina
int* percorso() {
  int* out = new int[0];
  if (cell(xA, yA, 0, 2) == 'u')
    return rot[0];
  else if (cell(xA, yA, 1, 2) == 'u')
    return rot[1];
  else if (cell(xA, yA, 2, 2) == 'u')
    return rot[2];
  else if (cell(xA, yA, 3, 2) == 'u')
    return rot[3];
  else
    return calcPer(xA, yA, dirA, out, true);
  return out;
}
/*
  metodo ricorsivo per il calcolo del percorso più veloce per una cella 'u'

  analizza per ogni cella i percorsi disponibili, calcola il percorso simulando il movimento
  quando richiama se stesso

  x e y sono lo coordinate della cella di partenza, di è la direzione dello spostamento, path è il percorso per
  la cella di destinazione, first indica se è il primo calcolo della serie(non esclude il calcolo dei percorsi
  dalla cella di provenienza)
*/
int* calcPer(int x, int y, int dir, int* path, bool first) {
  //controlla se la cella in cui sta andando è 'u', se sì ritorna il percorso dalla cella precendente a quella
  if (cell(x, y, dir, 2) == 'u')
    return path;
  else {
    int* min = NULL;
    int* per;
    //per ogni direzione(0-->3)viene calcolato il percorso, se non c'è un muro in mezzo
    for (int i = 0; i < 4; i++) {
      //tranne la prima volta viene esclusa la cella di provenienza
      if (first || i != (dir + 2) % 4) {
        if (cell(x, y, i, 1) != 'w') {
          //calcolo prosecuzione percorso
          per = calcPer(xCalc(i, 2, x), yCalc(i, 2, y), i, rot[i], false);
          //calcolo percorso migliore
          if (per != NULL) {
            //se il minimo non è ancora stato assegnato o se il percorso è più veloce min viene sostituito
            if (min == NULL || sizeI(per) < sizeI(min))
              min = per;
          }
        }
      }
    }
    //somma in out del percorso per arrivare alla cella e il percorso dalla cella, se min è nullptr ritorna nullptr
    if (min == NULL)
      return NULL;
    else {
      int* out = new int[sizeI(path) + sizeI(min)];
      for (int i = 0; i < sizeI(path); i++)
        out[i] = path[i];
      for (int i = 0; i < sizeI(min); i++)
        out[i + sizeI(path)] = min[i];
      return out;
    }
  }
}
//metodi per lo spostamento del robot nella tabella(coordinate e direzione)
//va avanti di una cella
void tabAvanti() {
  xA = xCalc(dirA, 2, xA);
  yA = yCalc(dirA, 2, yA);
  maze[yA][xA] = 'e';
}
//gira a sinistra di 90°
void tabSinistra() {
  dirA = (dirA + 1) % 4;
}
//gira a destra di 90°
void tabDestra() {
  dirA = (dirA + 3) % 4;
}
/*
  se c'è un quadrato di celle 'e' quando calcola il percorso entra in un loop infinito
  questo metodo aggiunge controlla se si verifica questa situazione e aggiunge nelle tabella
  un muro per far sì che non si bugghi
*/
void debugSquare() {
  //controlla se ci sono quadrati senza muri vicini, se ci sono ci mette dei muri in mezzo
  if (maze[yA - 2][xA - 1] == 'w' && maze[yA - 1][xA - 2] == 'e' && maze[yA - 1][xA] == 'e' && maze[yA][xA - 1] == 'e')
    maze[yA - 1][xA - 2] = 'w';
  if (maze[yA - 2][xA + 1] == 'w' && maze[yA - 1][xA] == 'e' && maze[yA - 1][xA + 2] == 'e' && maze[yA][xA + 1] == 'e')
    maze[yA - 2][xA + 1] = 'w';
  if (maze[yA + 2][xA + 1] == 'w' && maze[yA + 1][xA] == 'e' && maze[yA + 1][xA + 2] == 'e' && maze[yA][xA + 1] == 'e')
    maze[yA + 1][xA + 2] = 'w';
  if (maze[yA - 2][xA + 1] == 'w' && maze[yA - 1][xA + 2] == 'e' && maze[yA - 1][xA] == 'e' && maze[yA][xA + 1] == 'e')
    maze[yA + 2][xA - 1] = 'w';
}
int sizeI(int* arr) {
  return sizeof(arr) / sizeof(arr[0]);
}
int sizeC(char** arr) {
  return sizeof(arr) / sizeof(arr[0]);
}
