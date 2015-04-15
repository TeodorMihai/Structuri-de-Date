
template<typename T>
class Complex {

private:
	T im;
	T re;

public:

	Complex(T im, T re);
	Complex();
	~Complex();
	Complex conjugate() const;

	T& getRe();
	T& getIm();

	void setRe(T re);
	void setIm(T im);

};