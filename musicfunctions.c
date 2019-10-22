#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "musicfunctions.h"
#include "list.h"
#include "Map.h"

struct song{
 char* name;
 char* artist;
 char* length;
 char* album;
};

struct album{
    //char* name;
    char* date;
    Map* album_songs;           //puede ser una lista tambien, pero puesto que hay que asegurarse de cosas
};

struct artist{
    //const char* name;
    list* songlist;             //posee punteros a los struct song del artista (!) o  bien los titulos de las canciones y llama al mapa
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
        printf("%ld \n", mapCount(songMap));
        artist* currentArtist = searchMap(artistMap,newSong->artist);
        if(currentArtist == NULL){
            currentArtist = malloc(sizeof(artist));
            currentArtist->songlist = list_create_empty();
            list_push_front(currentArtist->songlist,newSong);
            insertMap(artistMap,newSong->artist,currentArtist);
        }else{
            list_push_front(currentArtist->songlist,newSong);
        }
        album * currentAlbum = searchMap(albumMap, newSong->album);
        if(currentAlbum == NULL){
            currentAlbum = malloc(sizeof(album));
            currentAlbum->album_songs = createMap(stringHash,stringEqual);
            insertMap(currentAlbum->album_songs,newSong->name,newSong);
            //strcpy(currentAlbum->name,newSong->album);
        }else{
            insertMap(currentAlbum->album_songs,newSong->name,newSong);
        }
    }
    fclose(fp);
    return;
};

song* new_song(char* String){
        song* newSong = malloc(sizeof(song));
        newSong->name = get_csv_field(String,1);
        newSong->artist = get_csv_field(String,2);
        newSong->length = get_csv_field(String,3);
        newSong->album = get_csv_field(String,4);
        return newSong;
}

void export_musicCSV(Map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap){
    song* currentSong = searchMap(songMap,title);
    if (currentSong == NULL){
       printf ("Cancion ingresada no existe, por favor intente nuevamente \n");
       return;
    }
    printf("%s %s %s %s \n",currentSong->name, currentSong->artist, currentSong->length, currentSong->album);
};

void search_by_album(char* album, Map* albumMap);   //recorrer mapa album

void add_song(char* title, char* artist, int length); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, Map* albumMap); // crea un nuevo album

void search_by_artist(char* name, Map* artistMap){
    artist* currentArtist = searchMap(artistMap,name);
    if (currentArtist == NULL){
        printf("Artista no encontrado, intente nuevamente \n");
        return;
    }
    song* currentSong = list_first(currentArtist->songlist);
    printf("%s \n", currentSong->artist);
    while(list_next(currentArtist->songlist) != NULL){
        printf("%s ", currentSong->name);
        printf("%s  %s \n", currentSong->album, currentSong->length);
        currentSong = list_next(currentArtist->songlist);
    }
    return;
};

void delete_artist(char* name, Map* artistMap);             //borra canciones primero, despues al artista
