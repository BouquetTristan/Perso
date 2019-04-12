/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: JeuDeLaVieCUI.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe permettant de représenter en mode caractères dans le terminal le JeuDeLaVie jeu passé en paramètre au constructeur.
* La représentation comprend les informations suivantes :
*    - Le numéro de génération (= le rang)
*    - Le nombre de cellules vivantes
*/
public class JeuDeLaVieCUI implements Observateur
{

    private JeuDeLaVie jeu;
    private static int numGeneration = 0;

	/**
	* Constructeur : permet de construire un nouveau JeuDeLaVieCUI : interface en caractères qui permet d'afficher le numéro de génération
	* et le nombre de cellules vivantes pour chaque actualisation (chaque changement de génération)
	* @param JeuDeLaVue jeu : le JeuDeLaVie que représentera le JeuDeLaVieCUI
	*/
    public JeuDeLaVieCUI(JeuDeLaVie jeu)
    {
        this.jeu = jeu;
	    jeu.attacheObservateur(this);
    }

	/**
	* Méthode pour implémenter l'interface Observateur. Permet d'afficher le numéro de génération et le nombre de cellules vivantes à chaque changement de génération.
	*/
    public void actualise()
    {
	   System.out.println("\n== Génération " + jeu.getNumGeneration() + " ==");
	   System.out.println("Nombre de cellules vivantes : " + jeu.getNbCellulesVivante());
    }


	/**
	* Affiche le message de fin de simulation (mort de toutes les cellules)
	*/
	public void signalerFinSimulation()
	{
		System.out.println("Toutes les cellules sont mortes");
	}




}
