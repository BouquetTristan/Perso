



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
				jdv.calculerGenerationSuivante();
			}

			jdv.notifieEndOfSimulation();

		}


}