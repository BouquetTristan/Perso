/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: Observateur.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Interface définissant les méthodes que devront comporter les objets Observateur (ie implémentant la présente interface Observateur)
*/
public interface Observateur
{

	/**
	* Méthode actualisant l'affichage suite à une notification de modification
	*/
	public void actualise();

	/**
	* Méthode affichant la popup de fin de simulation
	*/
	public void signalerFinSimulation();

}
