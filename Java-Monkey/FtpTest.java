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

import ftp.*;
import java.io.*;
import java.util.*;
import java.net.*;

class FtpTest
{
  FtpBean ftp;
  String fhost;
  FileOutputStream lfp;

  public FtpTest(String host, FileOutputStream logfp)
  {
    ftp = new FtpBean();
    fhost = host;
    lfp = logfp;
  }

  public boolean connect()
  {
    try {
      ftp.setSocketTimeout(1000);
    } catch(SocketException se) {
      return false;
    }
    return true;
  }

  public void close()
  {
    try {
      ftp.close();
    } catch(Exception e) {
      System.out.println(e);
    }
  }

  public void writeLog(String in)
  {
    for (int i=0; i < in.length(); i++)
    {
      try {
        lfp.write((byte)in.charAt(i));
      } catch(IOException ioe) {
        continue;
      }
    }
  }
  
  public HashSet listDirectory()
  {
    HashSet toret = new HashSet();
    FtpListResult ftplrs = null;
    try {
      ftp.setDirectory("/");
      ftplrs = ftp.getDirectoryContent();
    } catch(Exception e) {
      System.out.println(e);
      return null;
    }

    boolean haswdirs = false;
    while(ftplrs.next())
    {
      int type = ftplrs.getType();
      if(type == FtpListResult.DIRECTORY)
      {
	if (ftplrs.isGlobalWritable()) 
	{
	  toret.add(ftplrs.getName());
	  System.out.println(ftplrs.getName() + " is writable");
	  haswdirs = true;
	} else {
	  System.out.println(ftplrs.getName() + " is not writable");
        }
      } 
    
    }
    if(haswdirs == false) return null;
    return toret;
  }
  public void work()
  {
    System.out.print("Connection to " + fhost + "...");
    if(connect() == false)
    {
      System.out.println("ERROR");
      return;
    }
    System.out.println("OK");
    System.out.print("Logging in as anonymous...");
    try {
      ftp.ftpConnect(fhost, "anonymous", "pub-monkey@monkey-pub.org");
    } catch(Exception e) {
      System.out.println("ERROR");
      return;
    }
    
    System.out.println("OK");
    HashSet wdirs = listDirectory();
    if(wdirs == null) return;
    Iterator it = wdirs.iterator();
    writeLog("Writable Directories on " + fhost + ": ");
    while(it.hasNext())
    {
      writeLog((String)it.next() + " ");
    }
    close();
    writeLog("\n");
  }
}
