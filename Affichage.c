//
// Created by alexi on 01/11/2022.
//

#include "Affichage.h"
#include "barre_outil.h"

//simplification du code pour load une bitmap avec une erreur si pb
BITMAP * load_bitmap_check(char *nomImage){
    BITMAP *bmp;
    bmp=load_bitmap(nomImage,NULL);
    if (!bmp)
    {
        allegro_message("pas pu trouver %s",nomImage);
        exit(EXIT_FAILURE);
    }
    return bmp;
}

IMAGE* initialisation_liste_image()
{
    IMAGE* liste=(IMAGE*)malloc(sizeof(IMAGE));
    liste->menu= load_bitmap_check("test_ecran.bmp");
    liste->map= load_bitmap_check("damierTestProvisoire.bmp");
    liste->sous_map= load_bitmap_check("damierFond.bmp");
    liste->route = load_bitmap_check("route.bmp");
    return liste;
}

BUFFER* initialisation_liste_buffer()
{
    BUFFER* liste=(BUFFER*)malloc(sizeof(BUFFER));
    liste->buffer_menu=create_bitmap(900, 700);
    clear_bitmap(liste->buffer_menu);

    liste->buffer_map= create_bitmap(1120, 640);
    clear_bitmap(liste->buffer_map);

    liste->buffer_final= create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(liste->buffer_final);

    return liste;
}

void liberation_memoire_bitmaps(IMAGE* liste_image, BUFFER* liste_buffer)
{
    destroy_bitmap(liste_image->map);
    destroy_bitmap(liste_image->menu);
    destroy_bitmap(liste_image->route);
    destroy_bitmap(liste_image->sous_map);
    free(liste_image);
    destroy_bitmap(liste_buffer->buffer_map);
    destroy_bitmap(liste_buffer->buffer_menu);
    destroy_bitmap(liste_buffer->buffer_final);
}

t_pos calcul_pos_souris(BITMAP* sousMap, int decalageScreenX/*pour savoir où placer la bitmap*/)//retourne la position de la souris
{
    t_pos souris;
    souris.ligne=getb(getpixel(sousMap, mouse_x+decalageScreenX-124, mouse_y));
    souris.colonne=getr(getpixel(sousMap, mouse_x+decalageScreenX-124, mouse_y));
    return souris;
}

//affichage de la case selectionné, pas utile en soit mais ça permettra de bien placer les sprites avec la formule
void affichageCaseSelec(BITMAP* map, BITMAP* selec, t_pos souris)//R correspond à la colonne, B à la ligne
{
    draw_sprite(map, selec, (SCREEN_W/2-36)+souris.colonne*14-souris.ligne*14, souris.colonne*8+souris.ligne*8);
}

void affichageElement(BITMAP* bufferMap, BITMAP* route, int type, int ligne, int colonne)
{
    switch (type) {
        case 1:
            draw_sprite(bufferMap, route, (SCREEN_W/2-36)+colonne*14-ligne*14, colonne*8+ligne*8);
            break;
        case 2:
            //habitation
            break;
        case 3:
            //Chateau Deau;
            break;
    }
}

void affichageElementsCarte(BITMAP* bufferMap, BITMAP* route)//et toute les autres bitmap de batiments
{
    FILE* elementMap=fopen("element_map.txt", "r");//pour la nouvelle partie tout les elements sont à 0
    int type=0;
    for(int i=0; i<NBLIGNE; i++)
    {
        for(int j=0; j<NBCOLONNE; j++)
        {
            fscanf(elementMap, "%d", &type);
            affichageElement(bufferMap, route, type, i, j);
        }
    }
    fclose(elementMap);
}


void affichageTotal(t_graphe* map)//doit etre independant du jeu en lui meme
{
    int choix;
    int screenx; // Position de l'écran réel dans le repère du décor...
    t_pos souris;
    souris.ligne=0;
    souris.colonne=0;

    initialisationElementCarte();//genere le fichier

    //on genere les BITMAPs que l'on va utiliser

    IMAGE* liste_image=initialisation_liste_image();
    BUFFER* liste_buffer=initialisation_liste_buffer();

    // Ici initialisation du scrolling en haut à gauche du décor
    //  (on peut décider de partir autrement...)
    screenx=0;

    while (!key[KEY_ESC])
    {
        clear(liste_buffer->buffer_menu);
        clear_bitmap(liste_buffer->buffer_map);

        if (key[KEY_RIGHT])   screenx+=5;
        if (key[KEY_LEFT] )   screenx-=5;

        if ( screenx < 0 ) screenx=0;
        if ( screenx > liste_buffer->buffer_map->w - SCREEN_W +124) screenx=liste_buffer->buffer_map->w - SCREEN_W+124;

        blit(liste_image->menu, liste_buffer->buffer_menu, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        //blit(map, buffer2, 0, 0, 0, 0, map->w, map->h);

        draw_sprite(liste_buffer->buffer_map, liste_image->map, 0, 0);

        affichageElementsCarte(liste_buffer->buffer_map, liste_image->route);

        textprintf_ex(liste_buffer->buffer_map,font,10,10,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        textprintf_ex(liste_buffer->buffer_map,font,10,20,makecol(0,255,0),makecol(0,0,0),"case[%d][%d]",souris.ligne,souris.colonne);
        affichageElementsCarte(liste_buffer->buffer_map, liste_image->route);//juste mettre la liste d'image
        blit(liste_buffer->buffer_menu, liste_buffer->buffer_final, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if(mouse_b & 1)
        {

            if(mouse_x<124 || mouse_y>640)
            {
                choix = action(liste_buffer->buffer_final);
                rest(100);
            }
        }

        if(choix==1)
        {
            if(mouse_x>124 && mouse_y<640)
            {
                souris= calcul_pos_souris(liste_image->sous_map, screenx);
            }
            if(souris.ligne<35 && souris.colonne<45)
            {
                draw_sprite(liste_buffer->buffer_map, liste_image->route, (SCREEN_W/2-36)+souris.colonne*14-souris.ligne*14, souris.colonne*8+souris.ligne*8);
                if(mouse_b & 1)
                {
                    map = placementElement(map, souris.ligne, souris.colonne, choix);
                    choix=0;

                }
            }

        }
        blit(liste_buffer->buffer_map, liste_buffer->buffer_final, screenx, 0, 124, 0, SCREEN_W, SCREEN_H);

        show_mouse(liste_buffer->buffer_final);

        blit(liste_buffer->buffer_final, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    show_mouse(NULL);
    liberation_memoire_bitmaps(liste_image, liste_buffer);

}