#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

#define DUMP "DUMP"
#define TEMP "Temp"
using namespace std;
class File
{

  public:

     virtual void act(std::string nameOfFile)=0;

};
class SaveToFile:public File
{

  public:

      virtual void act(std::string nameOfFile);


};
class OpenFile:public File
{

  public:
      virtual void act(std::string nameOfFile);


};
class DumpFile:public File
{

  public:
    bool static checkDumpFile(std::string nameOfFile);
    virtual void act(std::string nameOfFile);
    static void copyRealFile(std::string nameOfFile,bool statusOfFile);

};
class SearchFileForBadSaved:public File
{

public:
    virtual void act(std::string nameOfFile);


};
class RealFile:public File
{
  public:
    virtual void act(std::string nameOfFile);


};
///Method
void SaveToFile::act(std::string nameOfFile)
{

    std::string temp;
    std::cout<<"Insert your text: "<<'\n';
    std::getline(std::cin,temp);
    std::ofstream ff(nameOfFile);

    ff<<temp;

    ff.close();


}
void OpenFile::act(std::string nameOfFile)
{

    std::string temp;

    std::ifstream ff(nameOfFile);
    while(std::getline(ff,temp))
    {
        std::cout<<temp<<'\n';
    }


    ff.close();


}

void RealFile::act(std::string nameOfFile)
{
    DumpFile dumpFile;
    dumpFile.act(nameOfFile);
    ///Next

}
bool DumpFile::checkDumpFile(std::string nameOfFile)
{

     FILE *file;
    std::string tempToFOpen = DUMP+nameOfFile;
    file = std::fopen(tempToFOpen.c_str(),"r");
   if(file){


    fclose(file);
    return true;
    }
    else return false;



    ///if Dump File exist, replace file with it

return true;
}
void DumpFile::act(std::string nameOfFile)
{

    if(checkDumpFile(nameOfFile)){

        DumpFile::copyRealFile(nameOfFile,false);

        std::cout<<"Restore file..."<<'\n';
    }
    else {
DumpFile::copyRealFile(nameOfFile,true);
        std::cout<<"Creating file"<<'\n';
    }

}
void DumpFile::copyRealFile(std::string nameOfFile,bool statusOfFile=true)
{
std::string StringDump = DUMP+nameOfFile;
std::string StringTemp = std::string(TEMP)+DUMP+nameOfFile;

   /* auto remFile = [](std::string& name){
    std::remove(name.c_str());
        return [](){};
    };
*/

 if(std::remove((StringTemp.c_str()))==0){std::perror("Previous Running was crashed");
 }
    if(statusOfFile){
    std::ifstream src(nameOfFile,std::ios::binary);
    std::ofstream dst(StringTemp,std::ios::binary);
    dst<<src.rdbuf();

    src.close();
    dst.close();
    std::rename(StringTemp.c_str(),StringDump.c_str());
    }
    else
    {

        std::cout<<"Your save restore before last modification"<<'\n';

        std::ifstream src(StringDump,std::ios::binary);
    std::ofstream dst(nameOfFile,std::ios::binary);
    dst<<src.rdbuf();
    dst.close();



    }

//    std::this_thread::sleep_for(std::chrono::seconds(15));
 if(std::remove((StringDump.c_str()))!=0)std::perror("Error while delete");

}

void SearchFileForBadSaved::act(std::string nameOfFile)
{

if(DumpFile::checkDumpFile(nameOfFile))
{
    DumpFile::copyRealFile(nameOfFile,false);
}

}

///END OF METHOD
void redict(File *fp,std::string nameOfFile)
{
    fp->act(nameOfFile);
}

int main()
{
    std::string nameOfFile="26-06-2017.txt";


    File *fp;
    SaveToFile saveToFile;
    OpenFile openFile;
    RealFile realFile;
    fp = &realFile;
  // auto n =[&](){ redict(fp,nameOfFile);};
   //n();
   //fp = &openFile;
   redict(fp,nameOfFile);

    cout << "Hello world!" << endl;
    return 0;
}
