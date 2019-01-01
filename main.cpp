#include <fstream>
#include <iostream>
#include "windows.h"
#include <string>
#include <iomanip>
using namespace std;

int counter = 0;

class SoloAlbum{
		public:
		int id;
		int year;
		string singer;
		string name;
		int amount;
		SoloAlbum *next, *prev;
		
		SoloAlbum(): id(++counter){
			cout<<"New album: "<<id;
		}
		
		SoloAlbum(int yearA, string nameA, string singerA, int amountA): year(yearA), name(nameA), singer(singerA), amount(amountA), id(++counter){
			cout<<"Album created: "<<name;
		}
		
		void showAll(){
			cout<<"Showing Solo Album with id: "<<id<<endl;
			cout<<"------------"<<endl;
			cout<<setw(30)<<left<<"Name: "<<name<<endl;
			cout<<setw(30)<<left<<"Year: "<<year<<endl;
			cout<<setw(30)<<left<<"Singer: "<<singer<<endl;
			cout<<setw(30)<<left<<"Amount: "<<amount<<endl;
		}
};

class Album{
	public:
		int id;
		int year;
		string group;
		string name;
		int amount;
		Album *next, *prev;
		SoloAlbum *ptrSolo;
		
		Album(): id(++counter){
			cout<<"New album: "<<id;
		}
		
		Album(int yearA, string nameA, string groupA, int amountA): year(yearA), name(nameA), group(groupA), amount(amountA), id(++counter){
			cout<<"Album created: "<<name;
		}
		
		void showAll(){
			cout<<"Showing Album with id: "<<id<<endl;
			cout<<"------------"<<endl;
			cout<<setw(30)<<left<<"Name: "<<name<<endl;
			cout<<setw(30)<<left<<"Year: "<<year<<endl;
			cout<<setw(30)<<left<<"Group: "<<group<<endl;
			cout<<setw(30)<<left<<"Amount: "<<amount<<endl;
		}		
};



class List{
	private:
		Album *begin;
	public:
		
		List(): begin(NULL){
		}
		
		void showAllList(){
			if(begin == NULL)
				cout<<"List is empty...";
			else{
				Album *finder = begin;
				while(finder != NULL){
					finder->showAll();
					finder = finder->next;
				}
			}	
		}
		void deleteById(){
			int uId;
			bool found = false;
			cout<<"Enter id: ";
			cin>>uId;
			Album *finder = begin;
				while(finder != NULL){
					if(finder->id == uId){
						found = true;
						if(finder->prev != NULL){
							finder->prev->next = finder->next;
						}
						else{
							begin = finder->next;
							begin->prev = NULL;
							break;
						}
						
						if(finder->next != NULL)
							finder->next->prev = finder->prev;	
						break;
					}
					cout<<"Searching...."<<endl;
					finder = finder->next;
				}
			if(!found)
				cout<<"Not found..."<<endl;
		}
		
		void findById(){
			int uId;
			bool found = false;
			cout<<"Enter id: ";
			cin>>uId;
			Album *finder = begin;
				while(finder != NULL){
					if(finder->id == uId){
						finder->showAll();
						found = true;
						break;
					}
					cout<<"Searching...."<<endl;
					finder = finder->next;
				}
			if(!found)
				cout<<"Not found..."<<endl;
		}
		
		void addAfterId(){
			int uId;
			bool found = false;
			cout<<"Enter id: ";
			cin>>uId;
			Album *finder = begin;
				while(finder != NULL){
					if(finder->id == uId){
						found = true;
						Album *temp = finder->next;
						finder->next = createAlbum();
						
						cout<<"1";
						finder->next->prev = finder;
						cout<<"2";
						if(temp != NULL){
							cout<<"3";
							finder->next->next = temp;
							cout<<"4";
							finder->next->next->prev = finder->next;	
							cout<<"5";
						}
						cout<<"6";
					}
					cout<<"Searching...."<<endl;
					finder = finder->next;
				}
			if(!found)
				cout<<"Id doesn`t exist..."<<endl;
		}
		
		void addToStartOfList(){
			
			if(begin == NULL){
				begin = createAlbum();
				cout<<"List empty: "<<begin->id<<endl;
			}
			else{
				Album *temp = begin;
				begin = createAlbum();
				begin->next = temp;
				begin->prev = NULL;
				begin->next->prev = begin;
			}
		}
		
		Album * createAlbum(){
			int yearA;
			string nameA;
			string groupA;
			int amountA;
			
			cout<<"Enter Year: ";
			cin>>yearA;
			cout<<"Enter nameA: ";
			cin>>nameA;
			cout<<"Enter group: ";
			cin>>groupA;
			cout<<"Enter amount: ";
			cin>>amountA;
			
			return new Album(yearA, nameA, groupA, amountA);
		}
		
		SoloAlbum * createSoloAlbum(){
			int yearA;
			string nameA;
			string singerA;
			int amountA;
			
			cout<<"Enter Year: ";
			cin>>yearA;
			cout<<"Enter nameA: ";
			cin>>nameA;
			cout<<"Enter singer: ";
			cin>>singerA;
			cout<<"Enter amount: ";
			cin>>amountA;
			
			return new SoloAlbum(yearA, nameA, singerA, amountA);
		}
		
		void addToEndOfList(){
			
			if(begin == NULL){
				begin = createAlbum();
			}
			else{
				Album *finder = begin;
				while(finder->next != NULL){
					cout<<"List not empty..."<<finder->next->id<<endl;
					finder = finder->next;
				}
				finder->next = createAlbum();
				finder->next->prev = finder;
			}
		}
		void readToFile(){
			ofstream fout; 
		    fout.open("example.txt");
		    fout.write((char*)this, sizeof(List));
		    fout.close();
		}
		
		void pushToListFromFile(){
			List file;
		    ifstream fin;
		    fin.open("example.txt");
			fin.read((char*)&file, sizeof(List));
			begin = file.begin;
			fin.close();
		}
		
		void clearList(){
			begin = NULL;
			cout<<"List was cleared";
		}
		
};



void showMenu(){
	List list;
	int choice;
	bool exit = false;
	do{
		cout<<endl<<"Menu"<<endl;
		cout<<"1. Add to end of List."<<endl;
		cout<<"2. Find by id."<<endl;
		cout<<"3. Delete from list."<<endl;
		cout<<"4. Show all list."<<endl;
		cout<<"5. Add to start of List."<<endl;
		cout<<"6. Add after id."<<endl;
		cout<<"7. Sort By Id."<<endl;
		cout<<"8. Write to file."<<endl;
		cout<<"9. Push list from file."<<endl;
		cout<<"10. Clear list."<<endl;
		cout<<"11. Exit."<<endl;
		cout<<"---------------------------"<<endl;
		cout<<"Select one of the options: ";
		cin>>choice;
		cout<<"---------------------------"<<endl;
		switch(choice){
			case 1:
				cout<<"1. Add Album."<<endl;
				cout<<"2. Add Solo Album."<<endl;
				cout<<"---------------------------"<<endl;
				cout<<"Select one of the options: ";
				cin>>choice;
				cout<<"---------------------------"<<endl;
				switch(choice){
					case(1):
						
				}
				
				list.addToEndOfList();
				break;
			case 2:
				list.findById();
				break;
			case 3:
				list.deleteById();
				break;
			case 4:
				list.showAllList();
				break;
			case 5:
				list.addToStartOfList();
				break;
			case 6:
				list.addAfterId();
				break;
			case 7:
				cout<<"Not working";
				break;
			case 8:
				list.readToFile();
				break;
			case 9:
				list.pushToListFromFile();
				break;
			case 10:
				list.clearList();
				break;
			case 11:
				cout<<"Exit";
				exit = true;
				break;
			default:
				cout<<"Try again;";
		}
	}
	while(!exit);	
}
 
int main(){
	
	showMenu();
	
	return 0;
}
