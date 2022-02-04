#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#define k 2
double bdst=1000,dist;
int *neigh;
// A structure to represent node of kd tree
struct Node {
    int point[k]; // To store k dimensional point
    struct Node *left, *right;
};
// A method to create a node of K D tree
struct Node* newNode(int arr[]);
// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
struct Node* insertRec(struct Node* root, int point[], unsigned depth);
// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
struct Node* insert(struct Node* root, int point[]);
// A utility function to find minimum of three integers
int min(int x, int y, int z);
// A utility function to find minimum of two integers
int min1(int x,int y);
// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
int findMinRec(struct Node* root, int d, unsigned depth);
// A wrapper over findMinRec(). Returns minimum of d'th dimension
int findMin(struct Node* root, int d);
//checks whether two points are the same
int arePointsSame(int point1[], int point2[]);
//copy one point into another
void copyPoint(int p1[], int p2[]);
//find min of three nodes and returns address of the minimum node
struct Node *minNode1(struct Node *x,struct Node *y,struct Node *z, int d);
// Recursively finds minimum of d'th dimension in KD tree 
// The parameter depth is used to determine current axis. 
struct Node *findMinRec1(struct Node* root, int d, unsigned depth);
// A wrapper over findMinRec(). Returns minimum of d'th dimension 
struct Node *findMin1(struct Node* root, int d);
// Function to delete a given point 'point[]' from tree with root 
// as 'root'.  depth is current depth and passed as 0 initially. 
// Returns root of the modified tree. 
struct Node *deleteNodeRec(struct Node *root, int point[], int depth);
// Function to delete a given point from K D Tree with 'root' 
struct  Node* deleteNode(struct Node *root, int point[]);
//searches for a record
int searchRec(struct Node* root, int point[], unsigned depth);
// Searches a Point in the K D tree. It mainly uses
// searchRec()
int search(struct Node* root, int point[]);
//calculates distance between two points
void distance(int p1[],int p2[]);
//to search for the nearest neighbour
void nearestNeighbour(int pt[],struct Node *root);
