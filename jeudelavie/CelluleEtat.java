/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: CelluleEtat.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */

package jeudelavie;

/**
* Interface définissant les états d'une cellule
*/
public interface CelluleEtat
{

	/**
	* Fait vivre une cellule (la Cellule passe à l'état vivant)
	*/
	public CelluleEtat vit();

	/**
	* Tue une cellule (la Cellule passe à l'état mort)
	*/
	public CelluleEtat meurt();

	/**
	* Renvoie vrai (true) si la Cellule est vivante, faux (false) si elle est morte
	* @return boolean isVivante : vrai (true) si la Cellule est vivante, faux (false) le cas contraire
	*/
	public boolean estVivante();

	/**
	* Permet d'appliquer le Visiteur v sur la Cellule c en fonction de son état
	* ie : appeller la bonne méthode du Visiteur selon l'état de la Cellule.
	* @param Visiteur v : le Visiteur qui visite la Cellule c
	* @param Cellule  c : la Cellule que souhaite visiter le Visiteur v
	*/
	public void accepte(Visiteur v, Cellule c);

}
