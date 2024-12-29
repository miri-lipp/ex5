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
void printPlaylistsMenu();
void printSongsMenu();
void DisplayPlaylists(int currentAmount, const Playlist *playlist);
void AddPlaylist(int *currentAmount, Playlist **playlist);
char *ReadLine();
void PrintPlaylist(int index, Playlist **playlist);
void AddSong(Playlist **playlist, int index, int *currentSong);

void deleteSong() {

    printf("Song deleted successfully.\n");
}



void playSong() {
    
}



void freeSong() {

}

void freePlaylist() {
    
}




void sortPlaylist() {
    
    printf("sorted\n");
}



int main() {
    int key = 0;
    int currentAmount = 0;
    Playlist *playlist = malloc (currentAmount * sizeof(Playlist)); //i made array of struct... i think...
    do {
        printPlaylistsMenu();
        scanf("%d", &key);
        switch (key) {
            case WATCH: {
                DisplayPlaylists(currentAmount, playlist);
                break;
            }
            case ADD: {
                AddPlaylist(&currentAmount, &playlist);
                break;
            }
            case REMOVE: {
                printf("%d current amount\n", currentAmount);
                break;
            }
            case EXIT: {
                break;
            }
            default: {
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
    printf("\t1. Show Playlist\n\t\
    2. Add Song\n\t\
    3. Delete Song\n\t\
    4. Sort\n\t\
    5. Play\n\t\
    6. Back\n");
}

void DisplayPlaylists(int currentAmount, const Playlist *playlist) { //need to input array of playlists
    int key = 0;
    printf("Choose a playlist:\n");
    if (currentAmount == 0) {
        printf("\t1. Back to main menu\n");
        scanf("%d", &key);
        if (key == 1)
            return;
    }
    for (int i = 0, j = 0; i < currentAmount; i++, j++) {
        printf("\t%d. %s\n", j + 1, playlist[i].name);
    }
    printf("\t%d. Back to main menu\n", currentAmount + 1);
    scanf("%d", &key);
    if (key == currentAmount + 1)
        return;
    PrintPlaylist(key - 1, &playlist);
    //else new function about playlist that i need info about func(index) with switch inside
}

//if struc playlist name == NULL then print back to main menu
    //if struc playlist at least one then move back to main to option 2
    //i'm going to do fucking recursion here i swear to god

void AddPlaylist(int *currentAmount, Playlist **playlist) {
    //allocate initial memory
    //when adding one more playlist here then to do realloc to memory + 1?
    *currentAmount = *currentAmount + 1;
    *playlist = realloc(*playlist, *currentAmount * sizeof(Playlist)); //can i do that?
    if (*playlist == NULL) {
        printf("Memory allocation failed.\n");
    }
    printf("Enter playlist's name: \n");
    //do i need to do malloc on new name every time?
    //i need to do new function that reads line
    scanf("%*c"); //never forget alway remember
    (*playlist)[*currentAmount - 1].name = ReadLine();
    ////am i doing this right chat? no i do not. BLYAT. after some considerations i think i do. nope. Finally i think yes
}

char *ReadLine() { //function to read new line  every time updaing it through realloc
    char *buffer = malloc(sizeof(char)); //new string
    int length = 0;
    char ch;
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
    }
    while (ch != '\n') { //i WILL do it with recursion i swear
        scanf("%c", &ch);
        buffer[length] = ch;
        if (length == sizeof(buffer)) { //if initial length equals to buffer size then do one more realloc and till the end of string
            buffer = realloc(buffer, length * sizeof(char));
            if (buffer == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
        }
        length++;
    }
    buffer[length] = '\0'; //end of line
    return buffer;
}

void PrintPlaylist(int index, Playlist **playlist) {
    //function with switch insides of playlist
    int currentSong = 0;
    int key = 0;
    printf("playlist %s\n", playlist[index]->name);
    playlist[index]->songs = malloc(currentSong * sizeof(Song*)); //not sure if i need sizeof songs?
    do {
        printSongsMenu();
        scanf("%d", &key);
        switch (key) {
            case '1': {
                break;
            }
            case 2: {
                AddSong(playlist, index, &currentSong);
                break;
            }
            case '3': {
                break;
            }
            case '4': {
                break;
            }
            case '5': {
                break;
            }
            case '6': {
                break;
            }
            default: {
                break;
            }
        }

    }while (key != 6);
}

void AddSong(Playlist **playlist, int index, int *currentSong) {
    printf("Enter song's details \n");
    *currentSong = *currentSong + 1;
    printf("Title:\n");
    scanf("%*c");//never forgetting
    playlist[index]->songs = realloc(playlist[index]->songs, *currentSong * sizeof(Song*)); //not sure if i need sizeof songs?
    if (playlist[index]->songs == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    playlist[index]->songs[*currentSong - 1]->title = ReadLine();
    printf("Artist:\n");
    scanf("%*c");
    playlist[index]->songs[*currentSong - 1]->artist = ReadLine();
    printf("Year of release:\n");
    scanf("%d", playlist[index]->songs[*currentSong - 1]->year);
    printf("Lyrics:\n");
    scanf("%*c");
    playlist[index]->songs[*currentSong - 1]->lyrics = ReadLine();
    //DO I NEED TO DO POINTER TO OTHER STRUCT AND THE DO OTHER STRUCR AS ARRAY? WHYYYYYYY
    //i have a pointer within this struct to another struct that means i need to do from this pointer array
    //and then to point within playlist array on songs array in song struct
    //i need to do array of songs pointers in this struct that points to song struct?
}