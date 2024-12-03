#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Student {
	std::string m_first = "First";
	std::string m_last = "Last";
	int m_id = 0;
	float m_avg = 0;

public:
	Student() {} //default constructor
	Student(std::string first, std::string last, int id, float avg) :
		m_first(first),
		m_last(last),
		m_id(id),
		m_avg(avg)
	{
	}

	float getAvg() const {
		return m_avg;
	}

	int getID() const {
		return m_id;
	}

	std::string getFirst() const {
		return m_first;
	}

	std::string getLast() const {
		return m_last;
	}

	void print() const {
		std::cout << m_first << " " << m_last << " "
			<< m_id << " " << m_avg << std::endl;
	}
};

class Course {

	std::string m_name = "Course";
	std::vector<Student> m_student;

public:
	Course() {}
	Course(const std::string& name) : m_name(name) {}

	void AddStudent(const Student& s) {
		m_student.push_back(s);
	}

	const std::vector<Student> getStudent() const {
		return m_student;
	}

	void print() const {
		for (const auto& s : m_student) {
			s.print();
		}
	}

	void loadFromFile(const std::string& filename) {
		std::ifstream fin(filename);//reading a file

		//load string tokens from files
		std::string first, last;
		int id;
		float avg;

		while (fin >> first) {
			fin >> last >> id >> avg;
			AddStudent(Student(first, last, id, avg));
		}
	}
};

//pass by value - we copy value the use it
//if we pass reference - we pass the og var 
void pp(int& i) {
	std::cout << &i << " " << i << " " << sizeof(i) << std::endl;
}

//We need to implement RAII for all 
// so we can use template just like generic in java
//IntArray - RAII
template <typename T>
class DynamicArray {

	T* m_arr;
	size_t m_size;

public:
	//constructor acquire resource
	DynamicArray(size_t size) :
		m_size(size),
		m_arr(new T[size]) {
		std::cout << "Arr constructed" << std::endl;
	}

	T get(size_t index) const {
		return m_arr[index];
	}

	void set(size_t index, T val) {
		m_arr[index] = val;
	}

	//operator overloading
	//T& is memory address of value - we can set it
	const T& operator [] (size_t index) const {
		return m_arr[index];
	}

	T& operator [] (size_t index) {
		return m_arr[index];
	}

	~DynamicArray() {
		std::cout << "Arr Destructed" << std::endl;
		delete[] m_arr;
	}

	void print() const {
		for (size_t i = 0; i < m_size; i++) {
			std::cout << (m_arr[i]) << std::endl;
		}
	}

};


int oldMain(int argc, char* argv[]) {

	//Course c("Sharma");
	//c.loadFromFile("students.txt");
	//c.print();
	//we cant modifiy const arr
	DynamicArray<float> arr(3);
	arr[0] = 7.14;
	arr[1] = 455.6;
	arr[2] = 2.119;


	arr.print();


	return 0;
}

