#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int ripe;
int M, N, cnt,m;
int map[1000][1000];
int visited[1000][1000];
int dist[1000][1000];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
queue<pair<int, int>>q;


void bfs() {
	while (!q.empty()) {
		pair<int, int> f = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int cx = f.first + dx[i];
			int cy = f.second + dy[i];
			if (!visited[cx][cy] && map[cx][cy] == 0 && cx >= 0 && cx < N && cy >= 0 && cy < M) {
				visited[cx][cy] = true;
				q.push(make_pair(cx, cy));
				if (dist[cx][cy] == 0 || dist[cx][cy] > dist[f.first][f.second] + 1) {
					dist[cx][cy] = dist[f.first][f.second] + 1;
				}

			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);
	// 저장
	// 저장될 때부터 모든 토마토 익은거 확인

	cin >> M >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1 || map[i][j] == 1) {
				ripe++;
			}
		}
	}
	if (ripe == N * M) { cout << 0; return 0; }

	// 방문 중
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) {
				q.push(make_pair(i, j));
			}
		}
	}
	bfs();
	// 방문하지 못한 곳 있는지 확인
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (!visited[i][j]&&map[i][j]==0) {
				cout << -1; return 0;
			}
			if (m < dist[i][j]) {
				m = dist[i][j];
			}
		}
	}
	cout << m << '\n';


	return 0;
}
