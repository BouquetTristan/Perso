/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: Cellule.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */

package jeudelavie;

/**
* Classe permettant de représenter une Cellule du Jeu de La Vie.
*/
public class Cellule
{

	private int x; //Abscisse de la Cellule dans la grille
	private int y; //Ordonnée de la Cellule dans la grille

	private CelluleEtat etat;


	/**
	* Constructeur : Construit une nouvelle Cellule ayant pour CelluleEtat l'état passé en paramètre et pour coordonnées les coordonnées passées en paramètre
	* @param CelluleEtat etat : l'état de la Cellule au départ (CelluleEtatMort ou CelluleEtatVivant)
	* @param x : abscisse de la cellule sur la grille
	* @param y : ordonnée de la cellule sur la grille
	*/
	public Cellule(int x, int y, CelluleEtat etat)
	{
		this.x = x;
		this.y = y;
		this.etat = etat;
	}


	/**
	* Permet de faire vivre la Cellule
	*/
	public void vit()
	{
		this.etat = etat.vit();
	}


	/**
	* Permet de faire mourrir la Cellule
	*/
	public void meurt()
	{
		this.etat = etat.meurt();
	}


	/**
	* Renvoie vrai (true) si la Cellule est vivante, faux (false) si elle est morte
	* Ici la méthode demande au CelluleEtat de la cellule de lui indiquer si la Cellule vit ou est morte
	*/
	public boolean estVivante()
	{
		//System.out.println("Est vivante sur ["+x+","+y+"]" + this.etat.getClass().getSimpleName());
		return this.etat.estVivante();
	}

	/**
	* Renvoie le nombre de voisines vivantes autour de la Cellule courante
	* Note : le voisinnage directe comprend 8 cellules (N, NE, E, SE, S, SO, O, NO)
	* @return int nbVoisines : le nombre de Cellules vivantes dans le voisinnage directe de la Cellule courante
	*/
	public int nombreVoisinesVivantes(JeuDeLaVie jeu)
	{
		int nbVoisines = 0;

		Cellule n  = jeu.getGrilleXY(x  ,y-1);
		Cellule ne = jeu.getGrilleXY(x+1,y-1);
		Cellule e  = jeu.getGrilleXY(x+1,y  );
		Cellule se = jeu.getGrilleXY(x+1,y+1);
		Cellule s  = jeu.getGrilleXY(x  ,y+1);
		Cellule so = jeu.getGrilleXY(x-1,y+1);
		Cellule o  = jeu.getGrilleXY(x-1,y  );
		Cellule no = jeu.getGrilleXY(x-1,y-1);

		if(n  != null && n.estVivante() ){ nbVoisines ++; }
		if(ne != null && ne.estVivante()){ nbVoisines ++; }
		if(e  != null && e.estVivante() ){ nbVoisines ++; }
		if(se != null && se.estVivante()){ nbVoisines ++; }
		if(s  != null && s.estVivante() ){ nbVoisines ++; }
		if(so != null && so.estVivante()){ nbVoisines ++; }
		if(o  != null && o.estVivante() ){ nbVoisines ++; }
		if(no != null && no.estVivante()){ nbVoisines ++; }

		//System.out.println("Nb voisins cellule ["+x+","+y+"] = " + nbVoisines);

		return nbVoisines;
	}

	/**
	* Méthode permettant à une Cellule d'accépter un Visiteur
	*/
	public void accepte(Visiteur v)
	{
		//La Cellule invoque la méthode accpete de son état (délégation)
		this.etat.accepte(v,this);
	}

}
