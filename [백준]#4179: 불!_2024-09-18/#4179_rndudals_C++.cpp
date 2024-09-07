#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
#define MAX 1000000
using namespace std;


int R, C;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,-1,1 };
bool visited[1000][1000];

char map[1000][1000];
vector<pair<int, int>> fire;
int fire_dist[1000][1000];

pair<int, int> jihun;
int jihun_dist[1000][1000];

void bfs1(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	fire_dist[x][y] = 0;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (map[nx][ny] == '#') continue;
			if (fire_dist[nx][ny] > fire_dist[cx][cy] + 1) {
				fire_dist[nx][ny] = fire_dist[cx][cy] + 1;
				q.push({ nx, ny });
			}
		}
	}
}

void bfs2(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });
	jihun_dist[x][y] = 0;
	visited[x][y] = true;
	while (!q.empty()) {
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
			if (map[nx][ny] == '#') continue;
			if (visited[nx][ny]) continue;
			if (fire_dist[nx][ny] > jihun_dist[cx][cy] + 1) {
				jihun_dist[nx][ny] = jihun_dist[cx][cy] + 1;
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	string st;


	cin >> R >> C;

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			fire_dist[i][j] = MAX;
			jihun_dist[i][j] = MAX;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'F') {
				fire.push_back({ i, j });
			}
			if (map[i][j] == 'J') {
				jihun.first = i;
				jihun.second = j;
			}
		}
	}
	for (int i = 0; i < fire.size(); i++) {
		bfs1(fire[i].first, fire[i].second);
	}
	
	bfs2(jihun.first, jihun.second);

	int ans = MAX;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (i == 0 || j == 0 || i == R - 1 || j == C - 1) {
				ans = min(ans, jihun_dist[i][j] + 1);
			}
		}
	}
	if (ans == MAX) {
		cout << "IMPOSSIBLE" << '\n';
	}
	else {
		cout << ans << '\n';
	}

	return 0;
}
