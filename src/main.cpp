#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <functions.hpp>
#include <helpers.hpp>

#define ver "0.9.76_beta"

using namespace std;

unsigned short ch;
string s;

static void menu(void);
static void AdvancedMenu(void);
static void SysfsTunner(void);
static void ShowMenu(void);
static void ShowAdvancedMenu(void);
static void ShowSysfsTunner(void);

static void clear(void);


int main()
{
	ShowMenu();
	menu();

	clear();
	return 0;
}


static void clear()
{
	remove("/data/local/data.txt");
	remove("/data/local/tmp.sh");
}

static void ShowMenu()
{
	if (IsNexus5())
		fprintf(stdout,"You are running Nexus 5\n");

	fprintf(stdout, "Qualcomm Device Info v%s by educk@XDA-Dev.com\n",ver);
	fprintf(stdout, "Options:\n"
			"1: Get ROM Information\n" 
			"2: Get CPU Information\n"
			"3: Get Battery Information\n"
			"4: Get Voltage Table\n"
			"5: Get Linux Kernel Informations\n"
			"6: Dump logcat and last_kmsg (store them to /sdcard/logs/)\n"
			"7: Get VM Stats\n"
			"8: Get RAM Informations\n"
			"9: Get Disk Informations\n"
			"10: Nexus 5 Extras[WIP]\n"
			"0: Quit\n");
	return;
}

static void ShowAdvancedMenu()
{
	fprintf(stdout,"\nAdvanced Options:\n"
			"1: Get HotPlug Info\n"
			"2: Get GPU Info\n"
			"3: Get Extra Kernel Info\n"
			"4: Sysfs Tunner\n"
			"0: Back\n");
}

static void ShowSysfsTunner()
{
	fprintf(stdout,"\nOptions:\n"
			"1 - CPU Temp Threshold\n"
			"2 - Vibration Amp\n"
			"3 - Fast Charge\n"
			"4 - TCP\n"
			"5 - Sound Control Parameters\n"
			"6 - GPU Up threshold\n"
			"7 - GPU Down threshold\n"
			"8 - Max GPU Freq[WIP]\n"
			"9 - Hotplug\n"
			"10 - Governor control[WIP]\n"
			"11 - CPU Freq Control\n"
			"0: Back\n");
}

static void menu()
{
	do
	{
		fscanf(stdin,"%hu",&ch);

		switch (ch)
		{
			case 0:
				fprintf(stdout, "Bye-Bye !\n");
				break;
			case 1:
				getProperty("ro.build.version.release",1);
				getProperty("ro.build.date",2);
				getProperty("ro.build.user",3);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 2:
				getCPUInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 3:
				getBatteryInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 4:
				getVddLevels();
				
				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 5:
				getKernelInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 6:
				getLogs();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 7:
				getVMStats();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 8:
				getRAMInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 9:
    				getDiskInfo();

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowMenu();
				break;
			case 10:
				ShowAdvancedMenu();
				AdvancedMenu();
				break;
			default: 
				fprintf(stderr, "Unknown value\n");
				break;
		}
	}

	while (ch != 0);
}

static void AdvancedMenu()
{
	do
	{
		fscanf(stdin,"%hu",&ch);

		switch(ch)
		{
			case 0:
				break;
			case 1:
				getHotPlugInfo();
				
				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 2:
				getGPUInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 3:
				getExtraKernelInfo(0);

				fprintf(stdout,"\nPress enter to continue");
				cin.ignore();
				getline(cin,s);
				ShowAdvancedMenu();
				break;
			case 4:
				ShowSysfsTunner();
				return SysfsTunner();

			default:
				fprintf(stderr, "Unknown value\n");
				break;
		}

	}
	while(ch != 0);

	ShowMenu();
	return menu();
}

static void SysfsTunner()
{

	do
	{
		ShowSysfsTunner();
		fprintf(stdout, "Value: ");
		fscanf(stdin,"%hu",&ch);

		if (ch>=0 && ch<=11)
			tune(ch);
		else
			fprintf(stderr, "Unknown value\n");
		
	}
	while (ch != 0);

	ShowAdvancedMenu();
	return AdvancedMenu();
}
