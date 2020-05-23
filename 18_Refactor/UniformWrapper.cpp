#include "UniformWrapper.h"
#include <iostream>
#include <exception>


GLint UniformWrapper::uniformloc(GLuint program, const std::string& name) noexcept
{
    glUseProgram(program);
    std::map<std::string, GLint>& program_mapping = _mapping[program];
    auto nameiter = program_mapping.find(name);
    if (nameiter == program_mapping.end()) {
        GLint location = glGetUniformLocation(program, name.c_str());
        if (location == -1) {
            std::cerr << "Uniform variable " << name << " not found " << std::endl;
        }
        program_mapping.insert(std::make_pair(name, location));
        return location;
    }

    return nameiter->second;
}

GLint UniformWrapper::onlyLocationFor(GLuint program) const
{
    auto programiter = _mapping.find(program);
    if (programiter == _mapping.end() || programiter->second.size() != 1) {
        throw std::logic_error("Program has more uniform variables");
    }
    return programiter->second.begin()->second;
}

GLint UniformWrapper::operator()(GLuint program, const std::string& name) noexcept
{
    return this->uniformloc(program, name);
}
