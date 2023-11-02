#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드

//간선 구조체
struct Edge {
	int start, end, weight;
};

//그래프를 위한 구조체 설정
typedef struct GraphType {
	int n;	// 간선의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 초기화
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Kruskal MST Algorithm(qsort) \n");
	int i = 0;
	while (edge_accepted < (g->n - 1))	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) Select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 6, 5, 9);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 9, 10, 10);

	kruskal(g);
	free(g);
	return 0;
}