#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 5
#define MAX_SEATS 20
#define MAX_LOG 100

// Structure Definition
typedef struct {
    int bus_id;
    char route[50];
    int seats[MAX_SEATS]; 
    float fare;
} Bus;

// --- STACK FOR TRANSACTION HISTORY ---
typedef struct {
    char action[100];
} Transaction;

Transaction undoStack[MAX_LOG];
int top = -1;

void pushAction(char* msg) {
    if (top < MAX_LOG - 1) {
        strcpy(undoStack[++top].action, msg);
    }
}

// --- QUEUE FOR BOOKING REQUESTS ---
typedef struct {
    int bus_id;
    int seat_num;
} BookingRequest;

BookingRequest queue[MAX_LOG];
int front = 0, rear = 0;

void enqueue(int id, int sn) {
    // BUG FIX: Added Queue Overflow check
    if (rear >= MAX_LOG) {
        printf("[Error] Queue is full! Process pending bookings first.\n");
        return;
    }
    queue[rear].bus_id = id;
    queue[rear].seat_num = sn;
    rear++;
    printf("[Queue] Request added to processing line.\n");
}

// Global Data
Bus buses[MAX_BUSES];

// --- FUNCTION PROTOTYPES ---
void initializeData();
void viewSchedules();
void viewStatusBoard();
void processQueue();
void cancelSeat();
void sortBusesByFare(); 
void showHistory();     
void clearBuffer();

int main() {
    int choice, id, sn;
    initializeData();

    while (1) {
        printf("\n===== BUS RESERVATION SYSTEM =====\n");
        printf("1. View Schedules\n");
        printf("2. View Status Board\n");
        printf("3. Add Booking to Queue\n");
        printf("4. Process All Pending Bookings\n");
        printf("5. Cancel a Seat\n");
        printf("6. View Transaction History\n");
        printf("7. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }

        switch(choice) {
            case 1: 
                sortBusesByFare(); 
                viewSchedules(); 
                break;
            case 2: viewStatusBoard(); break;
            case 3: 
                printf("Enter Bus ID and Seat (1-20): ");
                scanf("%d %d", &id, &sn);
                enqueue(id, sn);
                break;
            case 4: processQueue(); break;
            case 5: cancelSeat(); break;
            case 6: showHistory(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// --- DSA IMPLEMENTATIONS ---

void cancelSeat() {
    int id, sn, i, found = -1;
    printf("Enter Bus ID to cancel from: ");
    scanf("%d", &id);
    
    for (i = 0; i < MAX_BUSES; i++) {
        if (buses[i].bus_id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("Bus ID not found.\n");
        return;
    }

    printf("Enter Seat Number to cancel (1-20): ");
    scanf("%d", &sn);

    if (sn < 1 || sn > MAX_SEATS) {
        printf("Invalid seat number.\n");
    } else if (buses[found].seats[sn-1] == 0) {
        printf("Seat is already vacant.\n");
    } else {
        buses[found].seats[sn-1] = 0;
        char log[100];
        sprintf(log, "Bus %d Seat %d Cancelled", id, sn);
        pushAction(log);
        printf("[Success] %s\n", log);
    }
}

void sortBusesByFare() {
    int i, j;
    Bus temp;
    for (i = 0; i < MAX_BUSES - 1; i++) {
        for (j = 0; j < MAX_BUSES - i - 1; j++) {
            if (buses[j].fare > buses[j+1].fare) {
                temp = buses[j];
                buses[j] = buses[j+1];
                buses[j+1] = temp;
            }
        }
    }
    printf("[Sort] Buses sorted by cheapest fare.\n");
}

void processQueue() {
    if (front == rear) {
        printf("Queue is empty!\n");
        return;
    }
    while (front < rear) {
        int id = queue[front].bus_id;
        int sn = queue[front].seat_num;
        int i, found = -1;

        for (i = 0; i < MAX_BUSES; i++) {
            if (buses[i].bus_id == id) found = i;
        }

        // BUG FIX: Added seat range validation (1-20)
        if (found != -1 && sn >= 1 && sn <= MAX_SEATS) {
            if (buses[found].seats[sn-1] == 0) {
                buses[found].seats[sn-1] = 1;
                char log[100];
                sprintf(log, "Bus %d Seat %d Booked", id, sn);
                pushAction(log); 
                printf("[Success] Processed: %s\n", log);
            } else {
                printf("[Failed] Bus %d Seat %d already taken.\n", id, sn);
            }
        } else {
            printf("[Failed] Invalid Bus ID or Seat Number (%d).\n", sn);
        }
        front++;
    }
    front = 0; rear = 0; // Reset queue after processing
}

void showHistory() {
    if (top == -1) {
        printf("No history found.\n");
        return;
    }
    // BUG FIX: Corrected loop to show FCFS (0 to top)
    printf("\n--- TRANSACTION HISTORY (First to Last) ---\n");
    int i;
    for (i = 0; i <= top; i++) { 
        printf("%d. %s\n", i + 1, undoStack[i].action);
    }
}

void initializeData() {
    char *routes[] = {"Manila-Baguio", "Pasay-Bicol", "Cebu-Oslob", "Davao-Tagum", "Iloilo-Caticlan"};
    int i, j;
    for (i = 0; i < MAX_BUSES; i++) {
        buses[i].bus_id = 101 + i;
        strcpy(buses[i].route, routes[i]);
        buses[i].fare = 900.00 - (i * 50); 
        for (j = 0; j < MAX_SEATS; j++) buses[i].seats[j] = 0;
    }
}

void viewSchedules() {
    int i;
    printf("\nID\tRoute\t\tFare\n");
    for (i = 0; i < MAX_BUSES; i++) {
        printf("%d\t%-15s\tPHP %.2f\n", buses[i].bus_id, buses[i].route, buses[i].fare);
    }
}

void viewStatusBoard() {
    int i, j;
    for (i = 0; i < MAX_BUSES; i++) {
        printf("\nBus %d [%s]\n", buses[i].bus_id, buses[i].route);
        for (j = 0; j < MAX_SEATS; j++) {
            printf("%s ", buses[i].seats[j] ? "[X]" : "[ ]");
            if ((j + 1) % 4 == 0) printf("  ");
        }
        printf("\n");
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != -1);
}
