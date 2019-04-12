/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: CelluleEtatVivant.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe représentant le CelluleEtat d'une cellule en vie
*/
public class CelluleEtatVivant implements CelluleEtat
{

    private static volatile CelluleEtatVivant instanceUniqueCelluleEtatVivant = new CelluleEtatVivant();

	/**
	* Constructeur : permet de construire un nouvel CelluleEtatMort représentant l'état d'une Cellule qui est morte
	* Comme nous implémentons le pattern Singleton, le constructeur est privé
	*/
	private CelluleEtatVivant()
	{
		//Le constructeur ne fait rien
	}

	/**
	* Permet de récupérer l'instance unique de la classe CelluleEtatMort
	* @return CelluleEtatMort instanceUniqueCelluleEtatMort : l'instance unique de la classe CelluleEtatMort
	*/
	public static CelluleEtatVivant getInstance()
	{
		return instanceUniqueCelluleEtatVivant;
	}


	/**
	* Permet de renvoyer le CelluleEtat d'une Cellule vivante dont l'heure n'est pas encore venue
	* @return CelluleEtat etatMort : CelluleEtat d'une Cellule vivante dont l'heure n'est pas encore venue
	*/
	public CelluleEtat vit()
	{
		return getInstance();
	}


	/**
	* Permet de renvoyer le CelluleEtat d'une Cellule vivante qui trépasse
	* @return CelluleEtat etatMort : CelluleEtat d'une Cellule vivante qui trépasse
	*/
	public CelluleEtat meurt()
	{
		return CelluleEtatMort.getInstance();
	}


	/**
	* Renvoie vrai (true) si la Cellule est vivante, faux (false) si elle est morte
	* Ici la méthode renverra toujours vrai (true)
	*/
	public boolean estVivante()
	{
		return true;
	}


	/**
	* Invoque la fonction adéquate du Visiteur v sur la Cellule c
	* Invoque donc la méthode visiterCelluleVivante(Cellule cellule) dans le cas présent
	*/
	public void accepte(Visiteur v, Cellule c)
	{
		v.visiterCelluleVivante(c);
	}

}
