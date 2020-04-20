// Developed by : Fityandhiya Islam Nugroho
// Queue With Linked List Program
// topic : cpp, queue, linked list, node, head, costumer.
// language : Eng + Id.

/* Konsep :
    Menambahkan data dari belakang linked list (tail) dan mengeluarkan data dari awal linked list (head).
    Karena itulah digunakan single linked list.
    Pada data yg pertama kali masuk (node1), nilai next == NULL. Dan node1 menjadi head.
    Jika ada data baru (node2), maka node1 menyimpan alamat node2 (head->next == node2). Begitupun dengan node3, dst.
    Jika ada data keluar (node1 keluar), maka head menjadi milik node2 yg dimana dia sekarang menjadi node1.
*/

#include <iostream>
#include <windows.h>
#include <sstream>

using namespace std;

// Deklarasi node
int capacity = 5;
struct node
{
    string value;
    node *next;
};

// Membuat node baru
node *head = NULL;

int num_conversion(string str);
int isEmpty();
int isFull();
void insertQueue(string str);
void showQueue();
void deleteQueue();
void findQueue(string str);


main(){
    string str;

    while (1){
        system("cls");
        cout << "\n\n =================== QUEUE =======================";
        cout << "\n              1. New Costumer In";
        cout << "\n              2. Show Queue";
        cout << "\n              3. Costumer Out";
        cout << "\n              4. Find Costumer's Name";
        cout << "\n                                            0. Exit";
        cout << "\n Select The Number : "; cin >> str;

        switch (num_conversion(str)){
            case 1:
            	system("cls");
            	cout << "\n Insert costumer name : "; cin >> str;
	            insertQueue(str);	            
                break;
            case 2:
            	showQueue();
            	break;
            case 3:
            	deleteQueue();
            	break;
            case 4:
            	cout << "\n Input the costumer name who want to founded :\n "; cin >> str;
            	findQueue(str);
            	break;
            case 0:
                cout << "\n - You out from this program - \n";
                exit(1);
                break;
            default:
                cout << "\n - Your choice isn't valid -\n";
                break;
        }
        system("pause");
    }
}


int num_conversion(string str){
	int hsl_konversi, ini_angka = 0, bkn_angka = 0;

	for (int i = 0; i < str.size(); ++i){ 
        // membaca angka dalam inputan
		if (isdigit(str[i]))
			ini_angka++;
		else 
			bkn_angka++;
	}

	if (ini_angka == str.size() && bkn_angka == 0){
		stringstream stream(str);
		stream >> hsl_konversi;
	}
	else 
        hsl_konversi = -1;

    return hsl_konversi;
}

int isEmpty(){
    if (head == NULL)
        return 1;
    else
        return 0;
}

int isFull(){
    if (capacity == 0)
        return 1;
    else
        return 0;
}

void insertQueue(string str){
    if (isFull() != 1){
        node *addNode = new node();    // membuat node baru
        addNode->value = str;          // memasukkan data ke node baru
        addNode->next = NULL;          // menjadikan nilai next == NULL

        if (isEmpty() == 1)
            head = addNode;            // Jika list kosong, maka node ini menjadi head}
        else {
            node *current = head;            // deklarasi node temp
            while (current->next != NULL)
                current = current->next;     // Jika list tidak kosong, maka akan dicari node paling belakang
            
            current->next = addNode;         // node paling belakang menyimpan alamat node baru
        }
        cout << "\n New costumer is added \n";
        capacity--;                          // mengurangi kapasitas antrian
    } else
        cout << "\n Sorry, the queue is full. Can't add anymore.\n";
}

void showQueue(){
    node *current = head;

    if (isEmpty() == 1)
		cout << "\n The queue is empty now.\n";
	else {
		cout << "\n Queue now : \n";
	    while (current != NULL)  {                      // selama node yg dijumpai != NULL maka akan dicari smp NULL
	        cout << " " << current->value << " <-";     // mencetak value dari node current
	        current = current->next;                    // pindah ke node selanjutnya
	    }
        cout << " END\n" ;                            // saat mencapai ujung paling belakang
	}
}

void deleteQueue(){
    node *current = head;

    if (isEmpty() == 1)
        cout << "\n There is no one costumer.\n";
    else {
        if (current != NULL){                           // jika node yg dijumpai != NULL, maka program delete dieksekusi
            head = current->next;                       // menjadikan node setelah current sebagai head
            // Print notifikasi
            cout << "\n Costumer " << current->value << " had been served and out from queue now.\n";
            delete current;                             // menghapus node
            capacity++;                                 // menambahkan kapasitas antrian
        }
    }
}

void findQueue(string str){
    node *current = head;
    int counter = 0, found = 0;

    while (current != NULL){                    // selama node yg dijumpai != NULL, maka looping akan terus dilakukan sampai antrian terakhir
        counter++;                              // penghitung node bertambah

        if (current->value == str){              // jika data inputan == nilai di node, maka data ditemukan
            found++;
            cout << "\n Costumer " << str << " is found in place " << counter << endl;
        }
        current = current->next;                // pindah ke node selajutnya
    }
    // jika sampai node terakhir data tidak juga ditemukan, maka data memang tidak ada di antrian
    if (found == 0)                             
        cout << "\n There is no " << str << " in queue.\n";
}
