/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: CelluleEtatMort.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */

package jeudelavie;

/**
* Classe représentant le CelluleEtat d'une cellule morte
*/
public final class CelluleEtatMort implements CelluleEtat
{

    private static volatile CelluleEtatMort instanceUniqueCelluleEtatMort = new CelluleEtatMort();

	/**
	* Constructeur : permet de construire un nouvel CelluleEtatMort représentant l'état d'une Cellule qui est morte
	* Comme nous implémentons le pattern Singleton, le constructeur est privé
	*/
	private CelluleEtatMort()
	{
		//Le constructeur ne fait rien
	}

	/**
	* Permet de récupérer l'instance unique de la classe CelluleEtatMort
	* @return CelluleEtatMort instanceUniqueCelluleEtatMort : l'instance unique de la classe CelluleEtatMort
	*/
	public static CelluleEtatMort getInstance()
	{
		return instanceUniqueCelluleEtatMort;
	}


	/**
	* Permet de renvoyer le CelluleEtat d'une Cellule morte qui résussite
	* @return CelluleEtat etatMort : CelluleEtat d'une Cellule vivante dont l'heure n'est pas encore venue
	*/
	public CelluleEtat vit()
	{
		return CelluleEtatVivant.getInstance();
	}


	/**
	* Permet de renvoyer le CelluleEtat d'une Cellule morte
	* @return CelluleEtat etatMort : CelluleEtat d'une Cellule vivante qui trépasse
	*/
	public CelluleEtat meurt()
	{
		return getInstance();
	}


	/**
	* Renvoie vrai (true) si la Cellule est vivante, faux (false) si elle est morte
	* Ici la méthode renverra toujours faux (false)
	*/
	public boolean estVivante()
	{
		return false;
	}


	/**
	* Invoque la fonction adéquate du Visiteur v sur la Cellule c
	* Invoque donc la méthode visiterCelluleMorte(Cellule cellule) dans le cas présent
	*/
	public void accepte(Visiteur v, Cellule c)
	{
		v.visiterCelluleMorte(c);
	}

}
