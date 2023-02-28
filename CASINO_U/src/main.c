#include <ti/screen.h>
#include <ti/getcsc.h>
#include <tice.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Main function, called first */
int main(void)
{
  // Init
  os_ClrHome();
  os_NewLine();
  srand(time(NULL));

  // Vars
  int money = 50, bet, pay, random, key, pow, i;
  int payout[10] = {4, 8, 12, 16, 20, 40, 80, 120, 160, 200};
  int seq[4] = {0, 0, 0, 0};
  unsigned int row, col;
  int number[50];
  char buffer[50];

  for(;;) {

    // Betting
    os_SetCursorPos(0, 0);
    sprintf(buffer, "Money: %d               ", money);
    os_PutStrFull(buffer);
    os_SetCursorPos(1, 0);
    os_PutStrFull("Bet: ");

    // Retrieve digits
    do {

      i = 0;
      while((key = os_GetKey()) != k_Enter) {

        // If digit is pressed
        if (key > 141 && key < 152 && i < 6) {

          // Clean digits from last bet
          if (i == 0) {
            os_SetCursorPos(1, 5);
            os_PutStrFull("                    ");
            os_SetCursorPos(1, 5);
          }

          // Save the digit
          number[i] = key - 142;
          sprintf(buffer, "%d", number[i]);
          os_PutStrFull(buffer); i++;

        // Delete key
        } else if (key == 10 && i > 0) {
          i--;
          number[i] = '\0';
          os_GetCursorPos(&row, &col);
          os_SetCursorPos(row, col-1);
          os_PutStrFull(" ");
          os_SetCursorPos(row, col-1);

        // Delete key after bet
        } else if (key == 10 && i == 0) {
          os_SetCursorPos(1, 5);
          os_PutStrFull("                    ");
          os_SetCursorPos(1, 5);

        // Cancel key
        } else if (key == 9) {
          return 0;
        }
      }

      // Build number
      if (i > 0) {
        bet = 0; pow = 1;
        for (i--; i >= 0; i--) {
          bet += number[i] * pow;
          pow = pow * 10;
        }
      }

    } while (bet == 0 || bet > money);

    // Init for random numbers
    os_NewLine();
    os_PutStrFull("Numbers : ");
    pay = 0; money -= bet;
    int comb[5] = {0, 0, 0, 0, 0};

    // Random numbers
    for(int i=0; i < 4; i++) {
      random = rand() % 5;
      comb[random]++;
      seq[i] = random;
      sprintf(buffer, "%d ", random);
      os_PutStrFull(buffer);
    }
    os_NewLine();

    // Series
    if (seq[0] == 1 && seq[1] == 2 && seq[2] == 3 &&  seq[3] == 4) {
      pay = bet * 400;
      os_NewLine();
      os_PutStrFull("Suite!            ");
      os_NewLine();
      sprintf(buffer, "%d x 400 = %d          ", bet, pay);
      os_PutStrFull(buffer);
    } else if (seq[0] == 4 && seq[1] == 3 && seq[2] == 2 &&  seq[3] == 1) {
      pay = bet * 400;
      os_NewLine();
      os_PutStrFull("Inverted suite!   ");
      os_NewLine();
      sprintf(buffer, "%d x 400 = %d          ", bet, pay);
      os_PutStrFull(buffer);
    } else {

      // 3 or 4 times a number
      for(int i=0; i < 5; i++) {
        if (comb[i] == 3) {
          pay = bet * payout[i];
          os_NewLine();
          sprintf(buffer, "Triple %d!        ", i);
          os_PutStrFull(buffer);
          os_NewLine();
          sprintf(buffer, "%d x %d = %d          ", bet, payout[i], pay);
          os_PutStrFull(buffer);
          break;
        } else if (comb[i] == 4) {
          pay = bet * payout[i+5];
          os_NewLine();
          sprintf(buffer, "Quadruple %d!     ", i);
          os_PutStrFull(buffer);
          os_NewLine();
          sprintf(buffer, "%d x %d = %d          ", bet, payout[i+5], pay);
          os_PutStrFull(buffer);
          break;
        }
      }

    }

    // Results
    if (pay == 0) {
      os_SetCursorPos(4, 0);
      os_PutStrFull("No luck!                    ");
      os_SetCursorPos(5, 0);
      os_PutStrFull("                                           ");
    } else {
      money += pay;
    }

    // Check
    if (money == 0) {
      os_SetCursorPos(6, 0);
      os_PutStrFull("No money!");
      while (!os_GetCSC());
      return 0;
    } else if (money < 0) {
      os_SetCursorPos(6, 0);
      os_PutStrFull("Too much money!");
      while (!os_GetCSC());
      return 0;
    }
  }
}
