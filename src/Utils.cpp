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

			glGetShaderInfoLog(ProgramShader::getInstance()->getVertexShaderId(), sizeof(result), &maxLength, result);
			if(maxLength > 11)
				std::cerr << "Error Vertex Shader: " << result;

			glGetShaderInfoLog(ProgramShader::getInstance()->getFragmentShaderId(), sizeof(result), &maxLength, result);
			if(maxLength > 11)
				std::cerr << "Error Fragment Shader: " << result;

			glGetProgramInfoLog(ProgramShader::getInstance()->getProgramId(), sizeof(result), &maxLength, result);
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
	
}