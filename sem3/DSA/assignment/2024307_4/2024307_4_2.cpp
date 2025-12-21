#include <iostream>
#include <string>
using namespace std;

struct Incident {
    int id;
    string desc;
    Incident* next;
    Incident(int i, string d) {
        id = i;
        desc = d;
        next = nullptr;
    }
};

struct Location {
    int loc_id;
    string area;
    string city;
    Incident* incident_head;
    Location* left;
    Location* right;
    int height;
    Location(int id, string a, string c) {
        loc_id = id;
        area = a;
        city = c;
        incident_head = nullptr;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Location* N) {
    if (N == nullptr) return 0;
    return N->height;
}

int getBalance(Location* N) {
    if (N == nullptr) return 0;
    return getHeight(N->left) - getHeight(N->right);
}

// Add incident silently (no success message)
void addIncident(Location* loc, int id, string desc) {
    Incident* newIncident = new Incident(id, desc);
    // Check for duplicate incident ID
    Incident* temp = loc->incident_head;
    while (temp != nullptr) {
        if (temp->id == id) {
            delete newIncident;  // avoid memory leak
            return;  // silently fail if duplicate
        }
        if (temp->next == nullptr) break;
        temp = temp->next;
    }
    if (loc->incident_head == nullptr) {
        loc->incident_head = newIncident;
    } else {
        temp->next = newIncident;
    }
}

// Delete incident silently
void deleteIncident(Location* loc, int id) {
    if (loc->incident_head == nullptr) {
        return;
    }
    Incident* temp = loc->incident_head;
    Incident* prev = nullptr;
    if (temp != nullptr && temp->id == id) {
        loc->incident_head = temp->next;
        delete temp;
        return;
    }
    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == nullptr) {
        return;  // not found
    }
    prev->next = temp->next;
    delete temp;
}

void displayIncidents(Incident* head) {
    if (head == nullptr) {
        cout << "(No Incidents Recorded)" << endl;
        return;
    }
    Incident* temp = head;
    while (temp != nullptr) {
        cout << "  -> [Inc ID: " << temp->id << " ] " << temp->desc << endl;
        temp = temp->next;
    }
}

void clearIncidents(Incident* head) {
    Incident* current = head;
    while (current != nullptr) {
        Incident* next = current->next;
        delete current;
        current = next;
    }
}

Location* rightRotate(Location* y) {
    Location* x = y->left;
    Location* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Location* leftRotate(Location* x) {
    Location* y = x->right;
    Location* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Location* insertLocation(Location* node, int id, string area, string city) {
    if (node == nullptr) {
        return new Location(id, area, city);
    }
    if (id < node->loc_id) {
        node->left = insertLocation(node->left, id, area, city);
    } else if (id > node->loc_id) {
        node->right = insertLocation(node->right, id, area, city);
    } else {
        return node;  // duplicate location ID - ignore silently
    }
    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && id < node->left->loc_id) return rightRotate(node);
    if (balance < -1 && id > node->right->loc_id) return leftRotate(node);
    if (balance > 1 && id > node->left->loc_id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && id < node->right->loc_id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Location* minValueNode(Location* node) {
    Location* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Location* deleteLocation(Location* root, int id) {
    if (root == nullptr) return root;

    if (id < root->loc_id) {
        root->left = deleteLocation(root->left, id);
    } else if (id > root->loc_id) {
        root->right = deleteLocation(root->right, id);
    } else {
        clearIncidents(root->incident_head);
        root->incident_head = nullptr;

        if (root->left == nullptr || root->right == nullptr) {
            Location* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Location* temp = minValueNode(root->right);
            root->loc_id = temp->loc_id;
            root->area = temp->area;
            root->city = temp->city;
            root->incident_head = temp->incident_head;
            temp->incident_head = nullptr;
            root->right = deleteLocation(root->right, temp->loc_id);
        }
    }

    if (root == nullptr) return root;

    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Location* searchLocation(Location* root, int id) {
    if (root == nullptr || root->loc_id == id) {
        return root;
    }
    if (id > root->loc_id) {
        return searchLocation(root->right, id);
    }
    return searchLocation(root->left, id);
}

void inOrderDisplay(Location* root) {
    if (root != nullptr) {
        inOrderDisplay(root->left);
        cout << "------------------------------------------------" << endl;
        cout << "Location ID: " << root->loc_id
             << " | Area: " << root->area
             << " | City: " << root->city << endl;
        cout << "Incidents:" << endl;
        displayIncidents(root->incident_head);
        inOrderDisplay(root->right);
    }
}

int main() {
    Location* root = nullptr;
    root = insertLocation(root, 10, "Hayatabad", "Peshawar");
    root = insertLocation(root, 15, "DHA", "Peshawar");
    root = insertLocation(root, 20, "University Road", "Peshawar");

    Location* loc120 = searchLocation(root, 120);
    if (loc120) addIncident(loc120, 1, "Fire near bank");
    if (loc120) addIncident(loc120, 2, "Traffic Accident");

    Location* loc115 = searchLocation(root, 115);
    if (loc115) addIncident(loc115, 1, "Protest at Main Road");

    int choice;
    do {
        cout << " === Emergency Response Management System === " << endl;
        cout << "1. Add Location " << endl;
        cout << "2. Remove Location. " << endl;
        cout << "3. Add Incident to Location " << endl;
        cout << "4. Delete Incident from Location" << endl;
        cout << "5. Display All (In-Order Traversal) " << endl;
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string area, city;
            cout << "Enter Location ID: "; cin >> id;
            cout << "Enter Area Name: "; cin.ignore(); getline(cin, area);
            cout << "Enter City: "; getline(cin, city);
            root = insertLocation(root, id, area, city);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Location ID to remove: "; cin >> id;
            root = deleteLocation(root, id);
        }
        else if (choice == 3) {
            int locId, incId;
            string desc;
            cout << "Enter Location ID: "; cin >> locId;
            Location* loc = searchLocation(root, locId);
            if (loc == nullptr) {
                cout << "Location not found!" << endl;
            } else {
                cout << "Enter Incident ID: "; cin >> incId;
                cout << "Enter Description: "; cin.ignore(); getline(cin, desc);
                addIncident(loc, incId, desc);
            }
        }
        else if (choice == 4) {
            int locId, incId;
            cout << "Enter Location ID: "; cin >> locId;
            Location* loc = searchLocation(root, locId);
            if (loc == nullptr) {
                cout << "Location not found!" << endl;
            } else {
                cout << "Enter Incident ID to delete: "; cin >> incId;
                deleteIncident(loc, incId);
            }
        }
        else if (choice == 5) {
            cout << "--- City Status Report ---" << endl;
            if (root == nullptr) {
                cout << "System is Empty." << endl;
            } else {
                inOrderDisplay(root);
            }
            cout << "-----------------------------------------------" << endl;
        }
    } while (choice != 0);

    return 0;
}