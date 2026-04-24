#include <iostream>
#include <set>
#include <tuple>
using namespace std;

// Directions: 0=Up, 1=Right, 2=Down, 3=Left
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    int grid[10][10];
    int start_r = -1, start_c = -1;
    
    // Read grid and find start position
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 4) {
                start_r = i;
                start_c = j;
                grid[i][j] = 1; // Treat start as empty
            }
        }
    }
    
    int score = 0;
    int r = start_r, c = start_c;
    int dir = 0; // Start moving up
    
    // Track visited states (position + direction)
    set<tuple<int, int, int>> visited;
    
    while (true) {
        // Check if we've been in this state before (loop detection)
        if (visited.count({r, c, dir})) {
            cout << "Silly Pacman" << endl;
            return 0;
        }
        visited.insert({r, c, dir});
        
        // Check if current cell has a bean
        if (grid[r][c] == 2) {
            score += 2;
            grid[r][c] = 1; // Bean is eaten
        }
        
        // Try to find next move using right-hand rule
        // Priority: right turn > straight > left turn > u-turn
        int next_r = -1, next_c = -1, next_dir = -1;
        
        // Try right turn first
        int try_dir = (dir + 1) % 4;
        int try_r = r + dr[try_dir];
        int try_c = c + dc[try_dir];
        if (try_r >= 0 && try_r < 10 && try_c >= 0 && try_c < 10 && grid[try_r][try_c] != 0) {
            next_r = try_r;
            next_c = try_c;
            next_dir = try_dir;
        } else {
            // Try straight
            try_dir = dir;
            try_r = r + dr[try_dir];
            try_c = c + dc[try_dir];
            if (try_r >= 0 && try_r < 10 && try_c >= 0 && try_c < 10 && grid[try_r][try_c] != 0) {
                next_r = try_r;
                next_c = try_c;
                next_dir = try_dir;
            } else {
                // Try left turn
                try_dir = (dir + 3) % 4;
                try_r = r + dr[try_dir];
                try_c = c + dc[try_dir];
                if (try_r >= 0 && try_r < 10 && try_c >= 0 && try_c < 10 && grid[try_r][try_c] != 0) {
                    next_r = try_r;
                    next_c = try_c;
                    next_dir = try_dir;
                } else {
                    // Try u-turn
                    try_dir = (dir + 2) % 4;
                    try_r = r + dr[try_dir];
                    try_c = c + dc[try_dir];
                    if (try_r >= 0 && try_r < 10 && try_c >= 0 && try_c < 10 && grid[try_r][try_c] != 0) {
                        next_r = try_r;
                        next_c = try_c;
                        next_dir = try_dir;
                    } else {
                        // No valid move - stuck (shouldn't happen with valid input)
                        cout << score << endl;
                        return 0;
                    }
                }
            }
        }
        
        // Move to next position
        r = next_r;
        c = next_c;
        dir = next_dir;
        
        // Check if we hit a ghost
        if (grid[r][c] == 3) {
            score -= 500;
            cout << score << endl;
            return 0;
        }
    }
    
    return 0;
}
