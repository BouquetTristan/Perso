

import java.lang.Object;
import java.util.Observable;
import java.util.Observer;
import java.*;

public class JeuDeLaVieUI {

	public JeuDeLaVieUI()
	{

	}

	public static void main(String[] args)
	{
	
		JeuDeLaVie programmeDeJeu = new JeuDeLaVie();
		Fenetre fenetreDeJeu = new Fenetre(programmeDeJeu);
		
	}

	public void acualise()
	{
		paint();
	}

	public void paint(Graphics g)
	{
		super.paint(g);
		for(int x = 0; x < jeu.getXMax(); x ++)
		{
			for(int x = 0; x < jeu.getXMax(); x ++)
			{
				if(jeu.getGrilleXY(x, y).estVivante())
					g.fillOval(x*3, y*3, 3, 3)
			}
		}
	}
		
}