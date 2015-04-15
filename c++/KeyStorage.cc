#include "KeyStorage.h"


template<typename T>
KeyStorage<T>::KeyStorage(int key, T member) {

		this->key = key;
		this->member = member;
}

template<typename T>
KeyStorage<T>::KeyStorage(int key) {

	this->key = key;
}

template<typename T>
KeyStorage<T>::~KeyStorage() {

}

template<typename T>
T& KeyStorage<T>::getMember() {
	return this->member;
}

template<typename T>
T KeyStorage<T>::setMember(T member) {
	this->member = member;
	return this->member;
}
 

template class KeyStorage<int>;
template class KeyStorage<long int>;
template class KeyStorage<float>;
