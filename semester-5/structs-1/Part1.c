#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CheckParams (int, char **);
char **Create2DMat (int, int);
int ReadSudoku (char *, char **);
int CheckLine (char *);
char **Create2DMat (int, int);
int CheckSudoku (char **);
int CheckLines (char **);
int CheckCols (char **);
int CheckSquares (char **);
char CheckNine (char *);
void PrintSudoku (char **);
void Square2Coords (int, int *, int *, int *, int *);


int main (int argc, char **argv)
{
    char **Mat;
    int Res;

    CheckParams (argc, argv);
    Mat = Create2DMat (9, 9);
    if (!Mat)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }

    Res = ReadSudoku (argv [1], Mat);
    if (!Res)
    {
        fprintf (stderr, "Πρόβλημα με περιεχόμενο αρχείου. Το πρόγραμμα τερματίζεται...");
        exit (4);
    }

    PrintSudoku (Mat);

    Res = CheckSudoku (Mat);
    if (Res)
        printf ("Είναι\n");
    else
        printf ("Δεν είναι\n");

}

void CheckParams (int n, char **P)
{
    FILE *fp;
    if (n != 2)
    {
        fprintf (stderr, "Άκυρος αριθμός παραμέτρων. Σύνταξη εντολής: %s <όνομα αρχείου παζλ>\n", P[0]);
        exit (1);
    }

    if (! (fp=fopen (P[1], "r")))
    {
        fprintf (stderr, "Δεν μπορώ να ανοίξω το αρχείο <%s>\n", P[1]);
        exit (2);
    }
    fclose (fp);
}

//Γίνεται τυπικά ή πρακτικά έλεγχος ορθότητας των περιεχομένων του αρχείου; Αν όχι... κάτι πρέπει να γίνει
int ReadSudoku (char *FN, char **Mat)
{
    FILE *fp;
    int i, j;
    char *Buff;
    Buff = (char *) malloc (11);
    fp = fopen (FN, "r");
    for (i = 0; i < 9; i++)
    {
        fgets (Buff, 11, fp);
        if (!CheckLine (Buff))
        {
            free (Buff);
            fclose (fp);
            return 0;
        }
        for (j = 0; j < 9; j++)
            Mat[i][j] = Buff[j] - '0';
    }
    free (Buff);
    fclose (fp);
    return 1;
}

int CheckLine (char *Lin)
{
    int i;
    for (i = 0; i < 9; i++)
        if (Lin[i] < '0' || Lin[i] > '9')
            return 0;
    if (Lin[9] != '\n')
        return 0;
    return 1;
}

char **Create2DMat (int L, int C)
{
    char **Tmp;
    int i;
    Tmp = (char **) malloc (L * sizeof (char *));
    if (!Tmp)
        return NULL;
    for (i = 0; i < L; i++)
    {
        Tmp[i] = (char *) malloc (C);
        if (!Tmp[i])
            return NULL;
    }
    return Tmp;
}

int CheckSudoku (char **Mat)
{
    int R;
    R = CheckLines (Mat) && CheckCols (Mat) && CheckSquares (Mat);

    return R;

}

int CheckLines (char **Mat)
{
    int i;
    char *Nine;
    int R;
    Nine = (char *) malloc (9);
    for (i = 0; i < 9; i++)
    {
        memcpy (Nine, Mat[i], 9);
        R = CheckNine (Nine);
        if (R != 0)
        {
            printf ("Λάθος στη γραμμή %1d. Ο αριθμός %1d επαναλαμβάνεται\n", i + 1, R);
            free (Nine);
            return 0;
        }
    }
    free (Nine);
    return 1;
}

int CheckCols (char **Mat)
{
    int i, j;
    char *Nine;
    int R;
    Nine = (char *) malloc (9);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
            Nine[j] = Mat[j][i];
        R = CheckNine (Nine);
        if (R != 0)
        {
            printf ("Λάθος στη στήλη %1d. Ο αριθμός %1d επαναλαμβάνεται\n", i + 1, R);
            free (Nine);
            return 0;
        }
    }
    free (Nine);
    return 1;
}

int CheckSquares (char **Mat)
{
    int i, j, k, p;
    char *Nine;
    int R;
    int X1, Y1, X2, Y2;
    Nine = (char *) malloc (9);
    for (i = 0; i < 9; i++)
    {
        Square2Coords (i, &X1, &Y1, &X2, &Y2);
        p = 0;
        for (j = Y1; j <= Y2; j++)
            for (k = X1; k <= X2; k++)
                Nine[p++] = Mat[j][k];

        R = CheckNine (Nine);
        if (R != 0)
        {
            printf ("Λάθος στo εσωτερικό τετράγωνο %1d. Ο αριθμός %1d επαναλαμβάνεται\n", i + 1, R);
            free (Nine);
            return 0;
        }
    }
    free (Nine);
    return 1;
}

void Square2Coords (int Sq, int *X1, int *Y1, int *X2, int *Y2)
{
    *Y1 = Sq / 3 * 3;
    *X1 = Sq % 3 * 3;
    *Y2 = *Y1 + 2;
    *X2 = *X1 + 2;
}

/*
 * Ελέγχει αν σε έναν πίνακα 9 θέσεων, που δίδεται ως όρισμα, υπάρχει κάποιο από τα ψηφία [1..9] περισσότερες από μία
 * φορές. Αν όχι επιστρέφει 0 (πίνακας Ο.Κ.). Αν ναι επιστρέφει τον πρώτο αριθμό που βρήκε να επαναλαμβάνεται (λάθος).
 * Προϋπόθεση για την ορθή λειτουργία της συνάρτησης είναι το περιεχόμενο του πίνακα να είναι έγκυρο δηλάδή να περιέχει
 * μόνο τα ψηφία [0..9] (ως ακέραιες τιμές, όχι ως χαρακτήρες).
*/
char CheckNine (char *Nums)
{
    char *Chk;
    int i;
    Chk = (char *) malloc (9);
    memset (Chk, 0, 9);
    for (i = 0; i < 9; i++)
    {
        if (Nums[i] == 0)
            continue;
        if (++Chk [Nums[i] - 1] == 2)
        {
            free (Chk);
            return Nums[i];
        }
    }
    free (Chk);
    return 0;
}

void PrintSudoku (char **M)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf ("%c", M[i][j] + '0');
            if (j % 3 == 2)
                printf (" ");
        }
        printf ("\n");
        if (i % 3 == 2)
            printf ("\n");
    }
}
