#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions
#include "TicTacToe.h"
#include <string.h>
// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
   HAL_IncTick(); // tell HAL that a new tick has happened
   // we can do other things in here too if we need to, but be careful
}
void piece_location(char board[9], char charturn, int piece_value) {
   board[piece_value] = charturn;
}
bool fresh(){
   if ((!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4))||(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10))||(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))||(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15))||(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2))||(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6))||(!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11))||(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6))||(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)))
     {
       return false;
     }
   else {
       return true;
   }
}
bool check_hor(char board[], char charturn) {
for(int k=0; k<7; k = k+3){
    if((board[k] == board[k+1])&&(board[k] == board[k+2])&&(board[k] == charturn)){
        return true;
    }
}
return false;
}
bool check_ver(char board[], char charturn) {
for(int k=0; k<3; ++k){
    if((board[k] == board[k+3])&&(board[k] == board[k+6])&&(board[k] == charturn)){
        return true;
    }
}
return false;
}
bool check_diag(char board[], char charturn) {
    if(((board[0] == board[4])&&(board[0] == board[8]))||((board[2] == board[4])&&(board[2] == board[6]))) {
   
     if(board[4] == charturn){
        return true;
     } else {
       return false;
       }
    } else {
   return false;
    }
}
int main(void) {
    HAL_Init(); // initialize the Hardware Abstraction Layer
   // Peripherals (including GPIOs) are disabled by default to save power, so we
   // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.
   __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
   __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
   __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)
   // initialize the pins to be input, output, alternate function, etc...
   InitializePin(GPIOC, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //WHITE
   InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //BLACK
   InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //BEIGE
   InitializePin(GPIOB, GPIO_PIN_15, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //PURPLE
   InitializePin(GPIOB, GPIO_PIN_2, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //BLUE
   InitializePin(GPIOB, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //GREEN
   InitializePin(GPIOA, GPIO_PIN_11, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //YELLOW
   InitializePin(GPIOC, GPIO_PIN_6, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //ORANGE
   InitializePin(GPIOC, GPIO_PIN_8, GPIO_MODE_INPUT, GPIO_PULLUP, 1); //RED
   InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 1);
   // set up for serial communication to the host computer
   // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)
   SerialSetup(9600);
   char board[9]; //right way?
   char turnchar = '0';
   int piece_value = 0;
   int c = 0;
   int counter_one = 0;
   int counter_two = 0;
   int t = 1;
   char oldboard[9];
   bool game_finished = false;
 SerialPuts("\n Having X always start first, and player one in the first round, \n alternatingly place X and O pieces on the wooden board boxes. \n To assure the move has registered, look for “play registered” to be printed on the serial monitor with every piece placement. \n When a win has occurred, (3 of the same symbol pieces forming a vertical, horizontal, or diagonal line) an LED will flash blue. \n In order to restart the game, all pieces must be removed off the board. \n Once three points have been acquired for one player, the final winner will be outputted on the serial monitor.");
   
for(int j=3; true ; ++j){
     board[0] = 0;
     board[1] = 0;
     board[2] = 0;
     board[3] = 0;
     board[4] = 0;
     board[5] = 0;
     board[6] = 0;
     board[7] = 0;
     board[8] = 0;
     oldboard[0] = 'e';
     oldboard[1] = 'e';
     oldboard[2] = 'e';
     oldboard[3] = 'e';
     oldboard[4] = 'e';
     oldboard[5] = 'e';
     oldboard[6] = 'e';
     oldboard[7] = 'e';
     oldboard[8] = 'e';
     t = 1;
     if(j%2 != 0) { //j is odd,
       c = 3;
       } else { //j is even
       c = 4;
       //This way, the starting character would alternate between 'x' and 'o' in the next internal for loop.
       } 
     while(true){
         fresh();
         if(fresh() == true){
             HAL_Delay(8000);
             break;
         }
     }
     game_finished = false;
   
     while(game_finished == false) {
           if((t+c)%2 == 0) {
               turnchar = 'x';
           } else {
               turnchar = 'o';
           }
     
     
       if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)) {
           if(oldboard[0] == 'e'){
               piece_value = 0;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                     
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) {
        if(oldboard[1] == 'e'){
               piece_value = 1;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)) {
       if(oldboard[2] == 'e'){
               piece_value = 2;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                     
                   } else if(t - 1 == 9){
                       if ((!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5))  ){
                           while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                       }
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15)) {
       if(oldboard[3] == 'e'){
               piece_value = 3;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)) {
       if(oldboard[4] == 'e'){
               piece_value = 4;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
 
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)) {
       if(oldboard[5] == 'e'){
               piece_value = 5;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)) {
       if(oldboard[6] == 'e'){
               piece_value = 6;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                     
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)) {
       if(oldboard[7] == 'e'){
               piece_value = 7;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       if (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8)) {
       if(oldboard[8] == 'e'){
               piece_value = 8;
               oldboard[piece_value] = 'f';
               piece_location(board, turnchar, piece_value);
               ++t;
               SerialPuts(" play registered ");
               if((check_hor(board, turnchar) == true )||(check_ver(board, turnchar) == true )||(check_diag(board, turnchar) == true )) {
                   if(((turnchar == 'x')&&(c == 3))||((turnchar == 'o')&&(c == 4))) {
                       ++counter_one;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(((turnchar == 'x')&&(c == 4))||((turnchar == 'o')&&(c == 3))) {
                       ++counter_two;
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                           HAL_Delay(2500); 
                       HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
 
 
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   } else if(t - 1 == 9){
                       while(true)
                       {
                         fresh();
                         if(fresh() == true)
                         { game_finished = true;
                           break; }
                       }
                       break;
                   }
               }
           }
       }
       }
     
       if(counter_one == 3){
           SerialPuts("\nWINNER: Player 1");
           break;
       }
 
       else if(counter_two == 3){
           SerialPuts("\nWINNER: Player 2");
           break;
       }
       
   }
 
   return 0;
}