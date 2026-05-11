#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ── algorithm implementations ────────────────────────────────────────────── */

int euclid(int a, int b)
{
    int count = 0;
    while (b != 0)
    {
        count++;
        int r = a % b;
        a = b;
        b = r;
    }
    return count;
}

int MODeuclid(int a, int b)
{
    int count = 0;
    while (a != b)
    {
        count++;
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return count;
}

int CONint(int a, int b)
{
    int count = 0;
    int min = (a < b) ? a : b;
    while (min >= 1)
    {
        count++;
        if (a % min == 0)
        {
            count++;
            if (b % min == 0)
                break;
        }
        min--;
    }
    return count;
}

/* ── empirical plotter ────────────────────────────────────────────────────── */

void plotter_empirical(const char *worst_file, const char *best_file,
                       int (*algo)(int, int))
{
    FILE *fp_worst = fopen(worst_file, "w");
    FILE *fp_best  = fopen(best_file,  "w");

    for (int n = 10; n <= 100; n += 10)
    {
        int maxcount = 0;
        int mincount = 1000000;

        for (int j = 2; j <= n; j++)
            for (int k = 2; k <= n; k++)
            {
                int c = algo(j, k);
                if (c > maxcount) maxcount = c;
                if (c < mincount) mincount = c;
            }

        fprintf(fp_worst, "%d\t%d\n", n, maxcount);
        fprintf(fp_best,  "%d\t%d\n", n, mincount);
    }

    fclose(fp_worst);
    fclose(fp_best);
}

/* ── gnuplot graph generator ──────────────────────────────────────────────── */

void generateGraph(int method)
{
    const char *worstFile, *bestFile, *title, *xrange, *yrange;

    if (method == 1)
    {
        worstFile = "Euclid_Worst.txt";
        bestFile  = "Euclid_Best.txt";
        title     = "Euclid GCD Algorithm (Empirical)";
        xrange    = "[0:110]";
        yrange    = "[0:10]";
    }
    else if (method == 2)
    {
        worstFile = "MODEuclid_Worst.txt";
        bestFile  = "MODEuclid_Best.txt";
        title     = "Modified Euclid GCD Algorithm (Empirical)";
        xrange    = "[0:110]";
        yrange    = "[0:200]";
    }
    else
    {
        worstFile = "CONint_Worst.txt";
        bestFile  = "CONint_Best.txt";
        title     = "Consecutive Integer GCD Algorithm (Empirical)";
        xrange    = "[0:110]";
        yrange    = "[0:200]";
    }

    FILE *cmd = fopen("command.txt", "w");
    fprintf(cmd, "set title '%s'\n", title);
    fprintf(cmd, "set xlabel 'Input size (n)'\n");
    fprintf(cmd, "set ylabel 'Operation Count'\n");
    fprintf(cmd, "set xrange %s\n", xrange);
    fprintf(cmd, "set yrange %s\n", yrange);
    fprintf(cmd, "set style data linespoints\n");
    fprintf(cmd, "plot '%s' title 'Worst Case', '%s' title 'Best Case'\n",
            worstFile, bestFile);
    fprintf(cmd, "pause -1\n");
    fclose(cmd);

    system("gnuplot command.txt");
}
/* ── main ─────────────────────────────────────────────────────────────────── */

int main(void)
{
    printf("Running empirical analysis...\n");

    printf("  [1/3] Euclid...\n");
    plotter_empirical("Euclid_Worst.txt", "Euclid_Best.txt", euclid);

    printf("  [2/3] Modified Euclid...\n");
    plotter_empirical("MODEuclid_Worst.txt", "MODEuclid_Best.txt", MODeuclid);

    printf("  [3/3] Consecutive Integer...\n");
    plotter_empirical("CONint_Worst.txt", "CONint_Best.txt", CONint);

    printf("Generating graphs...\n");
    for (int method = 1; method <= 3; method++)
        generateGraph(method);

    printf("Done.\n");
    return 0;
}
