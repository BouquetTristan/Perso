

public class Singleton {

	public static final Singleton INSTANCE;

	private Singleton() {}

	public static final Singleton getInstance()
	{
		INSTANCE = new Signleton();

		return INSTANCE;
	}
}