/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: Visiteur.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe abstraite définissant les comportements que doivent implémenter les Visiteurs
*/
public abstract class Visiteur //Classe abstraite plutôt qu'interface permet de mutualiser le constructeur
{

	protected JeuDeLaVie jdv;

	/**
	* Constructeur : permet de construire un Visiteur pour le JeuDeLaVie passé en paramètre.
	* @param JeuDeLaVie jeu : le JeuDeLaVie sur lequel le Visiteur agira (il visitera les Cellules de ce JeuDeLaVie)
	*/
	public Visiteur(JeuDeLaVie jdv)
	{
		this.jdv = jdv;
	}

	/**
	* Méthode pour la visite d'une Cellule vivante
	* @param Cellule cellule : la cellule à visiter
	*/
	public abstract void visiterCelluleVivante(Cellule cellule);

	/**
	* Méthode pour la visite d'une Cellule morte
	* @param Cellule cellule : la cellule à visiter
	*/
	public abstract void visiterCelluleMorte(Cellule cellule);

}
