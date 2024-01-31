#include <iostream>
#include <string>

using namespace std;


class Guest
{
	string fullname;
	string connected_date; //tarix saat

public:
	Guest(string fullname, string date)
	{
		this->setFullName(fullname);
		this->setDate(date);
	}

	// Copy Constructor
	Guest(const Guest& guest)
	{
		this->setFullName(guest.getFullName());
		this->setDate(guest.getDate());
	}

	void setFullName(string fullname)
	{
		if (fullname.length() > 3)
			this->fullname = fullname;
		else
			throw exception("Ad min 4 herf olmalidir.");
	}

	void setDate(string date)
	{
		if (date.length() > 4)
			this->connected_date = date;
		else
			throw exception("Tarix min 5 herf olmalidir.");
	}

	void show_info()
	{
		cout << "Guest Full Name : " << fullname << endl;
		cout << "Guest Connected Date : " << connected_date << endl << endl;
	}

	string getFullName() const { return this->fullname; }
	string getDate() const { return this->connected_date; }
};

class Admin
{
	string username;
	string password;

public:

	Admin(string username, string password)
	{
		this->SetUsername(username);
		this->SetPassword(password);
	}

	// Copy Constructor
	Admin(const Admin& admin)
	{
		this->SetUsername(admin.GetUsername());
		this->SetPassword(admin.GetPassword());
	}

	void SetUsername(string username)
	{
		if (username.length() > 4)
			this->username = username;
		else
			throw exception("Username min 4 herf olmalidir.");
	}

	void SetPassword(string password)
	{
		if (password.length() > 5)
			this->password = password;
		else
			throw exception("Password min 6 herf olmalidir.");
	}

	string GetUsername() const { return this->username; }
	string GetPassword() const { return this->password; }

};

class Product
{
	static int _id;
	int id; //avtomatik
	string name = "";
	string description = "";
	double price = 0.0;
	double discount = 0.0;
	int quantity = 0;
	double tax = 0.0; //vergi faizi

public:

	Product() { id = ++_id; }

	Product(string name, double price, int quantity = 1)
		: Product()
	{
		this->setName(name);
		this->setPrice(price);
		this->setQuantity(quantity);
	}

	Product(string name, string description, double price, double discount, double tax, int quantity = 1)
		: Product(name, price, quantity)
	{
		this->setDescription(description);
		this->setDiscount(discount);
		this->setTax(tax);
	}

	// Copy constructor
	Product(const Product& product)
		: Product(product.getName(), product.getDescription(), product.getPrice(), product.getDiscount(), product.getTax(), product.getQuantity())
	{}

	void showSpecs_short()
	{
		cout << "\n\tProduct Id -> " << this->id << endl;
		cout << "\tProduct Name -> " << this->name << endl;
		cout << "\tProduct Price -> " << this->price << " AZN." << endl;
	}
	void showSpecs_long()
	{
		this->showSpecs_short();

		cout << "\tProduct Description -> " << this->description << endl;
		cout << "\tProduct Discount -> " << this->discount << " %." << endl;
		cout << "\tProduct Quantity -> " << this->quantity << endl;
		cout << "\tProduct Tax -> " << this->tax << " %." << endl;
	}

	/* Set and Get Methods */
	void setName(string name)
	{
		if (name.length() > 4)
			this->name = name;
		else
			throw exception("Ad min 5 herf olmalidir.");
	}

	void setDescription(string description)
	{
		if (description.length() > 3)
			this->description = description;
		else
			throw exception("Achiqlama min 4 herf olmalidir.");
	}

	void setPrice(double price)
	{
		if (price >= 0.0)
			this->price = price;
		else
			throw exception("Qiymet 0-dan Boyuk olmalidir.");
	}

	void setDiscount(double discount)
	{
		if (discount >= 0.0 && discount <= 100.0)
			this->discount = discount;
		else
			throw exception("Endirim Faizi 0 ile 100 arasinda olmalidir.");
	}

	void setTax(double tax)
	{
		if (tax >= 0.0 && tax <= 100.0)
			this->tax = tax;
		else
			throw exception("Vergi Faizi 0 ile 100 arasinda olmalidir.");
	}

	void setQuantity(int quantity)
	{
		if (quantity >= 0)
			this->quantity = quantity;
		else
			throw exception("Malin Sayi 0 ve ya 0-dan Boyuk olmalidir.");
	}

	double GetFinalPrice()const { return ((this->price - (this->price * this->discount / 100)) * (this->tax / 100)); }

	string getName()const { return this->name; }
	string getDescription()const { return this->description; }
	double getPrice()const { return this->price; }
	double getDiscount()const { return this->discount; }
	double getTax()const { return this->tax; }
	int getId()const { return this->id; }
	int getQuantity()const { return this->quantity; }
};

int Product::_id = 0;


template<typename T> class DbSet
{
	T** items = nullptr;
	int count = 0;

public:

	void add(const T* item)
	{
		if (items == nullptr)
		{
			items = new T * [++count];
			items[0] = new T(*item);
		}
		else
		{
			T** nItems = new T * [count + 1];
			for (size_t i = 0; i < count; i++)
				nItems[i] = items[i];

			nItems[count] = new T(*item);
			delete[] items;
			items = nItems;
			count++;
		}
	}

	bool checkId(const int& id)
	{
		for (size_t i = 0; i < count; i++)
			if (items[i]->getId() == id)
				return true;
		return false;
	}

	void deleteByid(const int& id)
	{
		if (checkId(id))
		{
			T** nItems = new T * [count - 1];
			size_t index = 0;

			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() != id)
					nItems[index++] = items[i];
				else
					delete items[i];
			}
			delete[] items;
			items = nItems;
			count--;
		}
	}

	void DeleteAllItems()
	{
		if (items != nullptr)
		{
			for (size_t i = 0; i < count; i++)
			{
				if (items[i] != nullptr)
					delete items[i];
			}
			delete[] items;
			items = nullptr;
			count = 0;
		}
	}

	T* getItem(const int& id)
	{
		if (checkId(id))
		{
			for (size_t i = 0; i < count; i++)
				if (items[i]->getId() == id)
					return items[i];
		}
		return nullptr;
	}

	size_t getCount() const { return count; }
	T** getItems() const { return items; }

	~DbSet()
	{
		if (items != nullptr)
		{
			for (size_t i = 0; i < count; i++)
			{
				if (items[i] != nullptr)
					delete items[i];
			}
			delete[] items;
			items = nullptr;
			count = 0;
		}
	}
};


class Database
{
public:

	DbSet<Product>products;
	DbSet<Admin>admins;
	DbSet<Guest>guest;

	bool checkAdmin(string username)
	{
		auto Items = admins.getItems();
		auto Count = admins.getCount();

		for (size_t i = 0; i < Count; i++)
		{
			if (Items[i]->GetUsername() == username)
				return true;
		}
		return false;
	}
	bool checkGuest(string fullname)
	{
		auto Guests = guest.getItems();
		auto Count = guest.getCount();

		for (size_t i = 0; i < Count; i++)
		{
			if (Guests[i]->getFullName() == fullname)
				return true;
		}
		return false;
	}

	bool adminLogin(string username, string password)
	{
		auto Items = admins.getItems();
		auto Count = admins.getCount();

		for (size_t i = 0; i < Count; i++)
		{
			if (Items[i]->GetUsername() == username && Items[i]->GetPassword() == password)
				return true;
		}
		return false;
	}
};


void start() {

	Database db;

	Admin* admin1 = new Admin("admin12", "admin123");
	db.admins.add(admin1);

	Guest* guest1 = new Guest("guest12", "12.01.2024 21:57");
	db.guest.add(guest1);

	Product* product1 = new Product("Ferrari-- 1", "Fastest Super Car1", 15000, 0.2, 18, 200);
	Product* product2 = new Product("Ferrari-- 2", "Fastest Super Car2", 125000, 0.3, 18, 300);
	Product* product3 = new Product("Ferrari-- 3", "Fastest Super Car3", 5000, 0.4, 18, 400);
	Product* product4 = new Product("Ferrari-- 4", "Fastest Super Car4", 75000, 0.5, 18, 500);
	Product* product5 = new Product("Ferrari-- 5", "Fastest Super Car5", 1000, 0.1, 11, 100);
	db.products.add(product1);
	db.products.add(product2);
	db.products.add(product3);
	db.products.add(product4);
	db.products.add(product5);


	// ////////////////////////// ////////////////////////////// //////////////////////////

	string menuOne = R"(
				[1] => As Gusest
				[2] => As Admin
				[0] => Exit
		)";

	string menuAdmin = R"(
				[1] => Add Product
				[2] => Delete Product
				[3] => Show All Products
				[4] => Show All Guests
				[5] => Update Product
				[6] => Delete All Products
				[7] => Delete All Guests
				[8] => Show Total price by Id
				[9] => Show Product Tax by Id
				[0] => Exit
		)";


	while (true)
	{
		system("cls");
		cout << menuOne << endl;
		cout << "Menudan secim edin: ";

		int select;
		cin >> select;
		cin.ignore();
		if (select == 1)
		{
			string Fullname;
			cout << "\nEnter Full Name : ";
			getline(cin, Fullname);

			if (db.checkGuest(Fullname))
			{
				while (true)
				{
					system("cls");

					auto _items = db.products.getItems();
					auto _count = db.products.getCount();

					for (size_t p = 0; p < _count; p++)
					{
						_items[p]->showSpecs_short();
						cout << "\n---------------------------------\n";
					}

					cout << "\n\n\t[1] => Buy Product with Id.";
					cout << "\n\t[2] => Show Full Product Specs with Id.";
					cout << "\n\t[3] => Exit\n";

					short guestChoice;
					cout << "\n\nEnter Choice : ";
					cin >> guestChoice;

					if (guestChoice == 1)
					{
					buying:
						cin.ignore();

						size_t g_id, amount = 0;
						cout << "\nEnter the Product id : ";
						cin >> g_id;

						cout << "\nHow many product do you want to buy? \n";

						int g_count;
						cin >> g_count;

						for (size_t p = 0; p < _count; p++)
						{
							if (_items[p]->getId() == g_id)
							{
								amount = _items[p]->getQuantity();

								if (amount >= g_count)
								{
									cout << "\nDo you want to buy this product for " << g_count * _items[p]->GetFinalPrice() << " AZN ?\n";
									cout << "1 - yes / 0 - no\n Sechim : ";
									cin >> g_id;

									if (g_id)
									{
										cout << "\nShopping Succesfully Completed.\n";
										_items[p]->setQuantity(amount - g_count);
										cout << endl; system("pause");
									}
								}
								else
								{
									cout << "\nThere is not enough product in the Depo. Total Product Quantity : " << amount << "\n";
									cout << endl; system("pause");
								}
								break;
							}
						}
						cout << "\nNo products were found for this id.\n";
						cout << endl; system("pause");
					}
					else if (guestChoice == 3)
					{
						break;
					}
					else if (guestChoice == 2)
					{
						cin.ignore();
						size_t g_id, amount = 0;
						cout << "\nEnter the Product id : ";
						cin >> g_id;

						for (size_t p = 0; p < _count; p++)
						{
							if (_items[p]->getId() == g_id)
							{
								amount = _items[p]->getQuantity();
								_items[p]->showSpecs_long();
							}
						}

						cout << "\nAre you sure to buy with " << amount << " amounts ? \n\t1 = yes / 0 = no.\nSechim : ";
						cin >> g_id;

						if (g_id) goto buying;
						else break;
					}
					else {
						cout << "\nMenudan Duzgun Sechim Edin.";
						continue;
					}
				}
			}
			else
			{
				cout << "\nGuest Not found." << endl;
				cout << endl; system("pause");
			}
		}
		else if (select == 2)
		{
			cin.ignore();
			string username, password;
			cout << "\nUsername : ";
			getline(cin, username);
			cout << "\nPassword : ";
			getline(cin, password);

			if (db.checkAdmin(username))
			{
				if (db.adminLogin(username, password))
				{
					int a_sechim;
					while (true)
					{
						system("cls");
						cout << menuAdmin << endl;
						cout << "\nMenudan Sechim Edin : "; cin >> a_sechim;

						if (a_sechim == 1)
						{
							cin.ignore();
							string name; string description; double price; double discount; double tax; int quantity;

							cout << "\nEnter The Product Name : "; getline(cin, name);
							cout << "\nEnter The Product Description : "; getline(cin, description);
							cout << "\nEnter The Product Price : "; cin >> price;
							cout << "\nEnter The Product Discount : "; cin >> discount;
							cout << "\nEnter The Product Tax : "; cin >> tax;
							cout << "\nEnter The Product Quantity : "; cin >> quantity;
							cin.ignore();
							Product* newProduct = new Product(name, description, price, discount, tax, quantity);

							db.products.add(newProduct);
							cout << "\nProduct Succesfully Added.\n";
							cout << endl; system("pause");
						}
						else if (a_sechim == 2)
						{
							cin.ignore();
							size_t delete_id;
							cout << "\nEnter the Product id : "; cin >> delete_id;

							if (db.products.checkId(delete_id))
							{
								db.products.deleteByid(delete_id);
								cout << "\nProduct Succesfully Deleted.\n";
								cout << endl; system("pause");
							}
							else {
								cout << "\nNo products were found for this id.\n";
								cout << endl; system("pause");
							}
						}
						else if (a_sechim == 3)
						{
							cout << "\t>>>>  All Products  <<<<\n\n";

							auto _products = db.products.getItems();
							auto _count = db.products.getCount();

							for (size_t pr = 0; pr < _count; pr++)
								_products[pr]->showSpecs_long();
							cout << endl; system("pause");
						}
						else if (a_sechim == 4)
						{
							cout << "\t>>>>  All Guests  <<<<\n\n";

							auto _guests = db.guest.getItems();
							auto _count = db.guest.getCount();

							for (size_t gu = 0; gu < _count; gu++)
								_guests[gu]->show_info();
							cout << endl; system("pause");
						}
						else if (a_sechim == 5)
						{
							cin.ignore();
							size_t up_id;
							cout << "\nEnter the Product id : "; cin >> up_id;

							if (db.products.checkId(up_id))
							{
								string menuChange = R"(
					[1] => Change Name
					[2] => Change Description
					[3] => Change Price
					[4] => Change Discount
					[5] => Change Tax
					[6] => Change Quantity
					[0] => Exit
					)";
								auto up_product = db.products.getItem(up_id);


								int sechim1;
								while (true)
								{
									system("cls");
									cin.ignore();
									up_product->showSpecs_long();
									cout << endl << menuChange << endl;
									cout << "\nMenudan Sechim Edin : "; cin >> sechim1;

									if (sechim1 == 1)
									{
										string name;
										cout << "\nEnter the New Name : ";
										getline(cin, name);

										up_product->setName(name);
									}
									else if (sechim1 == 2)
									{
										string description;
										cout << "\nEnter the New Description : ";
										getline(cin, description);

										up_product->setDescription(description);
									}
									else if (sechim1 == 3)
									{
										double price;

										cout << "\nEnter the New Price : "; cin >> price;

										up_product->setPrice(price);
									}
									else if (sechim1 == 4)
									{
										double Discount;

										cout << "\nEnter the New Discount : "; cin >> Discount;

										up_product->setDiscount(Discount);
									}
									else if (sechim1 == 5)
									{
										double Tax;

										cout << "\nEnter the New Tax : "; cin >> Tax;

										up_product->setTax(Tax);
									}
									else if (sechim1 == 6)
									{
										double Quantity;

										cout << "\nEnter the New Tax : "; cin >> Quantity;

										up_product->setQuantity(Quantity);
									}
									else if (sechim1 == 0)
									{
										break;
									}
									else {
										cout << "\nMenudan Duzgun Sechim Edin.\n";
										cout << endl; system("pause");
									}
								}
							}
							else {
								cout << "\nNo products were found for this id.\n";
								cout << endl; system("pause");
							}
						}
						else if (a_sechim == 6)
						{
							db.products.DeleteAllItems();
							cout << "\nAll Products Succesfully Deleted.\n";
							cout << endl; system("pause");
						}
						else if (a_sechim == 7)
						{
							db.guest.DeleteAllItems();
							cout << "\nAll Guests Succesfully Deleted.\n";
							cout << endl; system("pause");
						}
						else if (a_sechim == 8)
						{
							size_t show_id;
							cout << "\nEnter the Product id : "; cin >> show_id;

							if (db.products.checkId(show_id))
							{
								cout << "\nTotal Price : " << (db.products.getItem(show_id)->GetFinalPrice()) << " AZN.";
								cout << endl; system("pause");
							}
							else {
								cout << "\nNo products were found for this id.\n";
								cout << endl; system("pause");
							}
						}
						else if (a_sechim == 9)
						{
							size_t show_id;
							cout << "\nEnter the Product id : "; cin >> show_id;

							if (db.products.checkId(show_id))
							{
								cout << "\nProduct Tax : " << (db.products.getItem(show_id)->getTax()) << " AZN.";
								cout << endl; system("pause");
							}
							else {
								cout << "\nNo products were found for this id.\n";
								cout << endl; system("pause");
							}
						}
						else if (a_sechim == 0)
						{
							break;
						}
						else {
							cout << "\nMenudan Duzgun Sechim Edin.\n";
							cout << endl; system("pause");
						}
					}
				}
				else
				{
					throw exception("\nPassword is incorrect. Login prosses is not Accessible.\n");
					cout << endl; system("pause");
				}
			}
			else
			{
				throw exception("\nBele Admin Tapilmadi.\n");
				cout << endl; system("pause");
			}
		}
		else if (select == 0)
		{
			cout << "\n\nGood Bye.\n\n\n";

			break;
		}
		else
		{
			throw exception("\nBirinci Menudan Duzgun secim edilmedi.\n");
			cout << endl; system("pause");
		}
	}
	delete admin1;
	delete guest1;
	delete product1;
	delete product2;
	delete product3;
	delete product4;
	delete product5;
}


void main()
{
	while (true)
	{
		try
		{
			start();
			break;
		}
		catch (exception& ex)
		{
			cout << endl << ex.what() << endl;
			cout << endl; system("pause");
		}
	}
	cout << endl; system("pause");
}