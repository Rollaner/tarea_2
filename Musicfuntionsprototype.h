#ifndef MUSICFUNTIONSPROTOTYPE_H_INCLUDED
#define MUSICFUNTIONSPROTOTYPE_H_INCLUDED

typedef struct song{
 char[50] name;
 char[50] artist;
 int length;
 list* albumList;
}song;

typedef struct album{
    char[50] name;
    char[50] date;
    map* album_songs;
}album;

typedef struct artist{
    char[50] name;
    list* songlist;
}artist;

map* import_musicCSV();                //lee datos de un archivo csv y los inserta al mapa songs

void export_musicCSV(map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, map* songMap);

void search_by_album(char* album, map* albumMap);

void add_song(char* title, char* artist, int length); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, map* albumMap); // crea un nuevo album

void search_by_artist(char* name, map* artistMap);

void delete_artist(char* name, map* artistMap);
#endif // MUSICFUNTIONSPROTOTYPE_H_INCLUDED
