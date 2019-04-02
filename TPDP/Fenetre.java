

import java.awt.GridLayout; 
import java.awt.Color; 
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JPanel;


public class Fenetre extends JFrame 
{
	public Fenetre(JeuDeLaVie jeu)
	{
		int taille = 10;
		this.setTitle("Jeu de la Vie  ");
		this.setSize(600, 600);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		this.setLayout(new GridLayout(taille, taille));

		for(int i = 0; i < taille; i++){
			for(int j = 0; j < taille; j++){
				this.getContentPane().add(new JButton(jeu.getGrilleXY(i,j).to_s()));
			}
		}


		
		this.setVisible(true);
	}
}