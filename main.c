#include <stdio.h> 
#include <string.h>
#include <math.h> 

//Porte logiche
int NOT(int a) { return 1 - a;}
int AND(int a, int b) { return (a*b);}
int OR(int a, int b) { return (a+b)-(a*b);}
int XOR(int a, int b) { return (a+b) - 2*(a*b);}
int OR3(int a, int b, int c) { return OR(OR(a,b),c);}
int OR4(int a, int b, int c, int d) { return OR(OR3(a,b,c),d);}
int OR5(int a, int b, int c, int d, int e) { return OR(OR4(a,b,c,d),e);}
int NOR(int a, int b){ return NOT((a+b)-(a*b));}
int NOR3(int a, int b, int c){ return NOT(OR3(a,b,c));}
int NOR4(int a, int b, int c, int d){ return NOT(OR4(a,b,c,d));}
int AND3(int a, int b, int c) { return a*b*c;}
int AND4(int a, int b, int c, int d) { return a*b*c*d;}
int AND5(int a, int b, int c, int d, int e) {return a*b*c*d*e;}
int NAND(int a, int b){ return NOT(a*b);}
int NAND3(int a, int b, int c){ return NOT(a*b*c);}
int NAND4(int a, int b, int c, int d){ return NOT(a*b*c*d);}
int NAND5(int a, int b, int c, int d, int e){ return NOT(a*b*c*d*e);}
int XOR3(int a, int b, int c) { return XOR(XOR(a, b), c);}
int XOR4(int a, int b, int c, int d) { return XOR(XOR(a, b), XOR(c, d)); }
int XOR5(int a, int b, int c, int d, int e) { return XOR(XOR4(a, b, c, d), e); }

//ALU
void ALU(int Cn, int M, int A0, int B0, int A1, int B1, int A2, int B2, int A3, int B3, int S0, int S1, int S2, int S3, int* f0, int* f1, int* f2, int* f3, int* ab, int* cn4)
{
// Calcolo parte 1
int z = NOR3(AND(NOT(B0),S1),AND(S0,B0),A0);
int z1 = NOR(AND3(A0,NOT(B0),S2),AND3(B0,A0,S3));
int z2 = NOR3(AND(NOT(B1),S1),AND(S0,B1),A1);
int z3 = NOR(AND3(A1,NOT(B1),S2),AND3(B1,A1,S3));
int z4 = NOR3(AND(NOT(B2),S1),AND(S0,B2),A2);
int z5 = NOR(AND3(A2,NOT(B2),S2),AND3(B2,A2,S3));
int z6 = NOR3(AND(NOT(B3),S1),AND(S0,B3),A3);
int z7 = NOR(AND3(A3,NOT(B3),S2),AND3(B3,A3,S3));

// Calcolo parte 2
int nm = NOT(M);
*f0 = XOR(NAND(nm,Cn),XOR(z1,z2));
*f1 = XOR(NOR(AND(nm,z),AND3(nm,Cn,z1)),XOR(z2,z3));
*f2 = XOR(NOR3(AND(z2,nm),AND3(nm,z,z3),AND4(nm,z3,z1,Cn)),XOR(z4,z5));
*f3 = XOR(OR4(AND(nm,z4),AND3(nm,z2,z5),AND4(nm,z,z5,z3),AND5(nm,z5,z3,z1,Cn)),XOR(z6,z7));
*ab = AND4(*f0,*f1,*f2,*f3);
int x = NAND4(z1,z3,z5,z7);
*cn4 = OR(NOT(NAND5(Cn,z1,z3,z5,z7)),NOT(NOR4(AND4(z,z3,z5,z7),AND3(z2,z5,z7),AND(z4,z7),z6)));
int y = NOR4(AND4(z,z3,z5,z7),AND3(z2,z5,z7),AND(z4,z7),z6);
}

//Registro
void REGISTRO(int i0, int i1, int i2, int i3, int i4 , int i5, int i6, int i7, int* o0, int* o1, int* o2, int* o3, int* o4, int* o5, int* o6, int* o7){
int reset = 0;

//Reset
*o0 = AND(i0, NOT(reset));
*o1 = AND(i1, NOT(reset));
*o2 = AND(i2, NOT(reset));
*o3 = AND(i3, NOT(reset));
*o4 = AND(i4, NOT(reset));
*o5 = AND(i5, NOT(reset));
*o6 = AND(i6, NOT(reset));
*o7 = AND(i7, NOT(reset));
       
//Visualizzazione numeri memorizzati
printf("Numero che è stato memorizzato o0 = %d\n", *o0);
printf("Numero che è stato memorizzato o1 = %d\n", *o1);
printf("Numero che è stato memorizzato o2 = %d\n", *o2);
printf("Numero che è stato memorizzato o3 = %d\n", *o3);
printf("Numero che è stato memorizzato o4 = %d\n", *o4);
printf("Numero che è stato memorizzato o5 = %d\n", *o5);
printf("Numero che è stato memorizzato o6 = %d\n", *o6);
printf("Numero che è stato memorizzato o7 = %d\n", *o7);

// Scelte utente
while (1) {
    int s;
    printf("Scelte disponibili:\n");
    printf("1 = Reset\n");
    printf("2 = Sovrascrivere i valori nella memoria con nuovi valori\n");
    printf("3 = Termina\n");
    printf("Cosa vuoi fare?\n");
    scanf("%d", &s);

    if (s == 1) {
    // Caclolo reset
    i0 = 0;
    i1 = 0;
    i2 = 0;
    i3 = 0;
    i4 = 0;
    i5 = 0;
    i6 = 0;
    i7 = 0;
    reset = 1;
      
    *o0 = AND(i0, NOT(reset));
    *o1 = AND(i1, NOT(reset));
    *o2 = AND(i2, NOT(reset));
    *o3 = AND(i3, NOT(reset));
    *o4 = AND(i4, NOT(reset));
    *o5 = AND(i5, NOT(reset));
    *o6 = AND(i6, NOT(reset));
    *o7 = AND(i7, NOT(reset));
            
    printf("Il risultato del reset è o0 = %d\n", *o0);
    printf("Il risultato del reset è o1 = %d\n", *o1); 
    printf("Il risultato del reset è o2 = %d\n", *o2); 
    printf("Il risultato del reset è o3 = %d\n", *o3);
    printf("Il risultato del reset è o4 = %d\n", *o4); 
    printf("Il risultato del reset è o5 = %d\n", *o5);
    printf("Il risultato del reset è o6 = %d\n", *o6);
    printf("Il risultato del reset è o7 = %d\n", *o7);
    }
    
else if (s == 2) {
//Nuove variabili
printf("Inserire le 8 nuove variabili:\n");
scanf("%d", &i0);
scanf("%d", &i1);
scanf("%d", &i2);    
scanf("%d", &i3);    
scanf("%d", &i4);    
scanf("%d", &i5);    
scanf("%d", &i6);   
scanf("%d", &i7);    
     
//Memorizzazione variabili
*o0 = AND(i0, NOT(reset));
*o1 = AND(i1, NOT(reset));
*o2 = AND(i2, NOT(reset));
*o3 = AND(i3, NOT(reset));
*o4 = AND(i4, NOT(reset));
*o5 = AND(i5, NOT(reset));
*o6 = AND(i6, NOT(reset));
*o7 = AND(i7, NOT(reset));
    
//Visualizazzione memorizzazione
printf("Il numero che è stato memorizzato in o0 è %d\n", *o0);
printf("Il numero che è stato memorizzato in o1 è %d\n", *o1);
printf("Il numero che è stato memorizzato in o2 è %d\n", *o2);
printf("Il numero che è stato memorizzato in o3 è %d\n", *o3);
printf("Il numero che è stato memorizzato in o4 è %d\n", *o4);
printf("Il numero che è stato memorizzato in o5 è %d\n", *o5);
printf("Il numero che è stato memorizzato in o6 è %d\n", *o6);
printf("Il numero che è stato memorizzato in o7 è %d\n", *o7);
    } 
    else if (s == 3) {
    printf("Registro terminato\n");
    break;
    } 
    else {
    printf("Scelta non valida, riprova\n");
        }
    }
}

//Funzione per riempire gli spazi rimanenti con 0 se il valore è meno di 32 bit
void LETTURA(char* reg, int indicereg, int valreg[8]) {
    for (int b = 0; b < 8; b++) {
        int r = indicereg + b;
        
        if (reg[r] == '0' || reg[r] == '1') {
            valreg[b] = reg[r] - '0';
        } else {
            valreg[b] = 0; 
        }}}

void INVERTI(char* Abin) {
int lunghezza = strlen(Abin);
int i, j;
char rif;
for (i = 0, j = lunghezza - 1; i < j; i++, j--) {
rif = Abin[i];
Abin[i] = Abin[j]; 
Abin[j] = rif;
    }
}

//Deciamle a binario
void BIN(int A, char* Abin) {
if (A == 0) {
    strcpy(Abin, "0");
    return;
}

int i = 0;
int Arif = A;

while (Arif > 0){
    if(Arif % 2 == 0){Abin[i] = '0' ;}
    else{Abin[i]= '1' ;}
        
    Arif /= 2;
    i++;
}
    
Abin[i] = '\0';
INVERTI(Abin);
}

long long bindec(char bin[]) {
long long dec = 0;
int potenza = 0;         

//Potenza di ogni bit partendo da sinistra
for (int i = strlen(bin) - 1; i >= 0; i--) {
    if (bin[i] == '1') {
    dec += (long long)pow(2, potenza);
    }
    potenza++;
    }
    return dec;
}

int main() {
//Dichiarazione variabili
int A, B, S0, S1, S2, S3, M, Cn;
char numA[32 + 1];
char numB[32 + 1];

printf("Inserisci il primo numero decimale positivo\n");
scanf("%d", &A);
printf("Inserisci il secondo numero decimale positivo\n");
scanf("%d", &B);
printf("Inserisci il valore di S0 (0 o 1):\n");
scanf("%d", &S0);
printf("Inserisci il valore di S1 (0 o 1):\n");
scanf("%d", &S1);
printf("Inserisci il valore di S2 (0 o 1):\n");
scanf("%d", &S2);
printf("Inserisci il valore di S3 (0 o 1):\n");
scanf("%d", &S3);
printf("Inserisci il valore di M (0 o 1):\n");
scanf("%d", &M);
printf("Inserisci il valore di Cn (0 o 1):\n");
scanf("%d", &Cn);

//Richiamo funzione per convertire da decimale a binario
BIN(A, numA);
BIN(B, numB);

printf("Il numero %d in binario è %s\n", A, numA);
printf("Il numero %d in binario è %s\n", B, numB);

//Dichiarazione variabili
int lunghezza;
int IrA[4][8]; 
int OutrA[4][8];
int IrB[4][8]; 
int OutrB[4][8];

//Controllo overflow
lunghezza = strlen(numA);

printf("Numero inserito: %s il numero di bit è %d\n", numA, lunghezza);
if(lunghezza > 32){ 
    printf("Valore A causa overflow\n");
    return 0;
}

lunghezza = strlen(numB);

printf("Numero inserito: %s il numero di bit è %d\n", numB, lunghezza);
if(lunghezza > 32){ 
    printf("Valore B causa overflow\n");
    return 0;
}

//Memorizzazione nel registro A e B
    for (int r = 0; r < 4; r++) { 
        LETTURA(numA, r * 8, IrA[r]);

printf("Inizializzazione e Interazione con Registro %d\n", r);
        REGISTRO(IrA[r][0], IrA[r][1], IrA[r][2], IrA[r][3], IrA[r][4], IrA[r][5], IrA[r][6], IrA[r][7], &OutrA[r][0], &OutrA[r][1], &OutrA[r][2], &OutrA[r][3], &OutrA[r][4], &OutrA[r][5], &OutrA[r][6], &OutrA[r][7]);

LETTURA(numB, r * 8, IrB[r]);
printf("Inizializzazione e Interazione con Registro %d\n", r);
        REGISTRO(IrB[r][0], IrB[r][1], IrB[r][2], IrB[r][3], IrB[r][4], IrB[r][5], IrB[r][6], IrB[r][7], &OutrB[r][0], &OutrB[r][1], &OutrB[r][2], &OutrB[r][3], &OutrB[r][4], &OutrB[r][5], &OutrB[r][6], &OutrB[r][7]);
}

//Visualizzazione risultato
printf("Stato finale del registro A:\n");
for (int r = 0; r < 4; r++){
    printf("Registro %d: ", r);
    for (int b = 0; b < 8; b++) {
        printf("%d", OutrA[r][b]);
        }
    printf("\n");
    }

printf("Stato finale del registro B:\n");
for (int r = 0; r < 4; r++){
    printf("Registro %d: ", r);
    for (int b = 0; b < 8; b++) {
        printf("%d", OutrB[r][b]);
        }
    printf("\n");
    }

//Dichiarazione variabili
int F[4][8];
int Cn4[8];
int ab;

//Calcolo ALU
ALU(Cn, M, OutrA[1][0], OutrB[1][0], OutrA[2][0], OutrB[2][0], OutrA[3][0], OutrB[3][0], OutrA[4][0], OutrB[4][0], S0, S1, S2, S3, &F[1][0], &F[2][0], &F[3][0], &F[4][0], &ab, &Cn4[0]);
printf("Risultati 1° ALU:\n");
printf("%d\n", F[1][0]);
printf("%d\n", F[2][0]);
printf("%d\n", F[3][0]);
printf("%d\n", F[4][0]);
ALU(Cn4[0], M, OutrA[1][1], OutrB[1][1], OutrA[2][1], OutrB[2][1], OutrA[3][1], OutrB[3][1], OutrA[4][1], OutrB[4][1], S0, S1, S2, S3, &F[1][1], &F[2][1], &F[3][1], &F[4][1], &ab, &Cn4[1]);
printf("Risultati 2° ALU:\n");
printf("%d\n", F[1][1]);
printf("%d\n", F[2][1]);
printf("%d\n", F[3][1]);
printf("%d\n", F[4][1]);
ALU(Cn4[1], M, OutrA[1][2], OutrB[1][2], OutrA[2][2], OutrB[2][2], OutrA[3][2], OutrB[3][2], OutrA[4][2], OutrB[4][2], S0, S1, S2, S3, &F[1][2], &F[2][2], &F[3][2], &F[4][2], &ab, &Cn4[2]);
printf("Risultati 3° ALU:\n");
printf("%d\n", F[1][2]);
printf("%d\n", F[2][2]);
printf("%d\n", F[3][2]);
printf("%d\n", F[4][2]);
ALU(Cn4[2], M, OutrA[1][3], OutrB[1][3], OutrA[2][3], OutrB[2][3], OutrA[3][3], OutrB[3][3], OutrA[4][3], OutrB[4][3], S0, S1, S2, S3, &F[1][3], &F[2][3], &F[3][3], &F[4][3], &ab, &Cn4[3]);
printf("Risultati 4° ALU:\n");
printf("%d\n", F[1][3]);
printf("%d\n", F[2][3]);
printf("%d\n", F[3][3]);
printf("%d\n", F[4][3]);
ALU(Cn4[3], M, OutrA[1][4], OutrB[1][4], OutrA[2][4], OutrB[2][4], OutrA[3][4], OutrB[3][4], OutrA[4][4], OutrB[4][4], S0, S1, S2, S3, &F[1][4], &F[2][4], &F[3][4], &F[4][4], &ab, &Cn4[4]);
printf("Risultati 5° ALU:\n");
printf("%d\n", F[1][4]);
printf("%d\n", F[2][4]);
printf("%d\n", F[3][4]);
printf("%d\n", F[4][4]);
ALU(Cn4[4], M, OutrA[1][5], OutrB[1][5], OutrA[2][5], OutrB[2][5], OutrA[3][5], OutrB[3][5], OutrA[4][5], OutrB[4][5], S0, S1, S2, S3, &F[1][5], &F[2][5], &F[3][5], &F[4][5], &ab, &Cn4[5]);
printf("Risultati 6° ALU:\n");
printf("%d\n", F[1][5]);
printf("%d\n", F[2][5]);
printf("%d\n", F[3][5]);
printf("%d\n", F[4][5]);
ALU(Cn4[5], M, OutrA[1][6], OutrB[1][6], OutrA[2][6], OutrB[2][6], OutrA[3][6], OutrB[3][6], OutrA[4][6], OutrB[4][6], S0, S1, S2, S3, &F[1][6], &F[2][6], &F[3][6], &F[4][6], &ab, &Cn4[6]);
printf("Risultati 7° ALU:\n");
printf("%d\n", F[1][6]);
printf("%d\n", F[2][6]);
printf("%d\n", F[3][6]);
printf("%d\n", F[4][6]);
ALU(Cn4[6], M, OutrA[1][7], OutrB[1][7], OutrA[2][7], OutrB[2][7], OutrA[3][7], OutrB[3][7], OutrA[4][7], OutrB[4][7], S0, S1, S2, S3, &F[1][7], &F[2][7], &F[3][7], &F[4][7], &ab, &Cn4[7]);
printf("Risultati 8° ALU:\n");
printf("%d\n", F[1][7]);
printf("%d\n", F[2][7]);
printf("%d\n", F[3][7]);
printf("%d\n", F[4][7]);

//Dichiarazione matrice
int Out[4][8];

for (int r = 0; r < 8;) { 
printf("Inizializzazione e Interazione con Registro %d\n", r);
        REGISTRO(IrA[1][r], IrA[2][r], IrA[3][r], IrA[4][r],
                 IrA[1][r+1], IrA[2][r+1], IrA[3][r+1], IrA[4][r+1],
                 &Out[1][r], &Out[2][r], &Out[3][r], &Out[4][r],
                 &Out[1][r+1], &Out[2][r+1], &Out[3][r+1], &Out[4][r+1]);
      r+=2;
}

//Raggruppamento valori binari
    char Bitfin[32 + 1];
    int p = 0;

    for (int r = 0; r < 4; r++) {
        for (int b = 0; b < 8; b++) {
            if (p < 32) {
                Bitfin[p] = OutrA[b][r] + '0';
                p++;}
            else {
                break;
            }}
        if (p >= 32) {
            break;
        }}
    Bitfin[p] = '\0';
    
// Conversione da binario a decimale
    long long valdec = bindec(Bitfin);

//Visualizzazione risultato finale
    printf("Il numero binario %s in decimale è %lld\n", Bitfin, valdec);
    printf("\nProgramma finito\n");
    return 0;
} 
