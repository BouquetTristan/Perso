/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: ThreadSimulation.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
public class ThreadSimulation implements Runnable
{

		private JeuDeLaVie jdv;

		public ThreadSimulation(JeuDeLaVie jdv)
		{
			this.jdv = jdv;
		}


		public void run()
		{
			System.out.println("Lancement de la simulation");

			/* Boucle des générations */
	        while(!jdv.isEnded())
	        {
				if(!jdv.isPaused())
				{
	            	jdv.calculerGenerationSuivante();
				}

				try
	            {
	                Thread.sleep(60000/jdv.getGpm());
	            }
	            catch(Exception e) {}
	        }

			jdv.notifieEndOfSimulation();

		}


}
