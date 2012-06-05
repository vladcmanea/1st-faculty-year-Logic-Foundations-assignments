/*

 Anul I
 Grupa 6A
 Student Vlad Manea

 ------------------------------------------------------

 Realizat in Rhide DJGPP

 ------------------------------------------------------

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

*/

#include <stdio.h>
#include <conio.h>
#define nmax 128

int xj, yj, xc, yc, N, M;

int dx[] = {0, 1, 0, -1, 0};

int dy[] = {0, 0, 1, 0, -1};

int iswumpus[nmax][nmax], ishole[nmax][nmax];

int smell[nmax][nmax], winds[nmax][nmax];

int viz[nmax][nmax], A[nmax][nmax];

void update(int x, int y)
{
  int i, j;

  clrscr();

  printf("+");
  for (j = 1; j <= N; printf("------+"), ++j);

  for (i = 1; i <= N; ++i)
  {
    printf("\n|");
    for (j = 1; j <= N; ++j)
    {
      if (smell[i][j]) printf("m"); else printf(" ");
      printf("    ");
      if (i == xc && j == yc) printf("c"); else printf(" ");
      printf("|");
    }

    printf("\n|");
    for (j = 1; j <= N; ++j)
    {
      printf("  ");
      if (viz[i][j])
        printf("vi");
      else
      {
        if (iswumpus[i][j] == 1) printf("e");
        else if (iswumpus[i][j] == 0) printf("?");
        else printf("!");
        printf("W");
      }
        
      printf("  |");
    }

    printf("\n|");
    for (j = 1; j <= N; ++j)
    {
      printf("  ");
      if (viz[i][j])
        printf("zi");
      else
      {
        if (ishole[i][j] == 1) printf("e");
        else if (ishole[i][j] == 0) printf("?");
        else printf("!");
        printf("P");
      }
      printf("  |");
    }

    printf("\n|");
    for (j = 1; j <= N; ++j)
    {
      if (i == x && j == y) printf("j"); else printf(" ");
      printf("    ");
      if (winds[i][j]) printf("v"); else printf(" ");
      printf("|");
    }

    printf("\n+");
    for (j = 1; j <= N; printf("------+"), ++j);
  }

  getch();
}

void walk(int x, int y)
{
  int i, j, k, da, nu;

  // am vizitat pozitia curenta
  viz[x][y] = 1;

  // vad cum mai pot actualiza pozitiile vecine
  if (!smell[x][y])
    for (k = 0; k < 5; iswumpus[x+dx[k]][y+dy[k]] = -1, ++k);
  else
  {
    for (da = nu = 0, k = 1; k < 5; ++k)
    {
      da += (iswumpus[x+dx[k]][y+dy[k]] == 1);
      nu += (iswumpus[x+dx[k]][y+dy[k]] == -1);
    }

    for (k = 1; nu == 3 && da == 0 && k < 5; ++k)
      if (iswumpus[x+dx[k]][y+dy[k]] == 0)
        iswumpus[x+dx[k]][y+dy[k]] = 1;
  }

  if (!winds[x][y])
    for (k = 0; k < 5; ishole[x+dx[k]][y+dy[k]] = -1, ++k);
  else
  {
    for (da = nu = 0, k = 1; k < 5; ++k)
    {
      da += (ishole[x+dx[k]][y+dy[k]] == 1);
      nu += (ishole[x+dx[k]][y+dy[k]] == -1);
    }

    for (k = 1; nu == 3 && da == 0 && k < 5; ++k)
      if (ishole[x+dx[k]][y+dy[k]] == 0)
        ishole[x+dx[k]][y+dy[k]] = 1;
  }

  update(x, y);

  for (k = 1; k < 5 && !viz[xc][yc]; ++k)
    if (!viz[x+dx[k]][y+dy[k]] && ishole[x+dx[k]][y+dy[k]] == -1 && iswumpus[x+dx[k]][y+dy[k]] == -1)
    {
      walk(x+dx[k], y+dy[k]);

      if (!viz[xc][yc]) update(x, y);
    }
}

int main()
{
  int i, j, k;

  FILE * F = fopen ("wumpus.in","r");
  FILE * G = fopen ("wumpus.out", "w");
        
  fscanf(F, "%d%d", &N, &M);

  // umplu matricea si marchez pozitiile alaturate
  for (i = 1; i <= N; ++i)
    for (j = 1; j <= M; ++j)
    {
      fscanf(F, "%d", &A[i][j]);
      
      for (k = 0; k < 5 && (A[i][j] == 1 || A[i][j] == 3); smell[i+dx[k]][j+dy[k]] = 1, ++k);
      for (k = 0; k < 5 && (A[i][j] == 2 || A[i][j] == 3); winds[i+dx[k]][j+dy[k]] = 1, ++k);
    }

  fscanf(F, "%d%d%d%d", &xj, &yj, &xc, &yc);

  // bordez matricea cu elemente sigure
  for (i = 0; i <= N+1; viz[i][M+1] = viz[i][0] = iswumpus[i][M+1] = iswumpus[i][0] = ishole[i][M+1] = ishole[i][0] = -1, ++i);
  for (j = 0; j <= M+1; viz[0][j] = viz[N+1][j] = iswumpus[0][j] = iswumpus[N+1][j] = ishole[0][j] = ishole[N+1][j] = -1, ++j);

  if (A[xc][yc] || A[xj][yj] || xc==xj&&yc==yj)
  {
    clrscr();

    fprintf(G, "EROARE: pozitiile initiala si finala trebuie sa fie libere si diferite\n");
    printf("EROARE: pozitiile initiala si finala trebuie sa fie libere si diferite\n");

    getch();
  }
  else
  {
    walk(xj, yj);

  if (viz[xc][yc])
  {
    fprintf(G, "DA: piratul a gasit comoara si poate iesi la pensie\n");
    printf("\nDA: piratul a gasit comoara si poate iesi la pensie\n");

    getch();
  }
  else
  {
    fprintf(G, "NU: piratul nu a gasit comoara dar poate juca intr-un film de Oscar\n");
    printf("\nNU: piratul nu a gasit comoara dar poate juca intr-un film de Oscar\n");

    getch();
  }
  }

  return 0;
}
    

    
    

    

    

    

    
          
      
          

      
