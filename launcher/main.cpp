/***********************************************************************
 *  Copyright - Pacific Community                                      *
 *  Droit de copie - Communauté du Pacifique                           *
 *  http://www.spc.int/                                                *
 ***********************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

using namespace std;

#define CONFIG_FILE "config.ini"

typedef map<string, string> ConfigInfo;

/**
 * Find current working directory.
 * Note: on macOS when invoked from the command line returns current folder, when double-clicking on the executable rturns the home folder.
 * @return A {@code String} instance.
 */
const string getWorkDir() {
  char cCurrentPath[FILENAME_MAX];
  if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
    cerr << "Could not retrieve current directory." << endl;
    exit errno;
  }
  cCurrentPath[sizeof(cCurrentPath)-1] = '\0';
  const string result(cCurrentPath);
  return result;
}

#ifdef __APPLE__
#include <mach-o/dyld.h>
/**
 * Gets the base directory.
 * <br>On macOS this is the directory in which the executable is.
 * @return A {@code string} instance.
 */
const string getBaseDir() {
  char path[1024];
  uint32_t size = sizeof(path);
  if (_NSGetExecutablePath(path, &size) != 0) {
    cerr << "Could not locate current directory." << endl;
    exit errno;
  }
  char* cleanedPath = realpath(path, NULL);
  const string result(cleanedPath);
  const int index = result.find_last_of('/');
  return result.substr(0, index);
}
#endif

/**
 * Read config file from within the working directory.
 * <br>This function fails with {@code errno} if the config cannot be read.
 * @return A {@code ConfigInfo} instance.
 */
ConfigInfo readConfig() {
  const string path = CONFIG_FILE;
  ifstream configFile(path);
  if (!configFile.is_open()) {
    cerr << "could not open " << CONFIG_FILE << "." << endl;
    exit errno;
  }
  ConfigInfo config;
  string line;
  while(getline(configFile, line)) {
    istringstream is_line(line);
    string key;
    if (getline(is_line, key, '=')) {
      string value;
      if (key[0] == '#') {
	continue;
      }
      if (getline(is_line, value)) {
      }
      config[key] = value;
    }
  }
  configFile.close();
  return config;  
}

/**
 * Program entry point.
 * @param arcs Number of arguments.
 * @param argv Arguments from the command line.
 * @return Error code.
 */
int main(const int argc, const char * argv[]) {
  // Get Working directory (the directory where we are running from).
  const string workDir = getWorkDir();
  cout << "Work dir: " << workDir << endl;

  // Get base directory (the directory where our executable is located).
  const string baseDir = getBaseDir();
  cout << "Base dir: " << baseDir << endl;

  // Change current directory.
  chdir(baseDir.c_str());
  
  // Get app name from config file.
  ConfigInfo config = readConfig();
  const string app = config["app"];
  cout << "App: " << app << endl;
  if (app.empty()) {
    cerr << "No application defined in " << CONFIG_FILE << "." << endl;
    return errno;
  }

  // Build command.
  const string command = baseDir + "/" + app;
  cout << "Command: " << command << endl;

  // Run command.
  const int errCode = system(command.c_str());
  if (errCode != EXIT_SUCCESS) {
    cerr << "Command returned " << errCode << endl;
  }

  return errCode;
}
