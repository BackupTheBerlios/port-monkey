#include "ftp.h"

ftpTest::ftpTest(const string& host, ofstream* ofstr)
{
  fhost = host;
  logfilep = ofstr;
}

bool ftpTest::connect()
{
  cout << "Connecting to " << fhost << endl;
  try {
    connection = new TCPStream(InetHostAddress(fhost.c_str()), 21);
  } catch(...) {
    cout << "Could not connect!" << endl;
    return false;
  }
  if(!connection->isConnected())
  {
    cout << "Could not connect!" << endl;
    return false;
  }

  cout << "Connected successfully!" << endl;
  connected = true;
  return true;
}

void ftpTest::work()
{
  if(!connect())
  {
    return;
  }
  int result = login();
  if(result == 1 || result == 2) 
  {
    delete connection;
    delete this;
    return;
  }

  // cout << endl << endl;
  // cout << "TODO:" << endl;
  //  cout << "Check writability" << endl << "write out to a log-file" << endl;
  return;
}

bool ftpTest::isWritable()
{
  return writable;
}

void ftpTest::send(const string& tosend)
{
  consend.enterMutex();
  cout << "Port-Monkey: " << tosend << endl;
  (*connection) << tosend << endl;
  consend.leaveMutex();
  return;
}

string ftpTest::writable_dir()
{
  return wdir;
}

int ftpTest::login()
{ 
  string ffd;
    
  getline(*connection, ffd);
   if(ffd == "")
   {
     cout << "No Here is no FTP-Server." << endl;
     return 1;
   }

   if(ffd.substr(0, 3) == "220")
   {
     cout << "Found a FTP-Server." << endl;
   } else {
     cout << "Here in no FTP-Server." << endl;
     return 1;
   }
   
  this->send("USER anonymous");
  getline(*connection, ffd);
  if(ffd.substr(0, 3) != "331" && ffd.substr(0, 3) != "230")
  {
    cout << "anonymous-access not allowed (1)" << endl;
    this->send("QUIT");
    return 2;
  }
  if(ffd.substr(0, 3) == "230")
  {
    goto right;
  }
  
  this->send("PASS port-monkey@monkey-port.org");
  getline(*connection, ffd);
  if(ffd.substr(0, 3) == "530")
  {
    cout << "anonymous-access not allowed (2)" << endl;
    this->send("QUIT");
    return 2;
  }
  
right:
  if(ffd.substr(0, 3) == "230") {
    cout << "Logged in as anonymous, maybe a pub :)" << endl;
    this->logwrite("Found a public FTP-Server at " + fhost);
    
    this->send("QUIT"); // ATM
    return 0;
  } 
}

void ftpTest::logwrite(const string& add)
{
  logger.enterMutex();
  (*logfilep) << add << endl;
  logger.leaveMutex();
}

