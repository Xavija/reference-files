'''
TODO:
    - ToC iniziale
    - titoli in italiano affiancati da controparte inglese
'''
#!/usr/bin/env python3.7

# Permette di essere eseguito come un programma in python senza richiamare l'interprete:
# chmod +x reference.py
# ./reference.py

'''
DICHIARAZIONI
- globale
- funzioni
    - args
    - kwargs
'''
global a        # viene specificato di utilizzare la variabile globale `a`
                # anziché quella locale

def func():     # funzione
    pass

'''
TIPI DI DATO PRINCIPALI

TIPO    ESEMPIO     MODIFICABILE?
int     1               y
float   0.1 (.1)        y
str     'ciao'          n
bool    True False      y
list    [1, 'a']        y
'''
a = 1           # int
b = .0          # float
c = 'ciao'      # str
d = True        # bool
e = [1, '2']    # list

type(a)     # verificare il tipo di una variabile

"A" + "B"   # -> "AB"
# NOTA: è possibile utilizzare sia "" che '' per le stringhe.
# A tempo di esecuzione non cambia nulla, ma alcune pratiche
# prevedono l'utilizzo di '' per stringhe non interpolabili
# e "" per stringhe interpolabili:
# 'Utente' "%(nome)" 'si è autenticato'

'''
MANIPOLAZIONE STRINGHE
- concatenazione    (+)
- ripetizione       (*)
(str only, per il resto consultare sez. Liste)
'''
stringa = 'Ohi!'    # Ohi!
stringa + 'Orya!'   # Ohi!Orya!     (concatenazione)
stringa * 3         # Ohi!Ohi!Ohi!  (ripetizione)

'''
COSTRUTTI
- condizionali:
    - if
    - elif
    - else
- loop:
    - while
    - for
'''
# Condizionali
if condizione1:
    pass
elif condizione2:
    pass
else:
    # a questo punto è sicuro che non sono verificate
    # le condizioni 1 e 2
    pass

# Loop
for i in range(5):
    ...
while True:
    ...

# Nei loop vi sono diverse keyword che possono essere usate:
'''
pass        operazione nulla (come `;` in C)
continue    salta alla condizione da valutare (in altre parole nuova iterazione)
break       esce dal costrutto in cui si trova
'''

'''
ECCEZIONI
'''
try:
    x = 0/0
except ZeroDivisionError:       # più in generale: Exception
    print("Divisione per 0!")
finally:                        # blocco che viene comunque eseguito (opzionale)
    exit(0)

# ESEMPIO: inserimento num. intero positivo
num = 0
while num < 1:
    try:
        num = int(input("Enter an integer value... "))
    except ValueError:
        print("Invalid input! Try again.")

'''
LISTE
- indicizzazione
- len()
- del
- copy
    - shallow copy
    - deep copy
- sort()
'''
lista = [1, 2, 3]
lista[0]
lista[:2]               # restituisce el. [0, 2)
lista[-1]               # restituisce l'ultimo elemento (-2 il penultimo...)
lista[:-1]              # restituisce el. [0, 2)
len(lista)              # lunghezza
lista[2] = lista[1]     # [1, 3, 2]
lista * 2               # [1, 3, 2, 1, 3, 2]
lista += [1, 0]         # [1, 3, 2, 1, 0]

del lista[0]            # elimina l'elemento di indice 0 della lista
                        # [3, 2, 1, 0]

lista.delete(1)         # elimino l'elemento con valore 1 della lista

b = [3, 4]
a = [1, 2, b]           # [1, 2, b] -> [1, 2, [3, 4]]

# copia di una lista
import copy as cp
b = [3, 4]
a = [1, 2, b]

c = cp.copy(a)          # SHALLOW COPY: eventuali liste annidate
                        # vengono copiate come riferimento:
                        # ciò significa che il cambiamento di b
                        # si ripercuote su c
c = cp.deepcopy(a)      # DEEP COPY: eventuali liste annidate
                        # vengono copiate come valore

# ordinamento
x = ['a', 'Z']
x.sort()                # ['Z', 'a']  a meno di key=str.lower
                        # (ASCIIbetical order)

# indice
x.index('Z')            # restituisce l'indice dell'elemento indicato...
                        # oppure un'eccezione: element is not in list
'''
CONFRONTI
- is
- not
- (not) in
'''
a = 'ciao'
if a is 'ciao':
    pass
lista = [1, 2, 3, 4]
if 1 in lista:          
    pass
if 5 not in lista:
    pass

'''
ITERATORI
- range()
- element in
'''
for i in range(5):          # 0 ~ 5, step 1
    pass
for i in range(5, 1):       # 1 ~ 5, step 1
    pass
for i in range(-5, 0, -1):  # 0 ~-5, step -1
    pass
# liste/array/collezioni di elementi
for element in array:
    if element > 0:
        pass

'''
PRINT
'''
print("x",end=',')          # specifica un carattere finale (default=newline)
                            # x,
print("x", "y", sep='|')    # specifica un carattere separatore (default=' ')

print(r'Hello\nI\'m Phil.') # Hello\nI\'m Phil. RAW STRING

'''
DIZIONARI
- dichiarazione
- accesso
- confronto
- funzioni
'''
dizionario = { chiave: valore } # dichiarazione generica
combinationDict = { 'mainLuggage': '1234', 'backpack': '0000', 'suitcase': '3478' }

combinationDict['mainLuggage']  # accesso
                                # -> '1234'
# accedere al valore relativo ad una certa chiave può risultare in un'eccezione KeyError
# in caso la chiave fornita non sia valida
combinationDict['asd']          # raises KeyError

eggs = {'name': 'Zophie', 'species': 'cat', 'age': '8'}
ham = {'species': 'cat', 'age': '8', 'name': 'Zophie'}

eggs == ham             # True: i dict non possono essere ordinati,
                        # ma vengono confrontati i valori di ogni chiave coi
                        # rispettivi del secondo dict

for val in eggs.values():   # values() restituisce una lista* di valori del dict
    print(val)              # Zophie, cat, 8

for key in ham.keys():      # keys() restituisce una lista* di chiavi del dict
    print(key)              # species, age, name

for item in ham.items():    # items() restituisce ogni coppia chiave-valore del dict (iterable)
    print(item)             # (name, Zophie), (species, cat), (age, 8)
# in alternativa:
# for k, v in ham.items():
#    print("Key:", k, "value:", v)

# *: le liste restituite sono read-only (no append), nello specifico:
# dict_values([...]), dict_keys([...])

ham.get('species', 'unknown')       # metodo get() accetta due parametri:
                                    # chiave e valore di default da usare in caso
                                    # la chiave non esista
ham.setdefault('pedigree', 'no')    # aggiunta di una chiave con valore di default:
                                    # viene aggiunta la chiave pedigree col valore 'no'
                                    # specificato da setdefault()
# nota bene che setdefault NON aggiorna il valore della chiave se questa esiste già
import pprint   # pretty printing per dict (formattazione delle chiavi in stampa...)


