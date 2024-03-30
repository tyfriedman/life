#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define sz 40

void iboard(char [][sz]); // function prototypes
void display(char [][sz]);
void inputs(char [][sz]);
void run(char [][sz]);


int main(int argc, char *argi[]) {
   char board[sz][sz]; // declare the size of the board
   iboard(board); // create a blank board
   if (argc == 1) {
      inputs(board); // interactive mode - take user inputs
   } else if (argc == 2) { // enter batch mode
      FILE *fp = fopen(argi[1], "r"); // open file
      if (fp == NULL) { // checks if the file has anything in it
         printf("Not a valid file\n");
         return 1;
      }
      int len = 30;
      char str[len];
      int int1;
      int int2;
      char char1;
      while (1) { // get all of the inputs of the file line by line
         if (feof(fp)) break;
         fgets(str, len, fp);
         sscanf(str, "%c %d %d", &char1, &int1, &int2);
         if (char1 == 'a') {
            board[int1][int2] = 'X';
         } else break;
         printf("2\n");
      }
      while (1) {  // run the program indefinitely
         display(board);
         usleep(100000);
         run(board);
      }
   } else { // if there are too many inupts, terminate
      printf("Too many inputs. Program terminated.\n");
      return 1;
   }
   

   return 0;
}

void display(char board[][sz]) {
   for (int j = 0; j < sz+2; j++) printf("_"); // top of board
   printf("\n");
   for (int i = 0; i < sz; i++) { // middle portion of board
      printf("|");
      for (int j = 0; j < sz; j++) {
         printf("%c", board[i][j]);
      }
      printf("|\n");
   }
   for (int j = 0; j < sz+2; j++) printf("-"); // bottom of board
   printf("\n");
}

void iboard(char board[][sz]) {
   system("clear");
   for (int i = 0; i < sz; i++) { // iterate rows of board
      for (int j = 0; j < sz; j++) { // iterate columns of board
         board[i][j] = ' ';
      }
   }
}

void inputs(char board[][sz]) {
   char char1; // declare inputs
   int int1;
   int int2;
   int quit = 0;
   while (quit == 0) { // run until user quits
      display(board);
      printf("COMMAND: ");
      scanf("%c", &char1);
      if (char1 == 'a')  { // add X at input
         scanf("%d %d", &int1, &int2);
         board[int1-1][int2-1] = 'X';
      } else if (char1 == 'r') { // set removed spot to empty
         scanf("%d %d", &int1, &int2);
         board[int1-1][int2-1] = ' ';
      } else if (char1 == 'n') { // run the game once
         run(board);
      } else if (char1 == 'p') {
         while (1) {
            run(board);
            display(board);
            usleep(100000);
         }
      } else if (char1 == 'q') {
         break;
      }
      printf("\n");
   }
}

void run(char board[][sz]) {
   char nBoard[sz][sz]; // defines the intermediate board
   iboard(nBoard); // makes the intermediate board blank
   int num = 0;
   for (int i = 0; i < sz; i++) { // iterates through every square on the board
      for (int j = 0; j < sz; j++) { 
         if ((i-1 >= 0) && (j-1 >= 0)) {
            if (board[i-1][j-1] == 'X') num++; // checks each individual border square if it is a part of the board
         } 
         if ((i-1 >= 0)) {
            if (board[i-1][j] == 'X') num++;
         }
         if ((i-1 >= 0) && (j+1 < sz)) {
            if (board[i-1][j+1] == 'X') num++;
         }
         if (j-1 >= 0) {
            if (board[i][j-1] == 'X') num++;
         }
         if (j+1 < sz) {
            if (board[i][j+1] == 'X') num++;
         }
         if ((i+1 < sz) && (j-1 >= 0)) {
            if (board[i+1][j-1] == 'X') num++;
         }
         if (i+1 < sz) {
            if (board[i+1][j] == 'X') num++;
         }
         if ((i+1 < sz) && (j+1 < sz)) {
            if (board[i+1][j+1] == 'X') num++;
         }
         
         if (board[i][j] == 'X') {
            if ((num == 2) || (num == 3)) nBoard[i][j] = 'X';
         } else {
            if (num == 3) nBoard[i][j] = 'X';
         }
         num = 0;
      }
   } // updates the real board to be the same as the intermediate board
   for (int i = 1; i < sz+1; i++) {
      for (int j = 1; j < sz+1; j++) {
         board[i][j] = nBoard[i][j];
      }
   }
}
