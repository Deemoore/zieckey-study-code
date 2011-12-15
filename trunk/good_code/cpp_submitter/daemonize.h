#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <libdaemon/daemon.h>

class Daemonize
{
  public:
    Daemonize();
    ~Daemonize();
    void Init();

  private:
    void Finish();
};
/*
bool pid_file_delete(const char *pid_directory, int argc, char* argv[], char* pid_directory_file);

bool pid_file_write(const char *pid_directory, int argc, char* argv[], char* pid_directory_file);
*/
