#include <stdio.h>
#include <stdlib.h>

#define n 4

int main()
{
  int frames[n] = {-1, -1, -1, -1};
  int pagefault = 0;
  int hits = 0;
  int pagereferences[] = {0, 1, 2, 3, 4, 0, 1, 5, 2, 4, 6, 7, 3, 7, 3, 4, 1, 0, 7, 3};
  int numreferences = sizeof(pagereferences) / sizeof(pagereferences[0]);
  int i, j, k;

  printf("page references:");
  for (i = 0; i < numreferences; i++)
  {
    printf("%d ", pagereferences[i]);
  }
  printf("\n");

  for (i = 0; i < numreferences; i++)
  {
    int page = pagereferences[i];
    int pagefound = 0;

    for (j = 0; j < n; j++)
    {
      if (frames[j] == page)
      {
        pagefound = 1;
        hits++;
        break;
      }
    }

    if (!pagefound)
    {
      int lruindex = 0;
      int lruvalue = frames[0];

      for (j = 1; j < n; j++)
      {
        if (frames[j] < lruvalue)
        {
          lruvalue = frames[j];
          lruindex = j;
        }
      }

      frames[lruindex] = page;
      pagefault++;

      printf("page %d caused a page fault, Frames: ", page);
      for (k = 0; k < n; k++)
      {
        printf("%d ", frames[k]);
      }
      printf("\n");
    }
  }

  printf("total page fault : %d\n", pagefault);
  printf("total hits : %d\n", hits);
  printf("total misses : %d\n", pagefault);
  printf("hit ratio : %.2f\n", (float)hits / numreferences);
  printf("miss ratio : %.2f\n", (float)pagefault / numreferences);

  return 0;
}
