/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: Observable.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Interface définissant les méthodes que devront comporter les objets Observable (ie implémentant la présente interface Observable)
*/
public interface Observable
{

	/**
	* Ajoute un Observateur à la liste des Observateurs
	*/
	public void attacheObservateur(Observateur o);

	/**
	* Supprimer un Observateur de la liste des Observateurs
	*/
	public void detacheObservateur(Observateur o);

	/**
	* Notifie tous les Observateurs de la liste d'Observateurs
	*/
	public void notifieObservateur();

}
