/*
  Copyright (C) 2004 Giuliano Montecarlo

  This file is part of Java-Monkey

  Java-Monkey is free software, you can redistribute it and/or
  modify it under the terms of the Affero General Public License as
  published by Affero, Inc., either version 1 of the License, or
  (at your option) any later version.

  Java-Monkey is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY, without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  Affero General Public License for more details.

  You should have received a copy of the Affero General Public
  License in the COPYING file that comes with Java-Monkey. If
  not, write to Affero, Inc., 510 Third Street, Suite 225, San
  Francisco, CA 94107 USA.
*/

import java.util.*;
import java.io.*;

class Main
{
  static FileOutputStream lofp = null;

  public static void main(String[] argv)
  {
    int lognr = 0;
    String logname = new String();
    File thelog = null;
    boolean gotlog = true;
    while(gotlog == true)
    {
      thelog = new File("pubs" + Integer.toString(lognr));
      gotlog = thelog.exists();
      logname = "pubs" + Integer.toString(lognr);
      lognr++;
    }
    
    try {
      System.out.print("Opening Logfile...");
      lofp = new FileOutputStream(logname);
    } catch(Exception e) {
      System.out.println("ERROR");
      System.exit(1);
    }
    System.out.println("OK");
				    
    System.out.println("Java-Monkey 0.00 Beta started");
  
    String host = new String();
  
    String fistr, sestr, thstr, fostr;

    if(argv[0] == "")
    {
      System.out.println("Usage: " + argv[0] + " <Hostname or IP>");
      testIt("localhost");
    } else {
      host = argv[0];
      int dot;
      if(host.indexOf("*") != -1)
      {      
        dot = host.indexOf(".");
	fistr = host.substring(0, dot);
	host = host.substring(dot+1);
	
        dot = host.indexOf(".");
	sestr = host.substring(0, dot);
        host =  host.substring(dot+1);
	

        dot = host.indexOf(".");
	thstr = host.substring(0, dot);
        host =  host.substring(dot+1);
	

        dot = host.indexOf(".");
        
	fostr = host;
     
        if(fistr.equals("*"))
        {
          for(int i=1; i != 256; i++)
  	  {
	    testIt(Integer.toString(i) + "." +  sestr + "." + thstr + "." + fostr);
	  }
        } else if(sestr.equals("*")) {
          for(int i=1; i != 256; i++)
	  {
	    testIt(fistr + "." +  Integer.toString(i) + "." + thstr + "." + fostr);
	  }
        } else if(thstr.equals("*")) {
          for(int i=1; i != 256; i++)
	  {
	    testIt(fistr + "." +  sestr + "." + Integer.toString(i) + "." + fostr);
	  }
        } else if(fostr.equals("*")) {
          for(int i=1; i != 256; i++)
          {
            testIt(fistr + "." +  sestr + "." + thstr + "." + Integer.toString(i));
          }
        } else {
          testIt(host);
        }
      } else {
        testIt(host);
      }
    }
  if(thelog.length() == 0) thelog.delete();
  
  }
  
  static public void testIt(String host)
  {
     System.out.println("");
     FtpTest affe = new FtpTest(host, lofp);
     affe.work();
  }
}
