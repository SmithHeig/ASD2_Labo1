/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <map>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    std::map<std::string,int> indexs;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {         
        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        
        std::ifstream s(filename);
        
        int id = 0;
        
        this->g = new Graph(300000); //sale
        
        
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            //Film
            indexs.insert(std::pair<std::string,int>(names.at(0),id));
            int idFilm = id++;
            for(int i = 1; i < names.size(); ++i) {
                // add new actor
                if(contains(names.at(i)) == true){
                    g->addEdge(idFilm,index(names.at(i)));
                } else {
                    indexs.insert(std::pair<std::string,int>(names.at(i),id));
                    g->addEdge(idFilm,id++);
                }
            }
        }
        s.close();
        
        /* A IMPLEMENTER */
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) {
        if(indexs.find(name) != indexs.end()){
            return true;
        }
        return false;
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) {
        return indexs.find(name)->second;
    }
    
    //symbole correspondant au sommet
    std::string name(int idx) {
        for(std::map<std::string, int>::iterator it = indexs.begin(); it != indexs.end(); ++it){
            if(it->second == idx){
                return it->first;
            }
        }
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string & name) {
        return g->adjacent(index(name));
    }
    
    const Graph& G() {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
