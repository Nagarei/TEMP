//for VC++

template<typename FUNC>
struct Finally_C {
	Finally_C(FUNC&& func_):func(std::forward<FUNC>(func_)){}
	~Finally_C() { func(); }
	FUNC func;
};
template<typename FUNC>
Finally_C<FUNC> Finally(FUNC&& func_) {
	return Finally_C<FUNC>{ std::forward<FUNC>(func_) };
}
#define FINALLY_2(FUNC,N) \
	auto&& FINALLY_ ## N ## _FINALLY_ = Finally(FUNC);(void*)(&FINALLY_ ## N ## _FINALLY_)
#define FINALLY_1(FUNC,N) FINALLY_2(FUNC, N)
#define FINALLY(FUNC) FINALLY_1(FUNC, __COUNTER__)

//使い方 how to use
//{
//int* p = new int;
//FINALLY([&p]() {delete p;p = unllptr;);
// //do something...
//}//ここでFINALLYの引数の関数が実行され、pがdeleteされる
