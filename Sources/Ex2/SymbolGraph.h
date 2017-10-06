/* 
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 * Modified by: Jérémie Chatillon et James Smith
 *
 * Created on 26. septembre 2014, 15:08
 * Last modification on 06.10.2017
 * 
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
#include <list>

#include "Util.h"

template<typename GraphType>
class SymbolGraph
{
    typedef GraphType Graph; 
private:
    Graph* g;
    
    // Nous avons décidé d'optimiser la vitesse d'exécution (nombre d'itération) au dépend de la mémoire vive prise.
    // En effet, nous aurions pu créer un ficher contenant nos listes, mais cette version aurait été théoriquement moins rapide.
    // Cependant, elle aurait utilisé moins de RAM
    std::map<std::string, int> indexs;  // .find() en O(log(n)) et .insert() en log(n)
    std::list<int> graph;               // Push_back() et pop_front() sont de complexité constante
    
public:
    
    ~SymbolGraph()
    {
        delete g; 
    }            
    //
    // @brief Creation du SymbolGraph a partir d'un fichier texte
    //
    // @param string: nom du fichier (exemple film.txt)
    //        Le fichier doit être dans le format: 
    //        FILM/ACTEUR/ACTEUR/...
    //        FILM/ACTEUR/ACTEUR/...
    //        ...
    //
    SymbolGraph(const std::string& filename) {         
        //lecture du fichier, ligne par ligne puis element par element (separe par des /)
        std::string line;
        
        std::ifstream s(filename);
        
        int id = 0;
        int nbArete = 0;
        
        // Indexion des noms de films et auteurs dans une map
        // Lecture du fichier en ordonnant: Filme Acteur Film Acteur Film... dans une liste en utilisant leur index
        while (std::getline(s, line))
        {
            auto names = split(line,'/');
            //Film
            indexs.insert(std::pair<std::string,int>(names.at(0),id));
            int idFilm = id++;
            for(int i = 1; i < names.size(); ++i) {
                graph.push_back(idFilm);
                if(contains(names.at(i)) == true){
                    graph.push_back(index(names.at(i)));
                } else {
                    indexs.insert(std::pair<std::string,int>(names.at(i),id));
                    graph.push_back(id++);
                }
                ++nbArete;
            }
        }
        s.close();
        
        // Création du graphe
        this->g = new Graph(nbArete);
        int film, acteur;
        
        // Insersion des éléments deux à deux (film, acteur) dans le graphe
        for(size_t i = 0; i < nbArete; ++i){
            film = graph.front();
            graph.pop_front();
            acteur = graph.front();
            graph.pop_front();
            g->addEdge(film, acteur);
        }
        
        /* A IMPLEMENTER */
    }
    
    //
    // @brief Verifie si un film (symbole) est à déjà été indexé
    //
    // @param string: name - Nom du film.
    //
    // @return True si le film est dans la list et false si le film n'y est pas
    //
    bool contains(const std::string& name) {
        if(indexs.find(name) != indexs.end()){
            return true;
        }
        return false;
    }
    
    //
    // @brief Retourne l'index d'un film (symbole)
    //
    // @param string: name - Nom du film.
    //
    // @return int: index - Numéro de l'index du film dans la list
    //
    // @warning il faut toujours utilisé la fonction 
    //          "bool contains(const std::string& name)" avant d'appeler cette fonction
    //          ce choix et une raison d'optimisation de temps d'execution. 
    //          Pas besoin de double check
    //
    int index(const std::string& name) {
        return indexs.find(name)->second;
    }
    
    //
    // @brief Retourner le nom du film à un certain index
    //
    // @param int: idx - index du film à retourné le nom
    //
    // @return string: name - Nom du film
    //
    std::string name(int idx) {
        for(std::map<std::string, int>::iterator it = indexs.begin(); it != indexs.end(); ++it){
            if(it->second == idx){
                return it->first;
            }
        }
        return "";
    }

    
    //
    // @brief Retourner un vecteur d'adjacence des noeuds adjacent à un noeud spécifique(nom)
    //
    // @param string: name - Nom du noeud
    //
    // @return std::vector<std::string> vector d'ajacence - Noeud adjacent au noeud (name)
    //
    std::vector<std::string> adjacent(const std::string & name) {
        return g->adjacent(index(name));
    }
    
    const Graph& G() {
        return *g; 
    }
    
};


#endif	/* SYMBOLGRAPH_H */
