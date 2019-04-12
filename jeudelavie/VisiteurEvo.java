/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: VisiteurEvo.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe permettant d'implémenter un Visiteur qui aura les règles suivantes :
*    - Une Cellule vivante doit mourrir si elle a moins de 3 voisines vivantes, plus de 8 voisines vivantes ou 5 voisines vivantes ou plus de 3 voisines vivantes.
*    - Une Cellule morte doit ressuciter si elle a exactement 3,6,7 ou 8 voisines excactement
*/
public class VisiteurEvo extends Visiteur
{

	/**
	* Constructeur : permet de construire le VisiteurEvo pour le JeuDeLaVie passé en paramètre.
	* @param JeuDeLaVie jeu : le JeuDeLaVie sur lequel le VisiteurEvo agira (il visitera les Cellules de ce JeuDeLaVie)
	*/
	public VisiteurEvo(JeuDeLaVie jdv)
	{
		super(jdv);
	}

	/**
	* Gère la visite sur une Cellule vivante. Une Cellule vivante doit mourrir si elle a moins de 3 voisines vivantes, plus de 8 voisines vivantes ou 5 voisines vivantes
	* ou plus de 3 voisines vivantes.
	*/
	public void visiterCelluleVivante(Cellule cellule)
	{
		int nbVoisinesVivantes = cellule.nombreVoisinesVivantes(this.jdv);
		if(nbVoisinesVivantes<3 || nbVoisinesVivantes>8 || nbVoisinesVivantes==5)
		{
			this.jdv.ajouterCommande(new CommandeMeurt(cellule,jdv));
		}
	}

	/**
	* Gère la visite sur une Cellule morte. Une Cellule morte doit ressuciter si elle a exactement 3,6,7 ou 8 voisines excactement
	*/
	public void visiterCelluleMorte(Cellule cellule)
	{
		int nbVoisinesVivantes = cellule.nombreVoisinesVivantes(this.jdv);
		if( nbVoisinesVivantes == 3 || (nbVoisinesVivantes>5 && nbVoisinesVivantes<9) )
		{
			this.jdv.ajouterCommande(new CommandeVit(cellule,jdv));
		}
	}

}
