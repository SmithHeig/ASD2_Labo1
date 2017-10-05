/* 
 * File:   GraphFromImage.h
 * Author: Olivier Cuisenaire
 *
 * Created on 2. octobre 2014, 12:09
 */

#ifndef GRAPHFROMIMAGE_H
#define	GRAPHFROMIMAGE_H

#include <list>

#include "bitmap_image.hpp"

class GraphFromImage {
public:

    GraphFromImage(const bitmap_image& i);

    typedef std::list<int> Iterable;

    Iterable adjacent(int v) const; //sommets adjacents
    
    /*
        Méthode si un pixel à une coordonée (x1,y1) et de la même couleur (RGB) qu'un autre pixel à la coordonée (x2, y2)
    */
    bool same_pixel(int x1, int y1, int x2, int y2) const;
    
    
    int V() const;                  //nombre de sommets

    int idx(int x, int y) const;    //index du sommet représentant le pixel a la position x, y
    int x(int idx) const;           //coordonnee x du sommet idx
    int y(int idx) const;           //coordonnee y du sommet idx
    
private:
    const bitmap_image& image;
};

#endif	/* GRAPHFROMIMAGE_H */
