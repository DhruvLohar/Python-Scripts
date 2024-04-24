#include <stdio.h>

int main()
{
  int avail, i, j = 0, p, k, n, no, miss = 0, hit = 0, frame[20], arr[30], temp[100];
  float missper, hitper;

  printf("Enter number of pages: ");
  scanf("%d", &n);

  for (i = 0; i < n; i++)
  {
    printf("Page No.%d : ", i + 1);
    scanf("%d", &arr[i]);
  }

  printf("Enter frame size: ");
  scanf("%d", &no);

  printf("Pages\t\tPage Frame\n");

  // Initialize frame array
  for (i = 0; i < no; i++)
  {
    frame[i] = 0;
  }

  for (i = 0; i < no; i++)
  {
    temp[i] = -1;
  }

  for (i = 0; i < n; i++)
  {
    printf("%d\t\t", arr[i]);
    avail = 0;

    for (k = 0; k < no; k++)
    {
      if (frame[k] == arr[i])
      {
        avail = 1;

        for (k = 0; k < no; k++)
        {
          printf("%d\t", frame[k]);
        }

        printf("Hit");
        hit++;
      }
    }

    if (avail == 0)
    {
      frame[j] = arr[i];
      miss++;

      for (k = 0; k < no; k++)
      {
        if (j == k)
        {
          printf("%d\t", frame[k]);
          continue;
        }

        printf("%d\t", frame[k]);
      }

      j = (j + 1) % no;
    }

    printf("\n");
  }

  missper = (float)miss / n * 100;
  hitper = (float)hit * 100 / n;

  printf("No. of misses: %d\n", miss);
  printf("Miss Percentage: %f%% \n", missper);
  printf("No. of hits: %d\n", hit);
  printf("Hit percentage : %f%%\n", hitper);

  return 0;
}
