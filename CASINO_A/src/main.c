#include <ti/screen.h>
#include <ti/getcsc.h>
#include <tice.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Main function, called first */
int main(void)
{
  os_ClrHome();
  os_NewLine();
//  os_SetFlag(APP, AUTOSCROLL);
  srand(time(NULL));

  int money = 50, bet, pay, random;
  int payout[10] = {4, 8, 12, 16, 20, 40, 80, 120, 160, 200};
  int seq[4] = {0, 0, 0, 0};
  char buffer[50];

  for(;;) {

    // Betting
    os_SetCursorPos(0, 0);
    sprintf(buffer, "Money: %d", money);
    os_PutStrFull(buffer);
    os_NewLine();
    os_PutStrFull("Numbers : ");
    if (money < 50) {
      bet = 1;
    } else {
      bet = money / 10;
    }

    // Random numbers
    pay = 0; money -= bet;
    int comb[5] = {0, 0, 0, 0, 0};
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
    if (pay != 0) {
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

  while (!os_GetCSC());
  return 0;
}


