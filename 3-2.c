#include <stdio.h>

#define MAX_V 7
#define INF 1000

typedef char bool;
#define FALSE 0
#define TRUE 1

bool found[MAX_V];
int dist[MAX_V]; // distance(cost)
int PI[MAX_V]; // predecessors index
int S[MAX_V]; // 특정 경로를 지나는 vertex들의 집합

void Dijkstra(int Graph[MAX_V][MAX_V], char start, char end);
int choose();

int main(void)
{
	char start, end; // 시작 vertex와 도착 vertex
	int Graph[MAX_V][MAX_V] = {
		{0, 10, 7, INF, 15, INF, INF},
		{10, 0, INF, 5, 8, INF, INF},
		{7, INF, 0, INF, 6, INF, INF},
		{INF, 5, INF, 0, 12, 6, INF},
		{15, 8, 6, 12, 0, INF, 3},
		{INF, INF, INF, 6, INF, 0, 1},
		{INF, INF, INF, INF, 3, 1, 0}
	};

	printf("출발지역을 입력하세요: "); scanf_s("%c", &start, 1);
	printf("도착지역을 입력하세요: "); scanf_s(" %c", &end, 1);

	Dijkstra(Graph, start, end);

	return 0;
}

void Dijkstra(int Graph[MAX_V][MAX_V], char start, char end)
{
	int i, u, v;
	int index, len = 1, temp;

	// 모든 vertex의 found와 dist 초기화
	for (i = 0; i < MAX_V; i++) {
		dist[i] = INF;
		found[i] = FALSE;
	}

	// vertex A(0)의 dist, PI 초기화
	dist[0] = 0;
	PI[0] = -1;

	for (i = 0; i < MAX_V - 1; i++) {
		u = choose(dist, found);
		found[u] = TRUE;

		for (v = 0; v < MAX_V; v++) {
			// cycle을 형성하지 않고 && 자기 자신이 아니며 && Adjacent하고 && 최소값일 때
			if (found[v] == FALSE && Graph[u][v] != 0 && dist[u] != INF && dist[u] + Graph[u][v] < dist[v]) {
				// PI와 dist값 갱신
				dist[v] = dist[u] + Graph[u][v];
				PI[v] = u;
			}
		}
	}

	// 특정 vertex부터 A까지 가는 경로상의 vertex들을 저장함
	S[0] = end - 65;
	index = PI[end - 65];
	while (index != -1) {
		S[len] = index;
		index = PI[index];
		len++;
	}

	// 배열 요소를 뒤집음(A부터 특정 vertex까지 차례대로 저장)
	for (i = 0; i < len / 2; i++) {
		temp = S[i];
		S[i] = S[(len - 1) - i];
		S[(len - 1) - i] = temp;
	}

	// 결과 출력
	printf("Vertex %c에서 Vertex %c으로 가는 최단 경로는 ", start, end);
	for (i = 0; i < len; i++)
		printf("%c ", S[i] + 65);
	printf("이며, 이때 최단 거리는 %d입니다.\n", dist[end - 65]);
}

int choose()
{
	int i, index, min = INF;

	for (i = 0; i < MAX_V; i++) {
		if (found[i] == FALSE && dist[i] < min) {
			min = dist[i];
			index = i;
		}
	}
	return index;
}