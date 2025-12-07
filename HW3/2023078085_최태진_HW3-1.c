#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846
#define INF 1e18

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct Node
{
    char StopAreaId[64];
    char StopAreaFullName[256];
    double StopAreaLat;
    double StopAreaLong;
    int StopAreaType;
} Node;

typedef struct EdgeNode
{
    int targetIdx;
    struct EdgeNode *next;

} EdgeNode;

Node nodes[10005];
EdgeNode *edges[10005];

void parseStop(char *stop_name, int idx)
{
    char *ptr = stop_name;
    char *comma;

    comma = strchr(ptr, ',');
    *comma = '\0';
    strcpy(nodes[idx].StopAreaId, ptr);
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    if (*ptr == '"')
    {
        ptr++;
        *(comma - 1) = '\0';
    }
    else
    {
        *comma = '\0';
    }
    strcpy(nodes[idx].StopAreaFullName, ptr);
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    *comma = '\0';
    nodes[idx].StopAreaLat = atof(ptr);
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    *comma = '\0';
    nodes[idx].StopAreaLong = atof(ptr);
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    ptr = comma + 1;

    comma = strchr(ptr, ',');
    if (comma != NULL)
    {
        *comma = '\0';
    }
    nodes[idx].StopAreaType = atoi(ptr);
}

int getStopIdx(char *id, int N)
{
    for (int i = 0; i < N; i++)
    {
        if (strcmp(nodes[i].StopAreaId, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addEdge(int u, int v)
{
    EdgeNode *newEdge = (EdgeNode *)malloc(sizeof(EdgeNode));
    newEdge->targetIdx = v;
    newEdge->next = edges[u];
    edges[u] = newEdge;
}

double deToRad(double degree)
{
    return degree * PI / 180.0;
}

double getDist(int u, int v)
{
    double longA = deToRad(nodes[u].StopAreaLong);
    double latA = deToRad(nodes[u].StopAreaLat);

    double longB = deToRad(nodes[v].StopAreaLong);
    double latB = deToRad(nodes[v].StopAreaLat);

    double x = (longB - longA) * cos((latA + latB) / 2);
    double y = latB - latA;
    double d = sqrt(x * x + y * y) * 6371.0;

    return d;
}

int main()
{
    char start_point[257] = "";
    scanf("%s", start_point);
    char end_point[257] = "";
    scanf("%s", end_point);
    int N;
    scanf("%d", &N);
    fgetc(stdin);
    for (int i = 0; i < N; i++)
    {
        char stop_name[257] = "";
        scanf("%[^\n]", stop_name);
        fgetc(stdin);

        parseStop(stop_name, i);
    }
    int M;
    scanf("%d", &M);
    fgetc(stdin);
    for (int i = 0; i < M; i++)
    {
        char route[257] = "";
        scanf("%[^\n]", route);
        fgetc(stdin);

        char u_id[64], v_id[64];
        sscanf(route, "%s %s", u_id, v_id);

        int u = getStopIdx(u_id, N);
        int v = getStopIdx(v_id, N);

        if (u != -1 && v != -1)
        {
            addEdge(u, v);
        }
    }

    double *dist = (double *)malloc(sizeof(double) * N);
    int *visited = (int *)malloc(sizeof(int) * N);
    int *parent = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    int startIdx = getStopIdx(start_point, N);
    int endIdx = getStopIdx(end_point, N);

    if (startIdx != -1)
    {
        dist[startIdx] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        int u = -1;
        double minDist = INF;

        for (int j = 0; j < N; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF)
            break;

        if (u == endIdx)
            break;

        visited[u] = 1;

        for (EdgeNode *e = edges[u]; e != NULL; e = e->next)
        {
            int v = e->targetIdx;

            double weight = getDist(u, v);

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    if (startIdx != -1 && endIdx != -1 && dist[endIdx] != INF)
    {
        int path[10005];
        int pathCnt = 0;
        int cur = endIdx;

        while (cur != -1)
        {
            path[pathCnt++] = cur;
            cur = parent[cur];
        }

        for (int i = pathCnt - 1; i >= 0; i--)
        {
            printf("%s\n", nodes[path[i]].StopAreaFullName);
        }

        free(dist);
        free(visited);
        free(parent);

        return 0;
    }

    printf("IMPOSSIBLE\n");

    return 0;
}