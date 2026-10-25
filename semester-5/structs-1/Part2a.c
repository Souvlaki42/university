/*
 * Το σύνολο της Λύσης της 1ης άσκησης.
 * –-----------------------------------
 * Για να πάρετε ιδέες και μόνο....
 * Αν λείπει κάποιος έλεγχος μετά από malloc ή κάποιο free... Προσθέστε το!
 * Δουλέψτε πάνω στα ακόλουθα:
 * 1) Μήπως μπορεί να βελτιωθεί ο έλεγχος του πίνακα όταν προσπαθούμε να βρούμε την λύση του puzzle;
 * 2) Θα μπορούσε το πρόγραμμα να τροποποιηθεί ώστε να δημιουργεί όλα τα πιθανά sudoku (όλους τους πιθανούς πίνακες που πληρούν τους
 *     όρους);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CheckParams (int, char **);
char **Create2DMat (int, int);
int ReadSudoku (char *, char **);
int CheckLine (char *);
int CheckSudoku (char **);
int CheckLines (char **, int);
int CheckCols (char **, int);
int CheckSquares (char **, int);
char CheckNine (char *);
void PrintSudoku (char **);
void Square2Coords (int, int *, int *, int *, int *);
void Free2DMatrix (char **, int);
int SolvePuzzle (char **);
char *FillStat (char **);
void Pos2Coord (int, int *, int *);
int HandleSquare (char **, char *, int);

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
        printf ("Είναι\n\n------------------\n\n");
    else
    {
        //Τερματισμός σε περίπτωση μη έγκυρου πίνακα, Credit: ΔΑΜΙΑΝΙΔΗΣ ΔΗΜΗΤΡΙΟΣ (25390332)
        printf ("Δεν είναι\n");
        exit (0);
    }

    Res = SolvePuzzle (Mat);
    if (Res)
    {
        printf ("Το παζλ λύθηκε:\n\n");
        PrintSudoku (Mat);
    }
    else
        printf ("Δεν μπόρεσα να βρω λύση...:\n\n");

    Free2DMatrix (Mat, 9);
    return 0;
}

void CheckParams (int n, char **P)
{
    FILE *fp;
    if (n != 2)
    {
        fprintf (stderr, "Άκυρος αριθμός παραμέτρων. Σύνταξη εντολής: %s <όνομα αρχείου παζλ>\n>", P[0]);
        exit (1);
    }

    if (! (fp=fopen (P[1], "r")))
    {
        fprintf (stderr, "Δεν μπορώ να ανοίξω το αρχείο <%s>\n", P[1]);
        exit (2);
    }
    fclose (fp);
}

//Δεν καλύπτεται η περίπτωση το αρχείο να έχει λιγότερες ή περισσότερες γραμμές από όσες πρέπει.
//Προσθέστε τον έλεγχο. Το να έχει λιγότερες ή περισσότερες στήλες καλύπτεται. Είναι κατανοητό το πως;
int ReadSudoku (char *FN, char **Mat)
{
    FILE *fp;
    int i, j;
    char *Buff;
    Buff = (char *) malloc (11);
    if (!Buff)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }

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
    R = CheckLines (Mat, 0) && CheckCols (Mat, 0) && CheckSquares (Mat, 0);

    return R;

}

int CheckLines (char **Mat, int Verb)
{
    int i;
    char *Nine;
    int R;
    Nine = (char *) malloc (9);
    if (!Nine)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }
    for (i = 0; i < 9; i++)
    {
        memcpy (Nine, Mat[i], 9);
        R = CheckNine (Nine);
        if (R != 0)
        {
            if (Verb)
                printf ("Λάθος στη γραμμή %1d. Ο αριθμός %1d επαναλαμβάνεται\n", i + 1, R);
            free (Nine);
            return 0;
        }
    }
    free (Nine);
    return 1;
}

int CheckCols (char **Mat, int Verb)
{
    int i, j;
    char *Nine;
    int R;
    Nine = (char *) malloc (9);
    if (!Nine)
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται..."),
        exit (3);
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
            Nine[j] = Mat[j][i];
        R = CheckNine (Nine);
        if (R != 0)
        {
            if (Verb)
                printf ("Λάθος στη στήλη %1d. Ο αριθμός %1d επαναλαμβάνεται\n", i + 1, R);
            free (Nine);
            return 0;
        }
    }
    free (Nine);
    return 1;
}

int CheckSquares (char **Mat, int Verb)
{
    int i, j, k, p;
    char *Nine;
    int R;
    int X1, Y1, X2, Y2;
    Nine = (char *) malloc (9);
    if (!Nine)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }
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
            if (Verb)
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
    if (Chk == NULL)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }
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

void Free2DMatrix (char **Pin, int Size)
{
    int i;
    for (i = 0; i < Size; i++)
        free (*(Pin + i));
    free (Pin);
}

int SolvePuzzle (char **Mat)
{
    char *Stat;
    int Res;
    Stat = FillStat (Mat);
    Res = HandleSquare (Mat, Stat, 0);
    free (Stat);
    return Res;

}

char *FillStat (char **Pin)
{
    char *Tmp;
    int Pos, X, Y;
    Tmp = (char *) malloc (81);
    if (!Tmp)
    {
        fprintf (stderr, "Πρόβλημα δέσμευσης μνήμης. Το πρόγραμμα τερματίζεται...");
        exit (3);
    }
    memset (Tmp, 0, 81);
    for (Pos = 0; Pos < 81; Pos++)
    {
        Pos2Coord (Pos, &X, &Y);
        if (Pin[Y][X] > 0)
            Tmp [Pos] = 1;
    }
    return Tmp;
}

void Pos2Coord (int Pos, int *X, int *Y)
{
    *Y = Pos / 9;
    *X = Pos % 9;
}

int HandleSquare (char **Mat, char *Stat, int Squ)
{
    int X, Y;
    int CurVal;

    if (Squ == 81)
        return 1;
    if (Stat[Squ] == 1)
        return HandleSquare (Mat, Stat, Squ + 1);
    Pos2Coord (Squ, &X, &Y);
    for (CurVal = 1; CurVal <= 9; CurVal++)
    {
        Mat[Y][X] = CurVal;
        if (!CheckSudoku (Mat))
            continue;
        if (HandleSquare (Mat, Stat, Squ + 1))
            return 1;
    }
    Mat [Y][X] = 0;
    return 0;
}
