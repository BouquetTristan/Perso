/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: CommandeVit.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe implémentant la Commande vivre
*/
public class CommandeVit extends Commande
{

		/**
		* Constructeur : Crée une nouvelle Commande pour faire vivre une Cellule receptrice passée en paramètre
		* @param Cellule celluleReceptrice : la Cellule sur laquelle sera appliquée la Commande
		*/
		public CommandeVit(Cellule celluleReceptrice, JeuDeLaVie jeu)
		{
			super(celluleReceptrice, jeu);
		}


		/**
		* Exécute la Commande CommandeVit : fait vivre la Cellule receptrice
		*/
		public void executer()
		{
			this.celluleReceptrice.vit();
			this.jeu.incrementerNbCellulesVivantes();
		}

}
