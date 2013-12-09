#include "Utils.h"



namespace Utils {

	bool isOpenGLError() {
		bool isError = false;
		GLenum errCode;
		const GLubyte *errString;

		while ((errCode = glGetError()) != GL_NO_ERROR) {		
			isError = true;
			errString = gluErrorString(errCode);
			std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
		}
		return isError;
	}
	

	void checkOpenGLError(std::string error) {
		int maxLength;
		char result[128];

		if(isOpenGLError()) {
			std::cerr << error << std::endl;

			glGetShaderInfoLog(ProgramShader::getInstance()->getUId("VertexShader"), sizeof(result), &maxLength, result);
			if(maxLength > 11)
				std::cerr << "Error Vertex Shader: " << result;

			glGetShaderInfoLog(ProgramShader::getInstance()->getUId("FragmentShader"), sizeof(result), &maxLength, result);
			if(maxLength > 11)
				std::cerr << "Error Fragment Shader: " << result;

			glGetProgramInfoLog(ProgramShader::getInstance()->getUId("Program"), sizeof(result), &maxLength, result);
			if(maxLength > 11)
				std::cerr << "Error Program: " << result << std::endl;

			exit(EXIT_FAILURE);
		}
	}

	
	GLchar* readFile(char* path){
		std::string line, result;
		std::ifstream myfile(path);
		char* buffer;
		int size;

		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				result += line + "\n";
			}
			myfile.close();
		}
		size = result.size();
		buffer = new char[size];
		memcpy(buffer, result.c_str(), size);
		buffer[size-1] = '\0';
	
		return buffer;
	}

	
	GLubyte * Utils::index(int vertices){
		GLubyte * indices = new GLubyte [vertices];
		for(int i = 0; i < vertices; i++){
			indices[i] = i;
		}
		return indices;
	}
		
	
	Vertex * Utils::xmlParser(char * file, int *nVertices){
		int i = 0, v = 0;
		Vertex * vertices;
		rapidxml::xml_document<> doc;
		doc.parse<0>(readFile(file));
		rapidxml::xml_node<> * node = doc.first_node("object");
		rapidxml::xml_node<> * temp;
		
		*nVertices = 0;
		for(rapidxml::xml_node<> *child = node->first_node("vertex"); child != NULL; child = child->next_sibling(), (*nVertices)++);
		
		vertices = new Vertex[*nVertices];

		for(rapidxml::xml_node<> *child = node->first_node("vertex"); child != NULL; child = child->next_sibling(), v++)
		{
			i = 0;
			temp = child->first_node("position");
			for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++)
			{
				vertices[v].XYZW[i] = atof(attr->value());
			}

			i = 0;
			temp = child->first_node("color");
			for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++)
			{
				vertices[v].RGBA[i] = atof(attr->value());
			}
		}

		return vertices;
	}


	void Utils::loadScene(char * file, std::string id, glm::quat * quaternion, glm::vec3 * position){
		int i;
		rapidxml::xml_document<> doc;
		doc.parse<0>(readFile(file));

		rapidxml::xml_node<> * rootNode = doc.first_node("scene");
		rapidxml::xml_node<> * entitiesNode = rootNode->first_node("entities");
		rapidxml::xml_node<> * temp;

		for(rapidxml::xml_node<> *child = entitiesNode->first_node("entity"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(id) == 0) {
	
				i = 0;
				temp = child->first_node("quaternion");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {
					(*quaternion)[i] = atof(attr->value());
				}

				i = 0;
				temp = child->first_node("position");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++)	{
					(*position)[i] = atof(attr->value());
				}
				
			}
		}	

	}

	void Utils::saveScene(char * file, std::string id, glm::quat quaternion, glm::vec3 position) {
		int i;
		char * charValue = new char[30];
		//std::ostringstream valueStream;

		// Reading the file
		rapidxml::xml_document<> doc;
		doc.parse<0>(readFile(file));

		// Modifying the XML tree
		rapidxml::xml_node<> * rootNode = doc.first_node("scene");
		rapidxml::xml_node<> * entitiesNode = rootNode->first_node("entities");
		rapidxml::xml_node<> * temp;

		for(rapidxml::xml_node<> *child = entitiesNode->first_node("entity"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(id) == 0) {

				i = 0;
				temp = child->first_node("quaternion");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {

					std::cout << "Valor q:" << quaternion[i] << std::endl;	

					sprintf(charValue, "%f", quaternion[i]);
					std::cout << "Valor:" << charValue << std::endl;
					attr->value(charValue);

					//valueStream.str("");
					//valueStream << quaternion[i];
					//std::cout << "Valor:" << valueStream.str().data() << std::endl;	
					//attr->value(valueStream.str().data(), valueStream.str().length());

					std::cout << "Valor:" << attr->value() << std::endl;				
				}
			}
		}

		// Printing the new XML tree to the file
		rapidxml::print(file, doc, 0);
	}


	void Utils::loadObj(char* filename) {
/*		std::vector<glm::vec4> vertices;
		//std::vector<glm::vec4> normals;
		std::vector<glm::vec4> obj;
		std::ifstream in(filename, std::ios::in);
		if(!in){ 
			std::cerr << "Cannot open " << filename << std::endl; 
			exit(1); 
		}
 
		std::string line;
		while (getline(in, line)) {
			if (line.substr(0,2) == "v "){
				std::istringstream s(line.substr(2));
				glm::vec4 v; 
				s >> v.x;
				s >> v.y;
				s >> v.z;
				v.w = 1.0f;
				vertices.push_back(v);
				//std::cout << v.x << " " << v.y << " " << v.z << std::endl;
			}
/*			else if (line.substr(0,3) == "vt "){
				std::istringstream s(line.substr(3));
				glm::vec4 v; 
				s >> v.x;
				s >> v.y;
				s >> v.z;
				v.w = 1.0f;
				vertices.push_back(v);
			}
			else if (line.substr(0,3) == "vn "){
				std::istringstream s(line.substr(3));
				glm::vec4 v; 
				s >> v.x;
				s >> v.y;
				s >> v.z;
				v.w = 1.0f;
				normals.push_back(v);
			}*/
/*			else if (line.substr(0,2) == "f") {
				std::istringstream s(line.substr(2));
				std::string item, face;
				int i = 0;
				while(getline(s, face, ' ')){
					std::istringstream s1(face.substr(0));
					std::cout << face << std::endl;
					while(getline(s1, item, '/')){
						if(i == 0){
							std::cout << item << std::endl;
							obj.push_back(vertices.at(std::stoi(item) - 1));
							std::cout << vertices.at(std::stoi(item) - 1).x << " " << vertices.at(std::stoi(item) - 1).y << " " << vertices.at(std::stoi(item) - 1).z << std::endl;
						}
						i++;
						i = i % 3; 
					}
				}
			}
		}*/
	}
}