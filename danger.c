#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "danger.h"

msg send_cc(msg danger){
  return danger;
}

void init_msg(msg m,float d, float tf,float v,coordonnee c){
    time_t now;
    m.vitesse=v;
    m.position=c;
    m.heure=time(&now);
    m.distance=d;
    m.priorite=0;
    m.envoye=0;

}

CSC_rep Chassy_safety_controller(float d, float tf,float v,coordonnee c){
    msg msg_danger;
    action a;
    CSC_rep rep;
    if (d<30.0){
        time_t now;
        //printf("Danger inminent : freinage du vehicule\n");
        init_msg(msg_danger,d, tf,v,c);
      	tf=1.0;
        a = freinage;
        rep.taux_freinage=tf;
        rep.act=a;
        msg_danger.envoye=1;
      	msg_danger.priorite=1;
        msg_danger.vitesse=msg_danger.vitesse/(1+rep.taux_freinage*100);
        rep.danger=msg_danger;
        send_cc(rep.danger);
        return rep;
    }
    if(d>30 && d<100){
        time_t now;
        //printf("Deceleration du vehicule\n");
        a = deceleration;
        rep.taux_freinage = 0;
        rep.act = a;
        init_msg(msg_danger,d,tf,v,c);
        msg_danger.priorite=0;
        msg_danger.envoye=0;
        rep.danger = msg_danger;
        return rep;
    }
}

