#include <stdio.h>
#include <allegro.h>
#include "menu.h"
#include "moteur_du_jeu.h"

//lien du git
//https://github.com/NagiAiza/Projet-TDG-Simcity

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

int main() {
    //variable qui reçoit le mode souhaite //
    int Mode_de_Jeu=1;
    int nvlle_partie=0;

    ///importation de la musique de fond
    SAMPLE* music=load_sample("musique.wav");
    if(music==NULL){
        printf("Erreur le dossier << musique >> (format .wav) n'a pas ete trouvee");
    }

    initialisation_allegro();


    //Sous-programme menu
    musique(music);//on lance la musique
    Mode_de_Jeu = menu(&nvlle_partie); //si 1 communiste si 2 capitaliste, 1 en paramètre si nouvelle partie
    intro_du_jeu();//petite intro
    //Sous-programme jeu
    jeu(&Mode_de_Jeu, nvlle_partie);


    allegro_exit();
    return 0;
}END_OF_MAIN();

