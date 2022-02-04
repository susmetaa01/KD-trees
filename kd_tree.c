#include "D:\codeblocks\KD trees\kd_trees_header.h"
// A method to create a node of K D tree
struct Node* newNode(int arr[])
{
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
	int i;
    for (i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = NULL;
    return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
struct Node* insertRec(struct Node* root, int point[], unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
        return newNode(point);

    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);
    return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
struct Node* insert(struct Node* root, int point[])
{
    return insertRec(root, point, 0);
}

// A utility function to find minimum of three integers
int min(int x, int y, int z)
{
    if (x<y && x<z)
        {return x;}
    else if( y<x && y<z)
        {return y;}
    else if(z<x && z<y)
        {return z;}
}
int min1(int x,int y)
{
    if(x<y){return x;}
    else{return y;}
}
// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
int findMinRec(struct Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return 10000;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (cd == d) {
        if (root->left == NULL)
            return root->point[d];
        return min1(root->point[d], findMinRec(root->left, d, depth + 1));
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return min(root->point[d],
               findMinRec(root->left, d, depth + 1),
               findMinRec(root->right, d, depth + 1));
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
int findMin(struct Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec(root, d, 0);
}
//checks whether two points are the same
int arePointsSame(int point1[], int point2[])
{
    // Compare individual pointinate values
    int i;
    for (i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return 0;

    return 1;
}
//copy one point into another
void copyPoint(int p1[], int p2[])
{
	int i;
   for (i=0; i<k; i++)
       p1[i] = p2[i];
}
//find min of three nodes and returns address of the minimum node
struct Node *minNode1(struct Node *x,struct Node *y,struct Node *z, int d)
{
    struct Node *res = x;
    if (y != NULL && y->point[d] < res->point[d])
       res = y;
    if (z != NULL && z->point[d] < res->point[d])
       res = z;
    return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
struct Node *findMinRec1(struct Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec1(root->left, d, depth+1);
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode1(root,
               findMinRec1(root->left, d, depth+1),
               findMinRec1(root->right, d, depth+1), d);
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
struct Node *findMin1(struct Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec1(root, d, 0);
}
//searches for a record
int searchRec(struct Node* root, int point[], unsigned depth)
{
    // Base cases
    if (root == NULL)
        return 0;
    if (arePointsSame(root->point, point))
        return 1;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
int search(struct Node* root, int point[])
{
    // Pass current depth as 0
    return searchRec(root, point, 0);
}
// Function to delete a given point 'point[]' from tree with root
// as 'root'.  depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
struct Node *deleteNodeRec(struct Node *root, int point[], int depth)
{
    // Given point is not present
    if (root == NULL)
        return NULL;

    // Find dimension of current node
    int cd = depth % k;

    // If the point to be deleted is present at root
    if ((arePointsSame(root->point, point))==1)
    {
        // 2.b) If right child is not NULL
        if (root->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            struct Node *min = findMin1(root->right, cd);

            // Copy the minimum to root
            copyPoint(root->point, min->point);

            // Recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->point, depth+1);
        }
        else if (root->left != NULL) // same as above
        {
            struct Node *min = findMin1(root->left, cd);
            copyPoint(root->point, min->point);
            root->right = deleteNodeRec(root->left, min->point, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            free(root);
            return NULL;
        }
        return root;
    }

    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
}

// Function to delete a given point from K D Tree with 'root'
struct  Node* deleteNode(struct Node *root, int point[])
{
   // Pass depth as 0
   return deleteNodeRec(root, point, 0);
}

//calculates distance between two points
void distance(int p1[],int p2[])
{
	dist=sqrt(((p1[0]-p2[0])*(p1[0]-p2[0]))+((p1[1]-p2[1])*(p1[1]-p2[1])));
	if(dist<bdst)
	{
        bdst=dist;
        neigh=p2;
	}
}
//to search for the nearest neighbour
void nearestNeighbour(int pt[],struct Node *node)
{
	if (node == NULL)
        return;
	if(((node->point[0])!=pt[0])&& ((node->point[1])!=pt[1]))
    distance(pt,(node->point));
    nearestNeighbour(pt,node->left);
    nearestNeighbour(pt,node->right);
}
