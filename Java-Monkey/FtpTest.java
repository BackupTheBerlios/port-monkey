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

import ftp.*;
import java.io.*;
import java.util.*;

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
      ftp.ftpConnect(fhost, "anonymous", "pub-monkey@monkey-pub.org");
    } catch(Exception e) {
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
    HashSet set = new HashSet();
    FtpListResult ftplrs = null;
    try {
      ftp.setDirectory("/");
      ftplrs = ftp.getDirectoryContent();
    } catch(Exception e) {
      System.out.println(e);
    }

    while(ftplrs.next())
    {
      int type = ftplrs.getType();
      if(type == FtpListResult.DIRECTORY)
      {
        System.out.println(ftplrs.getName());
	System.out.println(" ");
	if (ftplrs.isGlobalWritable()) 
	{
	  set.add(ftplrs.getName());
	  System.out.println("is writable");
	} else {
	  System.out.println("is not writable");
        }
      } 
    
    }
    return set;
  }
  public void work()
  {
    if(connect() == false) return;
    HashSet wdirs = listDirectory();
    Iterator it = wdirs.iterator();
    while(it.hasNext())
    {
      writeLog((String)it.next());
      close();
    }
  }
}
