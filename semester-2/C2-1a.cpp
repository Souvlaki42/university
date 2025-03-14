#include <cstdio>
#include <cstring>
#include <cmath>

int main(int argc, char **argv)
{
    printf("Μήνυμα  : Γεια σου κόσμε\n");
    printf("Mέγεθος : %d\n\n", strlen("Γεια σου κόσμε\n"));
    printf("Τετραγωνική ρίζα 100.0 : %lf\n\n", sqrt(100.0));

    return 0;
}

// The reason strlen prints 27 instead of 15 is:
// Γεια σου κόσμε\n converts to ["Γ", "ε", "ι", "α", " ", "σ", "ο", "υ", " ", "κ", "ό", "σ", "μ", "ε", "\n"]
// All of these characters count as 2 bytes while " " and "\n" count as 1 byte
// That means 12 characters of 2 bytes each and 3 characters of 1 byte each
// 12 * 2 + 3 * 1 = 27 characters long string instead of 15