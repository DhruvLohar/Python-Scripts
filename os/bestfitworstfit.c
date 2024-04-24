#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory to blocks as per Best Fit algorithm
void bestFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n]; // Stores block id of the block allocated to a process

  // Initially no block is assigned to any process
  for (int i = 0; i < n; i++)
  {
    allocation[i] = -1;
  }

  // Pick each process and find suitable blocks according to its size and assign to it
  for (int i = 0; i < n; i++)
  {
    // Find the best fit block for the current process
    int bestIdx = -1;
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
        {
          bestIdx = j;
        }
      }
    }

    // If we could find a block for the current process
    if (bestIdx != -1)
    {
      // Allocate block bestIdx to ith process
      allocation[i] = bestIdx;
      // Reduce available memory in this block
      blockSize[bestIdx] -= processSize[i];
    }
  }

  printf("\nBest Fit Allocation:\n");
  printf("Process No.\tProcess Size\tBlock no.\n");
  for (int i = 0; i < n; i++)
  {
    printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
    if (allocation[i] != -1)
    {
      printf("%d", allocation[i] + 1);
    }
    else
    {
      printf("Not Allocated");
    }
    printf("\n");
  }
}

// Function to allocate memory to blocks as per First Fit algorithm
void firstFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n]; // Stores block id of the block allocated to a process

  // Initially no block is assigned to any process
  for (int i = 0; i < n; i++)
  {
    allocation[i] = -1;
  }

  // Pick each process and find suitable blocks according to its size and assign to it
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        // Allocating block j to the ith process
        allocation[i] = j;
        // Reduce available memory in this block
        blockSize[j] -= processSize[i];
        break; // Go to the next process in the queue
      }
    }
  }

  printf("\nFirst Fit Allocation:\n");
  printf("Process No.\tProcess Size\tBlock no.\n");
  for (int i = 0; i < n; i++)
  {
    printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
    if (allocation[i] != -1)
    {
      printf("%d", allocation[i] + 1);
    }
    else
    {
      printf("Not Allocated");
    }
    printf("\n");
  }
}

// Function to allocate memory to blocks as per Worst Fit algorithm
void worstFit(int blockSize[], int m, int processSize[], int n)
{
  int allocation[n]; // Stores block id of the block allocated to a process

  // Initially no block is assigned to any process
  for (int i = 0; i < n; i++)
  {
    allocation[i] = -1;
  }

  // Pick each process and find suitable blocks according to its size and assign to it
  for (int i = 0; i < n; i++)
  {
    // Find the worst fit block for the current process
    int worstIdx = -1;
    for (int j = 0; j < m; j++)
    {
      if (blockSize[j] >= processSize[i])
      {
        if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
        {
          worstIdx = j;
        }
      }
    }

    // If we could find a block for the current process
    if (worstIdx != -1)
    {
      // Allocate block worstIdx to ith process
      allocation[i] = worstIdx;
      // Reduce available memory in this block
      blockSize[worstIdx] -= processSize[i];
    }
  }

  printf("\nWorst Fit Allocation:\n");
  printf("Process No.\tProcess Size\tBlock no.\n");
  for (int i = 0; i < n; i++)
  {
    printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
    if (allocation[i] != -1)
    {
      printf("%d", allocation[i] + 1);
    }
    else
    {
      printf("Not Allocated");
    }
    printf("\n");
  }
}

int main()
{
  int blockSize[] = {100, 500, 200, 300, 600};
  int processSize[] = {212, 417, 112, 426};
  int m = sizeof(blockSize) / sizeof(blockSize[0]);
  int n = sizeof(processSize) / sizeof(processSize[0]);

  bestFit(blockSize, m, processSize, n);
  firstFit(blockSize, m, processSize, n);
  worstFit(blockSize, m, processSize, n);

  return 0;
}
