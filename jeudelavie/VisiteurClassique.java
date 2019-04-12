/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: VisiteurClassique.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe permettant d'implémenter un Visiteur qui aura les règles suivantes :
*    - Une Cellule vivante doit mourrir si elle a moins de deux voisines vivante ou plus de 3 voisines vivantes.
*    - Une Cellule morte doit ressuciter si elle a trois voisines excactement
*/
public class VisiteurClassique extends Visiteur
{

	/**
	* Constructeur : permet de construire le VisiteurClassique pour le JeuDeLaVie passé en paramètre.
	* @param JeuDeLaVie jeu : le JeuDeLaVie sur lequel le VisiteurClassique agira (il visitera les Cellules de ce JeuDeLaVie)
	*/
	public VisiteurClassique(JeuDeLaVie jdv)
	{
		super(jdv);
	}

	/**
	* Gère la visite sur une Cellule vivante. Une Cellule vivante doit mourrir si elle a moins de deux voisines vivantes
	* ou plus de 3 voisines vivantes.
	*/
	public void visiterCelluleVivante(Cellule cellule)
	{
		int nbVoisinesVivantes = cellule.nombreVoisinesVivantes(this.jdv);
		if(nbVoisinesVivantes<2 || nbVoisinesVivantes>3)
		{
			this.jdv.ajouterCommande(new CommandeMeurt(cellule,jdv));
		}
	}

	/**
	* Gère la visite sur une Cellule morte. Une Cellule morte doit ressuciter si elle a trois voisines excactement
	*/
	public void visiterCelluleMorte(Cellule cellule)
	{
		if(cellule.nombreVoisinesVivantes(this.jdv) == 3)
		{
			this.jdv.ajouterCommande(new CommandeVit(cellule,jdv));
		}
	}

}
