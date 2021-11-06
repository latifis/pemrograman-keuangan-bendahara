#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;
//variabel global
int totalmasuk=0;
int totalkeluar=0;

struct mhs {
int no;
string nama;
int kas;
}data[50];

struct outcome{
	int no;
	string tujuan;
	int jumlah;
}pengeluaran[50];

struct uang{
	int masuk;
	int keluar;
}catatan[13];
//isi nilai catatannya 0 untuk sementara

string file1= "file1.txt"; //ini buat nambahin materi aja

//deklarasi void
void inputdata();
void inputdatafile(int batas);
void lihatdata();
void hitungtotal(int *total, int batas); //rekrusif
void tambahdata();
void catatanmasuk();
void load (int *banyak);
void updatedata(int banyak);
void urutin(int banyak); //sorting
void hitungmasuk(int bln, int *hasil);
void hitungpengeluaran (int bln, int *batas); 
void loadfilemasuk();
void loadfilekeluar(int *batas);
void inputfilecatatanmasuk();
void inputfilecatatankeluar(int *batas);
void hitungpengeluaran (int bln, int *batas);
void pengeluaranbulanan(int bln, int *hasil);
void loadfilekeluarbulanan();
void inputfilecatatankeluarbulanan();
void lihat();




main (){
	//variabel
	int pilih;
	
	//program
	cout <<"Program catatan keuangan bendahara" <<endl;
	cout <<"1. Isi data siswa"<<endl;
	cout <<"2. Tambah data kas"<<endl;
	cout <<"3. Lihat data kas"<<endl;
	cout <<"4. Catat pemasukan dan pengeluaran"<<endl;
	cout <<"5. Lihat pemasukan dan pegeluaran"<<endl;
	cout <<"6. Exit"<<endl;
	cout <<"pilih : "; cin >>pilih;
	switch (pilih){
		case 1:
			inputdata(); //input data ke array dulu
			break;
		case 2:
			system("cls");
			tambahdata();
			break;
		case 3 :
			lihatdata();
			break;
		case 4 :
			system("cls");
			catatanmasuk();
			break;
		case 5 :
			lihat();
			break;
		default : system("cls");
	}
	
}

void inputdata(){
	int banyak;
	char menu;
	bool sorted=false; // untuk cek urut atau ga

	cout << endl <<endl;
	cout <<"*Menu ini hanya dijalankan ketika pertama kali membuka program*"<<endl; //konfirmasi ini buat pertama kali jalanin doang
	cout <<"lanjutkan?(y/n) : "; cin >> menu;
	system("cls");
	if (menu=='y'){
	
		cout<<"Masukan jumlah siswa : "; cin >> banyak;
		
		
		for (int i=0; i<banyak; i++){
			//isi data nomor absen dan nama
			cout <<i+1<<". No absen : "; cin>>data[i].no; 
			cout << "   Nama : "; cin.ignore(); getline(cin, data[i].nama);
	
			//buat data kas tiap siswa = 0
			data[i].kas=0;			
			}

		//cek apakah data nomor absen yang di input sudah urut	
		for (int i=0; i<banyak; i++){
			if (data[i].no!=i+1){ //kalo belum diurutin dulu
				sorted=true;
				break;
			}
		}
		if (sorted){
			urutin(banyak);
		}
		else{
			inputdatafile(banyak); //input data ke file
			system("cls");
		}
			
		}
		
	else {
		main();
	}
}

void urutin (int banyak){
	mhs temp;
	//selection sort urutin di array nya
	for (int i=0; i<banyak; i++){
		for (int j=i+1; j<banyak; j++){
			if (data[i].no>data[j].no){
				temp = data[j];
				data[j] = data[i];
				data[i] = temp;
			}
		}
	}
	inputdatafile(banyak); //input data yang sudah urut ke file

}

void inputdatafile(int batas){
	
		 //untuk nulis ke txt
		ofstream input;
		
		//masukin array data siswa ke file1.txt
		input.open(file1.c_str());
		for (int i=0; i<batas; i++){
			//masukin data siswa ke file1
			input << data[i].no << endl << data[i].nama<<endl;	
		}
		input.close();	
		
		//masukin array data kas ke file2.txt
		input.open("file2.txt");
		for (int i=0; i<batas; i++){
			input << data[i].no << endl << data[i].kas <<endl;
		}
		input.close();
		system("cls");
		cout << "data berhasil disimpan"<<endl;
		main();
}

void lihatdata(){
int batas=0, total=0;
load(&batas);
	hitungtotal(&total, batas);
	cout <<"|| No. || Nama                   || bayar kas        ||"<<endl;
	for (int i=0; i<batas; i++){
		cout <<"|| "<<setiosflags(ios::left)<<setw(4)<<data[i].no<<"|| ";
		cout <<setiosflags(ios::left)<<setw(23)<<data[i].nama << "|| ";
		cout <<setiosflags(ios::left)<<setw(17)<<data[i].kas<<"||"<<endl;
	}
	cout << endl << "total pemasukan kas : " << total;
	
	cout <<endl<<endl<<"tekan enter untuk kembali ke menu utama"<<endl;
	getch();
	system("cls");
	main();
}

//rekrusif
void hitungtotal(int *total, int batas){
	int nilaiakhir;
	if (batas>=0){
		*total+=data[batas].kas;
		batas-=1;
		hitungtotal(total, batas);
	}
}

void load (int *banyak){
	
		//load file buat ditambah
		ifstream baca;
				baca.open("file1.txt");
				for(int i=0; true; i++){
					baca>>data[i].no;
					baca.ignore();
					getline(baca,data[i].nama);
					// cout <<i<<" "<< data[i].no<<". "<<data[i].nama<<endl; buat ngecek aja sih
					if(baca.eof()){
						*banyak=i;
						break;
						}
					}
				baca.close();
				
						
			baca.open("file2.txt");
			for (int j=0; j<=*banyak; j++){
				baca >> data[j].no;
				baca >> data[j].kas;
			}
			baca.close();		
}

void tambahdata(){

	int pilih, byr, tambah, no=0;
	int banyak=0;
	
	

	load(&banyak);
	cout <<"1. tambah data kas siswa dengan nomor absen "<<endl;
	cout <<"2. tambah data kas semua siswa"<<endl;
	cout <<"3. tambah data siswa"<<endl;
	cout <<"4. Kembali ke menu utama"<<endl;
	cout << "pilih : "; cin >> pilih;
	switch (pilih){
		case 1 :

		cout <<"No || Nama                    ||"<<endl;
		cout<<"================================="<<endl; 
		for (int i=0; i<banyak; i++){
			cout << " "<< data[i].no << "    " << data[i].nama << endl;;
		}
		
		cout <<"pilih nomor absen siswa : "; cin >>pilih;
			//ini materi searching biasa
			for (int k=0; k<banyak; k++){
			if (pilih==data[k].no){
				cout << data[k].no << ". "<<data[k].nama<<endl;
				cout << "uang kas yang sudah dibayar : " << data[k].kas <<endl;
				cout << "bayar kas (x1000): "; cin >> byr;
				byr*=1000;
				data[k].kas+=byr;
				updatedata(banyak);
				system("cls");
				cout <<"data berhasil ditambahkan "<<endl<<endl;
				main();
				}
			}
			

		break;
		case 2 :

		for (int j=0; j<banyak; j++){
			cout << data[j].no << ". " << data[j].nama <<endl;
			cout << "uang kas yang sudah dibayar : " << data[j].kas <<endl;
			cout << "bayar kas (x1000) : "; cin >> byr;
			byr*=1000;
			data[j].kas+=byr;
		}
		updatedata(banyak);

		
		system("cls");
		cout <<"data berhasil ditambahkan "<<endl<<endl;
		main();
		break;
		case 3:
			cout << "Masukan banyak data siswa tambahan : "; cin >> tambah;
			for (int i=banyak; i<banyak+tambah; i++){
				cout <<no+1<<". No absen : "; cin>>data[i].no; 
				cout << "   Nama : "; cin.ignore(); getline(cin, data[i].nama);
				//buat data kas tiap siswa tambahannya = 0
				data[i].kas=0;
				no++;	
			}
			no=0; // kalo nanti nambah data lagi biar nomornya ngulang
			banyak+=tambah;
			inputdatafile(banyak);
			
		break;
		case 4:
			system("cls");
			main();
		break;
		default : system("cls");
	}
		
}

void updatedata(int banyak){
		ofstream input;
			//masukin data update nya ke file
		for (int j=0; j<banyak; j++){
			if (j==0){
				input.open("file2.txt"); // kalo nambahin data baru semua nilai kereset
				input << data[j].no << endl << data[j].kas <<endl;
				input.close();
			}
			else if (j>0) {
				input.open("file2.txt", ios::app);
				input << j+1 << endl << data[j].kas <<endl;
				input.close();
			}
		}
}

void catatanmasuk(){
	int pilih, bln, hasil=0;
	int no=0;
	char opsi;
	
			for (int i=0; i<=12; i++){
			catatan[i].masuk=0;
			catatan[i].keluar=0;
			}
			
	cout<<"1. catat pemasukan bulanan"<<endl;
	cout<<"2. catat pengeluaran bulanan"<<endl;
	cout<<"3. kembali ke menu utama"<<endl;
	cout << "pilih : "; cin >> pilih;
	switch (pilih){
	case 1:
		cout <<"Ini adalah bulan ke-(1-12) ? : "; cin >> bln;
		hitungmasuk(bln-1, &hasil);
		cout << "!data telah terekam"<<endl;
		cout << "data pemasukan kas bulan ke-"<<bln<<" sebesar " << hasil;
		
		cout <<endl<<endl<<"tekan enter untuk kembali ke menu utama"<<endl;
		getch();
		system("cls");
		main();
		break;
	case 2 :
			cout << "data pengeluaran kas bulan ke-(1-12) : "; cin>>bln;
			cout <<endl;
			loadfilekeluar(&no);
		do {
			pengeluaran[no].no=no+1;
			cin.ignore();
			cout<<no+1<<". Keperluan : ";  getline(cin,pengeluaran[no].tujuan);
			cout<<"   Biaya (x1000): "; cin >> pengeluaran[no].jumlah;
			pengeluaran[no].jumlah*=1000;
			cout<<endl;
			cout <<"masukan lagi ? (y/n) : "; cin >> opsi;
			cout<<endl;
			no++;
		}while (opsi=='y');

		inputfilecatatankeluar(&no);
		loadfilekeluarbulanan();
		hitungpengeluaran(bln-1, &no);
		pengeluaranbulanan(bln-1, &hasil);	
		inputfilecatatankeluarbulanan();

		cout << "data pengeluaran bulan ke-"<<bln<<" sebesar "<<hasil<<endl;
		
		cout <<endl<<endl<<"tekan enter untuk kembali ke menu utama"<<endl;
		getch();
		system("cls");
		main();
		
		break;
	case 3:
		system("cls");
		main();
		break;	
	}
}

void loadfilemasuk(){
	int b;
	int u;
	catatan[12].masuk=0;
	ifstream baca;
	baca.open("file3.txt");
	for (int i=0; i<12; i++){
		baca>>b;
		if (i+1==b){
			baca>>catatan[i].masuk;
			catatan[12].masuk+=catatan[i].masuk; //ngitung total uang masuk bulan bulan sebelumnya
		}
		else baca >> u;
	}
	baca.close();
}

void hitungmasuk(int bln, int *hasil){
	int batas=0;
	int uangbaru;
	load(&batas);
	loadfilemasuk();
	catatan[bln].masuk=0;
	for (int i=0; i<batas; i++){
		catatan[bln].masuk+=data[i].kas;
	}
	uangbaru=catatan[bln].masuk;
	catatan[bln].masuk-=catatan[12].masuk;
	
	cout<<"pemasukan total : " <<catatan[bln].masuk<<endl;
	cout<<"pemasukan bulan-bulan sebelumnya : "<<catatan[12].masuk<<endl;
	*hasil=catatan[bln].masuk;
	catatan[12].masuk=uangbaru;
	inputfilecatatanmasuk();
	
}

void inputfilecatatanmasuk(){
	ofstream input;
			input.open("file3.txt");
			for (int i=0; i<=12; i++){
				input << i+1 << endl;
				input << catatan[i].masuk<<endl;
			}
			input.close();
}

void inputfilecatatankeluar(int *batas){
	int banyak;
	ofstream input;

	input.open("file4.txt");
	for (int i=0; i<*batas; i++){
		input<<i+1<<endl;
		input<<pengeluaran[i].tujuan<<endl;
		input<<pengeluaran[i].jumlah<<endl;
		banyak=i+1;
	}
	*batas=banyak;
	input.close();
	
}
void loadfilekeluar(int *batas){
	
	ifstream baca;
	baca.open("file4.txt");
	if (baca.fail()){
		
		cout<<endl;
	}
	else {

		for (int i=0; true; i++){

		baca>>pengeluaran[i].no;
		baca.ignore();
		getline(baca,pengeluaran[i].tujuan);
		baca>>pengeluaran[i].jumlah;
			if (baca.eof()){

				*batas+=i;
				break;
			}
		}

	}
	baca.close();
}

void hitungpengeluaran (int bln, int *batas){
	for (int i=0; i<*batas; i++){
		catatan[bln].keluar+=pengeluaran[i].jumlah;
	}
}

void pengeluaranbulanan(int bln, int *hasil){
	int uangbaru;
	uangbaru=catatan[bln].keluar;
	cout<<"pengeluaran total : " <<catatan[bln].keluar<<endl;
	cout<<"pengeuaran bulan-bulan sebelumnya : "<<catatan[12].keluar<<endl;
	catatan[bln].keluar-=catatan[12].keluar; //pengeluaran baru dikurang pengeluaran sebelumnya
	*hasil=catatan[bln].keluar;
	catatan[12].keluar=uangbaru;
	inputfilecatatankeluarbulanan();
	
}

void loadfilekeluarbulanan(){
	int b;
	int u;
	ifstream baca;
	baca.open("file5.txt");
	catatan[12].keluar=0;
	for (int i=0; i<12; i++){
			baca>>b; //baca urutan bulannya
			baca>>catatan[i].keluar; //baca pengeluaran
			catatan[12].keluar+=catatan[i].keluar; //ngitung total uang keluar bulan bulan sebelumnya
	}
	baca.close();
}

void inputfilecatatankeluarbulanan(){
	ofstream input;
			input.open("file5.txt");
			for (int i=0; i<=12; i++){
				input << i+1 << endl;
				input << catatan[i].keluar<<endl;
			}
			input.close();
}

void lihat(){
	int batas=0, total=0;
	int pilih;
	string bulan[12]={"Januari","Februari","Maret","April","Mei","Juni",
	"Juli","Agustus","September","Oktober","November","Desember"};
	
	system("cls");
	cout <<"1. Lihat semua data pemasukan dan pengeluaran"<< endl;
	cout <<"2. Lihat data pemasukan dan pengeluaran perbulan"<<endl;
	cout <<"3. kembali ke menu utama"<<endl;
	cout <<"pilih : "; cin>>pilih;
	switch(pilih){
		case 1:
			
			load(&batas);
			hitungtotal(&total, batas);
			cout << "               Pemasukan kas kelas "<<endl;
			cout <<"======================================================="<<endl;
			cout <<"|| No. || Nama                   || bayar kas        ||"<<endl;
			for (int i=0; i<batas; i++){
				cout <<"|| "<<setiosflags(ios::left)<<setw(4)<<data[i].no<<"|| ";
				cout <<setiosflags(ios::left)<<setw(23)<<data[i].nama << "|| ";
				cout <<setiosflags(ios::left)<<setw(17)<<data[i].kas<<"||"<<endl;
				}
				cout <<"============================================================="<<endl;
				cout << "total pemasukan kas : " << total << endl;
				batas=0;
				loadfilekeluar(&batas);
				total=0;
				cout<<endl;
			cout << "               Pengeluaran kas kelas "<<endl;
			cout <<"============================================================="<<endl;
			cout <<"|| No. || Keperluan                   || Kas Keluar        ||"<<endl;
			for (int i=0; i<batas; i++){
				cout<<"|| "<<setiosflags(ios::left)<<setw(4)<<pengeluaran[i].no<<"|| ";
				cout<<setiosflags(ios::left)<<setw(28)<<pengeluaran[i].tujuan<< "|| ";
				cout<<setiosflags(ios::left)<<setw(18)<<pengeluaran[i].jumlah<<"||"<<endl;
				total+=pengeluaran[i].jumlah;
			}
			cout <<"============================================================="<<endl;
			cout << "total pengeluaran kas : " << total << endl;
			cout<<endl<<"tekan enter untuk kembali ke menu sebelumnya"<<endl;
			getch();
			system("cls");
			lihat();
			break;
		case 2:
			loadfilekeluarbulanan();
			loadfilemasuk();
			loadfilekeluarbulanan();
			cout <<""<<endl;
			cout <<"======================================================================================"<<endl;
			cout <<"|| No. || Bulan             || Pemasukan         || Pengeluaran       || Subtotal   ||"<<endl;
			for (int i=0; i<12; i++){
				cout<<"|| "<<setiosflags(ios::left)<<setw(4)<<i+1<<"|| ";
				cout<<setiosflags(ios::left)<<setw(18)<<bulan[i]<<"|| ";
				cout<<setiosflags(ios::left)<<setw(18)<<catatan[i].masuk<<"|| ";
				cout<<setiosflags(ios::left)<<setw(18)<<catatan[i].keluar<<"|| ";
				cout<<setiosflags(ios::left)<<setw(11)<<catatan[i].masuk-catatan[i].keluar<<"|| "<<endl;
			}
			cout <<"======================================================================================"<<endl;
			cout <<"|| TOTAL  :"<<setiosflags(ios::right)<<setw(29)<<catatan[12].masuk;
			cout << setiosflags(ios::right)<<setw(23)<<catatan[12].keluar;
			cout << setiosflags(ios::right)<<setw(18)<<catatan[12].masuk-catatan[12].keluar<<"   ||"<<endl;
			cout <<"======================================================================================"<<endl;

			cout<<endl<<endl<<"tekan enter untuk kembali ke menu sebelumnya"<<endl;
			getch();
			system("cls");
			lihat();
			break;
		case 3:
			system("cls");
			main;
			break;
	}
}

/*
catatan kekurangan program :
1. belum bisa edit misalkan ada data yng terlanjur di input atau salah
2. belum diatur buat reset 
3. masih ada bug data miss pada pencatatan bulanan, apabila terjadi double input

*/
