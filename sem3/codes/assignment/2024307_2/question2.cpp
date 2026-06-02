#include <iostream>
#include <string>
using namespace std;


struct person{

    string name;
    string address;
    int phone;

    person(string x = "", string y = "", int z = 0) : name(x), address(y), phone(z) {}
};


class Node {

    public:

        person data;
        Node* next;

        Node( person p) {

            data = p;
            next = nullptr;
        }
    
};

class linkedlist {

    Node* head= nullptr;

    public:

        void add(person p){

            Node* newnode = new  Node(p);

            if (head == nullptr || p.name < head->data.name)        // basically our pushfront logic for case 1
            {
            newnode->next = head;
            head = newnode;
            return;
            }

       
        Node* temp = head;

        while (temp->next != nullptr && temp->next->data.name < p.name) 
        {
            temp = temp->next;
        }

        newnode->next = temp->next;
        temp->next = newnode;           // setting the previous chain link to the new node so theres only 1 link
    }

        person find(string name){

        Node* temp = head;

        while(temp!= nullptr){

            if(temp->data.name== name){

                return (temp->data);
            }
            temp = temp->next;
        }
        return person("","",0);
     }
};


int main(){

    linkedlist L1;


    int choice;

    do {
        cout<<"\n1. ADD PERSON \n2. FIND PERSON \n3. EXIT \n";
        cout<<"ENTER CHOICE: ";

        cin>>choice;
        cin.ignore();


        if(choice == 1){

            string name,address;
            int phone;

            cout<<"ENTER NAME: ";
            getline(cin,name);

             cout << "Enter address: ";
            getline(cin, address);

            cout << "Enter phone: ";
            cin>>phone;


            person p(name, address, phone);
            L1.add(p);
            cout << "Person added!\n";
        }

        else if (choice == 2) 
        {
            string name;

            cout << "Enter name to find: ";
            getline(cin, name);

            person result = L1.find(name);


            if (result.name != "") {
                cout << "Record found:\n";
                cout << "Name: " << result.name << endl;
                cout << "Address: " << result.address << endl;
                cout << "Phone: " << result.phone << endl;
            }
             else 
            {
                cout << "No record found with that name.\n";
            }
        }

    } while (choice != 3);

    return 0;
}