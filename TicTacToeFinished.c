//  main.c
//  TicTacToe
//
//  Created by Jacob Tumak, Himanshi Kaushik and Jule Voskamp on 2022-11-14.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
 
/* •–––Function ProtoTypes––––• */
char Menu(void);
char Menu2(void);
int PlayGame(int[]);
int UserTurn(int[]);
void BotsTurn(int, int[]);
void SetGrid(int[]);
void DisplayGrid(int[]);
int ThreeInARow(int[]);
void Player1Wins(int[]);
void Player2Wins(int[]);
void GameIsTie(int[]);
int IsValidEntry(int, int[]);
int CheckForTie(int []);
/* •–––––––––––••••–––––––––––• */
 
 
 
/* •––––––––––\/–––––––––––MAIN––––––––––\/–––––––––––• */
 
//displays menus and executes game as long as user does not quit
 
int main(int argc, const char * argv[]) {
   int grid[8];
   int result = 0; //returns -1 and quits the game if user enters q, play keeps going if result is 0
   int userInput;
   int count = 0; //counts numbers of games played
   char q = 'q';
   
   do{
       
       if(count == 0){                          //introduction for game 1
           userInput = Menu();}
       else{
           userInput = Menu2();}                //introduction for game 2
       if(userInput == q || result == -1)
           break;
       
       ++count;
       
       do{
           userInput = Menu2();                 //new introduction if player quits game
           if(userInput == q)
               break;
           
           result = PlayGame(grid);             //play game
       
           if(result == -1){
               return 0;
           }
           
       }while (result == 0);                    //ends game if user quits game
   }while(userInput != q);
   
   return 0;
}
/* •––––––––––/\–––––––––––MAIN––––––––––/\–––––––––––• */
 
 
 
/* •–––––––––––––––––––∫∫∫∫∫––FUNCTIONS––∫∫∫∫∫––––––––––––––––––• */
 
/* •–––––––––––––––––––––DISPLAYGRID––––––––––––––––––––• */
 
// Displays Grid including numbers
 
void DisplayGrid(int grid[]){
   printf("%c | %c | %c\n–––––––––\n%c | %c | %c\n–––––––––\n%c | %c | %c\n\n", grid[0], grid[1], grid[2], grid[3], grid[4], grid[5], grid[6], grid[7], grid[8]);
}
 
 
/* •–––––––––––––––––––––SETGRID––––––––––––––––––––• */
 
//Sets and Resets all #'s in grid to their initial value in order to reset the board
 
void SetGrid(int grid []){
   int i;
   
   for(i = 0; i < 9; ++i){
       grid[i] = i + 49;
   }
}
 
/* •–––––––––––––––––––––USERTURN––––––––––––––––––––• */
 
//gets user input. if the input is a valid spot, the cooridinated spot on the board is assigned with "X"
 
int UserTurn(int grid[]){
   int userInput;
   
   printf("Type the number of the box you want to take:");
   scanf("%d", &userInput);
   printf("\n");
    
   if(userInput == 0){          //quits game if user enters 0
           return -1;
   }
   
   else if (grid[userInput - 1] > 48 && grid[userInput - 1] < 58){
        grid[userInput - 1] = 'X';                                      //enters X for valid user Input
   }
   else{
       
           if (IsValidEntry(userInput, grid) == 2) {                    //Message when user Input is not in rnage 1-9
           printf("\nInvalid Entry. Please Try Again\n\n");
            
           }
           else if (IsValidEntry(userInput, grid) == 1) {               //Message when spot was taken before
               printf("\nThis spot is taken. Please choose a different spot.\n\n");
               
           }
           DisplayGrid(grid);                                           //repeats entry for invalid input
           printf("Type the number of the box you want to take:\n");
           scanf("%d", &userInput);
           
          grid[userInput - 1] = 'X';                                    //enters X for new chosen spot
   }
   
       
   return userInput;
}
 
 
/* •–––––––––––––––––––––BOTSTURN––––––––––––––––––––• */
 
//generates a random place the bot places its turn
 
void BotsTurn(int userTurn, int grid[]){
   int bot;
   
   if(userTurn >= 0){
       
       
   srand(time(NULL));                   //random number
   
   do{
       bot = rand();                    //puts random number into range 1-9
       if(bot > 9){
           bot = bot % 10;
       }
   }while(bot + 48 != grid[bot-1]);
   
   grid[bot - 1] = 'O';                 // enters O for bots turn
   }
}
 
 
/* •–––––––––––––––––––––THREEINAROW––––––––––––––––––––• */
 
//checks if the condition of three taken spots is achieved of either bot or user
 
int ThreeInARow(int grid[]){
   int check;
   int i;
   
   check = 0;
 
    if(      (grid[0] == 'X' && grid[1] == 'X' && grid[2] == 'X')          //case user wins
          || (grid[3] == 'X' && grid[4] == 'X' && grid[5] == 'X')
          || (grid[6] == 'X' && grid[7] == 'X' && grid[8] == 'X')
          || (grid[0] == 'X' && grid[3] == 'X' && grid[6] == 'X')
          || (grid[1] == 'X' && grid[4] == 'X' && grid[7] == 'X')
          || (grid[2] == 'X' && grid[5] == 'X' && grid[8] == 'X')
          || (grid[0] == 'X' && grid[4] == 'X' && grid[8] == 'X')
          || (grid[2] == 'X' && grid[4] == 'X' && grid[6] == 'X'))
      {

       check = 1;
   }
   else if(   (grid[0] == 'O' && grid[1] == 'O' && grid[2] == 'O')          //case bot wins
           || (grid[3] == 'O' && grid[4] == 'O' && grid[5] == 'O')
           || (grid[6] == 'O' && grid[7] == 'O' && grid[8] == 'O')
           || (grid[0] == 'O' && grid[3] == 'O' && grid[6] == 'O')
           || (grid[1] == 'O' && grid[4] == 'O' && grid[7] == 'O')
           || (grid[2] == 'O' && grid[5] == 'O' && grid[8] == 'O')
           || (grid[0] == 'O' && grid[4] == 'O' && grid[8] == 'O')
           || (grid[2] == 'O' && grid[4] == 'O' && grid[6] == 'O'))
   {
       check = 2;
   }
   else if (CheckForTie(grid) == true){                                     //case game ends in tie
       check = 3;
   }
   for(i = 0; i < 8; ++i){                                                  //case user quits game
       if(grid[i] == 'q'){
           check = 4;
       }
   }
       return check;
   
   
}
 
/* •–––––––––––––––––––––PLAYGAME––––––––––––––––––––• */
 
//executes the functions for playing the game and states the winner of the game
//also returns error message if an error in the game occurrs
 
int PlayGame(int grid[]){
   int winner = 0;
   int quit = -1;
   int playerSpot;
   int checker;
   //int botSpot;
   
   SetGrid(grid);
    
   //following do - while loop runs until a player wins, a tie occurs or the user quits
   do{
   checker = ThreeInARow(grid);     //Checks Score before round commences
       
   DisplayGrid(grid);
   playerSpot = UserTurn(grid);     //enters users input
       
   checker = ThreeInARow(grid);     //checks for winning score
       
   if(checker == 0)
   BotsTurn(playerSpot, grid);      //enters bots input
    checker = ThreeInARow(grid);
   } while (checker == 0);
   
   
   switch(checker){
       case 1:                       //User wins
           winner = 1;
           Player1Wins(grid);
           return winner;
           
       case 2:                       //Bot wins
           winner = 2;
           Player2Wins(grid);
           return winner;
           
       case 3:                       //Game ends in a tie
           winner = 3;
           GameIsTie(grid);
           return winner;
           
       case 4:                      //User quits game
           return quit;
   }
    
    return 0;
}
 
/* •–––––––––––––––––––––PLAYER1WINS––––––––––––––––––––• */
 
//states win of the user and shows the final grid, asks user for new game
 
void Player1Wins(int grid[]){
   printf("\nCongratulations! You beat the bot!\n\n");
   DisplayGrid(grid);
   printf("\n");
   printf("Press \"p\" to play again or press \"q\" to quit the game\n");
}
 
/* •–––––––––––––––––––––PLAYER2WINS––––––––––––––––––––• */
 
// states win of the bot and shows the final grid, asks user for new game
 
void Player2Wins(int grid[]){
   printf("\nYikes, you need some practice... The bot won O_O\n\n");
   DisplayGrid(grid);
   printf("\n");
   printf("Press \"p\" to play again or press \"q\" to quit the game\n");
}
/*-----------------------GAMEISTIE---------------------------*/  //-----> EDIT
 
// states that the game ended in a tie
 
void GameIsTie(int grid[]) {
    printf("\nWell, both of you won ... or lost ^_^\n\n");
    DisplayGrid(grid);
    printf("\n");
    printf("Press \"p\" to play again or press \"q\" to quit the game\n");
}
 
 
/* •––––––––––––––––––––––––Menu–––––––––––––––––––––––• */
 
//introduces the first game, greets the user and asks whether user wants to play or quit
 
char Menu(void){
   char menuInput;
   
   printf("Welcome to Tic-Tac_Toe!\n\n");
   printf("Press:\n p - Play\n q - Quit\n\n");
   
   scanf("%c", &menuInput);
   
   printf("\n");
   
   return menuInput;
}
 
/* •––––––––––––––––––––––––MENU2–––––––––––––––––––––––• */
 
//displays the menu for another game, does not greet the user again
 
char Menu2(void){
   char menuInput;
   
   scanf("%c", &menuInput);
   
   printf("\n");
   
   return menuInput;
}
 
/* •––––––––––––––––––––––––ISVALIDENTRY–––––––––––––––––––––––• */
 
// checks if the entered character is a valid character in the range of 1 to 9 and the spot is availbale
 
int IsValidEntry(int input, int grid[]){
   int isValidNum = 0;   //valid number
   int isInvalidSpot = 1; //invalid digit, spot is already taken
   int isInvalid = 2;    //invalid character, not a in range of 1 to 9
   
   if(grid[input - 1] > 48 && grid[input - 1] < 58)
       return isValidNum;
   else if(grid[input - 1] == 'O' || grid[input - 1] == 'X')
       return isInvalidSpot;
    else
        return isInvalid;
   
}
 

/* •––––––––––––––––––––––––CheckForTie–––––––––––––––––––––––• */

// checks if the game ends in a tie and returns true if it does
    
   int CheckForTie(int grid[]){
       int i;
       int count = 0;
       
       for(i = 0; i < 9; ++i){
           if(grid[i] == 'O' || grid[i] == 'X')
               ++count;                             //number of symbols entered
       }
       
       if(count == i)                               //number of symbols equals spots in grid results in tie, no one won
           return true;
       else
           return false;
   }
    
   /* •––––––––––––––––––––––––––––––––––––––––––––––––––––• */

