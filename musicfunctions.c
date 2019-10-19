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
    Map* album_songs;           //puede ser una lista tambien, pero puesto que hay que asegurarse de cosas
}album;


typedef struct artist{
    char* name;
    list* songlist;             //posee punteros a los struct song del artista (!) o  bien los titulos de las canciones y llama al mapa
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
    FILE* fp = fopen("mdata\\canciones.csv","r");                   //luego añade la cancion a la lsita del artista correspondiente
    char* String = calloc(100,sizeof(char));                    //y crea un artista nuevo de ser necesario
    char* key = calloc(50, sizeof(char));                       //ademas crea los albumes ya pre-escritos y los rellena
    int i;
    song* newSong = malloc(sizeof(song));
    fgets(String,100,fp);
    while(fgets(String,100,fp)!= NULL){
        newSong->name = get_csv_field(String,1);
        newSong->artist = get_csv_field(String,2);
        newSong->length = get_csv_field(String,3);
        newSong->album = get_csv_field(String,4);
        key = get_csv_field(String,1);
        for(i=0; i<50; i++){
            if (isupper(key[i])&&(isdigit(key[i]) == 0)){
                key[i] = (char) tolower(key[i]);
            }
        }                                       //convierte titulo a minuscula para facilitar busqueda.
        insertMap(songMap, key, newSong);
        key = get_csv_field(String,2);
        for(i=0; i<50; i++){
            if (isupper(key[i])&&(isdigit(key[i]) == 0)){
                key[i] = (char) tolower(key[i]);
            }
        }
    }
    fclose(fp);
};

void export_musicCSV(Map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap){
    song* currentSong;
    int i;
    for(i=0; i<50; i++){
            if (isupper(title[i])&&(isdigit(title[i]) == 0)){
                title[i] = (char) tolower(title[i]);
            }
    }                                       // convierte a minuscula para facilitar busquedas.
    currentSong = searchMap(songMap,title);
    if (currentSong == NULL){
        printf ("Cancion ingresada no existe, por favor intente nuevamente \n");
        return;
    }
    printf("%s %s %s %s \n",currentSong->name, currentSong->artist, currentSong->length, currentSong->album);
};

void search_by_album(char* album, Map* albumMap);   //recorrer mapa album

void add_song(char* title, char* artist, int length); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, Map* albumMap); // crea un nuevo album

void search_by_artist(char* name, Map* artistMap){          // mostrar lista artista
    artist* currentArtist = searchMap(artistMap,name);


};

void delete_artist(char* name, Map* artistMap);             //borra canciones primero, despues al artista
