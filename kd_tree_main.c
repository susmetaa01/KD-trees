#include "D:\codeblocks\KD trees\kd_tree.c"
int main()
{
	FILE *in_file;
	int n,x,i,y;
	in_file = fopen("kd_tree.txt", "r");
    struct Node *root = NULL;
    if (in_file == NULL)
    {
        printf("Can't open file for reading.\n");
    }
    else
    {
        fscanf(in_file, "%d", &n);
        fscanf(in_file, "%d", &x);
        if(n==0||feof(in_file))
    	{
    		printf("Tree is empty");
			exit(0);
		}
		fscanf(in_file, "%d", &y);
		int pointa[2];
		pointa[0]=x;
		pointa[1]=y;
        root=insert(root,pointa);
        for(i=1;i<n;i++)
        {
        	fscanf(in_file, "%d", &x);
        	fscanf(in_file, "%d", &y);
			pointa[0]=x;
			pointa[1]=y;
        	insert(root,pointa);
    	}
    	fclose(in_file);
    	int choice ;
		char iterate ;
		do
		{
		printf ("Enter your choice:\n\t1.Delete\n\t2.Find minimum\n\t3.Search\n\t4.Nearest Neighbour\n\t5.Exit\n") ;
		scanf ("%d", &choice) ;
		switch (choice)
		{
			case 1 :
				printf("Enter the point to be deleted\n") ;
				scanf ("%d", &x) ;
				scanf ("%d", &y) ;
				pointa[0]=x;
				pointa[1]=y;
				root = deleteNode(root, pointa);
				printf("Root after deletion\n");
				printf("%d %d\n",(root->point[0]),(root->point[1]));
			break ;
			case 2 :
				printf("Enter the dimension to be searched(0/1)\n") ;
				scanf ("%d", &x) ;
                printf("Minimum of %d'th dimension is %d\n",x,findMin(root, x));
			break ;
			case 3:
                printf("Enter the point to be searched\n") ;
				scanf ("%d", &x) ;
				scanf ("%d", &y) ;
				pointa[0]=x;
				pointa[1]=y;
				(search(root, pointa))? printf("Found\n"): printf("Not Found\n");
                break;
			case 4:
				printf("Enter the point to find nearest neighbour\n") ;
				scanf ("%d", &x) ;
				scanf ("%d", &y) ;
				pointa[0]=x;
				pointa[1]=y;
				if(search(root, pointa))
				{
				nearestNeighbour(pointa,root);
				printf("NEIGHBOR NODE : %d,%d\n",neigh[0],neigh[1]);
				bdst=1000;
				}
				else
				{
					printf("Node not present in the tree\n") ;
				}
				break;
			case 5:
			default :
				exit(0);
		}
		printf ("\nDo you want to continue(Y/N)\n") ;
		scanf ("\n%c", &iterate) ;
	}while(iterate=='y' || iterate=='Y') ;
	}
    getchar();
    return 0;
}
