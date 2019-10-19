#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "musicfunctions.h"
#include "list.h"
#include "Map.h"

typedef struct song{
 char* name;
 char* artist;
 char* length;
 char* album;
}song;

typedef struct album{
    char* name;
    char* date;
    Map* album_songs;
}album;


typedef struct artist{
    char* name;
    list* songlist;
}artist;

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

void import_musicCSV(Map* songMap, Map* artistMap){                     //lee datos de un archivo csv y los inserta al mapa songs
    FILE* fp = fopen("mdata\\canciones.csv","r");
    char* String = calloc(100,sizeof(char));
    fgets(String,100,fp);
    while(fgets(String,100,fp)!= NULL){
        song* newSong = malloc(sizeof(song));
        newSong->name = get_csv_field(String,1);
        newSong->artist = get_csv_field(String,2);
        newSong->length = get_csv_field(String,3);
        newSong->album = get_csv_field(String,4);
        insertMap(songMap, newSong->name, newSong);
    }
    fclose(fp);
};

void export_musicCSV(Map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap){
    song* currentSong;
    currentSong = searchMap(songMap,title);
    printf("%s %s %s %s \n",currentSong->name, currentSong->artist, currentSong->length, currentSong->album);
};

void search_by_album(char* album, Map* albumMap);

void add_song(char* title, char* artist, int length); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, Map* albumMap); // crea un nuevo album

void search_by_artist(char* name, Map* artistMap){
    song* currentSong = searchMap(artistMap,name);
    printf("%s %s %s %s \n",currentSong-> name, currentSong->artist, currentSong-> length, currentSong->album);
};

void delete_artist(char* name, Map* artistMap);
