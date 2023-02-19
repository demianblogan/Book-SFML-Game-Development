#include "Utilities.h"

#define SWITCH_CASE_KEY_TO_STRING(KEY) case sf::Keyboard::KEY: return #KEY

std::string ConvertToString(sf::Keyboard::Key key)
{
	switch (key)
	{
		SWITCH_CASE_KEY_TO_STRING(Unknown);
		SWITCH_CASE_KEY_TO_STRING(A);
		SWITCH_CASE_KEY_TO_STRING(B);
		SWITCH_CASE_KEY_TO_STRING(C);
		SWITCH_CASE_KEY_TO_STRING(D);
		SWITCH_CASE_KEY_TO_STRING(E);
		SWITCH_CASE_KEY_TO_STRING(F);
		SWITCH_CASE_KEY_TO_STRING(G);
		SWITCH_CASE_KEY_TO_STRING(H);
		SWITCH_CASE_KEY_TO_STRING(I);
		SWITCH_CASE_KEY_TO_STRING(J);
		SWITCH_CASE_KEY_TO_STRING(K);
		SWITCH_CASE_KEY_TO_STRING(L);
		SWITCH_CASE_KEY_TO_STRING(M);
		SWITCH_CASE_KEY_TO_STRING(N);
		SWITCH_CASE_KEY_TO_STRING(O);
		SWITCH_CASE_KEY_TO_STRING(P);
		SWITCH_CASE_KEY_TO_STRING(Q);
		SWITCH_CASE_KEY_TO_STRING(R);
		SWITCH_CASE_KEY_TO_STRING(S);
		SWITCH_CASE_KEY_TO_STRING(T);
		SWITCH_CASE_KEY_TO_STRING(U);
		SWITCH_CASE_KEY_TO_STRING(V);
		SWITCH_CASE_KEY_TO_STRING(W);
		SWITCH_CASE_KEY_TO_STRING(X);
		SWITCH_CASE_KEY_TO_STRING(Y);
		SWITCH_CASE_KEY_TO_STRING(Z);
		SWITCH_CASE_KEY_TO_STRING(Num0);
		SWITCH_CASE_KEY_TO_STRING(Num1);
		SWITCH_CASE_KEY_TO_STRING(Num2);
		SWITCH_CASE_KEY_TO_STRING(Num3);
		SWITCH_CASE_KEY_TO_STRING(Num4);
		SWITCH_CASE_KEY_TO_STRING(Num5);
		SWITCH_CASE_KEY_TO_STRING(Num6);
		SWITCH_CASE_KEY_TO_STRING(Num7);
		SWITCH_CASE_KEY_TO_STRING(Num8);
		SWITCH_CASE_KEY_TO_STRING(Num9);
		SWITCH_CASE_KEY_TO_STRING(Escape);
		SWITCH_CASE_KEY_TO_STRING(LControl);
		SWITCH_CASE_KEY_TO_STRING(LShift);
		SWITCH_CASE_KEY_TO_STRING(LAlt);
		SWITCH_CASE_KEY_TO_STRING(LSystem);
		SWITCH_CASE_KEY_TO_STRING(RControl);
		SWITCH_CASE_KEY_TO_STRING(RShift);
		SWITCH_CASE_KEY_TO_STRING(RAlt);
		SWITCH_CASE_KEY_TO_STRING(RSystem);
		SWITCH_CASE_KEY_TO_STRING(Menu);
		SWITCH_CASE_KEY_TO_STRING(LBracket);
		SWITCH_CASE_KEY_TO_STRING(RBracket);
		SWITCH_CASE_KEY_TO_STRING(SemiColon);
		SWITCH_CASE_KEY_TO_STRING(Comma);
		SWITCH_CASE_KEY_TO_STRING(Period);
		SWITCH_CASE_KEY_TO_STRING(Quote);
		SWITCH_CASE_KEY_TO_STRING(Slash);
		SWITCH_CASE_KEY_TO_STRING(BackSlash);
		SWITCH_CASE_KEY_TO_STRING(Tilde);
		SWITCH_CASE_KEY_TO_STRING(Equal);
		SWITCH_CASE_KEY_TO_STRING(Dash);
		SWITCH_CASE_KEY_TO_STRING(Space);
		SWITCH_CASE_KEY_TO_STRING(Return);
		SWITCH_CASE_KEY_TO_STRING(BackSpace);
		SWITCH_CASE_KEY_TO_STRING(Tab);
		SWITCH_CASE_KEY_TO_STRING(PageUp);
		SWITCH_CASE_KEY_TO_STRING(PageDown);
		SWITCH_CASE_KEY_TO_STRING(End);
		SWITCH_CASE_KEY_TO_STRING(Home);
		SWITCH_CASE_KEY_TO_STRING(Insert);
		SWITCH_CASE_KEY_TO_STRING(Delete);
		SWITCH_CASE_KEY_TO_STRING(Add);
		SWITCH_CASE_KEY_TO_STRING(Subtract);
		SWITCH_CASE_KEY_TO_STRING(Multiply);
		SWITCH_CASE_KEY_TO_STRING(Divide);
		SWITCH_CASE_KEY_TO_STRING(Left);
		SWITCH_CASE_KEY_TO_STRING(Right);
		SWITCH_CASE_KEY_TO_STRING(Up);
		SWITCH_CASE_KEY_TO_STRING(Down);
		SWITCH_CASE_KEY_TO_STRING(Numpad0);
		SWITCH_CASE_KEY_TO_STRING(Numpad1);
		SWITCH_CASE_KEY_TO_STRING(Numpad2);
		SWITCH_CASE_KEY_TO_STRING(Numpad3);
		SWITCH_CASE_KEY_TO_STRING(Numpad4);
		SWITCH_CASE_KEY_TO_STRING(Numpad5);
		SWITCH_CASE_KEY_TO_STRING(Numpad6);
		SWITCH_CASE_KEY_TO_STRING(Numpad7);
		SWITCH_CASE_KEY_TO_STRING(Numpad8);
		SWITCH_CASE_KEY_TO_STRING(Numpad9);
		SWITCH_CASE_KEY_TO_STRING(F1);
		SWITCH_CASE_KEY_TO_STRING(F2);
		SWITCH_CASE_KEY_TO_STRING(F3);
		SWITCH_CASE_KEY_TO_STRING(F4);
		SWITCH_CASE_KEY_TO_STRING(F5);
		SWITCH_CASE_KEY_TO_STRING(F6);
		SWITCH_CASE_KEY_TO_STRING(F7);
		SWITCH_CASE_KEY_TO_STRING(F8);
		SWITCH_CASE_KEY_TO_STRING(F9);
		SWITCH_CASE_KEY_TO_STRING(F10);
		SWITCH_CASE_KEY_TO_STRING(F11);
		SWITCH_CASE_KEY_TO_STRING(F12);
		SWITCH_CASE_KEY_TO_STRING(F13);
		SWITCH_CASE_KEY_TO_STRING(F14);
		SWITCH_CASE_KEY_TO_STRING(F15);
		SWITCH_CASE_KEY_TO_STRING(Pause);

	default:
		return "";
	}
}