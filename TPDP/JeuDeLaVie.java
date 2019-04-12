

import java.lang.Math;
import java.util.List;
import java.util.ArrayList;



public class JeuDeLaVie implements Observable
{

	private Cellule[][] grille;
	private int xMax = 10, yMax = xMax;
	private List<Observateur> observateurs;
	private List<Commande> commandes;


	private boolean simulationTerminee = false;

	public JeuDeLaVie() 
	{
		observateurs = new ArrayList<Observateur>();
		commandes = new ArrayList<Commande>();
		this.grille = new Cellule[xMax][yMax];
		this.initialiseGrille();
	}

	public void initialiseGrille() 
	{
		for(int i = 0; i < xMax; i++)
			for(int j = 0; j < yMax; j++) 
			{
				if(Math.random() <= 0.5)
					this.grille[i][j] = new Cellule(i,j,new CelluleEtatVivant());
				else
					this.grille[i][j] = new Cellule(i,j,new CelluleEtatMort());
			}
	}

	public void lancer()
	{
		ThreadSimulation ts = new ThreadSimulation(this);
		new Thread(ts).start();
	}

	public void calculerGenerationSuivante()
	{

		notifieObservateurs();

	}

	public int getXMax()
	{
		return xMax;
	}

	public int getYMax()
	{
		return yMax;
	}

	public Cellule getGrilleXY(int x, int y)
	{
		return this.grille[x][y];
	}


	public boolean isEnded()
	{
		return this.simulationTerminee;
	}




	public void attacheObservateur(Observateur o)
	{
		this.observateurs.add(o);
	}

	public void detacheObservateur(Observateur o)
	{
		this.observateurs.remove(o);
	}

	public void notifieObservateurs()
	{
		for(Observateur observateurCourant : this.observateurs)
		{
			observateurCourant.actualise();
		}
	}

	public void notifieEndOfSimulation()
	{
		for(Observateur observateurCourant : this.observateurs)
		{
			//observateurCourant.signalerFinSimulation();
		}
	}





	public static void main(String[] args)
	{
		JeuDeLaVie jdv = new JeuDeLaVie();
		JeuDeLaVieUI jdvUI = new JeuDeLaVieUI(jdv);
		jdv.attacheObservateur(jdvUI);
		jdv.notifieObservateurs();
	}
}