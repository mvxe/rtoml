#include <iostream>
#include "rtoml.hpp"


int main(){
    int a=4;
    double b=57;
    
    rtoml::vsr mapa("a.toml");
    mapa["abcd"]=a;
    std::string st="X+1-2*sin(Y)";
    mapa["x"]["xx"]=st;
    mapa["x"]["xx"].comments.push_back(" hello there!");
    mapa["x"]["xx"].comments.push_back(" sec line.");
    
    
    rtoml::vsr mapb;
    mapa["x"]["yy"]=mapb;
    mapa["x"]["yy"].comments.push_back(" a section.");
    mapb["xxx"]=b;
    mapb["xxx"].comments.push_back(" Some random var.");
    double c=534;
    mapb["sd"]["zzz"]=c;
    std::string entryname="entry3";
    mapb["sd"][entryname]=a;
    mapb["sd"][entryname].comments.push_back(" Something about entry3");
    
    
    mapa.load(false);
    
    double ha=*mapa["abcd"].get<int>();
    std::string be=*mapa["x"]["xx"].get<std::string>();
    std::cerr<<ha<<" "<<be<<"\n";
    std::cerr<<b<<"\n";
    std::cerr<<"fname for mapa: "<<mapa.getConfFilename()<<"\n";
    
    //mapa.load(false, "b.toml");
    
    mapa.save(true);
}
