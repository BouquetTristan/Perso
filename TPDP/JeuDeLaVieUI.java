

import java.lang.Object;
import java.util.Observable;
import java.util.Observer;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class JeuDeLaVieUI extends JFrame implements Observateur 
{

	private JeuDeLaVie jeu;

	public JeuDeLaVieUI(JeuDeLaVie jeu)
	{

		this.jeu = jeu;


		int taille = 10;
		this.setTitle("Jeu de la Vie  ");
		this.setSize(600, 600);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		actualise();
		this.setVisible(true);

		
	}


	public void actualise()
	{
		repaint();
	}

	public void paint(Graphics g)
	{
		super.paint(g);
		Color maConasseDeCouleur = new Color(255, 0, 0);
		g.setColor(maConasseDeCouleur);

		for(int x = 0; x < jeu.getXMax(); x ++)
		{
			for(int y = 0; y < jeu.getYMax(); y ++)
			{

				if(jeu.getGrilleXY(x, y).estVivante())
					g.fillOval(x*10, y*10, 10, 10);
			}
		}
	}
		
}