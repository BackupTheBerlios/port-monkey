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
  License in the COPYING file that comes with YaCE3. If
  not, write to Affero, Inc., 510 Third Street, Suite 225, San
  Francisco, CA 94107 USA.
*/

#include "ftp.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cc++/thread.h>

using namespace std;


Mutex m_affe;

int main(int argc, const char* argv[])
{
  ofstream* lofp;
  try {
    cout << "Opening Logfile...";
    string logname = "pubs";
    lofp = new ofstream(logname.c_str(), ios::out | ios::app);
    if(!(*lofp))
    throw 1;
  } catch(...) {
    cout << "ERROR" << endl;
    exit(1);
  }
  cout << "OK" << endl;
				    
  
  vector<string> hosts;
  cout << "Pub-Monkey 0.00 Beta started" << endl;
  
  string host;
  
  if(argc != 2)
  {
    cout << "Usage: " << argv[0] << " <Hostname or IP>" << endl;
    hosts.push_back("localhost");
  } else {
    host = string(argv[1]);
	int dot;
    if(host.find("*") != string::npos)
    {
      string fistr, sestr, thstr, fostr;
      
      dot = host.find(".");
      fistr = host.substr(0, dot);
      host = host.substr(dot+1, host.length()-dot);
      
      dot = host.find(".");
      sestr = host.substr(0, dot);
      host =  host.substr(dot+1, host.length()-dot);
    
      dot = host.find(".");
      thstr = host.substr(0, dot);
      host =  host.substr(dot+1, host.length()-dot);
    
      dot = host.find(".");
      fostr = host.substr(0, dot);
      host =  host.substr(dot+1, host.length()-dot);
    
      ostringstream os;
      if(fistr == "*")
      {
         for(int i=1; i != 256; i++)
	 {
	   os << i;
	   hosts.push_back(os.str() + "." +  sestr + "." + thstr + "." + fostr);
	   os.str("");
	 }
      } else if(sestr == "*") {
        for(int i=1; i != 256; i++)
	{
	  os << i;
	  hosts.push_back(fistr + "." +  os.str() + "." + thstr + "." + fostr);
	  os.str("");
	}
      } else if(thstr == "*") {
        for(int i=1; i != 256; i++)
	{
	  os << i;
	  hosts.push_back(fistr + "." +  sestr + "." + os.str() + "." + fostr);
	  os.str("");
	}
      } else if(fostr == "*") {
        for(int i=1; i != 256; i++)
        {
	  os << i;
          hosts.push_back(fistr + "." +  sestr + "." + thstr + "." + os.str());
	  os.str("");
        }
      } else {
        hosts.push_back(host);
      }
    } else {
	  hosts.push_back(host);
	}
  }
  
  vector<string>::iterator it;
  ftpTest* affe;
  for(it = hosts.begin(); it != hosts.end(); ++it)
  {
    m_affe.enterMutex();
	cout << endl;
    affe = new ftpTest(*it, lofp);
    affe->work();
	delete affe;
	m_affe.leaveMutex();
  }
}
