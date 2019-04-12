


public class CommandeMeurt extends Commande
{


	public CommandeMeurt(Cellule celluleReceptrice, JeuDeLaVie jeu)
	{
		super(celluleReceptrice, jeu);
	}


	public void executer()
	{
		this.celluleReceptrice.meurt();
		this.jeu.decrementerNbCellulesVivantes();
	}

}
