

import java.lang.Math;



public class JeuDeLaVie {

    private Cellule[][] grille;
    private int xMax = 10, yMax = xMax;

    public JeuDeLaVie() 
    {

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
    

	public Cellule getGrilleXY(int x, int y)
	{
		return this.grille[x][y];
	}

	public void attacheObservateur(Observateur o)
	{

	}

	public void detacheObservateur(Observateur o)
	{

	}

	public void notifieObservateurs()
	{
		
	}
}