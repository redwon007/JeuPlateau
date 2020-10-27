#include <stdio.h>
#include <stdlib.h>
#include <math.h>



/*-----------------------------------------------------------------------------------------------
surface(plateau)

Cette fonction affiche le plateau avec le tableau à jour

Entree : plateau : tableau 5*5 composé d'entiers correspondant au code ascii ' ', 'X', 'x', 'O', 'o' selon l'état de la case


*/

void surface(int plateau[5][5])
{
    printf("    1   2   3   4   5 \n");
    int i;
    for(i=0;i<11;i++)
    {
        if (i%2==1)
        {
            printf("%c | %c | %c | %c | %c | %c |\n",i+'A'-1-i/2,plateau[i/2][0],plateau[i/2][1],plateau[i/2][2],plateau[i/2][3],plateau[i/2][4]);//code ascii pour afficher A,B,C,D,F
        }
        else printf("  +---+---+---+---+---+\n");
    }
}



/*-----------------------------------------------------------------------------------------------
saisie(l, c)

Cette fonction recupere la ligne et la colonne saisie au clavier

Entree : l : pointeur sur la ligne à recuperer
         c : poinreur sur la colonne à recuperer


*/

void saisie(int *l, int *c)
{
    char s[100];
    do
    {
        printf("Votre coup ?");
        scanf("%s",s);//chaine permettant d'ignorer les espaces : programme plus robuste
        *l=s[0]-'A';//On recupere un entier sous forme de caractere que l'on convertit en indice avec la translation -'A' du code ascii
        *c=s[1]-'1';
    }while (!(*l>=0&&*l<=4&&*c>=0&&*c<=4&&s[2]==0));//utilisateur doit rentrer 2 entiers entre 0 et 4 apres translation
}



/*-----------------------------------------------------------------------------------------------
joueruncoup(plateau, joueur, coup)

Cette fonction joue un coup sur le plateau

Entree : plateau : etat du tableau representant le jeu a l'etat precedant
         joueur : joueur qui joue : joueur 1 : utilisateur au clavier
                                    joueur 2 : ordinateur
         coup : drapeau qui dit si le coup a ete joue (si le coup propose est valide)


*/

void joueruncoup(int plateau[5][5], int joueur,int *coup)//le joueur X est codé 10 et le joueur O est codé 20
{
    int ligne;
    int colonne;
    int majeur1;
    int mineur1;
    int mineur2;

    if (joueur==1)
    {
        majeur1='X';
        mineur1='x';
        mineur2='o';
    }
    else
    {
        majeur1='O';
        mineur1='o';
        mineur2='x';
    }

    while(*coup==0)
    {
        if (joueur==1) saisie(&ligne,&colonne);
        else
        {
            ligne=rand()%5;//l'ordinateur joue aleatoirement la ou il peut
            colonne=rand()%5;//remarque : il test un coup sans savoir si il est jouable ici il y a que 25 cases, donc pas aberrant mais si beacoup plus
                            //il faut piocher au hasard parmis les cases jouables
        }
        if (plateau[ligne][colonne]==' ' || plateau[ligne][colonne]==mineur1) //case jouable pour le majeur
        {
            *coup=1;

            plateau[ligne][colonne]=majeur1;

            if (plateau[ligne+1][colonne]==' '&&ligne<4) plateau[ligne+1][colonne]=mineur1;//la case au nord, sud, est ou ouest est vide
            if (plateau[ligne-1][colonne]==' '&&ligne>0) plateau[ligne-1][colonne]=mineur1;
            if (plateau[ligne][colonne+1]==' '&&colonne<4) plateau[ligne][colonne+1]=mineur1;
            if (plateau[ligne][colonne-1]==' '&&colonne>0) plateau[ligne][colonne-1]=mineur1;


            if (plateau[ligne+1][colonne]==mineur2&&ligne<4) plateau[ligne+1][colonne]='#';//la case au nord, sud, est ou ouest est composé du minaur de l'advesaire
            if (plateau[ligne-1][colonne]==mineur2&&ligne>0) plateau[ligne-1][colonne]='#';
            if (plateau[ligne][colonne+1]==mineur2&&colonne<4) plateau[ligne][colonne+1]='#';
            if (plateau[ligne][colonne-1]==mineur2&&colonne>0) plateau[ligne][colonne-1]='#';
        }
    }
    printf("%c joue : %c%c\n",majeur1, ligne+'A',colonne+'1');
}



/*-----------------------------------------------------------------------------------------------
comptepoints(plateau, ptX, ptY)

Cette fonction calcule les points du plateau

Entree : plateau : etat du tableau representant le jeu
         ptX : pointeur sur le nombre de point de X
         ptO : pointeur sur le nombre de point de O

*/
void comptpoints(int plateau[5][5],int *ptX, int *ptO)
{
    int i,j;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if (plateau[i][j]=='X') *ptX+=4;
            if (plateau[i][j]=='x') *ptX+=1;
            if (plateau[i][j]=='O') *ptO+=4;
            if (plateau[i][j]=='o') *ptO+=1;
        }
    }
}



/*-----------------------------------------------------------------------------------------------
mainn(void)

Cette fonction permet de jouer.
On verifie que X (joueur 1) peut jouer,il joue, on affiche le plateau, on vérifie
que O peut jouer (joueur 2, l'ordi) il joue on affiche le plateau et ainsi de suite.
On affiche les points.


Entree : plateau : etat du tableau representant le jeu
         ptX : pointeur sur le nombre de point de X
         ptO : pointeur sur le nombre de point de O

*/
int main(void)
{
    int i,j;
    int ligne,colonne;
    int plateau[5][5];
    int coup;
    int ptX, ptO;
    ptX=0;
    ptO=0;
    int partieencours;
    for (i=0;i<5;i++)//init du tableau
    {
        for (j=0;j<5;j++)
        {
            plateau[i][j]=' ';
        }
    }
    surface(plateau);
    while (1)
    {
        partieencours=0;//la partie est termine
        for (i=0;i<5;i++)//init du tableau
        {
            for (j=0;j<5;j++)
            {
                if (plateau[i][j]==' '|| plateau[i][j]=='x') partieencours=1;//X peut jouer donc la partie n'est pas termine
            }
        }
        if (partieencours==0) break;//si la partie est termine on sort du while
        coup=0;
        joueruncoup(plateau,1,&coup);
        surface(plateau);
        partieencours=0;
        for (i=0;i<5;i++)//init du tableau
        {
            for (j=0;j<5;j++)
            {
                if (plateau[i][j]==' ' || plateau[i][j]=='o') partieencours=1;
            }
        }
        if (partieencours==0) break;
        coup=0;
        joueruncoup(plateau,2,&coup);
        surface(plateau);
    }
    comptpoints(plateau,&ptX,&ptO);
    printf("Le joueur X a %d points\n", ptX);
    printf("Le joueur O a %d points\n", ptO);

}
