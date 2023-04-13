#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NAME_LENGTH 50
#define MAX_TEAM_LENGTH 10
#define MAX_POS_LENGTH 3

// Struktura pro reprezentaci hráče
typedef struct Player {
    char name[MAX_NAME_LENGTH];
    char team[MAX_TEAM_LENGTH];
    char pos[MAX_POS_LENGTH];
    int games;
    int g;
    int a;
    int pts;
    int plusMinus;
    int pim;
    int sog;
    int gwg;
    int ppg;
    int ppa;
    int shg;
    int sha;
    int hits;
    int bs;
} Player;

// Prototypy funkcí
void printMenu();
void printPlayer(Player player);
Player *loadPlayers(const char *fileName, int *numPlayers);
void freePlayers(Player *players);
void top5(Player *players, int numPlayers);
Player *bestScorer(Player *players, int numPlayers);
Player *mostPenalties(Player *players, int numPlayers);
Player *defensemanWithMostAssists(Player *players, int numPlayers);

int main() {
    Player *players = NULL;
    int numPlayers = 0;
    Player *selectedPlayer;

    char userInput[100]; // Předpokládáme, že uživatel zadá nejvýše 99 znaků
    int menuChoice;
    char *invalidChoice;

    players = loadPlayers("data/stats.csv", &numPlayers);

    while (1) {
        printMenu();
        printf("Vyberte akci: ");

        fgets(userInput, sizeof(userInput), stdin); // Načtení vstupu jako řetězce
        userInput[strcspn(userInput, "\n")] = '\0'; // Odstranění znaku nového řádku z vstupu
        menuChoice = (int) strtol(userInput, &invalidChoice, 10); // Převedení řetězce na celé číslo

        if (userInput[0] == '\0' || *invalidChoice != '\0') {
            printf("Zadali jste neplatne cele cislo.\n");
        } else {
            switch (menuChoice) {
                case 1:
                    top5(players, numPlayers);
                    break;
                case 2:
                    selectedPlayer = bestScorer(players, numPlayers);
                    printPlayer(*selectedPlayer);
                    break;
                case 3:
                    selectedPlayer = mostPenalties(players, numPlayers);
                    printPlayer(*selectedPlayer);
                    break;
                case 4:
                    selectedPlayer = defensemanWithMostAssists(players, numPlayers);
                    printPlayer(*selectedPlayer);
                    break;
                case 0:
                    freePlayers(players);
                    printf("Program ukoncen.\n");
                    return 0;
                default:
                    printf("Neplatna volba. Zvolte znovu.\n");
                    break;
            }
        }
    }
}

// Funkce pro tisk menu
void printMenu() {
    printf("\n---- MENU ----\n");
    printf("1 - TOP 5 (nejproduktivnejsi hraci kanadskeho bodovani)\n");
    printf("2 - Nejlepsi strelec\n");
    printf("3 - Nejtretanejsi hrac\n");
    printf("4 - Obrance s nejvyssim poctem asistenci\n");
    printf("0 - Ukoncit program\n");
}

// Funkce pro načtení hráčů z CSV souboru
Player *loadPlayers(const char *fileName, int *numPlayers) {
    FILE *file = fopen(fileName, "r"); // Otevření souboru pro čtení
    if (file == NULL) {
        printf("Chyba: Nelze otevrit soubor '%s'\n", fileName);
        exit(1);
    }

    // Načtení hlavičky s názvy sloupců
    char line[MAX_LINE_LENGTH];
    if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
        printf("Chyba: Prazdny soubor '%s'\n", fileName);
        exit(1);
    }

    // Počet hráčů
    int count = 0;
    Player *players = NULL;

    // Načtení dat hráčů
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        Player player;
        char *token = strtok(line, ",");
        strcpy(player.name, token);

        token = strtok(NULL, ",");
        strcpy(player.team, token);

        token = strtok(NULL, ",");
        strcpy(player.pos, token);

        token = strtok(NULL, ",");
        player.games = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.g = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.a = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.pts = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.plusMinus = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.pim = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.sog = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.gwg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.ppg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.ppa = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.shg = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.sha = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.hits = (int) strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        player.bs = (int) strtol(token, NULL, 10);


        // Dynamická alokace paměti pro hráče
        players = (Player *) realloc(players, (count + 1) * sizeof(Player));
        if (players == NULL) {
            printf("Chyba: Nedostatek paměti\n");
            exit(1);
        }

        // Přidání hráče do pole
        players[count] = player;
        count++;
    }

    fclose(file); // Uzavření souboru
    *numPlayers = count; // Uložení počtu načtených hráčů do proměnné numPlayers
    return players; // Vrácení pole hráčů
}

// Funkce pro uvolnění paměti alokované pro hráče
void freePlayers(Player *players) {
    free(players);
}

// Funkce pro výpis hráče
void printPlayer(Player player) {
    printf("\n\n-------------------------------------\n");
    printf("%s\n", player.name);
    printf("-------------------------------------\n");
    printf("  Tym: %s\n", player.team);
    printf("  Pozice: %s\n", player.pos);
    printf("  Bodu: %d\n", player.pts);
    printf("  Zapasu: %d\n", player.games);
    printf("  Golu: %d\n", player.g);
    printf("  Asistenci: %d\n", player.a);
    printf("  +/- body: %d\n", player.plusMinus);
    printf("  Trestne minuty: %d\n", player.pim);
    printf("  Strely na branu: %d\n", player.sog);
    printf("  Vitezne goly: %d\n", player.gwg);
    printf("  Presilovkove goly: %d\n", player.ppg);
    printf("  Presilovkove nahravky: %d\n", player.ppa);
    printf("  Goly v oslabeni: %d\n", player.shg);
    printf("  Asistence v oslabeni: %d\n", player.sha);
    printf("  Blokovanych strel: %d\n", player.bs);
    printf("  Hitu: %d\n", player.hits);
    printf("-------------------------------------\n");
}

// Funkce pro výpis TOP 5 nejproduktivnějších hráčů
void top5(Player *players, int numPlayers) {
    // Seřazení hráčů podle celkového počtu bodů (points) - algoritmus bubble sort
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = 0; j < numPlayers - i - 1; j++) {
            if (players[j].pts < players[j + 1].pts) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Výpis TOP 5 hráčů
    printf("TOP 5 nejproduktivnějších hráčů kanadského bodování:\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. ", i + 1);
        printPlayer(players[i]);
    }
}

// Funkce pro nalezení nejlepšího střelce
Player *bestScorer(Player *players, int numPlayers) {
    if (numPlayers == 0) {
        // Pokud je počet hráčů 0, vrátíme NULL
        return NULL;
    }

    Player *bestScorer = &players[0]; // Předpokládáme, že první hráč je nejlepší střelec

    // Projdeme všechny hráče a porovnáme počet vstřelených branek
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].g > bestScorer->g) {
            // Pokud má aktuální hráč více branek než dosud nejlepší střelec, aktualizujeme ho
            bestScorer = &players[i];
        }
    }

    // Vrátíme pointer na nejlepšího střelce
    return bestScorer;
}

// Funkce pro nalezení hráče s největším počtem trestných minut
Player *mostPenalties(Player *players, int numPlayers) {
    if (numPlayers == 0) {
        // Pokud je počet hráčů 0, vrátíme NULL
        return NULL;
    }

    Player *mostPenalties = &players[0]; // Předpokládáme, že první hráč má největší počet trestných minut

    // Projdeme všechny hráče a porovnáme počet trestných minut
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].pim > mostPenalties->pim) {
            // Pokud má aktuální hráč více trestných minut než dosud hráč s největším počtem trestných minut, aktualizujeme ho
            mostPenalties = &players[i];
        }
    }

    // Vrátíme pointer na hráče s největším počtem trestných minut
    return mostPenalties;
}

// Funkce pro nalezení obránce s nejvíce asistencemi
Player *defensemanWithMostAssists(Player *players, int numPlayers) {
    Player *defenseman = NULL;
    int maxAssists = 0;

    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].pos, "D") == 0 && players[i].a > maxAssists) {
            maxAssists = players[i].a;
            defenseman = &players[i];
        }
    }

    return defenseman;
}
