#include <stdio.h>

#define MAX_V 7
#define INF 1000

typedef char bool;
#define FALSE 0
#define TRUE 1

bool found[MAX_V];
int dist[MAX_V]; // distance(cost)
int PI[MAX_V]; // predecessors index
int S[MAX_V]; // Ư�� ��θ� ������ vertex���� ����

void Dijkstra(int Graph[MAX_V][MAX_V], char start, char end);
int choose();

int main(void)
{
	char start, end; // ���� vertex�� ���� vertex
	int Graph[MAX_V][MAX_V] = {
		{0, 10, 7, INF, 15, INF, INF},
		{10, 0, INF, 5, 8, INF, INF},
		{7, INF, 0, INF, 6, INF, INF},
		{INF, 5, INF, 0, 12, 6, INF},
		{15, 8, 6, 12, 0, INF, 3},
		{INF, INF, INF, 6, INF, 0, 1},
		{INF, INF, INF, INF, 3, 1, 0}
	};

	printf("��������� �Է��ϼ���: "); scanf_s("%c", &start, 1);
	printf("���������� �Է��ϼ���: "); scanf_s(" %c", &end, 1);

	Dijkstra(Graph, start, end);

	return 0;
}

void Dijkstra(int Graph[MAX_V][MAX_V], char start, char end)
{
	int i, u, v;
	int index, len = 1, temp;

	// ��� vertex�� found�� dist �ʱ�ȭ
	for (i = 0; i < MAX_V; i++) {
		dist[i] = INF;
		found[i] = FALSE;
	}

	// vertex A(0)�� dist, PI �ʱ�ȭ
	dist[0] = 0;
	PI[0] = -1;

	for (i = 0; i < MAX_V - 1; i++) {
		u = choose(dist, found);
		found[u] = TRUE;

		for (v = 0; v < MAX_V; v++) {
			// cycle�� �������� �ʰ� && �ڱ� �ڽ��� �ƴϸ� && Adjacent�ϰ� && �ּҰ��� ��
			if (found[v] == FALSE && Graph[u][v] != 0 && dist[u] != INF && dist[u] + Graph[u][v] < dist[v]) {
				// PI�� dist�� ����
				dist[v] = dist[u] + Graph[u][v];
				PI[v] = u;
			}
		}
	}

	// Ư�� vertex���� A���� ���� ��λ��� vertex���� ������
	S[0] = end - 65;
	index = PI[end - 65];
	while (index != -1) {
		S[len] = index;
		index = PI[index];
		len++;
	}

	// �迭 ��Ҹ� ������(A���� Ư�� vertex���� ���ʴ�� ����)
	for (i = 0; i < len / 2; i++) {
		temp = S[i];
		S[i] = S[(len - 1) - i];
		S[(len - 1) - i] = temp;
	}

	// ��� ���
	printf("Vertex %c���� Vertex %c���� ���� �ִ� ��δ� ", start, end);
	for (i = 0; i < len; i++)
		printf("%c ", S[i] + 65);
	printf("�̸�, �̶� �ִ� �Ÿ��� %d�Դϴ�.\n", dist[end - 65]);
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