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


	void screenshot(std::string _filename, int _w, int _h) {
		_filename.append(date_time());
		_filename.append(".bmp");
        
		std::vector< unsigned char > buf( _w * _h * 3 );

		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
		glReadPixels( 0, 0, _w, _h, GL_RGB, GL_UNSIGNED_BYTE, &buf[0] );
		
		_w= glutGet(GLUT_WINDOW_WIDTH);
		_h = glutGet(GLUT_WINDOW_HEIGHT);
		int state = SOIL_save_screenshot(_filename.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, _w, _h);

		if (!state) std::cout << "Error: Cannot save the screenshot" << std::endl;
		else std::cout << "Saved in " << _filename << std::endl;
	}
	

	std::string date_time(){
	    time_t t = time(0);
		struct tm * now = localtime( & t );

		std::ostringstream datestream;
		datestream  << '_' << now->tm_mday << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900)
					<< '_' << now->tm_hour << '-' << now->tm_min << '-' << now->tm_sec;
		
		std::string s = datestream.str();
		return s;
	}


	void loadScene(char * file, std::string id, glm::quat * quaternion, glm::vec3 * position){
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


	void saveScene(char * file, std::string id, glm::quat quaternion, glm::vec3 position) {
		int i;
		std::string * strPos = new std::string[4];
		std::string * strQuat = new std::string[4];
		std::ostringstream valueStream;

		// Reading the file
		rapidxml::xml_document<> doc;
		doc.parse<0>(readFile(file));

		// Modifying the XML tree
		rapidxml::xml_node<> * rootNode = doc.first_node("scene");
		rapidxml::xml_node<> * entitiesNode = rootNode->first_node("entities");
		rapidxml::xml_node<> * temp;

		for(rapidxml::xml_node<> *child = entitiesNode->first_node("entity"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(id) == 0) {
				
				// Quaternion
				i = 0;
				temp = child->first_node("quaternion");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {
					valueStream.str("");
					valueStream << quaternion[i];					
					strQuat[i] = std::string(valueStream.str());
					attr->value(strQuat[i].data(), valueStream.str().length());
				}

				// Position
				i = 0;
				temp = child->first_node("position");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {
					valueStream.str("");
					valueStream << position[i];					
					strPos[i] = std::string(valueStream.str());
					attr->value(strPos[i].data(), valueStream.str().length());					
				}
			}
		}

		// Printing the new XML tree to the file
		std::string data;
		std::ofstream streamfile;
		streamfile.open(file);
		rapidxml::print(std::back_inserter(data), doc);
		streamfile << data;
		streamfile.close();	
	}


	void loadObj(char* filename, std::vector<unsigned int> &indices, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals){
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> uvIndices;
		std::vector<unsigned int> normalIndices;

		std::ifstream in(filename, std::ios::in);
		if(!in){ 
			std::cerr << "Cannot open " << filename << std::endl; 
			exit(1); 
		}
 
		std::string line;
		while (getline(in, line)) {
			if (line.substr(0,2) == "v "){
				std::istringstream s(line.substr(2));
				glm::vec3 v; 
				s >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			else if (line.substr(0,3) == "vt "){
				std::istringstream s(line.substr(3));
				glm::vec2 v;
				s >> v.x >> v.y;
				uvs.push_back(v);
			}
			else if (line.substr(0,3) == "vn "){
				std::istringstream s(line.substr(3));
				glm::vec3 v; 
				s >> v.x >> v.y >> v.z;
				normals.push_back(v);
			}
			else if (line.substr(0,2) == "f ") {
				std::istringstream s(line.substr(2));
				std::string item, face;
				int i = 0;
				while(getline(s, face, ' ')){
					std::istringstream s1(face.substr(0));
					while(getline(s1, item, '/')){
						if(item.size() && i == 0 && stoi(item) > 0 && stoi(item) <= vertices.size())
							indices.push_back(stoi(item)-1);
						else if(item.size() && i == 1 && stoi(item) > 0 && stoi(item) <= uvs.size())
							uvIndices.push_back(stoi(item)-1);
						else if(item.size() && i == 2 && stoi(item) > 0 && stoi(item) <= normals.size())
							normalIndices.push_back(stoi(item)-1);
						else{
							std::cerr << "Invalid index on " << filename << std::endl; 
							exit(1); 
						}
						i = ++i % 3; 
					}
				}
			}
		}

		for(unsigned int i = 0; i < indices.size(); i++){
			unsigned int vertexIndex = indices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];
		
			glm::vec3 vertex = vertices[vertexIndex];
			glm::vec2 uv = uvs[uvIndex];
			glm::vec3 normal = normals[normalIndex];
		
			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}
	}


	void loadMaterial(char* filename, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular, float &shininess, std::string &texture){
		std::ifstream in(filename, std::ios::in);
		int count = 0;
		if(!in){ 
			std::cerr << "Cannot open " << filename << std::endl; 
			exit(1); 
		}

		std::string line;
		while (getline(in, line)) {
			if (line.substr(0,3) == "Ka "){
				std::istringstream s(line.substr(3));
				s >> ambient.x >> ambient.y >> ambient.z;
				count++;
			}
			else if (line.substr(0,3) == "Kd "){
				std::istringstream s(line.substr(3));
				s >> diffuse.x >> diffuse.y >> diffuse.z;
				count++;
			}
			else if (line.substr(0,3) == "Ks "){
				std::istringstream s(line.substr(3));
				s >> specular.x >> specular.y >> specular.z;
				count++;
			}
			else if (line.substr(0,3) == "Ns "){
				std::istringstream s(line.substr(3));
				s >> shininess;
				count++;
			}
			else if (line.substr(0,7) == "map_Kd "){
				texture = line.substr(7);
				count++;
			}
		}
	}
}
