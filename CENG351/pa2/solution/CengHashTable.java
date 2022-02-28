import java.util.ArrayList;

public class CengHashTable {
	public int MaxDepth;
	public int Gdepth;
	public ArrayList<CengHashRow> MyTable;
	public int HashMod;
	public CengHashTable()
	{
		Gdepth=0;
		MyTable=new ArrayList<CengHashRow>();
		MyTable.add(new CengHashRow(0,""));
		HashMod=CengPokeKeeper.getHashMod();
		MaxDepth= (int) Math.round(Math.log(HashMod) / Math.log(2));
		// TODO: Create a hash table with only 1 row.
	}

	private int findPrefix(int x){
		int HashValue=x%HashMod;
		int row=HashValue>>(MaxDepth-Gdepth);
		int local=MyTable.get(row).Ldepth;
		row>>=(Gdepth-local);
		row<<=(Gdepth-local);
		return row;
	}

	public void deletePoke(Integer pokeKey)
	{


		MyTable.get(findPrefix(pokeKey)).Bucket.delete(pokeKey);
		int numberOfEmptyBuckets=0;
		for(CengHashRow row:MyTable){
			if(!row.Bucket.visited&&row.Bucket.pokeCount()==0){
				numberOfEmptyBuckets++;
				row.Bucket.visited=true;
			}
		}
		System.out.println("\"delete\": {");
		System.out.println("\t\"emptyBucketNum\": "+numberOfEmptyBuckets);
		System.out.println("}");

		for(CengHashRow row:MyTable){
			row.Bucket.visited=false;
		}


		// DONE
	}

	public void addPoke(CengPoke poke)
	{
		int row=findPrefix(poke.pokeKey());
		//#########################3
		//System.out.println("Check1");
		//System.out.println(""+Gdepth);
		//System.out.println(""+row);
		//System.out.println(""+MyTable.get(row).Ldepth);
		//System.out.println("poke "+poke.pokeKey());
		//#########################3
		if(MyTable.get(row).Bucket.pokeCount()==CengPokeKeeper.getBucketSize()){		//if bucket is full
			//TODO: (increase local depth) & (divide the bucket)
			if(MyTable.get(row).Ldepth==Gdepth){		//if global depth needs to increase
				Gdepth++;
				int size=MyTable.size();
				ArrayList<CengHashRow> MyTable2=new ArrayList<CengHashRow>();

				for(int i=0;i<size;i++){
					MyTable2.add(new CengHashRow(MyTable.get(i),"0"));
					MyTable2.add(new CengHashRow(MyTable.get(i),"1"));
				}
				row*=2;
				MyTable=MyTable2;
				//DOES: increase global depth if necessary
			}

			int limit=(int)Math.round(Math.pow(2,(Gdepth-MyTable.get(row).Ldepth)));
			CengBucket OldBucket=MyTable.get(row).Bucket;
			CengBucket newBucket1=new CengBucket();
			CengBucket newBucket2=new CengBucket();
			Boolean state=false;

			//#########################3
			//System.out.println("Check4");
			//System.out.println(""+Gdepth);
			//System.out.println(""+row);
			//System.out.println(""+MyTable.get(row).Ldepth);
			//System.out.println("poke "+poke.pokeKey());
			//#########################3

			for(int i=0;i<limit;i++){
				// if(state)	//HERE Before the fix
				if(i<limit/2){	//HERE After the fix
					MyTable.get(row+i).Bucket=newBucket1;
				}
				else{
					MyTable.get(row+i).Bucket=newBucket2;
				}
				MyTable.get(row+i).Ldepth++;
				state=!state;
			}

			//#########################3
			//System.out.println("Check5");
			//System.out.println(""+Gdepth);
			//System.out.println(""+row);
			//System.out.println(""+MyTable.get(row).Ldepth);
			//System.out.println("poke "+poke.pokeKey());
			//#########################3

			for(int i=0;i<OldBucket.n;i++){			//adding pokemon from old bucket
				addPoke(OldBucket.pokemons[i]);
			}
			addPoke(poke);

			//#########################3
			//System.out.println(""+Gdepth);
			//System.out.println("Check7");
			//System.out.println(""+row);
			//System.out.println(""+MyTable.get(row).Ldepth);
			//#########################3
			//DONE: increase local depth divide elements between new buckets
		}
		else{
			MyTable.get(row).Bucket.addPoke(poke);
		}
		// TODO: errrors present
	}
	
	public void searchPoke(Integer pokeKey)
	{
		int row=findPrefix(pokeKey);

		int limit=(int)Math.round(Math.pow(2,(Gdepth-MyTable.get(row).Ldepth)));

		System.out.println("\"search\": {");
		if(MyTable.get(row).Bucket.exists(pokeKey))
		for(int i=row;i<row+limit;i++){
			System.out.println("\t\"row\": {");

			String BucketHash;
			if(Gdepth==0)BucketHash="0";
			else BucketHash=MyTable.get(i).hash;
			System.out.println("\t\t\"hashPref\": "+BucketHash+",");
			System.out.println("\t\t\"bucket\": {");
			System.out.println("\t\t\t\"hashLength\": "+MyTable.get(i).Ldepth+",");
			System.out.println("\t\t\t\"pokes\": [");

			int currentCount=0;
			for(int k=0;k<CengPokeKeeper.getBucketSize();k++){
				if(MyTable.get(i).Bucket.pokemons[k]!=null){
					currentCount++;
					System.out.println("\t\t\t\t\"poke\": {");
					System.out.println("\t\t\t\t\t\"hash\": "+MyTable.get(i).Bucket.pokemons[k].hash+",");
					System.out.println("\t\t\t\t\t\"pokeKey\": "+MyTable.get(i).Bucket.pokemons[k].pokeKey()+",");
					System.out.println("\t\t\t\t\t\"pokeName\": "+MyTable.get(i).Bucket.pokemons[k].pokeName()+",");
					System.out.println("\t\t\t\t\t\"pokePower\": "+MyTable.get(i).Bucket.pokemons[k].pokePower()+",");
					System.out.println("\t\t\t\t\t\"pokeType\": "+MyTable.get(i).Bucket.pokemons[k].pokeType());
					if(currentCount!=MyTable.get(i).Bucket.count) System.out.println("\t\t\t\t},");
					else System.out.println("\t\t\t\t}");
				}
			}

			System.out.println("\t\t\t]");
			System.out.println("\t\t}");


			//MyTable.get(row+i).Bucket=;
			// System.out.println("\t}"); //HERE before the fix
			if(i!=row+limit-1)System.out.println("\t},"); //HERE changed this println to print ","s that I forgot into this if else
			else System.out.println("\t}");	//HERE change line 2 for search

		}
		System.out.println("}");

		// TODO: Empty Implementation
	}
	
	public void print()
	{
		// TODO
		System.out.println("\"table\": {");
		for(int i=0;i<MyTable.size();i++){
			System.out.println("\t\"row\": {");
			String BucketHash;
			if(Gdepth==0)BucketHash="0";
			else BucketHash=MyTable.get(i).hash;
			System.out.println("\t\t\"hashPref\": "+BucketHash+",");
			System.out.println("\t\t\"bucket\": {");
			System.out.println("\t\t\t\"hashLength\": "+MyTable.get(i).Ldepth+",");
			System.out.println("\t\t\t\"pokes\": [");

			int currentCount=0;
			for(int k=0;k<CengPokeKeeper.getBucketSize();k++){
				if(MyTable.get(i).Bucket.pokemons[k]!=null){
					currentCount++;
					System.out.println("\t\t\t\t\"poke\": {");
					System.out.println("\t\t\t\t\t\"hash\": "+MyTable.get(i).Bucket.pokemons[k].hash+",");
					System.out.println("\t\t\t\t\t\"pokeKey\": "+MyTable.get(i).Bucket.pokemons[k].pokeKey()+",");
					System.out.println("\t\t\t\t\t\"pokeName\": "+MyTable.get(i).Bucket.pokemons[k].pokeName()+",");
					System.out.println("\t\t\t\t\t\"pokePower\": "+MyTable.get(i).Bucket.pokemons[k].pokePower()+",");
					System.out.println("\t\t\t\t\t\"pokeType\": "+MyTable.get(i).Bucket.pokemons[k].pokeType());
					if(currentCount!=MyTable.get(i).Bucket.count) System.out.println("\t\t\t\t},");
					else System.out.println("\t\t\t\t}");
				}
			}


			System.out.println("\t\t\t]");
			System.out.println("\t\t}");
			if(MyTable.size()-1!=i)System.out.println("\t},");
			else System.out.println("\t}");
		}
		System.out.println("}");
	}

	// GUI-Based Methods
	// These methods are required by GUI to work properly.
	
	public int prefixBitCount()
	{
		// TODO: Return table's hash prefix length.
		return 0;		
	}
	
	public int rowCount()
	{
		// TODO: Return the count of HashRows in table.
		return 0;		
	}
	
	public CengHashRow rowAtIndex(int index)
	{
		// TODO: Return corresponding hashRow at index.
		return null;
	}
	
	// Own Methods
}
