#include <iostream>

using namespace std;

struct Package{
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct Courier{
    string courierName;
    string vehicleType;
};

class PackageStrack{
private:
    Package* top;

public:
    PackageStrack(): top(nullptr){}

    void push(string id, string city, int l, int w, int h){
        Package* newPkg = new Package;
        newPkg->packageID = id;
        newPkg->destinationCity = city;
        newPkg->dimensions[0]=l;
        newPkg->dimensions[1]=w;
        newPkg->dimensions[2]=h;
        top = newPkg;
        cout << "Package " << id << " added to stack.\n";
    }

    Package* pop(){
        if(isEmpty()) return nullptr;
        Package* temp = top;
        top = top->next;
        return temp;
    }

    bool isEmpty(){return top = nullptr;}

    void display(){
        if(isEmpty()){
            cout << "Stack is empty.\n";
            return;
        }
        Package* curr = top;
        cout << "---Current packages (stack)---\n";
        while (curr) {
            cout << "ID: " << curr->packageID << " | To: " << curr->destinationCity
                 << " | Dim: " << curr->dimensions[0] << "x" << curr->dimensions[1] << "x" << curr->dimensions[2] << endl;
            curr = curr->next;
        }
    }
};

class CourierQueue{
private:
    static const int SIZE = 5;
    Courier arr[SIZE];
    int front, rear;

public:
    CourierQueue(): front(-1), rear(-1){}

    bool isFull(){
        return (front==(rear-1)%SIZE);
    }

    bool isEmpty(){
        return (front == -1);
    }

    void enqueue(string name, string vehicle){
        if(isFull()){
            cout << "Queue is full! Cannot register courier" << name << ".\n";
            return;
        }
        if(isEmpty()) front = 0;
        rear = (rear+1)%SIZE;
        arr[rear].courierName = name;
        arr[rear].vehicleType = vehicle;
        cout << "Courier " << name << " registered.\n";
    }

    Courier dequeue(){
        Courier empty = {"",""};
        if(isEmpty()) return empty;

        Courier removed = arr[front];
        if (front == rear){
            front = rear == -1;
        }else{
            front = (front+1)%SIZE;
        }
        return removed;
    }

    void display(){
        if(isEmpty()){
            cout << "No couriers waiting.\n";
            return;
        }
        cout << "---Waiting Couriers (Circular Queque)---\n";
        int i=front;
        while (true) {
            cout << "Name: " << arr[i].courierName << " | Vehicle: " << arr[i].vehicleType << endl;
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
    }
};

int main()
{
    PackageStrack stack;
    CourierQueue queue;

    stack.push("PKG001", "New York", 10,10,5);
    stack.push("PKG002", "London", 20,15,10);

    queue.enqueue("Alice", "Van");
    queue.enqueue("Bob", "Motorcyle");

    stack.display();
    queue.display();

    cout << "\n---Dispatching---\n";
    if (!stack.isEmpty() && !queue.isEmpty()) {
        Package* p = stack.pop();
        Courier c = queue.dequeue();
        cout << "Courier " << c.courierName << " is delivering package " << p->packageID << " to " << p->destinationCity << ".\n";
        delete p;
    }

    cout << "\n---Final State---\n";
    stack.display();
    queue.display();
}
