/*
* Level_System.h
*
*/
#pragma once

#include <cstdlib>
#include <Python.h>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#undef snprintf
#include <nlohmann/json.hpp>
#include <fstream>
#include "cScreen.h"

class Level_System : public cScreen {
public:
	using json = nlohmann::json;
	sf::Font mainFont;


	//SFML Text definition. Needed to display the text
	sf::Text BeiBei_Text;

	sf::Text resultText;


	sf::Text Player_Text;

	/*declare the SFML variables for the player string
	the sf string displays the graphic, the std converts it to */
	sf::String sfPlayer_String;
	std::string psstring; // player code as c++ string
	const char *cPlayerString = &(psstring[0]); //convert player code to c string

	virtual int Run(sf::RenderWindow &App);

private:
	void BeiBeiDisplay();

	void execCode(const char* cPlayerString);

	//store.txt stores the result of executed code
	std::fstream storeFile{ "store.txt" };

	//write.py stores the python script to be executed
	std::fstream writeFile;

	//A button to execute the code
	sf::Sprite execButton;

	//Button to execute code and submit answer
	sf::Sprite submitButton;

	//read mouse functionality
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	sf::Sprite BeiBei;
	sf::Sprite compScreen;

	sf::Text consoleIn;

	//display if the program executed the right code or not
	sf::Text afterCheck;

	void checkAns();
};



void Level_System::BeiBeiDisplay()
{
	mainFont.loadFromFile("capAssets/Fonts/_bitmap_font____romulus_by_pix3m-d6aokem.ttf");
}

int Level_System::Run(sf::RenderWindow &App) {
	bool Running = true;
	sf::Event event;
	float offsetCount = 24;

	mainFont.loadFromFile("capAssets/Fonts/_bitmap_font____romulus_by_pix3m-d6aokem.ttf");

	Player_Text.setFont(mainFont);
	Player_Text.setCharacterSize(24);
	Player_Text.setFillColor(sf::Color::White);
	Player_Text.setPosition({ 130.f, 100.f });

	consoleIn.setFont(mainFont);
	consoleIn.setCharacterSize(24);
	consoleIn.setFillColor(sf::Color::White);
	consoleIn.setString(">>>");
	consoleIn.setPosition({ 100.f, 100.f });

	afterCheck.setFont(mainFont);
	afterCheck.setCharacterSize(24);
	afterCheck.setFillColor(sf::Color::White);

	sf::Texture textureBackground;
	textureBackground.loadFromFile("capAssets/UI/Full_Background_Pixel.png");

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//this sets the texture of the main "puzzle screen"
	sf::Texture textureScreen;
	textureScreen.loadFromFile("capAssets/UI/Windows_Screen.png");
	compScreen.setTexture(textureScreen);
	compScreen.setPosition({ 0.f, 0.f });

	//this sets the texture and position of Bei Bei
	sf::Texture beiBeiTexture;
	beiBeiTexture.loadFromFile("capAssets/Panda/BeiBei.png");
	BeiBei.setTexture(beiBeiTexture);
	BeiBei.setPosition({ 1200, 550 });

	sf::Texture button1;
	button1.loadFromFile("capAssets/UI/SubmitCode.png");
	submitButton.setTexture(button1);

	sf::Texture button2;
	button2.loadFromFile("capAssets/UI/ExecuteCode.png");

	execButton.setTexture(button2);


	/*
	* Below:
	* set positions for a button to execute the code
	* and a button to execute the code and check it against
	* the answer for the problem
	*
	*/
	submitButton.setPosition({ 775, 775 });
	execButton.setPosition({ 475, 775 });

	float submitButtonWidth = submitButton.getLocalBounds().width;
	float submitButtonHeight = submitButton.getLocalBounds().height;

	float execButtonWidth = execButton.getLocalBounds().width;
	float execButtonHeight = execButton.getLocalBounds().height;

	while (Running) {


		while (App.pollEvent(event)) {

			if (event.key.code == sf::Keyboard::Escape) {
				return (0);
				break;
			}

			if (event.type == sf::Event::MouseMoved)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePos = sf::Mouse::getPosition(App);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				if (event.mouseButton.button == sf::Mouse::Left && execButton.getGlobalBounds().contains(mousePosF))
				{
					writeFile.open("write.py");
					if (writeFile.is_open()) {
						writeFile.clear();
						writeFile << psstring;
					}
					writeFile.close();
					execCode(cPlayerString);

				}

				if (event.mouseButton.button == sf::Mouse::Left && submitButton.getGlobalBounds().contains(mousePosF))
				{
					writeFile.open("write.py");
					if (writeFile.is_open()) {
						writeFile.clear();
						writeFile << psstring;
					}
					writeFile.close();
					execCode(cPlayerString);
					checkAns();

				}
			}


			/*
			* Below: Poll the keyboard entry in SFML
			* Read in text near to real time and set the input string
			* to the entries. Checks for unique unicode characters are listed.
			*
			*/
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) {
					psstring = Player_Text.getString();
					if (event.text.unicode == 32) //spacebar
					{
						psstring += " ";
						Player_Text.setString(psstring);
					}
					if (event.text.unicode == 9) //tab
					{
						psstring += "\t";
						Player_Text.setString(psstring);
					}

					if (event.text.unicode == 13)//carriage return
					{
						psstring += "\n";
						Player_Text.setString(psstring);
						offsetCount += 24; //this variable is used for placement of the result when the code is executed
					}

					if (event.text.unicode == 8) //backspace
					{
						if (psstring.size() > 0) {
							psstring.resize(psstring.size() - 1);
							Player_Text.setString(psstring);
						}
					}

					//everything else	
					else
					{
						psstring += static_cast<char>(event.text.unicode);
						Player_Text.setString(psstring);
					}

				}
			}
		}



		App.clear();
		App.draw(spriteBackground);
		App.draw(BeiBei);
		App.draw(compScreen);
		App.draw(consoleIn);

		App.draw(execButton);
		App.draw(submitButton);
		App.draw(Player_Text);

		//set the result text
		sf::Vector2f playPos = Player_Text.getPosition();
		resultText.setPosition({ 100.f, playPos.y + offsetCount });

		sf::Vector2f resultPos = resultText.getPosition();
		afterCheck.setPosition({ 100.f, resultPos.y + 24 });



		App.draw(resultText);
		App.draw(afterCheck);
		App.display();
	}
	return -1;

}


void Level_System::execCode(const char* cPlayerString)
{
	Py_Initialize();

	//the expected output, the player's output, and the compare functions
	//PyObject* expectAnswer; //the expected answer for the level
	PyObject* main = PyImport_AddModule("__main__");
	PyObject* globalDictionary = PyModule_GetDict(main);
	PyObject* localDictionary = PyDict_New();
	//PyObject* result = PyRun_String(cPlayerString, Py_eval_input, globalDictionary, localDictionary);


	if (PyErr_Occurred()) {
		PyErr_Print();
		PyErr_Clear();

	}
	else {

		std::string stdOutErr =
			"import sys\n\
class CatchOutErr:\n\
    def __init__(self):\n\
        self.value = ''\n\
    def write(self, txt):\n\
        self.value += txt\n\
catchOutErr = CatchOutErr()\n\
sys.stdout = catchOutErr\n\
sys.stderr = catchOutErr\n\
"; //this is python code to redirect stdouts/stderr


		PyRun_SimpleString(stdOutErr.c_str());
//#pragma warning(suppress : 4996)
		FILE* readFile = fopen("write.py", "r");

		PyObject *catcher = PyObject_GetAttrString(main, "catchOutErr"); //get our catchOutErr created above
		//read the script from the file ande execute as python code
		PyObject* result = PyRun_File(readFile, "write.py", Py_file_input, globalDictionary, localDictionary);




		//close the file with the Python Script
		//must be done everytime for the code to execute properly
		//every time

		fclose(readFile);

		PyObject *output = PyObject_GetAttrString(catcher, "value"); //get the stdout and stderr from our catchOutErr object
		PyErr_Print(); //make python print any errors
		PyObject* ccheck = PyUnicode_AsEncodedString(output, "utf-8", "strict");
		const char* printCheck = PyBytes_AsString(ccheck);
		printf("Here's the output:\n %s", printCheck);


		PyObject *ioMod, *openedFile;
		PyGILState_STATE gilState = PyGILState_Ensure();
		ioMod = PyImport_ImportModule("io");
		openedFile = PyObject_CallMethod(ioMod, "open", "ss", "store.txt", "wb");

		//it is equivalent to python code : str(Object)
		PyObject* objectsRepresentation = PyObject_Str(result);
		PyObject* encoded = PyUnicode_AsEncodedString(objectsRepresentation, "utf-8", "strict");

		//convert Python String Object to C++ char*
		const char* capChar = PyBytes_AS_STRING(encoded);

		
		std::string writeString(capChar);


		PyObject_CallMethod(openedFile, "write", "y", printCheck);
		PyObject_CallMethod(openedFile, "flush", NULL);
		PyObject_CallMethod(openedFile, "close", NULL);
		Py_DECREF(ioMod);
		Py_DECREF(openedFile);

		PyGILState_Release(gilState);
		Py_Finalize();

		/*
		*
		*/


		sf::String sfResString(printCheck);


		resultText.setString(printCheck);
		resultText.setFont(mainFont);
		resultText.setCharacterSize(24);
		resultText.setFillColor(sf::Color::White);

		/*
		* Debug lines in the console that
		* check to see if conversions are occurring properly.
		* Function typeid(resString).name() returns the type that resString is.
		* s1 = resultText and std::cout << s1  returns the string stored in
		* result text. As it is:
		* The typeid(resString).name() always returns proper structure for std::string.
		* Returns string value of basic arithmetic functions in Python code:
		* ex: 2 + 7 returns 9 as a string value
		* Returns 'None' if a Python function such as print('string') is called.
		*/
		std::string s1 = sfResString.toAnsiString(std::locale());
		std::cout << "\nresString typeid is: " << typeid(writeString).name() << std::endl;
		std::cout << "resString data stored is : " << writeString.data() << std::endl;
		std::cout << writeString << std::endl;
		//std::cout << "sfResString typeid is: " << typeid(sfResString).name() << std::endl;
		//std::cout << "data stored in sfResString is: " << s1.data() << std::endl;


	}

	Py_Finalize();
}


void Level_System::checkAns()
{
	std::ifstream jIn("test.json");

	json jSoIn;

	jIn >> jSoIn;

	std::string userComp;
	std::string expectedComp;
	try {
		if (jSoIn.find("expectedAns") != jSoIn.end())
		{
			userComp = jSoIn.at("expectedAns").is_string();
			std::cout << userComp << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	/*
	* Compare strings in two files
	* If same, level passes
	* If not, restart
	*/
	std::string finalComp;

	//this is required with finalComp
	//because the parser reads in the string with quotation marks
	//this removes the quotation marks from the expected answer
	//in the JSON file.
	for (int i = 1; i < userComp.length() - 1; i++)
	{
		finalComp += userComp[i];
	}

	//open the stored file with the answer
	storeFile.open("store.txt");

	//read in the file to a string
	while (storeFile >> expectedComp);


	//compare the strings
	if (expectedComp == finalComp)
	{
		std::cout << "The two strings are equal" << std::endl;
		afterCheck.setString("That code was right!");
	}
	else {
		std::cout << "The two strings are not equal" << std::endl;
		afterCheck.setString("That code is not quite right. Try again");
	}

}
