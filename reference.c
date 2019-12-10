//MANUALE C
/*Indice:
    Librerie
    Definire una macro
    Definire un nuovo tipo enum
    PUNTATORI
        -Uso di * e &
        -Passaggio per riferimento
        -Funzione sizeof
    ALLOCAZIONE DINAMICA:
        -malloc()
        -free()
    DEFINIRE UN TIPO DI DATO
        -Struct
        -Typedef
        -Union
        -Discriminated union
        -Liste sequenziali
            -Nuova lista
            -Inserimento in coda
            -Inserimento in testa
            -Inserimento ordinato
            -Eliminazione
            -Ricerca
        -Liste collegate
            -Definizioni
            -Nuova lista
            -Vuota
            -Esempi di pattern:
                -forEach per stampa
                -Reduce (foldL) per somma
            -Inserimento in testa
            -Eliminazione in testa
            -Ricerca
            -Inserimento ordinato
            -Inserimento in coda
            -Insertion sort
    METODI
        -Definire una PROCEDURA
        -Prototipo di una FUNZIONE
        -Definire una FUNZIONE
    STRINGHE
        -Dichiarazione
        -Output
        -Alcuni metodi di string.h
    RAND                        
        -Calcolare un numero RANDOM
        -Calcolare un numero random compreso tra MAX e MIN
        -Calcolare un numero random con un SEED
    FILE
        -FILE DI TESTO
            -Lettura
            -Scrittura
        -FILE BINARI
            -Lettura
            -Scrittura
        -Accesso diretto
    SPECIFICATORI
    MAIN
        -Vincoli
        -Parametri
*/

//Librerie:
    #include <stdio.h>      //libreria standard input/output
    #include <stdlib.h>     //rand(), malloc(), free()...
    #include <math.h>       //pow, sqrt...
    #include <string.h>     //strchr(), strcmp(), strcpy()...
    //Alcuni metodi importanti:
        /*  strtol(char* str, char* endp, int base)
            stdlib.h
            Converte una stringa in un valore long int
        */
//Definire una macro:
    #define DIM 10

//Definire un nuovo tipo enum:
    enum week { sunday, monday, tuesday, wednesday, thursday, friday, saturday };
    enum week w1; //dichiarazione variabile
    w1 = sunday;

//PUNTATORI
    //Uso di * e &
        void puntatori() {
            int *p;
            int q;
            *p = &q;    //p punta alla cella di memoria di q

            int *c = (int*) 100;    //c punta alla cella #100
            c++;                    //ora c punta alla cella successiva: 104 (100 + una cella int)
                                    //equivale a c = c + sizeof(int);
        }

    //Passaggio per riferimento
        void passaggio(int b[]) {
            b[0] = 0;
            //in questo modo non serve ritornare un valore
            //per poi assegnarlo all'el. 0 dell'array
        }

    //Funzione sizeof
        int getSize() {
        return sizeof(int); //restituisce la dimensione in byte occupata dal tipo int
        }

    /*NOTA:
        l'operatore '->' è equivalente alla scrittura '(*a).attributo',
        dove *a è un puntatore ad una variabile di tipo struct x e attribute è un suo attributo definito appunto nella struct.
    */
//ALLOCAZIONE DINAMICA --> stdlib.h
	//malloc()
		void allocaMemoria() {
			int *p = (int*)malloc(5*sizeof(int));
			//In questo modo ho dichiarato una var. p allocando 5*4=20byte di memoria;
			p[4] = 7;	//20byte di memoria = array di 5 elementi;
		}

	//free()
		void liberaMemoria() {
			int *p = (int*) malloc(5*sizeof(int));
			//codice...
			free(p);
			//ora non posso più utilizzare la var. p: ho appena liberato i suoi 20byte di allocazione
			p = NULL;	//lecito
			p = 100; 	//ILLECITO (DANGLING POINTER: puntatore che punta ad una cella di memoria non più valida)
		}

//DEFINIRE UN TIPO DI DATO:
    //Struct
        struct Persona {
            char nome[8];
            char cognome[8];
            char sesso;
            int anno_nascita;
        } p1, p2;               //dichiaro due variabili di tipo struct Persona p1 e p2
                                //struct Persona p1;
    //Typedef
        typedef struct {
            int id;
            char titolo[20];
            char autore[20];
            int anno_pubblicazione;
        } Libro;                //DEFINISCO un nuovo tipo: Libro; per istanziare una var. di tipo libro userò:
                                //Libro l1;
    //Union
        typedef union {
            int a;
            float b;
        } numero;
        //La dimensione della union è pari al campo di dimensione maggiore:
        void unionNumero(){
            numero n;
            n.a = 5;    //numero significativo: 5 (int); dimensione occupata = dimensione float;
            n.b = 4.2;  //numero significativo: 4.2 (float); dimensione occupata = dimensione float;
        } 
        /*La dimensione della union è pari al campo di dimensione maggiore: se definisco union con campi int e float,
        allora la dimensione sarà pari al float.
        Inoltre, solo l'ultimo valore assegnato ha valore significativo nelle union;
        questo problema viene risolto dalle DISCRIMINATED UNION con un campo enumerativo.*/
    
    //Discriminated union:
        typedef enum {quadrato, cerchio, rettangolo, triangolo} TipoFigura;
        //dichiaro una variabile in grado di contenere dati di tipo diverso in momenti diversi;
        typedef struct {
            TipoFigura tipo;
            union {
                struct { float lato; } dati_quadrato;
                struct { float raggio; } dati_cerchio;
                struct { float base, altezza; } dati_rettangolo;
                struct { float lato1, lato2, lato3; } dati_triangolo;
            } dato;
        } Figura;
        /*ES: Figura f; 
            figura.tipo = quadrato;
            figura.dato.dati_quadrato.lato = 9.0;*/
    //Liste sequenziali:
        typedef struct {
            int n_elementi; //dimensione logica
            int dati[DIM];  //vettore (dimensione fisica: DIM; logica: n_elementi)
        } Lista;
        /*  - Si interagisce con le liste tramite procedure (liste ADT);
            - Non consentono l'accesso indicizzato agli elementi, quindi per la ricerca è necessario scorrere tutta la lista
              finché non si trova l'elemento ricercato
            - non hanno dimensione fissa*/
        
        //Nuova lista:
            void nuovaLista(Lista *l) {
                l->n_elementi = 0;
            }

        //Inserimento in coda:
            void inserimento_coda(Lista *l, int input) {
                int i;
                if(l->n_elementi == DIM) 
                    exit(-1);
                
                l->dati[l->n_elementi + 1] = input;
                l->n_elementi++;
            }

        //Inserimento in testa:
            void inserimento_testa(Lista *l, int input) {
                int i;
                if(l->n_elementi == DIM)
                    exit(-1); //lista piena: impossibile aggiungere elementi
                
                for(i = l->n_elementi; i > 0; i--)
                    l->dati[i] = l->dati[i-1];  //shift degli el. verso dx per ottenere spazio per l'el. da aggiungere
                
                l->dati[0] = input;    //inserimento
                
                l->n_elementi++;        //incremento della dimensione logica
            }

        //Inserimento ordinato:
            void inserimento_ordinato(Lista *l, int input) {
                int i;
                if(l->n_elementi == DIM)
                    exit(-1);   //lista piena: impossibile aggiungere elementi
                
                //shif dx di tutti gli el. della lista maggiori del numero in input
                i = l->n_elementi;
                while(i > 0 && l->dati[i-1] > input) {
                    l->dati[i] = l->dati[i-1];
                    i--;
                }
                //ora posso inserire l'elemento nella lista
                l->dati[i] = input;
                l->n_elementi++;    //aggiorno la dimensione logica
            }
        
        //Eliminazione
            void elimina(Lista *l, int elemento) {
                int i = 0, j;
                while(i < l->n_elementi) { //scorro tutti gli elementi della lista
                    if(l->dati[i] == elemento) {    //se trovo l'elemento da eliminare...
                        for(j = i; j < l->n_elementi-1; j++) //...shifto a sx tutti gli el. che lo seguono
                            l->dati[j] = l->dati[j+1];
                        l->n_elementi--;    //aggiorno la dimensione logica
                    }
                    else
                        i++;
                }
            }

        //Ricerca
            int ricerca(Lista l, int query) {
                int i;
                //scorre tutta la lista alla ricerca dell'elemento query
                for(i = 0; i < l.n_elementi; i++) {
                    if(l.dati[i] == query)
                        return 1;   //ritorna 1 se l'elemento è presente nella lista...
                }
                return 0; //...0 altrimenti
            }

    //Liste collegate:
        /*Implementa l'allocazione dinamica, allocando memoria con malloc() quando si aggiunge
            un elemento alla lista e liberandola con free() quando si elimina.
            Rispetto alle liste sequenziali, l'occupazione di memoria è relativa alla dimensione logica della lista.
            */
        //Definizioni
            typedef int Dato;
            typedef struct nodo { Dato dato; struct nodo* next; } Nodo;
            typedef Nodo* Lista;

        //Nuova lista
            void nuovaLista(Lista *l) {
                *l = NULL;
            }

        //Vuota
            int isEmpty(Lista l) {
                return l == NULL;
            }            
            //Una lista può essere vuota, ma non potrà mai essere piena.
        
        //Esempi di pattern:
            //forEach per stampa
                void stampa(Lista l) {
                    while(l) {
                        printf("%d ", l->dato);
                        l = l->next;
                    }
                    printf("\n");
                }

            //Reduce (foldL) per somma
                int somma(Lista l) {
                    int s = 0;
                    while(l) {
                        s += l->dato;
                        l = l->next;
                    }
                    return s;
                }

        //Inserimento in testa
            void inserimento_testa(Lista *l, Dato d) {
                Nodo* aux = (Nodo*) malloc(sizeof(Nodo));
                aux->dato = d;
                aux->next = *l;
                *l = aux;
            }

        //Eliminazione in testa
            //se e solo se la lista NON è vuota
            void eliminazione_testa(Lista *l) {
                Nodo* aux = *l;
                *l = (*l)->next;
                free(aux);  
            }
    
        //Ricerca
            Lista* query(Lista *l, Dato d) {
                while(*l) {
                    if((*l)->dato == d)
                        break;
                    else
                        l = &(*l)->next;
                }
                return l;
            }
        
        //Elimina tutti gli elementi ricercati
            int eliminaElementiRicercati(Lista *l, int d) {
                l = ricerca(l, d);
                if(*l) {
                    eliminazioneTesta(l); return 1;
                }
                else
                    return 0;
            }

        //Inserimento ordinato
            void inserimento_ordinato(Lista *l, Dato d) {
                l = query(l, d);
                inserimento_testa(l, d);
            }

        //Inserimento in coda
            //Richiede una modifica del metodo query
            Lista* query(Lista *l, Dato d) {
                while(*l) {
                    if((*l).dato > d)
                        break;
                    l = &(*l)->next;
                }
                return l;
            }
            void inserimento_coda(Lista *l, Dato d) {
                query(l, d);
                inserimento_testa(l, d);
            }

        //Insertion sort
            void insertionSort(Lista *a) {
                Lista b;
                nuovaLista(&b);
                
                while(*a) {
                    inserimento_ordinato(&b, (*a)->dato);
                    eliminazione_testa(a);
                }

                *a = b;
            }

//METODI:
    //Definire una PROCEDURA:
        void stampaNumero(int n) {  //tipo: VOID; ammette parametri ma non restituisce valori
            printf("%d",n);
        }

    //Prototipo di una FUNZIONE:
        int somma(int x, int y);    //la "dichiarazone" di una funzione

    //Definire una FUNZIONE:
        int somma(int x, int y) {   //tipo: QUALSIASI - {VOID}; ammette parametri
            return x + y;           //restituisce uno e un solo valore
        }

//STRINGHE:     --> ~ <string.h>
    //Dichiarazione
        void nuovaStringa() {
            char c = 'c';               //carattere
            char a[9] = "12345678";     //l'ultimo carattere è riservato per il null terminator '\0'
            char b[] = "ciao";          //b ha dimensione 4+1
            char s[9];
            scanf("%s",s);
        }

    //Output
        void stampaStringa() {
            char a[9] = "BoDereku";
            printf("%s\n",a);
        }

    //Alcuni metodi della libreria string.h
        void chiamate() {
            char a[9] = "Sventato", b[12] = "Barbatrucco", c[9];
            strcmp(a, b);           //confronta le due stringhe; se uguali ritorna 0, altrimenti <0 se a<b o >0 se a>b
            strchr(a, 'e');         //controlla che il carattere 'e' sia contenuto nella stringa a[];
                                    //restituisce un puntatore che indica la posizione del carattere trovato, altrimenti NULL
            strcpy(c, a);           //copia il contenuto della stringa a[] in c[]
        }


//RAND
    //Calcolare un numero RANDOM
        int nRandom(){
            return rand();
        }
    
    //Calcolare un numero random compreso tra MAX e MIN
        int randomMaxMin(int max, int min) {
            return min + rand() / RAND_MAX * (max-min);
        }

    //Calcolare un numero random con un SEED
        void randomSeed(int seed) {
            srand(seed);
            /* CASO PARTICOLARE:
            per generare un numeto random dipendente dall'ora:
            srand(time(NULL));*/
        }
//FILE          -->   <stdlib.h>
    //FILE DI TESTO:
        //Lettura
        void leggiFileDiTesto() {
            FILE *f;                        //dichiarazione del puntatore f di tipo FILE
            f = fopen("file.txt", "rt");    //fopen: apertura del file file.txt in modalità rt (read, text)
                                            /*  r   --> read        --> il file deve esistere
                                                w   --> write       --> se non esiste, crea un file, altrimenti sovrascrive
                                                a   --> append      --> scrive dentro al file partendo dall'EOF in momento di apertura
                                                r+  --> rw          --> apre un file esistente con permessi rw
                                                w+  --> rw          --> crea e are un file con permessi rw
                                                a+  --> ra          --> apre un file esistente e fa l'append
                                                *b  --> rb, wb, ab  --> operazioni per file binari
                                                *t  --> rt, wt, at  --> operazioni per file di testo
                                            */
            if(f == NULL) { //controllo OBBLIGATORIO di eventuali errori
                printf("Errore durante l'apertura del file\n");
                exit(-1);
            }
            
            char s[9];
            //lettura fino alla fine del file:
            while(!feof(f)) {   
                fscanf(f, "%s", s);     //lettura di testo formattato da file
                printf("%s\n",s);       //NON legge una riga intera; solo il testo definito
                
                fgets(s, 9, f);         //legge una riga fino a 9-1 elementi e li inserisce in s;
                                        //si ferma quando raggiugne n-1, EOF o '\n'
            }

            if(fclose(f))               //chiusura del flusso con annesso controllo di eventuali errori
                exit(-1);               
        }

        //Scrittura (append è analogo)
        void scriviSuFileDiTesto() {
            FILE *f = fopen("file.txt", "wt"); //apertura/creazione del file con wt (write, text)
            //CONTROLLO ERRORI
            char s[9] = "hissatsu";
            fprintf(f, "%s %d", s, 912); //scrivo: hissatsu 912 nel file
            //CHIUSURA DEL FLUSSO + CHECK
        }

    //FILE BINARI:
        //Lettura:
        void leggiFileBinario() {
            FILE *f = fopen("file.dat", "rb");  //apertura del file file.dat in modalità rb (read, bytes)
            //CONTROLLO DEGLI ERRORI
            int target[40];

            fread(target, sizeof(int), 40, f);  //legge fino a 40 interi di dimensione sizeof(int)
                                                // e li mette in target[]
            //CHIUSURA DEL FLUSSO + CHECK
        }

        //Scrittura:
        void scriviSuFileBinario() {
            FILE *f = fopen("file.dat", "wb");  //apertura/creazione del file file.dat in modalità wb (write, bytes)
            //CONTROLLO DEGLI ERRORI    
            int source[5] = {1, 2, 3, 4, 5};
            fwrite(source, sizeof(int), 5, f);  //scrive 5 elementi di dimensione sizeof(int) presi da source[]
            //CHIUSURA DEL FLUSSO + CHECK
        }
    //Accesso diretto
        void spostaTestina() {
            FILE *f = fopen("file.txt","rt"); //il tipo non centra; basta che sia aperto in r
            //CONTROLLO DEGLI ERRORI
            //fseek(FILE *f, long offset, int origin);
            fseek(f, ftell(f)-1, SEEK_SET); //ftell(f) restituisce la posizione corrente della testina
                                            //SEEK_SET è l'inizio del file
            //quindi sposto la testina indietro di una posizione
        }

//SPECIFICATORI
    /*
        %d      -->     int
        %c      -->     char
        %s      -->     char[]
        %f      -->     float
        %lf     -->     double
    */
//MAIN
    //Vincoli
        int main(int argc, char *argv[]) {   //tipo INT; l'ultima istruzione è return 0
            //argc      -->     n argonemnti
            //*argv[]   -->     vettore argomenti
            return 0;
        }
    
    //Parametri
        int main(int argc, char *argv[]) {
            //Esempio di un programma che apre un file definito dall'utente
            if(argc != 2) {
                printf("Uso: %s nomefile\n", argv[0]);
                exit(-3);
            }
            FILE *f = fopen(argv[1], "rt");
            //....
        }
        /*NOTA
        Per configurare il debugger nell'IDE Visual Studio Code
        bisogna, oltre al resto, inserire gli argomenti nel
        campo argv[]
        */