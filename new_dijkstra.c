#include<stdio.h>
#define INFINITY 999
#define MAX_SIZE 10
#define VISITED 1
#define UNVISITED 2
struct VERTEXINFO
{
    int parent; //kept predecessor
    int time;//kept all vertex update info
    int selected;//kept info which vertex is visited
} pathstate[MAX_SIZE]; //declared array of structure its contain parent,time,selected value in array

int shortagePathInfo(int adjacency[MAX_SIZE][MAX_SIZE],int size,int source, int destination,int shortestPath[MAX_SIZE],int *time,int shorttime[MAX_SIZE]);
void initializer_vertex(int source,int size);
void   relaxation(int adjacency[MAX_SIZE][MAX_SIZE],int sourceNode,int size);

int main()
{
    int  boolean=0,i = 0,j=0,size =0,to = 0,from = 0,totalNodes = 0,length = 0;
    int  shortestPath[MAX_SIZE],adjacent[MAX_SIZE][MAX_SIZE],shorttime[MAX_SIZE];
    char startvertex[0],endvertex[0], temp[256];
    printf("How many size of the graph:  ");
    scanf("%d",&size);
    char *vertexName[size];
    fflush(stdin);
    printf("Enter vertices name: \n");
    for (i = 0; i < size; i++)
{
   gets( temp);
   vertexName[i] = strdup(temp);
}
    for(i = 1; i<size+1; i++)
    {
        printf("\n");
        for(j = 1; j<size+1; j++)
        {
            printf("Time of Edge from %d. %s to %d. %s is: ",i,*(vertexName+i-1),j,*(vertexName+j-1));
            scanf("%d",&adjacent[i][j]);

        }
    }
    fflush(stdin);
    printf(" Enter start vertex name:  ");
    gets(startvertex);
    for(i=1; i<=size; i++)
    {
        if(strcmp(startvertex,*(vertexName+i-1))==0)
        {
            //printf("%d",i);
            from=i;
            boolean=1;
            break;
        }
    }
    if(boolean==0)
    {
        printf("input worng source \n");
    }

    printf(" Enter destination vertex name:  ");
    gets(endvertex);
    for(j=1; j<=size; j++)
    {
        if(strcmp(endvertex,*(vertexName+j-1))==0)
        {
            printf("%d",j);
            to=j;
            boolean=1;
            break;
        }
    }
    if(boolean==0)
    {
        printf("input worng destination ");
    }
    totalNodes = shortagePathInfo(adjacent,size,from,to,shortestPath,&length,shorttime);
      int cal=0;
     if(length)
    {
        printf("All vertex delay information\n");
        for(i = 1; i<=size ; i++)
        {
            printf("Vertex: %d %s = %d  \n",i,*(vertexName+i-1),pathstate[i].time);//print all vertex
        }
          printf("\nThe Shortest Path from: %s to %s \n",*(vertexName+from-1),*(vertexName+to-1));
        // printf("    Go from VERTEX %d ",shortestPath[1]);
        for(i = 1; i<totalNodes + 1; i++)
        {

            for(j=0; j<size; j++)
            {
                if(shortestPath[i]==j+1)
                {
                    //  printf("to %d ",j+1);
                    if(shortestPath[i]!=from)
                    {
                        cal=cal+shorttime[i-1];
                        //   printf("individual %d  ",cal);

                    }

                    if(shortestPath[i]!=to)
                    {
                        printf(" %s =>: ",*(vertexName+j));
                    }else
                    {
                        printf(" %s : ",*(vertexName+j));
                    }
                }
            }

        }
        printf("\n\nMinimum time: %d",length);
    }else
    {
        printf("\n\nHere No Path is Available");
    }

    return 0;

}
int shortagePathInfo(int adjacency[MAX_SIZE][MAX_SIZE],int size,int source, int destination,int shortestPath[MAX_SIZE],int *time,int shorttime[MAX_SIZE])
{

    int i =0,totalNodes = 0,sourceNode = 0,mintime = 0,tempPath[MAX_SIZE];
    *time = 0;
    initializer_vertex(source,size);
    sourceNode = source;
    do
    {

        relaxation(adjacency,sourceNode,size);
        mintime = INFINITY;
        sourceNode = 0;
        for(i = 1; i<size+1; i++)
        {
            if( (pathstate[i].selected == UNVISITED) && (pathstate[i].time < mintime))
            {
                mintime = pathstate[i].time;
                sourceNode = i;
            }
        }
        if(sourceNode == 0)
        {
            return 0;
        }
        pathstate[sourceNode].selected = VISITED;
    }
    while(sourceNode != destination);
    sourceNode = destination;
    do
    {
        totalNodes = totalNodes + 1;
        tempPath[totalNodes] = sourceNode;

        sourceNode = pathstate[sourceNode].parent;

    }
    while(sourceNode != 0);
    for(i = 1; i<totalNodes + 1; i++)
    {
        shortestPath[i] = tempPath[totalNodes-i+1];

    }
    for(i = 1; i<totalNodes; i++)
    {
        // printf("individual %d  ",adjacency[shortestPath[i]][shortestPath[i+1]]);
        shorttime[i]=adjacency[shortestPath[i]][shortestPath[i+1]];
        *time = *time + adjacency[shortestPath[i]][shortestPath[i+1]];

    }
    return totalNodes;
}
//initialization part
void initializer_vertex(int source,int size)
{
    int i;
    for(i = 1; i<size+1; i++)
    {
        pathstate[i].parent = 0;
        pathstate[i].time = INFINITY;
        pathstate[i].selected = UNVISITED;
    }
    pathstate[source].parent = 0;
    pathstate[source].time = 0;
    pathstate[source].selected = VISITED;
}
void   relaxation(int adjacency[MAX_SIZE][MAX_SIZE],int sourceNode,int size)
{
    int i;
    for(i = 1; i<size+1; i++)
    {
        if((adjacency[sourceNode][i]>0) && (pathstate[i].selected == UNVISITED))
        {
            if((pathstate[sourceNode].time + adjacency[sourceNode][i])< pathstate[i].time)
            {
                pathstate[i].parent = sourceNode;
                pathstate[i].time = pathstate[sourceNode].time + adjacency[sourceNode][i];
            }
        }
    }
}
