#include "Repository.h"

void Repository::add(const Product &prod)
{
	if (exist(prod))
	{
		throw RepositoryException("The product: " + prod.get_name() + " of type: " + prod.get_type() + " by producer: " + prod.get_producer() + " exist already! \n");
	}
	objects.push_back(prod);
}

bool Repository::exist(const Product &prod)
{
	try
	{
		search(prod.get_name(), prod.get_type(), prod.get_producer());
		return true;
	}
	catch (RepositoryException&)
	{
		return false;}
}


void Repository::update(const Product &prod)
{
	for (Product &oneProd : objects)
	{
		if (prod.get_name() == oneProd.get_name() && prod.get_type() == oneProd.get_type() && prod.get_producer() == oneProd.get_producer())
		{
			oneProd.set_price(prod.get_price());
			return;
		}
	}
	throw RepositoryException("The product: " + prod.get_name() + " of type: " + prod.get_type() + " by producer: " + prod.get_producer() + " doesn't exist! \n");
}

void Repository::remove(string _name, string _type, string _producer)
{
	int i = 0;
	for (const Product &oneProd : objects)
	{
		if (oneProd.get_name() == _name && oneProd.get_type() == _type && oneProd.get_producer() == _producer)
		{
			objects.erase(objects.begin() + i);
			return;
		}
		i++;
	}
	throw RepositoryException("The product: " + _name + " of type: " + _type + " by producer: " + _producer + " doesn't exist! \n");}

Product Repository::search(const string &_name, const string &_type, const string &_producer)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i).get_name() == _name && objects.at(i).get_type() == _type && objects.at(i).get_producer() == _producer)
			return objects.at(i);
	}
	throw RepositoryException("The product: " + _name + " of type: " + _type + " by producer: " + _producer + "doesn't exist! \n");
}

const vector<Product> &Repository::getAll() noexcept
{

	return objects;
}

void RepositoryFile::storeToFile()
{
	ofstream g(fileName, ofstream::trunc);
	for (const Product prod : Repository::getAll())
		g << prod.get_name() << "," << prod.get_type() << "," << prod.get_price() << "," << prod.get_producer() << endl;
}

void RepositoryFile::loadFromFile()
{
	std::ifstream f(fileName);
	string line;
	while (getline(f, line))
	{
		if (line != "" && line != " ")
		{
			vector<string> words;
			std::stringstream ss(line);
			while (ss.good())
			{
				string substr;
				getline(ss, substr, ',');
				words.push_back(substr);
			}
			Repository::add(Product(words[0], words[1], stod(words[2]), words[3]));
		}
		
	}
	f.close();
}

void RepositoryFile::add(const Product & prod)
{
	Repository::add(prod);
	storeToFile();
}

void RepositoryFile::update(const Product & prod)
{
	Repository::update(prod);
	storeToFile();
}

Product RepositoryFile::search(const string & _name, const string & _type, const string & _producer)
{
	return Repository::search(_name, _type, _producer);
	//storeToFile();
}

void RepositoryFile::remove(string _name, string _type, string _producer)
{
	Repository::remove(_name, _type, _producer);
	storeToFile();
}

string RepositoryFile::getFileName()
{
	return fileName;
}
