/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: CommandeMeurt.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe implémentant la Commande mourrir
*/
public class CommandeMeurt extends Commande
{

		/**
		* Constructeur : Crée une nouvelle Commande pour faire mourrir une Cellule receptrice passée en paramètre
		* @param Cellule celluleReceptrice : la Cellule sur laquelle sera appliquée la Commande
		*/
		public CommandeMeurt(Cellule celluleReceptrice, JeuDeLaVie jeu)
		{
			super(celluleReceptrice, jeu);
		}


		/**
		* Exécute la Commande CommandeMeurt : fait mourrir la Cellule receptrice
		*/
		public void executer()
		{
			this.celluleReceptrice.meurt();
			this.jeu.decrementerNbCellulesVivantes();
		}

}
