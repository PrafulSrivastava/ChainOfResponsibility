#include <iostream>
#include <string>

using namespace std;
class Numbers {
private:
	int a;
	int b;
	string task;
public:
	Numbers(int a, int b, string task) {
		this->a = a;
		this->b = b;
		this->task = task;
	}

	int get_a() {
		return a;
	}
	int get_b() {
		return b;
	}
	string get_task() {
		return task;
	}
};

class ReqHandleIntf {
public:
	virtual void set_next_in_chain(ReqHandleIntf* req) = 0;
	virtual int calculate(Numbers* num) = 0;
};
class AddReqHandleIntf : public ReqHandleIntf {
private:
	ReqHandleIntf* next_in_chain;
public:
	void set_next_in_chain(ReqHandleIntf* next_in_chain) {
		this->next_in_chain = next_in_chain;
	}
	int calculate(Numbers* num) {
		if(num->get_task() == "add")
			return num->get_a() + num->get_b();
		cout << "Moving to next chain\n";
		this->next_in_chain->calculate(num);
	}
};
class SubstractReqHandleIntf : public ReqHandleIntf {
private:
	ReqHandleIntf* next_in_chain;
public:
	void set_next_in_chain(ReqHandleIntf* next_in_chain) {
		this->next_in_chain = next_in_chain;
	}
	int calculate(Numbers* num) {
		if (num->get_task() == "sub")
			return num->get_a() - num->get_b();
		this->next_in_chain->calculate(num);
	}
};

int main() {
	Numbers* num = new Numbers(1, 3, "sub");
	ReqHandleIntf* obj1 = new AddReqHandleIntf();
	ReqHandleIntf* obj2 = new SubstractReqHandleIntf();
	obj1->set_next_in_chain(obj2);
	cout << obj1->calculate(num);
}
