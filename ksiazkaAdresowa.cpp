#include <iostream>
#include <cstdlib> //Windows <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

struct User
{
        int id;
        string username, password;
};

struct Contact
{
	int contactId, userId;
	string firstName, surname, phoneNumber, email, address;
};

string readData()
{
        string data = "";
        getline(cin, data);
        return data;
}

char readSign()
{
        string data = "";
        char sign = {0};

        while (true)
        {
                getline(cin, data);

                if (data.length() == 1 )
                {
                        sign = data[0];
                        break;
                }
                cout << "To nie jest pojedynczy znak. Wpisz ponownie. " << endl;
        }
        return sign;
}

void loadUsersFromFile (vector <User> &userList)
{
        string data = "";
        int position = 1;
        User users;

        fstream plik;
        plik.open("Uzytkownicy.txt", ios::in);

        if (plik.good() == true)
        {
                while (getline(plik, data, '|'))
                {
                        switch (position)
                        {
                        case 1:
                                users.id = atoi(data.c_str());
                                break;
                        case 2:
                                users.username = data;
                                break;
                        case 3:
                                users.password = data;
                                break;
                        }
                        if (position >= 3)
                        {
                                userList.push_back(users);
                                position = 1;
                        }
                        else
                        {
                                position++;
                        }
                }
                plik.close();
        }
	else
	{
		cout << "Nie uzyskano dostepu do pliku." << endl;
	}
        return;
}

void registration (vector <User> &userList)
{
        string username, password;
	int i = 0, numbersUsers = userList.size(), counter = 0;
	User users;

        cout << "Podaj login: ";
        username = readData();
        while(i < numbersUsers)
        {
                if (userList[i].username == username)
                {
                        cout << "Użytkownik o podanym loginie istnieje. Wpisz inny login: ";
                        username = readData();
                        i = 0;
                }
                else
                i++;
        }
        cout << "Podaj haslo: ";
        password = readData();

        if (userList.size() == 0)
        {
                counter = 1;
        }
        else
        {
                counter = userList[userList.size()-1].id+1;
        }


	users.id = counter;
        users.username = username;
        users.password = password;
	userList.push_back(users);

        fstream plik;
        plik.open("Uzytkownicy.txt", ios::out | ios::app);

        if (plik.good() == true)
        {
                plik << users.id << '|';
                plik << users.username << '|';
                plik << users.password << '|' << endl;
                plik.close();
        }
        else
        {
                cout << "Nie udalo się otworzyc pliku i zapisac do niego danych. " ;
                return;
        }
        cout << "Uzytkownik zostal dodany. " << endl;
        sleep(2);
        return;
}

void saveAllContacts (vector <Contact> &addressBook)
{
	fstream plik;
	plik.open("Adresaci.txt", ios::trunc | ios::out);
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą? Do zmiany...
	if (plik.good() == true)
        {
		for( vector<Contact>::iterator itr = addressBook.begin(); itr != addressBook.end(); ++itr)
		{
			plik << itr-> contactId << '|';
			plik << itr-> userId << '|';
			plik << itr-> firstName << '|';
                        plik << itr-> surname << '|';
			plik << itr-> phoneNumber << '|';
			plik << itr-> email << '|';
			plik << itr-> address << '|' << endl;
		}
		plik.close();
		return;
	}
	else
	{
		cout << "Nie udalo się otworzyc pliku i edytowac danych. " << endl;
		return;
	}
}

void addNewContact (vector <Contact> &addressBook,int lastContactId?)
{
	string auxiliaryFirstName, auxiliarySurname;
	Contact contacts;
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą?
	cout << "Podaj imie: ";
	auxiliaryFirstName = readData();
	cout << "Podaj nazwisko: ";
	auxiliarySurname = readData();

	int i = 0;
	while (i < addressBook.size())
	{
		if ((addressBook[i].firstName == auxiliaryFirstName) && (addressBook[i].surname == auxiliarySurname))
		{
			cout << "Kontakt o podanym imieniu i nazwisku juz istnieje. Prosze o podanie innego imienia i nazwiska do kontaktu.";
			cout << "Podaj imie: ";
			auxiliaryFirstName = readData();
			cout << "Podaj nazwisko: ";
			auxiliarySurname = readData(); i=0;
		}
		else
		{
			i++;
		}
	}

	int counter;
	if (addressBook.size() == 0)
	{
		counter = 1;
	}
	else
	{
		counter = addressBook[addressBook.size()-1].id+1;
	}
//zapis na końcu pliku. Id się nie zgadza to z vectora względem tego w pliku.
	contacts.contactId = counter;//Jak znalezc id ostatniego uzytkownika z pliku i znalezc jego id??
	contacts.userId = addressBook.userId;
	contacts.firstName = auxiliaryFirstName;
	contacts.surname = auxiliarySurname;
	cout << "Podaj numer telefonu: " ;
	contacts.phoneNumber = readData();
	cout << "Podaj adres e-mail: " ;
	contacts.email = readData();
	cout << "Podaj adres zamieszkania: " ;
	contacts.address = readData();
	addressBook.push_back(contacts);

	fstream plik;
	plik.open("Adresaci.txt", ios::out | ios::app);

	if (plik.good() == true)
	{
		plik << addressBook[addressBook.size()].contactId << '|';
                plik << addressBook[addressBook.size()].userId << '|';
		plik << addressBook[addressBook.size()].firstName << '|';
		plik << addressBook[addressBook.size()].surname << '|';
		plik << addressBook[addressBook.size()].phoneNumber << '|';
		plik << addressBook[addressBook.size()].email << '|';
		plik << addressBook[addressBook.size()].address << '|' << endl;
		plik.close();
	}
	else
	{
		cout << "Nie udalo się otworzyc pliku i zapisac do niego danych. " ;
		return;
	}
	cout << "Kontakt zostal dodany. " << endl;
	sleep(2);
	return;
}

int transferLastContactId (int lastContactId)
{
	return lastContactId;//do przekazania w inny sposób;
}

void loadContactsFromFile (vector <Contact> &addressBook, int loggedInUserId)
{
	string data;
	int position = 1, lastContactId = 0;
	Contact contacts;

	fstream plik;
	plik.open("Adresaci.txt", ios::in);

	if (plik.good() == true)
	{
		while (getline(plik, data, '|'))
		{
			switch (position)
			{
			case 1:
				contacts.contactId = atoi(data.c_str());
				break;
			case 2:
                                contacts.userId = atoi(data.c_str());
                                break;
			case 3:
				contacts.firstName = data;
				break;
			case 4:
				contacts.surname = data;
				break;
			case 5:
				contacts.phoneNumber = data;
				break;
			case 6:
				contacts.email = data;
				break;
			case 7:
				contacts.address = data;
				break;
			}
			if (position >= 7)
			{
				if(contacts.userId == loggedInUserId)
				{
					addressBook.push_back(contacts);
					lastContactId = contacts.contactId;
				}
				position = 1;
			}
			else
			{
				position++;
			}
		}
		plik.close();
	}
	else
	{
		cout << "Nie uzyskano dostepu do pliku." << endl;
	}
	transferLastContactId (lastContactId);
	return;
}

void displayAllContacts (vector <Contact> &addressBook)
{
	for (int i = 0; i < addressBook.size(); i++)
	{
		cout << endl;
		cout << "ID adresata: " << addressBook[i].contactId << endl;
		cout << "ID uzytkownika: " << addressBook[i].userId << endl;
		cout << addressBook[i].firstName << " " << addressBook[i].surname << endl;
		cout << "telefon: " << addressBook[i].phoneNumber << endl;
		cout << "email: " << addressBook[i].email << endl;
		cout << "adres: " << addressBook[i].address << endl;
		cout << endl;
	}
		cout << "Nacisnij enter, aby przejsc do kolejnego wyswietlenia." << endl;
		getchar(); //Windows system("pause");
}

void searchByFirstName (vector <Contact> &addressBook)
{
	string auxiliaryFirstName;

	cout << "Podaj imie, ktore chcialbys wyszukac w kontaktach: " << endl;
	auxiliaryFirstName = readData();

	for (int i = 0; i < addressBook.size(); i++ )
	{
		if (addressBook[i].firstName == auxiliaryFirstName)
		{
			cout << endl;
			cout << "ID adresata: " << addressBook[i].contactId << endl;
			cout << "ID uzytkownika: " << addressBook[i].userId << endl;
			cout << addressBook[i].firstName << " " << addressBook[i].surname << endl;
			cout << "telefon: " << addressBook[i].phoneNumber << endl;
			cout << "email: " << addressBook[i].email << endl;
			cout << "adres: " << addressBook[i].address << endl;
			cout << endl;
		}
	}
	cout << "Nacisnij enter, aby przejsc do kolejnego wyswietlenia." << endl;
	getchar(); //Windows system("pause"), albo sleep(10);
}

void searchBySurname (vector <Contact> &addressBook)
{
        string auxiliarySurname;

        cout << "Podaj nazwisko, ktore chcialbys wyszukac w kontaktach: " << endl;
        auxiliarySurname = readData();

        for (int i = 0; i < addressBook.size(); i++ )
        {
                if (addressBook[i].surname == auxiliarySurname)
                {
                    	cout << "ID adresata: " << addressBook[i].contactId << endl;
			cout << "ID uzytkownika: " << addressBook[i].userId << endl;
                        cout << addressBook[i].firstName << " " << addressBook[i].surname << endl;
                        cout << "telefon: " << addressBook[i].phoneNumber << endl;
                        cout << "email: " << addressBook[i].email << endl;
                        cout << "adres: " << addressBook[i].address << endl;
			cout << endl;
                }
        }
	cout << "Nacisnij enter, aby przejsc do kolejnego wyswietlenia."<<endl;
	getchar();
}

void deleteContact (vector <Contact> &addressBook)
{
	char choice;
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą?
	while(true)
        {
                cout << "Podaj id uzytkownika, ktorego dane chcesz edytowac. W celu wyswietlenia wszystkich adresatow nacisnij d. W celu wyjscia do wczesnijeszego kokpitu nacisnij e." << endl;
                choice = readSign();

                if (choice == 'd')
                {
                        displayAllContacts (addressBook);
                }
		else if (choice == 'e')
		{
			return;
		}
                else if ((int (choice-48) > 0) && (int (choice-48) <= addressBook.size()))
             	{
                        int idToEdit = choice-48; int i = 0;
			vector<Contact> ::iterator itr = addressBook.begin();
			for (itr; itr != addressBook.end(); ++itr)
			{
				if (idToEdit == itr-> id)
				{
					break;
				}
			}
			cout << "Czy na pewno chcesz usunac uzytkownika? Jesli tak wciśnij t. "<<endl;
			char choice2 = readSign();
			if ( choice2 == 't')
			{
				addressBook.erase(itr);
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą?
				saveAllContacts(addressBook);
				cout << "Kontakt zostal usuniety. " << endl;
				sleep (1);
				return;
			}
			else
			{
				cout<< "Zdecydowales sie nie usuwac danych."<<endl;
				sleep(2);
				return;
			}
                }
                else
                {
			cout<< "Blad wprowadzanej danej. Wybierz numer id uzytkownika do usuniecia lub nacisnij w jesli chcesz wyswietlic wszystkie kontakty."<<endl;

                }
        }
return;
}

void editContact (vector <Contact> &addressBook)
{
	char choice, choice2; int idToEdit, i; 
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą?

	system("clear");//Windows "cls";
	while(true)
	{
		cout << "Podaj id uzytkownika, ktorego dane chcesz edytowac. W celu wyswietlenia wszystkich adresatow nacisnij d. W celu wyjscia do wczesniejszego kokpitu nacisnij e." << endl;
		choice = readSign();

		if (choice == 'd')
		{
			displayAllContacts (addressBook);
		}
		else if (choice == 'e')
		{
			return;
		}
		else if ((int (choice-48) > 0) && (int (choice-48) <= addressBook.size()))
		{
			idToEdit = choice-48;

			for ( i = 0; i <= addressBook.size(); i++ )
			{
				if( idToEdit == addressBook[i].id )
				{
					break;
				}
			}

			system("clear");//Windows "cls";

                	cout << "1 - imie" << endl;
                	cout << "2 - nazwisko" << endl;
                	cout << "3 - numer telefonu" << endl;
                	cout << "4 - email" << endl;
                	cout << "5 - adres" << endl;
                	cout << "6 - powrot do menu glownego" << endl;

			cout << "Podaj numer zmiennej, ktora chcesz edytowac. "<<endl;
			choice2 = readSign();

			if( (int(choice2-48) > 0) && (int(choice2-48) < 7) )
			{
				switch (choice2)
				{
				case '1':
					cout << "Wprowadz nowe imie: " << endl;
					addressBook[i].firstName = readData();
                			break;
                		case '2':
					cout << "Wprowadz nowe nazwisko: " << endl;
                                	addressBook[i].surname = readData();
                			break;
                		case '3':
                        		cout << "Wprowadz nowy numer telefonu: " << endl;
                                	addressBook[i].phoneNumber = readData();
					break;
                		case '4':
                        		cout << "Wprowadz nowy email: " << endl;
                                	addressBook[i].email = readData();
                			break;
                		case '5':
                        		cout << "Wprowadz nowy adres: " << endl;
                                	addressBook[i].address = readData();
					break;
                		case '6':
					cout << "Powrot do wczesniejszego menu. " << endl;
					exit(0);
					break;
				}
//zapis z pliku na zasadzie dodania wszystkich kontaktów dla użytkownika o danym id, a co z resztą?
				saveAllContacts(addressBook);
 				cout << "Kontakt zostal edytowany. " << endl;
 				sleep(2);
 				return;

                	}
			else
			{
				cout << "Blad wprowadzanej danej do edycji." << endl;
			}
		}
		else
		{			cout<< "Blad wprowadzanej danej. Wybierz numer id uzytkownika do edycji lub nacisnij w jesli chcesz wyswietlic wszystkich uzytkownikow."<<endl;

		}
	}
return;
}

void changePassword (vector <User> &userList, vector <Contact> &addressBook)
{
        string password = "";

        cout<< "Podaj nowe haslo: ";
        password = readData();

        for (int i = 0; i < usersList.size(); i++)
        {
                if (userList[i].id == addressBook.userId)
                {
                        userList[i].password = password;

			fstream plik;
        		plik.open("Uzytkownicy.txt", ios::trunc | ios::out);

        		if (plik.good() == true)
        		{
                		for(vector<User>::iterator itr = userList.begin(); itr != userList.end(); ++itr)
                		{
                        		plik << itr-> id << '|';
                        		plik << itr-> username << '|';
                        		plik << itr-> password << '|' << endl;
                		}
                		plik.close();
				cout<< "Hasło zostało zmienione" <<endl;
                		sleep(2);
                		return;
        		}
        		else
        		{
                		cout << "Nie udalo się otworzyc pliku i edytowac danych."<<endl;
				sleep(2);
                		return;
        		}

                }
        }
}

void runDashbord2 (vector <User> userList, int loggedInUserId)
{
	char choice;
        vector <Contacts> addressBook;

        loadContactsFromFile (addressBook, loggedInUserId);

        while(true)
        {

                system("clear");//Windows "cls";
                cout << " KSIAZKA ADRESOWA " << endl;
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmiana hasła" <<endl;
                cout << "8. Wylogowanie "<<endl;
                cout << "Dokonaj wyboru wprowadzajac odpowiedni numer:";

                choice = readSign();
                switch ( choice )
                {
                case '1':
                        addNewContact (addressBook);
                        break;
                case '2':
                        searchByFirstName (addressBook);
                        break;
                case '3':
                        searchBySurname (addressBook);
                        break;
		case '4':
                        displayAllContacts (addressBook);
                        break;
                case '5':
                        deleteContact (addressBook);
                        break;
                case '6':
                        editContact (addressBook);
                        break;
                case '7':
                        changePassword (userList, addressBook);
                        break;
                case '8':
                        exit (0);
                        break;
                default:
                        cout << "Niepoprawny wybór." << endl;
                        break;
                }

        }
}

void logIn (vector <User> &userList)
{
        string username = "", password = "";
        int = 0, loggedInUserId = 0;

        cout << "Podaj login: ";
        username = readData();

        while (i < usersList.size())
        {
                if (usersList[i].username == username)
                {
                        for(int attempt = 0; attempt < 3; attempt++)
                        {
                                cout << "Podaj hasło. Pozostało prób " << 3-attempt<< ": ";
                                password = readData();
                                if (usersList[i].password == password)
                                {
                                        cout << "Zalogowałeś się." << endl;
					loggedInUserId = userList[i].id;
                                        sleep(1);
					runDashbord2 (userList, loggedInUserId);
                                        return;
                                }
                        }
                        cout << "Podałeś 3 razy błędne hasło. Poczekaj 3 sekundy przed kolejną próbą." << endl;
                        sleep(3);
                        return;
                }
                i++;
        }
        cout << "Nie ma użytkownika z takim loginem." << endl;
        sleep(3);
        return;
}

int main()
{
	char choice;
	vector <User> userList;

	loadUsersFromFile (userList);

	while (true)
	{
                        system("clear");//system("cls") na Windowsie;
                        cout << " KSIAZKA ADRESOWA " << endl;
			cout << "1. Rejestracja" <<endl;
                        cout << "2. Logownie "<<endl;
                        cout << "3. Zakończ program "<<endl;
			cout << "Dokonaj wyboru wprowadzajac odpowiedni numer:";
                        choice = readSign();

                        switch (choice)
                        {
			case '1':
				registration (userList);
				break;
                        case '2':
                                logIn (userList);
				break;
                        case '3':
                                exit(0);
				break;
			default:
                        	cout << "Niepoprawny wybór." << endl;
                        	break;
                        }
	}
return 0;
}
