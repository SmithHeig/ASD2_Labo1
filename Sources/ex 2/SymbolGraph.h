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

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    
    //creation du SymbolGraph a partir du fichier movies.txt
    SymbolGraph(const std::string& filename) {         
        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        int cnt=0; 

        std::ifstream s(filename);
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            for( auto name : names ) 
                std::cout << name << " "; //on affiche le contenu du fichier, vous devrez commencer a remplir le graphe ici
            
            std::cout << std::endl;
        }
        s.close();
        
        /* A IMPLEMENTER */
    }
    
    //verifie la presence d'un symbole
    bool contains(const std::string& name) {
        /* A IMPLEMENTER */
    }
    
    //index du sommet correspondant au symbole
    int index(const std::string& name) {
         /* A IMPLEMENTER */
    }
    
    //symbole correspondant au sommet
    std::string name(int idx) {
        /* A IMPLEMENTER */
    }

    //symboles adjacents a un symbole
    std::vector<std::string> adjacent(const std::string & name) {
        /* A IMPLEMENTER */
    }
    
    const Graph& G() {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
