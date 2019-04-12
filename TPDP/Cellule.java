

public class Cellule  {
	
	private CelluleEtat etat;

	private int x;
	private int y;

	public Cellule(int x, int y, CelluleEtat etat)
	{
		this.etat = etat;
		this.x = x;
		this.y = y;
	}

	public CelluleEtat getEtat()
	{
		return this.etat;
	}

	public void vit()
	{
		this.etat = etat.vit();
	}

	public void meurt()
	{
		this.etat = etat.meurt();
	}

	public int nombreVoisinesVivantes(JeuDeLaVie jeu)
	{
		int nbVoisinesVivantes = 0; 

		for (int i = -1; i < 1 ; i++ ) 
		{
			for (int j = -1; j < 1 ; j++ ) 
			{
				if (jeu.getGrilleXY(x+i, y+j).estVivante() == true && i != 0 && j != 0)
					nbVoisinesVivantes++;
			}
		}

		return nbVoisinesVivantes;
	}

	public boolean estVivante()
	{
		return this.etat.estVivante();
	}


}