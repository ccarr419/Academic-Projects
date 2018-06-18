/*****************************************************************************
* Author:	Christian Carreras
* File:		coordinateConvert.cpp
* Created:	11/30/2015
* About:	This program converts latitude and longitude coordinates from
*		an input file to computer notation in an output file.
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//This structure holds an individual longitude or latitude's coordinates
struct coordinate
{
	int degrees;
	double minutes;
	double seconds;
	char hemisphere;
};

//This structure holds the complete latitude and longitude coordinates
struct coordinates
{
	coordinate lat;
	coordinate lon;
};

/*****************************************************************************
* Function:	convert
* Parameters:	const coordinate& - input only
* Return Value:	double - the converted coordinate
* About:	Converts a coordinate object into a coordinate number
*****************************************************************************/
double convert(const coordinate&);

int main()
{
	ifstream inf; //input file
	ofstream ofs; //output file
	coordinates c;
	
	inf.open("coordinates.dat");
	ofs.open("convertedCoordinates.dat");
	cout << "Converting coordinates... ";
	while(!inf.eof())
	{
		inf >> c.lat.degrees;
		if(c.lat.degrees == -1) //-1 designates end of input
			break;
			
		inf >> c.lat.minutes >> c.lat.seconds >> c.lat.hemisphere;
		inf >> c.lon.degrees >> c.lon.minutes >> c.lon.seconds;
		inf >> c.lon.hemisphere;
		
		ofs << setprecision(8);
		ofs << convert(c.lat);
		ofs << setw(4) << "\t";
		ofs << convert(c.lon) << endl;
	}	
	cout << "done\n";
	inf.close();
	ofs.close();
	return 0;
}

//Takes the coordinates individual values to converts them into
//a floating-point number. The new converted number is the return value.
double convert(const coordinate& c)
{
	int degree = c.degrees;
	double minute = c.minutes*60;
	double second = c.seconds;
	double coord = degree + ((minute+second)/3600);
	//Western and Southern hemispheres designate negative numbers
	if(tolower(c.hemisphere) == 'w' || tolower(c.hemisphere) == 's')
		coord = -1 * coord;
	return coord;
}