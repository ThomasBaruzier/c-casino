#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
  // Initialisation
  srand(time(NULL));
  int money = 50, bet, pay, random;
  int payout[10] = {4, 8, 12, 16, 20, 40, 80, 120, 160, 200};
  int seq[4] = {0, 0, 0, 0};
  printf("\n");

  for(;;) {

    // Betting
    printf("Money : %d, Numbers : ", money);
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
      printf("%d ", random);
    }
    printf("\n");

    // Series
    if (seq[0] == 1 && seq[1] == 2 && seq[2] == 3 &&  seq[3] == 4) {
      pay = bet * 400;
      printf("\n\033[35mWin! You got a suite!\n");
      printf("Payout : %d x \033[34m400\033[35m = %d\033[0m\n\n", bet, pay);
    } else if (seq[0] == 4 && seq[1] == 3 && seq[2] == 2 &&  seq[3] == 1) {
      pay = bet * 400;
      printf("\n\033[35mWin! You got an inverted suite!\n");
      printf("Payout : %d x \033[34m400\033[35m = %d\033[0m\n\n", bet, pay);
    } else {

      // 3 or 4 times a number
      for(int i=0; i < 5; i++) {
        if (comb[i] == 3) {
          pay = bet * payout[i];
          printf("\n\033[32mWin! You got three %d in a row!\n", i);
          printf("Payout : %d x \033[34m%d\033[32m = %d\033[0m\n\n", bet, payout[i], pay);
          break;
        } else if (comb[i] == 4) {
          pay = bet * payout[i+5];
          printf("\n\033[32mWin! You got four %d in a row!\n", i);
          printf("Payout : %d x \033[34m%d\033[32m = %d\033[0m\n", bet, payout[i+5], pay);
          break;
        }
      }

    }

    // Results
    if (pay != 0) {
      money += pay;
    }

    // Check
    if (money <= 0) {
      printf("\n\033[31mNo more money!\033[0m\n\n");
      exit(0);
    }
  }
}
