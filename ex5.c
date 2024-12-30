/******************
Name:Miriam Lipkovich
ID:336239652
Assignment: ex5
*******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WATCH 1
#define ADD 2
#define REMOVE 3
#define EXIT 4
#define INITIAL_BUFFER_SIZE 128 //for read strings with dynamic memory allocation i think :/


typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

//some recommendations for functions, you may implement however you want
void CleanBuffer();
void printPlaylistsMenu();
void printSongsMenu();
void printSortMenu();
void DisplayPlaylists(int *currentAmount, Playlist **playlist, int key_menu);
void AddPlaylist(int *currentAmount, Playlist ***playlist);
char *ReadLine();
void PrintPlaylist(int index, Playlist **playlist, int *currentAmount, int key_menu);
void AddSong(Playlist **playlist, int index, int *currentSong);
void DisplaySongs(const int *currentSong, Playlist **playlist, int index);
void PlaySong(int song_key, Playlist **playlist, int index);
void Swap(Song *x, Song *y);
void SwapPlaylist(Playlist *x, Playlist *y);
void SortAlphabetically(Playlist **playlist, int index, const int *currentSong);
void SortYears(Playlist **playlist, int index, const int *currentSong);
void SortStreamsAscending(Playlist **playlist, int index, const int *currentSong);
void SortStreamsDescending(Playlist **playlist, int index, const int *currentSong);
void deleteSong(int index, int song_index, Playlist **playlist, int *currentSong);
void freeSong(int index, Playlist **playlist, int song_index);
void freePlaylist(int index, Playlist **playlist);
void sortPlaylist(int key_sort, Playlist **playlist, int index, int *currentSong);
void DeletePlaylist(int index, Playlist **playlist, int *currentAmount);
void DeleteEverything(const int *currentAmount, Playlist **playlist);


int main() {
    int key = 0;
    int currentAmount = 0;
    Playlist **playlist = malloc (currentAmount * sizeof(Playlist)); //i made array of struct... i think...
    if (playlist == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    do {
        printPlaylistsMenu();
        scanf("%d", &key);
        switch (key) {
            case WATCH: {
                DisplayPlaylists(&currentAmount, playlist, key);
                break;
            }
            case ADD: {
                AddPlaylist(&currentAmount, &playlist);
                break;
            }
            case REMOVE: {
                DisplayPlaylists(&currentAmount, playlist, key); //need to update display playlist for it not to go then to print playlist
                break;
            }
            case EXIT: { //add free all of playlists function and i'm golden
                DeleteEverything(&currentAmount, playlist);
                break;
            }
            default: { //idk what to do here you didn't write i think. not sure. need to check
                printf("Wrong input\n");
                break;
            }
        }
    }while(key != EXIT);
    printf("Goodbye!\n");  
}

void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}

void printSongsMenu() {
    printf("\t1. Show Playlist\n\
        2. Add Song\n\
        3. Delete Song\n\
        4. Sort\n\
        5. Play\n\
        6. exit\n");
}

void printSortMenu() {
    printf("choose:\n\
        1. sort by year\n\
        2. sort by streams - ascending order\n\
        3. sort by streams - descending order\n\
        4. sort alphabetically\n");
}

void CleanBuffer() {
    scanf("%*[^\n]");
    scanf("%*c");
}

void DisplayPlaylists(int *currentAmount, Playlist **playlist, int key_menu) { //need to input array of playlists
    int key = 0;
    printf("Choose a playlist:\n");
    if (*currentAmount == 0) {
        printf("\t1. Back to main menu\n");
        scanf("%d", &key);
        if (key == 1)
            return;
    }
    for (int i = 0, j = 0; i < *currentAmount; i++, j++) {
        printf("\t%d. %s\n", j + 1, playlist[i]->name);
    }
    printf("\t%d. Back to main menu\n", *currentAmount + 1);
    scanf("%d", &key);
    if (key == *currentAmount + 1)
        return;
    if (key_menu == WATCH && key != *currentAmount + 1)
        PrintPlaylist(key - 1, playlist, currentAmount, key_menu);
    else if (key_menu == REMOVE && key != *currentAmount + 1)
        DeletePlaylist(key - 1, playlist, currentAmount);
    //else new function about playlist that i need info about func(index) with switch inside
}

//if struc playlist name == NULL then print back to main menu
    //if struc playlist at least one then move back to main to option 2
    //i'm going to do fucking recursion here i swear to god

void AddPlaylist(int *currentAmount, Playlist ***playlist) {
    //allocate initial memory
    //when adding one more playlist here then to do realloc to memory + 1?
    *currentAmount = *currentAmount + 1;
    *playlist = realloc(*playlist, *currentAmount * sizeof(Playlist*)); //can i do that?
    if (*playlist == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    (*playlist)[*currentAmount- 1] = malloc(sizeof(Playlist));
    if ((*playlist)[*currentAmount- 1] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Enter playlist's name: \n");
    //do i need to do malloc on new name every time?
    //i need to do new function that reads line
    CleanBuffer(); //never forget alway remember
    (*playlist)[*currentAmount - 1]->name = ReadLine();
    if ((*playlist)[*currentAmount - 1]->name == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    (*playlist)[*currentAmount - 1]->songsNum = 0;
    ////am i doing this right chat? no i do not. BLYAT. after some considerations i think i do. nope. Finally i think yes
}

char *ReadLine() { //function to read new line  every time updaing it through realloc
    char *buffer = malloc(1); //new string
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    int length = 0;
    char ch;
    while (1) { //i WILL do it with recursion i swear
        scanf("%c", &ch);
        if (ch == '\n') //to not input \n in my string because printf goes brrr if i do
            break;
        buffer[length] = ch;//if initial length equals to buffer size then do one more realloc and till the end of string
        length++;
        char *temp  = realloc(buffer, length + 1);
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            free(buffer);
            exit(1);
        }
        buffer = temp;
    }
    buffer[length - 1] = '\0'; //end of line
    return buffer;
}

void PrintPlaylist(int index, Playlist **playlist, int *currentAmount, int key_menu) {
    //function with switch insides of playlist
    int currentSong = 0;
    int key = 0;
    //playlist[index]->songsNum = 0;
    printf("playlist %s:\n", playlist[index]->name);
    playlist[index]->songs = (Song**)malloc(currentSong * sizeof(Song*)); //not sure if i need sizeof songs?
    do {
        printSongsMenu();
        scanf("%d", &key);
        switch (key) {
            case 1: {
                int song_key = -1;
                if (currentSong == 0) {
                    printf("choose a song to play, or 0 to quit:\n");
                    scanf("%d", &song_key);
                    free(playlist[index]->songs);
                    PrintPlaylist(index, playlist, currentAmount, key_menu); //she's small but she's strong
                }
                DisplaySongs(&currentSong, playlist, index);
                while (1){
                    printf("choose a song to play, or 0 to quit:\n");
                    scanf("%d", &song_key);
                    if (song_key == 0 || song_key > currentSong)
                        break;
                    PlaySong(song_key - 1, playlist, index);
                }
                break;
            }
            case 2: {
                AddSong(playlist, index, &currentSong);
                break;
            }
            case 3: {
                int song_key = -1;
                if (currentSong == 0) {
                    printf("choose a song to play, or 0 to quit:\n");
                    scanf("%d", &song_key);
                    free(playlist[index]->songs);
                    PrintPlaylist(index, playlist, currentAmount, key_menu); //she's small but she's strong
                }
                DisplaySongs(&currentSong, playlist, index);
                printf("choose a song to delete, or 0 to quit:\n");
                scanf("%d", &song_key);
                deleteSong(index, song_key - 1, playlist, &currentSong);
                break;
            }
            case 4: {
                int key_sort = 0;
                printSortMenu();
                scanf("%d", &key_sort);
                sortPlaylist(key_sort, playlist, index, &currentSong);
                break;
            }
            case 5: {
                for (int i = 0; i < currentSong; i++) {
                    PlaySong(i, playlist, index);
                }
                break;
            }
            case 6: {
                DisplayPlaylists(currentAmount, playlist, key_menu);
                break;
            }
            default: {
                DisplayPlaylists(currentAmount, playlist, key_menu);
                break;
            }
        }

    }while (key != 6);
}

void AddSong(Playlist **playlist, int index, int *currentSong) {
    printf("Enter song's details \n");
    *currentSong = *currentSong + 1;
    printf("Title:\n");
    CleanBuffer();//never forgetting
    playlist[index]->songs = (Song**)realloc(playlist[index]->songs, *currentSong * sizeof(Song*)); //not sure if i need sizeof songs?
    playlist[index]->songs[*currentSong - 1] = (Song*)malloc(sizeof(Song)); //making memory for new song?
    if (playlist[index]->songs[*currentSong - 1] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    playlist[index]->songs[*currentSong - 1]->title = ReadLine();
    if (playlist[index]->songs[*currentSong - 1]->title == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Artist:\n");
    playlist[index]->songs[*currentSong - 1]->artist = ReadLine();
    if (playlist[index]->songs[*currentSong - 1]->artist == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Year of release:\n");
    scanf("%d", &playlist[index]->songs[*currentSong - 1]->year);\
    CleanBuffer();
    printf("Lyrics:\n");
    playlist[index]->songs[*currentSong - 1]->lyrics = ReadLine();
    if (playlist[index]->songs[*currentSong - 1]->lyrics == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    playlist[index]->songs[*currentSong - 1]->streams = 0;
    playlist[index]->songsNum++;
    //DO I NEED TO DO POINTER TO OTHER STRUCT AND THE DO OTHER STRUCR AS ARRAY? WHYYYYYYY
    //i have a pointer within this struct to another struct that means i need to do from this pointer array
    //and then to point within playlist array on songs array in song struct
    //i need to do array of songs pointers in this struct that points to song struct?
}

void DisplaySongs(const int *currentSong, Playlist **playlist, int index) {
    for (int i = 0, j = 0; i < *currentSong; i++, j++) {
        printf("%d. Title: %s\n", j+1, playlist[index]->songs[i]->title);
        printf("   Artist: %s\n", playlist[index]->songs[i]->artist);
        printf("   Released: %d\n", playlist[index]->songs[i]->year);
        printf("   Streams: %d\n", playlist[index]->songs[i]->streams);
    }
}

void PlaySong(int song_key, Playlist **playlist, int index) {//didn't need to clean buffer here :(
    printf("Now playing %s:\n", playlist[index]->songs[song_key]->title);
    printf("$ %s $\n", playlist[index]->songs[song_key]->lyrics);
    playlist[index]->songs[song_key]->streams++;
}

void sortPlaylist(int key_sort, Playlist **playlist, int index, int *currentSong) {
    switch (key_sort) {
        case 1: {
            SortYears(playlist, index, currentSong);
            break;
        }
        case 2: {
            SortStreamsAscending(playlist, index, currentSong);
            break;
        }
        case 3: {
            SortStreamsDescending(playlist, index, currentSong);
            break;
        }
        case 4: {
            SortAlphabetically(playlist, index, currentSong);
            break;
        }
        default: {
            SortAlphabetically(playlist, index, currentSong);
            break;
        }
    }
    printf("sorted\n");
}

void Swap(Song *x, Song *y) { //BEST FUNCTION EVAAAAAAAA
    const Song temp = *y;
    *y = *x;
    *x = temp;
}

void SwapPlaylist(Playlist *x, Playlist *y) {//also best function ever i think there is function like this inb some library but i'm not sure
    const Playlist temp = *y;
    *y = *x;
    *x = temp;
}

void SortAlphabetically(Playlist **playlist, int index, const int *currentSong) { //bubble sorts
    if (*currentSong == 0) {
        return;
    }
    //if first letter a then need to check second letter????
    //first letter of the first word then if the word equal or less then do nothing else swap tm
    for (int i = 0; i < *currentSong - 1; i++) {//4
        for (int j = 0; j < *currentSong - i - 1; j++) {
            if (strcmp(playlist[index]->songs[j]->title, playlist[index]->songs[j + 1]->title) > 0)
                Swap(playlist[index]->songs[j], playlist[index]->songs[j + 1]);
        }
    }
}

void SortYears(Playlist **playlist, int index, const int *currentSong) {
    if (*currentSong == 0) {
        return;
    }
    for (int i = 0; i < *currentSong - 1; i++) {
        for (int j = 0; j < *currentSong - i - 1; j++) {
            if (playlist[index]->songs[j]->year > playlist[index]->songs[j + 1]->year)
                Swap(playlist[index]->songs[j], playlist[index]->songs[j + 1]);
        }
    }
}

void SortStreamsAscending(Playlist **playlist, int index, const int *currentSong) {
    if (*currentSong == 0) {
        return;
    }
    for (int i = 0; i < *currentSong - 1; i++) {
        for (int j = 0; j < *currentSong - i - 1; j++) {
            if (playlist[index]->songs[j]->streams > playlist[index]->songs[j + 1]->streams)
                Swap(playlist[index]->songs[j], playlist[index]->songs[j + 1]);
        }
    }
}

void SortStreamsDescending(Playlist **playlist, int index, const int *currentSong) {
    if (*currentSong == 0) {
        return;
    }
    for (int i = 0; i < *currentSong - 1; i++) {
        for (int j = 0; j < *currentSong - i - 1; j++) {
            if (playlist[index]->songs[j]->streams < playlist[index]->songs[j + 1]->streams)
                Swap(playlist[index]->songs[j], playlist[index]->songs[j + 1]);
        }
    }
}

void deleteSong(int index, int song_index, Playlist **playlist, int *currentSong) {
    Swap(playlist[index]->songs[song_index], playlist[index]->songs[*currentSong - 1]);
    freeSong(index, playlist, *currentSong - 1);
    *currentSong = *currentSong - 1;
    playlist[index]->songsNum--;
    printf("Song deleted successfully.\n");

}

void freeSong(int index, Playlist **playlist, int song_index) {
    free(playlist[index]->songs[song_index]->title);
    free(playlist[index]->songs[song_index]->artist);
    free(playlist[index]->songs[song_index]->lyrics);
    free(playlist[index]->songs[song_index]);
}

void DeletePlaylist(int index, Playlist **playlist, int *currentAmount) {
    SwapPlaylist(playlist[index], playlist[*currentAmount - 1]);
    freePlaylist(*currentAmount - 1, playlist);
    *currentAmount = *currentAmount - 1;
    printf("Playlist deleted.\n");
}

void freePlaylist(int index, Playlist **playlist) { //add swap function to swap places with current playlist that i will always delete last
    if (playlist[index]->songsNum != 0) {
        for (int i = 0; i < playlist[index]->songsNum; i++) {//add current - 1
            free(playlist[index]->songs[i]);
        }
        free(playlist[index]->name);
        free(playlist[index]->songs);
    }
}

void DeleteEverything(const int *currentAmount, Playlist **playlist) {
    if (*currentAmount == 0)
        return;
    for (int i = 0; i < *currentAmount; i++) {
        freePlaylist(i, playlist);
    }
    free(*playlist);
    free(playlist);
}
