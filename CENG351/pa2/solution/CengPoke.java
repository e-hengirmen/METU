public class CengPoke {
	
	private Integer pokeKey;
	
	private String pokeName;
	private String pokePower;
	private String pokeType;
	public String hash;

	public CengPoke(Integer pokeKey, String pokeName, String pokePower, String pokeType)
	{
		this.pokeKey = pokeKey;
		this.pokeName = pokeName;
		this.pokePower = pokePower;
		this.pokeType = pokeType;
		this.hash = pokeHashString(pokeKey);
	}
	
	// Getters
	
	public Integer pokeKey()
	{
		return pokeKey;
	}
	public String pokeName()
	{
		return pokeName;
	}
	public String pokePower()
	{
		return pokePower;
	}
	public String pokeType()
	{
		return pokeType;
	}
		
	// GUI method - do not modify
	public String fullName()
	{
		return "" + pokeKey() + "\t" + pokeName() + "\t" + pokePower() + "\t" + pokeType;
	}
		
	// Own Methods
	public String pokeHashString(int x){
		int HashMod=CengPokeKeeper.getHashMod();
		int num=x%HashMod;
		int moddd=HashMod>>1;
		String res="";
		while(moddd!=0){
			if((num & moddd)!=0)res+="1";
			else res+="0";
			moddd>>=1;
		}
		return res;
	}
}
