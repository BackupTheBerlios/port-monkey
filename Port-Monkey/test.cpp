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

#include <cc++/ftp.h>
#include <iostream>
using namespace std;
using namespace ost;
using namespace __gnu_cxx;
int main()
{
  
  FTPSocket* ftps = new FTPSocket(InetHostAddress("216.10.26.161"));
  
  ftps->login("anonymous", "affe@");
  ftps->cwd("/");
  //cout << ftps->pwd() << endl;
  try {
  		FTPSocket::DirType d = ftps->getDir(ftps->pwd());
		for(FTPSocket::DirType::iterator i = d.begin(); i != d.end(); ++i)
		{
			if((*i).canOtherWrite() && (*i).isDir())
				cout << (*i).getName() << " is writable" << endl; //(*i).getLine()
		}
	} catch(...) {
		cout << "Not Listable" << endl;
	}
  
  ftps->quit();
}
