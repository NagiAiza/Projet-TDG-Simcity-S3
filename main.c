#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

void initialisation_allegro() {    ///Initialisation pour Allegro
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,678,0,0)!=0) {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

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

int main()
{
    //declaration BITMAP devant recevoir l'image

    // SuperCool
    BITMAP* debut_projet;
    // barre de chargement
    BITMAP* chargement[17];
    char tableauChargement[14];
    // COMMENCER/CONTINUER/QUITTER
    BITMAP* image;
    BITMAP* prop1;
    BITMAP* prop2;
    BITMAP* prop3;
    // BILOU/CAPITALISTE
    BITMAP* Image;
    BITMAP* prop4;
    BITMAP* prop5;


    //Lancer allegro et le mode graphique
    initialisation_allegro();

    // pour voir le pointeur de la souris
    show_mouse(screen);

    debut_projet=load_bitmap_check("debut_projet.bmp");


    ///Tableau d'image
    for (int i=0 ; i<=16 ; i++)
    {
        printf ("--> tg %d\n",i);
        sprintf(tableauChargement, "chargement%d.bmp",i);
        chargement[i]=load_bitmap(tableauChargement,NULL);
        //blindage
        if(!chargement[i])
        {
            allegro_message("pas pu trouver %s", tableauChargement);
            exit(EXIT_FAILURE);
        }
    }

    // Chargement de l'image (l'allocation a lieu en même temps)
    image=load_bitmap_check("mon_image.bmp");

    prop1=load_bitmap_check("prop1.bmp");

    prop2=load_bitmap_check("prop2.bmp");

    prop3=load_bitmap_check("prop3.bmp");

    Image=load_bitmap_check("mon_image2.bmp");

    prop4=load_bitmap_check("prop4.bmp");

    prop5=load_bitmap_check("prop5.bmp");


    blit(debut_projet,screen,0,0,SCREEN_W-debut_projet->w,SCREEN_H-debut_projet->h, debut_projet->w, debut_projet->h);
    rest(2000);

    printf ("ruig^rgh\n");
    //affichage d'un tableau d'image
    for (int i=1 ; i<16 ; i++)
    {
        printf("%d\n",i);
        blit(chargement[i],screen,0,0, (SCREEN_W-chargement[i]->w)/2, (SCREEN_H-chargement[i]->h)/2, chargement[i]->w, chargement[i]->h);
        rest(100);
    }
    blit(chargement[16],screen,0,0,SCREEN_W-chargement[16]->w,SCREEN_H-chargement[16]->h, chargement[16]->w, chargement[16]->h);
    rest(1000);

    //boucle
    while (!key[KEY_ESC])
    {
        //Affichage
        blit(image,screen,0,0,SCREEN_W-image->w,SCREEN_H-image->h, image->w, image->h);

        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
        //textprintf_ex(screen,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

        if (mouse_x>=391 && mouse_x<=607 && mouse_y>=87 && mouse_y<=154)
        {
            blit(prop1,screen,0,0,SCREEN_W-prop1->w,SCREEN_H-prop1->h, prop1->w, prop1->h);
            rest(100);
            if (mouse_b&1)
            {
                printf ("COMMENCER\n");
                rest(500);
                while (!key[KEY_ESC])
                {
                    //textprintf_ex(screen,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

                    blit(Image,screen,0,0, SCREEN_W-Image->w,SCREEN_H-Image->h, Image->w, Image->h);
                    if (mouse_x>=227  && mouse_x<=444 && mouse_y>=290   && mouse_y<= 357)
                    {
                        blit(prop4,screen,0,0, SCREEN_W-prop4->w,SCREEN_H-prop4->h, prop4->w, prop4->h);
                        rest(100);
                        if (mouse_b&1)
                        {
                            printf ("communiste\n");
                            rest(500);
                        }
                    }
                    else if (mouse_x>=582 && mouse_x<=800&& mouse_y>=290   && mouse_y<=357 )
                    {
                        blit(prop5,screen,0,0, SCREEN_W-prop5->w,SCREEN_H-prop5->h, prop5->w, prop5->h);
                        rest(100);
                        if (mouse_b&1)
                        {
                            printf ("capitaliste\n");
                            rest(500);
                        }
                    }

                }

            }

        }
        else if (mouse_x>=391 && mouse_x<=607 && mouse_y>=293 && mouse_y<=361)
        {
            blit(prop2,screen,0,0,SCREEN_W-prop2->w,SCREEN_H-prop2->h, prop2->w, prop2->h);
            rest(100);
            if (mouse_b&1)
            {
                printf ("CONTINUER\n");
                rest(500);
            }
        }
        else if (mouse_x>=391 && mouse_x<=607 && mouse_y>=500 && mouse_y<=566)
        {
            blit(prop3,screen,0,0,SCREEN_W-prop3->w,SCREEN_H-prop3->h, prop3->w, prop3->h);
            rest(100);
            if (mouse_b&1)
            {
                printf ("QUITTER\n");
                rest(500);
                allegro_exit();
            }
        }

    }
    allegro_exit();
    return 0;
}
END_OF_MAIN();
