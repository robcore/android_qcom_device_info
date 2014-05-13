#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include <constants.hpp>
#include <functions.hpp>
#include <classes.hpp>
#include <helpers.hpp>

using namespace std;

static void _error(int val)
{
	fprintf(stderr,"Invalid value(%d), aborting...\n",val);
}

class FileR {
	
	private:
		char c,*status;
		int val;
		string path;
		bool isChar,on;

	void init()
	{
		ifstream in(path.c_str());
			status = new char[8];
			strcpy(status,"OFF");
			on = false;

			if(isChar) {
				in>>c;
				if(c == 'Y' || c == 'y') {
					strcpy(status,"ON");
					on = true;
				}

			} else {

				in>>val;
				if(val) {
					strcpy(status,"ON");
					on = true;
				}
			}
			in.close();
	}
			
	public:
		FileR(string path,bool isChar) {
			this->path = path;
			this->isChar = isChar;
			init();
		}

	void sswitch()
	{
		ofstream out(path.c_str());
		if(isChar && on) {
			out<<"N";
			out.close();
			return;
		}

		if (isChar && !on) {
			out<<"Y";
			out.close();
			return;
		}

		if(!isChar) {
			out<<(!on);
			out.close();
			return;
		}
	}

	string stat() { init(); string ret(status); return ret; }

	~FileR() { delete [] status; }
};

void tune(int p)
{
/*
 * 1 - CPU Temp Threshold
 * 2 - Vibration Amp
 * 3 - Fast Charge
 * 4 - TCP
 * 5 - Sound Control Parameters(Franco)
 * 6 - GPU Up threshold
 * 7 - GPU Down threshold
 * 8 - Max GPU Freq
 * 9 - Hotplug
 * 10 - Governor control
 * 11 - CPU Freq Control
 * 12 - Eco Mode
 * 13 - INTELLIPLUG
 * 14 - Intellithermal
 * 15 - Dyanimc FSYNC
 * 16 - FauxSound
 */

	int val;
	unsigned int nr;
	SysfsIO TUNNER;
	SysfsVector V_TUNNER;
	string content;
	char c;

	switch (p)
	{
		case 0:
			return;

		case 1:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<30 || val>150)
				return _error(val);
			else
				 TUNNER.create_w(TEMP_THRESHOLD,val);
			getExtraKernelInfo(p);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 2:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(VIBRATION_AMP,val);
			getExtraKernelInfo(p);
			
			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 3:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value(ON:1 OFF:0):");
			fscanf(stdin,"%d",&val);

			if (val != 1 && val != 0)
				return _error(val);
			else
				 TUNNER.create_w(FORCE_FAST_CHARGE,val);
			getExtraKernelInfo(p);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 4:
			getExtraKernelInfo(p);
			fprintf(stdout,"New TCP: ");
			cin.ignore();
			getline(cin,content);

			if(TUNNER.create_w(AVAILABLE_TCP_CONGESTION_ALGORITHM,
						TCP_CONGESTION_ALGORITHM,content))
				getExtraKernelInfo(p);
			else
				return _error(-1);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 5: //FIXME
			V_TUNNER.populate_vector(SOUND_CONTROL_PATH);
			V_TUNNER.print_vector();
			fprintf(stdout,"Choose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);
			if(nr>V_TUNNER.vsize()-1)
				return _error(nr);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>20)
				return _error(val);
			else
				 V_TUNNER.write_vector(nr,val);
			V_TUNNER.populate_vector(SOUND_CONTROL_PATH);
			V_TUNNER.print_vector();

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
			
		case 6:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(GPU_UP_THRESHOLD,val);
			getExtraKernelInfo(p);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		case 7:
			getExtraKernelInfo(p);
			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			if (val<0 || val>100)
				return _error(val);
			else
				 TUNNER.create_w(GPU_DOWN_THRESHOLD,val);
			getExtraKernelInfo(p);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 8:
			getGPUInfo(p);
			getGPUInfo(-1);
			V_TUNNER.populate_vector(GPU_AVAILABLE_FREQ,NULL);
			fprintf(stdout,"Choose new MAX GPU Freq value:\n");
			V_TUNNER.print_vector(NULL);
			
			cin.ignore();
			fscanf(stdin,"%d",&val);
				
			if(V_TUNNER.write_vector(GPU_MAX_FREQ,val))
				getGPUInfo(p);
			else
				return _error(val);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 9:
			V_TUNNER.populate_vector(HOTPLUG_PATH);
			V_TUNNER.print_vector();
			fprintf(stdout,"Choose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if(nr>V_TUNNER.vsize()-1)
				return _error(nr);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			V_TUNNER.write_vector(nr,val);
			V_TUNNER.populate_vector(HOTPLUG_PATH);
			V_TUNNER.print_vector();
			
			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 10:
			getCPUInfo(p);
			V_TUNNER.populate_vector(SCALING_AVAILABLE_GOVS,NULL);
			V_TUNNER.print_vector(NULL);

			fprintf(stdout,"Choose new governor number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if(V_TUNNER.write_vector(CURRENT_CPU_GOV,nr))
					getCPUInfo(p);
			else
				return _error(nr);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 11:
			getCPUInfo(p);
			V_TUNNER.populate_vector(SCALING_AVAILABLE_FREQ,NULL);
			fprintf(stdout,"1 - Min\n2 - Max\nValue: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if (nr == 1)
			{
				fprintf(stdout,"Choose new MIN value:\n");
				V_TUNNER.print_vector(NULL);
				cin.ignore();
				fscanf(stdin,"%d",&val);
				
				if(V_TUNNER.write_vector(CURRENT_MIN_CPU_FREQ,val))
					getCPUInfo(p);
				else
					return _error(val);
			}
			else if (nr == 2)
			{
				fprintf(stdout,"Choose new MAX value:\n");
				V_TUNNER.print_vector(NULL);
				cin.ignore();
				fscanf(stdin,"%d",&val);
				
				if(V_TUNNER.write_vector(CURRENT_MAX_CPU_FREQ,val))
					getCPUInfo(p);

				else
					return _error(val);
			}
			else
				return _error(nr);

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;

		case 12:
		{
			FileR EM(ECO_MODE,false);
			fprintf(stdout,"Eco Mode is %s, switch?(y/n): ",
						EM.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				EM.sswitch();

			fprintf(stdout,"Eco Mode is %s\n",
						EM.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 13:
		{
			FileR IP(INTELLIPLUG,false);
			fprintf(stdout,"Intelliplug is %s, switch?(y/n): ",
						IP.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				IP.sswitch();

			fprintf(stdout,"Intelliplug is %s\n",
						IP.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 14:
		{
			FileR IT(INTELLITHERMAL,true);
			fprintf(stdout,"Intellithermal is %s, switch?(y/n): ",IT.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				IT.sswitch();

			fprintf(stdout,"Intellithermal is %s\n", IT.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}

		case 15:
		{
			FileR DF(DYN_FSYNC,false);
			fprintf(stdout,"Dynamic Fsync is %s, switch?(y/n): ",DF.stat().c_str());

			cin.ignore();
			fscanf(stdin," %c",&c);

			if(c == 'y' || c == 'Y')
				DF.sswitch();

			fprintf(stdout,"Dynamic Fsync is %s\n", DF.stat().c_str());

			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;
		}
			

		case 16:
			V_TUNNER.populate_vector(FAUX_SOUND);
			V_TUNNER.print_vector();
			fprintf(stdout,"Choose Interface number: ");
			cin.ignore();
			fscanf(stdin,"%d",&nr);

			if(nr>V_TUNNER.vsize()-1)
				return _error(nr);

			fprintf(stdout,"New Value:");
			fscanf(stdin,"%d",&val);

			V_TUNNER.write_vector(nr,val);
			V_TUNNER.populate_vector(FAUX_SOUND);
			V_TUNNER.print_vector();
			
			fprintf(stdout,"\nPress enter to continue");
			cin.ignore();
			getline(cin,s);
			break;	
	  
		
		default:
			break;
	}
}
