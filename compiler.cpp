#include <stdio.h>
#include <filesystem>
#include <fstream>

using namespace std;

bool validName(string name) {
	if(name.length() == 0) return false;

	return true;
}

int main(int argc, char *argv[]) {
	
	if(argc > 1) {
		string name = argv[1];
		if(validName) {
			// create a new directory with the name of the first arg, create a folder with a src and a plugin.yml
			filesystem::path dir = name;
			create_directory(dir);
			current_path(dir);
			
			dir = "src";
			create_directory(dir);
			current_path(dir);
			
			// create the plugin.yml
			ofstream file;
			file.open("plugin.yml");
			if(file.is_open()) {
				file << "name: TestPlugin" << endl;
				file << "version: 1.0.0" << endl;
				file << "main: me.jstaples.TestPlugin.Main" << endl;

				file.close();
			}

			dir = "me/jstaples/TestPlugin";
			create_directories(dir);
			current_path(dir);

			// Create start file
			file.open("Main.java");
			if(file.is_open()) {
				file << "package me.jstaples.TestPlugin;" << endl << endl;
				file << "public class Main {" << endl;
				file << "	public void onEnable() {" << endl;
				file << "	}" << endl;
				file << "}" << endl;

				file.close();
			}

			printf("Project %s created.\n", name.c_str());
		}

		return 0;
	}

	printf("Invalid arguments\n");
	return 1;
}

