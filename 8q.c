#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solve8q() {
  int qrow[9]  = {0,0,0,0,0,0,0,0,0}; // [0] ignored, using indexes 1..8 and values 1..8 used for readability.
  int qlast[9] = {0,0,0,0,0,0,0,0,0}; // last row attempted for each column
  int col = 1;
  int i,j,k,bad;

  while(1) {

    printf("col=%d qrow=[%d,%d,%d,%d,%d,%d,%d,%d]\n",col,
           qrow[1],qrow[2],qrow[3],qrow[4],
           qrow[5],qrow[6],qrow[7],qrow[8]);

    if (qlast[col]==8) {
      if (col>1) { 
        /* tried every position on this column, didn't work. backtrack to previous column */
        qlast[col]=0;
        qrow[col]=0;
        col--; 
        continue;  
      } else {
        /* tried every position, no column to backtrack to */
        printf("failed.\n");
        return -1 /* failed */;
      }
    } else {
      qrow[col] = ++qlast[col];
    }

    /* check whether each queen pair attacks one another */
    
    bad = 0;
    for(i=1;i<=7 && !bad;i++) {
      for(j=i+1;j<=8 &&!bad;j++) {
        if (qrow[i]!=0 && qrow[i]==qrow[j]) bad=1;
        if (qrow[i]!=0 && qrow[j]!=0 && abs(i-j)==abs(qrow[i]-qrow[j])) bad=1;
      }
    }
    
    if (bad) continue; // queens touch, cannot proceed to next column(s)
    if (col==8) break; // 8 queens on the board, none touch each other: solved
    ++col; // no queens touch, proceed to fill next column

  }

  for(i=1;i<=8;i++) {
    for(k=1;k<=8;k++) printf("+---"); printf("+\n");
    for(j=1;j<=8;j++)
      printf("| %c ",qrow[j]==i ? 'Q' : ' ');
    printf("|\n");
  }
  for(k=1;k<=8;k++) printf("+---"); printf("+\n");

  return 0;
}

int main() {

  solve8q();

  return 0;
}
