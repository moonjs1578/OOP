/*
 *  + class VectorPerson: erase(), insert() 추가
 *  + class PersonManager: remove(), insert() 추가
 *  + class ClassAndObject: 멤버 객체 변수의 초기화 시점 및 방법 추가
 *        (멤버 선언시, 생성자 서두, 생성자 본체 등)
 *        함수 선언 시 매개변수 const의 필요성 제기
 *  + 이를 위해 class Init1 ~ class Init6 추가, ClassAndObject 내부에
 *        memberInitialization(), class Parameter, normalParameter(),
 *        constParameter(), temporaryParameter(), stringParameter(),
 *        parameters() 멤버 추가
 */

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/******************************************************************************
 * 아래 상수 정의는 필요에 따라 변경하여 사용하라.
 ******************************************************************************/
#define AUTOMATIC_ERROR_CHECK false // true: 자동 오류 체크, false: 키보드에서 직접 입력하여 프로그램 실행
/******************************************************************************
 * Person class
 ******************************************************************************/

class Person
{
    string name;        // 이름
    string passwd;		// 비
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char*   address;     // 주소
    char* memo_c_str;

protected:
    void inputMembers(istream* in);
    void printMembers(ostream* out);
    void copyAddress(const char* address); // 5_2에서 추가
    void copyMemo(const char* c_str);      // 5_2에서 추가
public:
    //Person();
    //Person(const string name);
    Person(const string name={}, int id={}, double weight={}, bool married={}, const char *address={});
    Person(const Person& p);
    ~Person();

    void set(const string name, int pid, double pweight, bool pmarried, const char *paddress);
    void setName(const string name)      { this -> name = name; }
    void setPasswd(const string passwd)	 { this -> passwd = passwd; }
    void setId(int id)                   { this -> id = id; }
    void setWeight(double weight)        { this -> weight = weight; }
    void setMarried(bool married)        { this -> married = married; }
    void setAddress(const char* paddress);
    void setMemo(const char* c_str);
    string getName()    { return name; }
    string getPasswd()		 { return passwd; }
    int         getId()      { return id; }
    double      getWeight()  { return weight; }  // 구현 시
    bool        getMarried() { return married; }  // 리턴 값들을
    const char* getAddress() { return address; } // 수정하시오.
    const char* getMemo()	 { return memo_c_str; }
    void input(istream* pin)  { inputMembers(pin); } // ch3_2에서 추가
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
    void whatAreYouDoing();                          // ch3_2에서 추가
    Person& assign(const Person& p);
    bool isSame(const string name, int pid);         // ch3_2에서 추가
};


//Person::Person() : Person(""){
//}

//Person::Person(const string name) : Person(name, 0, 0, 0, ""){
//}
Person::Person(const string name, int id, double weight, bool married,const char *address)
	: name(name), id{id}, weight{weight}, married{married}, memo_c_str{} {
    copyAddress(address);
    cout << "Person::Person(...):"; println();
}
Person::Person(const Person& p):
    name(p.name), id{p.id}, weight(p.weight), married(p.married){
    copyAddress(p.address);
    copyMemo(p.memo_c_str);
    cout << "Person::Person(const Person&):";
    println();
}
Person::~Person() {
	cout << "Person::~Person():"; println();
	  if (address != nullptr) {
	        delete[] address;
	  }
	    if (memo_c_str != nullptr) {
	        delete[] memo_c_str;
	    }
}

void Person::printMembers(ostream* pout)   {
	*pout << name << " " << id << " " << weight << " "
		 << married << " " << ":" << (address==nullptr ? "" : address) << ":";
}

void Person::set(const string name, int pid, double pweight,
    bool pmarried, const char *paddress) {
    this -> name = name;
    id = pid;
    weight = pweight;
    married = pmarried;
    setAddress(paddress);
}

void Person::inputMembers(istream* pin)   {
    *pin >> name >> id >> weight >> married;
    if (!(*pin)) return;

    // 지역변수로 미리 큰 주소용 배열을 잡는다.
    char address[40];    // ch5_2에서 추가됨
    pin->getline(address, 40, ':');

    pin->getline(address, 40, ':');
    // 아래 함수를 통해 위 지역변수 address[]에 있는 주소를 멤버 address로 복사한다.
    // 아래 함수에서 address[]의 문자열 길이만큼 메모리를 할당(멤버 address용) 받은 후 복사한다.
    // 멤버 address는 이전에 이미 초기화되었기 때문에 copyAddress()가 아닌 아래 함수를 사용함
    setAddress(address); // ch5_2에서 추가됨
}

void Person::whatAreYouDoing() {
	cout << name << " is taking a rest." << endl;
}

Person& Person::assign(const Person& p) {
    this->name = p.name;
    this->passwd = p.passwd;
    this->id = p.id;
    this->weight = p.weight;
    this->married = p.married;

    setAddress(p.address);       // 기존 메모리 반납 후 새로 할당 + 복사
    setMemo(p.memo_c_str);       // 기존 메모리 반납 후 새로 할당 + 복사

    return *this;
}
bool Person::isSame(const string name, int pid) {
	return (this -> name == name&& id == pid);
}
void Person::setAddress(const char* address) {
	if(this->address!=nullptr) {
        delete[] this->address;
	}
    copyAddress(address); // 새로 메모리 할당받은 후 복사한다.
}
// 멤버 memo_c_str은 생성자에 의해 nullptr로 설정되었거나 복사생성자에 의해 이미 초기화되었 수도 있음
// 만약 멤버 memo_c_str용 메모리가 할당되었다면 먼저 반납해야 함
void Person::setMemo(const char* c_str)      {
	if(this->memo_c_str!=nullptr){
		delete[] this->memo_c_str;
	}
    copyMemo(c_str); // 새로 메모리 할당받아 복사한다.
}
// 처음 객체가 초기화될 때(생성자 또는 복사생성자) address 멤버를 초기화하고자 할 때 호출된다.
// 즉, 일반 생성자 또는 복사 생성자에서만 호출됨.
// 새로 할당받은 메모리에 매개변수 address 문자열을 복사한다.
void Person::copyAddress(const char* address) {
		  if (address==nullptr){
			  this->address = nullptr;
			  return;
		  }
		  this->address = new char[strlen(address) + 1];
		  strcpy(this->address, address);

          // [교재 예제 5-11]의 복사 생성자  참조할 것
          // strlen(), strcpy() 함수는 구글링 또는 http://www.cplusplus.com/reference/에서 검색
          // strlen()은 끝의 null 문자를 포함하지 않은 길이이므로
          // 이를 포함하기 위해 할당해야 할 메모리는 strlen()+1이어야 함
          // strcpy()는 끝의 null 문자도 함께 복사해 준다라는 사실에 유의하라.
}

// 복사 생성자에 의해 처음 메모 문자열 memo_c_str을 초기화할 때 호출된다.
// 복사 생성자에서만 호출되고 일반 생성자에서는 nullptr로 설정됨
void Person::copyMemo(const char* c_str)      {
    if(c_str == nullptr){
    	this->memo_c_str =  nullptr;
    	return;
    }
    this->memo_c_str = new char[strlen(c_str)+1];
    strcpy(this->memo_c_str, c_str);
}

/******************************************************************************
 * User Interface
 ******************************************************************************/
// 기본적인 입력과 관련된 전역 함수들을 UI라는 이름공간 내부에 정의함

class UI {


static string line, emptyLine;
public:
	static bool echo_input;
	static bool checkInputError(istream* pin, const string msg);
	static bool checkDataFormatError(istream* pin);
	static bool inputPerson(Person* p);
	static string getNext(const string msg);
	static string getNextLine(const string msg);
	static int getInt(const string msg);
	static int getPositiveInt(const string msg);
	static int getIndex(const string msg, int size);
	static int selectMenu(const string menuStr, int menuItemCount);
};
bool UI::echo_input = false;
string UI::line, UI::emptyLine;
// 입력에서 정수 대신 일반 문자가 입력되었는지 체크하고 에러 발생시 에러 메시지 출력
bool UI::checkInputError(istream* pin, const string msg) {
    if (!(*pin)) { // 에러가 발생했다면
        cout << msg;  // 에러 메시지를 출력
        pin->clear(); // 에러 발생 상태정보를 리셋함; 그래야 다음 문장에서 읽을 수 있음
        getline(*pin, emptyLine); // 에러가 발생한 행 전체를 읽어 데이터를 버림
        return true;
    }
    return false;
}

// 정수나 실수를 입력해야 하는 곳에 일반 문자열을 입력한 경우의 에러 체크
bool UI::checkDataFormatError(istream* pin) {
    return checkInputError(pin, "Input-data format MISMATCHED\n");
}

// 한 사람의 정보 즉, 각 멤버 데이터를 순서적으로 입력 받아 p에 저장하고
// 입력 중 입력 데이터에 오류가 있는지 확인하고 오류가 있을 시 에러 메시지를 출력한다.
bool UI::inputPerson(Person* p) {
    cout << "input person information:" << endl;
    p->input(&cin);
    if (checkDataFormatError(&cin)) return false;
    if (echo_input) p->println(); // 자동체크에서 사용됨
    return true;
}

// 입력장치에서 하나의 단어로 구성된 문자열을 입력 받음
string UI::getNext(const string msg) {
    cout << msg; // 입력용 메시지를 출력
    cin >> line; // 하나의 단어를 읽어 들임
    if (echo_input) cout << line << endl; // 자동체크 시 출력됨
    getline(cin, emptyLine); // 입력받은 한 단어 외 그 행의 나머지 데이타(엔터포함)는 읽어서 버림
    return line;             // 이유는 여기서 [엔터]를 제거하지 않으면
}                            // 다음의 getNextLine()에서 엔터만 읽어 들일 수 있기 때문에

// 입력장치에서 한 행을 입력 받음
string UI::getNextLine(const string msg) {
    cout << msg; // 입력용 메시지를 출력
    getline(cin, line); // 한 행을 읽어 들임

    // MAC 컴퓨터의 경우 키보드에서는 정상적으로 한 행이 읽혀지나
    // 파일에서 입력을 받을 경우 행 끝의 '\r'이 제거되지 않으므로 강제 제거해 줌
    if ((line.size() > 0) && (line[line.size()-1] == '\r'))
    	line.erase(line.size()-1, 1);

    if (echo_input) cout << line << endl; // 자동체크 시 출력됨
    return line;
}

// 하나의 정수를 입력 받음; 정수가 아닌 아닌 문자열 입력시 에러 메시지 출력 후 재입력 받음
int UI::getInt(const string msg) {
    for (int value; true; ) {
        cout << msg;
        cin >> value;
        if (echo_input) cout << value << endl; // 자동체크 시 출력됨
        if (checkInputError(&cin, "Input an INTEGER.\n"))
            continue;
        getline(cin, emptyLine); // skip [enter] after the number
        return value;
    }
}

// 하나의 양의 정수를 입력 받음; 음수 입력시 에러 메시지 출력 후 재입력 받음
int UI::getPositiveInt(const string msg) {
    int value;
    while ((value = getInt(msg)) < 0)
        cout << "Input a positive INTEGER." << endl;
    return value;
}

// 0~(size-1)사이의 선택된 메뉴 항목 또는 리스트의 항목의 인덱스 값을 리턴함
// 존재하지 않는 메뉴항목을 선택한 경우 에러 출력
int UI::getIndex(const string msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index  && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ "
             << size-1 << ")" << endl;
    }
}

// 사용자에게 메뉴를 보여주고 사용자가 선택한 메뉴항목의 인덱스를 리턴함
int UI::selectMenu(const string menuStr, int menuItemCount) {
    cout << endl << menuStr;
    return getIndex("Menu item number? ", menuItemCount);
}

 // namespace UI

/******************************************************************************
 * ch4_3: string and Memo class
 ******************************************************************************/

class Memo
{
    string mStr; // 메모를 저장해 두는 문자열

    string get_next_line(size_t* ppos);
    bool find_line(int line, size_t* start, size_t* next);
    size_t find_last_line();

public:
    Memo(const char* c_str = nullptr) : mStr(c_str ? c_str : "") { }
    string getNext(size_t* ppos);
    void displayMemo();
    const char *get_c_str();
    void set_c_str(const char *c_str);
    void findString();
    void compareWord();
    void dispByLine();
    void deleteLine();
    void replaceLine();
    void scrollUp();
    void scrollDown();
    void inputMemo();
    void run();
};

string Memo::get_next_line(size_t* ppos) {
    size_t pos = *ppos, end;

    /*
    TODO: string::find()를 이용해 행의 끝('\n') 위치를 찾아서(현재 행의 시작 위치는 pos임) end에 저장
    */
    end = mStr.find('\n', pos);

    // 메모의 끝에 '\n'이 없을 경우: (end == string::npos)
    end = (end == string::npos)? mStr.length() : end+1;
    *ppos = end; // 다음 행의 시작 위치를 기록해 둠

    /*
    TODO: 찾은 현재 행을 string::substr()으로 발췌해서 별도의 string으로 구성하여 리턴하라.
          발췌할 단어 길이는 pos와 end로 간단히 계산할 수 있음
    */
    return (pos<mStr.size()) ? mStr.substr(pos, end- pos) : " ";
}

void Memo::displayMemo() { // Menu item 1
    cout << "------- Memo -------" << endl;
    cout << mStr;
    if (mStr.length() > 0 && mStr[mStr.length()-1] != '\n')
        cout << endl; // 메모 끝에 줄바꾸기 문자가 없을 경우 출력
    cout << "--------------------" << endl;
}

void Memo::findString() {
    string word = UI::getNext("Word to find? ");
    int count = 0, len = word.length();
    for(size_t pos = 0; (pos = mStr.find(word, pos)) != string::npos; pos+=len){
    	count++;
    }
    /*
    TODO: for 문을 사용하여 반복적으로 string::find() 함수를 호출하여 찾은 단어의
          출현 회수(count)를 세어라. find()를 통해 찾은 위치에서 len을 더하면
          찾은 단어의 끝 위치가 되는데 이것이 다음 번에 찾기 시작할 위치이다.
          string::find()의 리턴 값이 string::npos와 같으면
          단어를 찾지 못했다는 것을 의미한다. 못 찾을 때까지 반복 수행하면 됨.
          찾기 시작 위치 또는 리턴 값의 타입은 size_t를 사용하라.
    */
    cout << "Found count: " << count << endl;
}

string Memo::getNext(size_t* ppos) {
    size_t pos = *ppos, end;
    for ( ; pos < mStr.size() && isspace(mStr[pos]); ++pos) ; // 단어 앞의 공백 문자들 스킵(있을 경우)
    end = pos; // pos는 단어의 시작 위치이고 end는 단어의 끝 다음 위치이다.
    if (end < mStr.size() && ispunct(mStr[end])) // 첫 글자가 구두점일 경우
        ++end;
    else { // 단어의 끝을 찾음
        for ( ; end < mStr.size() && !isspace(mStr[end]) &&
                !ispunct(mStr[end]); ++end) ;
    }
    *ppos = end; // 다음 단어의 시작 위치를 기록해 둠
    return (pos < mStr.size()) ? mStr.substr(pos, end - pos) : "";
    /*
    TODO: string::substr()을 이용해서 찾은 단어를 발췌해서 별도의 string으로 구성하여 리턴하라.
          mStr의 끝에 도착하여 더 이상 찾을 단어가 없을 경우 "" 문자열을 반환하게 된다.
          발췌할 단어의 길이는 pos와 end의 간단한 계산으로 구할 수 있다.
    */
}

void Memo::compareWord() {
    string next, word = UI::getNext("Word to compare? ");
    int less = 0, same = 0, larger = 0;

    for (size_t pos = 0; ; ) {
    	next = getNext(&pos);
        if (next == "") break;
        if (next < word)
        	++less;
        else if (next == word)
            ++same;
        else
            ++larger;
    }
    /*
    아래 pos는 getNext(&pos)를 호출할 때 다음 단어를 찾아야 할 시작 위치임
    TODO: for(size_t pos = 0; getNext(&pos)를 호출하여 mStr의 끝까지 반복 수행; )
             위 getNext(&pos)를 호출시 리턴된 다음 단어를 next에 저장한 후
             next가 ""일 경우 mStr의 끝을 의미하므로 for문 종료
             ""가 아닌 경우 찾을 단어인 word와 비교(<, >, ==)하여
             적절한 less, same, larger 변수의 값을 증가시킨다.
    */
    cout << "less: "   << less   << endl;
    cout << "same: "   << same   << endl;
    cout << "larger: " << larger << endl;
}

void Memo::dispByLine() {
    cout << "--- Memo by line ---" << endl;
    /*
    아래 pos는 get_next_line(&pos)를 호출할 때 다음 행의 시작 위치임
    TODO: for(size_t pos = 0, ... 문을 이용하여 pos가 mStr의 길이보다 작을 동안 반복 수행
             get_next_line(&pos)를 호출하여 반환된 다음 행 문자열을 line에 저장하고
             적절한 행 번호와 함께 해당 행(line)을 출력(행번호 출력은 PersonManager::display() 참조)
             행의 끝에 줄바꾸기 문자 '\n'가 없을 경우 endl 출력 (displayMemo() 참조)
    */
    size_t pos = 0;        // 줄의 시작 위치
    string line;
    for (int lineNum = 0; pos < mStr.length(); ++lineNum) {
            string line = get_next_line(&pos);
            cout << "[" << lineNum << "] " << line << endl;
    }
    cout << "--------------------" << endl;
}

bool Memo::find_line(int line_num, size_t* pstart, size_t* plen) {
    size_t start = 0;
    for(int i=0; i<line_num; i++){
    	start = mStr.find('\n', start);
    	if (start == string::npos) return false;
    	start++;
    }
    *pstart = start; // line_num 행의 시작 위치를 기록

    size_t end = mStr.find('\n', start);
    if (end == string::npos)
        *plen = string::npos; // 끝을 못 찾은 경우 (즉, 마지막 줄이고 \n이 없는 경우)
    else
        *plen = end - start; // 길이 = 끝 위치 - 시작 위치

    return true; // line_num 행을 찾았다는 것을 의미함
}

void Memo::deleteLine() {
    size_t start, len;
    size_t line_num = UI::getPositiveInt("Line number to delete? ");

    // 1. 유효성 검사: 해당 행을 못 찾은 경우 또는 start가 텍스트 끝에 도달한 경우
    if (mStr.empty() || !find_line(line_num, &start, &len) || start == mStr.size()) {
        cout << "Out of line range" << endl;
        return;
    }

    // 2. 해당 행을 삭제 (substr을 이용한 문자열 삭제)
    if (len == string::npos) // 줄바꿈 없는 마지막 줄인 경우
        mStr.erase(start);   // start부터 끝까지 삭제
    else
        mStr.erase(start, len + 1); // '\n' 포함해서 삭제

    // 3. 삭제 후 메모 내용 줄 단위로 출력
    dispByLine();
}

void Memo::replaceLine() {
    size_t start, len;
    size_t line_num = UI::getPositiveInt("Line number to replace? ");

    // 행을 찾는다. 못 찾더라도 line_num이 "다음 줄 추가"라면 허용
    bool found = find_line(line_num, &start, &len);

    string line = UI::getNextLine("Input a line to replace:\n");
    line += '\n';

    if (!found) {
        // 현재 마지막 줄 바로 뒤에 추가하는 경우
        if (line_num == 0 || find_line(line_num - 1, &start, &len)) {
            // start = 끝 위치로 설정
            start = mStr.size();
            mStr.insert(start, line); // 그냥 끝에 삽입
        } else {
            cout << "Out of line range" << endl;
            return;
        }
    } else {
        // 존재하는 행이면 해당 부분 교체
        mStr.replace(start, len + 1, line); // '\n' 포함
    }

    dispByLine();
}

void Memo::scrollUp() {
    size_t start, len;

    // 0번째 줄 찾기
    if (!find_line(0, &start, &len)) {
        cout << "Nothing to scroll.\n";
        return;
    }

    // 첫 줄 추출 (줄바꿈까지 포함해야 하므로 len + 1 문자까지 가져옴)
    string firstLine = mStr.substr(start, len);

    // 줄바꿈 문자도 포함되어 있는지 확인해서 없으면 추가로 붙이자
    if (start + len < mStr.size() && mStr[start + len] == '\n') {
        firstLine += '\n';
        len += 1; // 삭제 길이도 1 증가
    }

    // 삭제
    mStr.erase(start, len);

    // 맨 끝에 줄바꿈 없으면 하나 추가
    if (!mStr.empty() && mStr.back() != '\n') {
        mStr += '\n';
    }

    // 첫 줄 다시 붙이기
    mStr += firstLine;

    // 출력
    dispByLine();
}


// 아래 R"( 와 )"는 그 사이에 있는 모든 문자를 하나의 문자열로 취급하라는 의미이다.
// 따라서 행과 행 사이에 있는 줄바꾸기 \n 문자도 문자열에 그대로 포함된다.
// 이런 방식을 사용하지 않으면 여러 행에 걸친 문자열을 만들려면 복잡해진다.
const char* memoData = R"(The Last of the Mohicans
James Fenimore Cooper
Author's Introduction
It is believed that the scene of this tale, and most of the information
necessary to understand its allusions, are rendered sufficiently 
obvious to the reader in the text itself, or in the accompanying notes.
Still there is so much obscurity in the Indian traditions, and so much
confusion in the Indian names, as to render some explanation useful.
Few men exhibit greater diversity, or, if we may so express it, 
greater antithesis of character, 
than the native warrior of North America.
)";

size_t Memo::find_last_line() {
    for (size_t start = 0, pos = 0; true; start = pos + 1) {
        pos = mStr.find('\n', start);
        if (pos == string::npos || pos + 1 == mStr.size()) {
            return start; // 마지막 행의 시작 위치 반환
        }
    }
}

void Memo::scrollDown() {
    size_t last = find_last_line();                    // 마지막 행의 시작 위치
    size_t len = mStr.size() - last;                   // 마지막 행의 길이
    string lastLine = mStr.substr(last, len);          // 마지막 행 문자열 추출
    mStr.erase(last, len);                             // 마지막 행 삭제
    mStr = lastLine + mStr;                            // 맨 앞에 추가
    dispByLine();
}

void Memo::inputMemo() {
    mStr.clear();  // 기존 메모 문자열을 비움

    string line;
    cout << "--- Input memo lines, and then input empty line at the end ---" << endl;
    while (true) {
        getline(cin, line);  // 한 줄 입력 받기

        if (UI::echo_input) cout << line << endl;  // 자동 채점용 출력

        if (line.empty()) return;  // 빈 줄이면 종료

        line += '\n';      // 줄 끝에 개행 문자 추가
        mStr += line;      // 메모 끝에 추가
    }
}

const char* Memo::get_c_str() {
	return mStr.c_str();
}

void Memo::set_c_str(const char *c_str) {
    mStr = (c_str == nullptr) ? "" : c_str;
}

void Memo::run() {
    // TODO 문제 [1]: func_arr[], menuCount 선언
	using func_t = void(Memo::*)();
	func_t func_arr[] = {
			nullptr, &Memo::displayMemo, &Memo::findString, &Memo::compareWord, &Memo::dispByLine,
			&Memo::deleteLine, &Memo::replaceLine, &Memo::scrollUp, &Memo::scrollDown, &Memo::inputMemo
	};
	int menuCount = sizeof(func_arr)/sizeof(func_arr[0]);

    string menuStr =
        "++++++++++++++++++++++ Memo Management Menu +++++++++++++++++++++\n"
        "+ 0.Exit 1.DisplayMemo 2.FindString 3.CompareWord 4.DispByLine  +\n"
        "+ 5.DeleteLine 6.RepaceLine 7.ScrollUp 8.ScrollDown 9.InputMemo +\n"
        "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    if (mStr == "") mStr = memoData;// 멤버 mStr이 비었을 경우 위 memoData로 초기화한다.
    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
    // TODO 문제 [1]: while 문장 삽입하여 선택된 메뉴항목 실행하는 함수 호출
}

/******************************************************************************
 * ch3_2: CurrentUser class
 ******************************************************************************/

class CurrentUser
{
    Person* pUser;
    Memo memo;
public:
    CurrentUser(Person* pUser):pUser(pUser) { }  // user(u)는 this->user = u 와 동일한 기능
    void display();
    void setter();
    void getter();
    void set();
    void whatAreYouDoing();
    void isSame();
    void inputPerson();
    void changePasswd();
    void manageMemo();
    void run();
    void defaultParameter();
    void staticMember();
};

void CurrentUser::display() { // Menu item 1
    pUser -> println();
}

void CurrentUser::getter() { // Menu item 2
	cout << "name:" << pUser->getName() << ", id:" << pUser->getId()
		 << ", weight:" << pUser->getWeight() << ", married:" << pUser->getMarried()
		 << ", address:" << pUser->getAddress() << endl;
}

void CurrentUser::setter() { // Menu item 3
	Person* pp = new Person("pp");
    pp->setName(pp->getName());
    pp->setId(pUser->getId());
    pp->setWeight(pUser->getWeight());
    pp->setMarried(pUser->getMarried());
    pp->setAddress(pUser->getAddress());
    cout << "pp->setMembers():"; pp->println();
    delete pp;
}

void CurrentUser::set() { // Menu item 4
	Person* pp = new Person("pp");
    pp->set(pp->getName(), pUser->getId(), pUser->getWeight(),
              !pUser->getMarried(), pUser->getAddress());
    cout << "pp->set():"; pp->println();
    delete pp;
}

void CurrentUser::whatAreYouDoing() {  // Menu item 5
    pUser->whatAreYouDoing();
}

void CurrentUser::isSame() { // Menu item 6
    pUser->println();
    cout << "isSame(\"user\", 1): " << pUser->isSame("user", 1) << endl;
}

void CurrentUser::inputPerson() { // Menu item 7
    if (UI::inputPerson(pUser)) // GilDong 1 70.5 true :Jongno-gu, Seoul:
        display();              // user 1 71.1 true :Gwangju Nam-ro 21:
}

void CurrentUser::changePasswd() {
    string newpasswd = UI::getNext("New password: ");
    pUser -> setPasswd(newpasswd);
    cout << "Password changed" << endl;
}

void CurrentUser::manageMemo() { // Menu item 9
    memo.set_c_str(pUser->getMemo());
    memo.run();
    pUser->setMemo(memo.get_c_str());
}

void CurrentUser::defaultParameter() { // Menu item 10
    Person ps1;
    Person ps2("ps2");
    Person ps3("ps3", 3);
    Person ps4("ps4", 4, 70.4);
    Person ps5("ps5", 5, 70.5, true);
    Person ps6("ps6", 6, 70.6, true, "ps6 address");

    cout << "\nMemo m1;" << endl;
    Memo m1; // 메모 생성자에게 인자를 넘겨 주지 않은 경우
    m1.displayMemo();

    cout << "\nMemo m2(pUser->getMemo())" << endl;
    Memo m2(pUser->getMemo()); // 메모 생성자에게 인자를 넘겨 준 경우
    m2.displayMemo();
}

void CurrentUser::staticMember() { // Menu item 11
	string word1;
	word1 = UI::getNext("Input a word: ");
    //TODO: string 변수 word1을 선언하고 클래스 이름을 사용하여 UI의
    //      getNext("Input a word: ")를 호출한 후 리턴 값으로 word1 변수를 초기화하라.
    cout << "UI::getNext(): " << word1 << endl << endl;

    UI ui;
    string word2;
    word2 = UI::getNext("Input a word: ");
    //TODO: string 변수 word2을 선언하고 UI의 객체인 ui 이름으로
    //      getNext("Input a word: ")를 호출한 후 리턴 값으로 word2 변수를 초기화하라.
    cout << "ui.getNext() : " << word2 << endl;
}

void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    using CU = CurrentUser;
    func_t func_arr[] = {
    		nullptr, &CU::display, &CU::getter, &CU::setter,
    		&CU::set, &CU::whatAreYouDoing,
            &CU::isSame, &CU::inputPerson, &CU::changePasswd, &CU::manageMemo,
			&CU::defaultParameter, &CU::staticMember
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 배열의 길이
    string menuStr =
        "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
        "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
    	"+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
    	"+ 10.DefaultParameter(6_1) 11.StaticMember(6_1)                +\n"
        "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}
// ch3_2: CurrentUser class

/******************************************************************************
 * ch4_2: VectorPerson class
 ******************************************************************************/
// VectorPerson는 n개의 Person * 포인터를 pVector[] 배열에 담아 관리하는 클래스이다.
// 필요에 따라 포인터를 삽입, 삭제, 추가 등을 할 수 있다.
// 삽입하는 포인터 개수가 점점 많아지면 pVector[] 배열을 위한 메모리를 자동 확장하기도 한다.

class VectorPerson
{
    static const int DEFAULT_SIZE = 10; // pVector의 디폴트 배열 원소 개수

    Person **pVector; // Person *pVector[]; Person에 대한 포인터들의 배열, 배열에 저장될 값이 Person *이다.
    int count;        // pVector 배열에 현재 삽입된 객체 포인터의 개수
    int allocSize;    // 할당 받의 pVector의 총 배열 원소의 개수

    void extend_capacity(); /* TODO 문제 [7] */

public:
    //VectorPerson() : VectorPerson(DEFAULT_SIZE){
    //}
    VectorPerson(int capacity={DEFAULT_SIZE});
    ~VectorPerson();
    void erase(int index){}
    void insert(int index, Person *p){}
    Person* at(int index) const { return pVector[index]; }

    // 할당 받의 pVector의 총 배열 원소의 개수를 반환
    int     capacity()    const { return allocSize; }

    // pVector 배열에 현재 삽입된 객체 포인터의 개수를 0으로 설정
    void    clear()             { count = 0; }

    // 현재 삽입된 객체 포인터가 하나도 없으면 true, 있으면 false
    bool    empty()       const { return count == 0; }

    // 현재 삽입된 객체 포인터의 개수를 반환
    int     size()        const { return count; }

    // pVector 배열에 마지막 삽입된 원소 뒤에 새로운 원소 p를 삽입하고 현재 삽입된 객체 개수를 증가
    void    push_back(Person* p); /* TODO 문제 [4, 7] */

};

// capacity는 할당해야 할 배열 원소의 개수
VectorPerson::VectorPerson(int capacity) : count{}, allocSize(capacity){
    cout << "VectorPerson::VectorPerson(" << allocSize << ")" << endl;
    pVector = new Person*[allocSize]; // Person* 들의 배열을 위한 동적 메모리 할당
}

VectorPerson::~VectorPerson() {
    cout << "VectorPerson::~VectorPerson(): pVector deleted" << endl;
    delete pVector;
}
void VectorPerson::push_back(Person *p){
	if (count == allocSize)
		extend_capacity();
	pVector[count++] = p;
}
void VectorPerson::extend_capacity() {
    Person **saved_persons = pVector; // 기존의 pVector를 백업함
    allocSize *= 2;
    pVector = new Person*[allocSize];
    for(int i = 0; i < count; i++){
    	pVector[i] = saved_persons[i];
    }
    delete[] saved_persons;
    cout << "VectorPerson: capacity extended to " << allocSize << endl;
}
void VectorPerson::erase(int index){
	if(index < 0 || index >= count){
		return;
	}
	for(int i=index; i<count-1; i++){
		pVector[i] = pVector[i+1];
	}
	count--;
}
void VectorPerson::insert(int index, Person* p){}

/******************************************************************************
 * ch4_2: Factory class
 ******************************************************************************/

class Factory
{
public:
    // 동적으로 Person 객체를 할당 받은 후 키보드로부터 새로 추가하고자 하는 사람의
    // 인적정보를 읽어 들여 해당 객체에 저장한 후 그 객체의 포인터를 반환한다.
    Person* inputPerson(istream* in) {
        Person* p = new Person();
        p->input(in);  // 멤버들을 입력 받음
        if (UI::checkDataFormatError(in)) { // 정수입력할 곳에 일반 문자 입력한 경우
            delete p;         // 할당한 메모리 반납
            return nullptr;   // nullptr 반환은 에러가 발생했다는 의미임
        }
        if (UI::echo_input) p->println(); // 자동체크에서 사용됨
        return p;
    }
};

/******************************************************************************
 * ch4_2: PersonManager class
 ******************************************************************************/

class PersonManager
{
    VectorPerson persons;
    Factory factory;
    void deleteElemets();
    void printNotice(const string preMessage, const string postMessage);
    Person* findByName(const string name);

public:
    PersonManager(Person* array[], int len); // 6장에서 default 매개변수 설정
    ~PersonManager();
    void display();
    void append();
    void clear();
    void login();
    void run();
    void insert();
    void remove();
};

PersonManager::PersonManager(Person* array[], int len) {
    cout << "PersonManager::PersonManager(array[], len)" << endl;
    for(int i = 0; i<len; i++){
    	Person* s = array[i];
    	Person* NewPerson = new Person(*s);
    	persons.push_back(NewPerson);
    }
    display();
}

PersonManager::~PersonManager() {
    deleteElemets();
}

void PersonManager::deleteElemets() {
	for(int i = 0; i<persons.size(); i++){
		delete persons.at(i);
	}
	persons.clear();
}

void PersonManager::display() { // Menu item 1
    int count = persons.size();
    cout << "display(): count " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << "[" << i << "] ";
        persons.at(i)->println();
    }
    cout << "empty():" << persons.empty() << ", size():" << persons.size()
         << ", capacity():" << persons.capacity() << endl;
}

void PersonManager::printNotice(const string preMessage, const string postMessage) {
    cout << preMessage;
    cout << " [person information] ";
    cout << postMessage << endl;
}

// 아래 함수는 사용자로부터 새로 추가할 Person 객체의 수를 입력 받고 for문을 이용하여
// 그 개수만큼의 Person 객체를 생성하고 인적정보를 입력받은 후 (factory.inputPerson(&cin)을 통해)
// 그 객체 포인터를 VectorPerson persons의 맨 끝 원소로 추가한다.

/* append() 실행 시 아래 항목들을 복사해서 순서적으로 입력하면 편하게 인적정보를 입력할 수 있음
3
HongGilDong 0 71.5 false :Gwangju Nam-gu Bongseon-dong 21:
LeeMongRyong 1 65 true :Jong-ro 1-gil, Jongno-gu, Seoul:
LeeSoonShin 2 80 true :1001, Jungang-daero, Yeonje-gu, Busan:
*/
void PersonManager::append() { // Menu item 2
    int count = UI::getPositiveInt("The number of persons to append? ");
    // to_string(10) 함수: 정수 10을 문자열 "10"으로 변환
    // stoi("10") 함수: 문자열 "10"을 정수 10으로 변환
    printNotice("Input "+to_string(count), ":");
    for (int i = 0; i < count; ++i) {
        Person* p = factory.inputPerson(&cin); // 한 사람 정보 입력 받음
        if (p) persons.push_back(p); // if (p != nullptr) 와 동일;
        // 만약 p가 nullptr이면 이는 입력 시 에러가 발생한 것임
        // (즉, 정수를 입력해야 하는 곳에 일반 문자를 입력한 경우)
    }
    display();
}

void PersonManager::clear() { // Menu item 3
    deleteElemets();
    display();
}

// VectorPerson에 저장된 사람들 중 매개변수 name과 동일한 이름을 가진 사람을 찾는다.
Person* PersonManager::findByName(const string name) {
    for (int i = 0; i < persons.size(); i++){
        Person* p = persons.at(i);
        if (p->getName() == name) return p;
    }
    // 찾지 못한 경우
    cout << name + ": NOT found" << endl;
    return nullptr;
}

// 사용자로부터 로그인할 사람의 이름과 비번을 입력받고 동일한 이름을 가진 Person 객체를
// persons에서 찾고 비번이 일치하는지 체크한 후 CurrentUser(p).run() 실행한다.
// 기존(ch4-1)의 Main Menu에서 호출하던 CurrentUser를 메뉴항목에서 삭제한 후
// 대신 여기서 호출함(사용자가 선택한 인적정보 p를 인자로 넘겨 주면서)
void PersonManager::login() {
    string name = UI::getNext("user name: ");
    Person* p = findByName(name); // 해당 사람을 VectorPerson에서 찾는다.
    if (p == nullptr) return;     // 해당 사람 존재하지 않음
    string passwd = UI::getNextLine("password: ");
    if (passwd != p->getPasswd()) // 비번 불일치
        cout << "WRONG password!!" << endl;
    else
        CurrentUser(p).run();
}

void PersonManager::insert(){
}
void PersonManager::remove(){
	if(persons.size == 0){
		cout << "No entry to remove" << endl;
		return;
	}
	UI::getIndex("Index to delete? ", persons.size());
	delete persons.at(index);
	persons.erase(index);
	display();
}


void PersonManager::run() {
    using func_t = void (PersonManager::*)();
    using PM = PersonManager; // 코딩 길이를 줄이기 위해
    func_t func_arr[] = {
        nullptr, &PM::display, &PM::append, &PM::clear, &PM::login,
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
    string menuStr =
    		"====================== Person Management Menu ===================\n"
    		"= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch6)   =\n"
    		"= 5.Insert(6_2) 6.Delete(6_2)                                   =\n"
    		"=================================================================\n";


    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}


/******************************************************************************
 * ch3_2, 4_1, 4_2: MultiManager class
 ******************************************************************************/
class MultiManager
{
    static const int personCount = 5;
    Person persons[personCount] = {
        Person("p0", 10, 70.0, false, "Gwangju Nam-gu Bongseon-dong 21"),
        Person("p1", 11, 61.1, true,  "Jong-ro 1-gil, Jongno-gu, Seoul"),
        Person("p2", 12, 52.2, false, "1001, Jungang-daero, Yeonje-gu, Busan"),
        Person("p3", 13, 83.3, true,  "100 Dunsan-ro Seo-gu Daejeon"),
        Person("p4", 14, 64.4, false, "88 Gongpyeong-ro, Jung-gu, Daegu"),
    };
    // new를 이용해 동적으로 할당할 경우 소멸자 함수를 만들어 거기서 delete 해 주어야 함

    static const int allPersonCount = personCount;
    Person* allPersons[allPersonCount] = {
        &persons[0], &persons[1], &persons[2], &persons[3], &persons[4],
    };

    PersonManager personMng { allPersons, allPersonCount };
    // 위 문장은 PersonManager personMng(allPersons, allPersonCount);와 동일함

public:
    void run() {
        cout << "PersonManager::run() starts" << endl;
        personMng.run();
        cout << "PersonManager::run() returned" << endl;
    }
}; // ch3_2, 4_1, 4_2: MultiManager class


/******************************************************************************
 * ch3_1: Class And Object
 ******************************************************************************/

//Person gps("gps", 1000, 100, true, "gps adress");

class ClassAndObject
{
	void defualConstructor() { // Menu item 1
	        Person ps;    // Person::Person() 기본 생성자 및 소멸자 실행
	}

	void constructor() { // Menu item 2: 지역객체의 다양한 생성자 및 소멸자 실행
	        Person ps1;
	        Person ps2("ps2");
	        Person ps3("ps3", 3, 70.3, true, "ps3 address");
	}

	void construcor_destructor_inner_inner() {
        cout << "\n--- construcor_destructor_inner_inner() begins ---" << endl;
        Person ps3("ps3");
        cout << "\n- if begins -" << endl;
        if (true) {
            Person ps4("ps4");
        }
        cout << "- if ends -\n" << endl;
        cout << "- temporary object begins -" << endl;
        Person("temp_ps_1"); // 임시객체(이름 없는 객체) 성성 및 소멸
        cout << endl;
        Person("temp_ps_2").setName("TEMP_PS_2"); // 임시객체 생성,
	                                                  // setName() 호출, 임시객체 소멸
        cout << "- temporary object ends -\n" << endl;
        Person ps5("ps5");
	    }

	void construcor_destructor_inner() {
        cout << "\n--- construcor_destructor_inner() begins ---" << endl;
        Person ps2("ps2");
        construcor_destructor_inner_inner();
        cout << "--- construcor_destructor_inner_inner() returned ---\n" << endl;
        Person ps6("ps6");
	}

	void construcorDestructor() { // Menu item 3
        Person ps1("ps1");
        construcor_destructor_inner();
        cout << "--- construcor_destructor_inner() returned ---\n" << endl;
    }

	void global_static_local_objects_inner() {
        cout << "\n--- global_static_local_objects_inner() begins ---" << endl;
        //static Person sps("sps", 2000, 200, false, "sps adress");
    }

    void globalStaticLocalObjects() { // Menu item 4
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
    }

public:
    // 사용자가 선택한 메뉴 항목을 실행하는 멤버 함수(func_arr[menuItem]에 등록된 함수)를 호출
    void run() {
        // ClassAndObject의 멤버 함수에 대한 포인터 타입인 새로운 데이타 타입 func_t를 정의함
        using func_t = void (ClassAndObject::*)();
        // 위 using 문은 ClassAndObject 클래스의 멤버 함수(리턴 타입이 void 이면서 매개변수가 없는)에
        // 대한 포인터 타입을 앞으로는 간단히 func_t로 사용하겠다는 의미이다.

        // ClassAndObject의 멤버 함수 포인터들의 배열
        // 나중에 호출하기 위해 멤버 함수의 이름을 미리 배열에 저장(등록)
        //     함수 이름이 곧 함수에 대한 포인터임: 즉, 함수의 첫번째 명령어의 주소를 저장함
        // 등록된 이 멤버 함수들은 나중에 run()에서 호출됨
        //     (즉, 함수 주소로 jump 해 가서 함수를 실행함)

        func_t func_arr[] = { // 메뉴항목을 실행하는 멤버 함수를 배열에 미리 저장(등록)해 둠
            nullptr, &ClassAndObject::defualConstructor, &ClassAndObject::constructor,
            &ClassAndObject::construcorDestructor, &ClassAndObject::globalStaticLocalObjects,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        // func_arr[]의 원소의 개수 = 배열 전체 크기 / 한 배열 원소의 크기

        // 화면에 보여 줄 메뉴
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount); // 메뉴 번호 입력 받음
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])(); // 선택된 메뉴 항목을 실행할 멤버 함수를 호출함
            /* 위 문장은 다음을 간단히 한 것이다. 앞으로 계속 나올테니 잘 이해하기 바란다.
               func_t f = func_arr[menuItem];// 배열에 저장된 멤버 함수 포인터
               (this->*f)();                 // 멤버함수 포인터를 이용하여 해당 함수를 호출함
            */
        }
    }
}; // ch3_1: class ClassAndObject


/******************************************************************************
 * ch5_1: Reference and CopyConstructor
 ******************************************************************************/
class CopyConstructor
{
    Person u;
    Person backup;

public:
    // u는 일반 생성자, backup은 복사생성자를 이용하여 멤버를 초기화
    CopyConstructor(): u("u", 1, 70, true, "Gwangju"), backup(u) { }

    void explicitCopyConstructor() { // Menu item 1
            cout << "u: "; u.println();
            Person p = (u);
            p.setName("p");
            p.setId(2);
            p.setWeight(80);
            p.setMarried(false);
            p.setAddress("Seoul");
            cout << "u: "; u.println();
            cout << "p: "; p.println();
            // 함수 리턴 시 객체 p의 소멸자가 실행됨
    }
    void referenceVariable() { // Menu item 2
            cout << "p: ";
            Person p(u);

            Person& r = p;
            cout << "p: "; p.println();         // r은 참조이고 u와 동일한 객체를 공유하므로
            cout << "r: "; r.println();         // 두 출력물은 동일한 객체를 출력함

            r.setName("r");
            r.setId(2);
            r.setWeight(80);
            r.setMarried(false);
            r.setAddress("Seoul");
            cout << "p: "; p.println();
            cout << "r: "; r.println();

            p.setName("p");
            p.setId(1);
            p.setWeight(70);
            p.setMarried(true);
            p.setAddress("Gwangju");
            cout << "p: "; p.println();
            cout << "r: "; r.println();
            // r은 객체 p를 공유하는 참조이므로 함수 리턴 시 소멸자가 실행되지 않음
        }
    void function_argument(Person a) { // Menu item 3-1
        cout << "a: "; a.println();
        cout << "a.setName(a)" << endl;
        a.setName("a");
        cout << "a: "; a.println();
    }

    Person return_member_object() { // Menu item 3-2
    	return u;
    }

    void implicitCopyConstructor() { // Menu item 3
        cout << "u: "; u.println();
        cout << "\nimplicit copy constructor 1: operator =" << endl;
        cout << "Person p = u" << endl;
        cout << "p: ";

        Person p =u;
        cout << "p.setName(p)" << endl;
        p.setName("p");
        cout << "p: "; p.println();

        cout << "\nimplicit copy constructor 2: function argument" << endl;
        cout << "call function_argument(u)" << endl;

        // 묵시적으로 복사 생성자를 호출하여 함수 인자를 복사하여 함수의 매개변수 a에 넘김
        function_argument(u);
        cout << "function_argument(u) returned" << endl;

        cout << "\nimplicit copy constructor 3: return object" << endl;
        cout << "call return_member_object().println()" << endl;
        return_member_object().println();
          // return_member_object()의 리턴 값을 복사생성자에 의해 임시객체(이름 없는 지역변수)에 복사하고
          // 그 임시 객체의 println()을 호출하여 객체를 출력한다.
          // 출력 후 더 이상 그 임시 객체가 필요 없기 때문에 소멸자를 호출하여 바로 임시 객체를 소멸시킴
        cout << "return_member_object() returned" << endl;
    }

    Person return_local_object() { // Menu item 4-1
        Person pL("pL", 0, 70, true, "Gwangju Nam-gu");
        cout << "return_local_object() returns pL" << endl;
        return pL;
        // 정석대로 하면 리턴하기 전에 복사생성자를 호출하여 지역 객체 pL를 복사해 준 후
        // 리턴 직전에 pL를 소멸해야 한다.
        // 그러나 컴파일러는 효율적인 실행을 위해 복사생성자와 소멸자를 호출하지 않고
        // 함수가 리턴한 후 return_local_object().println() 호출 시
        // 함수의 지역 객체 pL의 메모리를 그대로 재사용한다. (소멸되지 않았으므로)
        // println() 실행 후 더 이상 객체가 필요 없으면 그제서야 소멸자를 호출하여 소멸시킴
    }

    Person return_temporary_object() { // Menu item 4-2
        cout << "return_temporary_object() returns Person(pT, 0, 70, true, Gwangju Nam-gu)" << endl;
        return Person("pT", 0, 70, true, "Gwangju Nam-gu"); // 임시 객체를 리턴함
        // return {"p", 0, 70, true, "Gwangju Nam-gu"}; // 위 문장과 동일한 기능임
        // 위 문장은 컴파일러가 함수의 리턴 타입을 참고하여
        //   Person("p", 0, 70, true, "Gwangju Nam-gu")으로 자동 처리함
    }

    void temporaryObject() { // Menu item 4
        cout << "temporary object 1: Person(p0, 10, 70, true, Gwangju)" << endl;
        // 임시객체 생성 방법: 클래스이름(생성자 인자들)
        // 생성자 호출된 후 아래 문장이 끝나면 바로 소멸자가 호출됨
        // 주요: 임시 객체가 포함된 해당 문장의 실행이 종료되면 임시 객체는 소멸됨
        Person("p0", 10, 70, true, "Gwangju");

        cout << "\ntemporary object 2: Person(p1, 11, 60, false, Seoul).println()" << endl;
        // 임시객체: 생성자 호출, println() 호출, 소멸자 호출
        Person("p1", 11, 60, false, "Seoul").println();

        cout << "\nreturn_member_object().println()" << endl;
        return_member_object().println(); // 복사 생성자 활용
        cout << "return_member_object() returned" << endl;

        cout << "\nreturn_local_object().println()" << endl;
        return_local_object().println(); // 복사 생성자 사용하지 않음
        cout << "return_local_object() returned" << endl;

        cout << "\nPerson pL = return_local_object()" << endl;
        Person pL = return_local_object(); // 복사 생성자 활용
        cout << "return_local_object() returned" << endl;
        pL.println();

        cout << "\nreturn_temporary_object().println()" << endl;
        return_temporary_object().println();  // 생성자 활용
        cout << "return_temporary_object() returned" << endl;

        cout << "\nPerson pT = return_temporary_object()" << endl;
        Person pT = return_temporary_object();  // 생성자 활용
        cout << "return_temporary_object() returned" << endl;
        pT.println();
    }

    // TODO: 아래 함수 매개변수를 call by value가 되게 Person의 객체 p로 선언하라.
        void call_by_value(Person p) { // Menu item 5-1: call by value: 복사생성자에 의해 복사됨
            cout << "p: "; p.println();
            cout << "u: "; u.println();
            cout << "p.set(p, 2, 80, false, Seoul)" << endl;
            p.set("p", 2, 80, false, "Seoul");
            cout << "p: "; p.println();      // p는 u과 다른 메모리를 사용하는 객체임
            cout << "u: "; u.println(); // u은 영향을 받지 않음
            // 함수 리턴 시 매개변수 p 객체의 소멸자 함수가 호출됨
        }

        // TODO: 아래 함수 매개변수를 call by reference가 되게 Person의 참조변수 p로 선언하라.
        void call_by_reference(Person &p) { // Menu item 5-2: call by reference
            cout << "p: "; p.println();   // p는 u의 참조이므로 u와 동일한 객체 메모리를 공유함
            cout << "u: "; u.println();
            cout << "p.set(p, 2, 80, false, Seoul)" << endl;
            p.set("p", 2, 80, false, "Seoul");
            cout << "p: "; p.println();   // p와 u은 동일한 객체 메모리를 공유하므로 항상 내용이 동일함
            cout << "u: "; u.println();
            u.assign(backup);       // u 값을 원래 값으로 복구
            // 매개변수 p는 참조이므로 함수 리턴 시 소멸자가 호출되지 않음
        }

        // TODO: 아래 함수 매개변수를 call by address가 되게 Person에 대한 포인터 변수 p로 선언하라.
        void call_by_address(Person *p) { // Menu item 5-3: call by address
            cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 동일한 내용이 출력됨
            cout << "u: "; u.println();
            cout << "p->set(p, 2, 80, false, Seoul)" << endl;
            p->set("p", 2, 80, false, "Seoul");
            cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 항상 동일한 내용이 출력됨
            cout << "u: "; u.println();
            u.assign(backup);       // u 값을 원래 값으로 복구
            // 매개변수 p는 포인터이므로 함수 리턴 시 소멸자가 호출되지 않음
        }

        void functionParameterType() { // Menu item 5
            cout << "call_by_value" << endl;
            // 함수 호출 시 복사생성자를 통해 u 객체를 매개변수 p에 복사
            call_by_value(u);
            cout << endl;

            cout << "call_by_reference" << endl;
            call_by_reference(u);
            cout << endl; // 단순히 u의 참조만 전달됨

            cout << "call_by_address" << endl;
            call_by_address(&u);
            cout << endl; // 단순히 u의 주소값, 즉 포인터가 전달됨
        }

        Person return_value() {                   // return value
                return u;
        }

        void return_value_test() { // Menu item 6-1
        	cout << "--- return_value_test() ---" << endl;
            cout << "call return_value()" << endl;
            cout << "p: ";

        	Person p = return_value();
            cout << "return_value() returned" << endl;
            cout << "p: "; p.println();
            cout << "p.set(p, 2, 80, false, Seoul)" << endl;
            p.set("p", 2, 80, false, "Seoul");
            cout << "p: "; p.println();        // 두 객체의 name은 다른 값임
            cout << "u: "; u.println();
                // 함수 리턴 시 지역변수 p 객체의 소멸자 함수가 호출됨
       }

       Person& return_reference() {                  // return reference
    	   return u;
       }

       void return_reference_test() { // Menu item 6-2
    	   cout << "--- return_reference_test() ---" << endl;
           cout << "call return_reference()" << endl;
           cout << "p: ";


           Person p = return_reference();
           cout << "return_reference() returned" << endl;
           cout << "p.set(p, 2, 80, false, Seoul)" << endl;
           p.set("p", 2, 80, false, "Seoul");
           cout << "p: "; p.println();
           cout << "u: "; u.println();
           cout << endl;

           cout << "call return_reference()" << endl;

           Person &r = return_reference(); // r는 리턴된 u의 참조를 저장하고 있는 참조변수임
           cout << "return_reference() returned" << endl;
           cout << "u: "; u.println();
           cout << "r.set(p, 2, 80, false, Seoul)" << endl;
           r.set("r", 2, 80, false, "Seoul");
           cout << "r: "; r.println();
           cout << "u: "; u.println();
           u.assign(backup);
                // 함수 리턴 시 지역 객체 p의 경우 소멸자 함수가 호출되지만
                //           참조 변수 r는 소멸자가 호출되지 않음
            }

        // TODO: 아래 주석을 지우고 함수의 리턴 값을 참조하여 함수의 리턴 데이타 타입을 적절히 선언하라.
        Person* return_address() {                  // return address
        	return &u;
        }

            void return_address_test() { // Menu item 6-3
                cout << "--- return_address_test() ---" << endl;
                cout << "call return_address()" << endl;

                Person *p = return_address();
                cout << "return_address() returned" << endl;
                cout << "p: "; p->println();
                cout << "u: "; u.println();
                cout << "p.set(p, 2, 80, false, Seoul)" << endl;
                p->set("p", 2, 80, false, "Seoul"); // p는 u 객체를 포인터하므로 u과 동일한 메모리를 공유함
                cout << "p: "; p->println();
                cout << "u: "; u.println();
                u.assign(backup);
                // 함수 리턴 시 p는 포인터 변수이므로 소멸자가 호출되지 않음
            }

            void returnDataType() { // Menu item 6
                return_value_test();        cout << endl;
                return_reference_test();    cout << endl;
                return_address_test();
            }
            void inputPerson() { // Menu item 7
                	cout << "u: "; u.println();
                    while (!UI::inputPerson(&u)) ;  // USER 11 88 false :DONG-GU, DAEGU:
                    backup.assign(u);
                    cout << "u: "; u.println();
                }

    void run() {
    	using func_t = void(CopyConstructor::*)();
        using CC = CopyConstructor;
        func_t func_arr[] = {
        		nullptr, &CC::explicitCopyConstructor, &CC::referenceVariable,
				&CC::implicitCopyConstructor, &CC::temporaryObject, &CC::functionParameterType,
				&CC::returnDataType, &CC::inputPerson
        };
        int menuCount = sizeof(func_arr)/sizeof(func_arr[0]);
        // TODO 문제 [3]: func_t, func_arr[], menuCount 선언
        string menuStr =
            "+++++++++ Reference And Copy Constructor Menu ++++++++++\n"
            "+ 0.Exit 1.ExplicitCopyConstructor 2.ReferenceVariable +\n"
            "+ 3.ImplicitCopyConstructor 4.TemporaryObject          +\n"
            "+ 5.FunctionParameterType 6.FunctionReturnType         +\n"
            "+ 7.inputPerson                                        +\n"
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        // TODO 문제 [3]: while 문장 삽입하여 선택된 메뉴항목 실행하는 함수를 호출하라.
        while (true) {
                int menuItem = UI::selectMenu(menuStr, menuCount);
                if (menuItem == 0) return;
                (this->*func_arr[menuItem])();
        }
  }
}; // ch5_1: Reference and CopyConstructor

/******************************************************************************
 * ch5_2: AllocatedMember, new을 이용한 동적 메모리 할당한 멤버 취급
 ******************************************************************************/
class AllocatedMember
{
    Person  u;
    Memo    memo;
    void set_print_address(Person& p, const char* address) {
    	cout << "p.setAddress(" << (address? address : "") << ")" << endl;
        p.setAddress(address);
        p.println();
        cout << endl;
    }

    void changeAddress() { // Menu Item 1
        Person p("p", 1, 70, true, "Gwangju");
        set_print_address(p, "short address");
        set_print_address(p, "middle length Address, Seoul");
        set_print_address(p, "long length Address Seoul Mapo-gu Korea");
        set_print_address(p, u.getAddress());
    }

    void print_memo(Person& p) { // 객체 p의 메모 출력
        cout << "------ " << p.getName() << " memo ------" << endl;
        const char *pmemo = p.getMemo();
        cout << (pmemo? pmemo : ""); // 메모 출력; nullptr이면 "" 출력
        cout << "--------------------" << endl << endl;
    }

    void set_print_memo(Person& p, const char* memo) { // 객체 p에 메모 복사하고 출력
        cout << "p.setMemo(memo)" << endl;
        p.setMemo(memo);
        print_memo(p);
    }

    void changeMemo() { // Menu Item 2
        Person p("p", 1, 70, true, "Gwangju");
        set_print_memo(p, "short memo\n");
        set_print_memo(p, "middle long memo: The Last of the Mohicans\n");
        set_print_memo(p, u.getMemo());
    }
    void manageMemo() { // Menu item 3
        memo.set_c_str(u.getMemo());
        memo.run();
        cout << "\nmemo.run() returned" << endl;
        u.setMemo(memo.get_c_str());   // 메모 메뉴에서 새로 삽입한 메모를 u에 저장
        print_memo(u);
    }
    Person call_by_value_and_return_value(Person p) { // 복사생성자로 p 초기화
            cout << "p.setName(p)" << endl;
            p.setName("p");
            // 함수 리턴 전에 p를 p2에 복사해서 초기화(복사생성자)
            cout << "p2: ";
            return p; // 함수 리턴 시 p 소멸자 실행
        }

    void copyConstructor() { // Menu Item 4
         cout << "u: ";    u.println();
            print_memo(u);

            cout << "Person p1(u)" << endl;
            cout << "p1: ";
            Person p1(u); // 명시적 복사생성자로 p1 초기화
            p1.setName("p1");
            p1.println();
            print_memo(p1);

            cout << "Person p2 = call_by_value_and_return_value(p1)" << endl;
            // 묵시적으로 두번의 복사생성자 실행: 함수 인자를 넘길 때, 함수 리턴 값을 p2에 복사할 때
            cout << "p: ";
            Person p2 = call_by_value_and_return_value(p1);
            cout << "call_by_value_and_return_value(p1) returned\n" << endl;
            cout << "p2.setName(p2)" << endl;
            p2.setName("p2");
            p2.println();
            print_memo(p2);
            cout << "copyConstructor() returns" << endl;
            // 함수 리턴 시 지역객체 p1, p2 소멸자 실행됨
        }
    void nullptrMember() { // Menu Item 5
            u.println();
            print_memo(u);
            cout << "set address = memo_c_str = nullptr" << endl;
            u.setAddress(nullptr);
            u.setMemo(nullptr);
            u.println();
            print_memo(u);

            cout << "memo.set_c_str(u.getMemo())" << endl;
            memo.set_c_str(u.getMemo()); // u.getMemo() == nullptr이므로 memo의 mStr은 ""이다.
            memo.displayMemo();

            cout << endl << "u.setMemo(memo.get_c_str())" << endl;
            u.setMemo(memo.get_c_str()); // memo.get_c_str() == nullptr 이므로
                                          // u의 memo_c_str은 nullptr로 설정
            print_memo(u);
        }
    void inputPerson() { // Menu item 6
            cout << "u: "; u.println();
            while (!UI::inputPerson(&u)) ;  // USER 11 88 false :DONG-GU, DAEGU:
            cout << "u: "; u.println();
    }

public:
    AllocatedMember():
        u("u", 1, 70, true, "NAMDAEMUN-RO 123, JONGNO-GU, SEOUL, KOREA") {
        u.setMemo("It is believed that the Aborigines of the American continent\n");
    }


    void run() {
        using func_t = void(AllocatedMember::*)();
        using AM = AllocatedMember;
        func_t func_arr[] = {
        		nullptr, &AM::changeAddress, &AM::changeMemo, &AM::manageMemo,
				&AM::copyConstructor, &AM::nullptrMember, &AM::inputPerson
        };
        int menuCount = sizeof(func_arr)/sizeof(func_arr[0]);
        // TODO 문제 [1]: func_t, func_arr[], menuCount 선언
        string menuStr =
            "++++++++++++++++ Allocated Member Menu ++++++++++++++++\n"
            "+ 0.Exit 1.ChangeAddress 2.ChangeMemo 3.UsingMemoMenu +\n"
            "+ 4.CopyConstructor 5.NullptrMember 6.inputPerson     +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        // TODO 문제 [1]: while 문장 삽입하여 선택된 메뉴항목 실행하는 함수 호출
        while (true) {
       	  int menuItem = UI::selectMenu(menuStr, menuCount);
             if (menuItem == 0) return;
             (this->*func_arr[menuItem])();
        }
  }
}; // ch5_2: AllocatedMember


/******************************************************************************
 * Main Menu
 ******************************************************************************/
class MainMenu
{
public:
    void run() {
        int menuCount = 5; // 상수 정의
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.PersonManager(ch3_2, 4, 6)                                        *\n"
"* 2.Class:Object(ch3_1) 3.CopyConstructor(ch5_1) 4.AllocatedMember(ch5_2) *\n"
"***************************************************************************\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: MultiManager().run();     break;
            case 2: ClassAndObject().run();           break;
            case 3: CopyConstructor().run();	break;
            case 4: AllocatedMember().run();		break;
            }
        }
        cout << "Good bye!!" << endl;
    }
}; // class MainMenu



/******************************************************************************
 * run() 함수
 ******************************************************************************/

void run() {
    MainMenu().run();
    // MainMenu 타입의 이름 없는 임시객체를 생성한 후
    // 그 객체의 run() 멤버함수를 호출함; run()에서 리턴한 후에는 임시객체가 자동 소멸됨
    // 즉, 위 문장은 아래 두 문장과 동일한 기능임
    // MainMenu mm;
    // mm.run();
}

/******************************************************************************
 * Program Test: Automatic Error Check
 ******************************************************************************/
#if AUTOMATIC_ERROR_CHECK
#include "check_error.h"
#endif

/******************************************************************************
 * main() 함수
 ******************************************************************************/
int main() {
    cout << boolalpha;  // 11장에서 배움; bool 타입 값을 0, 1 대신 true, false로 출력하도록 설정
    cin >> boolalpha;   // bool 타입 값을 0, 1 대신 true, false로 입력 받도록 설정

#if AUTOMATIC_ERROR_CHECK
    evaluate(false);   // 각 문제에 대해 단순히 O, X만 확인하고자 할 때는 false
#else
    MainMenu().run();
#endif
}
