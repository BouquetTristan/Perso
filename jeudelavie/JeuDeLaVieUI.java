/**
 * @Author: Corentin Petit <zeigon>
 * @Date:   27-Mar-2019
 * @Email:  corentin.petit.etu@univ-lemans.fr
 * @Filename: JeuDeLaVieUI.java
 * @Last modified by:   zeigon
 * @Last modified time: 02-Apr-2019
 */


package jeudelavie;
/**
* Classe permettant de représenter graphiquement le JeuDeLaVie passé en paramètre au constructeur
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;


public class JeuDeLaVieUI extends Canvas implements Observateur
{

    private JeuDeLaVie jeu;
    private final int ECHELLE;
	  private final Color COULEUR_CELLULE = Color.BLUE;

    //Combobox pour le choix des règles
    private String[] stringRegles = { "Visiteur classique", "Visiteur évo" };
    //JComboBox<String> listeRegles = new JComboBox<String>(stringRegles); //pas compilable sur les Windows 7 du département
    private JComboBox listeRegles = new JComboBox(stringRegles);

    //Bouttons de contrôle
    private JButton boutonPlayPause     = new JButton("Lancer");
    private JButton boutonSautGeneation = new JButton("+1");
    private JButton boutonReset         = new JButton("Reset");
    private JButton boutonDimensions    = new JButton("Dim.");

    //Slider pour le choix de la vitesse
    private JLabel sliderGPMLabel = new JLabel("      Gén./minute :", JLabel.CENTER);
    private JSlider sliderGPM = new JSlider(JSlider.HORIZONTAL, 1, 300, jeu.gpm); //300 gén./min max


    /**
    * Constructeur : Construit une nouvelle instance de JeuDeLaVieUI à partir du JeuDeLaVie passé en paramètre
	  * Cette instance permettera d'afficher le JeuDeLaVie, d'actualiser l'affichage et d'offir une zone de contrôle du jeu (modification de lé vitesse, play/pause...)
    * @param JeuDeLaVie jeu : le JeuDeLaVie que représentera graphiquement le JeuDeLaVieUI
    */
    public JeuDeLaVieUI(JeuDeLaVie jeu)
    {
      this.jeu = jeu;
      this.ECHELLE = 800/Math.min(jeu.getXMax(), jeu.getXMax()); //Permet un affichage avec une échelle fonction du nombre de cases

      JFrame frmMain = new JFrame("Jeu de la vie");
      frmMain.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

	    JPanel mainPanel = new JPanel(new BorderLayout());

      Canvas cnvs = this;
      //cnvs.setBackground(Color.BLACK);
      cnvs.setSize(jeu.getXMax()*ECHELLE, jeu.getYMax()*ECHELLE);

	    /* Ajout des éléments (Panel de contrôle et Canvas des Cellules) au Panel principal */
      mainPanel.add(cnvs,BorderLayout.CENTER);
      mainPanel.add(creerPanelZoneCtrl(),BorderLayout.PAGE_END);

	    /* Aout des listeners */
  		listeRegles.addActionListener(new ComboBoxReglesListener());
      boutonPlayPause.addActionListener(new BoutonPlayPauseListener());
  		boutonSautGeneation.addActionListener(new BoutonSautGeneationListener());
  		boutonReset.addActionListener(new BoutonResetListener());
  		sliderGPM.addChangeListener(new SliderGPMListener());
  		boutonDimensions.addActionListener(new BoutonDimensionsListener());

	    frmMain.add(mainPanel);
      frmMain.pack();
	    frmMain.setLocationRelativeTo(null); //Centre la fenêtre dans l'écran

      frmMain.setVisible(true);

      jeu.attacheObservateur(this);
    }


	/**
	* Crée le JPanel qui contient les contrôles du JeuDeLaVieCUI (play/pause, vitesse, +1 génération)
	* @return JPanel pan : le JPanel contenant les contrôles du JeuDeLaVieCUI
	*/
    public JPanel creerPanelZoneCtrl()
    {
        JPanel pan = new JPanel(new FlowLayout());
        pan.add(listeRegles);
        boutonPlayPause.setPreferredSize(new Dimension(90,25));
        pan.add(boutonPlayPause);
        pan.add(boutonSautGeneation);
        pan.add(boutonReset);
        pan.add(boutonDimensions);
        pan.add(sliderGPMLabel);
        pan.add(sliderGPM);
	    return pan;
    }


	/**
	* Fonction permettant de créer et d'afficher un popup offrant le choix de régénéré une nouvelle grille avec des dimensions personnalisées
	* @return int[] nouvellesDimensions : les nouvelles dimensions choisies par l'utilisateur (0 = nbLignes, 1 = nbCol) si ces dernières sont valides ou null le cas contraire
	*/
	public int[] afficherDialogChoixDimensions()
	{
		JTextField champX = new JTextField(5);
        JTextField champY = new JTextField(5);

      	JPanel myPanel = new JPanel();
    	myPanel.add(new JLabel("Nb lignes :"));
      	myPanel.add(champX);
    	myPanel.add(new JLabel("Nb colonnes :"));
      	myPanel.add(champY);

        //int result = jop.showConfirmDialog(null, "Saisissez les dimensions souhaitées : ", "Erreur", JOptionPane.ERROR_MESSAGE);
 		int result = JOptionPane.showConfirmDialog(null, myPanel,
               "Saisissez les dimensions souhaitées", JOptionPane.OK_CANCEL_OPTION);

		if(result == JOptionPane.OK_OPTION)
		{
	        System.out.println("x value: " + champX.getText());
	        System.out.println("y value: " + champY.getText());
			try
			{
				int nouvellesDimensions[] = new int[2];
				nouvellesDimensions[0] = Integer.parseInt(champX.getText());
				nouvellesDimensions[1] = Integer.parseInt(champY.getText());
				return (nouvellesDimensions[0]>0 && nouvellesDimensions[1]>0) ? nouvellesDimensions : null;
			}
			catch(NumberFormatException nfe)
			{
				return null; //Erreur de cast
			}
	    }

		return null; //Fenêtre non validée (croix pour fermeture ou bouton annuler)
	}


    /**
    * Actualise l'affichage du jeu quand un changement est notifié
    */
    public void actualise()
    {
        repaint();
    }


	/**
	* Affiche la popup de fin de simulation (mort de toutes les cellules)
	*/
	public void signalerFinSimulation()
	{
		JOptionPane jop = new JOptionPane();
        jop.showMessageDialog(null, "Fin de la simulation : Toutes les cellules sont à présent mortes.", "Fin de la simulation", JOptionPane.INFORMATION_MESSAGE);
	}


	/**
	* Méthode qui permet de déssiner les composants graphiques (les Cellules)
	* @param Graphics g : l'élément graphique sur lequel seront déssinés les composants graphiques (les Cellules)
	*/
    public void paint(Graphics g)
    {
        super.paint(g);
        g.setColor(COULEUR_CELLULE);

        for(int x=0; x<jeu.getXMax(); x++)
        {
            for(int y=0; y<jeu.getYMax(); y++)
            {
                if(jeu.getGrilleXY(x,y).estVivante())
                {
                    g.fillOval(x*ECHELLE,y*ECHELLE,ECHELLE,ECHELLE);
                }
            }
        }
    }



    /* === CLASSES INTERNES POUR DEFINIR LES LISTENERS === */


	/* Listener pour le ComboBox des règles */
	class ComboBoxReglesListener implements ActionListener
	{
		private Visiteur visiteurClassique = new VisiteurClassique(jeu);
		private Visiteur visiteurEvo       = new VisiteurEvo(jeu);

    	public void actionPerformed(ActionEvent e)
		{
			System.out.println("Changement de règles actionné");
			String strVisiteur = (String)listeRegles.getSelectedItem();
			if(strVisiteur.equals("Visiteur classique"))
			{
				jeu.setVisiteur(visiteurClassique);
	  		}
			else if(strVisiteur.equals("Visiteur évo"))
			{
				jeu.setVisiteur(visiteurEvo);
	  		}
		}
	}

    /* Listener pour gérer le bouton play/pause */
    class BoutonPlayPauseListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            System.out.println("Play/Pause actionné");
            if(boutonPlayPause.getText().equals("Pause"))
            {
		        jeu.pause();
				boutonSautGeneation.setEnabled(true);
                boutonPlayPause.setText("Lancer");
            }
            else
            {
		        jeu.reprendre();
				boutonSautGeneation.setEnabled(false);
                boutonPlayPause.setText("Pause");
            }
        }
    }

    /* Listener pour gérer le bouton +1 génération */
    class BoutonSautGeneationListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            System.out.println("+1 actionné");
            jeu.calculerGenerationSuivante();
        }
    }

	/* Listener pour gérer le bouton reset */
    class BoutonResetListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            System.out.println("Reset actionné");
            jeu.reset();
        	repaint();
        }
    }


	/* Listener pour gérer le bouton test */
    class BoutonDimensionsListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            System.out.println("Redimensionnement actionné");
			int nouvellesDim[] = afficherDialogChoixDimensions();
			if(nouvellesDim != null)
			{
            	jeu.redim(nouvellesDim);
        		repaint();
        	}
		}
    }

	/* Listener pour le slider de vitesse (les Générations Par Minute) */
	class SliderGPMListener implements ChangeListener
	{
	 	public void stateChanged(ChangeEvent ev)
		{
			jeu.setSpeed(sliderGPM.getValue());
	  	}
	}


}
