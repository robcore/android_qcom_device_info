#include <string>

using namespace std;

bool IsNexus5();

bool FileExists(const char *filename);

bool IsOn(const char *infile);

string BuffFile(const char *infile);

string LineFile(const char *infile);

void cpy (const char *infile, const char *outfile);

void PrintDirContent(const char *path);

void ExecuteScript(const char *content);

void write_to_file(int val, const char *path);
