package com.idkjava.thelements.custom;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

import android.util.Log;

import com.idkjava.thelements.MainActivity;
import com.idkjava.thelements.game.FileManager;

public class CustomElement
{
	private String mFilename; // What the is the filename?
	private int mCopy; // Which numerical tag are we at? (for duplicate element names) -- Not used right now
	private boolean mValid; // Does the file exist, and is it valid?
	private boolean mLoaded; // Have the properties been loaded?
	
	// Properties
	public String name;
	public int baseElementIndex;
	public int state;
	public int startingTemp;
	public int lowestTemp;
	public int highestTemp;
	public int lowerElementIndex;
	public int higherElementIndex;
	public int red;
	public int green;
	public int blue;
	public int density;
	public int fallVel;
	public int inertia;
	public ArrayList<Integer> collisions;
	public ArrayList<Integer> specials;
	public ArrayList<Integer> specialVals;
	
	// Constructors
	public CustomElement() {}
	public CustomElement(String filename)
	{
		mFilename = filename;
		mCopy = 0;
		mValid = loadNameFromFile();
		mLoaded = false;
	}
	// Call if you use the default constructor
	public void setFilename(String filename)
	{
		mFilename = filename;
		mCopy = 0;
		mValid = loadNameFromFile();
		mLoaded = false;
	}
	public String getFilename()
	{
		return mFilename;
	}
	public int getCopy()
	{
		return mCopy;
	}
	public boolean isValid()
	{
		return mValid;
	}
	public boolean isLoaded()
	{
		return mLoaded;
	}
	private boolean loadNameFromFile()
	{
		File fp = new File(FileManager.ROOT_DIR + FileManager.ELEMENTS_DIR + mFilename  + FileManager.ELEMENT_EXT);
		try
		{
			BufferedReader br = new BufferedReader(new InputStreamReader(new DataInputStream(new FileInputStream(fp))));
			name = br.readLine();
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
			return false;
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		return true;
	}
	
	public boolean loadPropertiesFromFile()
	{
		File fp = new File(FileManager.ROOT_DIR + FileManager.ELEMENTS_DIR + mFilename + FileManager.ELEMENT_EXT);
		try
		{
			BufferedReader br = new BufferedReader(new InputStreamReader(new DataInputStream(new FileInputStream(fp))));
			name = br.readLine();
			baseElementIndex = Integer.parseInt(br.readLine());
			state = Integer.parseInt(br.readLine());
			startingTemp = Integer.parseInt(br.readLine());
			lowestTemp = Integer.parseInt(br.readLine());
			highestTemp = Integer.parseInt(br.readLine());
			lowerElementIndex = Integer.parseInt(br.readLine());
			higherElementIndex = Integer.parseInt(br.readLine());
			red = Integer.parseInt(br.readLine());
			green = Integer.parseInt(br.readLine());
			blue = Integer.parseInt(br.readLine());
			density = Integer.parseInt(br.readLine());
			fallVel = Integer.parseInt(br.readLine());
			inertia = Integer.parseInt(br.readLine());
			
			// Collisions
			String collisionString;
			collisions = new ArrayList<Integer>();
			// Custom element header line -- C###, indicates how many collisions to read
			int numCollisionsToRead;
			br.mark(1000);
			collisionString = br.readLine();
			if (collisionString.startsWith("C"))
			{
				Log.d("LOG", "Found collisions header: " + collisionString);
				// Try reading the number of collisions, fallback to as many elements as we have
				try
				{
					numCollisionsToRead = Integer.parseInt(collisionString.substring(1));
				}
				catch (IndexOutOfBoundsException e)
				{
					numCollisionsToRead = MainActivity.NUM_BASE_ELEMENTS - MainActivity.NORMAL_ELEMENT;
				}
			}
			else
			{
				Log.d("LOG", "No collision header found");
				// Move the pointer back to before this line, since it is part of the data to be read
				br.reset();
				numCollisionsToRead = MainActivity.NUM_BASE_ELEMENTS - MainActivity.NORMAL_ELEMENT;
			}
			int collision;
			for (int i = 0; i < numCollisionsToRead; i++)
			{
				collisionString = br.readLine();
				if (collisionString == null)
				{
					break;
				}
				collision = Integer.parseInt(collisionString);
				if (collision < 0 || collision > MainActivity.NUM_COLLISIONS)
				{
					collision = 0;
				}
				collisions.add(collision);
			}
			String specialString;
			String specialValString;
			specials = new ArrayList<Integer>();
			specialVals = new ArrayList<Integer>();
			Log.d("LOG", "Reading specials");
			for (int i = 0; i < MainActivity.MAX_SPECIALS; i++)
			{
				specialString = br.readLine();
				specialValString = br.readLine();
				Log.d("LOG", "(" + specialString + ", " + specialValString + ")");
				
				if (specialString == null || specialValString == null)
				{
					break;
				}
				specials.add(Integer.parseInt(specialString));
				specialVals.add(Integer.parseInt(specialValString));
			}
		}
		catch (NumberFormatException e)
		{
			e.printStackTrace();
			return false;
		}
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
			return false;
		}
		catch (IOException e)
		{
			e.printStackTrace();
			return false;
		}
		mLoaded = true;
		mValid = true;
		return true;
	}
	
	public boolean writeToFile()
	{
		// Look for an available file location
		File fp = new File(FileManager.ROOT_DIR + FileManager.ELEMENTS_DIR + mFilename + FileManager.ELEMENT_EXT);
		/*
		if (!mValid)
		{
			mCopy = 0;
			while(fp.exists())
			{
				mCopy++;
				fp = new File(FileManager.ROOT_DIR + FileManager.ELEMENTS_DIR + mFilename + String.valueOf(mCopy) + FileManager.ELEMENT_EXT);
			}
		}
		*/
		
		// Now write our properties to it
		try
		{
			FileWriter writer = new FileWriter(fp);
			BufferedWriter out = new BufferedWriter(writer);
			
			out.write(name);
			out.newLine();
			out.write(String.valueOf(baseElementIndex));
			out.newLine();
			out.write(String.valueOf(state));
			out.newLine();
			out.write(String.valueOf(startingTemp));
			out.newLine();
			out.write(String.valueOf(lowestTemp));
			out.newLine();
			out.write(String.valueOf(highestTemp));
			out.newLine();
			out.write(String.valueOf(lowerElementIndex));
			out.newLine();
			out.write(String.valueOf(higherElementIndex));
			out.newLine();
			out.write(String.valueOf(red));
			out.newLine();
			out.write(String.valueOf(green));
			out.newLine();
			out.write(String.valueOf(blue));
			out.newLine();
			out.write(String.valueOf(density));
			out.newLine();
			out.write(String.valueOf(fallVel));
			out.newLine();
			out.write(String.valueOf(inertia));
			out.newLine();
			
			int arrayLength = collisions.size();
			out.write("C" + String.valueOf(arrayLength));
			out.newLine();
			for (int i = 0; i < arrayLength; i++)
			{
				out.write(String.valueOf(getCollisionIndexFromPos(collisions.get(i))));
				out.newLine();
			}
			
			arrayLength = specials.size();
			for (int i = 0; i < arrayLength; i++)
			{
				out.write(String.valueOf(getSpecialIndexFromPos(specials.get(i))));
				out.newLine();
				out.write(String.valueOf(specialVals.get(i)));
				out.newLine();
			}
			
			out.close();
		}
		catch (IOException e)
		{
			return false;
		}
		
		mValid = true;
		
		// Add this element to the element list
		fp = new File(FileManager.ROOT_DIR + FileManager.ELEMENTS_DIR + FileManager.ELEMENT_LIST_NAME + FileManager.LIST_EXT);
		
		if (!fp.exists())
		{
			try
			{
				FileWriter writer = new FileWriter(fp);
				BufferedWriter out = new BufferedWriter(writer);
				out.write(mFilename + FileManager.ELEMENT_EXT);
				out.newLine();
				
				return true;
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
			
			return false;
		}
		else if (fp.canRead() && fp.canWrite())
		{
			try
			{
				FileReader reader = new FileReader(fp);
				BufferedReader br = new BufferedReader(reader);
				
				String line;
				while((line = br.readLine()) != null)
				{
					if (line == mFilename)
					{
						return true;
					}
				}
				
				FileWriter writer = new FileWriter(fp);
				BufferedWriter bw = new BufferedWriter(writer);
				bw.append(mFilename + "\n");
				
				return true;
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
			
			return false;
		}
		
		return false;
	}
	
	public static int getCollisionIndexFromPos(int pos)
	{
		// Use this function to do a conversion if ever needed
		return pos;
	}
	public static int getSpecialIndexFromPos(int pos)
	{
		// Use this function to do a conversion if ever needed
		if (pos == 0)
		{
			return -1;
		}
		return pos;
	}
	public static int getSpecialPosFromIndex(int index)
	{
		// Use this function to do a conversion if ever needed
		if (index == -1)
		{
			return 0;
		}
		return index;
	}
}
