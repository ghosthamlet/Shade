#include <map>
#include <string>
#include <list>
#include <set>
#include <cstdio>
#include <clocale>
#include <cmath>
#include <cctype>
#include <cstddef>
#define G0A(func, r) globals[#func] = new cFuncWrapper<r>(func)
#define G1A(func, r, a1) globals[#func] = new cFuncWrapper<r, a1>(func, 0)
#define G2A(func, r, a1, a2) globals[#func] = new cFuncWrapper<r, a1, a2>(func, 0, 0)
#define G3A(func, r, a1, a2, a3) globals[#func] = new cFuncWrapper<r, a1, a2, a3>(func, 0, 0, 0)
int *add(int *first, int *second){printf("add\n"); return new int((*first) + (*second));}
using namespace std;
class object{
	public:
		virtual object *call(){
			return attrs["__call__"]->call();
		}
		virtual object *call(object *arg1){
			return attrs["__call__"]->call(arg1);
		}
		virtual object *call(object *arg1, object *arg2){
			return attrs["__call__"]->call(arg1, arg2);
		}
		virtual object *call(object *arg1, object *arg2, object *arg3){
			return attrs["__call__"]->call(arg1, arg2, arg3);
		}
		virtual void *getValue(){
			return attrs["__val__"]->getValue();
		}
		object *getAttr(const char *attr){
			return attrs[attr];
		}
		void setAttr(const char *attr, object *val){
			attrs[attr] = val;
		}
		map<const char *, object *> attrs;
};
template <class T>
class cObject : public object{
	public:
		cObject(T val){
			wrapped = val;
		}
		void *getValue(){
			return (void *) wrapped;
		}
	private:
		T wrapped;
};
template <class R, class A=int, class A2=int, class A3=int>//A, A2, and A3 must be pointers.
class cFuncWrapper : public object {
	public:
		cFuncWrapper(R (*func)()){
			wrapped0 = func;
		}
		cFuncWrapper(R (*func)(A), int p1){//P1, P2, and P3 are used to differentiate between the different constructors. Just pass 0.
			wrapped1 = func;
		}
		cFuncWrapper(R (*func)(A, A2), int p1, int p2){
			wrapped2 = func;
		}
		cFuncWrapper(R (*func)(A, A2, A3), int p1, int p2, int p3){
			wrapped3 = func;
		}
		object *call(){
			return new cObject<R>(wrapped0());
		}
		object *call(object *arg1){
			return new cObject<R>(wrapped1((A) arg1->getValue()));
		}
		object *call(object *arg1, object *arg2){
			return new cObject<R>(wrapped2((A) arg1->getValue(), (A2) arg2->getValue()));
		}
		object *call(object *arg1, object *arg2, object *arg3){
			return new cObject<R>(wrapped3((A) arg1->getValue(), (A2) arg2->getValue(), (A3) arg3->getValue()));
		}
	private:
		R (*wrapped0)();
		R (*wrapped1)(A);
		R (*wrapped2)(A, A2);
		R (*wrapped3)(A, A2, A3);
};
map<string, object *> globals;
extern "C" {
void setValueInt(const char *to, int *val){
	//~ printf("set: %d\n", globals.count(to));
	globals[to] = new cObject<int *>(val);
}
void setValueString(const char *to, const char *val){
	//~ printf("set: %s, %s\n", to, val);
	//~ printf("set: %d\n", globals.count(to));
	globals[to] = new cObject<const char *>(val);
	//~ printf("set 1: %d\n", globals.count(to));
}
void getValue(const char *to, const char *name){
	//~ printf("get: %d\n", globals.count(to));
	globals[to] = globals[name];
}
void getAttr(const char *to, const char *name, const char *attr){
	//~ printf("get: %d\n", globals.count(to));
	globals[to] = globals[name]->getAttr(attr);
}
void setAttr(const char *to, const char *attr, const char *name){
	//~ printf("set: %d\n", globals.count(to));
	globals[to]->setAttr(attr, globals[name]);
}
void callFreeFunction0Arg(const char *to, const char *name){
	//~ printf("call: %d\n", globals.count(to));
	globals[to] = globals[name]->call();
}
void callFreeFunction1Arg(const char *to, const char *name, const char *arg1){
	//~ printf("call: %s, %s, %s\n", to, name, arg1);
	//~ printf("call: %d\n", globals.count(arg1));
	globals[to] = globals[name]->call(globals[arg1]);
	//~ printf("call 1: %d\n", globals.count(arg1));
}
void callFreeFunction2Arg(const char *to, const char *name, const char *arg1, const char *arg2){
	globals[to] = globals[name]->call(globals[arg1], globals[arg2]);
}
void callFreeFunction3Arg(const char *to, const char *name, const char *arg1, const char *arg2, const char *arg3){
	globals[to] = globals[name]->call(globals[arg1], globals[arg2], globals[arg3]);
}
void initialize(){
	//PREPARE GLOBALS//
	//globals["puts"] = new cFuncWrapper<int, const char *>(puts, 0);
	//globals["yo"] = new cObject<const char *>("yo");
	///////////////////
}
void libcinit(){
	//~ //ctypes
	//~ G1A(isalnum, int, int);
	//~ G1A(isalpha, int, int);
	//~ G1A(iscntrl, int, int);
	//~ G1A(isdigit, int, int);
	//~ G1A(isgraph, int, int);
	//~ G1A(islower, int, int);
	//~ G1A(isprint, int, int);
	//~ G1A(ispunct, int, int);
	//~ G1A(isupper, int, int);
	//~ G1A(isxdigit, int, int);
	//~ G1A(toupper, int, int);
	//~ G1A(tolower, int, int);
	//~ //locale
	//~ G2A(setlocale, char *, int, const char *);
	//~ //math
	//~ /*G1A(cos, double, double);
	//~ G1A(sin, double, double);
	//~ G1A(tan, double, double);
	//~ G1A(acos, double, double);
	//~ G1A(asin, double, double);
	//~ G1A(atan, double, double);
	//~ G2A(atan2, double, double, double);
	//~ G1A(cosh, double, double);
	//~ G1A(sinh, double, double);
	//~ G1A(tanh, double, double);
	//~ G1A(exp, double, double);
	//~ G2A(frexp, double, double, int *);
	//~ //G2A(idexp, double, double, int);
	//~ G1A(log, double, double);
	//~ G1A(log10, double, double);
	//~ G2A(modf, double, double, double *);
	//~ G2A(pow, double, double, double);
	//~ G1A(sqrt, double, double);
	//~ G1A(ceil, double, double);
	//~ G1A(fabs, double, double);
	//~ G1A(floor, double, double);
	//~ G2A(fmod, double, double, double);*/
	//~ //stdio
	//~ G1A(remove, int, const char *);
	//~ G2A(rename, int, const char *, const char *);
	//~ G1A(fclose, int, FILE *);
	//~ G1A(fflush, int, FILE *);
	//~ G2A(fopen, FILE *, const char *, const char *);
	//~ G3A(freopen, FILE *, const char *, const char *, FILE *);
	//~ //G2A(setbuf, void, FILE *, char *);
	//~ //G3A(setvbuf, int, FILE *, char *, int, size_t);
	//~ G1A(fgetc, int, FILE *);
	//~ G3A(fgets, char *, char *, int, FILE *);
	//~ G2A(fputc, int, int, FILE *);
	//~ G2A(fputs, int, const char *, FILE *);
	//~ G0A(getchar, int);
	//~ G1A(gets, char *, char *);
	//~ G1A(putchar, int, int);
	//~ G1A(puts, int, const char *);
	//~ G2A(ungetc, int, int, FILE *);
}
void libshadeinit(){
	G2A(add, int *, int *, int *);
	G1A(puts, int, const char *);
}
}
