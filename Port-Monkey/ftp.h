#include <cc++/thread.h>
#include <cc++/socket.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace ost;
using namespace __gnu_cxx;

class ftpTest
{
private:
  string wdir, dir, fhost;
  bool writable, connected;
  TCPStream* connection;
  Mutex logger, consend;
  ofstream* logfilep;
public:
  ftpTest(const string& host, ofstream* ofstr);
  bool connect();
  void work();
  bool isWritable();
  string writable_dir();
  int login();
  void send(const string& tosend);
  void logwrite(const string& add);
};
