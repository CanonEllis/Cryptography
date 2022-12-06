#include <emscripten/emscripten.h>
// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/embind.html
#include "emscripten/bind.h"
#include <string>
#include <stdlib.h>
#include <thread>
#include <chrono>

#include <iostream>
using namespace std;
using namespace emscripten;
using namespace std::chrono;

struct EncryptionPacket {
  string phrase;
  string key;
  string version;
  int shift;
};

string caesar(string text, int s, string version)
{
  auto start = std::chrono::high_resolution_clock::now();
  string result = "";
  if(version == "-p"){
    // traverse text
    for (int i = 0; i < text.length(); i++) {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);

        // Encrypt Lowercase letters
        else
            result += char(int(text[i] + s - 97) % 26 + 97);
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Return the resulting string
    std::chrono::duration<double> diff = end - start;
    cout << to_string(diff.count()) << "\n";
    return to_string(diff.count());
    //return result;
  } else if(version == "-e"){
      for (int i = 0; i < text.length(); i++) {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);

        // Encrypt Lowercase letters
        else
            result += char(int(text[i] + s - 97) % 26 + 97);
    }

    // Return the resulting string
    cout << result << "\n";
    return result;



  }else{
    cout << "ERROR: Improper Formatting of Function Variables: String, Int, String" << "\n";
    return "ERROR: Improper Formatting of Function Variables: String,Int, String";
  }
}

string rot13(string text, string version)
{
  auto start = std::chrono::high_resolution_clock::now();
	string transformed;
  if(version == "-p"){
    for (size_t i = 0; i < text.size(); ++i) {
  		if (isalpha(text[i])) {
  			if ((tolower(text[i]) - 'a') < 14)
  				transformed.append(1, text[i] + 13);
  			else
  				transformed.append(1, text[i] - 13);
  		} else {
  			transformed.append(1, text[i]);
  		}
  	}
  	//return transformed;
    auto end = std::chrono::high_resolution_clock::now();
    // Return the resulting string
    std::chrono::duration<double> diff = end - start;
    cout << to_string(diff.count()) << "\n";
    return to_string(diff.count());
  } else if(version == "-e"){
    for (size_t i = 0; i < text.size(); ++i) {
  		if (isalpha(text[i])) {
  			if ((tolower(text[i]) - 'a') < 14)
  				transformed.append(1, text[i] + 13);
  			else
  				transformed.append(1, text[i] - 13);
  		} else {
  			transformed.append(1, text[i]);
  		}
  	}
  	//return transformed;
    // Return the resulting string
    cout << transformed << "\n";

    return transformed;
  }else{
    cout << "ERROR: Improper Formatting of Function Variables: String, String" << "\n";
    return "ERROR: Improper Formatting of Function Variables: String,String";
  }
}

string vig(string str, string key, string version)
{
  auto start = std::chrono::high_resolution_clock::now();

	string cipher_text;

	int x = str.size();

  if(version == "-p"){
    for (int i = 0; ; i++)
  	{
  		if (x == i)
  			i = 0;
  		if (key.size() == str.size())
  			break;
  		key.push_back(key[i]);
  	}

  	for (int i = 0; i < str.size(); i++)
  	{
  		// converting in range 0-25
  		char x = (str[i] + key[i]) %26;

  		// convert into alphabets(ASCII)
  		x += 'A';

  		cipher_text.push_back(x);
  	}
  	//return cipher_text;
    auto end = std::chrono::high_resolution_clock::now();

    // Return the resulting string
    std::chrono::duration<double> diff = end - start;
    cout << to_string(diff.count()) << "\n";
    return to_string(diff.count());

  } else if(version == "-e"){
    for (int i = 0; ; i++)
    {
      if (x == i)
        i = 0;
      if (key.size() == str.size())
        break;
      key.push_back(key[i]);
    }

    for (int i = 0; i < str.size(); i++)
    {
      // converting in range 0-25
      char x = (str[i] + key[i]) %26;

      // convert into alphabets(ASCII)
      x += 'A';

      cipher_text.push_back(x);
    }
    //return cipher_text;
    // Return the resulting string
    cout << cipher_text << "\n";
    return cipher_text;
  }else{
    cout << "ERROR: Improper Formatting of Function Variables: String, String, String" << "\n";
    return "ERROR: Improper Formatting of Function Variables: String, String, String";
  }

}

void Threaded(string selector, struct EncryptionPacket encp){
  //cout << "Entered Threaded Function" << "\n";
  if(selector == "caesar"){
    thread th1(caesar,encp.phrase, encp.shift,encp.version);
    th1.join();

    cout << "Done with Caesar" << "\n";


  } else if( selector == "rot13"){

    thread th2(rot13,encp.phrase,encp.version);
    th2.join();

    cout << "Done with rot13" << "\n";


  }else if( selector == "vigenere"){

    thread th3(vig,encp.phrase,encp.key,encp.version);
    th3.join();
    cout << "Done with vigenere" << "\n";
  }

}

int main()
{
  // struct EncryptionPacket enc;
  // enc.phrase = "hello does this work, I really hope it does";
  // enc.key = "HLOL";
  // enc.version = "-p";
  // enc.shift = 1;
  // string cypher1 = "caesar";
  // string cypher2 = "rot13";
  // string cypher3 = "vigenere";
  // auto start = std::chrono::high_resolution_clock::now();
	// Threaded(cypher1,enc);
  // Threaded(cypher2,enc);
  // Threaded(cypher3,enc);
  // auto end = std::chrono::high_resolution_clock::now();
  // // Return the resulting string
  // std::chrono::duration<double> diff = end - start;
  // cout << "Total Time of ONE Multithread Run: " << "\n";
  // cout << to_string(diff.count()) << "\n";

//return 0;
}
EMSCRIPTEN_BINDINGS(my_module)
{
  value_object<EncryptionPacket>("EncryptionPacket")
  .field("phrase", &EncryptionPacket::phrase)
  .field("key", &EncryptionPacket::key)
  .field("version", &EncryptionPacket::version)
  .field("shift", &EncryptionPacket::shift);
  emscripten::function("Threaded", &Threaded);
  emscripten::function("caesar", &caesar);
  emscripten::function("rot13", &rot13);
  emscripten::function("vig", &vig);
}
