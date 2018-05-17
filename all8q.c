#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(const int *board) {
  int i,j,k;
  static int n=1;

  printf("Board %d:\n",n);
  ++n;
  for(i=1;i<=8;i++) {
    for(k=1;k<=8;k++) printf("+---"); printf("+\n");
    for(j=1;j<=8;j++)
      printf("| %c ",board[j]==i ? 'Q' : ' ');
    printf("|\n");
  }
  for(k=1;k<=8;k++) printf("+---"); printf("+\n\n");
}

int solve8q() {
  int qrow[9]  = {0,0,0,0,0,0,0,0,0}; // [0] ignored, using indexes 1..8 and values 1..8 for readability.
  int col = 1;
  int i,j,bad;

  while(1) {

    if (qrow[col]==8) {
      if (col>1) { 
        /* tried every position on this column, didn't work. backtrack to previous column */
        qrow[col]=0;
        col--; 
        continue;  
      } else {
        /* tried every position, no column to backtrack to */
        return 0 /* done */;
      }
    } else {
      qrow[col]++;
    }

    /* check if queens attack each other */
    
    bad = 0;
    for(i=1;i<=7 && !bad;i++) {
      for(j=i+1;j<=8 && !bad;j++) {
        if (qrow[i]!=0 && qrow[i]==qrow[j]) bad=1;
        if (qrow[i]!=0 && qrow[j]!=0 && abs(i-j)==abs(qrow[i]-qrow[j])) bad=1;
      }
    }
    
    if (bad) continue; // queens touch, cannot proceed to next column(s)
    if (col==8) {
      // solved, print solution, clear this row, back up to previous column
      print(qrow);
      qrow[col]=0;
      --col;
      continue;
    }
    ++col; // no queens touch, proceed to fill next column

  }

  return 0;
}

int main() {

  solve8q();

  return 0;
}
