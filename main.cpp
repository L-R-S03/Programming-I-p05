// -----------------------------------------------------------------------------------------------------------------------
//program p05 accepts the name of an input and output file via the command line or by prompting
//reads pairs of base 10 numbers alongside a foreign base to converts them to and writes the conversion to the output file
//errors are handled for too many arguments on the command line, nonexsistent file, or invalid numbers or bases
//------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
//Method convert takes a base and value and calculates the base conversion string returning the string
string convert(int base, int value)
{
        //this is a string of all hex digit values
        string hex="abcdefghijklmanopqrstuvwxyz";
        //sets the initial dividend to the base 10 value
        int dividend=value;
        int remainder=0;
        int conversion=0;
        string result="";
        //while the dividend is more than 0
        while(dividend>0)
        {
                //the remainder is found using the mod operator qurg the duvusor and the base
                remainder=dividend%base;
                //the new dividend is found by casting the dividend divided by the base to an int
                dividend=int(dividend/base);
                //if the base is less than 10 so no letters are involved
                if(base<10)
                {
                        //convert the remainder to a string and add it to the beginning of the result string the function returns
                        result = to_string(remainder)+result;
                }
                //if base is greater than 10 digits are involved
                if(base>10)
                {
                        //if the remainder is greater than 10 calculate needed hex digit by subtracting the remainder from 10
                        if(remainder>9)
                        {
                                conversion=remainder-10;
                                //adds hex digit to the end of the returned string
                                result= hex.substr(conversion,1)+result;
                        }
                        //otherwise its a normal number and does the same as base 9 and below
                        else
                        {
                                result=to_string(remainder)+result;
                        }
                }
        }
        //return the completed string of the conversion
        return result;
}
//function ConversionMgr returns nothing and takes a ifstream and ofstream via reference to read in the values from the file and write to the output file
void ConversionMgr(ifstream &i,ofstream &o)
{
        int value,base,temp;
        //for the length of the entire input file
        for(;; )
        {
                //reads in the values for the decimal value and the converted base
                i>> value;
                i>>base;
                //if the file has reached the end of the file exit the loop v
                if(i.eof())
                {
                        break;
                }
                //if the decimal value is not within range write that it is out of range to the output
                if(value < 0 or value > 2147483647)
                {
                        o << value << " is outside the range of valid decimal values."<<endl;
                }
                //if the base is not within range write that it is out of range to the output
                else if(base<2 or base > 36)
                {
                        o << base << " is outside the range of valid foreign bases." <<endl;
                }
                //otherwise input is valid and it uses the convert function for the conversion and writes the value to the output file
                else
                {
                        o <<value << " base 10 equals " <<  convert(base,value)  << " base " <<base << "." <<  endl;
                }

        }

}
//function CommandLineException returns nothing and accepts two parameters, one for the max number of command arguments and one for the number entered
void CommandLineException(int max, int num)
{
        //prints the number of max arguments allowed and the number entered before exiting with a exit failure
        cout << endl;
        cout << "A maximum of " << max << " arguments are permitted." << endl;
        cout << num << " arguments were entered." << endl;
        cout << "Program terminated." << endl;
        exit(EXIT_FAILURE);
}
//function FileException returns nothing an accepts a char pointer for the file name
void FileException(char* fn)
{
        //prints that the file could not be opened and the program is being terminated before running an exit with an exit failure
        cout << endl;
        cout << "File " << fn << " could not be opened ." << endl;
        cout << "Program terminated." << endl;
        exit(EXIT_FAILURE);
}
//int main can accept 1 to 3 arguments from the command line as parameters being the program to run, the input file name and output file name
int main(int argc, char* argv[])
{
        //inits the variables for the output and input files
        char ifn[255];
        char ofn[255];
        //swotch statement is used dependent on how many arguments are entered on the command line
        switch(argc)
        {
                //if case is one only the program name was entered so it prompts and collects the input and output file name
                case 1:
                        cout << "Enter the input file name. ";
                        cin >> ifn;
                        cout << "Enter the output file name. ";
                        cin >> ofn;
                        break;
                //if case is 2 the program and input file name was entered so it collects  the input file name from the command line and prompts and
                //prompts and collects the output file name
                case 2:
                        strcpy(ifn, argv[1]);
                        cout << "Enter the output file name. ";
                        cin >> ofn;
                        break;
                //if there are 3 arguments on the command line all information was entered and it is collected from the command line
                case 3:
                        strcpy(ifn, argv[1]);
                        strcpy(ofn, argv[2]);
                        break;
                //otherwise an invalid number of arguments was entered so the CommandLineException is ran with the number of arugments
                default:
                        CommandLineException(2,argc-1);
                        break;
        }
        //ifstream i opens the input file
        ifstream i(ifn);

        //if the input file doesn't exist a FileExeption is thrown using the FileException function
        if(!i)
        {
                FileException(ifn);
        }
        //same process as above repeated with the output file
        ofstream o(ofn);
        if(!o)
        {
                FileException(ofn);
        }
        //otherwise all the files exist and the ConversionMgr function is passed the files and completes the conversion
        ConversionMgr(i,o);
        return 0;
}
