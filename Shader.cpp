#include "Shader.h"

char* fail(FILE* file, char* buffer) {
	if (file) {
		int saved_errno = errno;
		fclose(file);
		errno = saved_errno;
	}
	if (buffer) {
		free(buffer);
	}
	return NULL;
}

char* readFile(const char* file_path)
{
	FILE* f = NULL;
	char* buffer = NULL;

	errno_t err = fopen_s(&f, file_path, "rb");
	if (err != NULL) return fail(f, buffer);

	if (fseek(f, 0, SEEK_END) < 0) return fail(f, buffer);

	long size = ftell(f);
	if (size < 0) return fail(f, buffer);

	buffer = (char*)malloc(size + 1);
	if (buffer == NULL) return fail(f, buffer);

	if (fseek(f, 0, SEEK_SET) < 0) return fail(f, buffer);

	fread(buffer, sizeof(char), size, f);
	if (ferror(f)) return fail(f, buffer);

	buffer[size] = '\0';
	printf("last: %s", buffer);
	if (f) {
		fclose(f);
		errno = 0;
	}
	return buffer;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	const char* vertexCode = readFile(vertexFile);
	const char* fragmentCode = readFile(fragmentFile);
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	free((void*)vertexCode);
	free((void*)fragmentCode);
}
