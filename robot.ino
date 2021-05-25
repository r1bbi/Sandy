
void robot(){
  pot1=A15;
  pot2=A14;
  check=53;
  pinMode(pot1,INPUT);
  pinMode(pot2,INPUT);
  pinMode(check,INPUT);
}
void avanti(){
    //avanti di una cella
}
void sinistra(){
    //giro di 90 a sinistra
}
void destra(){
    //giro di 90 a destra
}
void stabilizza(){
    //va indietro e si raddizza
}
void indietro(){
     //va indietro di una casella
}
bool sAvanti(){
    //true se il sonar davanti sta vedendo un muro
    return true;
}
bool sSinistra(){
    //true se il sonar sinistro sta vedendo un muro
    return true;
}
bool sDietro(){
    //true se il sonar dietro sta vedendo un muro
    return true;
}
bool sDestra(){
    //true se il sonar destro sta vedendo un muro
    return true;
}
