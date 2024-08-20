#include <stdio.h>
#include <filesystem>
#include <vector>
#include <fstream>

using namespace std;

bool validName(string name)
{
	if (name.length() == 0)
		return false;

	return true;
}

int main(int argc, char *argv[])
{

	if (argc > 1)
	{
		string name = argv[1];
		if (validName)
		{
			// create a new directory with the name of the first arg, create a folder with a src and a plugin.yml
			filesystem::path dir = name;
			filesystem::path initialDirectory = filesystem::current_path();
			create_directory(dir);
			current_path(dir);

			// create the plugin.yml
			ofstream file;

			dir = "src/me/jstaples/" + name;
			create_directories(dir);
			current_path(dir);

			// Create start file
			file.open("Main.java");
			if (file.is_open())
			{
				file << "package me.jstaples." << name << ";" << endl
					 << endl;
				file << "import org.bukkit.plugin.java.JavaPlugin;" << endl
					 << endl;
				file << "public class Main extends JavaPlugin {" << endl;
				file << "	public void onEnable() {" << endl;
				file << "	}" << endl;
				file << "}" << endl;

				file.close();
			}

			printf("Project %s created.\n", name.c_str());
			printf("Compiling the jar...\n");

			current_path(initialDirectory);

			std::vector<std::string> javaFiles;
			for (const auto &entry : std::filesystem::recursive_directory_iterator(name))
			{
				if (entry.path().extension() == ".java")
				{
					javaFiles.push_back(entry.path().string());
				}
			}

			std::string compileCommand = "javac -cp PluginBase.jar -d dest/src";
			for (const auto &file : javaFiles)
			{
				compileCommand += " " + file;
			}

			// Compile Java code
			int compileResult = system(compileCommand.c_str());

			// extract the dependency files into the directory for a "Fat jar"
			std::string extractCommand = "cp PluginBase.jar extract.jar && cd dest/src && jar xf ../../extract.jar";
			int extractResult = system(extractCommand.c_str());

			dir = "dest/src";
			current_path(dir);

			// generates plugin.yml
			file.open("plugin.yml");
			if (file.is_open())
			{
				file << "name: " << name << endl;
				file << "version: 1.0.0" << endl;
				file << "main: me.jstaples." + name + ".Main" << endl;

				file.close();
			}

			// creates final jar
			std::string jarCommand = "jar cvf " + name + ".jar *";
			int jarResult = system(jarCommand.c_str());

			// cleanup
			std::string cleanupCommand = "mv " + name + ".jar ../../ && cd ../../ && rm -rf dest && rm -rf " + name + " && rm extract.jar";
			int cleanupResult = system(cleanupCommand.c_str());

			printf("%s jar successfully created", name.c_str());
		}

		return 0;
	}

	printf("Invalid arguments\n");
	return 1;
}
