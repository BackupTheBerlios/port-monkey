/*
  Copyright (C) 2004 Giuliano Montecarlo

  This file is part of Pub-Monkey

  Pub-Monkey is free software, you can redistribute it and/or
  modify it under the terms of the Affero General Public License as
  published by Affero, Inc., either version 1 of the License, or
  (at your option) any later version.

  Pub-Monkey is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY, without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  Affero General Public License for more details.

  You should have received a copy of the Affero General Public
  License in the COPYING file that comes with Pub-Monkey. If
  not, write to Affero, Inc., 510 Third Street, Suite 225, San
  Francisco, CA 94107 USA.
*/

import java.util.*;
import java.io.*;

class Main
{
  public static void main(String[] argv)
  {
    try {
      System.out.println("Opening Logfile...");
      String logname = new String("pubs");
      FileOutputStream lofp = new FileOutputStream(logname);
    } catch(Exception e) {
      System.out.println("ERROR\n");
      System.exit(1);
    }
    System.out.println("OK\n");
				    
  
    HashSet hosts = new HashSet();
    System.out.println("Pub-Monkey 0.00 Alpha started\n");
  
    String host = new String();
  
    String fistr, sestr, thstr, fostr;

    if(argv[1] == "")
    {
      System.out.println("Usage: " + argv[0] + " <Hostname or IP>\n");
      hosts.add("localhost");
    } else {
      host = argv[1];
      int dot;
      if(host.indexOf("*") != -1)
      {      
        dot = host.indexOf(".");
        fistr = host.substring(0, dot);
        host = host.substring(dot+1, host.length()-dot);
      
        dot = host.indexOf(".");
        sestr = host.substring(0, dot);
        host =  host.substring(dot+1, host.length()-dot);
    
        dot = host.indexOf(".");
        thstr = host.substring(0, dot);
        host =  host.substring(dot+1, host.length()-dot);
    
        dot = host.indexOf(".");
        fostr = host.substring(0, dot);
        host =  host.substring(dot+1, host.length()-dot);
     
        if(fistr.equals("*"))
        {
          for(int i=1; i != 256; i++)
  	  {
	    hosts.add(Integer.toString(i) + "." +  sestr + "." + thstr + "." + fostr);
	  }
        } else if(sestr.equals("*")) {
          for(int i=1; i != 256; i++)
	  {
	    hosts.add(fistr + "." +  Integer.toString(i) + "." + thstr + "." + fostr);
	  }
        } else if(thstr.equals("*")) {
          for(int i=1; i != 256; i++)
	  {
	    hosts.add(fistr + "." +  sestr + "." + Integer.toString(i) + "." + fostr);
	  }
        } else if(fostr.equals("*")) {
          for(int i=1; i != 256; i++)
          {
            hosts.add(fistr + "." +  sestr + "." + thstr + "." + Integer.toString(i));
          }
        } else {
          hosts.add(host);
        }
      } else {
        hosts.add(host);
      }
    }
  
    Iterator it = hosts.iterator();
    FtpTest affe;
    while(it.hasNext())
    {
      System.out.println("\n");
      affe = new FtpTest((String)it.next(), lofp);
      affe.work();
    }
  }
}
