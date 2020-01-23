#include "Test.h"

void testProduct()
{
	Product prod{ "lion", "cereale", 10.9, "nestle" };
	assert(prod.get_name() == "lion");
	assert(prod.get_type() == "cereale");
	assert(prod.get_price() == 10.9);
	assert(prod.get_producer() == "nestle");
	prod.set_name("alferst");
	prod.set_type("napolitane");
	prod.set_price(3.5);
	prod.set_producer("alka");
	assert(prod.get_name() == "alferst");
	assert(prod.get_type() == "napolitane");
	assert(prod.get_price() == 3.5);
	assert(prod.get_producer() == "alka");
	Product prod1{ "lion", "baton", 12, "nestle" };
	assert(compareNameAndType(prod, prod1));
	assert(compareNameAndType(prod1, prod) == false);
	assert(comparePrice(prod, prod1));
	assert(comparePrice(prod1, prod) == false);
	Product prod2{ "milka", "baton", 12, "nestle" };
	assert(compareName(prod, prod2));
	assert(compareName(prod2, prod) == false);
	assert(compareNameAndType(prod, prod2));
	prod.getString();
}

void testRepoAdd(const Product &prod)
{
	RepositoryFile repo{ "test.txt" };
	repo.add(prod);
	try { repo.add(prod); }
	catch (RepositoryException) {}
	vector<Product> objects = repo.getAll();
	assert(objects.size() == 1);
	assert(objects.at(0).get_name() == "lion");
	repo.getFileName();
}

void testRepoUpdate(const Product& prod)
{
	RepositoryFile repo{ "test.txt" };
	repo.add(prod);
	assert(repo.search("lion", "cereale", "nestle").get_price() == 10.9);
	Product prod1{ "lion", "cereale", 9.9, "nestle" };
	repo.update(prod1);
	assert(repo.search("lion", "cereale", "nestle").get_price() == 9.9);
	Product prod2("altfers", "napolitane", 3.6, "alka");
	try { repo.update(prod2); }
	catch (const RepositoryException) {  }
}

void testRepoRemove(const Product &prod)
{
	RepositoryFile repo{ "test.txt" };
	repo.add(prod);
	vector<Product> list = repo.getAll();
	assert(list.size() == 1);
	Product prod2{ "a", "a", 3, "a" };
	Product prod3{ "b", "a", 3, "a" };
	repo.add(prod2);
	repo.add(prod3);
	repo.remove("a", "a", "a");
	vector<Product> list2 = repo.getAll();
	assert(list2.size() == 2);
	try { repo.remove("a", "a", "a"); }
	catch (RepositoryException) {}
}

void testRepo()
{
	Product prod{ "lion", "cereale", 10.9, "nestle" };
	testProduct();
	testRepoAdd(prod);
	testRepoUpdate(prod);
	testRepoRemove(prod);
}

void testServiceAdd()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	vector<Product> list = serv.getAll();
	assert(list.size() == 1);
}

void testServiceUpdate()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("a", "a", 1, "a");
	serv.updateProduct("a", "a", 10, "a");
	vector<Product> list = serv.getAll();
	assert(list.at(0).get_price() == 10);
}

void testServiceRemove()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	vector<Product> list = serv.getAll();
	assert(list.size() == 1);
	serv.removeProduct("lion", "cereale", "nestle");
	vector<Product> list2 = serv.getAll();
	assert(list2.size() == 0);
	serv.doUndo();
}

void testServiceSearch()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	Product prod = serv.searchProduct("lion", "cereale", "nestle");
	assert(prod.get_price() == 10.9);
}

void testServiceFilter()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	assert(serv.filterAfterName("lion").size() == 1);
	assert(serv.filterAfterPrice(10.9).size() == 1);
	assert(serv.filterAfterProducer("nestle").size() == 1);
}

void testServiceSort()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	serv.addProduct("altfers", "napolitane", 5.3, "alka");
	serv.addProduct("lion", "baton", 2.46, "nestle");
	vector<Product> list0 = serv.getAll();
	vector<Product> list = serv.sortAfterName(list0);
	assert(list.at(0).get_name() == "altfers");
	vector<Product> list2 = serv.sortAfterPrice(list0);
	assert(list2.at(0).get_price() == 2.46);
	vector<Product> list3 = serv.sortAfterNameAndType(list0);
	assert(list3.at(0).get_type() == "napolitane");
}

void testValidation()
{
	Product prod{ "", "", -1, "" };
	Validation valid;
	try { valid.validationProduct(prod); }
	catch (ValidationException) { }
}

void testServiceAddToCart()
{
	RepositoryFile repo{ "test.txt" };
	Validation valid;
	Service serv{ repo, valid };
	serv.addProduct("lion", "cereale", 10.9, "nestle");
	serv.addToCart("lion");
	assert(serv.totalPrice() == 10.9);
	serv.emptyCart();
	serv.addProduct("a", "a", 10.9, "a");
	serv.addProduct("b", "b", 10.9, "b");
	serv.addProduct("c", "c", 10.9, "c");
	serv.addProduct("d", "d", 10.9, "d");
	serv.randomAddToCart(3);
	serv.allFromCart();
	serv.report();
}

void testAll()
{
	testRepo();
	testServiceAdd();
	testServiceUpdate();
	testServiceRemove();
	testServiceSearch();
	testServiceFilter();
	testServiceSort();
	testValidation();
	testServiceAddToCart();
}