#include <curses.h>
#include <string>
#include <time.h>

#define SIZE 8

void print_board(int board[SIZE][SIZE]) {
	std::string board_string;
	for (int a = 0; a < SIZE; a++) {
		for (int b = 0; b < SIZE; b++) {
			board_string.append(std::to_string(board[a][b])).append("  ");
		}
		board_string.append("\n");
	}
	mvaddstr(0, 0, board_string.c_str());
	refresh();
}

bool is_valid_pos(int board[SIZE][SIZE], int i, int j) {
	for (int a = 0; a < SIZE; a++) {
		if (board[a][j] == 1 || board[i][a]) {
			return false;
		}
	}

	for (int a = i, b = j; a < SIZE && b < SIZE; a++, b++) {
		if (board[a][b] == 1)
			return false;
	}
	for (int a = i, b = j; a < SIZE && b >= 0; a++, b--) {
		if (board[a][b] == 1)
			return false;
	}
	for (int a = i, b = j; a >= 0 && b < SIZE; a--, b++) {
		if (board[a][b] == 1)
			return false;
	}
	for (int a = i, b = j; a >= 0 && b >= 0; a--, b--) {
		if (board[a][b] == 1)
			return false;
	}

	return true;
}

bool find_solution(int board[SIZE][SIZE], int nth_queen) {
	if (nth_queen == SIZE) {
		return true;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (is_valid_pos(board, i, j)) {
				board[i][j] = 1;
				print_board(board);
				if (find_solution(board, nth_queen + 1)) {
					return true;
				} else {
					board[i][j] = 0;
				}
			}
		}
	}
	return false;
}

int main() {
	int board[SIZE][SIZE] = {0};

	initscr();
	noecho();
	cbreak();

	clock_t t1, t2;
	t1 = clock();
	find_solution(board, 0);
	t2 = clock();
	float diff((float)t2 - (float)t1);
	addstr(std::to_string(diff / CLOCKS_PER_SEC).c_str());
	if (getch() == 'q') {
		endwin();
	}
}
