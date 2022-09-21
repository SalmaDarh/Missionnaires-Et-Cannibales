#include <stdio.h>
#include <stdlib.h>
typedef struct Etat
{
    int x;//nombre de missionnaires sur la rive droite
    int y; //nombre de cannibales sur la rive droite
    char P;//position de la barque G ou D
}Etat;

typedef struct noeud
{
    Etat etat;
    struct noeud *suivant;
}Noeud;

typedef struct liste
{
    Noeud *sommet;
}Liste;//on travaille avec une pile pour la recherche en profondeur

Liste listeNoeuds;
Liste NoeudsDejaTraite;
void Inserer(Etat e, Liste *L)
{
    Noeud *nouveau=malloc(sizeof(*nouveau));
    nouveau->etat=e;
    nouveau->suivant=L->sommet;
    L->sommet=nouveau;

}
Etat Extraire(Liste *L)
{
    Etat e;
    e=L->sommet->etat;
    L->sommet=L->sommet->suivant;
    return e;
}
int Vide(Liste L)
{
    return (L.sommet==NULL);
}
int Appartient(Etat e, Liste L)
{
    Noeud *ptr;
    for (ptr=L.sommet;ptr!=NULL;ptr=ptr->suivant)
    {
        if ((ptr->etat.x==e.x)&&(ptr->etat.y==e.y )&&(ptr->etat.P==e.P)) return 1;
    }
    return 0;
}
int etatSolution(Etat etat)
{
    if ((etat.x==0)&&(etat.y==0 )&&(etat.P=='G')) return 1;
    return 0;
}
void genereSuccesseurs(Etat e)

{
    int x0,y0;
    char p0;
    Etat et;
    if (e.P=='D')
    {
        x0=e.x;
        y0=e.y;
        p0=e.P;
    }
    else if (e.P=='G')
    {
        x0=3-e.x;
        y0=3-e.y;
        p0=e.P;
    }

   if(((x0-1==0)||(x0-1>=y0))&&(y0>=0)&&(x0-1>=0)&&((3-x0>=3-(y0))||(3-(x0-1)==0)))//R10 : 1 missionnaire 0 cannibale
   {
       et.x=(p0=='D')?x0-1:3-(x0-1)  ;
       et.y=(p0=='D')?y0:3-y0;
       et.P=(p0=='D')?'G':'D';
       Inserer(et,&listeNoeuds);
   }
   if(((x0==0)||(x0>=y0-1))&&(y0-1>=0)&&(x0>=0)&&((3-x0>=3-(y0-1))||(3-x0==0)))//R01:0missionnaire 1 cannibale
   {
       et.x=(p0=='D')?x0:3-(x0);
       et.y=(p0=='D')?y0-1:3-(y0-1);
       et.P=(p0=='D')?'G':'D';
       Inserer(et,&listeNoeuds);
   }
   if(((x0==0)||(x0>=y0-2))&&(y0-2>=0)&&(x0>=0)&&((3-x0>=3-(y0-2))||(3-(x0)==0)))//R02
   {
       et.x=(p0=='D')?x0:3-(x0);
       et.y=(p0=='D')?y0-2:3-(y0-2);
       et.P=(p0=='D')?'G':'D';
       Inserer(et,&listeNoeuds);
   }
   if(((x0-2==0)||(x0-2>=y0))&&(y0>=0)&&(x0-2>=0)&&((3-(x0-2)>=3-(y0))||(3-(x0-2)==0)))//R20
   {
       et.x=(p0=='D')?x0-2:3-(x0-2);
       et.y=(p0=='D')?y0:3-(y0);
       et.P=(p0=='D')?'G':'D';
       Inserer(et,&listeNoeuds);
   }
   if(((x0-1==0)||(x0>=y0-1))&&(y0-1>=0)&&(x0-1>=0)&&((3-(x0-1)>=3-(y0-1))||(3-(x0-1)==0)))//R11
   {
       et.x=(p0=='D')?x0-1:3-(x0-1);
       et.y=(p0=='D')?y0-1:3-(y0-1);
       et.P=(p0=='D')?'G':'D';
       Inserer(et,&listeNoeuds);
   }
  // if(!Appartient(et,NoeudsDejaTraite)) printf(" (%d,%d,%c)\n",et.x, et.y, et.P);



}


void rechercheEnProfondeur(Etat etatInitial, Etat etatFinal, void genereSuccesseurs())
{
    Etat etatCourant;
    NoeudsDejaTraite.sommet= NULL ;
    listeNoeuds.sommet=NULL;
    Inserer(etatInitial,&listeNoeuds);
    printf("Voici le chemin vers la solution: (missionnaires a droite,cannibales a droite, position de la barque)\n");
    while(!Vide(listeNoeuds))
    {
        etatCourant=Extraire(&listeNoeuds);

        if(etatSolution(etatCourant))
        {
            printf("Arret sur le noeud (%d,%d,%c)\nSucces \n",etatCourant.x,etatCourant.y,etatCourant.P);
            exit(0);
        }
        else if (!Appartient(etatCourant,NoeudsDejaTraite))
        {
            genereSuccesseurs( etatCourant);
            Inserer(etatCourant, &NoeudsDejaTraite);
            printf(" (%d,%d,%c)\n",etatCourant.x, etatCourant.y, etatCourant.P);

        }
    }
    puts("\nPas de Solution");
    }


int main()
{

    Etat etatInitial = {3,3,'D'};
    Etat etatFinal = {0,0,'G'};
    rechercheEnProfondeur(etatInitial,etatFinal,genereSuccesseurs);
    return 0;
}
