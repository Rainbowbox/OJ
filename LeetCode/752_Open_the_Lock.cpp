#include "shared.h"

/*
 You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.
 
 The lock initially starts at '0000', a string representing the state of the 4 wheels.
 
 You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.
 
 Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.
 
 Example 1:
 Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
 Output: 6
 Explanation:
 A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
 Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
 because the wheels of the lock become stuck after the display becomes the dead end "0102".
 Example 2:
 Input: deadends = ["8888"], target = "0009"
 Output: 1
 Explanation:
 We can turn the last wheel in reverse to move from "0000" -> "0009".
 Example 3:
 Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
 Output: -1
 Explanation:
 We can't reach the target without getting stuck.
 Example 4:
 Input: deadends = ["0000"], target = "8888"
 Output: -1
 Note:
 The length of deadends will be in the range [1, 500].
 target will not be in the list deadends.
 Every string in deadends and the string target will be a string of 4 digits from the 10,000 possibilities '0000' to '9999'.
 */


namespace OpenTheLock {
    
    /*
     
    // With BFS, we can return once we find an answer.
    // But with DFS, we don't know whether we already find the min value until we traverse the entire search space.
    class SolutionDFS {
    public:
        int openLock(vector<string>& deadends, string target) {
            string start = "0000";
            if(start == target)
                return 0;
            
            unordered_map<string, int> visited;
            unordered_set<string> blocks;
            for(auto &deadend : deadends) {
                visited[deadend] = -1;
            }
            
            return findMin(blocks, start, target, visited);
        }
    private:
        int findMin(unordered_set<string>& blocks, string current, string& target, unordered_map<string, int>& visited) {
            if(current == target) {
                return 0;
            }
            
            if(visited.find(current) != visited.end())
                return visited[current];
            
            if(blocks.find(current) == blocks.end())
                blocks.insert(current);
            
            for(int i = 0; i < 4; ++ i) {
                for(int j = 1; j >= -1; -- j) {
                    string temp = current;
                    temp[i] += j;
                    if(temp[i] < '0')
                        temp[i] = '9';
                    else if(temp[i] > '9')
                        temp[i] = '0';
                    if(temp == current || blocks.find(temp) != blocks.end())
                        continue;
                    int distance = findMin(blocks, temp, target, visited);
                    if(distance != -1) {
                        if(visited.find(current) != visited.end())
                            visited[current] = distance + 1;
                        
                        else if (distance < visited[current])
                            visited[current] = distance + 1;
                    }
                }
            }
            if(visited.find(current) == visited.end())
                visited[current] = -1;
            
            blocks.erase(current);
            return visited[current];
        }
    };
    */
    
    class Solution {
    public:
        int openLock(vector<string>& deadends, string target) {
            string start = "0000";
            if(start == target)
                return 0;
            set<string> blocks(deadends.begin(), deadends.end());
            if(blocks.find(start) != blocks.end())
                return -1;
            queue<string> q;
            set<string> visited;
            q.push(start);
            visited.insert(start);
            int distance = 0;
            while(! q.empty()) {
                int size = q.size();
                for(int i = 0; i < size; ++ i) {
                    string current = q.front();
                    q.pop();
                    if (current == target)
                        return distance;
                    for(int j = 0; j < 4; ++ j) {
                        for(int t = -1; t <= 1; ++ t) {
                            if(t == 0)
                                continue;
                            string temp = current;
                            temp[j] += t;
                            if(temp[j] < '0')
                                temp[j] = '9';
                            else if(temp[j] > '9')
                                temp[j] = '0';
                            if(temp == target)
                                return distance + 1;
                            if(blocks.find(temp) != blocks.end())
                                continue;
                            if(visited.find(temp) == visited.end()) {
                                q.push(temp);
                                visited.insert(temp);
                            }
                        }
                    }
                }
                
                distance ++;
            }
            return -1;
        }
    };
    class helper {
    public:
        void test(vector<string> depends, string target, int expected) {
            Solution sln;
            int actual = sln.openLock(depends, target);
            ASSERT_EQ(expected, actual);
        }
    };
    TEST(OpenTheLock, openlock) {
        helper h;
        h.test({"0201","0101","0102","1212","2002"}, "0202", 6);
        h.test({"8888"}, "0009", 1);
        h.test({"8887","8889","8878","8898","8788","8988","7888","9888"}, "8888", -1);
        h.test({"0000"}, "8888", -1);
    }
}
