#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
std::ostringstream toout;

class PolyNode {
private:
	int coefficient, exponent;
	PolyNode *next;

public:
	PolyNode() {};
	void setCoeff(int coeff) { coefficient = coeff; }
	void setExp(int exp) { exponent = exp; }
	void setNext(PolyNode* TheNext) { next = TheNext; }
	int getCoeff() { return coefficient; }
	int getExp() { return exponent; }
	PolyNode* Next() { return next; }
};



class PolyLList {
private:
	PolyNode* head;

public:
	PolyLList() {
		PolyNode *newNode = new PolyNode();
		newNode->setCoeff(0);
		newNode->setExp(0);
		newNode->setNext(NULL);
		head = newNode;
	};

	//destructor
	~PolyLList() {};

	void append(int coeff, int exp) {
		if (coeff == 0) {
			exp = 0;
		}

		PolyNode *newNode = new PolyNode();
		newNode->setCoeff(coeff);
		newNode->setExp(exp);
		newNode->setNext(NULL);

		PolyNode* p = head->Next();
		while (p != NULL) {
			if (p->getExp() == exp) {
				p->setCoeff(p->getCoeff() + coeff);
				return;
			}
			p = p->Next();
		}

		p = head;
		while (p->Next() != NULL) {
			if (newNode->getExp() > p->Next()->getExp()) {
				newNode->setNext(p->Next());
				p->setNext(newNode);
				return;
			}
			p = p->Next();
		}
		p->setNext(newNode);
	}

	std::string convertInt(int number){
		std::stringstream ss;
		ss << number;
		return ss.str();
	}

	std::string print() {
		std::string prints = "";
		PolyNode* p = head->Next();
		while (p != NULL) {
			if (p->getCoeff() == 0) {
				prints += convertInt(p->getCoeff()) + " " + convertInt(p->getCoeff());
			}
			else {
				prints += convertInt(p->getCoeff()) + " " + convertInt(p->getExp()) + " ";
			}
			p = p->Next();
		}
		return prints;
	}
};



void Extract(std::string str1, std::string str2) {
	PolyLList list1, list2, Add, Sub, Prod;
	int coeff, exp, coeffA, expA;
	std::stringstream str(str1);

	while (str >> coeff >> exp) {
		std::stringstream thestr(str2);

		while (thestr >> coeffA >> expA) {
			Prod.append(coeff*coeffA, exp + expA);
		}
		list1.append(coeff, exp);
		Add.append(coeff, exp);
		Sub.append(coeff, exp);
	}

	std::stringstream otherstr(str2);
	while (otherstr >> coeff >> exp) {
		list2.append(coeff, exp);
		Add.append(coeff, exp);
		Sub.append(-coeff, exp);

	}
	toout << "original 1: " << str1 << std::endl;
	toout << "original 2: " << str2 << std::endl;
	toout << "cononical 1: " << list1.print() << std::endl;
	toout << "cononical 2: " << list2.print() << std::endl;
	toout << "sum: " << Add.print() << std::endl;
	toout << "difference: " << Sub.print() << std::endl;
	toout << "product: " << Prod.print() << std::endl << std::endl;
}



int main() {
	std::string line1, line2;
	std::ifstream readFile;
	readFile.open("input.txt");
	std::ofstream outputFile("output.txt");
	
		if (readFile.is_open()) {
		while (readFile.good()) {
			getline(readFile, line1);
			getline(readFile, line2);
			Extract(line1, line2);
		}
	}
	outputFile << toout.str();
	readFile.close();
	outputFile.close();
	std::cout <<"done";
	std::cin.get();
	return 0;
	
}
