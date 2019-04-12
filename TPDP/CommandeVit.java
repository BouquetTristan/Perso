

public class CommandeVit extends Commande
{

		
	public CommandeVit(Cellule celluleReceptrice, JeuDeLaVie jeu)
	{
		super(celluleReceptrice, jeu);
	}


	
	public void executer()
	{
		this.celluleReceptrice.vit();
		this.jeu.incrementerNbCellulesVivantes();
	}

}