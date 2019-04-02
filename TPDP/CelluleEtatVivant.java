

public class CelluleEtatVivant implements CelluleEtat {

	public static CelluleEtatVivant INSTANCE;
	
	public CelluleEtat vit()
	{
		return this;
	}

	public CelluleEtat meurt()
	{
		return CelluleEtatVivant.getInstance();
	}

	public boolean estVivante()
	{
		return true;
	}

	public static final CelluleEtatVivant getInstance()
	{
		if (INSTANCE == null) {
			INSTANCE = new CelluleEtatVivant();
		}

		return INSTANCE;
	}
}