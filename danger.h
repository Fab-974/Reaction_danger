#ifndef DANGER_H
#define DANGER_H

#include <time.h>

// Taux de freinage entre 0 et 1; 0 etant aucun freinage
// priorite de 1 A 100  (1 etant la plus prioritaire)
// envoye = 1 si le message a ete envoye
typedef enum action {deceleration,freinage } action; 

typedef struct coordonnee { float latitude;float longitude;float altitude;} coordonnee;

typedef struct msg {int priorite; float vitesse;coordonnee position; time_t heure; float distance;int envoye;} msg;

typedef struct CSC_rep{float taux_freinage;action act; msg danger;} CSC_rep;

msg send_cc(msg danger);

void init_msg(msg m,float d, float tf,float v,coordonnee c);

extern CSC_rep Chassy_safety_controller(float d, float tf,float v,coordonnee c);

#endif /* DANGER_H */
