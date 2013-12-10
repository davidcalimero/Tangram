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


	int screenshot(std::string _filename, int _w, int _h) {
		std::cout << _w << "  " << _h << std::endl;

		_filename.append(date_time());
		_filename.append(".bmp");
		std::cout << _filename << std::endl;
		glutSwapBuffers();
        
		/*std::vector< unsigned char > buf( _w * _h * 3 );
		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
        	glReadPixels( 0, 0, _w, _h, GL_RGB, GL_UNSIGNED_BYTE, &buf[0] );
		return SOIL_save_image( _filename.c_str(), SOIL_SAVE_TYPE_BMP, _w, _h, 3, &buf[0]);*/
		
		return SOIL_save_screenshot(_filename.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, _w, _h);
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

					//std::cout << "Atributo: " << attr->name() << std::endl;
					//std::cout << "Valor q[" << i << "]" << quaternion[i] << std::endl;	

					valueStream.str("");
					valueStream << quaternion[i];					
					strQuat[i] = std::string(valueStream.str());

					//std::cout << "Valor:" << strQuat[i].data() << std::endl;
					attr->value(strQuat[i].data(), valueStream.str().length());

					//std::cout << "Valor:" << attr->value() << std::endl;
				}

				// Position
				i = 0;
				temp = child->first_node("position");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {

					//std::cout << "Atributo: " << attr->name() << std::endl;
					//std::cout << "Valor p[" << i << "]" << position[i] << std::endl;	

					valueStream.str("");
					valueStream << position[i];					
					strPos[i] = std::string(valueStream.str());

					//std::cout << "Valor:" << strPos[i].data() << std::endl;
					attr->value(strPos[i].data(), valueStream.str().length());

					//std::cout << "Valor:" << attr->value() << std::endl;
					
				}

			}
		}

		// Printing the new XML tree to the file

		//std::cout << doc << std::endl;

		std::string data;
		std::ofstream streamfile;
		streamfile.open(file);
		rapidxml::print(std::back_inserter(data), doc);
		streamfile << data;
		streamfile.close();	
	}


	void Utils::loadObj(char* filename, std::vector<unsigned int> &indices, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals){
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
				//std::cout << "vertices " << v.x << " " << v.y << " " << v.z << std::endl;
			}
			else if (line.substr(0,3) == "vt "){
				std::istringstream s(line.substr(3));
				glm::vec2 v; 
				s >> v.x >> v.y;
				uvs.push_back(v);
				//std::cout << "uvs " << v.x << " " << v.y << std::endl;
			}
			else if (line.substr(0,3) == "vn "){
				std::istringstream s(line.substr(3));
				glm::vec3 v; 
				s >> v.x >> v.y >> v.z;
				normals.push_back(v);
				//std::cout << "normals " << v.x << " " << v.y << " " << v.z << std::endl;
			}
			else if (line.substr(0,2) == "f ") {
				std::istringstream s(line.substr(2));
				std::string item, face;
				int i = 0;
				while(getline(s, face, ' ')){
					std::istringstream s1(face.substr(0));
					while(getline(s1, item, '/')){
						if(i == 0) indices.push_back(stoi(item)-1);
						else if(i == 1) uvIndices.push_back(stoi(item)-1);
						else if(i == 2) normalIndices.push_back(stoi(item)-1);
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
}
