#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    /* A IMPLEMENTER */
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    Iterable list;
    int colonne = x(v);
    int ligne = y(v);
    
    // Haut
    if(ligne != 0 && same_pixel(colonne, ligne, colonne, ligne - 1)){
        list.push_back(idx(colonne, ligne - 1));
    }
    // Gauche
    if(colonne != 0 && same_pixel(colonne,ligne, colonne - 1, ligne)){
        list.push_back(idx(colonne - 1, ligne));
    }
    // Droite
    if(colonne != image.width() && same_pixel(colonne, ligne, colonne + 1, ligne)){
        list.push_back(idx(colonne + 1, ligne));
    }
    // Bas
    if(ligne != image.height() && same_pixel(colonne, ligne, colonne, ligne + 1)){
        list.push_back(idx(colonne, ligne + 1));
    }
    return list;
}

int GraphFromImage::idx(int x, int y) const {
    return (y * image.width()) + x;
}

int GraphFromImage::x(int idx) const {
    return idx % image.width();
}

int GraphFromImage::y(int idx) const {
    return idx / image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}

bool GraphFromImage::same_pixel(int x1, int y1, int x2, int y2) const{
    unsigned char red1;
    unsigned char blue1;
    unsigned char green1;
    unsigned char red2;
    unsigned char blue2;
    unsigned char green2;
    
    image.get_pixel(x1, y1, red1, blue1, green1);
    image.get_pixel(x2,y2, red2, blue2, green2);
    
    return (red1 == red2 && blue1 == blue2 && green1 == green2);
}
