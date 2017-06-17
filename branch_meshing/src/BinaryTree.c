//
//  BinaryTree.c
//  branch_meshing
//
//  Created by Austin Slominski on 3/11/17.
//
//
#include <stdint.h>

#include "BinaryTree.h"
struct color{
    float r;
    float g;
    float b;
    float a;
};

struct vector3{
    float x;
    float y;
    float z;
};
struct nodeData{
    struct color color;
    struct vector3 position;
    struct vector3 growthVector;
};

struct node{
    struct node *leftNode;
    struct node *rightNode;
    struct node *parent;
    struct nodeData data;

};

typedef struct node binaryTree;

void distanceFromCenter(struct node *n);




void asjkdfbnasdfas(){
    binaryTree b;
    b.data.color.r =1;
    b.data.color.g =1;
    b.data.color.b = 1;
    b.data.color.a = 1;
    
    
    struct node newNode;
    struct node node2;
    struct node node3;
    struct node node4;
    //... initialize new Node
    
    b.leftNode = &newNode;
    b.rightNode = &node2;
    b.rightNode->leftNode = &node3;
    node2.leftNode = &node3;
}

