// priority arrival time 0
#include <stdio.h>
#define max 50
int main()
{
    int i, j, n, t, p[max], bt[max], pr[max], wt[max], tat[max], Total_wt = 0, Total_tat = 0;
    float awt = 0, atat = 0;
    printf("Enter the number of processes:");
    scanf("%d", &n);
    printf("Enter the process id, burst time and priority of the process:\n");
    // Enter the processes according to their arrival times
    for (i = 0; i < n; i++)
    {
        printf("P%d:",i+1);
        scanf("%d %d %d", &p[i],&bt[i],&pr[i]);
        
    }
    // Apply the bubble sort technique to sort the processes according to their priorities times
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (pr[j] > pr[j + 1])
            {
                // Sort according to priorities
                t = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = t;
                // Sorting burst times
                t = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = t;
                // Sorting Process numbers
                t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
            } 
        }     
    } 
    printf("\nGantt Chart:\n");
    // Print Gantt chart header
    printf("\n--------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("  P%d  |", p[i]);
    }
    printf("\n---------------------------------------------\n");        
    
    printf("\nProcessid \t Burst Time\t Priority\t Waiting Time\t Turn Around Time\n");
    for (i = 0; i < n; i++)
    {
        wt[i] = 0;
        tat[i] = 0;
        for (j = 0; j < i; j++)
            wt[i] = wt[i] + bt[j];
        tat[i] = wt[i] + bt[i];
        Total_wt = Total_wt + wt[i];
        Total_tat = Total_tat + tat[i];
        printf("%d\t\t %d\t\t %d\t\t  %d\t\t  %d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }
    awt = (float)Total_wt / n;
    atat = (float)Total_tat / n;
    printf("The average waiting time = %f\n", awt);
    printf("The average turn aroud time = %f\n", atat);
}