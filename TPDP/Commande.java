


public abstract class Commande
{

	protected Cellule celluleReceptrice;
	protected JeuDeLaVie jeu; 


	public Commande(Cellule celluleReceptrice, JeuDeLaVie jeu)
	{
		this.celluleReceptrice = celluleReceptrice;
		this.jeu = jeu;
	}


 	public abstract void executer();

}