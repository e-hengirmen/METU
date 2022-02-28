public class CengHashRow {

	// GUI-Based Methods
	// These methods are required by GUI to work properly.

	public CengBucket Bucket;
	public int Ldepth;
	public String hash;

	public CengHashRow(int depth,String HASH){
		hash=""+HASH;
		Bucket=new CengBucket();
		Ldepth=depth;
	}
	public CengHashRow(CengHashRow other){
		hash=""+other.hash;
		Bucket=other.Bucket;
		Ldepth=other.Ldepth;
	}

	public CengHashRow(CengHashRow other,String suffix){
		hash=""+other.hash+suffix;
		Bucket=other.Bucket;
		Ldepth=other.Ldepth;
	}

	public String hashPrefix()
	{
		// TODO: Return row's hash prefix (such as 0, 01, 010, ...)
		return "-1";		
	}
	
	public CengBucket getBucket()
	{
		// TODO: Return the bucket that the row points at.
		return null;		
	}
	
	public boolean isVisited()
	{
		// TODO: Return whether the row is used while searching.
		return false;		
	}
	
	// Own Methods
}
