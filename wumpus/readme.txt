
 Fisierul de intrare "wumpus.in" trebuie sa contina:

 N = numarul de linii
 M = numarul de coloane

 NXM valori cu semnificatia:
 0 = nimic
 1 = wumpus
 2 = prapastie

 xj = linia de pe care se porneste cautarea
 yj = coloana de pe care se porneste cautarea

 xc = linia pe care se gaseste comoara
 yc = coloana pe care se gaseste comoara

 Este indicat ca xj, yj, xc, yc sa nu determine puncte
 care sa se suprapuna intre ele sau cu primejdii

 ------------------------------------------------------

 Structura unui patratel

 +------+
 |s    c|
 |  ?W  |
 |  ?P  |
 |j    v|
 +------+

 s apare in patratelele mirositoare
 c apare in patratelul comorii

 W este statusul wumpus, este prefixat:
   - de e pentru existenta,
   - de ! pentru inexistenta,
   - de ? pentru indecizie

 P este statusul prapastie, este prefixat la fel ca W

 Daca patratelul este vizitat, statusul wumpus/prapastie
 va fi inlocuit de cuvantul vi/zi

 j apare in patratelul in care se afla piratul Jack
 v apare in patratelele cu vant

 ------------------------------------------------------

 Situatia piratului este salvata si intr-un
 fisier "wumpus.out", care va fi trimis amiralului
