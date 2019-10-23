#ifndef musicfunctions_h
#define musicfunctions_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"

typedef struct song song;

typedef struct album album;

typedef struct artist artist;

char * _strdup (const char *s);

const char *get_csv_field (char * tmp, int i);

long long stringHash(const void * key);

int stringEqual(const void * key1, const void * key2);

void import_musicCSV(Map* songMap, Map* artistMap, Map* albumMap);                //lee datos de un archivo csv y los inserta al mapa songs

void export_musicCSV(Map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap);

void search_by_album(char* album, Map* albumMap);

song* new_song(char* String);

void add_song(char* title, char* artist, char* length, char* songAlbum); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, Map* albumMap); // crea un nuevo album

void search_by_artist(char* name, Map* artistMap);

void delete_artist(char* name, Map* artistMap);

#endif // musicfunctions_h //
