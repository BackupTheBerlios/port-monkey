#include "ftp.h"
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;



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
  cout << "Port-Monkey 0.00 Pre-Alpha started" << endl;
  
  string host = string(argv[1]);
  
  if(argc != 2)
  {
    cout << "No/too many Host(s) specivied, using localhost" << endl;
    hosts.push_back("localhost");
  } else {
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
    cout << endl;
    affe = new ftpTest(*it, lofp);
    affe->work();
  }
}
