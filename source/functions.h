#include <string>

#define SIZE 1024

using namespace std;

void getProperty(string line1, unsigned short s);

void getCPUInfo();

void getBatteryInfo();

bool getVddLevels();

void getKernelInfo();

void getLogs();

void getVMStats();

void getRAMInfo();

void getDiskInfo();

/* ADVANCED MENU */

void getHotPlugInfo();

void getGPUInfo();

void getExtraKernelInfo(int p);


/* CUSTOMIZER */

void tune(int p);
