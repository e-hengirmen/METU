import java.util.ArrayList;

public class CengBucket {

	// GUI-Based Methods
	public int n,count;
	public CengPoke[] pokemons;
	public Boolean visited;
	// These methods are required by GUI to work properly.

	public CengBucket(){
		count=0;
		n=CengPokeKeeper.getBucketSize();
		pokemons=new CengPoke[n];
		visited=false;
		for(int i=0;i<n;i++)pokemons[i]=null;
	}

	public void delete(int pokeKey){
		for(int i=0;i<n;i++){
			if(pokemons[i]!=null && pokemons[i].pokeKey()==pokeKey){
				pokemons[i]=null;
				count--;
				break;
			}
		}
	}

	public void addPoke(CengPoke poke){
		for(int i=0;i<n;i++){
			if(pokemons[i]==null){
				pokemons[i]=poke;
				count++;
				break;
			}
		}
	}
	public Boolean exists(int key){
		for(int i=0;i<n;i++){
			if(pokemons[i]!=null && pokemons[i].pokeKey()==key){
				return true;
			}
		}
		return false;
	}
	
	public int pokeCount()
	{

		// DOES: Return the pokemon count in the bucket.
		return count;
	}
	
	public CengPoke pokeAtIndex(int index)
	{
		// TODO: Return the corresponding pokemon at the index.
		return null;
	}
	
	public int getHashPrefix()
	{
		// TODO: Return hash prefix length.
		return 0;
	}
	
	public Boolean isVisited()
	{
		// TODO: Return whether the bucket is found while searching.
		return false;		
	}
	
	// Own Methods
}
