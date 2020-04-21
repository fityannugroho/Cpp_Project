// BUY CINEMA TICKETS - ARRAY IMPLEMENTATION
// Developed By : FITYANDHIYA ISLAM NUGROHO
// topics       : cpp, array, array1d, 1dimensi, array2d, 2dimensi, struct, while, for, void, return function.
// language     : ENG - ID

#include <iostream>
#include <sstream> 
#include <conio.h>

using namespace std;

// Deklarasi objek movie dgn atribut title, cinema, seat, dan price
struct Movie {
	string title[2] = {"AVENGER : INFINITY WAR", "AVENGER : END GAME"};
	string cinema[4] = {"XXI UBERTOS", "CGV UBERTOS", "XXI JATOS", "CGV JATOS"};

	int stRow = 6, stNum = 5;
	string seat[6][5] = {
		"A1", "A2", "A3", "A4", "A5",
		"B1", "B2", "B3", "B4", "B5",
		"C1", "C2", "C3", "C4", "C5",
		"D1", "D2", "D3", "D4", "D5",
		"E1", "E2", "E3", "E4", "E5",
		"F1", "F2", "F3", "F4", "F5"
		};

	int price[2][4] = {
		50000, 55000, 40000, 30000,     // harga tiket movie1 di cinema1-2-3-4
		30000, 35000, 10000, 1000       // harga tiket movie2 di cinema1-2-3-4
		};
} film;

struct Transaction {
	Movie film;
	int movieCh, cinemaCh, many_tickets, sum_cost;
	string *num_seat = new string[15];
	string info;
} pay;

// variabel pendukung
int n_movie = sizeof(film.title)/sizeof(string);
int n_cinema = sizeof(film.cinema)/sizeof(string);
string choose;
bool valid;

// prototype fungsi-fungsi
void selectMovie();
void selectCinema();
void selectSeat();
void countPrice();
void showReceipt();
int num_conversion(string &);

// main
main(){
	while (1){
		system("cls");
		cout << "\n ====================== TIKS ID ======================";
		cout << "\n             Get Your Cinema Tickets Here";
		cout << "\n =====================================================";
		cout << "\n                BEST OFFER FOR TODAY :";
		cout << "\n                    Buy 5 get 6";
		cout << "\n               Buy 10 get 10% discount\n";
		cout << "\n   1. BUY NOW";
		cout << "\n   0. Exit\n";
		cout << "\n   Select Here : "; cin >> choose;

		switch (num_conversion(choose)){
		case 1:
			selectMovie();
 			selectCinema();
 			selectSeat();
 			countPrice();
			showReceipt();
			break;
		case 0:
			cout << "\n You out from this app\n";
			exit(1);
			break;
		default:
			cout << "\n Sorry, your choice isn't available !!!";
			break;
		}
		getch();
	}
}

// fungsi-fungsi
int num_conversion(string &str){
	int hsl_konversi, ini_angka = 0, bkn_angka = 0;

	for (int i = 0; i < str.size(); ++i){
		if (isdigit(str[i]))
			ini_angka++;
		else 
			bkn_angka++;
	}

	if (ini_angka == str.size() && bkn_angka == 0){
		stringstream streamObject(str);
		streamObject >> hsl_konversi;
		return hsl_konversi;
	}
	else
		return 0;
}

void selectMovie(){
	valid = false;
	while (valid == false)
	{
		// LIST MOVIE
		system("cls");
		cout << "\n -----------------------------------------------------";
		cout << "\n List Movie : ";
		for (int i = 0; i < n_movie; ++i)
			cout << "\n " << i+1 << ". "<< film.title[i];
		cout << "\n -----------------------------------------------------\n";

		cout << " Choose movie do you want to watch : ";
		cin >> choose;
		pay.movieCh = num_conversion(choose);

		if (pay.movieCh > 0 && pay.movieCh <= n_movie)
			valid = true;
		else {
			cout << "\n Sorry, your movie isn't available !!!";
			getch();
		}
	}
}

void selectCinema(){
	valid = false;
	while (valid == false)
	{
		// LIST CINEMA
		system("cls");
		cout << "\n List Cinema : ";
		cout << "\n Item |\t Cinema \t|\t Ticket Price \t";
		for (int i = 0; i < n_cinema; ++i)
			cout << "\n   " << i+1 << "  |\t" << film.cinema[i] << "\t|\t Rp " << film.price[(pay.movieCh)-1][i];
		cout << "\n -----------------------------------------------------\n";

		// CHOOSE CINEMA
		cout << " Choose where do you want to watch : "; cin >> choose;
		pay.cinemaCh = num_conversion(choose);

		if (pay.cinemaCh > 0 && pay.cinemaCh <= n_cinema)
			valid = true;
		else {
			cout << "\n Sorry, your cinema isn't available !!!";
			getch();
		}
	}
}

void selectSeat(){
	// BUY TICKETS
	valid = false;
	while (valid == false)
	{
		system("cls");
		cout << "\n How many tickets do you want : "; cin >> choose;
		pay.many_tickets = num_conversion(choose);

		if (pay.many_tickets > 0 && pay.many_tickets <= 15){
			cout << "\n Next, choose where you will sit...";
			valid = !valid;
		}
		else if (pay.many_tickets > 15)
			cout << "\n You have only buy max. 15 tickets each transaction !!!"; 
		else if (pay.many_tickets < 1)
			cout << "\n Sorry, your choice isn't valid !!!";
		getch();
	}

	// CHOOSE SEAT
	int counter = 0;
	while (counter < pay.many_tickets){
		valid = false;
		system("cls");

		cout << "\n Available Seat : \n\n     ";
		for (int i = 0; i < film.stRow; ++i){
			for (int j = 0; j < film.stNum; ++j)
				cout << " " << film.seat[i][j];
			cout << "\n     ";
		}
		cout << "\n ========= SCREEN =========\n\n";

		cout << " Choose the number " << counter+1 << " seat : "; cin >> pay.num_seat[counter];

		// Cek keberadaan kursi
		for (int i = 0; i < film.stRow; ++i){
			for (int j = 0; j < film.stNum; ++j)
			{
				if (pay.num_seat[counter] == film.seat[i][j])
				{
					cout << " Seat " << film.seat[i][j] << " is selected.";
					film.seat[i][j] = "--";
					counter++;                         
					valid = true;
				}
			}
		}
		if (valid == false)
			cout << " Sorry, the seat of your choice isn't available !!!";
		getch();
	}
}

void countPrice(){
	if (pay.many_tickets >= 10){
		pay.sum_cost = film.price[(pay.movieCh)-1][(pay.cinemaCh)-1] * pay.many_tickets;
		pay.many_tickets++;
		pay.info = " - You got free 1 ticket -";
	} 
	else if (pay.many_tickets >= 5 && pay.many_tickets < 10){
		int notDisc = film.price[(pay.movieCh)-1][(pay.cinemaCh)-1] * pay.many_tickets;
		int disc = notDisc * 10 / 100;
		pay.sum_cost = notDisc - disc;
		pay.info = " - You got discount 10% for this transaction -";
	} 
	else
		pay.sum_cost = film.price[(pay.movieCh)-1][(pay.cinemaCh)-1] * pay.many_tickets;
}

void showReceipt(){
	system("cls");
	cout << "\n =============== Your Transaction ===================";
	cout << "\n Movie Title      : " << pay.film.title[pay.movieCh-1];
	cout << "\n Cinema           : " << pay.film.cinema[pay.cinemaCh-1];
	cout << "\n Total Ticket(s)  : " << pay.many_tickets;
	cout << "\n Number Seat      : ";
	for (int i = 0; i < pay.many_tickets; ++i)
		cout << pay.num_seat[i] << " ";

	cout << "\n TOTAL PRICE      : Rp " << pay.sum_cost;

	if (pay.many_tickets >= 5)
		cout << "\n " << pay.info;
	cout << "\n ====================================================";
	cout << "\n             THANKS FOR YOUR PURCHASE";
}
