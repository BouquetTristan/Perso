/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: JeuDeLaVie.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
import java.util.List;
import java.util.ArrayList;
import java.util.Random;

public class JeuDeLaVie implements Observable
{
    public static int gpm = 30;
	private static int numGeneration = 0;

    private boolean isPaused;

    private Cellule[][] grille;
    private int xMax = 100; //colonnes
    private int yMax = 100; //lignes
    private Visiteur visiteur;

    private int nbCellulesVivantes;

    private List<Observateur> observateurs;
    private List<Commande> commandes;

	private boolean simulationTerminee = false;

    /**
    * Constructeur : Crée un nouveau JeuDeLaVie
    */
    public JeuDeLaVie()
    {
        observateurs = new ArrayList<Observateur>();
        commandes = new ArrayList<Commande>();
        visiteur = new VisiteurClassique(this);
		nbCellulesVivantes = 0;
		isPaused = true;
        initialiseGrille();
    }


    /**
    * Peuple la grille avec des Cellules vivantes ou mortes de manière aléatoire
    */
    public void initialiseGrille()
    {
        Random random = new Random();
		grille = new Cellule[xMax][yMax];

        for(int x=0; x<xMax; x++)
        {
            for(int y=0; y<yMax; y++)
            {
                if(random.nextBoolean()) //vivante or not vivante
                {
                    grille[x][y] = new Cellule(y,x,CelluleEtatVivant.getInstance());
		   			nbCellulesVivantes ++;
                }
                else
                {
                    grille[x][y] = new Cellule(y,x,CelluleEtatMort.getInstance());
                }
            }
        }
    }


	/**
	* Lance la simulation du jeu
	*/
	public void lancer()
	{
		ThreadSimulation ts = new ThreadSimulation(this);
		new Thread(ts).start();
	}


    /**
    * Invoque la méthode accepte(Visiteur v) de chaque Cellule avec le VisiteurClassique du JeuDeLaVie
    */
    public void distribuerVisiteur()
    {
        for(int x=0; x<xMax; x++)
        {
            for(int y=0; y<yMax; y++)
            {
                getGrilleXY(x,y).accepte(this.visiteur);
            }
        }
    }


    /**
    * Fait avancer l'automate d'une génération
    * - Distribue un visiteur à chaque Cellule
    * - Exécute les Commandes
    * - Actualise les Observateurs
    */
    public void calculerGenerationSuivante()
    {
        //Etape 1 : Distribue un visiteur à chaque Cellule
        distribuerVisiteur();

        //Etape 2 : Exécution des Commandes ajoutées par le Visiteur
        executerCommandes();

        //Etape 3 : Actualisation des Observateurs
        notifieObservateur();

		numGeneration ++; //Incrémente le numéro de génération
    }



    /* === Méthodes pour le pattern Commande === */

    /**
    * Ajoute la Commande c passée en paramètre à la liste des Commandes à exécuter lors de l'invocation de la méthode executerCommandes()
    * @param Commande c : la Commande à ajouter à la liste des Commandes
    */
    public void ajouterCommande(Commande c)
    {
        this.commandes.add(c);
    }

    /**
    * Exécute les Commandes qui se trouvent dans la liste des Commandes commandes et vide cette liste
    */
    public void executerCommandes()
    {
        for(Commande cmdCourante : commandes)
        {
            cmdCourante.executer();
        }
        commandes.clear();
    }


    /* === Getters === */


    /**
    * Renvoie l'abscisse maximale de la grille
    * @return int xMax : l'abscisse maximale de la grille
    */
    public int getXMax()
    {
        return this.xMax;
    }


    /**
    * Renvoie l'ordonnée maximale de la grille
    * @return int yMax : l'ordonnée maximale de la grille
    */
    public int getYMax()
    {
        return this.yMax;
    }


    /**
    * Retourne la Cellule qui se trouve à la position indiquée par les coordonnées passée en paramètre
    * Cette fonction renvoie null en cas de coordonnées non valides
    * @param int x : abscisse visée
    * @param int y : ordonnée visée
    */
    public Cellule getGrilleXY(int x, int y)
    {
        if( x<0 || x>this.xMax-1 || y<0 || y>this.yMax-1 )
        {
            return null;
        }
        return this.grille[y][x];
    }


    /**
    * Retourne le nombre de Cellules en vie
    * @return int nbCellulesVivantes : le nombre de Cellules vivantes
    */
    public int getNbCellulesVivante()
    {
       /* int nbCellulesVivantes = 0;

        for(int x=0; x<xMax; x++)
        {
            for(int y=0; y<xMax; y++)
            {
                if (getGrilleXY(x,y).estVivante())
                {
                    nbCellulesVivantes++;
                }
            }
        }

        return nbCellulesVivantes;*/
        return this.nbCellulesVivantes;
    }


	/**
	* Renvoie le numéro de génération courante
	* @return numGeneration : un entier représentant le numéro de la génération courante
	*/
	public int getNumGeneration()
	{
		return numGeneration;
	}


	/**
	* Renvoie le nombre de génération par minute (gpm)
	* @return gpm : un entier représentant le numéro de génération par minute
	*/
	public int getGpm()
	{
		return gpm;
	}


	/**
	* Renvoie un booléen indiquand si la simulation est terminée ou non
	* @return isEnded : un booléen à vrai (true) si la simulation est terminée, à faux (false) le cas contraire
	*/
	public boolean isEnded()
	{
		return this.simulationTerminee;
	}


	/* == Gestion du nombre de cellules vivantes == */

	/**
	* Incrémente le nombre de cellule vivantes d'1 cellule
	*/
	public void incrementerNbCellulesVivantes()
	{
		this.nbCellulesVivantes ++;
	}

	/**
	* Décrémente le nombre de cellule vivantes d'1 cellule
	*/
	public void decrementerNbCellulesVivantes()
	{
		this.nbCellulesVivantes --;
		if(nbCellulesVivantes == 0)
		{
			simulationTerminee = true;
		}
	}


    /* === Implémentation da l'interface Observable === */

    /**
    * Ajoute un Observateur à la liste des Observateurs
    */
    public void attacheObservateur(Observateur o)
    {
        this.observateurs.add(o);
    }

    /**
    * Supprimer un Observateur de la liste des Observateurs
    */
    public void detacheObservateur(Observateur o)
    {
        this.observateurs.remove(o);
    }

    /**
    * Notifie tous les Observateurs de la liste d'Observateurs qu'une génération s'est écoulée
    */
    public void notifieObservateur()
    {
        for(Observateur observateurCourant : this.observateurs)
        {
            observateurCourant.actualise();
        }
    }

    /**
    * Notifie tous les Observateurs de la liste d'Observateurs que la fin de la simulation est survenue
    */
    public void notifieEndOfSimulation()
    {
        for(Observateur observateurCourant : this.observateurs)
        {
            observateurCourant.signalerFinSimulation();
        }
    }


	/* === Contrôle du jeu === */

	/**
	* Met en pause le jeu : les générations ne seront plus effectives
	*/
	public void pause()
	{
		this.isPaused = true;
	}

	/**
	* Reprend le jeu : réactibe les générations
	*/
	public void reprendre()
	{
		this.isPaused = false;
	}

	/**
	* Permet de déterminer si le JeuDeLaVie est en pause ou non
	* @return boolean paused : un booléen initialisé à vrai (true) si le jeu est en pause, à faux (false) le cas contraire
	*/
	public boolean isPaused()
	{
		return isPaused;
	}


	/**
	* Permet de faire un reset du JeuDeLaVie
	* Redémarre un nouveau JeuDeLaVie en réinitialisant la grillé aléatoirement
	*/
	public void reset()
	{
		//On remet à 0 le numéro de génération
		numGeneration = 0;
		//On remet à 0 le nombre ce cellules vivantes
		nbCellulesVivantes = 0;
		//On réinitialise la grille
        initialiseGrille();

		//On relance la simulation
		if(simulationTerminee)
		{
			simulationTerminee = false;
			lancer();
		}
	}


	/**
	* Permet de paramétrer la vitesse des génération en GPM (Généations Par Minute)
	*/
	public void setSpeed(int gpm) //gmp = génération / minute
	{
		this.gpm = gpm;
	}


	/**
	* Permet de choisir le Visiteur à employer
	*/
	public void setVisiteur(Visiteur v)
	{
		this.visiteur = v;
	}


	/**
	* Permet de réinitialiser le jeu avec d'autres dimensions
	*/
	public void redim(int[] nouvellesDimensions)
	{
		this.xMax = nouvellesDimensions[0];
		this.yMax = nouvellesDimensions[1];
		reset();
	}

    /* === Fonction Main */

    /**
    * Fonction Main : instancie une JeuDeLaVie, un JeuDeLaVieUI pour l'IHM et un JeuDeLaVieCUI pour l'IHM en mode caractères (affichage dans la terminal)
	* Le jeu sera mis en pause lors du démarrage afin de permettre l'analyse du rang 0.
    */
    public static void main(String args[])
    {
        JeuDeLaVie    jdv    = new JeuDeLaVie();
        JeuDeLaVieUI  jdvui  = new JeuDeLaVieUI(jdv);
        JeuDeLaVieCUI jdvcui = new JeuDeLaVieCUI(jdv);


	    System.out.println("Génération de la grille initiale...");

		jdv.lancer();
    }

}
