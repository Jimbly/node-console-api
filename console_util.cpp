// hello.cc
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <napi.h>

#include <string>

using namespace Napi;

static void consoleSetPalette(unsigned int palette[16])
{
	#ifdef _WIN32
	const int color_map[16] = { 0, 4, 2, 6, 1, 5, 3, 7, 8, 12, 10, 14, 9, 13, 11, 15 };

	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX sbi = {0};
	sbi.cbSize = sizeof(sbi);
	GetConsoleScreenBufferInfoEx(hConsoleOut, &sbi);
	for(int i = 0; i < 16; i++)
		sbi.ColorTable[i] = palette[color_map[i]];
	SetConsoleScreenBufferInfoEx(hConsoleOut, &sbi);

	#endif
}

Value setPalette(const CallbackInfo &info) {
  Env env = info.Env();

  if (info.Length() != 1) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsArray()) {
    TypeError::New(env, "Argument must be an Array").ThrowAsJavaScriptException();
    return env.Null();
  }
  Array arr = info[0].As<Array>();

  if (arr.Length() != 16) {
    TypeError::New(env, "Argument Array must be length 16").ThrowAsJavaScriptException();
    return env.Null();
  }

  unsigned int palette[16];
  for (size_t ii = 0; ii < 16; ++ii) {
  	Value v = arr[ii];
  	unsigned int rgb = v.As<Number>().Uint32Value();
	  palette[ii] = ((rgb & 0xFF0000) >> 16) | (rgb & 0x00FF00) | ((rgb & 0x0000FF) << 16);
  }
  consoleSetPalette(palette);
  return env.Null();
}

Value setTitle(const CallbackInfo &info) {
  Env env = info.Env();

  if (info.Length() != 1) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  String str_value = info[0].ToString();
  std::string str = str_value;

  #ifdef _WIN32
  SetConsoleTitle(str.c_str());
  #endif

  return env.Null();
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "setPalette"), Function::New(env, setPalette));
  exports.Set(String::New(env, "setTitle"), Function::New(env, setTitle));
  return exports;
}

NODE_API_MODULE(addon, Init)