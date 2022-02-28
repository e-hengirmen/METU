import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CengPokeParser {

	public static ArrayList<CengPoke> parsePokeFile(String filename)
	{
		ArrayList<CengPoke> pokeList = new ArrayList<CengPoke>();

		// You need to parse the input file in order to use GUI tables.
		// TODO: Parse the input file, and convert them into CengPokes

		return pokeList;
	}

	public static int findCommand(String word){
		if(word.equalsIgnoreCase("quit"))return 1;
		if(word.equalsIgnoreCase("add"))return 2;
		if(word.equalsIgnoreCase("search"))return 3;
		if(word.equals("delete"))return 4;
		if(word.equalsIgnoreCase("print"))return 5;
		else return 0;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		// TODO: Start listening and parsing command line -System.in-.
		// There are 5 commands:
		Scanner input = new  Scanner(System.in);
		String word;
		Boolean flag=false;

		int key;

		while(true){
			word = input.next();
			// System.out.println(word);		//HERE commented this line out
			switch (findCommand(word)){
				case 1://quit
					flag=true;
					break;
				case 2://add
					key=input.nextInt();
					String name=input.next();
					String power=input.next();
					String type=input.next();
					CengPokeKeeper.addPoke(new CengPoke((Integer)key,name,power,type));
					break;
				case 3://search
					key=input.nextInt();
					CengPokeKeeper.searchPoke(key);
					break;
				case 4://delete
					key=input.nextInt();
					CengPokeKeeper.deletePoke(key);
					break;
				case 5://print
					CengPokeKeeper.printEverything();
					break;
				default:
					break;
			}
			if(flag)break;
		}

		// 1) quit : End the app. Print nothing, call nothing.
		// 2) add : Parse and create the poke, and call CengPokeKeeper.addPoke(newlyCreatedPoke).
		// 3) search : Parse the pokeKey, and call CengPokeKeeper.searchPoke(parsedKey).
		// 4) delete: Parse the pokeKey, and call CengPokeKeeper.removePoke(parsedKey).
		// 5) print : Print the whole hash table with the corresponding buckets, call CengPokeKeeper.printEverything().

		// Commands (quit, add, search, print) are case-insensitive.
	}
}
