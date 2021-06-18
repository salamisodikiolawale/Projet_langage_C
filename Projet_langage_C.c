
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;


typedef struct File File;
struct File
{
    Bloc *premier;
};



/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*               PARTIE I                        */
/*                                               */
/*************************************************/

//########MA Fonction d'Affichage convert#################/
void convert(int x)
{
    if(x==TRUE)
        printf("TRUE\n");
    else
        printf("FALSE\n");
}

float facto (int n){
    if (n<1) 
        return 1;
    else
        return  n * facto(n-1);
}

float e (int n){
    long double result =  1/facto(n);
    if (result == 0)
        return 0;
    else
        return result + e(n+1);
}


double puissance(double x, int n)
{
    if(n==0)
        return 1;
    else return x * puissance(x, n-1);
}

/*********FONCTION D'ACKERMANN****************/

//Itérative
int A_iter(int m, int n)
{ 
    if(m==0)
        return n+1;
    else 
    { 
        int r=1;
        for(int i = 0; i < n+1; i++)
            r = A_iter(m-1,r);
        return r;
    } 
}

//Récursive
int A_rec(int m, int n)
{ 
    if(m==0) 
        return n+1;
    else
        if(n==0) 
            return A_rec(m-1,1);
        else 
            return A_rec(m-1,A_rec(m,n-1));
}


//Pseudo code de X 
float X_aux(float *y, int n, int n_incr, float x_cour)
{
    if (n_incr <= n)
    {
        *y = x_cour + 1/x_cour;
        return X_aux(y, n, n_incr + 1, *y);
    }
}

float X(int n)
{
    float y = 1.0;
    X_aux(&y, n, 1, 1);
    printf("result\n");
    return y;
}

//Version Itérative de X sans sous fonction
float X_Ite(int n)
{
    float x_cour = 1;
    for (int i = 0; i < n; ++i)
        x_cour = x_cour + 1/x_cour;
    return x_cour;
}

float x_recursive_version (int n){
    if (n==0)
        return 1;
    else if (n>=1)
        return x_recursive_version(n-1) + (1 / x_recursive_version(n-1)); 
}

/*
    Version récursive de X sans sous fonction
    Cette fonction a ete mise en commentaire pour le calcul X_Rec(100) dans le main.
    Décommenter dans le main pour l'utiliser.
*/
float X_Rec(int n)
{
    float x_cour = 1;
    if(n==0)
        return 1;
    else if (n>=1)
        return x_recursive_version(n-1) + (1 / x_recursive_version(n-1)); 
}


/*************************************************/
/*                                               */
/*               PARTIE II                       */
/*                                               */
/*************************************************/
bool DebutDeuxIdentiques(Liste l)
{
    if (estVide(l) OR estVide(suite(l)) )
      return FALSE;
    else if(premier(l) == premier(suite(l)) )
      return TRUE;
    else
      return FALSE;
}

bool QueDesZeros(Liste l)
{
    if(estVide(l))
      return TRUE;
    else if (premier(l) ISNOT 0)
        return FALSE;
    else
       QueDesZeros(suite(l));
}

bool SousEnsemble(Liste l1, Liste l2)
{
  if (estVide(l1))
    return TRUE;
  else if (estVide(l2))
    return FALSE;
  
  if (premier(l1) ISNOT premier(l2))
    return SousEnsemble(l1, suite(l2));
  else
    return (premier(l1) == premier(l2)) AND SousEnsemble(suite(l1), suite(l2));

}

void Permutations(int *x, int *y)
{
    int tmp ;
    tmp = *x ;
    *x = *y ;
    *y = tmp ;
}

void Palindrome_aux (Liste *p, Liste L, int *resultat)
{

    if(estVide(L))
        *resultat = TRUE;
    else 
    {
        Palindrome_aux(&(*p), suite(L), &*resultat);
        if(NOT(estVide(L)))
             if(premier(*p) != premier(L))
                *resultat = FALSE;
        *p = (*p)->suivant;   
    }    
           
}

int estPalindrome(Liste L)
{
    Liste p = L;
    int resultat;
    Palindrome_aux(&p, L, &resultat) ;
    return resultat;
}

void EliminePositionsPaires_aux(Liste *L, int cpt)
{
    if (NOT(estVide(*L)))
    {
        cpt ++;
        if(cpt%2 == 0)
            depile(L);
        EliminePositionsPaires_aux(&((*L)->suivant), cpt);
    }
}

void EliminePositionsPaires(Liste *L)
{
    EliminePositionsPaires_aux(L, 0);
}

void Begaye(Liste *L )
{
    if (NOT(estVide(*L))) {
        if (premier(*L)<=0) {
            depile(L);
            Begaye(L);
        } else {
            empile(premier(*L), L);
            Begaye( &((*L)->suivant->suivant) );
        }
    }
}

//MaxZerosConsecutifs ITERATIF
void MaxZerosConsecutifs_ite_aux(Liste L, int *pt_plusG)
{
    Liste L2 = L;
    int cpt = 0;    

    while(NOT(estVide(L2)))
    {
        if (premier(L2) == 0)
        {
            cpt++;
            L2 = suite(L2);
        }
        else
        {
            if(cpt > *pt_plusG)
                *pt_plusG = cpt;

            cpt = 0;
            L2 = suite(L2);
        }
    }
}

int MaxZerosConsecutifs_ite(Liste L)
{
    int plusG = 0;
    MaxZerosConsecutifs_ite_aux(L, &plusG);
    return plusG;
}


//MaxZerosConsecutifs RECURSIVE
int MaxZerosConsecutifs_rec_aux(Liste L, int cpt, int pt_plusG)
{
    if(NOT(estVide(L)))
    {
        if (premier(L) == 0)
        {
            cpt++;
            return MaxZerosConsecutifs_rec_aux(suite(L), cpt, pt_plusG);
        }
        else
        {
            if(cpt > pt_plusG)
                pt_plusG = cpt;
            cpt = 0;
            return MaxZerosConsecutifs_rec_aux(suite(L), cpt, pt_plusG);
        }
    }
    return pt_plusG;
}

int MaxZerosConsecutifs_rec(Liste L)
{
    return MaxZerosConsecutifs_rec_aux(L, 0, 0);
}

//VERSION RECURSIVE AVEC DEUX VAR OUT ET UNE IN
int MaxZerosConsecutifs_rec_out_aux(Liste L, int *pt_cpt, int *pt_plusG)
{
    *pt_cpt = 0;
    *pt_plusG = 0;

    if (estVide(L))
        return *pt_plusG;
    else
    {
        MaxZerosConsecutifs_rec_out_aux(suite(L), pt_cpt, pt_plusG);
        if (premier(L) == 0)
        {
            *pt_cpt= *pt_cpt + 1;
        }
        else
        {
            if(*pt_cpt > *pt_plusG)
                *pt_plusG = *pt_cpt;
            *pt_cpt = 0;
        }
    }
    return *pt_plusG;
}

int MaxZerosConsecutifs_rec_out(Liste L)
{
    int cpt, pt_plusG;
    return MaxZerosConsecutifs_rec_out_aux(L, &cpt, &pt_plusG);

}


bool SommeAvantApres_aux(Liste L, int somG, int *somD, int *b)
{
    *somD = 0;
    if(NOT(estVide(L)))
    {
        SommeAvantApres_aux(suite(L), somG + premier(L), somD, b);
        if (somG == *somD)
            *b = TRUE;
        *somD = *somD + premier(L);
    }

}


bool SommeAvantApres(Liste L)
{
    int somD;
    int b = FALSE;
    SommeAvantApres_aux(L, 0, &somD, &b);
    return b;
}

/*************************************************/
/*                                               */
/*               PARTIE FILE                     */
/*                                               */
/*************************************************/

File *initFile()
{
    File *file = malloc(sizeof(*file));
    file->premier = NULL;

    return file;
}

void afficherFile(File *F)
{
    if (F == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Bloc *actuel = F->premier;

    while (actuel != NULL)
    {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");
}


void enfiler(int x, File *F)
{
    Bloc *tmp =  malloc(sizeof(Bloc)); 
    tmp->nombre = x; 
    tmp->suivant = NULL;

    if(F->premier != NULL)
    {
        Bloc *BlocActuel = F->premier;
        while(BlocActuel->suivant != NULL)
        {
            BlocActuel = BlocActuel->suivant;
        }
        BlocActuel->suivant = tmp;
    }
    else
    {
        F->premier = tmp;
    }
}

int defiler(File *F)
{
    if (F == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    if (F->premier != NULL)
    {
        Bloc *elementDefile = F->premier;

        nombreDefile = elementDefile->nombre;
        F->premier = elementDefile->suivant;
        free(elementDefile);
    }

    return nombreDefile;
}

/*************************************************/
/*                                               */
/*          definition type image                */
/*                                               */
/*************************************************/

typedef struct bloc_image
{ 
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;
typedef bloc_image *image ;

image construitBlanc()
{
    image img_blanc  = (image) malloc(sizeof(bloc_image));
    return img_blanc;
}

image construitnoir()
{
    image img_noir  = (image) malloc(sizeof(bloc_image));
    img_noir->toutnoir = TRUE;
    int i = 0;
    while(i<4)
    {
        img_noir->fils[i] = NULL;
        i++;
    }
    return img_noir;
}

image construitcomposee(image i1,image i2,image i3,image i4)
{
    image img_composee = (image) malloc(sizeof(bloc_image));

            img_composee->toutnoir = FALSE;

            img_composee->fils[0] = i1;
            img_composee->fils[1] = i2;
            img_composee->fils[2] = i3;
            img_composee->fils[3] = i4;

    return img_composee;
}


void afficheNormal(image img)
{
    if(img == NULL)
        printf(" B");
    else 
        if (img->toutnoir)
            printf("  N");
        else
        {
            printf(".");
            afficheNormal(img->fils[0]);
            afficheNormal(img->fils[1]);
            afficheNormal(img->fils[2]);
            afficheNormal(img->fils[3]);
        }
}

void afficheProfondeur_aux(image img, int i)
{
    if(img == NULL)
        printf(" B%d", i);
    else 
        if (img->toutnoir)
            printf("  N%d", i);
        else
        {
            printf(".%d", i);
            afficheProfondeur_aux(img->fils[0], i+1);
            afficheProfondeur_aux(img->fils[1], i+1);
            afficheProfondeur_aux(img->fils[2], i+1);
            afficheProfondeur_aux(img->fils[3], i+1);
        }
}

void afficheProfondeur(image img)
{
    afficheProfondeur_aux(img, 0);
}

bool estNoir(image img)
{
    if (img == NULL)
        return FALSE;
    if (img->toutnoir)
        return TRUE;
    return estNoir(img->fils[0]) && estNoir(img->fils[1]) && estNoir(img->fils[2]) && estNoir(img->fils[3]);
}

bool estBlanche(image img)
{
    if (img == NULL)
        return TRUE;
    if (img->toutnoir)
        return FALSE;
    return estBlanche(img->fils[0]) && estBlanche(img->fils[1]) && estBlanche(img->fils[2]) && estBlanche(img->fils[3]);
}

bool meme_dessin(image img1, image img2)
{
    if(img1 == NULL)
        if(img2 == NULL)
            return TRUE;
        else
            return FALSE;
    else if((!img1->toutnoir && img2->toutnoir ) || (img1->toutnoir && !img2->toutnoir) ) 
            return FALSE;
        else
            return TRUE && meme_dessin(img1->fils[0], img2->fils[0]) && meme_dessin(img1->fils[1], img2->fils[1]) &&
            meme_dessin(img1->fils[2], img2->fils[2]) && meme_dessin(img1->fils[3], img2->fils[3]);
}


image difference(image img1, image img2)
{
    if((img1 == NULL))
        if((img2 == NULL)){}
        else
            return construitnoir();
    else if(img2 == NULL){}
    else
        return construitnoir();
    if((!img1->toutnoir && img2->toutnoir ) || (img1->toutnoir && !img2->toutnoir) ) 
        return construitnoir();
    else
        return difference(img1->fils[0], img2->fils[0]) , difference(img1->fils[1], img2->fils[1]),
            difference(img1->fils[2], img2->fils[2]) , difference(img1->fils[3], img2->fils[3]);
}


void rendmemoire(image *img)
{
    if(*img == NULL) 
        free(*img);
    else
    {
        rendmemoire(&(*img)->fils[0]) , rendmemoire(&(*img)->fils[1]),
        rendmemoire(&(*img)->fils[2]), rendmemoire(&(*img)->fils[3]);
        free(*img);
    }
}

void negatif(image *img)
{
    if (img == NULL)
        *img = construitnoir();
    else if(&(*img)->toutnoir)
            *img = NULL;
    else 
        negatif(&(*img)->fils[0]) , negatif(&(*img)->fils[1]),
        negatif(&(*img)->fils[2]), negatif(&(*img)->fils[3]);

}


double aire(image img)
{
    if(img == NULL)
        return 0;
    else if(img->toutnoir)
        return 1;
    else
        return (aire(img->fils[0])+ aire(img->fils[1]) + 
    aire(img->fils[2]) + aire(img->fils[3]))/4;
}

image copie(image img)
{
     if(estBlanche(img))
        return construitBlanc();
    else if(estNoir(img))
        return construitnoir();
    else
    {
        copie(img->fils[0]),copie(img->fils[1]), copie(img->fils[2]), copie(img->fils[3]);
        if(estNoir(img->fils[0]) && estNoir(img->fils[1]) && estNoir(img->fils[2]) && estNoir(img->fils[3]))
        {
            return construitnoir();
        }
        else if(estBlanche(img->fils[0]) && estBlanche(img->fils[1]) && estBlanche(img->fils[2]) && estBlanche(img->fils[3]))
        {
            return construitBlanc();
        }
        else
            return construitcomposee(img->fils[0], img->fils[1], img->fils[2], img->fils[3]);
    }
}

int compteSousImagesPleines_aux(image img, int h, int e, int *cpt, int hcopie)
{
    if(img == NULL)
        *cpt = 0;
    else if(img->toutnoir){
        *cpt = 1;
    }
    else
    {
        if(h>0)
        {
            compteSousImagesPleines_aux(img->fils[0], h-1, e+1, cpt, hcopie);
            compteSousImagesPleines_aux(img->fils[1], h-1, e+1, cpt, hcopie);
            compteSousImagesPleines_aux(img->fils[2], h-1, e+1, cpt, hcopie);
            compteSousImagesPleines_aux(img->fils[3], h-1, e+1, cpt, hcopie);
    
            
            if(hcopie == e)
            {
                if (estBlanche(img->fils[0]) OR estNoir(img->fils[0]) && 
                    estBlanche(img->fils[1]) OR estNoir(img->fils[1]) &&
                    estBlanche(img->fils[2]) OR estNoir(img->fils[2])&&
                    estBlanche(img->fils[3]) OR estNoir(img->fils[3]))
                {
                    *cpt++;
                }
            }
        }
    }
}

int compteSousImagesPleines(image img, int h)
{
    int cpt;
    compteSousImagesPleines_aux(img, h, 1, &cpt, h);
    return cpt;
}

image simplifie(image *img)
{
    if(estBlanche(*img))
    {
        *img = NULL;
    }
    else if(estNoir(*img))
    {
        (*img)->toutnoir = TRUE;
    }
    else
    {
        simplifie(&(*img)->fils[0]);
        simplifie(&(*img)->fils[1]);
        simplifie(&(*img)->fils[2]);
        simplifie(&(*img)->fils[3]);
    }
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{

printf("/*************************************************/\n");
printf("/*                                               */\n");
printf("/*           PARTIE I                            */\n");
printf("/*                                               */\n");
printf("/*************************************************/\n");
printf("################################## 1- Quelques calculs simples##############################\n");

printf("#########Version Itératif Ack ################\n");
printf("%f\n", e(5));
printf("#########Version Itératif Ack ################\n");

printf("Ack(0) = A_iter(0,0) = %d\n", A_iter(0,0));
printf("Ack(1) = A_iter(1,0) = %d\n", A_iter(1,0));
printf("Ack(2) = A_iter(2,0) = A_iter(1,1) = %d\n", A_iter(1,1));
//printf("Ack(2) = A(3,0) = A(2,1) = %d\n", A(2,1));

printf("#########Version Récurcive Ack ################\n"); 

printf("Ack(0) = A_rec(0,0) = %d\n", A_rec(0,0));
printf("Ack(1) = A_rec(1,0) = %d\n", A_rec(1,0));
printf("Ack(2) = A_rec(2,0) = A_rec(1,1) = %d\n", A_rec(1,1));
//printf("Ack(2) = A_rec(3,0) = A_rec(2,1) = %d\n", A_rec(8,1));


printf("######### Function X avec sous_func, X Itératif et X récursif ################\n"); 
printf("Function X      = %f\n", X(100));
printf("Function X_iter = %f\n", X_Ite(100));
//printf("Function X_Rec  = %f\n", X_Rec(100));



printf("/******************Puissance*********************/\n");
printf("( 1.1 puiss 10     ) = %f\n",  puissance(1.1, 10));
printf("( 1.01 puiss 100   ) = %f\n",  puissance(1.01, 100));
printf("( 1.001 puiss 1000 ) = %f\n",  puissance(1.001, 1000));
printf("( 1.0001 puiss 1000) = %f\n",  puissance(1.0001, 10000));
printf("( 1.0001 puiss 1000) = %f\n",  puissance(1.00001, 100000));
//printf("( 1.0001 puiss 1000) = %f\n",  puissance(1.000001, 1000000));

printf("/*************************************************/\n");
printf("/*                                               */\n");
printf("/*           PARTIE II                           */\n");
printf("/*                                               */\n");
printf("/*************************************************/\n");
printf("################################## 2 Listes-Piles et Files ##############################\n");
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);


    printf("/******************DebutDeuxIdentiques*********************/\n");

    Liste maListe ;

    initVide(&maListe);

    empile(2, &maListe) ;
    empile(5, &maListe) ;
    empile(7, &maListe) ;
    empile(9, &maListe) ;
    empile(9, &maListe) ;

    affiche_rec(maListe);
    
    bool result = DebutDeuxIdentiques(maListe);
    printf("%d\n", result);

    printf("/******************QueDesZeros*********************/\n");

    Liste listeZero ;

    initVide(&listeZero);

    empile(0, &listeZero) ;
    empile(0, &listeZero) ;
    empile(1, &listeZero) ;

    affiche_rec(listeZero);
    
    convert(QueDesZeros(listeZero));

    printf("/******************SousEnsemble*********************/\n");

    Liste ensemble1, ensemble2 ;

    printf("SousEnsemble1\n");
    initVide(&ensemble1);

    empile(3, &ensemble1) ;
    empile(2, &ensemble1) ;

    affiche_rec(ensemble1);

    printf("SousEnsemble2\n");
    initVide(&ensemble2);

    empile(3, &ensemble2) ;
    empile(2, &ensemble2) ;
    empile(1, &ensemble2) ;

    affiche_rec(ensemble2);
    
    convert(SousEnsemble(ensemble1, ensemble2));
    
    printf("/******************EliminePositionsPaires*********************/\n");

    Liste listeEli ;

    initVide(&listeEli);

    empile(3, &listeEli) ;
    empile(8, &listeEli) ;
    empile(8, &listeEli) ;
    empile(6, &listeEli) ;
    empile(1, &listeEli) ;
    empile(2, &listeEli) ;

    affiche_rec(listeEli);

    EliminePositionsPaires(&listeEli);

    printf("liste Elimine = ");

    affiche_rec(listeEli);

    printf("/******************MaxZerosConsecutifs*********************/\n");
    Liste listeMax ;

    initVide(&listeMax);


    
    empile(0, &listeMax) ;
    empile(0, &listeMax) ;
    empile(7, &listeMax) ;
    empile(8, &listeMax) ;
    empile(0, &listeMax) ;
    empile(7, &listeMax) ;
    empile(0, &listeMax) ;
    empile(0, &listeMax) ;
    empile(7, &listeMax) ;
    empile(9, &listeMax) ;

    //1 ) VERSION ITERATIF:
    
    affiche_rec(listeMax);
    printf("plus G Nbr de 0 consécutifs : %d\n", MaxZerosConsecutifs_ite(listeMax));

    //2 ) VERSION RECURSIVE AVEC SOUS FONCTION
    affiche_rec(listeMax);
    printf("plus G Nbr de 0 consécutifs (REC_S_F): %d\n", MaxZerosConsecutifs_rec(listeMax));
    
    //3 ) VERSION RECURSIVE AVEC SOUS FONCTION OUT
    affiche_rec(listeMax);
    printf("plus G Nbr de 0 consécutifs (REC_S_F_OUT): %d\n", MaxZerosConsecutifs_rec_out(listeMax));

    printf("/******************Bagaye*********************/\n");
    
    Liste listeBag ;

    initVide(&listeBag);

    
    empile(7, &listeBag) ;
    empile(-2,&listeBag) ;
    empile(4, &listeBag) ;
    empile(0, &listeBag) ;
    empile(3, &listeBag) ;
    empile(5, &listeBag) ;

    
    affiche_rec(listeBag);
    Begaye(&listeBag);
    affiche_rec(listeBag);
    
    
    printf("/******************SommeAvantApres*********************/\n");
    
    Liste listeSom ;

    initVide(&listeSom);

    
    empile(7, &listeSom) ;
    empile(-2, &listeSom) ;
    empile(4, &listeSom) ;
    empile(0, &listeSom) ;
    empile(3,&listeSom) ;
    empile(2, &listeSom) ;

    affiche_rec(listeSom);
    convert(SommeAvantApres(listeSom));

    // printf("/******************DP*********************/\n");
    // int h = DP(listeSom, 3);
    // printf("%d\n", h);

    printf("/******************estPalindrome*********************/\n");
    
    Liste listeEstPal ;

    initVide(&listeEstPal);

    empile(2, &listeEstPal) ;
    empile(2, &listeEstPal) ;
    empile(2, &listeEstPal) ;
    empile(2, &listeEstPal) ;

    affiche_rec(listeEstPal);
    convert(estPalindrome(listeEstPal));

    printf("/******************Permutations*********************/\n");
    
    int a = 2;
    int b = 3;
     printf("Avant :%d %d\n",a,b) ;
    Permutations(&a, &b);
    printf("Après: %d %d\n",a,b) ;

    printf("/******************File*********************/\n");
    File *maFile = initFile();
    enfiler(1, maFile);
    enfiler(2, maFile);
    enfiler(3, maFile);
    enfiler(4, maFile);
    enfiler(5, maFile);
    enfiler(6, maFile);
    printf("==Avant==\n");
    afficherFile(maFile);
    
    printf("Element defiler %d\n", defiler(maFile));

    printf("==Apres==\n");
    afficherFile(maFile);

printf("/*************************************************/\n");
printf("/*                                               */\n");
printf("/*           PARTIE III                          */\n");
printf("/*                                               */\n");
printf("/*************************************************/\n");


    image img_noir = construitnoir();

    printf("img_noir  ");
    afficheNormal(img_noir);

    printf("\n");

    printf("img_composee ");

    image i1 = construitnoir();
    image i2 = construitBlanc();
    image i3 = construitnoir();
    image i4 = construitBlanc();
    image img_composee = construitcomposee(i1, i2, i3, i4);
    afficheNormal(img_composee);
    printf("\n");

    printf("estBlanche :");
    convert(estBlanche(i4));

    printf("estNoir :");
    convert(estNoir(img_noir));

    printf("\n");
    printf("afficheProfondeur image noir  :\n");
    afficheProfondeur(img_noir);

    printf("\n");

    printf("afficheProfondeur image img_composee  : \n");
    afficheProfondeur(img_composee);
    printf("\n");

    printf("meme_dessin (img_composee, img_noir): ");
    convert(meme_dessin(img_composee, img_noir));
    printf("\n");

    printf("meme_dessin (img_composee, img_composee): ");
    convert(meme_dessin(img_composee, img_composee));
    printf("\n");

    printf("difference : ");
    afficheNormal(difference(img_composee, img_composee));
    printf("\n");

    printf("rendmemoire ");
    image img_test = construitnoir();
    rendmemoire(&img_test);
    printf("\n");

    printf("Avant Tranformation : ");
    afficheNormal(img_noir);
    printf("\n");
    negatif(&img_noir);
    printf("Après Tranformation : ");
    afficheNormal(img_noir);
    printf("\n");

    printf("Calcul d'aire :");
    image composee = construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitBlanc()));
    printf("%f\n", aire(composee));
    
    printf("******************Fonction copie******************** \n");
    printf("Copie\n");
    image copies = copie(composee);

    rendmemoire(&composee);
    afficheNormal(copies);
    printf("\n");

    printf("******************Fonction compteSousImagesPleines******************** \n");
    image composee1 = construitcomposee(construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitBlanc()), 
        construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitBlanc()), 
        construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitBlanc()), 
        construitcomposee(construitnoir(), construitBlanc(), construitnoir(), construitBlanc()));
    printf("compteSousImagesPleines :%d\n", compteSousImagesPleines(composee1, 0));


    printf("******************Fonction Simplifie********************************** \n");

    image aSimplifier = construitcomposee( 
        construitcomposee(construitnoir(), construitnoir(),construitcomposee(construitnoir(), construitnoir(), construitnoir(), construitnoir()),construitnoir() ),
        construitcomposee(construitBlanc(), construitBlanc(), construitBlanc(), construitBlanc()),
        construitnoir(),
        construitcomposee(construitBlanc(), construitnoir(), construitBlanc(), construitnoir())
        );

    printf("******************Simplifie Image**************************************\n");
    afficheNormal(aSimplifier);
    printf("\n");
    printf("******************Après Simplication***********************************\n");
    afficheNormal(simplifie(&aSimplifier));
    printf("\n");
    
    
    //putchar(c);
    //return 0;
    
}





