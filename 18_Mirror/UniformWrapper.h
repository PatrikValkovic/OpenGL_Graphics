#ifndef __UNIFORM_WRAPPER_H__
#define __UNIFORM_WRAPPER_H__

#include <map>
#include <string>
#include <glad/glad.h>

class UniformWrapper
{
private:
	std::map<GLuint, std::map<std::string, GLint>> _mapping;
public:
	UniformWrapper() = default;
	UniformWrapper(const UniformWrapper&) = default;
	UniformWrapper(UniformWrapper&&) = default;
	UniformWrapper& operator=(const UniformWrapper&) = default;
	UniformWrapper& operator=(UniformWrapper&&) = default;
	virtual ~UniformWrapper() = default;

	GLint uniformloc(GLuint program, const std::string &name) noexcept;
	GLint onlyLocationFor(GLuint program) const;
	GLint operator()(GLuint program, const std::string& name) noexcept;
};

#endif