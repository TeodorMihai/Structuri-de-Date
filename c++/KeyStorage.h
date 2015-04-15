template<typename T>
class KeyStorage {

private:
	int key;
	T member;

public:

	KeyStorage(int k, T member);
	KeyStorage(int k);
	~KeyStorage();
	 T& getMember() ;
	 T setMember(T element);

};