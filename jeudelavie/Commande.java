/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: Commande.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Interface représentant les méthodes invoquables sur les Commandes
*/
public abstract class Commande
{

	protected Cellule celluleReceptrice;
	protected JeuDeLaVie jeu; //Utile pour l'incrémentation/décrémentation du nombre de celulles vivantes


	/**
	* Constructeur : Crée une nouvelle instance de Commande à partir des informations passées en paramètres
	* @param Cellule celluleReceptrice : la Cellule sur laquelle sera appliquée la Commande
	* @param JeuDeLaVie jeu : le JeuDeLaVie lié aux Commandes (permet de demander la MAJ du nombre de Cellules vivantes)
	*/
	public Commande(Cellule celluleReceptrice, JeuDeLaVie jeu)
	{
		this.celluleReceptrice = celluleReceptrice;
		this.jeu = jeu;
	}

	/**
	* Exécute la Commande
	*/
 	public abstract void executer();

}
