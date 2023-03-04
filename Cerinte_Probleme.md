# OOP
Object-Oriented Programming Codes

Problema WOW

Se implementează versiunea simplificată a unei interacțiuni de tip Player-versus-Player din World of Warcraft. Implementarea presupune realizarea secvențială a unor lupte 1v1 între caracterul propriu și alt caracter.

 

O luptă poate fi descrisă prin mai multe runde; la începutul unei runde, fiecare Caracter alege o abilitate pe care să o folosească runda respectivă:

●            pentru Caracterul propriu abilitatea este citită de la tastatură;

●            pentru Caracterul inamic abilitatea este aleasă automat de către calculator.

 

Caracterul este descris astfel:

●            Nume

●            Nivel (LEVEL)

●            Atribute de bază

●           Viață (BASE_HP)

●             Atac (BASE_ATK)

●             Apărare (BASE_DEF)

●             Atac special (BASE_SP_ATK)

●            Apărare specială (BASE_SP_DEF)

●            Viteză (BASE_SPD)

 

La începutul luptei se calculează atributele specifice nivelului pentru ambi jucători, după formulele:

●            Viață (HP_LEVEL) = [(BASE_HP * LEVEL) / 50] + LEVEL + 10

●            Orice alt atribut (ATR_LEVEL) = [(BASE_ATR * LEVEL) / 50] + 10

 

Cu excepția atributului de viață efectivă (HP), orice alt atribut efectiv (ATR) poate fi modificat în luptă de abilitățile folosite. Valoarea atributelor efective se calculează cu ajutorul atributelor specifice nivelului și a unui nivel de modificare (STAGE), cu următoarele proprietăți:

●            Nivelul de modificare (STAGE) este specific fiecărui atribut;

●            STAGE este un întreg între -6 și 6;

●            Dacă STAGE este pozitiv, atunci valoarea efectivă ATR = [(2 + STAGE) * ATR_LEVEL / 2]

●            Dacă STAGE este negativ, atunci valoarea efectivă ATR = [2 * ATR_LEVEL / (2 - STAGE)]

 

Atributul de viață efectivă (HP) al unui jucător scade de fiecare dată când acesta suferă damage (DMG) și nu poate fi crescut în cadrul unei lupte. La începutul fiecărei lupte HP este egal cu atributul specific nivelului (HP_LEVEL) pentru ambi jucători implicați.


În cadrul fiecărei runde, cel cu viteza efectivă (SPD) cea mai mare începe primul și alege o abilitate. Dacă există egalitate între vitezele efective, caracterul propriu va fi primul.

 

Atunci când jucătorii folosesc abilități care cauzează daune (DMG), viața efectivă (HP) a adversarului scade cu daunele (DMG) cauzate. Primul caracter care atinge un nivel pentru viața efectivă (HP) mai mic sau egal cu 0 pierde lupta.

 

Dacă caracterul propriu va câștiga lupta, atunci va primi experiență (EXP) egală cu nivelul caracterului înfrânt (LEVEL). Dacă experiența (EXP) curentă lui este cel puțin egală cu dublul nivelului său (2 * LEVEL), atunci el va trece la nivelul următor și va pierde din experiența (EXP) sa acea valoare (2 * LEVEL). Caracterul jucătorului poate să avanseze  mai mult de 1 nivel în urma unei lupte. Caracterele nu pot avea un nivel (LEVEL) mai mare decât 100.

Dacă caracterul propriu va pierde lupta, atunci nu va primi experiență (EXP). Abilitățile caracterelor au cel puțin un efect din următoarele:

●            Cauzează daune (DMG) cu o anumită putere (PWR) dintr-un anumit tip (TYPE_ATK) după formula:

DMG = [(LEVEL * PWR * TYPE_ATK) / (60 * ENEMY_TYPE_DEF)]

TYPE_ATK poate fi ATK sau SP_ATK. Inamicul este forțat să se apere cu tipul corespunzător.

●            Modifică un atribut propriu (ATR) cu un anumit nivel de modificare (STAGE), care poate fi și negativ.

●            Modifică un atribut pentru inamic (ATR) cu un anumit nivel de modificare (STAGE) care poate fi și negativ.

 

Abilitățile vor avea cel mult un efect cauzator de daune (DMG), dar pot avea mai multe efecte de modificare (MOD) de atribute (fie proprii, fie pentru inamic, fie mixte). Efectul cauzator de daune (DMG) se aplică întotdeauna primul și abia apoi se aplică modificările de atribute, dacă lupta nu a fost deja câștigată.

 

Caracterele cunosc o listă de abilități și le pot folosi doar pe acestea. Caracterele au unul din următoarele 4 moduri de control:

●            Ușor: automat; folosește doar prima abilitate cunoscută;

●            Mediu: automat; folosește în ordine toate abilitățile pornind de la prima și când le termină pornește din nou de la început;

●            Avansat: automat; în fiecare rundă folosește abilitatea care cauzează cele mai multe daune (DMG).

●            Personalizat: în fiecare rundă se citește de la tastatură abilitatea folosită.

 

Cunoscând descrierea fiecărei abilități, atributele de bază pentru fiecare caracter, care este caracterul propriu și ce abilități cunoaște, precum și fiecare luptă prin care trece, afișați pentru fiecare luptă, atributele caracterelor la sfârșitul fiecărei runde. Separați luptele cu o linie goală.



La începutul, caracterul propriu are 0 puncte de experiență, indiferent de nivelul său.

Nici o abilitate care cauzează daune (DMG) nu poate cauza 0 daune; valoarea minimă este 1.

 

Efectele care modifică atribute nu vor pentru nivelul de modificare (STAGE) avea valori mai mari în modul decât 20.

 

Toate efectele de daune (DMG) vor avea puterea (PWR) cel puțin egală cu 1. Toate caracterele vor avea toate atributele de bază cel puțin egale cu 1.

Date de intrare:

Pe prima linie numele fișierului ce conține descrierea tuturor abilităților.

Pe a doua linie, numele fișierului ce conține descrierea tuturor caracterelor.

 

Pe a treia linie, separate prin spațiu, numele caracterului propriu, nivelul (LEVEL) acestuia, modul de control (USOR / MEDIU / AVANSAT / PERSONALIZAT) precum și numele tuturor abilităților pe care le cunoaște.

 

Până la final informații despre lupte, astfel:

Pe prima linie, separate prin spațiu, numele caracterului inamic, nivelul (LEVEL) acestuia, modul de control (USOR / MEDIU / AVANSAT / PERSONALIZAT) precum și numele tuturor abilităților pe care le cunoaște.

Pe următoarea linie, dacă este cazul, separate prin spațiu, abilitățile folosite de caracter

cu modul de control PERSONALIZAT.



Date din fișier


Fișierul ce conține descrierea tuturor abilităților este structurat astfel:

 

Un număr necunoscut de linii, fiecare linie conținând descrierea unei abilități. Informațiile sunt separate prin spațiu după cum urmează:

Numele abilității și un număr necunoscut de efecte până la finalul liniei. Efectele pot fi:

●            DMG PWR TYPE_ATK

●            SELF_MOD ATR STAGE

●            ENEMY_MOD ATR STAGE

Fișierul ce conține descrierea tuturor caracterelor este structurat astfel:

Un număr necunoscut de linii, fiecare linie conținând descrierea unui caracter. Informațiile sunt separate prin spațiu după cum urmează:

 

NUME BASE_HP BASE_ATK BASE_DEF BASE_SP_ATK BASE_SP_DEF BASE_SPD


Date de ieșire:
Pentru fiecare luptă, atributele caracter la începutul luptei precum și la finalul fiecărei runde. Întotdeauna afișați informațiile despre caracterul propriu pe primul rând indiferent de cine a fost primul în runda respectivă.


HP ATK DEF SP_ATK SP_DEF SPD

 

Atributele afișate sunt cele efective (Viața modificată de daune, restul atributelor modificate de abilități specifice).



Problema Acvariu

Fie o fabrică ce produce acvarii având următoarele forme: cub, paralelipiped dreptunghic, cilindru.

Fabrica folosește 3 tipuri de sticla pentru acvarii. Cele 3 tipuri de sticla au prețuri diferite (Lei / cm3) și suportă grosimi de până la 3 / 5 / X cm (X oarecare). Un acvariu cu grosime mai mare de 3 cm nu poate fi construit cu tipul 1 de sticlă. În mod asemănător, un acvariu cu grosime mai mare de 5 nu poate fi construit cu tipul 2 de sticlă.

Când comandă un acvariu, clientul precizează prețul (Lei / cm3), tipul acvariului (CUB / PARALELIPIPED / CILINDRU), dimensiunile acestuia (cm), tipul sticlei (1 / 2 / 3) precum și grosimea sticlei (cm).

Clientul plătește pentru acvariu prețul * volumul acestuia. Costul de producție al acvariului depinde de tipul de sticlă și este: grosime * (preț tip sticlă) * (aria totală) a acvariului. Profitul obținut de fabrică este diferența dintre prețul plătit de client și costul de producție.

Date fiind prețurile celor 3 tipuri de sticlă, precum și informațiile pentru N comenzi, să se afișeze descrescător profiturile obținute pentru acestea.

 

Date de intrare

Pe prima linie 3 numere reale separate prin spațiu: p1 p2 p3 reprezentând prețul pentru cele 3 tipuri de sticlă .

Pe următoarea linie un număr natural N, numărul de comenzi

Pe următoarele N linii, câte o comandă pe fiecare linie: p c [dc] ca g, reprezentând prețul, tipul acvariului {“CUB, “PARALELIPIPED”, “CILINDRU”}, dimensiunile acvariului în funcție de tip: L pentru “CUB”, H L W pentru “PARALELIPIPED”, H R pentru “CILINDRU”, tipul sticlă {1, 2, 3} și grosimea sticlei.

 

Date de ieșire

Cele N comenzi sortate descrescător după profit. Afișarea se va face cu 2 zecimale.




Problema Firma

O firmă de distribuție livrează în K țări. În fiecare zi, firma se află într-o țară și în ziua următoare poate ajunge în orice altă țară.

În fiecare țară există N resurse. Țările pot deține cantități din fiecare resursă și își pot modifica cantitatea de resurse deținute prin interacțiuni proprii sau prin interacțiune cu firma.

Interacțiunile proprii ale unei țări sunt:

● Producția: țara obține o cantitate X dintr-o anumită resursă;

● Consumul: țara consumă o cantitate dintr-o resursă. Dacă țara nu deține suficient din resursa respectivă atunci va consuma toata resursa respectivă și fericirea țării va scădea cu diferența;

● Prelucrarea : țara consumă o cantitate dintr-o resursă pentru a obține o cantitate din altă resursă. Dacă țara nu deține suficient din resursa consumată atunci prelucrarea nu va avea loc.

În ceea ce privește interacțiunile proprii, se cunosc următoarele următoarele:

● Nu este obligatoriu ca o țară să interacționeze cu toate resursele disponbile

● Nu va exista nici o resursă care să fie consumată în 2 interacțiuni diferite de către țara respectivă

● Nu va exista nici o resursă obținută din prelucrare care să fie consumată în altă prelucrare de către țara respectivă

Interacțiunile dintre o țară și firmă se realizează vânzare / cumpărare.

Țara sau firma oferă bani pentru o cantitate dintr-o resursă deținută de cealaltă parte.

Ofertele la care are acces țara în momentul când firma este prezentă sunt:

● Cumpără: firma oferă o cantitate dintr-o resursă. Firma deține resursa în cantitatea pe care o oferă. Țara poate să accepte oferta sau nu.

● Vinde: firma cere o cantitate dintr-o resursă. Țara poate să dețină resursa în cantitatea cerută sau nu. Țara poate să accepte oferta sau nu.

Dacă o ofertă a fost acceptată, cantitatea efectivă ce va fi schimbată între cele 2 părți implicate depinde de banii celui care plătește (dacă nu poate plăti toată cantitatea, va primi o cantitate întreagă egală cu cât poate plăti).

În ceea ce privește interacțiunile țării cu firma, acestea sunt:

● Cumpără: doar resursele de consum / doar resursele de producție + consum / toate resursele

● Vinde: orice resurse / orice resurse mai puțin cele de consum / orice resurse mai puțin cele de producție + consum

Toate ofertele se realizează în ordinea în care au fost primite.

Prețul de bază al resurselor este același pentru toate țările. Prețul efectiv al unei resurse depinde de cantitatea de resursă deținută de țară astfel:

● Preț cumpărare = preț bază - 3 - [cantitate / 5] ( []  partea întreagă).

● Preț vânzare = preț bază - [cantitate / 5] ( []  partea întreagă).

Prețul efectiv va fi întotdeauna cel puțin egal cu 1 și va fi constant pe durata unei zile.

Fericirea țării:

● este număr întreg.

● scade pentru fiecare interacțiune de consum incompletă cu cantitatea lipsă (ex: țara vrea să consume 5 PESTE, dar deține doar 3 PESTE, deci pierde 2 fericire).

● crește cu 5 la sfârșitul fiecărei zile.

● la sfârșitul zilei, (după creșterea cu 5 puncte) dacă fericirea este mai mare strict decât 100, ea devine 100

● la sfârșitul zilei, (după creșterea cu 5 puncte) dacă fericirea este mai mică strict decât 50, ea devine 50

● fericirea (F) influențează proporțional cantitatea (C) de resurse / bani obținuți zilnic după formula [C * F / 100] ( []  partea întreagă).

În fiecare zi, pentru fiecare țară, se realizează următoarele acțiuni în această ordine:

1. Țara primește bani din taxe.

2. Dacă firma se află în țară, se rezolvă ofertele de cumpărare.

3. Se realizează toate producțiile.

4. Se realizează toate prelucrările.

5. Se realizează tot consumul.

6. Dacă firma se află în țară, se rezolvă ofertele de vânzare.

Înainte de prima zi firma deține B bani și nici o resursă.

Înainte de prima zi, fiecare țară deține 0 bani și nici o resursă. De asemenea, fiecare țară are fericirea 100.

Simulați primele D zile și afișați la sfârșitul fiecărei zile informațiile despre țări.

 

Date de intrare

N numărul de resurse

numele celor N resurse

prețul celor N

B numărul inițial de bani ai firmei.

K numărul de țări.

cele K țări sub forma:

Pe prima linie NUME_ȚARA BANI_TAXE C_CUMPARARE *** C_VANZARE ***, reprezentând numele țării, banii obținuți zilnic din taxe,comportamentul la cumpărare și comportamentul la vânzare.



*** C_CUMPARARE este unul dintre {CONSUM, PRODUCTIE, TOT} (cumpără doar resurse pentru consum, doar resurse pentru consum + prelucrare sau cumpără tot ce i se oferă).

*** C_VANZARE este unul dintre {ORICE, FARA_CONSUM, FARA_PRODUCTIE} (vinde orice, orice mai puțin resursele de consum, orice mai puțin resursele de consum + prelucrare).



Pe următoarea linie N_PRODUCTIE, numărul de interacțiuni de producție.

Urmează N_PRODUCȚIE linii ce descriu interacțiunile de producție pentru țară sub forma:

RESURSA_OBTINUTA CANTITATE_OBTINUTA

Pe următoarea linie N_PRELUCRARE, numărul de interacțiuni de prelucrare.

Urmează N_PRELUCRARE linii ce descriu interacțiunile de prelucrare pentru țară sub forma:

RESURSA_CONSUMATA CANTITATE_CONSUMATA RESURSA_OBTINUTA

CANTITATE_OBTINUTA

Pe următoarea linie N_CONSUM , numărul de interacțiuni de consum.

Urmează N_CONSUM linii ce descriu interacțiunile de consum pentru țară sub forma:

RESURSA_CONSUMATA CANTITATE_CONSUMATA

Pe următoarea linie D, numărul de zile ce trebuiesc simulate.

Se descriu în continuare cele D zile, sub forma:

Pe prima linie: NUME_TARA, țara în care se afla firma în ziua respectivă.

Pe următoarea N_CUMPARARE numărul de oferte de cumpărare ale firmei.

Urmează N_CUMPARARE linii ce descriu ofertele de cumpărare sub forma RESURSA CANTITATE

Pe următoarea N_VANZARE numărul de oferte de vanzare ale firmei.

Urmează N_VANZARE linii ce descriu ofertele de vânzare sub forma RESURSA CANTITATE

 

Date de ieșire

La finalul fiecărei zile, informații despre toate țările, în ordinea în care au fost date acestea, astfel:

pe prima linie, numele țarii, fericirea și numărul de bani pe care îi deține țara.

Pe următoarele linii, în ordine alfabetică a resurselor, numele resursei și cantitatea deținută doar dacă țara deține resursa respectivă (are cel puțin 1 cantitate din ea). Afișați un rând liber după fiecare țară. Forma afișării:

NUME_ȚARA FERICIRE_ȚARA BANI_ȚARA

RESURSA_DETINUTA_1 CANTITATE_RESURSA_1

…

RESURSA_DETINUTA_K CANTITATE_RESURSA_K




Problema Robot

Gigel a construit un mic robotel care traseaza forme geometrice simple, cerc, triunghi, patrat s.a.m.d. Fiind mandru de realizarea sa Gigel mai construieste inca un robot care deseneaza (umple) formele deja trasate.

In constructia robotului, Gigel a implementat 3 tipuri de precizie pentru primul robot: precizia 1 care deseneaza contur de minim 10 mm, precizie 2 care deseneaza contur de minim 5 mm si precizie 3 care deseneaza orice contur de orice precizie. Evident, precizia 3 va consuma cele mai multe resurse de calcul ale robotului deoarece robotul trebuie sa fie cat mai precis. Costul de calcul este grosime * biti_precizie * perimetru. 

In cazul robotului 2, treaba este mai simpla deoarece resursele de calcul alocate variaza dupa urmatoarea formula ( biti culoare * arie figura). Figurile pot fi desenate doar cu un singur tip de precizie si pot fi goale sau colorate.

Afisati crescator resursele de calcul utilizate pentru N figuri stiind resursele de calcul alocate pentru cele 3 precizii si resursele alocate pentru 1 bit de culoare/mm2.

Se vor utiliza functii virtuale/polimorfism.

În funcția main se va folosi o structură de date definită în STL în care se va stoca rezultatul. Tipul de date este double.

Nu se acroda punctaj pentru nerespectarea cerintei!

Date de intrare:

cost precizia 1

cost precizia 2

cost precizia 3

cost culoare

Pe urmatoarele N linii sunt figurile din desen cu atributele lor: grosime, tip precizie(1, 2, 3), Goala sau Colorata, tip figura, dimensiune figura (Raza pentru cerc, Latura pentru patrat, Baza si inaltime pentru Dreptunghi si triunghi).



Date de iesire:

resursele de calcul ordonate crescator





Problema Semnale1

Se consideră o clasă abstractă Semnal care permite adăugarea eșantioanleor în mod succesiv. Să se deriveze clasele DSP1 și DSP2 din clasa de bază. 
Să se implementeze metode de prelucrare în funcție de tipul semnalelor astfel:

- în DSP1 se va extrage numărul de treceri prin zero ale semnalului, iar în DSP se vor extrage numărul de maxime ale semnalului

- DSP1 va modifica semnalul astfel incat esantionul curent sa reprezinte media ultimelor 9 esantioane, iar DSP2 va determina cate maxime sunt mai mari decat tensiunea de prag (tensiunea de prag P va fi data de la tastatura)

- DSP1 va pragui semnalul (tensiunea de prag este egala cu 15) astfel încât orice esantion >=15 devine 1 si orice esantion <15 devine 0, iar în DSP2 maximele care sunt sub tensiunea de prag sunt inlocuite cu media aritmentica a valorilor vecine ( valoarea anterioara si valoarea urmatoare)

- DSP1 va subesantioneze semnalul cu factor de 5 (este pastrat fiecare esantion din 5 in 5 incepand cu primul) iar DSP2 va insera la inceputul si la finalul semnalului cate 5 esantioane de garda cu valoarea 0.

În funcția main se va folosi o structură de date definită în STL în care se va stoca esantioanele. Tipul de date este double.

Date de intrare:
tipul semnalului (1 sau 2)
tensiunea de prag P (se va lua în considerare doar daca este semnal de tipul 2)
esantioanele semnalului

Date de iesire:
semnalele rezultate in urma fiecarei operatii de prelucrare





Problema Semnale2

Se consideră o clasă abstractă Semnal care permite adăugarea eșantioanleor în mod succesiv. Să se deriveze clasele DSP1 și DSP2 din clasa de bază. 
Să se implementeze metode de prelucrare în funcție de tipul semnalelor astfel:

- în DSP1 se va extrage numărul de treceri prin zero ale semnalului, iar în DSP se vor extrage numărul de maxime ale semnalului

- DSP1 va modifica semnalul astfel incat esantionul curent sa reprezinte media ultimelor 9 esantioane, iar DSP2 va determina cate maxime sunt mai mari decat tensiunea de prag (tensiunea de prag P va fi data de la tastatura)

- DSP1 va pragui semnalul (tensiunea de prag este egala cu 15) astfel încât orice esantion >=15 devine 1 si orice esantion <15 devine 0, iar în DSP2 maximele care sunt sub tensiunea de prag sunt inlocuite cu media aritmentica a valorilor vecine ( valoarea anterioara si valoarea urmatoare)

- DSP1 va subesantioneze semnalul cu factor de 5 (este pastrat fiecare esantion din 5 in 5 incepand cu primul) iar DSP2 va insera la inceputul si la finalul semnalului cate 5 esantioane de garda cu valoarea 0.

Nu se admit rezolvări bazate pe vectori.

Date de intrare:
tipul semnalului (1 sau 2)
tensiunea de prag P (se va lua în considerare doar daca este semnal de tipul 2)
esantioanele semnalului

Date de iesire:
semnalele rezultate in urma fiecarei operatii de prelucrare
