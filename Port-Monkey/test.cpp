#include <cc++/ftp.h>
#include <iostream>
using namespace std;
using namespace ost;
using namespace __gnu_cxx;
int main()
{
  
  FTPSocket* ftps = new FTPSocket(InetHostAddress("216.10.26.231"));
  
  ftps->login("anonymous", "affe@");
  ftps->cwd("/incoming");
  cout << ftps->pwd() << endl;
  FTPSocket::DirType d = ftps->getDir(ftps->pwd());
    for(FTPSocket::DirType::iterator i = d.begin(); i != d.end(); ++i)
        cout << (*i).getUser()  << '\t'
	     << (*i).getGroup() << '\t'
	     << (*i).getName()  << ':' << endl;
  //if(dirtest)  //<-- need GoGi or an other good C++-Coder to fix
  //{
  //  cout << "/incoming kann von jedem beschreiben werden." << endl;
 // } else {
  //  cout << "/incoming kann nicht von jedem beschreiben werden." << endl;
 // }
  
  ftps->quit();
}
