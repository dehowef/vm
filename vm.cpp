//Dehowe Feng 998259086
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

//need clock replacement algorithm
//first 16 accesses don't do anything

using namespace std;


struct page{
    string address;
    int usebit;
    page(){
        usebit = 0;
    };
};


int main(int argc, char *argv[]){
    
    page headerline[16];
    page RAM[4];
    string read;
    int index = 0; //buffer index;
    
    char *filename = argv[1];
    
    ifstream inputfile;
    inputfile.open(filename);
    
    
    ofstream outputfile("vm-out.txt");

    for(int i = 0; i < 16; i++){
        getline(inputfile, read);
        headerline[i].address = read;
        headerline[i].usebit = 0;
    }
    
    for(int i = 0; i < 16; i++){
//        cout << "page " << i << " range is: " << hex << headerline[i].address << endl;
    }
    
    while(inputfile){
        getline(inputfile,read);
        
        if(!read.empty())
        read.replace(5,3, "000"); //since there's that linebreak at the end of the file
        else break;
        
  //      cout << "current read is " << read << endl;
        
        for(int i = 0; i < 4; i++){ // read through RAM
            
            if(RAM[i].address == read){// if there's a hit
  //              cout << "read, nothing changed. " << endl;
                RAM[i].usebit = 1;
                break;
            }
            
            else if(RAM[i].address.empty()){//if nothing loaded
  //              cout << "nothing loaded, now loading " << endl;
                RAM[i].address = read;
                RAM[i].usebit = 1;
                index = (i + 1)% 4;
                break;
            }
            else if (i == 3){  // no match. this is where shit gets messy
                
                for (int j = 0; j < 5; j++){
                    if(RAM[(index + j)% 4 ].usebit == 1){ //if usebit is 1, set to 0
                        RAM[(index + j)% 4 ].usebit = 0;
                    }
                    else if(RAM[(index + j)% 4 ].usebit == 0){
                        RAM[(index + j)% 4 ].usebit = 1;
                        RAM[(index + j)% 4 ].address = read;
                        index = (index + j + 1)% 4;
                        break;
                    }
                }
            }//end if
            
        }//end for

        for(int i = 0; i < 4; i++){
            if(i > 0 && !RAM[i].address.empty())
                outputfile << " ";
            
            outputfile << RAM[i].address;
        }
        outputfile << endl;
    }//end while
    
    inputfile.close();
    outputfile.close();
    return 0;
} //end main
