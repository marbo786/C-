// ===================================================================
// DSA PROJECT: Data Structures & Algorithms Demonstration
// ===================================================================
// This program demonstrates core DSA concepts:
// 1. TRIE - Location auto-complete (Prefix Tree)
// 2. GRAPH - Location network with Dijkstra's Algorithm
// 3. LINKED LIST - Bus route management
// 4. HASH MAP - User storage (unordered_map)
// 5. QUEUE - Traffic updates (FIFO)
// 6. PRIORITY QUEUE - Dijkstra's algorithm (Min-heap)
// ===================================================================

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Utility function for case-insensitive comparison
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// ===================================================================
// DSA 1: HASH MAP (unordered_map) - User Storage
// ===================================================================
// Demonstrates: Hash table operations (insert, find, delete)
// ===================================================================

class User {
public:
    string name;
    string id;
    
    User() : name(""), id("") {}
    User(string n, string i) : name(n), id(i) {}
};

class UserSystem {
private:
    // Hash Map: O(1) average time complexity for operations
    unordered_map<string, User> users;

public:
    // Insert operation - O(1) average
    void addUser(string id, string name) {
        if (users.find(id) != users.end()) {
            cout << "[!] User already exists!\n";
            return;
        }
        users[id] = User(name, id);
        cout << "[+] User added successfully!\n";
    }

    // Search operation - O(1) average
    User* findUser(string id) {
        auto it = users.find(id);
        if (it != users.end()) {
            return &it->second;
        }
        return nullptr;
    }

    // Delete operation - O(1) average
    bool removeUser(string id) {
        if (users.find(id) == users.end()) {
            cout << "[!] User not found!\n";
            return false;
        }
        users.erase(id);
        cout << "[+] User removed successfully!\n";
        return true;
    }

    // Display all users
    void displayAll() {
        cout << "\n========================================\n";
        cout << "     ALL USERS (Hash Map)\n";
        cout << "========================================\n";
        if (users.empty()) {
            cout << "[!] No users found.\n";
        } else {
            int i = 1;
            for (auto &kv : users) {
                cout << i << ". ID: " << kv.first << " | Name: " << kv.second.name << "\n";
                i++;
            }
        }
        cout << "========================================\n";
    }
};

// ===================================================================
// DSA 2: TRIE (Prefix Tree) - Location Auto-Complete
// ===================================================================
// Demonstrates: Tree structure, recursive traversal, prefix matching
// ===================================================================

class TrieNode {
public:
    bool isEnd;
    TrieNode* children[26];

    TrieNode() {
        isEnd = false;
        fill(begin(children), end(children), nullptr);
    }
};

class Trie {
private:
    TrieNode* root;

    int idx(char c) {
        if (isalpha(c)) {
            return tolower(c) - 'a';
        }
        return -1;
    }

    void collectAll(TrieNode* node, string prefix, vector<string> &out) {
        if (!node) return;
        
        if (node->isEnd) {
            out.push_back(prefix);
        }

        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                collectAll(node->children[i], prefix + char('a' + i), out);
            }
        }
    }

    void destroyTrie(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                destroyTrie(node->children[i]);
            }
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroyTrie(root);
    }

    // Insert operation - O(m) where m is word length
    void insert(const string &word) {
        TrieNode* cur = root;
        
        for (char c : word) {
            int i = idx(c);
            if (i == -1) continue;

            if (!cur->children[i]) {
                cur->children[i] = new TrieNode();
            }
            cur = cur->children[i];
        }
        
        cur->isEnd = true;
    }

    // Search operation - O(m) where m is prefix length
    vector<string> suggest(const string &prefix) {
        TrieNode* cur = root;
        string p;

        for (char c : prefix) {
            int i = idx(c);
            if (i == -1) continue;

            if (!cur->children[i]) {
                return {};
            }
            
            cur = cur->children[i];
            p.push_back(tolower(c));
        }

        vector<string> out;
        collectAll(cur, p, out);
        return out;
    }
};

// ===================================================================
// DSA 3: GRAPH + DIJKSTRA'S ALGORITHM - Shortest Path
// ===================================================================
// Demonstrates: Graph representation (adjacency list), 
//               Dijkstra's algorithm, Priority Queue (min-heap)
// ===================================================================

class Graph {
public:
    // Adjacency List representation
    unordered_map<string, int> nameToNode;
    vector<string> nodeToName;
    vector<vector<pair<int, int>>> adj;  // (neighbor, weight)

    Graph() {}

    int addLocation(string name) {
        string normalized = toLower(name);
        
        for (auto& pair : nameToNode) {
            if (toLower(pair.first) == normalized) {
                return pair.second;
            }
        }
        
        int id = nodeToName.size();
        nameToNode[name] = id;
        nodeToName.push_back(name);
        adj.push_back({});
        
        return id;
    }

    void addEdge(string uName, string vName, int w) {
        int u = addLocation(uName);
        int v = addLocation(vName);
        
        // Check if edge exists
        for (auto& edge : adj[u]) {
            if (edge.first == v) {
                edge.second = w;
                for (auto& revEdge : adj[v]) {
                    if (revEdge.first == u) {
                        revEdge.second = w;
                        break;
                    }
                }
                return;
            }
        }
        
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        cout << "[+] Edge added successfully!\n";
    }

    bool hasLocation(string name) {
        string normalized = toLower(name);
        for (auto& pair : nameToNode) {
            if (toLower(pair.first) == normalized) {
                return true;
            }
        }
        return false;
    }

    string getActualLocationName(string name) {
        string normalized = toLower(name);
        for (auto& pair : nameToNode) {
            if (toLower(pair.first) == normalized) {
                return pair.first;
            }
        }
        return name;
    }

    // Dijkstra's Algorithm - O((V + E) log V)
    // Uses Priority Queue (min-heap) for efficient node selection
    bool shortestPath(string srcName, string destName, vector<string> &pathOut, int &distOut) {
        pathOut.clear();
        distOut = INF;

        srcName = getActualLocationName(srcName);
        destName = getActualLocationName(destName);

        if (!hasLocation(srcName) || !hasLocation(destName)) {
            cout << "[!] One or both locations not found!\n";
            return false;
        }

        int n = nodeToName.size();
        vector<int> dist(n, INF);
        vector<int> parent(n, -1);
        vector<bool> visited(n, false);

        // Priority Queue (Min-Heap) - O(log V) for insert/extract
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int s = nameToNode[srcName];
        int t = nameToNode[destName];

        dist[s] = 0;
        pq.push({0, s});

        // Main Dijkstra loop
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int u = cur.second;
            int d = cur.first;

            if (visited[u]) continue;
            visited[u] = true;

            // Relax edges
            for (auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[t] == INF) {
            cout << "[!] No path found!\n";
            return false;
        }

        // Reconstruct path
        int cur = t;
        while (cur != -1) {
            if (!nodeToName[cur].empty()) {
                pathOut.push_back(nodeToName[cur]);
            }
            cur = parent[cur];
        }

        reverse(pathOut.begin(), pathOut.end());
        distOut = dist[t];
        
        return true;
    }

    void showAllLocations() {
        cout << "\n========================================\n";
        cout << "     ALL LOCATIONS (Graph Nodes)\n";
        cout << "========================================\n";
        if (nodeToName.empty()) {
            cout << "[!] No locations found.\n";
        } else {
            for (size_t i = 0; i < nodeToName.size(); i++) {
                if (!nodeToName[i].empty()) {
                    cout << (i+1) << ". " << nodeToName[i] << "\n";
                }
            }
        }
        cout << "========================================\n";
    }
};

// ===================================================================
// DSA 4: LINKED LIST - Bus Route Management
// ===================================================================
// Demonstrates: Linked list operations (insert, delete, reverse, traverse)
// ===================================================================

struct Stop {
    string name;
    Stop* next;
    
    Stop(string n) : name(n), next(nullptr) {}
};

class BusRoute {
public:
    string routeName;
    Stop* head;

    BusRoute() : head(nullptr) {}
    BusRoute(string rn) : routeName(rn), head(nullptr) {}

    ~BusRoute() {
        while (head) {
            Stop* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Insert at end - O(n)
    void addStop(string n) {
        Stop* node = new Stop(n);
        
        if (!head) {
            head = node;
            return;
        }

        Stop* cur = head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = node;
    }

    // Delete operation - O(n)
    bool deleteStop(string n) {
        if (!head) return false;
        
        if (head->name == n) {
            Stop* tmp = head;
            head = head->next;
            delete tmp;
            return true;
        }

        Stop* cur = head;
        while (cur->next && cur->next->name != n) {
            cur = cur->next;
        }

        if (!cur->next) return false;

        Stop* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
        return true;
    }

    // Reverse linked list - O(n)
    void reverseRoute() {
        Stop* prev = nullptr;
        Stop* cur = head;

        while (cur) {
            Stop* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }

        head = prev;
    }

    // Traverse and display - O(n)
    void display() {
        if (!head) {
            cout << "  (Empty route)\n";
            return;
        }
        
        Stop* cur = head;
        while (cur) {
            cout << cur->name;
            if (cur->next) {
                cout << " -> ";
            }
            cur = cur->next;
        }
        cout << "\n";
    }

    vector<string> getStopsVector() {
        vector<string> v;
        Stop* cur = head;
        while (cur) {
            v.push_back(cur->name);
            cur = cur->next;
        }
        return v;
    }
};

class BusRouteManager {
private:
    unordered_map<string, BusRoute> routes;

public:
    void addRoute(string rn) {
        if (routes.find(rn) != routes.end()) {
            cout << "[!] Route already exists!\n";
            return;
        }
        routes[rn] = BusRoute(rn);
        cout << "[+] Route added successfully!\n";
    }

    void addStopToRoute(string rn, string s) {
        if (routes.find(rn) == routes.end()) {
            cout << "[!] Route not found!\n";
            return;
        }
        routes[rn].addStop(s);
        cout << "[+] Stop added successfully!\n";
    }

    void deleteStopFromRoute(string rn, string s) {
        if (routes.find(rn) == routes.end()) {
            cout << "[!] Route not found!\n";
            return;
        }
        if (routes[rn].deleteStop(s)) {
            cout << "[+] Stop deleted successfully!\n";
        } else {
            cout << "[!] Stop not found!\n";
        }
    }

    bool deleteRoute(string rn) {
        if (routes.find(rn) == routes.end()) {
            cout << "[!] Route not found!\n";
            return false;
        }
        routes.erase(rn);
        cout << "[+] Route deleted successfully!\n";
        return true;
    }

    void reverseRoute(string rn) {
        if (routes.find(rn) == routes.end()) {
            cout << "[!] Route not found!\n";
            return;
        }
        routes[rn].reverseRoute();
        cout << "[+] Route reversed successfully!\n";
    }

    void displayAllRoutes() {
        cout << "\n========================================\n";
        cout << "     ALL BUS ROUTES (Linked Lists)\n";
        cout << "========================================\n";
        if (routes.empty()) {
            cout << "[!] No routes found.\n";
        } else {
            int i = 1;
            for (auto &kv : routes) {
                cout << "\nRoute #" << i << ": " << kv.first << "\n";
                cout << "  Stops: ";
                kv.second.display();
                i++;
            }
        }
        cout << "========================================\n";
    }
};

// ===================================================================
// DSA 5: QUEUE (FIFO) - Traffic Updates
// ===================================================================
// Demonstrates: Queue operations (enqueue, dequeue)
// ===================================================================

enum TrafficLevel { LOW=1, MEDIUM=2, HIGH=3 };

struct TrafficUpdate {
    string routeName;
    TrafficLevel level;
    
    TrafficUpdate(string r="", TrafficLevel l=LOW) : routeName(r), level(l) {}
};

class TrafficManager {
private:
    // Queue data structure - FIFO order
    queue<TrafficUpdate> updates;
    unordered_map<string, TrafficLevel> currentTraffic;

public:
    // Enqueue operation - O(1)
    void pushUpdate(TrafficUpdate u) {
        updates.push(u);
        cout << "[+] Traffic update queued!\n";
    }

    // Dequeue and process - O(1) per operation
    void processUpdates() {
        int count = 0;
        while (!updates.empty()) {
            TrafficUpdate u = updates.front();
            updates.pop();
            currentTraffic[u.routeName] = u.level;
            count++;
        }
        cout << "[+] Processed " << count << " update(s)!\n";
    }

    void showAllTraffic() {
        cout << "\n========================================\n";
        cout << "     TRAFFIC STATUS (Queue Demo)\n";
        cout << "========================================\n";
        if (currentTraffic.empty()) {
            cout << "[!] No traffic data.\n";
        } else {
            int i = 1;
            for (auto &kv : currentTraffic) {
                cout << i << ". " << kv.first << " -> ";
                if (kv.second == LOW) cout << "LOW\n";
                else if (kv.second == MEDIUM) cout << "MEDIUM\n";
                else cout << "HIGH\n";
                i++;
            }
        }
        cout << "========================================\n";
    }
};

// ===================================================================
// MAIN MENU - Unified Interface for All DSA Operations
// ===================================================================

void mainMenu(UserSystem &us, Graph &g, Trie &trie, BusRouteManager &brm, TrafficManager &tm) {
    int choice;
    string input1, input2, input3;
    int distance, level;

    while (true) {
        cout << "\n========================================\n";
        cout << "     DSA PROJECT MENU\n";
        cout << "========================================\n";
        cout << "  HASH MAP (unordered_map):\n";
        cout << "    1. Add User\n";
        cout << "    2. Find User\n";
        cout << "    3. Remove User\n";
        cout << "    4. Display All Users\n";
        cout << "\n  TRIE (Prefix Tree):\n";
        cout << "    5. Insert Location\n";
        cout << "    6. Search Locations (Auto-complete)\n";
        cout << "\n  GRAPH + DIJKSTRA'S ALGORITHM:\n";
        cout << "    7. Add Location\n";
        cout << "    8. Add Edge (Route)\n";
        cout << "    9. Find Shortest Path\n";
        cout << "   10. Display All Locations\n";
        cout << "\n  LINKED LIST:\n";
        cout << "   11. Add Bus Route\n";
        cout << "   12. Add Stop to Route\n";
        cout << "   13. Delete Stop from Route\n";
        cout << "   14. Delete Route\n";
        cout << "   15. Reverse Route\n";
        cout << "   16. Display All Routes\n";
        cout << "\n  QUEUE (FIFO):\n";
        cout << "   17. Add Traffic Update\n";
        cout << "   18. Process Traffic Updates\n";
        cout << "   19. View Traffic Status\n";
        cout << "\n    0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "\n[+] Thank you for using the DSA Project!\n";
            break;
        }

        switch(choice) {
            case 1: {
                cout << "\n[*] Add User (Hash Map)\n";
                cout << "Enter user ID: ";
                getline(cin, input1);
                cout << "Enter user name: ";
                getline(cin, input2);
                us.addUser(input1, input2);
                break;
            }
            case 2: {
                cout << "\n[*] Find User (Hash Map)\n";
                cout << "Enter user ID: ";
                getline(cin, input1);
                User* u = us.findUser(input1);
                if (u) {
                    cout << "[+] Found: ID=" << u->id << ", Name=" << u->name << "\n";
                } else {
                    cout << "[!] User not found!\n";
                }
                break;
            }
            case 3: {
                cout << "\n[*] Remove User (Hash Map)\n";
                cout << "Enter user ID: ";
                getline(cin, input1);
                us.removeUser(input1);
                break;
            }
            case 4:
                us.displayAll();
                break;
            case 5: {
                cout << "\n[*] Insert Location (Trie)\n";
                cout << "Enter location name: ";
                getline(cin, input1);
                trie.insert(input1);
                cout << "[+] Location inserted!\n";
                break;
            }
            case 6: {
                cout << "\n[*] Search Locations (Trie Auto-complete)\n";
                cout << "Enter prefix: ";
                getline(cin, input1);
                auto suggestions = trie.suggest(input1);
                if (suggestions.empty()) {
                    cout << "[!] No matches found.\n";
                } else {
                    cout << "\n[+] Found " << suggestions.size() << " match(es):\n";
                    for (size_t i = 0; i < suggestions.size(); i++) {
                        cout << "  " << (i+1) << ". " << suggestions[i] << "\n";
                    }
                }
                break;
            }
            case 7: {
                cout << "\n[*] Add Location (Graph)\n";
                cout << "Enter location name: ";
                getline(cin, input1);
                g.addLocation(input1);
                cout << "[+] Location added!\n";
                break;
            }
            case 8: {
                cout << "\n[*] Add Edge (Graph)\n";
                cout << "Enter first location: ";
                getline(cin, input1);
                cout << "Enter second location: ";
                getline(cin, input2);
                cout << "Enter distance: ";
                cin >> distance;
                cin.ignore();
                g.addEdge(input1, input2, distance);
                break;
            }
            case 9: {
                cout << "\n[*] Find Shortest Path (Dijkstra's Algorithm)\n";
                cout << "Enter source: ";
                getline(cin, input1);
                cout << "Enter destination: ";
                getline(cin, input2);
                vector<string> path;
                int dist;
                if (g.shortestPath(input1, input2, path, dist)) {
                    cout << "\n[+] Shortest Path Found:\n";
                    cout << "Path: ";
                    for (size_t i = 0; i < path.size(); i++) {
                        cout << path[i];
                        if (i + 1 < path.size()) cout << " -> ";
                    }
                    cout << "\nDistance: " << dist << " units\n";
                }
                break;
            }
            case 10:
                g.showAllLocations();
                break;
            case 11: {
                cout << "\n[*] Add Bus Route (Linked List)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                brm.addRoute(input1);
                break;
            }
            case 12: {
                cout << "\n[*] Add Stop (Linked List)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                cout << "Enter stop name: ";
                getline(cin, input2);
                brm.addStopToRoute(input1, input2);
                break;
            }
            case 13: {
                cout << "\n[*] Delete Stop (Linked List)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                cout << "Enter stop name: ";
                getline(cin, input2);
                brm.deleteStopFromRoute(input1, input2);
                break;
            }
            case 14: {
                cout << "\n[*] Delete Route (Linked List)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                brm.deleteRoute(input1);
                break;
            }
            case 15: {
                cout << "\n[*] Reverse Route (Linked List)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                brm.reverseRoute(input1);
                break;
            }
            case 16:
                brm.displayAllRoutes();
                break;
            case 17: {
                cout << "\n[*] Add Traffic Update (Queue)\n";
                cout << "Enter route name: ";
                getline(cin, input1);
                cout << "Enter level (1=LOW, 2=MEDIUM, 3=HIGH): ";
                cin >> level;
                cin.ignore();
                TrafficLevel l = (level == 1) ? LOW : (level == 2) ? MEDIUM : HIGH;
                tm.pushUpdate(TrafficUpdate(input1, l));
                break;
            }
            case 18:
                cout << "\n[*] Process Traffic Updates (Queue)\n";
                tm.processUpdates();
                break;
            case 19:
                tm.showAllTraffic();
                break;
            default:
                cout << "[!] Invalid choice!\n";
        }
    }
}

int main() {
    cout << "\n========================================\n";
    cout << "  DSA PROJECT\n";
    cout << "  Data Structures & Algorithms Demo\n";
    cout << "========================================\n";
    cout << "\nDemonstrates:\n";
    cout << "1. Hash Map (unordered_map)\n";
    cout << "2. Trie (Prefix Tree)\n";
    cout << "3. Graph + Dijkstra's Algorithm\n";
    cout << "4. Linked List\n";
    cout << "5. Queue (FIFO)\n";
    cout << "6. Priority Queue (Min-Heap)\n";
    cout << "========================================\n";

    UserSystem us;
    Trie trie;
    Graph g;
    BusRouteManager brm;
    TrafficManager tm;

    // Add some sample data for demonstration
    cout << "\n[*] Adding sample data...\n";
    
    // Sample locations for Trie and Graph
    vector<string> sampleLocations = {"Mumbai", "Delhi", "Bangalore", "Chennai", "Kolkata"};
    for (auto &loc : sampleLocations) {
        trie.insert(loc);
        g.addLocation(loc);
    }
    
    // Sample graph edges
    g.addEdge("Mumbai", "Delhi", 1400);
    g.addEdge("Mumbai", "Bangalore", 850);
    g.addEdge("Delhi", "Bangalore", 2150);
    g.addEdge("Bangalore", "Chennai", 350);
    g.addEdge("Chennai", "Kolkata", 1650);
    
    cout << "[+] Sample data added!\n";

    mainMenu(us, g, trie, brm, tm);

    return 0;
}
