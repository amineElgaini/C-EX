#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

enum Funcs
{
    ADD = 1,
    DELETE,
    SEARCH,
    SEARCH_PLAYERS,
    ORDER,
    DISPLAY,
    UPDATE,
    STATISTIC, //
    EXIT
};

enum SEARCH
{
    SEARCH_ID = 1,
    SEARCH_NOM,

    SEARCH_POSTS,     // each post
    SEARCH_ORDER_NOM, // nom alphabetique
    SEARCH_ORDER_AGE, // order age

    SEARCH_POST,       // one post
    SEARCH_TRANCH_AGE, // age [ ]
};

typedef struct DateInscription
{
    int year;
    int month;
    int day;
} DateInscription;

int requireButsToBeAstar = 10;
char validPosts[][100] = {"gardien", "defenseir", "milieu", "attaquant"};
char validStatus[][100] = {"titulaire", "remplacant"};

typedef struct Player
{
    long id;
    char nom[100];
    char prenom[100];
    int numerMaillot;
    char post[100]; //{fardien, defenseir, milieu, attaquant}
    int age;
    int buts;
    DateInscription dateInscription;
    char status[100]; //{titulaire, remplacant}
} Player;

int player_count = 0;

void toLowerString(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);  // safe conversion
    }
}

void clear_buffer()
{
    while (getchar() != '\n')
        ;
}

void clear_newline(char str[])
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
    else
    {
        clear_buffer();
    }
}

void saveToFile(Player *arr)
{
    FILE *fp = fopen("./players.dat", "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to save to file!\n");
        return;
    }
    if (player_count > 0)
    {
        fwrite(arr, sizeof(Player), player_count, fp);
    }
    fclose(fp);
}

void loadFromFile(Player **arr)
{
    FILE *fp = fopen("./players.dat", "rb");
    if (fp == NULL)
    {
        printf("No existing data file found. Starting fresh.\n");
        player_count = 0;
        *arr = NULL;
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);

    if (fileSize == 0)
    {
        printf("Data file is empty. Starting fresh.\n");
        player_count = 0;
        *arr = NULL;
        fclose(fp);
        return;
    }

    player_count = fileSize / sizeof(Player);
    *arr = malloc(player_count * sizeof(Player));

    if (*arr == NULL)
    {
        printf("Error: Memory allocation failed!\n");
        player_count = 0;
        fclose(fp);
        return;
    }

    size_t items_read = fread(*arr, sizeof(Player), player_count, fp);
    if (items_read != player_count)
    {
        printf("Warning: Could not read all player from file!\n");
        player_count = items_read;
    }

    fclose(fp);
    printf("Loaded %d player from file.\n", player_count);
}

void printPlayer(Player arr)
{
    // printf("Id: %ld, Nom: %s, Prenom: %s, numeroMaillot: %d, post: %s, age:%d, buts: %d, date: %d-%02d-%02d, status: %s\n",
    //        (arr).id, (arr).nom, (arr).prenom,
    //        (arr).numerMaillot, (arr).post,
    //        (arr).age, (arr).buts, (arr).dateInscription.year,
    //        (arr).dateInscription.month, (arr).dateInscription.day, (arr).status);
    printf("\n  ID            : %d\n", (arr).id);
    printf("  Nom           : %s\n", (arr).nom);
    printf("  Prenom        : %s\n", (arr).prenom);
    printf("  NumMaillot    : %d\n", (arr).numerMaillot);
    printf("  Post          : %s\n", (arr).post);
    printf("  Age           : %d\n", (arr).age);
    printf("  Buts          : %d\n", (arr).buts);
    printf("  Inscription Date: %d-%02d-%02d\n",(arr).dateInscription.year, (arr).dateInscription.month, (arr).dateInscription.day);
    printf("  Status          : %s\n", (arr).status);
}

void addPlayer(Player **arr)
{
    char add = 'y';

    while (add == 'y')
    {
        Player newPlayer;
        printf("Enter player nom: ");
        fgets(newPlayer.nom, sizeof(newPlayer.nom), stdin);
        clear_newline(newPlayer.nom);
        toLowerString(newPlayer.nom);

        printf("Enter player prenom: ");
        fgets(newPlayer.prenom, sizeof(newPlayer.prenom), stdin);
        clear_newline(newPlayer.prenom);
        toLowerString(newPlayer.prenom);

        printf("Enter player numerMaillot: ");
        scanf("%d", &newPlayer.numerMaillot);
        clear_buffer();

        bool isNotValidPost = true;
        do
        {
            printf("Enter player post: ");
            scanf("%s", &newPlayer.post);
            clear_buffer();
            for (int i = 0; i < sizeof(validPosts) / sizeof(validPosts[0]); i++)
            {
                if (strcmp(validPosts[i], newPlayer.post) == 0)
                {
                    isNotValidPost = false;
                    break;
                }
            }
        } while (isNotValidPost);

        printf("Enter player age: ");
        scanf("%d", &newPlayer.age);
        clear_buffer();

        printf("Enter player buts: ");
        scanf("%d", &newPlayer.buts);
        clear_buffer();

        time_t t;
        struct tm *currentTime;
        t = time(NULL);
        currentTime = localtime(&t);
        int year = currentTime->tm_year + 1900;
        int month = currentTime->tm_mon + 1;
        int day = currentTime->tm_mday;

        newPlayer.dateInscription.year = year;
        newPlayer.dateInscription.month = month;
        newPlayer.dateInscription.day = day;

        bool isNotValidStatus = true;
        do
        {
            printf("Enter player status: ");
            scanf("%s", &newPlayer.status);
            clear_buffer();
            for (int i = 0; i < sizeof(validStatus) / sizeof(validStatus[0]); i++)
            {
                if (strcmp(validStatus[i], newPlayer.status) == 0)
                {
                    isNotValidStatus = false;
                    break;
                }
            }
        } while (isNotValidStatus);

        *arr = realloc(*arr, (player_count + 1) * sizeof(Player));
        if (*arr == NULL)
        {
            printf("Error: Memory allocation failed!\n");
            return;
        }

        time_t current_time = time(NULL);
        newPlayer.id = current_time;

        (*arr)[player_count] = newPlayer;
        player_count++;

        saveToFile(*arr);
        printf("Player added successfully!\n");
        if (newPlayer.buts >= requireButsToBeAstar)
        {
            printf("star de l'equipe\n");
        }

        printf("If you wanna add again type 'y': ");
        scanf("%c", &add);
        clear_buffer();
    }
}

void deletePlayer(Player **arr)
{
    if (player_count == 0)
    {
        printf("No player to delete!\n");
        return;
    }

    long id;
    printf("Enter player id: ");
    scanf("%ld", &id);
    clear_buffer();
    
    char validation = 'n';
    printf("If you are sure type Y/y: ");
    scanf("%c", &validation);
    clear_buffer();

    if (validation == 'Y' || validation == 'y')
    {
        int found = 0;
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].id == id)
            {
                for (int j = i; j < player_count - 1; j++)
                {
                    (*arr)[j] = (*arr)[j + 1];
                }
                player_count--;

                if (player_count > 0)
                {
                    *arr = realloc(*arr, player_count * sizeof(Player));
                }
                else
                {
                    free(*arr);
                    *arr = NULL;
                }

                found = 1;
                break;
            }
        }

        if (found)
        {
            saveToFile(*arr);
            printf("Player deleted successfully!\n");
        }
        else
        {
            printf("Player not found!\n");
        }
    } else {
        printf("Your deletion is canceld\n");
    }
}

void displayPlayers(Player **arr)
{
    if (player_count == 0)
    {
        printf("No player to display!\n");
        return;
    }

    for (int i = 0; i < player_count; i++)
    {
        printPlayer((*arr)[i]);
    }
}

enum SEARCH_PLAYER
{
    ID = 1,
    NOM
};
void searchPlayer(Player **arr)
{
    if (player_count == 0)
    {
        printf("No players to search!\n");
        return;
    }
    int choix;
    printf("Enter CHOIX [1] id, [2] nom: ");
    scanf("%d", &choix);
    clear_buffer();

    int found = 0;
    switch (choix)
    {
    case ID:
    {

        long id;
        printf("Enter player id: ");
        scanf("%ld", &id);
        clear_buffer();

        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].id == id)
            {
                printPlayer((*arr)[i]);
                found = 1;
                break;
            }
        }
        break;
    }
    case NOM:
    {

        char nom[100];
        printf("Enter player nom: ");
        fgets(nom, sizeof(nom), stdin);
        clear_newline(nom);

        for (int i = 0; i < player_count; i++)
        {
            if (strcmp((*arr)[i].nom, nom) == 0)
            {
                printPlayer((*arr)[i]);
                found = 1;
                // break;
            }
        }
        break;
    }
    default:

        printf("Out of available options!\n");
        break;
    }

    if (!found)
    {
        printf("Player not found!\n");
    }
}

void updatePlayer(Player **arr)
{
    if (player_count == 0)
    {
        printf("No players to update!\n");
        return;
    }

    long id;
    printf("Enter player id that you wanna update: ");
    scanf("%ld", &id);
    clear_buffer();

    char post[100];
    int age, buts;
    bool isNotValidPost = true;
    do
    {
        printf("Enter player post: ");
        scanf("%s", &post);
        clear_buffer();
        for (int i = 0; i < sizeof(validPosts) / sizeof(validPosts[0]); i++)
        {
            if (strcmp(validPosts[i], post) == 0)
            {
                isNotValidPost = false;
                break;
            }
        }
    } while (isNotValidPost);

    printf("Enter player age: ");
    scanf("%d", &age);
    clear_buffer();

    printf("Enter player buts: ");
    scanf("%d", &buts);
    clear_buffer();

    int found = 0;
    for (int i = 0; i < player_count; i++)
    {
        if ((*arr)[i].id == id)
        {
            (*arr)[i].age = age;
            strcpy((*arr)[i].post, post);
            (*arr)[i].buts = buts;
            found = 1;
            break;
        }
    }

    if (found)
    {
        saveToFile(*arr);
        printf("Player age updated successfully!\n");
    }
    else
    {
        printf("Player not found!\n");
    }
}

enum SEARCH_PLAYERS
{
    POST = 1,
    POSTS,
    AGE_TRANCHE
};

void searchPlayers(Player **arr)
{
    if (player_count == 0)
    {
        printf("No players to search!\n");
        return;
    }
    int choix;
    printf("Enter CHOIX [1] post, [2] posts ,[3] age tranche:");
    scanf("%d", &choix);
    clear_buffer();

    int found = 0;
    switch (choix)
    {
    case POST:
    {

        char post[100];
        printf("Enter post: ");
        fgets(post, sizeof(post), stdin);
        clear_newline(post);

        for (int i = 0; i < player_count; i++)
        {
            if (strcmp((*arr)[i].post, post) == 0)
            {
                printPlayer((*arr)[i]);
                found = 1;
            }
        }
        break;
    }
    case POSTS:
    {

        int postCount = sizeof(validPosts) / sizeof(validPosts[0]);
        for (int i = 0; i < postCount; i++)
        {
            printf("Post: %s\n", validPosts[i]);
            for (int j = 0; j < player_count; j++)
            {
                if (strcmp((*arr)[j].post, validPosts[i]) == 0)
                {
                    printPlayer((*arr)[j]);
                    found = 1;
                    break;
                }
            }
        }

        break;
    }
    case AGE_TRANCHE:
    {

        int minAge;
        printf("Enter player min age: ");
        scanf("%d", &minAge);
        clear_buffer();

        int maxAge;
        printf("Enter player max age: ");
        scanf("%d", &maxAge);
        clear_buffer();

        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].age >= minAge && (*arr)[i].age <= maxAge)
            {
                printPlayer((*arr)[i]);
                found = 1;
                break;
            }
        }
        break;
    }
    default:

        printf("Out of available options!\n");
        break;
    }

    if (!found)
    {
        printf("Nothing Found!\n");
    }
}

enum ORDER_PLAYER
{
    SORT_AGE = 1,
    SORT_NOM
};

enum STATISTICS_OPTIONS
{
    TOTAL_JOUEURS = 1,
    AGE_MOYEN,
    BUTS_SUPERIEUR_DE,
    MEILLEUR_BUTEUR,
    JOUEUR_PLUS_JEUNE,
    JOUEUR_PLUS_AGE
};

void statistics(Player **arr)
{
    if (player_count == 0)
    {
        printf("No players to search!\n");
        return;
    }

    int choix;
    printf("Statistics Menu:\n");
    printf("[1] Nombre total de joueurs\n");
    printf("[2] age moyen des joueurs\n");
    printf("[3] Joueurs avec plus de X buts\n");
    printf("[4] Meilleur buteur\n");
    printf("[5] Joueur le plus jeune\n");
    printf("[6] Joueur le plus age\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    clear_buffer();

    switch (choix)
    {
    case TOTAL_JOUEURS:
        printf("Total number: %d\n", player_count);
        break;
    case AGE_MOYEN:
        int ageMoyen = 0;
        for (int i = 0; i < player_count; i++)
        {
            ageMoyen += (*arr)[i].age;
        }
        ageMoyen /= player_count;
        printf("Moyen de age est: %d\n", ageMoyen);
        break;
    case BUTS_SUPERIEUR_DE:
        int sup = 0;
        scanf("%d", &sup);
        clear_buffer();
        int found = 0;
        printf("Les jouer marque plus de %d est: \n", sup);
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].buts > sup)
            {
                found = 1;
                printPlayer((*arr)[i]);
            }
        }
        if (found == 0)
        {
            printf("0\n", sup);
        }
        break;

    case MEILLEUR_BUTEUR:
        int max = (*arr)[0].buts;

        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].buts > max)
            {
                max = (*arr)[i].buts;
            }
        }
        printf("Les meilleur buteur sont:\n");
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].buts == max)
            {
                printPlayer((*arr)[i]);
            }
        }
        break;
    case JOUEUR_PLUS_JEUNE:
        int minAge = (*arr)[0].age;
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].age < minAge)
            {
                minAge = (*arr)[i].age;
            }
        }
        printf("Les joueer les plus jeune sont:\n");
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].age == minAge)
            {
                printPlayer((*arr)[i]);
            }
        }
        break;
    case JOUEUR_PLUS_AGE:
        int maxAge = (*arr)[0].age;
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].age > maxAge)
            {
                maxAge = (*arr)[i].age;
            }
        }
        printf("Les joueer les plus age sont:\n");
        for (int i = 0; i < player_count; i++)
        {
            if ((*arr)[i].age == maxAge)
            {
                printPlayer((*arr)[i]);
            }
        }
        break;
    default:
        printf("Choix invalide !\n");
    }
}

void order(Player **arr)
{
    if (player_count == 0)
    {
        printf("No players to sort!\n");
        return;
    }

    Player temp;

    int choix;
    printf("Enter choix [1] age, [2] nom: ");
    scanf("%d", &choix);
    clear_buffer();

    int theOrder;
    printf("[0] for asc, [1] for desc: ");
    scanf("%d", &theOrder);
    clear_buffer();

    int found = 0;
    switch (choix)
    {
    case SORT_AGE:
    {
        for (int i = 0; i < player_count - 1; i++)
        {
            for (int j = 0; j < player_count - i - 1; j++)
            {
                if (theOrder==0) {
                    if ((*arr)[j].age > (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                } else if (theOrder==1) {
                    if ((*arr)[j].age < (*arr)[j + 1].age)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }

                }
            }
        }
        break;
    }
    case SORT_NOM:
    {
        for (int i = 0; i < player_count - 1; i++)
        {
            for (int j = 0; j < player_count - i - 1; j++)
            {
                if (theOrder==0) {
                    if (strcmp((*arr)[j].nom, (*arr)[j + 1].nom) > 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                } else if (theOrder==1) {
                    if (strcmp((*arr)[j].nom, (*arr)[j + 1].nom) < 0)
                    {
                        temp = (*arr)[j];
                        (*arr)[j] = (*arr)[j + 1];
                        (*arr)[j + 1] = temp;
                    }
                } 
            }
        }
        break;
    }
    default:
        break;
    }

    saveToFile(*arr);
    printf("Players sorted successfully!\n");
    displayPlayers(arr);
}

int main()
{
    Player *Players = NULL;
    // saveFakeDataToFile();
    loadFromFile(&Players);
    while (1)
    {
        printf("\n=== Player Management System ===\n");
        printf("Enter 1 to add a player\n");
        printf("Enter 2 to delete a player\n");

        printf("Enter 3 to search a player\n");
        printf("Enter 4 to search players\n");
        printf("Enter 5 to order\n");
        printf("Enter 6 to display all players\n");
        printf("Enter 7 to update player\n");

        printf("Enter 8 statistic\n");
        printf("Enter 10 to exit\n");
        printf("=================================\n");
        printf("Your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clear_buffer();
            continue;
        }
        clear_buffer();

        switch (choice)
        {
        case ADD:
            addPlayer(&Players);
            break;
        case DELETE:
            deletePlayer(&Players);
            break;
        case SEARCH:
            searchPlayer(&Players);
            break;
        case SEARCH_PLAYERS:
            searchPlayers(&Players);
            break;
        case ORDER:
            order(&Players);
            break;
        case DISPLAY:
            displayPlayers(&Players);
            break;
        case UPDATE:
            updatePlayer(&Players);
            break;
        case STATISTIC:
            statistics(&Players);
            break;
        case EXIT:
            if (Players)
                free(Players);
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}












// void saveFakeDataToFile()
// {
// Player fakeData[10] = {
//     {1625152800, "lionel", "messi", 10, "attaquant", 34, 30, {1, 7, 2021}, "titulaire"},
//     {1625239200, "cristiano", "ronaldo", 7, "attaquant", 36, 25, {2, 7, 2021}, "titulaire"},
//     {1625325600, "neymar", "jr", 11, "attaquant", 29, 20, {3, 7, 2021}, "titulaire"},
//     {1625412000, "kevin", "de bruyne", 17, "milieu", 30, 10, {4, 7, 2021}, "titulaire"},
//     {1625498400, "virgil", "van dijk", 4, "defenseur", 30, 5, {5, 7, 2021}, "titulaire"},
//     {1625584800, "manuel", "neuer", 1, "gardien", 35, 0, {6, 7, 2021}, "titulaire"},
//     {1625671200, "kylian", "mbappe", 7, "attaquant", 22, 15, {7, 7, 2021}, "titulaire"},
//     {1625757600, "luka", "modric", 10, "milieu", 36, 8, {8, 7, 2021}, "titulaire"},
//     {1625844000, "sergio", "ramos", 4, "defenseur", 35, 6, {9, 7, 2021}, "titulaire"},
//     {1625930400, "thibaut", "courtois", 1, "gardien", 29, 0, {10, 7, 2021}, "titulaire"}
// };


//     FILE *fp = fopen("./players.dat", "wb");
//     if (fp == NULL)
//     {
//         printf("Error: Unable to save fake data to file!\n");
//         return;
//     }
//     fwrite(fakeData, sizeof(Player), 10, fp);
//     fclose(fp);
//     printf("Fake data saved to file successfully!\n");
// }

