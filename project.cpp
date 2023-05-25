#include <iostream>
#include <fstream>
#include <typeinfo>
#include<cstring>
#include <process.h>
using namespace std;
enum gtype {tmember,ttrainer,null};
class Gym
{
	protected:
		char pass[20];
		int n; //Total number of entities
	public:
		char name[30],id[20];
		virtual void getdata()
		{
			cin.ignore();
			cout<<"Enter name: ";cin.clear();
			cin.get(name,19);cin.clear();
		}
		virtual void putdata()
		{
			cout<<"Name: "<<name<<endl;	
			cout<<"Email ID: "<<id<<endl;
		}
		void setpass(char pass[20])
			{strcpy(this->pass,pass);}
		gtype gettype();
		void display_trainer();	
		void write(char );
		void read();
		int compare(char id[20]);
		gtype login(char id[20],char pass[20]);
		void delete_acc(char id[20],char ch);
};
class Trainer:public Gym
{
	protected:
		int age;char gender;char contact[15];char disciples[10][20];double charges,rating;int tr;
	public:
		int x[2];
		Trainer(){}
		Trainer(char email[20])
		{
			string test;
			int flag=0;
			ifstream inf("Trainer.Data",ios::binary);
			while(true)
			{
				if(!inf)
					break;
				inf.read((char*)this,sizeof(*this));
				test=this->id;
				if(test==email)
					{flag=1;break;}	
			}
			inf.close();
			if(flag==0)
			{cout<<"Record not found\n";exit(1);}
		}
		double getcharge()
		{return charges;}
		void setcharge(double charges)
			{this->charges=charges;}
		void setcontact(char contact[15])
		{strcpy(this->contact,contact);}	
		virtual void getdata()
		{
			Gym::getdata();
			int flag=1;
			while (flag==1)
			{
				cout<<"Enter Email id:          [ For e.g >>>> t_xyz]"<<endl;
				cin.clear();
				cin>>id;
				cout<<"Enter Password:";cin>>pass;
				flag=compare(id);
				if(flag==1)
					cout<<"This email id is already taken!!!\n\n.Enter again\n";
			}
			rating=0;tr=0;
			cout<<"Enter age: ";cin>>age;
			cout<<"Enter contact number: ";cin>>contact;
			cout<<"Enter gender(M/F): ",cin>>gender;
			cout<<"Enter your monthly charges: ";cin>>charges;
			cout<<"Please enter maximum number of Members you can train within a month:";cin>>x[1];x[0]=0;
			for(int i=0;i<x[1];i++)
			{
				strcpy(disciples[i],"--");
			}
		}
		virtual void putdata()
		{
			Gym::putdata();
			cout<<"Age: "<<age<<endl;
			cout<<"Contact Number: "<<contact<<endl;
			cout<<"Gender: "<<gender<<endl;
			cout<<"Monthly Charges: "<<charges<<"Rs."<<endl;
			cout<<"Names of members under your training:"<<endl<<endl;
			for(int i=0;i<x[1];i++)
			{
				cout<<i+1<<"."<<disciples[i]<<endl;
			}
			cout<<"Average Rating: "<<rating<<endl;
		}
		void updatefee();
		void change(char id1[20])
		{
			int i;
			char temp[x[1]][20];
			for(i=0;i<x[1];i++)
			{
				if(strcmp(disciples[i],id1)!=0)
					strcpy(temp[i],disciples[i]);
				else
					strcpy(temp[i],"------");	
			}
			for(i=0;i<x[1];i++)
			{
				strcpy(disciples[i],temp[i]);
			}
			x[0]--;
			update();
		}
		int available(char id1[30])
		{
			if(x[0]<x[1])
			{
				cout<<this->name<<" has been added as your personal trainer\n";
				strcpy(disciples[x[0]],id1);
				x[0]++;
				update();
				return 1;
			}
			else return 0;
		}
		void update()
		{
			string test;
			Trainer temp;
			int flag=0;
			fstream inf("Trainer.Data",ios::binary|ios::in|ios::out);
			while(true)
			{
				if(!inf)
					break;
				inf.read((char*)&temp,sizeof(temp));
				test=this->id;
				if(test==temp.id)
				{
					inf.seekp(inf.tellp()-sizeof(*this));
					inf.write((char*)this,sizeof(*this));
					flag=1;
					break;
				}	
			}
			inf.close();
			if(flag==0)
			{cout<<"Record not found\n";exit(1);}
		}
		void setrating(double nrating)
		{
			rating=((rating*tr)+nrating)/(tr+1);
			tr++;
		}
};
class Member : public Gym
{
	private:
		int age,sub;double fees;char gender;char trainer[30];
	public:
		double weight;
		Member()
		{}
		Member(char email[20])
		{
			int flag=0;
			ifstream inf("Member.Data",ios::binary);
			while(true)
			{
				if(!inf)
					break;
				inf.read((char*)this,sizeof(*this));
				if(strcmp(this->id,email)==0)
					{flag=1;break;}	
			}
			inf.close();
			if(flag==0)
			{cout<<"Record not found\n";exit(1);}	
		}
		void setweight(double weight)
			{
			this->weight=weight;
			}
		void setsub(int sub)
			{
			this->sub=sub;
			}
		void settrainer(char trainer[20])
			{
			strcpy(this->trainer,trainer);
			}
		void setfees(double fees)
			{
			this->fees=fees;
			}
		int getsub()
			{return sub;}
		char* gettrainer()
		{return trainer;}			
		virtual void getdata()
		{
			char ch;
			Gym::getdata();
			int flag=1;
			while (flag==1)
			{
				cout<<"Enter Email id:           [ For e.g >>> m_xyz] "<<endl;
				cin>>id;
				cout<<"Enter Password:";cin>>pass;
				flag=compare(id);
				if(flag==1)
					cout<<"This email id is already taken.Enter again\n";
			}
			cout<<"Enter age: ";cin.clear();
			cin>>age;
			cout<<"Enter your weight in kilograms(Kg): ";
			cin>>weight;
			cout<<"Enter gender(M/F): \n";
			cin>>gender;
			cout<<"\n---------------\n";
			cout<<"Select from the below options\n"<<"1. Monthly Subscription(1000 Rs)\n"<<"2. Three Months package(2500 Rs.)\n"<<"3. Six Months Package(5000 Rs. + 10% Discount on Trainer fees)";
			cin>>sub;
			fees=1000;
			cout<<"Do you want a trainer?(Y/N)";
			cin>>ch;
			flag=0;
			if(ch=='y'||ch=='Y')
			{
				while(flag==0)
				{
					display_trainer();
					cout<<"Enter email id of the trainer you have selected: ";
					char tid[20];cin>>tid;
					Trainer t(tid);
					flag=t.available(id);
					if(flag==0)
						{
						cout<<">>This trainer's slots are full!!\n\n>>Please select another trainer\n\n";
					}
					else
					{
						strcpy(trainer,t.id);
						if (sub==3)
							{
							fees+=0.9*t.getcharge();
						}
						else
							{
							fees+=t.getcharge();
						}
					}
				}
			}
			else 
			{
			strcpy(trainer,"--");
		}
		}	
		virtual void putdata()
		{
			Gym::putdata();
			cout<<"Age: "<<age<<endl;
			cout<<"Current Weight: "<<weight<<"Kg"<<endl;
			cout<<"Gender: "<<gender<<endl;
			cout<<"Monthly Subscription: "<<sub<<endl;
			cout<<"Personal Trainer Name: "<<trainer<<endl;
			cout<<"Your monthly subscription: \n";
			if(sub==1)
				cout<<"1. Normal Monthly subscription\n";
			else if(sub==2)
				cout<<"2. Three months Package\n";
			else if(sub==3)
				cout<<"3. Six Months Package\n";
			cout<<"Monthly fees: "<<fees<<"Rs."<<endl;	
		}
		void update()
		{
			string test;
			Member temp;
			int flag=0;
			fstream inf("Member.Data",ios::binary|ios::in|ios::out);
			while(true)
			{
				if(!inf)
					break;
				inf.read((char*)&temp,sizeof(temp));
				test=this->id;
				if(test==temp.id)
				{
					inf.seekp(inf.tellp()-sizeof(*this));
					inf.write((char*)this,sizeof(*this));
					flag=1;
					break;
				}	
			}
			inf.close();
			if(flag==0)
			{cout<<"Record not found\n";exit(1);}
		}
		void changetrainer();
		
};
class Admin: public Gym
{
	private:
		double ebill,total;char contact[15];
	public:
		Admin():total(0){}
		int alogin(char id1[20],char pass1[20])
		{
			int flag=0;
			ifstream inf("Admin.Data");
			while (true)
			{
				if(inf.eof())
					break;
				inf.read((char*)this,sizeof(*this));
				if(strcmp(id,id1)==0&&strcmp(pass,pass1)==0)
				{
					flag=1;break;
				}
			}
			return flag;
		}
		void setebill(double bill)
		{ebill=bill;}
		void getdata()
		{
			Gym::getdata();
			cout<<"Enter ID: ";cin>>id;
			cout<<"Enter password: ";cin>>pass;
			cout<<"Enter contact number: ";cin>>contact;
		}
		void putdata()
		{
			Gym::putdata();
			cout<<"Contact Number: "<<contact;
		}
		void awrite()
		{
			getdata();
			ofstream ouf("Admin.Data",ios::app|ios::out);
			ouf.write((char*)this,sizeof(*this));
		}
		double calculate_income()
		{
			double comm=0;
			ifstream inf("Member.Data",ios::binary);
			int size;
			size=sizeof(Member);
			Member temp;
			while (true)
			{
				inf.read((char*)&temp,size);
				if(inf.eof())
					{
					break;
					}
					if(!inf)
					{
					cout<<"Cannot open file\n";
					break;
					}		
				total+=1000;		
			}
			inf.close();
			ifstream inf2("Trainer.Data",ios::binary);
			size=sizeof(Trainer);
			Trainer temp1;
			while(true)
			{
				inf2.read((char*)&temp1,size);
				if(inf2.eof())
					{break;}
				if(!inf2)
					{
					cout<<"Cannot read data from file\n";
					break;
					}
				for(int i=0;i<temp1.x[0];i++)
					comm+=0.2*temp1.getcharge();	
			}
			inf2.close();
			total+=comm;
			return total;
		}
		double profit()
		{return (total-ebill);}
};
Gym *arrp[100];
gtype Gym::gettype()
{
	if(typeid(*this)==typeid(Member))
		return tmember;
	else if (typeid(*this)==typeid(Trainer))
		return ttrainer;
}
void Gym::write(char ch)
{
	if (ch=='m'||ch=='m')
	{
		Member temp;
		temp.getdata();
		ofstream ouf("Member.Data",ios::binary|ios::app|ios::out);
		ouf.write((char*)&temp,sizeof(temp));
		ouf.close();
	}
	else if (ch=='t'||ch=='T')
	{
		Trainer temp;
		temp.getdata();
		ofstream ouf("Trainer.Data",ios::binary|ios::app|ios::out);
		ouf.write((char*)&temp,sizeof(temp));
		ouf.close();
	}
}
void Gym::display_trainer()
{
	ifstream inf("Trainer.Data",ios::binary);
	Trainer temp;
	while (true)
	{
		inf.read((char*)&temp,sizeof(temp));
		if(inf.eof())
			break;
		temp.putdata();
	}
}
void Gym::read()
{
	int i=0;
	ifstream inf("Member.Data",ios::binary);
	int size;
	size=sizeof(Member);
	while (true)
	{
		if(inf.eof())
			{break;}
		if(!inf)
			{cout<<"Cannot open file\n";break;}	
		arrp[i]=new Member;	
		inf.read((char*)arrp[i],size);	
		i++;	
	}
	inf.close();
	ifstream inf2("Trainer.Data",ios::binary);
	size=sizeof(Trainer);
	while(true)
	{
		if(inf2.eof())
			{break;}
		if(!inf2)
			{cout<<"Cannot read data from file";break;}
		arrp[i]=new Trainer;
		inf2.read((char*)arrp[i],size);
		i++;	
	}
	n=i;
	inf2.close();
}
int Gym::compare(char id[20])
{
	int flag=0;
	read();
	for(int i=0;i<n;i++)
	{
		if(strcmp(arrp[i]->id,id)==0)
		{
			flag=1;
			break;
		}
	}
	return flag;	
}
gtype Gym::login(char id[20],char pass[20])
{
	gtype etype;
	int flag=0;
	for(int i=0;i<n;i++)
	{
		if(strcmp(arrp[i]->id,id)==0&&strcmp(arrp[i]->pass,pass)==0)
		{
			etype=arrp[i]->gettype();
			flag=1;
			break;
		}
	}
	if(flag==0)
		etype=null;
	return etype;	
}
void Member:: changetrainer()
{
	int flag;
	while(flag==0)
	{
		display_trainer();
		cout<<"Enter email id of the trainer you have selected: ";
		char tid[20];cin>>tid;
		Trainer t(tid);
		flag=t.available(id);
		if(flag==0)
			cout<<">>This trainer's slots are full!!\n\n>>Please select another trainer\n\n";
		else
		{
			if(strcmp(trainer,"----")!=0)
			{
				Trainer temp(trainer);
				temp.change(id);
			}
			strcpy(trainer,t.id);
			if (sub==3)
				{
				fees+=0.9*t.getcharge();
			    }
			else
				{
				fees+=t.getcharge();
			    }
		}
	}
}
void Trainer:: updatefee()
{
	double fees;
	for(int i=0;i<x[0];i++)
	{
		Member temp(disciples[i]);
		if (temp.getsub()==3)
			{
		    fees=1000+(0.9*charges);
		}
		else
			{
			fees=1000+charges;
		}
		temp.setfees(fees);
		temp.update();
	}
}
void Gym::delete_acc(char id[20],char ch)
{
	if (ch=='m')
	{
		Member temp;
		ifstream inf("Member.Data",ios::binary);
		ofstream ouf("Temp.Data",ios::binary|ios::app|ios::out);
		while(true)
		{
			if(inf.eof())
				break;
			inf.read((char*)&temp,sizeof(temp));
			if(strcmp(id,temp.id)!=0)
				{
				ouf.write((char*)&temp,sizeof(temp));
			}
		}
		inf.close();
		ouf.close();
		remove("Member.Data");
		rename("Temp.Data","Member.Data");
	}
	else if (ch=='t')
	{
		Trainer temp;
		ifstream inf("Trainer.Data",ios::binary);
		ofstream ouf("Temp.Data",ios::binary|ios::app|ios::out);
		while(true)
		{
			if(inf.eof())
				break;
			inf.read((char*)&temp,sizeof(temp));	
			if(strcmp(id,temp.id)!=0)
			{
			
				ouf.write((char*)&temp,sizeof(temp));
			}
		}
		inf.close();
		ouf.close();
		remove("Trainer.Data");
		rename("Temp.Data","Trainer.Data");
	}
}
void start()
{
	int choice;char ch;
	int flag;char cont='Y';
	char id[20],pass[20];
	gtype etype;
	Gym obj;
	obj.read();
	while (true)
		{
			cout<<"Enter ID: ";cin>>id;
			cout<<"Enter password: ";cin>>pass;
			etype=obj.login(id,pass);
			if(etype!=null)
				{cout<<"\nSuccess!!!!\n";break;}
			else
				cout<<"\nIncorrect ID or password.Enter again\n";
		}
		if(etype==tmember)
		{
			Member m(id);m.putdata();
			cout<<"Do you want to update your information?(Y/N)\n\n";cin>>ch;
			while(ch=='y'||ch=='Y')
			{
				cout<<">Press 1 to update name\n>Press 2 to change password\n>Press 3 to update weight\n>Press 4 to update your subscription\n>Press 5 to change Trainer\n>Press 6 rate your trainer\n>Press 7 to view your BMI index\n";
				cin>>choice;
				switch(choice)
				{
					case 1:
						{
						cout<<"Enter new name: ";cin>>m.name;
						break;
					}
					case 2:
						{
						cout<<"Enter new Password: ";cin>>pass;	
						m.setpass(pass);break;
					}
					case 3:
						{
						cout<<"Enter new weight: ";double weight;cin>>weight;
						m.setweight(weight);break;
					}
					case 4:
						{
						cout<<"Select from the following options\n\n"<<"1. Monthly Subscription(1000 Rs)\n\n"<<"2. Three Months package(2500 Rs.)\n\n"<<"3. Six Months Package(5000 Rs. + 10% Discount on Trainer fees)";
						int sub;cin>>sub;m.setsub(sub);
						break;
					}
					case 5:
						{
						m.changetrainer();
						break;
					}
					case 6:
						{
						cout<<"Enter Your rating of the trainer:\n1->Worst\n2->Bad\n3->Average\n4->Good\n5->Perfect\n";
						double rate;cin>>rate;
						Trainer temp(m.gettrainer());
						temp.setrating(rate);temp.update();
						break;
					}
					case 7:
						{
							cout<<"Enter your height in Feets and Inches\n:";
							double htF,htI,bmi;cout<<"Feets:";cin>>htF;cout<<"Inches:";cin>>htI;
							double ht=(htF*12)+htI;
							bmi=((m.weight*2.205)*703)/(ht*ht);
                            cout<<"Your BMI is : "<<bmi<<endl;
							if(bmi>25)
                            cout<<">You are Overweight !!!!\n";
                            else if(bmi<25 && bmi>18.5)
                            cout<<"Your BMI is Optimal :)\n";
                            else
                            cout<<"You are Underweight !!!!\n";
						}
							
				}
				cout<<"Do you want to make any more changes?(Y/N)\n ";cin>>ch;
				if(ch=='n'||ch=='N')
					m.update();
			}
		}
		else if(etype==ttrainer)
		{
			Trainer t(id);
			t.putdata();
			cout<<"Do you want to update your information?(Y/N)\n";cin>>ch;
			while(ch=='y'||ch=='Y')
			{
				cout<<">Press 1 to update name\n>Press 2 to change password\n>Press 3 to update contact Number\n>Press 4 to update your monthly charges\n>Press 5 to remove from List\n";
				cin>>choice;
				switch(choice)
				{
					case 1:
						{
						cout<<"Enter new name: ";cin>>t.name;
						break;
					}
					case 2:
						{
						cout<<"Enter new Password: ";cin>>pass;	
						t.setpass(pass);
						break;
					}
					case 3:
						{
						cout<<"Enter new contact: ";char contact[15];
						cin>>contact;
						t.setcontact(contact);break;
					}
					case 4:
						{
						cout<<"Enter new Monthly charges:";
						double charges;cin>>charges;
						t.setcharge(charges);
						t.updatefee();
						break;
					}
					case 5:
						{
						cout<<"Enter email id of the Member you want to remove from your list: ";
						char id[20];cin>>id;
						t.change(id);
						Member temp(id);
						temp.settrainer("--");
						temp.update();
						break;
					}
				}
				cout<<"Do you want to make any more changes?(Y/N) ";cin>>ch;
				if(ch=='n'||ch=='N')
					t.update();
			}
		}
}
void start(int n)
{
		char ch;int choice;
	    int flag;char cont='Y';
	    char id[20],pass[20];
		Admin a;
		int next;
		
		while (flag==0)
			{
				cout<<"Enter ID: ";cin>>id;
				cout<<"Enter password: ";cin>>pass;
				flag=a.alogin(id,pass);
				if (flag==0)
					cout<<"Incorrect ID or password.Try again\n";
			}
			a.putdata();
			while (cont=='Y'||cont=='Y')
			{
			cout<<"\n>Press 1 to display Monthly Income\n>Press 2 to to display net monthly profit\n>Press 3 to delete an account\n>Press 4 to view trainer info\n";cin>>choice;
			if(choice==1)
				cout<<"Monthly Income: "<<a.calculate_income()<<"Rs."<<endl;
			else if(choice==2)
			{
				cout<<"Enter electricty expenses: ";
				double elec;cin>>elec;
				cout<<"Enter staff wages: ";
				double swages;cin>>swages;
				cout<<"Enter rent: ";
				double rent;cin>>rent;
				double bill;
				bill=elec+swages+rent;
				a.setebill(bill);
				a.calculate_income();
				cout<<"Net Profit after excluding all expenses: "<<a.profit()<<"Rs."<<endl;
			}
			else if(choice==3)
			{
				while(cont=='Y'||cont=='y')
				{
				cout<<"Press M for member\nPress T for trainer\n";cin>>ch;
				cout<<"Enter id of the account to be deleted: ";cin>>id;
				if(ch=='m'||ch=='M')
				a.delete_acc(id,'m');
				cout<<"Record Deleted!\n"<<endl;
				cout<<"Do you want to delete more records(Y/N):";
				cin>>cont;
				if(cont=='N'||'n')
				break;
					
				else if(ch=='t'||ch=='T')	
					a.delete_acc(id,'t');
					cout<<"Record Deleted!\n"<<endl;
				cout<<"Do you want to delete more records(Y/N):";
				cin>>cont;
				if(cont=='N')
				break;	
			}
			}
			else if(choice==4)
				a.display_trainer();
		cout<<endl<<"Do you want to view more info or make any more changes(Y/N):";cin>>cont;
		if(cont=='N'||'n')
		{
			exit(1);
		}
		}
}
	

int main()
{
	cout<<"\t\t\t\t*****-----------Welcome to FITHUB----------*****\n\n\n";
	cout<<">Press 1 to login\t\t(If you are new.Press 0 to signup)\n>Press 2 for Admin account\n";
	int choice;char ch;
	cin>>choice;
	int flag;char cont='Y';
	char id[20],pass[20];
	gtype etype;
	Gym obj;
	obj.read();
	if (choice==1)
	{
		start();
	}
	else if (choice==0)
	{
		cout<<"Do you want to join as Trainer or Member?\n>Press M for member\n>Press T for trainer\n";
		cin>>ch;
		if(ch=='m'||ch=='M')
		{
			Member m;
			m.write('m');
			cout<<"Do you want to login now ?(Y/N):";cin>>cont;
			if(cont=='N'||cont=='n')
			{
				exit(1);
			}
			else
			{
				start();
			}		
		}
		else if(ch=='t'||ch=='T')
		{
			Trainer t;
			t.write('t');
				cout<<"Do you want to login now ?(Y/N):";cin>>cont;
			if(cont=='N'||cont=='n')
			{
				exit(1);
			}
			else
			{
				start();
			}
			
		}
	}
	else if(choice==2)
	{
		Admin a;
		int next;
		cout<<"Press 1 to login.Press 0 to signup for new account\n";
		cin>>next;
		if(next==1)
		{
		    start(1);
		}
		else if (next==0)
			a.awrite();
			cout<<"Do you want to login now ?(Y/N)";cin>>cont;
			if(cont=='N'||cont=='n')
			{
				exit(1);
			}
			else
			{
				start(1);
			}
	}
}


