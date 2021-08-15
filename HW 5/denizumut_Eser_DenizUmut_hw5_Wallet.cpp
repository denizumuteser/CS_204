#include "denizumut_Eser_DenizUmut_hw5_Wallet.h"

Wallet::Wallet() 
{
	size = 0;
}

Wallet::Wallet(const Wallet& wallet)
{	
	currencies = wallet.deepCopy();
	size = wallet.size;
}

Wallet::~Wallet()
{
	delete[] currencies;
}

Money* Wallet::deepCopy() const
{
	Money* arr = new Money[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = currencies[i];
	}
	return arr;
}

bool Wallet::isExist(const Money& money) const
{
	for (int i = 0; i < size; i++)
	{
		if (currencies[i].currency == money.currency) 
			return true; //if same currency exist
	}
	return false;
}

bool Wallet::isExistEqual(const Money& money) const
{
	for (int i = 0; i < size; i++)
	{
		if ((currencies[i].currency == money.currency) && (currencies[i].amount == money.amount))
		{
			return true; //if same amount of same currency exists
		}
	}
	return false;
}

int Wallet::getSize() const
{
	return size; //accessing private size data for free functions
}

Money* Wallet::getCurrencies() const
{
	return currencies; //accessing private currencies data for free functions
}

Wallet Wallet::operator+(const Money& rhs) const
{
	int newsize;
	Wallet newWallet;
	if (this->isExist(rhs)) //if currency already exist
	{
		Money* arr = new Money[size]; 
		for (int i = 0; i < size; i++)
		{
			arr[i] = currencies[i];
			if (arr[i].currency == rhs.currency)
			{
				arr[i].amount += rhs.amount; //add given money amount to wallet
			}
		}
		newWallet.size = size;
		newWallet.currencies = arr;
	}
	else //if money wasnt exist in wallet
	{
		Money* arr = new Money[size + 1]; //increase wallet size by one
		for (int i = 0; i < size; i++)
		{
			arr[i] = currencies[i];
		}

		arr[size] = rhs; //add given money to the end of the old wallet
		newWallet.size = size + 1;
		newWallet.currencies = arr;
	}
	return newWallet;
}

Wallet Wallet::operator+(const Wallet& rhs) const
{
	Wallet newWallet;
	newWallet = *this;
	int size2 = rhs.size;
	for (int i = 0; i < size2; i++) //add every currency in rhs to copy of lhs wallet
	{
		newWallet = newWallet + rhs.currencies[i];
	}
	return newWallet; //return sum of two wallets
}

const Wallet& Wallet::operator=(const Wallet& rhs)
{
	if (this != &rhs)
	{
		size = 0; //delete lhs wallet
		//delete[] currencies; //destructor deletes them already 

		size = rhs.size;
		currencies = new Money[size]; //create new wallet

		for (int i = 0; i < size; i++)
		{
			currencies[i] = rhs.currencies[i]; //assign rhs currencies to lhs wallet
		}
	}
	return *this; //return newly assigned lhs wallet
}

const Wallet& Wallet::operator+=(const Wallet& rhs)
{
	Wallet newWallet(*this);
	for (int i = 0; i < rhs.size; i++)
	{
		newWallet = newWallet + rhs.currencies[i]; //add each rhs currency to lhs wallet
	}
	*this = newWallet;
	return *this;
}

Wallet Wallet::operator-(const Money& rhs) const
{
	bool toDelete = false;
	Wallet newWallet;
	Money* arr = new Money[size];
	for (int i = 0; i < size; i++)
	{	
		arr[i] = currencies[i];

		if ((arr[i].currency == rhs.currency) && (arr[i].amount >= rhs.amount)) //if sufficent currency is exist in the wallet
		{
			arr[i].amount -= rhs.amount; //spend from the wallet
			if (arr[i].amount == 0) //if amount becomes 0, give an order for deletion
			{
				toDelete = true;
			}
		}
	}
	if (!toDelete) { //if currency amount become 0, delete currency from wallet
		newWallet.size = size;
		newWallet.currencies = arr;
		return newWallet;
	}
	Money* arr2 = new Money[size - 1]; //decrease wallet size by 1
	for (int i = 0; i < size-1; i++)
	{
		if (arr[i].amount == 0)
		{
			arr2[i] = arr[i + 1];
		}
		else
		{
			arr2[i] = arr[i];
		}
	}
	newWallet.size = size-1;
	newWallet.currencies = arr2;
	return newWallet;	
}

bool Wallet::operator>=(const Money& rhs) const
{
	for (int i = 0; i < size; i++)
	{
		if (currencies[i].currency == rhs.currency && currencies[i].amount >= rhs.amount)
		{
			return true; //if wallet has more money then given amount
		}
	}
	return false;
}

bool operator==(const Wallet& lhs, const Wallet& rhs)
{
	bool isEqual = true;
	if (lhs.getSize() == rhs.getSize())
	{
		for (int i = 0; i < lhs.getSize(); i++)
		{
			if (!(lhs.isExistEqual(rhs.getCurrencies()[i]))) // check for each currency exist at the same amount in the wallet
			{
				isEqual = false;
			}
		}
		return isEqual;
	}
	else
	{
		return false;
	}

}

ostream& operator<<(ostream& os, const Wallet& ct)
{     
	{
		ostringstream ostr;
		for (int i = 0; i < ct.getSize(); i++)
		{
			ostr << ct.getCurrencies()[i].currency<< " " << ct.getCurrencies()[i].amount;
			if ((i + 1) != ct.getSize())
			{
				ostr << " - ";
			}
		}
		os << ostr.str(); //put wallet currencies into stream in wanted format
		return os;
	}
}

bool operator<=(const Money& lhs, const Wallet& rhs)
{
	if (!(rhs.isExist(lhs))) {
		return false;
	}
	for (size_t i = 0; i < rhs.getSize(); i++)
	{
		if (rhs.getCurrencies()[i].currency == lhs.currency && rhs.getCurrencies()[i].amount >= lhs.amount)
		{
			return true; //if money is less than money in wallet
		}
	}
	return false;
}
