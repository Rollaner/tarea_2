#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "musicfunctions.h"
#include "list.h"
#include "Map.h"

struct song{
 char* name;
 char* artistName;
 char* length;
 char* albumName;
};

struct album{
    char* name;
    Map* album_songs;
};

struct artist{
    list* songlist;
};

char * _strdup (const char *s) {
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

void import_musicCSV(Map* songMap, Map* artistMap, Map* albumMap){                     //lee datos de un archivo csv y los inserta al mapa songs
    FILE* fp = fopen("mdata\\canciones.csv","r");                   //luego añade la cancion a la lsita del artista correspondiente
    char* String = calloc(100,sizeof(char));                    //y crea un artista nuevo de ser necesario, ademas crea los albumes ya pre-escritos y los rellena
    fgets(String,100,fp);
    while(fgets(String,100,fp)!= NULL){
        song* newSong = new_song(String);
        insertMap(songMap, newSong->name, newSong);
        artist* currentArtist = searchMap(artistMap,newSong->artistName);
        if(currentArtist == NULL){
            currentArtist = malloc(sizeof(artist));
            currentArtist->songlist = list_create_empty();
            list_push_front(currentArtist->songlist,newSong);
            insertMap(artistMap,newSong->artistName,currentArtist);
        }else{
            list_push_front(currentArtist->songlist,newSong);
        }
        album * currentAlbum = searchMap(albumMap, newSong->albumName);
        if(currentAlbum == NULL){
            currentAlbum = malloc(sizeof(album));
            currentAlbum->name = calloc(30, sizeof(char));
            strcpy(currentAlbum->name,newSong->albumName);
            currentAlbum->album_songs = createMap(stringHash,stringEqual);
            insertMap(currentAlbum->album_songs,newSong->name,newSong);
            insertMap(albumMap,newSong->albumName,currentAlbum);
        }else{
            insertMap(currentAlbum->album_songs,newSong->name,newSong);
        }
    }
    fclose(fp);
    return;
}

song* new_song(char* String){
        song* newSong = malloc(sizeof(song));
        newSong->name = calloc(50,sizeof(char));
        newSong->albumName = calloc(50,sizeof(char));
        newSong->artistName = calloc(50,sizeof(char));
        newSong->length = calloc(6,sizeof(char));
        strcpy(newSong->name,get_csv_field(String,1));
        strcpy(newSong->artistName,get_csv_field(String,2));
        strcpy(newSong->length,get_csv_field(String,3));
        strcpy(newSong->albumName,get_csv_field(String,4));
        return newSong;
}

void export_musicCSV(Map* songs){
    song* currentSong = firstKeyMap(songs);
    FILE* fp = fopen("mdata\\cancionesOUTPUT.csv","w");
    fprintf(fp,"Nombre,Artista,Duracion,Album\n");
    while(currentSong != NULL){
     fprintf(fp,"%s,%s,%s,%s\n",currentSong->name,currentSong->artistName,currentSong->length,currentSong->albumName);
     currentSong = nextKeyMap(songs);
    }
    fclose(fp);
};      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap){
    song* currentSong = searchMap(songMap,title);
    if (currentSong == NULL){
       printf ("Cancion ingresada no existe, por favor intente nuevamente \n");
       return;
    }
    printf("%s %s %s %s \n",currentSong->name, currentSong->artistName, currentSong->length, currentSong->albumName);
}

void search_by_album(char* name, Map* albumMap){
    album* currentAlbum;
    currentAlbum = searchMap(albumMap,name);
    if (currentAlbum == NULL){
       printf ("Album ingresado no existe, por favor intente nuevamente \n");
       return;
    }
    else{
        song* currentSong = firstMap(currentAlbum->album_songs);
        printf("%s \n", currentSong->albumName);
        while(currentSong != NULL){
            printf("%s %s %s\n",currentSong->name, currentSong->artistName, currentSong->length);
            currentSong = nextMap(currentAlbum->album_songs);
        }
    }
}   //recorrer mapa album

void add_song(char* title, char* songArtist, char* length, char* songAlbum, Map* songMap, Map* artistMap, Map* albumMap){
    song* newSong = malloc(sizeof(song));
        newSong->name = calloc(50,sizeof(char));
        strcpy(newSong->name,title);
        newSong->artistName = calloc(50,sizeof(char));
        strcpy(newSong->artistName,songArtist);
        newSong->length = calloc(6,sizeof(char));
        strcpy(newSong->length,length);
        newSong->albumName = calloc(50,sizeof(char));
        strcpy(newSong->albumName,songAlbum);
        insertMap(songMap,newSong->name,newSong);
    album* addAlbum = searchMap(albumMap,songAlbum);
        if(addAlbum == NULL){
            addAlbum = malloc(sizeof(album));
            addAlbum->album_songs = createMap(stringHash,stringEqual);
            insertMap(addAlbum->album_songs,newSong->name,newSong);
            insertMap(albumMap,newSong->albumName,addAlbum);
        }
        else{
            insertMap(addAlbum->album_songs,newSong->name,newSong);
        }
    artist* addArtist = searchMap(artistMap, songArtist);
        if(addArtist == NULL){
            addArtist = malloc(sizeof(artist));
            addArtist->songlist = list_create_empty();
            list_push_front(addArtist->songlist,newSong);
            insertMap(artistMap,newSong->artistName,addArtist);
        }
        else{
            list_push_front(addArtist->songlist,newSong);
        }
        return;
}

void add_album(char* name, Map* albumMap, Map* songMap){
    album* currentAlbum = searchMap(albumMap,name);
    char Answer;
    if (currentAlbum != NULL){
        printf("Album ya existe, desea agregar mas canciones? Y/N \n");
        while(Answer != 'n'){
            scanf("%c", &Answer);
            if(isupper(Answer)){
                Answer = tolower(Answer);
            }
            if(Answer == 'y'){
                printf("Ingrese nombre cancion: \n");
                    char* title = calloc(30,sizeof(char));
                    fgets(title,10,stdin);
                    fgets(title,30,stdin);
                    if ((strlen(title) > 0) && (title[strlen (title) - 1] == '\n'))
                        title[strlen (title) - 1] = '\0';
                    song* songAdd = searchMap(songMap,title);
                    if(songAdd == NULL){
                        printf("Cancion no esta presente en el archivo, porfavor ingrese su cancion e intente nuevamente \n");
                        printf("Desea agregar otra cancion? Y/N \n");
                        continue;
                    }
                    strcpy(songAdd->albumName, name);
                    insertMap(currentAlbum->album_songs,songAdd->name,songAdd);
                printf("Desea agregar otra cancion? Y/N \n");
            }
        }
    }else{
        currentAlbum = malloc(sizeof(album));
        strcpy(currentAlbum->name, name);
        currentAlbum->album_songs = createMap(stringHash,stringEqual);
        insertMap(albumMap,currentAlbum->name,currentAlbum);
        printf("Desea agregar canciones al album creado? Y/N \n");
        while(Answer != 'n'){
            scanf("%c", &Answer);
            if(isupper(Answer)){
                Answer = tolower(Answer);
            }
            if(Answer == 'y'){
                printf("Ingrese nombre cancion: \n");
                    char* songTitle = calloc(30,sizeof(char));
                    fgets(songTitle,10,stdin);
                    fgets(songTitle,30,stdin);
                    if ((strlen(songTitle) > 0) && (songTitle[strlen (songTitle) - 1] == '\n'))
                        songTitle[strlen (songTitle) - 1] = '\0';
                    song* songAdd = searchMap(songMap,songTitle);
                    if(songAdd == NULL){
                        printf("Cancion no esta presente en el archivo, porfavor ingrese su cancion e intente nuevamente \n");
                        printf("Desea agregar otra cancion? Y/N \n");
                        continue;
                    }
                    songAdd->albumName = currentAlbum->name;
                    insertMap(currentAlbum->album_songs,songAdd->name,songAdd);
                printf("Desea agregar otra cancion? Y/N \n");
            }
        }
    }
    return;
} // crea un nuevo album

void search_by_artist(char* nameArtist, Map* artistMap){
    artist* currentArtist = searchMap(artistMap,nameArtist);
    if (currentArtist == NULL){
        printf("Artista no encontrado, intente nuevamente \n");
        return;
    }
    song* currentSong = list_first(currentArtist->songlist);
    while(currentSong != NULL){
        printf("%s ", currentSong->name);
        printf("%s  %s \n", currentSong->albumName, currentSong->length);
        currentSong = list_next(currentArtist->songlist);
    }
    return;
}

void delete_artist(char* name, Map* artistMap, Map* songMap, Map* albumMap){
    artist* currentArtist = searchMap(artistMap,name);
    if(currentArtist == NULL){
     printf("Artista no existe, revise datos ingresados \n");
    }
    else{
        song* currentSong = list_pop_front(currentArtist->songlist);
        album* currentAlbum = searchMap(albumMap, currentSong->albumName);
        while  (currentSong != NULL){
                free(eraseKeyMap(currentAlbum->album_songs,currentSong->name));
                free(eraseKeyMap(songMap,currentSong->name));
                if(strcmp(currentSong->albumName,currentAlbum->name)!= 0)
                    free(eraseKeyMap(albumMap,currentAlbum->name));
                currentSong = list_pop_front(currentArtist->songlist);
                }
        free(eraseKeyMap(albumMap,currentAlbum->name));
        free(eraseKeyMap(artistMap,name));
        free(currentArtist);
    }
}             //borra canciones primero, despues al artista
