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
#include <cc++/ftp.h>
#include <vector>

ftpTest::ftpTest(const string& host, ofstream* ofstr)
{
  fhost = host;
  logfilep = ofstr;
}

bool ftpTest::connect()
{
  cout << "Connecting to " << fhost << "...";
  try {
    connection = new FTPSocket(InetHostAddress(fhost.c_str()));
  } catch(...) {
    cout << "Could not connect!" << endl;
    return false;
  }
  cout << "connected" << endl;
  try {
	  cout << "Loging in...";
	  connection->login("anonymous", "monkey@monkey.com");
  } catch(...) {
	  cout << "Could not login as anonymous" << endl;
	  return false;
  }

  cout << "logged in" << endl;
  connected = true;
  return true;
}

void ftpTest::work()
{
  if(!connect())
  {
    return;
  }
  	vector<string> wdirs;
	connection->cwd("/");
	FTPSocket::DirType d = connection->getDir(connection->pwd());
	bool hasWritableDirs = false;
    for(FTPSocket::DirType::iterator i = d.begin(); i != d.end(); ++i)
	{
		// cout << (*i).getLine() << endl;
		if((*i).canOtherWrite() && (*i).isDir())
		{
			wdirs.push_back((*i).getName());
			hasWritableDirs = true;
			cout << "Access on " << (*i).getName() << endl;
		} else if((*i).isDir() && !(*i).canOtherWrite())cout << "No access on " << (*i).getName() << endl;
	}
	
	if(hasWritableDirs)
	{
		this->logwrite("Writable Directories on " + fhost + ": ");
		vector<string>::iterator it;
		for(it=wdirs.begin(); it != wdirs.end(); ++it) this->logwrite((*it) + " ");
		this->logwrite("", true);
	}
	
	connection->quit();

}

void ftpTest::logwrite(const string& add, bool nl)
{
  logger.enterMutex();
  (*logfilep) << add;
  if(nl) (*logfilep) << endl;
  logger.leaveMutex();
}
