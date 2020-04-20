// Developed by : FITYANDHIYA ISLAM NUGROHO
// MINIGAME BALL C++
// topic : cpp, stack, array, game, push, pop

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>     // digunakan pd fungsi codeBall() & isColorBall()
#include <sstream>    // digunakan pd fungsi num_conversion()

// Utk membuat random number generator pd fungsi addBall()
#include <cstdlib>
#include <ctime>

using namespace std;


// Deklarasi Jumlah Tabung & Volumenya
const int nTube = 4;   // lebihkan 1 dr jumlah warna bola sbg tabung kosong
const int volume = 3;  // kapasitas bola maks. dalam setiap tabung

// Deklarasi Warna Bola                                 // !! Warna dpt diganti TETAPI TIDAK BISA DITAMBAHKAN
string color[nTube-1] = {"Pink", "Biru", "Hijau"};      // lakukan pergantian nama warna dgn fungsi Replace All pada Editor
int nColor[nTube-1];                                    // banyak bola masing2 jenis warna

// variabel lain
int countMoving = 0;       // menghitung jumlah perpindahan bola
string str;                // variabel utk menampung inputan user

// deklarasi tabung
struct Tube{
    int top;
    string ball[volume];
} t[nTube];


// fungsi-fungsi
int num_conversion(string str);       // mengubah tipe data string ke int (Terkait Validasi Inputan)
void createTube();                    // mereset isi tabung
void pushTube(int n, string ball);    // memasukkan bola ke tabung[n]
void popTube(int n);                  // mengeluarkan bola dari tabung[n]
void moveFromTo(int x, int y);        // memindahkan bola dari tabung[x] ke tabung[y]
int volExist(int n);                  // mengecek volume tabung yg tersedia
void setColor();                      // mereset jumlah warna bola disetiap tabung
void showTube();                      // menampilkan tabung dan isinya
void start();                         // prosedur mulai gamenya
void startSort();                     // prosedur menyusun bola
string codeBall(int ch);              // memberikan kode bola sesuai warna
string isColorBall(string ball);      // menganalisa warna bola
void addBall();                       // prosedur menambahkan bola
bool allSorted();                     // menganalisis hasil penyusunan agar GAME OVER


// Main
main(){
	createTube();
	showTube();
	cout << "\n Tekan Enter..."; getch();

    while (1){
        system("cls");
        createTube();
        
        cout << endl;
        cout << "\n ========== GAME BOLA DALAM TABUNG ===========";
        cout << "\n                  1. Mulai";
        cout << "\n                                      0. Exit";
        cout << "\n  Pilih : "; cin >> str;
        
        switch(num_conversion(str)){
            case 1:
                start();
                break;
            case 0:
                cout << "\n Anda keluar dari aplikasi \n";
                exit(1);
                break;
            default:
                cout << "\n Pilihan anda tidak valid";
                break;
        }
        cout << "\n Tekan tombol apapun untuk melanjutkan...";
        getch();
    }
}

void start(){
	system("cls");
	cout << "\n PETUNJUK :\n Akan ada tabung-tabung berisi bola dengan warna acak.\n Anda harus mengelompokkan bola-bola sesuai warnanya dalam satu tabung yang sama.\n";
	cout << "\n   Warna Bola :   " << color[0].at(0) << " = Pink     " << color[1].at(0) << " = Biru     " << color[2].at(0) << " = Hijau";
	setColor();
    cout << "\n\n Mulai Game..."; getch();
    addBall();


   	while(allSorted() == false) {
   	    startSort();
   	}

	cout << "\n Anda Berhasil"; getch();
   	system("cls");
	cout << "\n Hasil Akhir : ";
	showTube();
	cout << "\n Banyak perpindahan bola yang anda lakukan : \n";
	cout << "\n " << countMoving << " kali\n";
}

void addBall(){
	// No Tabung [pd array]       :  0, 1, 2 dst.
	// KODE WARNA BOLA            :  1 = Pink   2 = Biru   3 = Hijau

    // PILIH BOLA YG AKAN DIMASUKKAN
	// cth : pushTube(<noTabung>, codeBall(<kodeWarna>))

	// integrasi fungsi rand dan time
	srand(time(NULL));

	// utk menyimpan bilangan random
	int rnd1, rnd2;

	// loop tabung
	for (int i = 0; i < nTube-1; ++i)
	{
		// loop volume
		for (int j = 0; j < volume; ++j)
		{
			MARK :
			// mendapatkan bil. random (antara 0 - 2)
			rnd1 = (rand()%10/4);  // utk no tabung (0 - 2)
			rnd2 = (rand()%10/4+1);  // utk kode warna (1 - 3)

			// mengecek ketersediaan bola && kapasitas tabung
			if (nColor[rnd2-1] != 0 && volExist(rnd1) > 0)
            {
				/* Menginputkan Bola */
				pushTube(rnd1, codeBall(rnd2));
			} 
			else
				goto MARK;
		}
	}
}

int num_conversion(string str){
	int hsl_konversi, ini_angka = 0, bkn_angka = 0;

	for (int i = 0; i < str.size(); ++i)
    { 
        // membaca angka dalam inputan
		if (isdigit(str[i]))
			ini_angka++;
		else 
			bkn_angka++;
	}

	if (ini_angka == str.size() && bkn_angka == 0)
	{
		stringstream stream(str);
		stream >> hsl_konversi;
	}
	else 
        hsl_konversi = -1;

    return hsl_konversi;
}

void createTube(){
    for (int i = 0; i < nTube; ++i){
    	for (int j = 0; j < volume; ++j)
	    	t[i].ball[j] = "  ";           // reset ball
    	
    	t[i].top = -1;                     // reset top
    }
}

int volExist(int n){
	int hsl;
	// jika kosong
	if (t[n].top == -1){
		hsl = volume;
	}

	// jika penuh
	else if (t[n].top == volume-1){
		hsl = 0;
	}

	// jika terisi sebagian
	else if (t[n].top < volume-1){
		hsl = (volume-1) - (t[n].top);
	}
	return hsl;
}

void pushTube(int n, string ball){
    if(t[n].top != volume-1)       // jika TIDAK PENUH           
    {
        t[n].top++;
        t[n].ball[t[n].top] = ball;
    }
}

void popTube(int n){
    if(t[n].top != -1)     // jika TIDAK KOSONG
    {
    	// menghapus data tersimpan
        t[n].ball[t[n].top] = "  ";

        // menurunkan top
        t[n].top--;
    }
}

void moveFromTo(int x, int y){
	// memindahkan bola dari tabung[x] ke tabung[y]
	if (t[y].top < volume)
	{
		pushTube(y, t[x].ball[t[x].top]);
		popTube(x);
		countMoving++;
	}
}

void setColor(){
	// LOOPING JML WARNA
	for (int i = 0; i < nTube-1; ++i){
		nColor[i] = volume;
	}
}

string codeBall(int ch){
	string code;

	switch(ch){
		case 1 :
			// Jika Kode warna = 1 (dalam kasus ini = Pink)
			code = color[ch-1].at(0) + to_string(nColor[ch-1]);    // Output = 'P'
			(nColor[ch-1])--;                                      // Mengurangi Jml Bola Pink
			break;
		case 2 :
			// Jika Kode warna = 2
			code = color[ch-1].at(0) + to_string(nColor[ch-1]);
			(nColor[ch-1])--;
			break;
		case 3 :
			// Jika Kode warna = 2
			code = color[ch-1].at(0) + to_string(nColor[ch-1]);
			(nColor[ch-1])--;
			break;
		}
    return code;
}

string isColorBall(string ball){
	// akses kode warna
	int x = 0;
	if (ball.at(0) == color[x].at(0))
        str = "Pink";
    else if (ball.at(0) == color[x+1].at(0))
    	str = "Biru";
    else if (ball.at(0) == color[x+2].at(0))
        str = "Hijau";
    else
    	str = "None";

    return str;
}

void showTube(){
	int n = nTube;

	cout << endl;
	for (int i = volume-1; i >= 0; i--){
	    cout << "\n\t| " << t[n-4].ball[i] << " |\t| " << t[n-3].ball[i] << " |\t| " << t[n-2].ball[i] << " |\t| " << t[n-1].ball[i] << " |";
	}
	cout << "\n\t|====|\t|====|\t|====|\t|====|";
	cout << "\n\t  1   \t  2   \t  3   \t  4   "; 
	cout << endl;
}

void startSort(){
	int popValid = 0, pushValid = 0;

	while(popValid != 1 && pushValid != 1) 
	{
	    int frm = -1, to = -1;
	    string ballFrom, ballTo;

		system("cls");
		showTube();
		// cout << "\n Perpindahan Bola = " << countMoving << " kali\n";

		cout << "\n Pindahkan Dari Tabung : "; cin >> ballFrom;
		frm = num_conversion(ballFrom);
		cout << " Ke Tabung             : "; cin >> ballTo;
		to = num_conversion(ballTo);

		// Decrement Nilai Inputan
		frm--;
		to--;

		// Cek Pilihan Tabung
		// Utk melakukan POP, maka tabung 'from' tdk boleh KOSONG
		cout << endl;
		if ((frm >= 0 && frm < nTube))
		{
			if (t[frm].top != -1)
				popValid++;
			else
				cout << "!!! Tabung " << frm+1 << " kosong !!!\n";
		}
		else
			cout << "!!! Tabung " << ballFrom << " Tidak Ada !!!\n";

		// Utk melakukan PUSH, maka tabung 'to' tdk boleh PENUH
		if ((to >= 0 && to < nTube))
		{
			if (volExist(to) > 0)
				pushValid++;
			else
				cout << "!!! Tabung " << to+1 << " sudah penuh !!!\n";
		}
		else
			cout << "!!! Tabung " << ballTo << " Tidak Ada !!!\n";

		// JIKA VALID
		if (popValid == 1 && pushValid == 1){
			moveFromTo(frm, to);
			break;
		}
		getch();
	}
}

bool allSorted(){
    // default return == false
	
	/*  
		Game berhasil apabila setiap tabung berisi bola dengan warna yang sama.
		Karena itu, perlu dilakukan pengecekan jumlah warna pada tiap tabung.
		Jika jumlah salah satu warna pada masing2 tabung == volume maksimal,
		maka Game selesai.  
	*/
    int matchT = 0, matchV = 0;
    
	// Looping Tabung
	for (int i = 0; i < nTube; ++i)
	{
		matchV = 0;

		//Looping value
		for (int j = 0; j < volume-1; ++j)
		{
			if (isColorBall(t[i].ball[j]) == isColorBall(t[i].ball[j+1]))
				matchV++;
			if (matchV == volume-1){
				matchT++;
				break;
			}
		}
		if (matchT == nTube)
			break;
	}
	
	if (matchT == nTube)
		return true;
	else
		return false;
}
