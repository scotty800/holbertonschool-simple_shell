#include <stdio.h>
#include "shell.h"

// Prototype de la fonction shell_path
//char *shell_path(const char *filename);

int main() {
    char *path = shell_path("touch");
    if (path != NULL) {
        printf("Le chemin de l'exécutable est : %s\n", path);
        free(path);  // N'oubliez pas de libérer la mémoire
    } else {
        printf("Executable non trouvé.\n");
    }
    return 0;
}
