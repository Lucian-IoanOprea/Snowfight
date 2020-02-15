// "Copyright[2018]<OPREA LUCIAN>"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

  struct spiridus {
    char nume[20];
    int hp;
    int x, y;
    int stamina;
    int dmg;
    int id;
    int elim;
    int drq;
  }
v[155];
int modulo(int a, int b) {
  if (a >= b)
    return a - b;
  else
    return b - a;
}
int form(int number, int k, int p) {
  return (((1 << k) - 1) & (number >> (p - 1)));
}

int cautare(int id, struct spiridus v[], int nrplayers) {
  int i;
  for (i = 0; i < nrplayers; i++)
    if (v[i].id == id) {
      return i;
    }
}
int cautare2(int x, int y, struct spiridus v[], int nrplayers) {
  int i;
  for (i = 0; i < nrplayers; i++)
    if (v[i].x == x && v[i].y == y) return i;
  return -1;
}

int valid(int x, int y, int x1, int y1, int r) {
  if (sqrt((modulo(x, x1)) * modulo(x, x1) + modulo(y, y1) * modulo(y, y1)) > r)
    return 0;
  return 1;
}

void fight(struct spiridus v[], int poz, int poz1, FILE * g) {
  if (v[poz].stamina >= v[poz1].stamina) {
    while (v[poz].hp > 0 && v[poz1].hp > 0) {
      v[poz1].hp -= v[poz].dmg;
      if (v[poz1].hp <= 0) break;
      v[poz].hp -= v[poz1].dmg;
    }
    if (v[poz].hp <= 0) {
      fprintf(g, "%s", v[poz1].nume);
      fprintf(g, " sent ");
      fprintf(g, "%s ", v[poz].nume);
      fprintf(g, "back home.\n");
      v[poz].x = -100;
      v[poz].y = -100;
      v[poz1].elim++;
      v[poz1].stamina += v[poz].stamina;
      return;
    }
    if (v[poz1].hp <= 0) {
      fprintf(g, "%s", v[poz].nume);
      fprintf(g, " sent ");
      fprintf(g, "%s ", v[poz1].nume);
      fprintf(g, "back home.\n");
      v[poz1].x = -100;
      v[poz1].y = -100;
      v[poz].elim++;
      v[poz].stamina += v[poz1].stamina;
      return;
    }
  } else {
    while (v[poz].hp > 0 && v[poz1].hp > 0) {
      v[poz].hp -= v[poz1].dmg;
      if (v[poz].hp <= 0) break;
      v[poz1].hp -= v[poz].dmg;
    }
    if (v[poz].hp <= 0) {
      fprintf(g, "%s", v[poz1].nume);
      fprintf(g, " sent ");
      fprintf(g, "%s ", v[poz].nume);
      fprintf(g, "back home.\n");
      v[poz].x = -100;
      v[poz].y = -100;
      v[poz1].elim++;
      v[poz1].stamina += v[poz].stamina;
      return;
    }
    if (v[poz1].hp <= 0) {
      fprintf(g, "%s", v[poz].nume);
      fprintf(g, " sent ");
      fprintf(g, "%s ", v[poz1].nume);
      fprintf(g, "back home.\n");
      v[poz1].x = -100;
      v[poz1].y = -100;
      v[poz].elim++;
      v[poz].stamina += v[poz1].stamina;
      return;
    }
  }
}

void move1(int a[][32], int b[][32], FILE * g, int raza, struct spiridus v[],
  int nrplayers, int poz, int x1, int y1, int copie[]) {
  int i, poz1, aux;
  if (v[poz].stamina >= modulo(a[x1][y1], a[v[poz].x][v[poz].y])) {
    if (valid(x1, y1, (2 * raza + 1) / 2, (2 * raza + 1) / 2, raza) != 1) {
      fprintf(g, "%s", v[poz].nume);
      fprintf(g, " fell off the glacier.\n");
      v[poz].x = -100;
      v[poz].y = -100;
      v[poz].hp = 0;
      copie[0]--;
      return;
    }
    v[poz].stamina -= modulo(a[x1][y1], a[v[poz].x][v[poz].y]);
    poz1 = cautare2(x1, y1, v, nrplayers);
    if (v[poz].dmg < b[x1][y1]) {
      aux = v[poz].dmg;
      v[poz].dmg = b[x1][y1];
      b[x1][y1] = aux;
    }
    if (poz1 != -1) {
      copie[0]--;
      fight(v, poz, poz1, g);
    }
    if (v[poz].hp > 0) {
      v[poz].x = x1;
      v[poz].y = y1;
    }
  }
}

void move(int a[][32], int b[][32], FILE * g, FILE * f, struct spiridus v[],
  int nrplayers, int raza, int copie[]) {
  int i, x1, y1, poz = 0, poz1 = 0, id;
  char s[20];
  fscanf(f, "%d", & id);
  fscanf(f, " %s", s);
  poz = cautare(id, v, nrplayers);
  if (v[poz].hp > 0 && poz != -1) {
    for (i = 0; i < strlen(s) && v[poz].hp > 0; i++) {
      if (s[i] == 'L') {
        x1 = v[poz].x;
        y1 = v[poz].y - 1;
        if (y1 < 0) {
          fprintf(g, "%s ", v[poz].nume);
          fprintf(g, "fell off the glacier.\n");
          v[poz].x = -100;
          v[poz].hp = 0;
          v[poz].y = -100;
          copie[0]--;
        } else {
          move1(a, b, g, raza, v, nrplayers, poz, x1, y1, copie);
        }

      } else if (s[i] == 'U') {
        x1 = v[poz].x - 1;
        y1 = v[poz].y;
        if (x1 < 0) {
          fprintf(g, "%s ", v[poz].nume);
          fprintf(g, "fell from the glacier.\n");
          v[poz].x = -100;
          v[poz].hp = 0;
          v[poz].y = -100;
          copie[0]--;
        } else {
          move1(a, b, g, raza, v, nrplayers, poz, x1, y1, copie);
        }
      } else if (s[i] == 'D') {
        x1 = v[poz].x + 1;
        y1 = v[poz].y;
        if (x1 >= 2 * raza + 1) {
          fprintf(g, "%s ", v[poz].nume);
          fprintf(g, "fell from the glacier.\n");
          v[poz].x = -100;
          v[poz].hp = 0;
          copie[0]--;
          v[poz].y = -100;
        } else {
          move1(a, b, g, raza, v, nrplayers, poz, x1, y1, copie);
        }
      } else if (s[i] == 'R') {
        x1 = v[poz].x;
        y1 = v[poz].y + 1;
        if (y1 >= 2 * raza + 1) {
          fprintf(g, "%s ", v[poz].nume);
          fprintf(g, "fell from the glacier.\n");
          v[poz].x = -100;
          v[poz].hp = 0;
          v[poz].y = -100;
          copie[0]--;
        } else {
          move1(a, b, g, raza, v, nrplayers, poz, x1, y1, copie);
        }
      }
    }
  }
}

void snowstorm(FILE * f, FILE * g, struct spiridus v[], int nrplayers,
  int copie[]) {
  int x, y, raza, damage, i;
  int number, poz;
  fscanf(f, "%d", & number);
  x = form(number, 8, 1);
  y = form(number, 8, 9);
  raza = form(number, 8, 17);
  damage = form(number, 8, 25);
  if (raza == 0) {
    poz = cautare2(x, y, v, nrplayers);
    v[poz].hp -= damage;
    if (v[poz].hp <= 0 && poz != -1) {
      fprintf(g, "%s ", v[poz].nume);
      fprintf(g, "was hit by snowstorm.\n");
      copie[0]--;
      v[poz].x = -100;
      v[poz].y = -100;
    }
  } else {
    for (i = 0; i < nrplayers; i++) {
      if (v[i].x >= 0 && v[i].y >= 0) {
        if (valid(v[i].x, v[i].y, x, y, raza) == 1) {
          v[i].hp -= damage;
          if (v[i].hp <= 0) {
            fprintf(g, "%s ", v[i].nume);
            fprintf(g, "was hit by snowstorm.\n");
            copie[0] = copie[0] - 1;
            v[poz].x = -100;
            v[poz].y = -100;
          }
        }
      }
    }
  }
}
void realocare(int a[][32], int raza) {
  int i, j;
  for (i = 1; i <= 2 * raza + 1; i++)
    for (j = 1; j <= 2 * raza + 1; j++) a[i - 1][j] = a[i][j];
  for (i = 0; i <= 2 * raza + 1; i++)
    for (j = 1; j <= 2 * raza + 1; j++) a[i][j - 1] = a[i][j];
}
void sortare(int vector[], int l, struct spiridus v[]) {
  int i, j, aux;
  int ok = 0;
  do {
    ok = 1;
    for (i = 0; i < l - 1; i++)
      if (v[vector[i]].id > v[vector[i + 1]].id) {
        aux = vector[i];
        vector[i] = vector[i + 1];
        vector[i + 1] = aux;
        ok = 0;
      }
  } while (ok != 1);
}
void meltdown(FILE * f, FILE * g, int a[][32], int b[][32], struct spiridus v[],
  int nrplayers, int raza, int copie[]) {
  int i, adaug, poz, vector[155], l = 0;
  fscanf(f, "%d", & adaug);
  raza++;
  for (i = 0; i < nrplayers; ++i) {
    if (valid(v[i].x, v[i].y, (2 * raza + 1) / 2, (2 * raza + 1) / 2,
        raza - 1) != 1 && v[i].x >= 0 && v[i].y >= 0 && v[i].hp > 0) {
      vector[l] = i;
      l++;

    } else if (v[i].x >= 0 && v[i].y >= 0) {
      v[i].stamina += adaug;
      v[i].x--;
      v[i].y--;
    }
  }
  sortare(vector, l, v);
  for (i = 0; i < l; i++) {
    fprintf(g, "%s", v[vector[i]].nume);
    fprintf(g, " got wet because of global warming.\n");
    copie[0]--;
    v[vector[i]].hp = 0;
    v[vector[i]].x = -100;
    v[vector[i]].y = -100;
  }
  raza--;
  realocare(a, raza);
  realocare(b, raza);
}
void score(FILE * g, struct spiridus v[], int nrplayers) {
  int i, j, ok = 0;
  struct spiridus aux;
  for (i = 0; i < nrplayers; i++) {
    if (v[i].hp <= 0)
      v[i].drq = 0;
    else
      v[i].drq = 1;
  }
  do {
    ok = 1;
    for (i = 0; i < nrplayers - 1; i++)
      if ((v[i].drq > v[i + 1].drq) || (v[i].drq == v[i + 1].drq &&
        v[i].elim > v[i + 1].elim) || (v[i].drq == v[i + 1].drq  &&
        v[i].elim == v[i + 1].elim  && strcmp(v[i].nume, v[i + 1].nume) < 0)) {
        aux = v[i];
        v[i] = v[i + 1];
        v[i + 1] = aux;
        ok = 0;
      }
  } while (ok != 1);

  fprintf(g, "SCOREBOARD:\n");
  for (i = nrplayers - 1; i >= 0; i--) {
    fprintf(g, "%s\t", v[i].nume);
    if (v[i].drq == 1)
      fprintf(g, "DRY\t");
    else
      fprintf(g, "WET\t");
    fprintf(g, "%d\n", v[i].elim);
  }
}
void castigator(FILE * g, struct spiridus v[], int nrplayers) {
  int i;
  for (i = 0; i < nrplayers; i++)
    if (v[i].hp > 0) {
      fprintf(g, "%s", v[i].nume);
      fprintf(g, " has won.\n");
      break;
    }
}
void citire(int a[][32], int b[][32], int raza, int nrplayers,
  struct spiridus v[], FILE * f, FILE * g) {
  int i, j, copie[1] = {
    0
  };
  char comanda[20];
  copie[0] = nrplayers;
  for (i = 0; i < nrplayers; i++) {
    fscanf(f, "%s%d%d%d%d",  v[i].nume, & v[i].x, & v[i].y, & v[i].hp, &
      v[i].stamina);
    if (valid(v[i].x, v[i].y, (2 * raza + 1) / 2, (2 * raza + 1) / 2, raza) !=
      1) {
      fprintf(g, "%s", v[i].nume);
      fprintf(g, " has missed the glacier.\n");
      copie[0] = copie[0] - 1;
      v[i].x = -100;
      v[i].y = -100;
      v[i].hp = 0;
    }
    if (v[i].x >= 0 && v[i].y >= 0) {
      v[i].id = i;
      v[i].dmg = b[v[i].x][v[i].y];
      b[v[i].x][v[i].y] = 0;
      v[i].elim = 0;
    }
  }
  if (copie[0] == 1) {
    castigator(g, v, nrplayers);
    return;
  }

  while (fscanf(f, "%s", comanda) != EOF) {
    if (strcmp(comanda, "MOVE") == 0) {
      move(a, b, g, f, v, nrplayers, raza, copie);
    }
    if (strcmp(comanda, "SNOWSTORM") == 0) snowstorm(f, g, v, nrplayers, copie);
    if (strcmp(comanda, "MELTDOWN") == 0) {
      raza--;
      meltdown(f, g, a, b, v, nrplayers, raza, copie);
    }
    if (strcmp(comanda, "PRINT_SCOREBOARD") == 0) {
      score(g, v, nrplayers);
    }
    if (copie[0] == 1) {
      castigator(g, v, nrplayers);
      return;
    }
  }
  if (copie[0] == 1) {
    castigator(g, v, nrplayers);
    return;
  }
}
int main() {
  FILE * f, * g;
  f = fopen("snowfight.in", "r");
  g = fopen("snowfight.out", "w");
  int raza, nrplayers;
  int a[32][32], b[32][32], i, n, j;
  fscanf(f, "%d%d", & raza, & nrplayers);
  n = 2 * raza + 1;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) fscanf(f, "%d%d", & a[i][j], & b[i][j]);
  citire(a, b, raza, nrplayers, v, f, g);
  return 0;
}