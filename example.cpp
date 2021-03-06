#include <iostream>
#include "rtoml.hpp"


int main(){
    int a=4;
    double b=57;
    
    rtoml::vsr mapa("a.toml");
    mapa["abcd"]=a;
    
    int d[3]{1,2,3};
    mapa["u"]=d[0];
    mapa["b"]=d[1];
    mapa["g"]=d[2];
    std::vector<int> vec{1,2,3};
    mapa["vec"]=vec;
    std::vector<int> lvec{1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3};
    mapa["lvec"]=lvec;
    std::unordered_map<std::string, double> map{{"a",1},{"b",2},{"c",3}};
    mapa["map"]=map;
    mapa["map"].comments().push_back(" Something about map");
    
    std::string st="X+1-2*sin(Y)";
    mapa["x"].comments().push_back(" Something about x");
    mapa["x"]["xx"]=st;
    mapa["x"]["xx"].comments().push_back(" hello there!");
    mapa["x"]["xx"].comments().push_back(" sec line.");
    
    
    rtoml::vsr mapb;
    mapa["x"]["yy"]=mapb;
    mapa["x"]["yy"].comments().push_back("indented section");
    mapb.comments().push_back("indented section direct");
    mapb["xxx"]=b;
    mapb["xxx"].comments().push_back(" Some random var.");
    double c=534;
    mapb["sd"]["zzz"]=c;
    std::string entryname="entry3";
    mapb["sd"][entryname]=a;
    std::string longs("This a long single line string#########################################################################################################################################################");
    mapb["longs"]=longs;
    std::string longsnl="this is a line with newline\nnext line\nanother line\nlast line";
    mapb["longsnl"]=longsnl;
    
    mapa["x"]["yb"]["yy"]["rtdf"]=b;
    mapa["x"]["yb"]["yy"].comments().push_back("multiindented section");
    
    mapa.load(false);
    
    double ha=*mapa["abcd"].get<int>();
    std::string be=*mapa["x"]["xx"].get<std::string>();
    std::cerr<<ha<<" "<<be<<"\n";
    std::cerr<<b<<"\n";
    std::cerr<<"fname for mapa: "<<mapa.getConfFilename()<<"\n";
    
    //mapa.load(false, "b.toml");
    
    mapa.save(true);
    c=100;
    mapb.save(true);
    mapb.save(true, "b.toml");
    
    std::cerr<<"try changing a.toml within 10 seconds\n";
    system("sleep 10\n");
    std::cerr<<"mapa changed = "<<mapa.changed()<<"\n";
    std::cerr<<"mapb changed = "<<mapb.changed()<<"\n";
}
